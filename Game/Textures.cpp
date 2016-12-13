#include <iostream>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "Textures.h"

#pragma comment (lib, "glaux.lib")    /* link with Win32 GLAUX lib usada para ler bitmaps */
extern "C" int read_JPEG_file(char *, char **, int *, int *, int *); // função para ler jpegs do ficheiro readjpeg.c

AUX_RGBImageRec* Textures::LoadBMP(char *filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle
	if (!filename) return NULL;							// Make Sure A Filename Was Given
	File=fopen(filename,"r");							// Check To See If The File Exists
	if (File){											// Does The File Exist?
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;										// If Load Failed Return NULL
}

/**
Loads a Texture into GL
TextEnv - Define modo de mistura da textura com o material. hipoteses possiveis:
GL_REPLACE - usa apenas a cor da textura
GL_MODULATE - cor da textura * cor do material
GL_DECAL - interpolação da cor usando alpha
*/
bool Textures::Load_Texture(GLuint & aTexture, char * filename, bool itsBMP, GLfloat TextEnv, bool setMipMaps) {

	AUX_RGBImageRec *image_record = NULL;		// Create Storage Space For The Texture
    char *image;
    int w, h, bpp;

	if (itsBMP){
		image_record=LoadBMP(filename);
		if (!image_record) 
			return false;						//check that loaded
	} else{
		if(!read_JPEG_file(filename, &image, &w, &h, &bpp))
			return false;						//check that loaded		
	}

	glGenTextures(1, &aTexture);				//generates 1 texture name

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);		//sets how the pixels of the texture are stored

	glBindTexture(GL_TEXTURE_2D, aTexture);		//binds the name to the target

												//Create MipMapped Texture (prefiltered textures at different resolutions)
	if (itsBMP){
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_record->sizeX, image_record->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image_record->data);
	}else{
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
												//give the texture its attributes
	if (setMipMaps){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	}
												//Set envelope mode
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, TextEnv);

	// Now we need to free the image data that we loaded since openGL stored it as a texture
	if (image_record) {							//if we stored data then free the memory
		if (image_record->data) {				//check if there is any data
			free(image_record->data);			//free the memory
		}
		free(image_record);						//free the image record
	}

	glBindTexture(GL_TEXTURE_2D, NULL);

	return true; //everything should have worked so return true

}

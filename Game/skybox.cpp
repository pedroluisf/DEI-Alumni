#include <windows.h>
#include <stdio.h>  
#include <gl\gl.h>							
#include <gl\glu.h>							
#include <gl\glaux.h>
#include "skybox.h"
#include "Textures.h"

void skybox::Init() {

	OFFSET = 1/512.0; //set offset value for skybox

	rot_x = 0.0; rot_y = 0.0;

	//load first set of skybox textures
	Textures::Load_Texture(texture[0],"images/day_clear_left.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[1],"images/day_clear_front.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[2],"images/day_clear_right.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[3],"images/day_clear_back.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[4],"images/day_clear_down.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[5],"images/day_clear_up.bmp", true, GL_REPLACE, true);

	//load second set of skybox textures
	Textures::Load_Texture(texture[6],"images/day_cloud_left.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[7],"images/day_cloud_front.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[8],"images/day_cloud_right.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[9],"images/day_cloud_back.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[10],"images/day_cloud_down.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[11],"images/day_cloud_up.bmp", true, GL_REPLACE, true);

	//load third set of skybox textures
	Textures::Load_Texture(texture[12],"images/night_clear_left.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[13],"images/night_clear_front.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[14],"images/night_clear_right.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[15],"images/night_clear_back.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[16],"images/night_clear_down.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[17],"images/night_clear_up.bmp", true, GL_REPLACE, true);

	//load fourth set of skybox textures
	Textures::Load_Texture(texture[18],"images/night_cloud_left.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[19],"images/night_cloud_front.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[20],"images/night_cloud_right.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[21],"images/night_cloud_back.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[22],"images/night_cloud_down.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(texture[23],"images/night_cloud_up.bmp", true, GL_REPLACE, true);

}

void skybox::draw() {

	glPushMatrix();
		glRotated(rot_x, 1.0, 0.0, 0.0);	//Rotate around the x axis
		glRotated(rot_y, 0.0, 1.0, 0.0);	//Rotate around the y axis

		glColor3f(1.0f,1.0f,1.0f);			//Set colour to White
		glEnable(GL_TEXTURE_2D);			//Enable texture mapping
		glDisable (GL_DEPTH_TEST);			//Disable depth testing

			//before you can use a texture you have to bind it
			glBindTexture(GL_TEXTURE_2D, texture[0 + sky]);
			glBegin (GL_QUADS);		
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,10.0);
			glEnd ();

			glBindTexture(GL_TEXTURE_2D, texture[1 + sky]);
			glBegin (GL_QUADS);		
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,0.0 + OFFSET);	glVertex3d (10.0,-10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,1.0 - OFFSET);	glVertex3d (10.0,10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,-10.0);
			glEnd ();

			glBindTexture(GL_TEXTURE_2D, texture[2 + sky]);
			glBegin (GL_QUADS);		
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,-10.0);
			glEnd ();

			glBindTexture(GL_TEXTURE_2D, texture[3 + sky]);	
			glBegin (GL_QUADS);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);		
			glEnd ();

			glBindTexture(GL_TEXTURE_2D, texture[4 + sky]);	
			glBegin (GL_QUADS);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,-10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,-10.0,-10.0);
			glEnd ();

			glBindTexture(GL_TEXTURE_2D, texture[5 + sky]);
			glBegin (GL_QUADS);		
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,10.0,-10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);
					glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,10.0,10.0);
			glEnd ();

		//Re-Enable the depth test
		glEnable(GL_DEPTH_TEST);
		//disable texture mapping
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
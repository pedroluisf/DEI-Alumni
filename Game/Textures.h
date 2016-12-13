#include <GL\glut.h>
#include <GL/glaux.h>

class Textures {
private:

	static AUX_RGBImageRec* LoadBMP(char *filename);

public:  

	static bool Load_Texture(GLuint & aTexture, char * filename, bool itsBMP, GLfloat TextEnv, bool setMipMaps);

};
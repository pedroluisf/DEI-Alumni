#define MAX_TEXTURES 24
#define SKY_DAY_CLEAR 0
#define SKY_DAY_CLOUD 6
#define SKY_NIGHT_CLEAR 12
#define SKY_NIGHT_CLOUD 18

class skybox {
public:  //just make everything public than you don't have to worry about access

	skybox() { } //constructor

	//bool Load_Texture(unsigned int & aTexture, char * fileName);
	void Init();
	void draw();

	GLuint	texture[MAX_TEXTURES];

	//used to correct the edges of the skybox overlap
	//try setting this to 0.0 in the Init() and you will see the seams of the textures
	double	OFFSET,	rot_x, rot_y;
	//set the type of sky by offset on indexes
	long	sky;
};
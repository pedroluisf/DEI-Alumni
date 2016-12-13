#include <vector>
#include "Encomenda.h"
#include "Tetromino.h"

#define BUFSIZE								512
#define MAX_TEXTURES_CARGO					2
#define ID_TEXTURA_CARGO_BACK						1
#define ID_TEXTURA_CARGO_GO						2

#define MAX_X				26
#define MIN_X				-26
#define MAX_Y				19
#define MIN_Y				-19
#define CARGO_X				-12
#define CARGO_Y				-7
#define CARGO_WIDTH			18
#define CARGO_HEIGHT		16
#define NUM_ENCOMENDAS		6
#define NUM_MAX_BARRAS		4

class cargo {
private: 

	int num_objectos;

	// arrays de encomendas em jogo, de barras de frio e objectos (são todos objectos encomenda)
	vector<Encomenda*> *encomendas;
	vector<Encomenda*> *encomendas_entregues;
	vector<Encomenda*> *frios;
	vector<Encomenda*> *objectos;

	// a matriz completa de posicao --> controla todos os objectos em jogo
	// X -> colunas // Y -> linhas
	// vai ser necessário corrigir a origem: [0][0] em (-19,-26)
	int matObjectos[MAX_Y*2+1][MAX_X*2+1];

	// encomenda seleccionada 
	int selIdx;

	void GetOGLPos(int x, int y, int nx, int ny);

	char cargoHold[CARGO_HEIGHT][CARGO_WIDTH+1];

	// modo: carga / true - descarga / false
	bool cargo_mode;

	void updateMatObjectos(int idx, int val);bool checkLoaded();

	void cargo::entregaEncomendas(string no);
	
	bool checkAllUnloaded();

	void initObjectos();

	bool checkSelfCubo(GLint x, GLint y, GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3);

	bool validaCarga();

	void strokeCenterString(char *str,double x, double y, double z, double s);

	bool checkColisao(GLint nx0, GLint ny0, GLint no);

	void moveTetromino(GLint nx, GLint ny);

	void setVisualArea (bool pick, int x, int y);

	void desenhaCargoHold();

	void drawGOButton ();

	void drawUserFeedBack ();

	void mostraTempoJogo();

	void drawCargoBoxs ();

	void pickPackage (GLint hits, GLuint buffer[]);

	void dragPackage (int x, int y, int z);

public:  

	//Texturas próprias
	GLuint	cargoTextures[MAX_TEXTURES_CARGO];

	cargo() { } //constructor

	char msgUser [100];

	int timeElapsed;

	int hourStarted;

	int minuteStarted;

	bool startDrag;

	void dragCargo (int x, int y);

	void Init(vector<Encomenda*>* jencomendas, vector<Encomenda*>* jencomendas_entregues);

	void initModelo();

	bool checkAllLoaded();

	bool cargo::checkTodasEncomendasEntreguesEmNo(string no);

	void draw(string no);

	void picking(int x, int y);

	void rodaTetromino();	
	
};
#define _WINSOCKAPI_
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <AL\alut.h>

#include "stdafx.h"
#include "Website.h"
#include "Model_3DS.h"
#include "Bean.h"
#include "Jogo.h"
#include "mathlib.h"
#include "studio.h"
#include "mdlviewer.h"
#include "Textures.h"
#include "Grafo.h"
#include "skybox.h"
#include "menu.h"
#include "cargo.h"
#include "Ai.h"
#include "includes\INT386W.HPP"

using namespace std;

#define graus(X) (double)((X)*180./M_PI)
#define rad(X)   (double)((X)*M_PI/180.)
#define round(X) (int) (X+0.5)
#define darco(X,R) (double) X*R //X em radianos

#define NUM_TEXTURAS					8
string Texturas_File_Array[NUM_TEXTURAS] = {
	"pavement-road.jpg",
	"pavement-stone.jpg",
	"pavement-street.jpg",
	"houses2.bmp",
	"houses2_mask.bmp",
	"rotunda.jpg",
	"btn_off.jpg",
	"sand.jpg"
};
#define ID_TEXTURA_PAVIMENTO_ESTRADA		0
#define ID_TEXTURA_PAVIMENTO_PARALELO		1
#define ID_TEXTURA_PAVIMENTO_GRAVILHA		2
#define ID_TEXTURA_CASAS					3
#define ID_TEXTURA_CASAS_MASK				4
#define ID_TEXTURA_ROTUNDA					5
#define ID_TEXTURA_BOTAO					6
#define ID_TEXTURA_AREIA					8

#define ALTURA_PAREDE 0.75

GLuint  myTextures[NUM_TEXTURAS];
GLTexture tgaTextures;

// luzes e materiais

const GLfloat mat_ambient[][4] = {{0.33, 0.22, 0.03, 1.0},	// brass
{0.0, 0.0, 0.0},			// red plastic
{0.0215, 0.1745, 0.0215},	// emerald
{0.02, 0.02, 0.02},		// slate
{0.0, 0.0, 0.1745},		// azul
{0.02, 0.02, 0.02},		// preto
{0.1745, 0.1745, 0.1745}};// cinza

const GLfloat mat_diffuse[][4] = {{0.78, 0.57, 0.11, 1.0},		// brass
{0.5, 0.0, 0.0},				// red plastic
{0.07568, 0.61424, 0.07568},	// emerald
{0.78, 0.78, 0.78},			// slate
{0.0, 0.0,  0.61424},			// azul
{0.08, 0.08, 0.08},			// preto
{0.61424, 0.61424, 0.61424}};	// cinza

const GLfloat mat_specular[][4] = {{0.99, 0.91, 0.81, 1.0},			// brass
{0.7, 0.6, 0.6},					// red plastic
{0.633, 0.727811, 0.633},		// emerald
{0.14, 0.14, 0.14},				// slate
{0.0, 0.0, 0.727811},			// azul
{0.03, 0.03, 0.03},				// preto
{0.727811, 0.727811, 0.727811}};	// cinza

const GLfloat mat_shininess[] = {27.8,	// brass
	32.0,	// red plastic
	76.8,	// emerald
	18.78,	// slate
	30.0,	// azul
	75.0,	// preto
	60.0};	// cinza

enum tipo_material {brass, red_plastic, emerald, slate, azul, preto, cinza};

#ifdef __cplusplus
inline tipo_material operator++(tipo_material &rs, int ) {
	return rs = (tipo_material)(rs + 1);
}
#endif

typedef	GLdouble Vertice[3];
typedef	GLdouble Vector[4];

typedef struct Camera{
	GLfloat fov;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice center;
}Camera;

typedef struct Estado{
	Camera		camera;
	int			xMouse,yMouse;
	GLboolean	light;
	GLboolean	apresentaNormais;
	GLint		lightViewer;
	GLint		eixoTranslaccao;
	GLdouble	eixo[3];
	int tipo_camera;
	bool buzina_on;
	int streetNameRotation;
	int modo_anterior;
}Estado;

typedef struct Modelo {

#ifdef __cplusplus
	tipo_material cor_cubo;
#else
	enum tipo_material cor_cubo;
#endif

	GLfloat g_pos_luz1[4];
	GLfloat g_pos_luz2[4];

	GLfloat escala;
	GLUquadric *quad;
}Modelo;

Jogo* j;
Model_3DS modelocamiao;
Estado	estado;
Modelo	modelo;
skybox	aSkyBox;
menu	theMenu;
cargo	theCargo;


void passiveMotionMouse(int x, int y);
void myReshape(int w, int h);	
void NovoJogo(int mapa);
void actualiza_percurso();

/****************************************************************************************************************************
Funções auxiliares 
****************************************************************************************************************************/

void strokeCenterString(char *str,double x, double y, double z, double s)
{
	int i,n;
	
	n = strlen(str);
	glPushMatrix();
	  glTranslated(x-glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char*)str)*0.5*s,y-119.05*0.5*s,z);
	  glScaled(s,s,s);
	  for(i=0;i<n;i++)
		  glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)str[i]);
	glPopMatrix();

}



//Função de efectua a escoilha dos destinos e acrescenta a um array pela ordem 
void escolhaDestinos(int noId){

	if (noId<=0) return;
	vector<No*>* v = j->GetPercurso();
	int noa;
	if (v->size() > 0)
		noa=j->GetGrafo()->GetNoByName(v->at(v->size()-1)->Nome());
	else{
		if (j->NoSeguinte() == NULL)
			noa=j->GetGrafo()->GetNoByName(j->NoActual()->Nome());
		else
			noa=j->GetGrafo()->GetNoByName(j->NoSeguinte()->Nome());
		}
	
	if (j->GetGrafo()->ArcoEntre(noId-1,noa) != -1 || j->GetGrafo()->ArcoEntre(noa,noId-1) != -1)
		v->push_back(j->GetGrafo()->Nos()->at(noId-1));

	//Não esquecer que o id do nó é sempre +1 que a posição do array
	printf("Escolhido Nó %d\n", noId-1);

}

void alterarModoJogo(int modo){

	if (modo==MODO_MENU){
		j->ModoJogo(MODO_MENU);
		glutPassiveMotionFunc(passiveMotionMouse);
	} else if(modo==MODO_ANIMACAO) {
		estado.tipo_camera = 2;
		j->ModoJogo(MODO_ANIMACAO);
		glutPassiveMotionFunc(NULL);
	} else if (modo==MODO_CARGA){
		j->ModoJogo(MODO_CARGA);		
		strcpy(theCargo.msgUser,""); //Limpa a mensagem ao user
		glutPassiveMotionFunc(NULL);
	} else if (modo==MODO_DESTINO){
		estado.tipo_camera = 0;
		j->ModoJogo(MODO_DESTINO);
		glutPassiveMotionFunc(NULL);
	}

	//Repoe projecção chamando reshape
	myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

}

//funcao que obtem vector de nos ligados a um no. Vai servir para ajundar no desenho das paredes da rotunda

int numeroRamosDeNo(int no){
	int contagem=0;
	vector<Arco*>* arcos = j->GetGrafo()->Arcos();
	for(int i=0; i < arcos->size(); i++){
		if (arcos->at(i)->NoInicial() == no || arcos->at(i)->NoFinal() == no)
			contagem++;
	}

	return contagem;
}

int* nosLigadosANo(int no){
	int nnos=numeroRamosDeNo(no);
	int* vecnos=new int[2*nnos];
	int in=0;
	vector<Arco*>* arcos = j->GetGrafo()->Arcos();
	for(int i=0; i<arcos->size(); i++){
		//cout << "Arco: " << arcos[i].noi << " - " << arcos[i].nof << endl;
		if (arcos->at(i)->NoInicial() == no) {
			vecnos[in]=arcos->at(i)->NoFinal();
			vecnos[in+1]=0;   // 0 no de inicio
			//cout <<"Procura de nos:" << no << " tem " << vecnos[in] << " " <<arcos[i].nof << " uuu " << vecnos[in+1] << " in " << in << endl;
			in+=2;
		}
		if (arcos->at(i)->NoFinal() == no){
			vecnos[in]=(arcos->at(i)->NoInicial());
			vecnos[in+1]=1;  //1 no de fim
			//cout <<"Procura de nos:" << no << " tem " << vecnos[in] << endl;
			in+=2;
		}
	}

	return vecnos;
}


GLdouble getAnguloRotacaoPlano(GLfloat xi, GLfloat yi,GLfloat xf, GLfloat yf){
	GLdouble length=sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
	GLdouble angulo_rotacao=asin((yf-yi)/length);
	if ( (xf-xi) < 0 && (yf-yi) > 0 ) 
		angulo_rotacao=acos((yf-yi)/length);
	else if ( (xf-xi) < 0 && (yf-yi) < 0 ) 
		angulo_rotacao=M_PI/2. + asin((yi-yf)/length);
	else if ( (xf-xi) > 0 && (yf-yi) < 0 ) 
		angulo_rotacao=M_PI + asin((xf-xi)/length);
	else if ( (xf-xi) > 0 && (yf-yi) > 0 ) 
		angulo_rotacao=3.*M_PI/2. + acos((xf-xi)/length);
	else if (xf-xi == 0)
		if (yf-yi>=0) angulo_rotacao=0;
		else angulo_rotacao=M_PI;
	else if (yf-yi == 0)
		if (xf-xi >= 0) angulo_rotacao=3.*M_PI/2.;
		else angulo_rotacao=M_PI/2.;

		return angulo_rotacao;
}

void initEstado(){
	estado.tipo_camera=0;
	estado.camera.dir_lat=M_PI/4;
	estado.camera.dir_long=-M_PI/4;
	estado.camera.fov=60;
	estado.camera.dist=100;
	estado.eixo[0]=0;
	estado.eixo[1]=0;
	estado.eixo[2]=0;
	estado.camera.center[0]=0;
	estado.camera.center[1]=0;
	estado.camera.center[2]=0;
	estado.light=GL_FALSE;
	estado.apresentaNormais=GL_FALSE;
	estado.lightViewer=1;
	estado.buzina_on=false;
}

void initModelo(){
	modelo.escala=0.2;

	modelo.cor_cubo = brass;
	modelo.g_pos_luz1[0]=-5.0;
	modelo.g_pos_luz1[1]= 5.0;
	modelo.g_pos_luz1[2]= 5.0;
	modelo.g_pos_luz1[3]= 0.0;
	modelo.g_pos_luz2[0]= 5.0;
	modelo.g_pos_luz2[1]= -15.0;
	modelo.g_pos_luz2[2]= 5.0;
	modelo.g_pos_luz2[3]= 0.0;
}

void imprime_ajuda(void)
{
	printf("\n\nDesenho de um labirinto a partir de um grafo\n");
	printf("h,H - Ajuda \n");
	printf("i,I - Reset dos Valores \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("k,K - Alerna luz de camera com luz global \n");
	printf("s,S - PolygonMode Fill \n");
	printf("w,W - PolygonMode Wireframe \n");
	printf("p,P - PolygonMode Point \n");
	printf("c,C - Liga/Desliga Cull Face \n");
	printf("n,N - Liga/Desliga apresentação das normais \n");
	printf("******* grafos ******* \n");
	printf("F1  - Grava grafo do ficheiro \n");
	printf("F2  - Lê grafo para ficheiro \n");
	printf("F6  - Cria novo grafo\n");
	printf("******* Camera ******* \n");
	printf("Botão esquerdo - Arrastar os eixos (centro da camera)\n");
	printf("Botão direito  - Rodar camera\n");
	printf("Botão direito com CTRL - Zoom-in/out\n");
	printf("PAGE_UP, PAGE_DOWN - Altera distância da camara \n");
	printf("ESC - Sair\n");
}

void CrossProduct (GLdouble v1[], GLdouble v2[], GLdouble cross[])
{
	cross[0] = v1[1]*v2[2] - v1[2]*v2[1];
	cross[1] = v1[2]*v2[0] - v1[0]*v2[2];
	cross[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

GLdouble VectorNormalize (GLdouble v[])
{
	int		i;
	GLdouble	length;

	if ( fabs(v[1] - 0.000215956) < 0.0001)
		i=1;

	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt (length);
	if (length == 0)
		return 0;

	for (i=0 ; i< 3 ; i++)
		v[i] /= length;	

	return length;
}

/****************************************************************************************************************************
Projection 
****************************************************************************************************************************/
void setProjection(int x, int y, GLboolean picking){
	glLoadIdentity();
	if (picking) { // se está no modo picking, lê viewport e define zona de picking
		GLint vport[4];
		glGetIntegerv(GL_VIEWPORT, vport);
		gluPickMatrix(x, glutGet(GLUT_WINDOW_HEIGHT)  - y, 1.0, 1.0, vport); // Inverte o y do rato para corresponder à jana
	}

	gluPerspective(estado.camera.fov,(GLfloat)glutGet(GLUT_WINDOW_WIDTH) /glutGet(GLUT_WINDOW_HEIGHT) ,1,500);

}

/****************************************************************************************************************************
Texturas + iluminação
****************************************************************************************************************************/
const GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
const GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat blue_light[] = {0.0, 0.0, 1.0, 1.0};
const GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};

void putLights(GLfloat* diffuse)
{
	const GLfloat white_amb[] = {0.2, 0.2, 0.2, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT0, GL_POSITION, modelo.g_pos_luz1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT1, GL_POSITION, modelo.g_pos_luz2);

	/* desenhar luz */
	//material(red_plastic);
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz1[0], modelo.g_pos_luz1[1], modelo.g_pos_luz1[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz2[0], modelo.g_pos_luz2[1], modelo.g_pos_luz2[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void createTextures()
{
	for (int i=0; i < NUM_TEXTURAS; i++){
		char strpath [128];
		strcpy(strpath, "images/");
		strcat(strpath, Texturas_File_Array[i].c_str());
		if (i == ID_TEXTURA_PAVIMENTO_ESTRADA || i == ID_TEXTURA_PAVIMENTO_GRAVILHA || i == ID_TEXTURA_PAVIMENTO_PARALELO ){
			if (!Textures::Load_Texture(myTextures[i], strpath, Texturas_File_Array[i].substr(Texturas_File_Array[i].size()-4, 4)==".bmp", GL_REPLACE, false)){
				printf("Error loading texture %s \n",Texturas_File_Array[i]);
			}
		} else {
			if (!Textures::Load_Texture(myTextures[i], strpath, Texturas_File_Array[i].substr(Texturas_File_Array[i].size()-4, 4)==".bmp", GL_REPLACE, true)){
				printf("Error loading texture %s \n",Texturas_File_Array[i]);
			}
		}
	}

	tgaTextures.LoadTGA("images/houses1.tga");

}

/****************************************************************************************************************************
Para o menu
****************************************************************************************************************************/
void passiveMotionMouse(int x, int y){
	if (j->ModoJogo()==MODO_MENU) {
		theMenu.pickMenu(x,y, false);
	}
}

void handleMenuChoice(){

	switch (theMenu.action){
	case 1:  //Iniciar 
		theMenu.menuLevel=2;
		theMenu.selectedMenuItem=25;
		glutPostRedisplay();
		break;
	case 21: //Escolher mapa Esquerda
		theMenu.selectMenuLeft();
		break;
	case 22: //Escolher mapa Direita
		theMenu.selectMenuRight();
		break;
	case 25: //Escolher mapa
		NovoJogo(theMenu.selectedMapa);
		theMenu.action = 0; //Repôe a acção para nenhuma
		theMenu.menuLevel = 1; //Repôe o nivel de menu para 1
		alterarModoJogo(MODO_DESTINO);
		break;
	case 3: //Torneio
		theMenu.menuLevel=3;
		theMenu.selectedMenuItem=31;
		glutPostRedisplay();
		//alterarModoJogo(MODO_CARGA); //APAGAR SO PARA TESTES
		break;
	case 31: //Escolher Torneio
	case 32: 
	case 33: 
		//Escolher e fazer download do Torneio 
		//nº torneio = theMenu.action (31=1, 32=2, 33=3)
		j->Activar();
		theMenu.action = 0; //Repôe a acção para nenhuma
		theMenu.menuLevel = 1; //Repôe o nivel de menu para 1
		alterarModoJogo(MODO_ANIMACAO);
		//Repoe projecção chamando reshape
		myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case 5: //Open Site

		break;
	case 9: //Voltar
		alterarModoJogo(estado.modo_anterior);
		break;
	case 99: //Sair
		exit(0);
		break;
	}
}

/****************************************************************************************************************************
Rotinas de Desenho 
****************************************************************************************************************************/
void mostraPercursoEscolhido(){
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Altera viewport e projecção
	glViewport(width-300, 0, 300, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 250, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Blending (transparencias)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	//BackGround
	glColor4f(1,1,1,0.7);
	glBegin(GL_POLYGON);
		glVertex2d(10,10);
		glVertex2d(10,height - 10);
		glVertex2d(240,height - 10);
		glVertex2d(240,10);
	glEnd();

	//Escreve o Percurso
	glColor4f(0.0,0.0,0.0, 1);
	strokeCenterString("Percurso", 120, height - 50, 0, 0.3); // string, x ,y ,z ,scale

	int inc = height - 80;
	vector<No*>* v = j->GetPercurso();
	for (int i = 0; i < v->size(); i++){
		inc-=30;
		glColor4f(v->at(i)->R(), v->at(i)->G(), v->at(i)->B(), 1);
		char nome[100] = "";
		strcpy(nome, v->at(i)->Nome().c_str());
		strcat(nome, " - ");
		strcat(nome, v->at(i)->NomePontoEntrega().c_str());
		strokeCenterString(nome, 100, inc, 0, 0.1); // string, x ,y ,z ,scale						
	}

	// ropõe estado
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//repõe projecção chamando redisplay
	myReshape(width, height);

}

void mostraTempoJogo(){
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Altera viewport e projecção
	glViewport(10, 0, 180, 60);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-90, 90, 0, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Blending (transparencias)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	//BackGround
	glColor4f(1.0,1.0,0.7,0.8);
	glBegin(GL_POLYGON);
		glVertex2d(-90,10);
		glVertex2d(-90,50);
		glVertex2d(90,50);
		glVertex2d(90,10);
	glEnd();

	//Escreve as horas
	glColor4f(0.0,0.0,0.0, 1);
	char tmp [50];

	GLuint horas, minutos,segundos,totalTime;
	totalTime = j->Temporizador();
	horas = totalTime / 3600;
	minutos = (totalTime % 3600) / 60;
	segundos = totalTime % 60;

	sprintf(tmp, "Tempo decorrido: %dh %dm %ds", horas, minutos, segundos);
	strokeCenterString(tmp, 0, 20, 0, 0.08); // string, x ,y ,z ,scale

	sprintf(tmp, "Hora Actual: %dh %dm %ds", j->Hora() + horas, j->Minuto() + minutos, segundos);
	strokeCenterString(tmp, 0, 40, 0, 0.08); // string, x ,y ,z ,scale

	// ropõe estado
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//repõe projecção chamando redisplay
	myReshape(width, height);

}

void desenhaNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat){
	switch (mat){
	case red_plastic:
		glColor3f(1,0,0);
		break;
	case azul:
		glColor3f(0,0,1);
		break;
	case emerald:
		glColor3f(0,1,0);
		break;
	default:
		glColor3f(1,1,0);
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(0.4,0.4,0.4);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3dv(normal);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void desenhaSolo(){
#define STEP 10
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR);
    glBindTexture(GL_TEXTURE_2D, ID_TEXTURA_AREIA);
	for(int i=-200;i<200;i+=STEP)
		for(int j=-200;j<200;j+=STEP){
            glBegin(GL_POLYGON);
                glNormal3f(0,0,1);
                glTexCoord2f(1,1);
                glVertex2f(i+STEP,j+STEP);
                glTexCoord2f(0,1);
                glVertex2f(i,j+STEP);
                glTexCoord2f(0,0);
                glVertex2f(i,j);
                glTexCoord2f(1,0);
                glVertex2f(i+STEP,j);
            glEnd();
		}
    glBindTexture(GL_TEXTURE_2D, NULL);
	glEnable(GL_COLOR);
	glDisable(GL_TEXTURE_2D);
}

void desenhaEstradinha(GLdouble width, GLdouble length){
	if (width < 1.2){
		glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_PAVIMENTO_PARALELO]);
	}else{
		glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_PAVIMENTO_ESTRADA]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-width/2,0,0);
	glTexCoord2f(1,0);
	glVertex3f(+width/2,0,0);
	glTexCoord2f(1,length);
	glVertex3f(+width/2,length,0);
	glTexCoord2f(0,length);
	glVertex3f(-width/2,length,0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaParedes(GLdouble width, GLdouble length, GLdouble altura){
	//glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_CASAS]);
	tgaTextures.Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(-width/2,0,altura);
	glTexCoord2f(0,0);
	glVertex3f(-width/2,0,0);
	glTexCoord2f(round(length),0);
	glVertex3f(-width/2,length,0);
	glTexCoord2f(round(length),1);
	glVertex3f(-width/2,length,altura);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(width/2,0,altura);
	glTexCoord2f(0,0);
	glVertex3f(width/2,0,0);
	glTexCoord2f(round(length),0);
	glVertex3f(width/2,length,0);
	glTexCoord2f(round(length),1);
	glVertex3f(width/2,length,altura);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

}

void desenhaEstradaComRampa(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat Raioi, GLfloat xf, GLfloat yf, GLfloat zf,GLfloat Raiof, GLdouble width){
	//GLdouble length=sqrt(pow(xf-xi, 2) + pow(yf-yi, 2)+ pow(zf-zi, 2));
	GLdouble lengthxy=sqrt(pow(xf-xi, 2) + pow(yf-yi, 2))-Raioi-Raiof;
	//GLdouble angulo_subida=asin((zf-zi)/(length - (Raioi+Raiof) ) );
	GLdouble angulo_subida=atan((zf-zi)/(lengthxy) );
	//GLdouble angulo_rotacao=getAnguloRotacaoPlano(xi, yi,xf, yf,(length-(Raioi+Raiof))*cos(angulo_subida)+ (Raioi+Raiof));
	GLdouble angulo_rotacao=getAnguloRotacaoPlano(xi, yi,xf, yf);
	//cout << length << " : "<< angulo_rotacao/M_PI << " " << graus(angulo_rotacao) << " "<< xi << ","<<yi<<" : "<<xf<<","<<yf  <<endl;
	glPushMatrix();
	glTranslatef(xi,yi,zi);
	glRotated(graus(angulo_rotacao), 0,0,1);
	desenhaEstradinha(width,Raioi);
	glTranslatef(0,Raioi,0);
	glRotated(graus(angulo_subida), 1,0,0);
	desenhaEstradinha(width, sqrt(lengthxy*lengthxy+(zf-zi)*(zf-zi)));

	glPushMatrix();			
	float shear[] = { 
		1, 0, 0, 0, 
		0, 1, 0, 0,
		0, tan(angulo_subida), 1, 0,
		0, 0, 0, 1 };
		glMultMatrixf(shear);
		desenhaParedes(width,sqrt(lengthxy*lengthxy+(zf-zi)*(zf-zi)) , ALTURA_PAREDE*cos(angulo_subida));
		glPopMatrix();
		glTranslatef(0,sqrt(lengthxy*lengthxy+(zf-zi)*(zf-zi)),0);
		glRotated(-graus(angulo_subida), 1,0,0);
		desenhaEstradinha(width,Raiof);
		glPopMatrix();
}

void desenhaCamiao(){
	Veiculo* v = j->GetVeiculos()->at(0);
	GLfloat comp=2;
	GLfloat larg=1;
	GLfloat alt=1;
	glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_PAVIMENTO_PARALELO]);
	glPushMatrix();
	glTranslatef(v->X(), v->Y(), v->Z() + 0.1);
	glRotated(v->Yaw(), 0,0,1);
	glRotated(v->Pitch(), 1,0,0);
	glTranslatef(0.15, 0, 0);	//Podemos por o camiao a andar na direita da estrada aqui. (Passar como parametro a largura da estrada)
	glRotated(90, 1,0,0);
	glRotated(90, 0,1,0);
	//glutSolidTeapot(0.25);
	//glScaled(0.03,0.03,0.03);
	glScaled(0.00003,0.00003,0.00003);
	modelocamiao.Draw();

	glPopMatrix();
}

/****************************************************************************************************************************
Rotinas de Desenho do grafo
****************************************************************************************************************************/
void desenhaParedeRotunda(GLfloat raio, GLfloat alphai, int tiponoi, GLfloat alphaf, int tiponof, int num_segments){
	alphai+=M_PI/2; //ajustar o angulo a conta do eixo dos y para o a contar a partir do eixo dos x
	alphaf+=M_PI/2;
	GLfloat dalpha=alphaf-alphai; //alphai tem de ser menor que o alphaf; atencao a parede que passa de 359 para 1 grau...
	int lengthParede=round(darco(dalpha,raio));
	double dlength=(double) lengthParede/num_segments;
	double alt_parede=ALTURA_PAREDE;
	//cout << tiponoi << " " << tiponof << " " << num_segments << " " << darco(dalpha,raio) <<" " <<  lengthParede <<  endl;
	glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_CASAS]);
	double passo_alpha=dalpha/num_segments;
	for (int i=0; i<num_segments;i++){
		double alphaDesenho=alphai+passo_alpha*i;
		double lengthDesenho=(double) lengthParede-i*dlength;
		double lengthDesenhon=(double) lengthDesenho-dlength;
		double x=raio*cos(alphaDesenho);
		double y=raio*sin(alphaDesenho);
		double xn=raio*cos(alphaDesenho+passo_alpha);
		double yn=raio*sin(alphaDesenho+passo_alpha);
		//cout<<x<<" " << y <<" "<< alphaDesenho <<endl;
		glBegin(GL_QUADS);
		glTexCoord2f(lengthDesenho,0);
		glVertex3f(x,y,0);
		glTexCoord2f(lengthDesenho,1);
		glVertex3f(x,y,alt_parede);
		glTexCoord2f(lengthDesenhon,1);
		glVertex3f(xn,yn,alt_parede);
		glTexCoord2f(lengthDesenhon,0);
		glVertex3f(xn,yn,0);
		glEnd();
	}
}

void desenhaParedeRotunda2(GLfloat raio, GLfloat alpha1, GLfloat largura_arco1, GLfloat alpha2, double largura_arco2, int num_segments){
	float dalpha_arco1=asin((largura_arco1/2)/raio);
	float dalpha_arco2=asin((largura_arco2/2)/raio);
	GLfloat alphai=alpha1+M_PI/2+dalpha_arco1;//ajustar o angulo a conta do eixo dos y para o a contar a partir do eixo dos x
	GLfloat alphaf=alpha2+M_PI/2-dalpha_arco2;
	GLfloat dalpha=alphaf-alphai; //alphai tem de ser menor que o alphaf; atencao a parede que passa de 359 para 1 grau...
	GLfloat lengthParedeRampa1=raio*(1-sqrt(cos(dalpha_arco1)*cos(dalpha_arco1)));
	GLfloat lengthParedeRampa2=raio*(1-sqrt(cos(dalpha_arco2)*cos(dalpha_arco2)));
	int lengthParede=round(darco(dalpha,raio)+lengthParedeRampa1+lengthParedeRampa2);
	double dlength=(double) (lengthParede-(lengthParedeRampa1+lengthParedeRampa2))/num_segments;
	double alt_parede=ALTURA_PAREDE;
	
	//glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_CASAS]);
	tgaTextures.Use();
	//tapa buraco 1
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	GLfloat raio2=sqrt(raio*raio+largura_arco1*largura_arco1/4);
	GLfloat dalpha2=atan((largura_arco1/2)/raio);
	glBegin(GL_QUADS);
	glTexCoord2f(lengthParede,0);
	glVertex3f(raio2*cos(alpha1+M_PI/2+dalpha2),raio2*sin(alpha1+M_PI/2+dalpha2),0);
	glTexCoord2f(lengthParede,1);
	glVertex3f(raio2*cos(alpha1+M_PI/2+dalpha2),raio2*sin(alpha1+M_PI/2+dalpha2),alt_parede);
	glTexCoord2f(lengthParede-lengthParedeRampa1,1);
	glVertex3f(raio*cos(alphai),raio*sin(alphai),alt_parede);
	glTexCoord2f(lengthParede-lengthParedeRampa1,0);
	glVertex3f(raio*cos(alphai),raio*sin(alphai),0);
	glEnd();

	double passo_alpha=dalpha/num_segments;
	for (int i=0; i<num_segments;i++){
		double alphaDesenho=alphai+passo_alpha*i;
		double lengthDesenho=(double) lengthParede-lengthParedeRampa1-i*dlength;
		double lengthDesenhon=(double) lengthDesenho-dlength;
		double x=raio*cos(alphaDesenho);
		double y=raio*sin(alphaDesenho);
		double xn=raio*cos(alphaDesenho+passo_alpha);
		double yn=raio*sin(alphaDesenho+passo_alpha);
		//cout<<x<<" " << y <<" "<< alphaDesenho <<endl;
		glBegin(GL_QUADS);
		glTexCoord2f(lengthDesenho,0);
		glVertex3f(x,y,0);
		glTexCoord2f(lengthDesenho,1);
		glVertex3f(x,y,alt_parede);
		glTexCoord2f(lengthDesenhon,1);
		glVertex3f(xn,yn,alt_parede);
		glTexCoord2f(lengthDesenhon,0);
		glVertex3f(xn,yn,0);
		glEnd();
	}
	//tapa buraco 2
	raio2=sqrt(raio*raio+largura_arco2*largura_arco2/4);
	dalpha2=atan((largura_arco2/2)/raio);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(raio2*cos(alpha2+M_PI/2-dalpha2),raio2*sin(alpha2+M_PI/2-dalpha2),0);
	glTexCoord2f(0,1);
	glVertex3f(raio2*cos(alpha2+M_PI/2-dalpha2),raio2*sin(alpha2+M_PI/2-dalpha2),alt_parede);
	glTexCoord2f(lengthParedeRampa2,1);
	glVertex3f(raio*cos(alphaf),raio*sin(alphaf),alt_parede);
	glTexCoord2f(lengthParedeRampa2,0);
	glVertex3f(raio*cos(alphaf),raio*sin(alphaf),0);
	glEnd();

	glDisable(GL_BLEND);

}

void ordenarBeanAngulos(double* angvec, Bean* beans, int n){
	for (int i=0;i<n-1;i++){
		for (int j=i+1;j<n;j++){
			if 	(angvec[i]>angvec[j]){
				double aux=angvec[j];
				angvec[j]=angvec[i];
				angvec[i]=aux;
				Bean auxi=beans[j];
				beans[j]=beans[i];
				beans[i]=auxi;
			}
		}
	}
}

Bean* nosLigadosANoLargura(int no){
	int nnos=numeroRamosDeNo(no);
	Bean* vecnos=new Bean[nnos];
	int in=0;
	vector<Arco*>* arcos = j->GetGrafo()->Arcos();
	for(int i=0; i<arcos->size(); i++){
		//cout << "Arco: " << arcos[i].noi << " - " << arcos[i].nof << endl;
		if (arcos->at(i)->NoInicial() == no) {
			vecnos[in].no=(arcos->at(i)->NoFinal());
			vecnos[in].tipo=0;   // 0 no de inicio
			vecnos[in].arco=i;
			//cout <<"Procura de nos:" << no << " tem " << vecnos[in] << " " <<arcos[i].nof << " uuu " << vecnos[in+1] << " in " << in << endl;
			in++;
		}
		if (arcos->at(i)->NoFinal() == no){
			vecnos[in].no=(arcos->at(i)->NoInicial());
			vecnos[in].tipo=1;  //1 no de fim
			vecnos[in].arco=i;
			//cout <<"Procura de nos:" << no << " tem " << vecnos[in] << endl;
			in++;
		}
	}

	return vecnos;
}


void desenhaParedesRotunda(int nno){
	No *no=j->GetGrafo()->Nos()->at(nno);
	int num_paredes=numeroRamosDeNo(nno);
	if (num_paredes == 0) 
		desenhaParedeRotunda(no->Raio(),0,0,2*M_PI,0,32);
	else {
		double* alphasvec=new double[num_paredes];
		Bean* nosvec=nosLigadosANoLargura(nno);
		if (num_paredes == 1){
			No* nof=j->GetGrafo()->Nos()->at(nosvec[0].no);
			Arco* arcof=j->GetGrafo()->Arcos()->at(nosvec[0].arco);
			double angulo=getAnguloRotacaoPlano(no->X(),no->Y(),nof->X(),nof->Y());
			double largura_arco=arcof->Largura();
			float delta_angulo=asin((largura_arco/2)/no->Raio());
			desenhaParedeRotunda2(no->Raio(), angulo, largura_arco, angulo+2*M_PI, largura_arco, 32);
		} else {
			double* angvec=new double[num_paredes];

			for (int i=0; i<num_paredes;i++){
				No *nof=j->GetGrafo()->Nos()->at(nosvec[i].no);
				angvec[i]=getAnguloRotacaoPlano(no->X(),no->Y(),nof->X(),nof->Y());
			}
			ordenarBeanAngulos(angvec, nosvec, num_paredes);			
			for (int i=0; i<num_paredes-1;i++){
				Arco* arco1=j->GetGrafo()->Arcos()->at(nosvec[i].arco);
				Arco* arco2=j->GetGrafo()->Arcos()->at(nosvec[(i+1)].arco);
				double largura_arco1=arco1->Largura();
				double largura_arco2=arco2->Largura();
				desenhaParedeRotunda2(no->Raio(), angvec[i], largura_arco1, angvec[i+1], largura_arco2, 32);
			}
			Arco* arco2=j->GetGrafo()->Arcos()->at(nosvec[0].arco);
			Arco* arco1=j->GetGrafo()->Arcos()->at(nosvec[num_paredes-1].arco);
			double largura_arco1=arco1->Largura();
			double largura_arco2=arco2->Largura();
			desenhaParedeRotunda2(no->Raio(), angvec[num_paredes-1], largura_arco1, angvec[0]+2*M_PI, largura_arco2, 32);
		}
	}	
}

void drawRotunda(GLfloat r, int num_segments, bool bindTexture) 
{ 
	if (bindTexture){
		glBindTexture(GL_TEXTURE_2D, myTextures[ID_TEXTURA_ROTUNDA]);
	}

	glBegin(GL_POLYGON);
	//glVertex3f(0., 0., 0.);
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cos(theta);//calculate the x component 
		float y = r * sin(theta);//calculate the y component 
		if (bindTexture){
			float s =  cos(theta)/2+0.5;
			float t =  sin(theta)/2+0.5;
			glTexCoord2f(s,t);
		}
		//Desenha a cor ligeiramente acima para nao aparecer os riscos de sobreposição
		if (bindTexture){
			glVertex3f(x, y ,0);//rotunda com textura 
		}else{
			glVertex3f(x, y ,0.01);//cor da rotunda
		}
	} 
	glEnd();
}

void drawNomeEntrega(string nome, float x, float y, float z){
	char tmp[20] = "";
	strcpy(tmp, nome.c_str());
	glPushMatrix();
		glTranslatef(0.0,0.0,2.0);
		glScalef(0.01, 0.01, 0.01);
		glRotatef(90,1,0,0);
		glRotatef(estado.streetNameRotation,0,1,0);
		strokeCenterString(tmp, x, y, z, 0.5);
	glPopMatrix();
}

void desenhaNo2(int no){
	No *noi=j->GetGrafo()->Nos()->at(no);
	glPushMatrix();
		glTranslatef(noi->X(),noi->Y(),noi->Z()+0.001);
		desenhaParedesRotunda(no);
		//Desenha rotunda com textura
		GLfloat circleSize = noi->Raio();
		drawRotunda(circleSize ,32, true);

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glPushName(no+1);
			//Desenha rotunda com cor
			glColor3f(noi->R(), noi->G(), noi->B());
			circleSize = (noi->Raio() / 3) * 2;
			drawRotunda(circleSize, 32, false);
			drawNomeEntrega(noi->NomePontoEntrega(),noi->X(),noi->Y(),noi->Z());
		glPopName();

		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);

	glPopMatrix();
}

void desenhaArco2(Arco* arco){
	No *noi,*nof;
	noi=j->GetGrafo()->Nos()->at(arco->NoInicial());
	nof=j->GetGrafo()->Nos()->at(arco->NoFinal());
	desenhaEstradaComRampa(noi->X(),noi->Y(),noi->Z(),noi->Raio(), nof->X(),nof->Y(),nof->Z(),nof->Raio(),arco->Largura());

}

void desenhaLabirinto(){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);			//Enable texture mapping

	glTranslatef(0,0,0.05);
	glScalef(5,5,5);

	glColor3f(1.0f,1.0f,1.0f);
	vector<Arco*>* arcos = j->GetGrafo()->Arcos();
	for(int i=0; i<arcos->size(); i++){
		desenhaArco2(arcos->at(i));
	}
	vector<No*>* nos = j->GetGrafo()->Nos();
	for(int i=0; i<nos->size(); i++)
		desenhaNo2(i);

	desenhaCamiao();

	glDisable(GL_TEXTURE_2D);			//Set all back to normal
	glPopMatrix();
}

/****************************************************************************************************************************
Câmaras e Eixos
****************************************************************************************************************************/
double angulo_entre_dois_vectores(double v1x,double v1y, double v1z, double v2x,double v2y, double v2z){
	double angulo_rad=0;
	double prod_int=(v1x*v2x + v1y*v2y + v1y*v2y);
	double v1_norm=sqrt(v1x*v1x+v1y*v1y+v1z*v1z);
	double v2_norm=sqrt(v2x*v2x+v2y*v2y+v2z*v2z);
	angulo_rad=acos((prod_int)/(v1_norm*v2_norm));
	return angulo_rad;
}

void setCamera(){
	//tipo 0 para a origem
	//tipo 1 para o carro
	Veiculo* v = j->GetVeiculos()->at(0);
	if (estado.tipo_camera==0){
		estado.camera.center[0]=0;
		estado.camera.center[1]=0;
		estado.camera.center[2]=0;
	}
	if (estado.tipo_camera==1){
		estado.camera.center[0]=5*v->X();
		estado.camera.center[1]=5*v->Y();
		estado.camera.center[2]=5*v->Z();
	}

	Vertice eye;
	eye[0]=estado.camera.center[0]+estado.camera.dist*cos(estado.camera.dir_long)*cos(estado.camera.dir_lat);
	eye[1]=estado.camera.center[1]+estado.camera.dist*sin(estado.camera.dir_long)*cos(estado.camera.dir_lat);
	eye[2]=estado.camera.center[2]+estado.camera.dist*sin(estado.camera.dir_lat);

	//Set SkyBox rotation
	aSkyBox.rot_y = -graus(estado.camera.dir_long);
	aSkyBox.rot_x = graus(estado.camera.dir_lat);

	if (estado.tipo_camera==2){
		estado.camera.center[0]=5*v->X();
		estado.camera.center[1]=5*v->Y();
		estado.camera.center[2]=5*v->Z();
		double dirxy=v->Yaw()+90.;
		double ang_sub=v->Pitch();
		eye[0]=estado.camera.center[0]-0.05*estado.camera.dist*cos(rad(dirxy))*cos(rad(ang_sub));
		eye[1]=estado.camera.center[1]-0.05*estado.camera.dist*sin(rad(dirxy))*cos(rad(ang_sub));
		eye[2]=estado.camera.center[2]-0.05*estado.camera.dist*sin(rad(ang_sub))+3;


		double v_camx=estado.camera.center[0]-eye[0];
		double v_camy=estado.camera.center[1]-eye[1];
		double v_camz=estado.camera.center[2]-eye[2];
		double v_cam_comp=sqrt(v_camx*v_camx+v_camy*v_camy+v_camz*v_camz);
		double latitude=-asin(v_camz/v_cam_comp);
		double longitude=angulo_entre_dois_vectores(-1,0,0,v_camx,v_camy,0);
		if (v_camy>0)  longitude=-longitude;
		//Set SkyBox rotation
		aSkyBox.rot_y = -graus(longitude);
		aSkyBox.rot_x = graus(latitude);

	}

	if (estado.tipo_camera==3){
		double dirxy=v->Yaw()+90.;
		double ang_sub=v->Pitch();
		estado.camera.center[0]=5*v->X()+0.05*estado.camera.dist*cos(rad(dirxy))*cos(rad(ang_sub));
		estado.camera.center[1]=5*v->Y()+0.05*estado.camera.dist*sin(rad(dirxy))*cos(rad(ang_sub));
		estado.camera.center[2]=5*v->Z()+0.05*estado.camera.dist*sin(rad(ang_sub))+0.8;
		eye[0]=5*v->X()+0.01*estado.camera.dist*cos(rad(dirxy))*cos(rad(ang_sub));;
		eye[1]=5*v->Y()+0.01*estado.camera.dist*sin(rad(dirxy))*cos(rad(ang_sub));;
		eye[2]=5*v->Z()+0.01*estado.camera.dist*sin(rad(ang_sub))+0.8;

		double v_camx=estado.camera.center[0]-eye[0];
		double v_camy=estado.camera.center[1]-eye[1];
		double v_camz=estado.camera.center[2]-eye[2];

		double v_cam_comp=sqrt(v_camx*v_camx+v_camy*v_camy+v_camz*v_camz);
		double latitude=-asin(v_camz/v_cam_comp);
		double longitude=angulo_entre_dois_vectores(-1,0,0,v_camx,v_camy,0);
		if (v_camy>0)  longitude=-longitude;
		//Set SkyBox rotation
		aSkyBox.rot_y = -graus(longitude);
		aSkyBox.rot_x = graus(latitude);
	}


	if(estado.light){
		gluLookAt(eye[0],eye[1],eye[2],estado.camera.center[0],estado.camera.center[1],estado.camera.center[2],0,0,1);
		putLights((GLfloat*)white_light);
	}else{
		putLights((GLfloat*)white_light);
		gluLookAt(eye[0],eye[1],eye[2],estado.camera.center[0],estado.camera.center[1],estado.camera.center[2],0,0,1);
	}


}

/****************************************************************************************************************************
Main & CallBacks
****************************************************************************************************************************/

void myInit()
{
	j = new Jogo();

	createTextures();

	//modelocamiao.Load("models/Freightliner Aerodyne.3ds");
	//modelocamiao.Load("models/FireTruck.3DS");
	modelocamiao.Load("models/BLITZ_L.3DS");
	modelocamiao.lit = true;
	modelocamiao.rot.y = 90;

	GLfloat LuzAmbiente[]={0.5,0.5,0.5, 0.0};

	glClearColor (0.0, 0.0, 0.0, 0.0);

	glEnable(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	glEnable(GL_NORMALIZE);

	glDepthFunc(GL_LESS);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente); 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 

	initModelo();
	initEstado();

	aSkyBox.Init();
	theMenu.Init();

	modelo.quad=gluNewQuadric();
	gluQuadricDrawStyle(modelo.quad, GLU_FILL);
	gluQuadricNormals(modelo.quad, GLU_OUTSIDE);

}

void myReshape(int w, int h){	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	setProjection(0,0,GL_FALSE);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void NovoJogo(int mapa)
{
	j->Activar();
	string nome_mapa = theMenu.mapasNames[mapa];
	j->Load(nome_mapa);
	theCargo.Init(j->GetEncomendas(), j->GetEncomendasEntregues());

	if(j->Hora() < 8 || j->Hora() > 20)
	{
		if(j->GetCondicoes()->at(0)->IsChuva())
		{
			aSkyBox.sky = SKY_NIGHT_CLOUD;
		}
		else
		{
			aSkyBox.sky = SKY_NIGHT_CLEAR;
		}
	}
	else
	{
		if(j->GetCondicoes()->at(0)->IsChuva())
		{
			aSkyBox.sky = SKY_DAY_CLOUD;
		}
		else
		{
			aSkyBox.sky = SKY_DAY_CLEAR;
		}
	}

	// TODO: mandar as encomendas para o cargo

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (j->ModoJogo()==MODO_MENU){

		theMenu.onGame = j->IsActivo();
		theMenu.draw();	

	}else if (j->ModoJogo()==MODO_ANIMACAO || j->ModoJogo()==MODO_DESTINO){

		aSkyBox.draw();

		setCamera();

		desenhaSolo();	

		desenhaLabirinto();

		mostraTempoJogo();

		if (j->ModoJogo()==MODO_DESTINO){
			mostraPercursoEscolhido();
		}

	}else if (j->ModoJogo()==MODO_CARGA){

		theCargo.hourStarted = j->Hora();
		theCargo.minuteStarted = j->Minuto();
		theCargo.timeElapsed = j->Temporizador();

		if (j->NoSeguinte()==NULL)
			theCargo.draw("-1");
		else	
			theCargo.draw(j->NoSeguinte()->Nome());

	}

	glFlush();
	glutSwapBuffers();

}

void al_music_jogo(int i){
	glutTimerFunc(180000,al_music_jogo,0);
	ALuint helloBuffer, helloSource;
	//helloBuffer = alutCreateBufferHelloWorld ();
	helloBuffer = alutCreateBufferFromFile("Music\\Game_music.wav");
	alGenSources (1, &helloSource);
	alSourcei (helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay (helloSource);
}

void al_som_estrada(int i){
	ALuint helloBuffer, helloSource;
	//helloBuffer = alutCreateBufferHelloWorld ();
	helloBuffer = alutCreateBufferFromFile("Music\\city_street_traffic.wav");
	alGenSources (1, &helloSource);
	alSourcei (helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay (helloSource);
}

void al_buzina(){
	estado.buzina_on=true;
	ALuint helloBuffer, helloSource;
	//helloBuffer = alutCreateBufferHelloWorld ();
	helloBuffer = alutCreateBufferFromFile("Music\\buzina.wav");
	alGenSources (1, &helloSource);
	alSourcei (helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay (helloSource);

}

void Activa_buzina(int i){
	estado.buzina_on=false;
}

void keyboard(unsigned char key, int x, int y)
{
	Veiculo* v;

	switch (key)
	{
	case 13 : // Enter Key
		if (j->ModoJogo()==MODO_MENU){
			theMenu.action=theMenu.selectedMenuItem;
			handleMenuChoice();
		}
		break;
	case 27 : //Esc Key
		if (j->ModoJogo()==MODO_MENU){
			if (j->IsActivo()){
				theMenu.action = 9;
				handleMenuChoice();
			}
		}else{
			estado.modo_anterior=j->ModoJogo();
			alterarModoJogo(MODO_MENU);
				theMenu.action = 0;
		}
		break;
	case '1':
		estado.tipo_camera=0;
		glutPostRedisplay();
		break;
	case '2':
		estado.tipo_camera=1;
		glutPostRedisplay();
		break;
	case '3':
		estado.tipo_camera=2;
		glutPostRedisplay();
		break;
	case '4':
		estado.tipo_camera=3;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		if(j->ModoJogo()==MODO_DESTINO){
			j->setPercursoByGPS();
		}
		break;
	case 'g':
	case 'G':
		if (j->ModoJogo() == MODO_DESTINO) {
			if (theCargo.checkAllLoaded()){
					alterarModoJogo(MODO_ANIMACAO);
					actualiza_percurso();
			} else {
					strcpy(theCargo.msgUser,"TEM DE CARREGAR TODAS AS ENCOMENDAS");
					alterarModoJogo(MODO_CARGA);
			}
		}
		if (j->ModoJogo() ==MODO_CARGA) {
			if (j->NoSeguinte()==NULL) {
				if (theCargo.checkAllLoaded()){
					alterarModoJogo(MODO_ANIMACAO);
					actualiza_percurso();
				} else strcpy(theCargo.msgUser,"TEM DE CARREGAR TODAS AS ENCOMENDAS");
			} else{
				if (!theCargo.checkTodasEncomendasEntreguesEmNo(j->NoSeguinte()->Nome())) {
					strcpy(theCargo.msgUser,"DESCARREGUE AQUI AS ENCOMENDAS DESTE NO");
				}	else if (!theCargo.checkAllLoaded()) {
						strcpy(theCargo.msgUser,"CARREGUE TODAS AS ENCOMENDAS QUE NAO PERTENCEM A ESTE NO");
						} else {
							alterarModoJogo(MODO_ANIMACAO);
							actualiza_percurso();
						}
			}
			glutPostRedisplay();
		}
		break;
	case 't':
	case 'T':/*{
				if (j->ModoJogo() == MODO_DESTINO) {
					alterarModoJogo(MODO_CARGA);
				}
			 }*/
		break;
	case 'f':
	case 'F':
		break;
	case 'h':
	case 'H':
		imprime_ajuda();
		break;
	case 'b':
	case 'B':
		if (!estado.buzina_on) {
			al_buzina();
			glutTimerFunc(3200,Activa_buzina,0);
		}
		break;

	case 'l':
	case 'L':
		if(estado.lightViewer)
			estado.lightViewer=0;
		else
			estado.lightViewer=1;
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer);
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		estado.light=!estado.light;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		if(glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		glutPostRedisplay();
		break;    
	case 'n':
	case 'N':
		estado.apresentaNormais=!estado.apresentaNormais;
		glutPostRedisplay();
		break;    		
	case 'i':
	case 'I':
		initEstado();
		initModelo();
		glutPostRedisplay();
		break;    
	//case 'y':
	//case 'Y':
	//	//v->Accelerate(0.05);
	//case 't':
	//case 'T':
		//v->Brake(0.05);
	}
}

void Special(int key, int x, int y){

	switch(key){
	case GLUT_KEY_F1 :
		break;
	case GLUT_KEY_F2 :
		break;	
	case GLUT_KEY_F6 :
		break;	
	case GLUT_KEY_UP:
		if (j->ModoJogo()==MODO_MENU){
			theMenu.selectMenuUp();
		}else{
			estado.camera.dist-=1;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if (j->ModoJogo()==MODO_MENU){
			theMenu.selectMenuDown();
		}else{
			estado.camera.dist+=1;
		}
		glutPostRedisplay();
		break;	
	case GLUT_KEY_LEFT:
		if (j->ModoJogo()==MODO_MENU){
			theMenu.selectMenuLeft();
			glutPostRedisplay();
		}
		break;	
	case GLUT_KEY_RIGHT:
		if (j->ModoJogo()==MODO_MENU){
			theMenu.selectMenuRight();
			glutPostRedisplay();
		}
		break;	
	}
}

void motionRotate(int x, int y){
#define DRAG_SCALE	0.01
	double lim=M_PI/2-0.1;

	estado.camera.dir_long+=(estado.xMouse-x)*DRAG_SCALE;
	estado.camera.dir_lat-=(estado.yMouse-y)*DRAG_SCALE*0.5;
	if(estado.camera.dir_lat>lim)
		estado.camera.dir_lat=lim;
	else {
		if(estado.camera.dir_lat<-lim)
			estado.camera.dir_lat=-lim;
	}
	estado.xMouse=x;
	estado.yMouse=y;
	glutPostRedisplay();
}

void motionZoom(int x, int y){
#define ZOOM_SCALE	0.5
	estado.camera.dist-=(estado.yMouse-y)*ZOOM_SCALE;
	if(estado.camera.dist<5)
		estado.camera.dist=5;
	else 
		if(estado.camera.dist>200)
			estado.camera.dist=200;
	estado.yMouse=y;
	glutPostRedisplay();
}

void motionDrag(int x, int y){
	//Handle Mouse Drag on cargo
	if (j->ModoJogo()==MODO_CARGA){		
		theCargo.picking(x,y);
	}	
	glutPostRedisplay();
}

int picking(int x, int y){
	int i, n, objid=0;
	double zmin = 10.0;
	GLuint buffer[100], *ptr;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projecção
	glLoadIdentity();
	setProjection(x,y,GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera();
	glPushMatrix();
		glTranslatef(0,0,0.05);
		glScalef(5,5,5);
		vector<No*>* nos = j->GetGrafo()->Nos();
		for(int i=0; i<nos->size(); i++)
			desenhaNo2(i);
	glPopMatrix();

	n = glRenderMode(GL_RENDER);

	if (n > 0)
	{
		ptr = buffer;
		for (i = 0; i < n; i++)
		{
			if (zmin > (double) ptr[1] / UINT_MAX) {
				zmin = (double) ptr[1] / UINT_MAX;
				objid = ptr[3];
			}
			ptr += 3 + ptr[0]; // ptr[0] contem o número de nomes (normalmente 1); 3 corresponde a numnomes, zmin e zmax
		}
	}

	glMatrixMode(GL_PROJECTION); //repõe matriz projecção
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	return objid;
}

void mouse(int btn, int state, int x, int y){
	switch(btn) {
	case GLUT_RIGHT_BUTTON :
		if (j->ModoJogo()==MODO_CARGA) {
			if(state == GLUT_DOWN){
				theCargo.rodaTetromino();
			}
		} else if (j->ModoJogo()==MODO_ANIMACAO || j->ModoJogo()==MODO_DESTINO) {
			if(state == GLUT_DOWN){
				estado.xMouse=x;
				estado.yMouse=y;
				if(glutGetModifiers() & GLUT_ACTIVE_CTRL)
					glutMotionFunc(motionZoom);
				else
					glutMotionFunc(motionRotate);
				cout << "Left down\n";
			}
			else{
				glutMotionFunc(NULL);
				cout << "Left up\n";
			}
		}
		break;
	case GLUT_LEFT_BUTTON :
		if (j->ModoJogo()==MODO_MENU) {

			theMenu.pickMenu(x,y, true);
			handleMenuChoice();

		}else if (j->ModoJogo()==MODO_CARGA) {

			if(state == GLUT_DOWN){
				theCargo.picking(x,y);
				if(theCargo.startDrag){
					glutMotionFunc(motionDrag);
				} else {
					glutMotionFunc(NULL);
				}
			} else {
				theCargo.startDrag=false;
			}

		}else if (j->ModoJogo()==MODO_DESTINO) {
			if(state == GLUT_DOWN){
				escolhaDestinos(picking(x,y));
			}
		}
		break;
	}
}

bool createGLUTWindow(char* title, bool fullscreenflag) {

	bool sucess=true;

	if (fullscreenflag){
		glutGameModeString("1920x1080:32@60"); // 1º teste
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) glutEnterGameMode(); 
		else  
		{ 
			glutGameModeString("1280x800:32@60"); // 2º teste
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) glutEnterGameMode(); 
			else  
			{ 
				glutGameModeString("1024x768:32@60");  // 3º teste
				if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) glutEnterGameMode(); 
				else  
				{ 
					glutGameModeString("800x600:32@60");  // 4º teste

					if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) glutEnterGameMode(); 
					else 
					{ 
						sucess=false;
					}
				}	
			} 
		} 
	}

	if (!fullscreenflag || !sucess) {
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(800, 600); 
		return glutCreateWindow(title) == GL_TRUE;
	}

	return sucess;
}

double distancia(double x1,double y1, double z1, double x2,double y2, double z2){
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
}

bool camiao_em_no_final(){
	No* nof=j->NoSeguinte();
	Veiculo* v = j->GetVeiculos()->at(0);
	double dist=distancia(nof->X(),nof->Y(),nof->Z(),v->X(),v->Y(),v->Z());
	return (dist < 0.05);
}

void calcula_posicao_animacao_camiao(){
	No* noi=j->NoActual();
	No* nof=j->NoSeguinte();
	Veiculo* v = j->GetVeiculos()->at(0);
	v->Accelerate(0.05);
	double passo_dist=v->Velocidade();
	double dirsub=0;
	double dirxy=getAnguloRotacaoPlano(noi->X(),noi->Y(),nof->X(),nof->Y())+M_PI/2;
	double lengthxy=sqrt(pow(nof->X()-noi->X(), 2) + pow(nof->Y()-noi->Y(), 2))-noi->Raio()-nof->Raio();

	v->Yaw(graus(dirxy-M_PI/2));

	if (distancia(v->X(),v->Y(),v->Z(),noi->X(),noi->Y(),noi->Z()) < noi->Raio() || distancia(v->X(),v->Y(),v->Z(),nof->X(),nof->Y(),nof->Z()) < nof->Raio()) {		
		v->Pitch(0);
		v->X(v->X()+passo_dist*cos(dirxy));
		v->Y(v->Y()+passo_dist*sin(dirxy));
	}
	else {
		dirsub=atan((nof->Z()-noi->Z())/(lengthxy) );
		v->X(v->X()+passo_dist*cos(dirxy)*cos(dirsub));
		v->Y(v->Y()+passo_dist*sin(dirxy)*cos(dirsub));
		v->Z(v->Z()+passo_dist*sin(dirsub));
		v->Pitch(dirsub);
	}
	//	cout << camiao.dirxy << " - " << noi->X() << "   " << noi->Y() << " - " << nof->X() << " - " << nof->Y() << endl;
	//	cout << camiao.x << " " << camiao.y << " " << camiao.z << endl;
}

bool camiao_em_no(No* no){
	No* nof=no;
	Veiculo* v = j->GetVeiculos()->at(0);
	double dist=distancia(nof->X(),nof->Y(),nof->Z(),v->X(),v->Y(),v->Z());
	return (dist < (DISTANCIA_PARAGEM_NO_FRACAO)*nof->Raio());
}

void calcula_posicao_animacao_camiao2(){
	No* noa=j->NoAnterior();
	No* noi=j->NoActual();
	No* nof=j->NoSeguinte();
	Veiculo* v = j->GetVeiculos()->at(0);
	//v->Accelerate(0.05);


	double passo_dist=v->Velocidade();
	double dirsub=0;
	double dirxy=getAnguloRotacaoPlano(noi->X(),noi->Y(),nof->X(),nof->Y())+M_PI/2;
	bool esta_no_act=camiao_em_no(noi);

	double lengthxy=sqrt(pow(nof->X()-noi->X(), 2) + pow(nof->Y()-noi->Y(), 2))-noi->Raio()-nof->Raio();




	//v->Yaw(graus(dirxy-M_PI/2));
	if (!esta_no_act) {
		v->Yaw(graus(dirxy-M_PI/2));
		if (distancia(v->X(),v->Y(),v->Z(),noi->X(),noi->Y(),noi->Z()) < noi->Raio() || distancia(v->X(),v->Y(),v->Z(),nof->X(),nof->Y(),nof->Z()) < nof->Raio()) {		
			v->Pitch(0);
			v->X(v->X()+passo_dist*cos(dirxy));
			v->Y(v->Y()+passo_dist*sin(dirxy));
		}
		else {
			dirsub=atan((nof->Z()-noi->Z())/(lengthxy) );
			v->X(v->X()+passo_dist*cos(dirxy)*cos(dirsub));
			v->Y(v->Y()+passo_dist*sin(dirxy)*cos(dirsub));
			v->Z(v->Z()+passo_dist*sin(dirsub));
			v->Pitch(graus(dirsub));
		}
	} else {
		//		cout << "Calculo trajectoria Rotunda" << endl;
		double dirxy_ant=getAnguloRotacaoPlano(noi->X(),noi->Y(),noa->X(),noa->Y())+M_PI/2;
		if (dirxy <= dirxy_ant) dirxy+=2*M_PI;
		double delta_angulo=dirxy-dirxy_ant;
		double dirxy_cami=getAnguloRotacaoPlano(noi->X(),noi->Y(),v->X(),v->Y())+M_PI/2;
		if (dirxy_cami < dirxy_ant) dirxy_cami+=2*M_PI;
		double we=0; //largura da estrada entrada
		double ws=0; //largura da estrada saida 0 seguir pelo meio da estrada
		double Dp= DISTANCIA_PARAGEM_NO_FRACAO*noi->Raio();
		double Dr= DISTANCIA_RODAGEM_NO_FRACAO*noi->Raio();
		double RJ_ent=(Dp*Dp + (we/4.)*(we/4.) - Dr*Dr)/(2*Dr - 2.*we/4.);
		double RJ_sai=(Dp*Dp + (ws/4.)*(ws/4.) - Dr*Dr)/(2*Dr - 2.*ws/4.);
		double hip_ent=Dr+RJ_ent;
		double hip_sai=Dr+RJ_sai;
		double ang_ent=atan(Dp/(RJ_ent+we/4.));
		double ang_ent_op=M_PI/2-ang_ent;
		double ang_sai=atan(Dp/(RJ_sai+we/4));
		double ang_sai_op=M_PI/2-ang_sai;

		//dirxy_cami vai variar entre o dirxy_ant e o  dirxy (seg)
		//existem 3 movimentos separados e a escolha desses movimentos depende da posicao dele no no em termos de angulo:
		// curva de entrada: entre dirxy_ant e dirxy_ant+ang_ent
		// curva da rotunda: entre dirxy_ant+ang_ent e dirxy - ang_sai
		// curva de saida: entre dirxy - ang_sai e dirxy
		//cout << graus(dirxy_cami) << " - "<< graus(dirxy) << " - " << graus(dirxy_ant+ang_ent_op) << " - " << graus(dirxy-ang_sai_op) << " - " << graus(dirxy) << endl;
		if (dirxy_cami >= dirxy_ant && dirxy_cami < dirxy_ant+ang_ent_op){
			//cout << "ESTA NA ENTRADA" << endl;
			double PxRje=noi->X()+hip_ent*cos(dirxy_ant+ang_ent_op);
			double PyRje=noi->Y()+hip_ent*sin(dirxy_ant+ang_ent_op);
			double Pex=noi->X()+Dp*cos(dirxy_ant);
			double Pey=noi->Y()+Dp*sin(dirxy_ant);
			//double Delta_ang=ang_ent/8.;	//calibra o valor 3-(6)-10-15...
			double Delta_ang=v->Velocidade()/(RJ_ent);
			//double Delta_ang=0;
			double val=( (Pex-PxRje)*(v->X()-PxRje) + (Pey-PyRje)*(v->Y()-PyRje) )/ (RJ_ent*RJ_ent);
			double alpha_R_cam=acos(float(val));
			//cout << graus(alpha_R_cam) << endl;
			v->X(PxRje+RJ_ent*cos(dirxy_ant-M_PI/2-alpha_R_cam-Delta_ang));	//arranjar melhor os angulos
			v->Y(PyRje+RJ_ent*sin(dirxy_ant-M_PI/2-alpha_R_cam-Delta_ang));
			v->Yaw(graus(dirxy_ant+M_PI-alpha_R_cam-M_PI/2.));
		}

		if (dirxy_cami >= dirxy_ant+ang_ent_op && dirxy_cami < dirxy-ang_sai_op){
			//cout << " ESTA NA ROTUNDA " << endl;
			double Delta_ang=v->Velocidade()/(noi->Raio()*DISTANCIA_RODAGEM_NO_FRACAO);
			double novo_ang=dirxy_cami+Delta_ang;
			v->X(noi->X()+(noi->Raio()*DISTANCIA_RODAGEM_NO_FRACAO)*cos(novo_ang));
			v->Y(noi->Y()+(noi->Raio()*DISTANCIA_RODAGEM_NO_FRACAO)*sin(novo_ang));
			v->Yaw(graus(novo_ang));
		}

		if (dirxy_cami >= dirxy-ang_sai_op && dirxy_cami <= dirxy){
			//			cout << "ENTROU NA SAIDA DA ROTUNDA" << endl;
			double PxRjs=noi->X()+hip_sai*cos(dirxy-ang_ent_op);
			double PyRjs=noi->Y()+hip_sai*sin(dirxy-ang_ent_op);
			double Psx=noi->X()+Dp*cos(dirxy);
			double Psy=noi->Y()+Dp*sin(dirxy);
			double Delta_ang=ang_sai/12.;	//calibra o valor 3-(6)-15... reparei que o 10 nao funciona por falta de precisao 8 e muito bom
			//double Delta_ang=v->Velocidade()/(RJ_sai+0.01);
			//double Delta_ang=0;
			double val=( (Psx-PxRjs)*(v->X()-PxRjs) + (Psy-PyRjs)*(v->Y()-PyRjs) )/ (RJ_sai*RJ_sai);
			double alpha_R_cam=acos(float(val));
			//			cout << graus(alpha_R_cam) << endl;
			v->X(PxRjs+RJ_sai*cos(dirxy+M_PI/2+alpha_R_cam-Delta_ang));	//arranjar melhor os angulos
			v->Y(PyRjs+RJ_sai*sin(dirxy+M_PI/2+alpha_R_cam-Delta_ang));
			v->Yaw(graus(dirxy+alpha_R_cam-M_PI/2.));
		}
	}

	//		cout << v->X() << " " << v->Y() << " " << v->Z() <<" graus: "  << v->Yaw() << endl;
	//		cout << distancia(noi->X(),noi->Y(),noi->Z(),v->X(),v->Y(),v->Z())<< endl;
}

void actualiza_percurso(){
	if(j->GetPercurso()->size() > 0) {
		if (j->NoSeguinte() == NULL) {
			j->NoSeguinte(j->GetPercurso()->at(0));
			j->GetPercurso()->erase(j->GetPercurso()->begin());
		} else {
			j->NoAnterior(j->NoActual());
			j->NoActual(j->NoSeguinte());
			j->NoSeguinte(j->GetPercurso()->at(0));
			j->GetPercurso()->erase(j->GetPercurso()->begin());
		}
	} else {
		alterarModoJogo(MODO_DESTINO);
	}
}


void mexe_camiao2(){
	if (!camiao_em_no(j->NoSeguinte()))
		calcula_posicao_animacao_camiao2();
	else {
		if (j->NoSeguinte()!=NULL){
			if (j->NoSeguinte()->IsPontoEntrega()){
				alterarModoJogo(MODO_CARGA);
			} else {
				actualiza_percurso();
			}
		} else actualiza_percurso();
	}
}


void Timer(int value)
{	
	glutTimerFunc(50,Timer,0);

	if (j->ModoJogo() == MODO_DESTINO) {
		if (j->GetEncomendas()->size() == 0) {
			cout << "FIM DO JOGO" << endl;
			cout << "PONTUACAO: " << j->Temporizador() << endl;
			Website* w = new Website();
			theMenu.resultados = w->SetResultados(1, 1, 1, j->Temporizador());
			Sleep(1500);
			alterarModoJogo(MODO_MENU);
			theMenu.menuLevel= 4;
			j->Desactivar();
			theMenu.onGame=j->IsActivo();
		}
	}

	if (j->ModoJogo() == MODO_ANIMACAO) {
		mexe_camiao2();
		glutPostRedisplay();
	}

	estado.streetNameRotation+=5;
	if (estado.streetNameRotation >= 360) estado.streetNameRotation=0;
}

void Temporizador(int value)
{

	glutTimerFunc(1000,Temporizador,0);

	if (j->ModoJogo() == MODO_ANIMACAO || j->ModoJogo() == MODO_CARGA) 
	{
		j->IncrementTemporizador(1);
	}
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	alutInit (&argc, argv);

	/* need both double buffering and z buffer */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if (!createGLUTWindow("DEI Alumni", false)) exit(1);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotionMouse);

	myInit();
	al_music_jogo(0);
	imprime_ajuda();

	glutTimerFunc(1000,Temporizador,0);
	glutTimerFunc(50,Timer,0);
	glutMainLoop();
}

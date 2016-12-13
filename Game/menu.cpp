#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "menu.h"
#include "Textures.h"

void menu::Init() {

	menuLevel=1;
	action=0;

	//Load mapas Thumbs
	this->LoadMaps();
	
	for(int i = 0; i < maxMapas; i++)
	{
		char nome[261] = "mapas/";
		strcat(nome, mapasThumbnailsNames[i]);
		Textures::Load_Texture(mapasThumbnails[i], nome , false, GL_REPLACE, true);
	}
	
	//load textures
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_BACK],"images/menu_back.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_DEI],"images/menu_DEIAlumni.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_INICIAR_OFF],"images/menu_iniciar_off.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_INICIAR_ON],"images/menu_iniciar_on.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_SAIR_OFF],"images/menu_sair_off.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_SAIR_ON],"images/menu_sair_on.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_TORNEIO_OFF],"images/menu_torneio_off.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_TORNEIO_ON],"images/menu_torneio_on.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_VOLTAR_OFF],"images/menu_voltar_off.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_VOLTAR_ON],"images/menu_voltar_on.bmp", true, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_LEFT],"images/btn_l.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_RIGHT],"images/btn_r.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_BTN_OFF],"images/btn_off.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_BTN_ON],"images/btn_on.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(menuTextures[ID_TEXTURA_MENU_TORNEIOS],"images/menu_torneios.jpg", false, GL_REPLACE, true);

	selectedMenuItem = ID_MENU_START;

}

void menu::initializeMenu(){
	menuLevel=1;
	action=0;
	selectedMenuItem=0;
}

void menu::LoadMaps()
{
	ifstream fin;
	string dir, filepath;
	int num;
	DIR *dp;
	struct dirent *dirp;
	Utilities u;
	vector<string> v;
	int i = 0, j = 0;

	dp = opendir("mapas");
	if (dp == NULL)
	{
		cout << "Error(" << errno << ") opening " << dir << endl;
		return;
	}

	while ((dirp = readdir( dp )))
	{
		filepath = dir + "\\" + dirp->d_name;

		if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
		{
			cout << "Filename: " << dirp->d_name << " Filetype: " << dirp->d_type << endl;
			v = u.split(dirp->d_name, '.');

			if(v[1].compare("jpg") == 0)
			{
				string str = v[0] + '.' + v[1];
				strcpy(this->mapasThumbnailsNames[i], str.c_str());
				i++;
			}
			else
			{
				string str = "mapas/" + v[0] + '.' + v[1];
				strcpy(this->mapasNames[j], str.c_str());
				j++;
			}

		}
	}

	maxMapas=i;
	closedir( dp );
}

void menu::selectMenuLeft (){
	selectedMapa++;
	if (selectedMapa >= maxMapas) selectedMapa = 0;
}

void menu::selectMenuRight (){
	selectedMapa--;
	if (selectedMapa < 0) selectedMapa = maxMapas-1;
}

void menu::selectMenuUp (){
	if (menuLevel != 1 && menuLevel != 3) {
		return;
	}
	switch (selectedMenuItem){
	case ID_MENU_START:
		//Do Nothing
		break;
	case ID_MENU_TORNEIO:
		selectedMenuItem=ID_MENU_START;
		break;
	case ID_MENU_VOLTAR:
		//Do Nothing
		break;
	case ID_MENU_SAIR:
		if (onGame) {
			selectedMenuItem=ID_MENU_VOLTAR;
		}else{
			selectedMenuItem=ID_MENU_TORNEIO;
		}
		break;
	case 31:
		selectedMenuItem=33;
		break;
	case 32:
		selectedMenuItem=31;
		break;
	case 33:
		selectedMenuItem=32;
		break;
	}
	glutPostRedisplay();
}

void menu::selectMenuDown (){
	if (menuLevel != 1 && menuLevel != 3) {
		return;
	}
	switch (selectedMenuItem){
	case ID_MENU_START:
		selectedMenuItem=ID_MENU_TORNEIO;
		break;
	case ID_MENU_TORNEIO:
		selectedMenuItem=ID_MENU_SAIR;
		break;
	case ID_MENU_VOLTAR:
		selectedMenuItem=ID_MENU_SAIR;
		break;
	case ID_MENU_SAIR:		
		//Do Nothing
		break;
	case 31:
		selectedMenuItem=32;
		break;
	case 32:
		selectedMenuItem=33;
		break;
	case 33:
		selectedMenuItem=31;
		break;
	default:
		if (onGame){
			selectedMenuItem=ID_MENU_VOLTAR;
		}else{
			selectedMenuItem=ID_MENU_START;
		}
		break;
	}
	glutPostRedisplay();
}

void menu::processMenuHits (GLint hits, GLuint buffer[], bool select)
{
	unsigned int i, j;
	GLuint names, *ptr;

	if (hits > 0 ) {
		ptr = (GLuint *) buffer;
		selectedMenuItem=ptr[3];
		if (select) {
			action = selectedMenuItem;
		}else{
			action=0;
			glutPostRedisplay();
		}
	}
	else
	{
		selectedMenuItem = 0;
	}
}

void menu::desenhaMenuItem(int textureID, int itemID, int x, int y){
	glEnable(GL_TEXTURE_2D);
	glPushName(itemID); //Load Name to selection stack
	glBindTexture(GL_TEXTURE_2D, menuTextures[textureID]);
	glBegin (GL_QUADS);		
	glTexCoord2d (0.0,1.0);	glVertex2d (x,y);
	glTexCoord2d (1.0,1.0);	glVertex2d (x+400,y);
	glTexCoord2d (1.0,0.0);	glVertex2d (x+400,y+100);
	glTexCoord2d (0.0,0.0);	glVertex2d (x,y+100);
	glEnd ();
	glPopName();
	glDisable(GL_TEXTURE_2D);
}

void menu::desenhaMenuAllItems(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	desenhaMenuItem(ID_TEXTURA_MENU_DEI, ID_MENU_DEIALUMNI, 100, -500);

	if (!onGame) {
		if (selectedMenuItem == ID_MENU_VOLTAR) selectedMenuItem=ID_MENU_START;

		if (selectedMenuItem==ID_MENU_START){
			desenhaMenuItem(ID_TEXTURA_MENU_INICIAR_ON, ID_MENU_START, 300, -300);
		}else{
			desenhaMenuItem(ID_TEXTURA_MENU_INICIAR_OFF, ID_MENU_START, 300, -300);
		}

		if (selectedMenuItem==ID_MENU_TORNEIO){
			desenhaMenuItem(ID_TEXTURA_MENU_TORNEIO_ON, ID_MENU_TORNEIO, 300, -150);
		}else{
			desenhaMenuItem(ID_TEXTURA_MENU_TORNEIO_OFF, ID_MENU_TORNEIO, 300, -150);
		}

	}else{
		if (selectedMenuItem == ID_MENU_START) selectedMenuItem=ID_MENU_VOLTAR;

		if (selectedMenuItem==ID_MENU_VOLTAR){
			desenhaMenuItem(ID_TEXTURA_MENU_VOLTAR_ON, ID_MENU_VOLTAR, 300, -300);
		}else{
			desenhaMenuItem(ID_TEXTURA_MENU_VOLTAR_OFF, ID_MENU_VOLTAR, 300, -300);
		}
	}

	if (selectedMenuItem==ID_MENU_SAIR){
		desenhaMenuItem(ID_TEXTURA_MENU_SAIR_ON, ID_MENU_SAIR, 300, 0);
	}else{
		desenhaMenuItem(ID_TEXTURA_MENU_SAIR_OFF, ID_MENU_SAIR, 300, 0);
	}
}

void menu::desenhaMenuMapChoice(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_LEFT]);
	glPushName(21); 
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(100, 0);
	glTexCoord2d (1.0,0.0);	glVertex2d(150, 0);
	glTexCoord2d (1.0,1.0);	glVertex2d(150, 50);
	glTexCoord2d (0.0,1.0);	glVertex2d(100, 50);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	//Load Map Pic
	glPushName(25); 
	glBindTexture(GL_TEXTURE_2D, mapasThumbnails[selectedMapa]);
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(200, -200);
	glTexCoord2d (0.0,1.0);	glVertex2d(200, 200);
	glTexCoord2d (1.0,1.0);	glVertex2d(600, 200);
	glTexCoord2d (1.0,0.0);	glVertex2d(600, -200);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glPushName(22); 
	glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,1.0);	glVertex2d(650, 50);
	glTexCoord2d (0.0,0.0);	glVertex2d(650, 0);
	glTexCoord2d (1.0,0.0);	glVertex2d(700, 0);
	glTexCoord2d (1.0,1.0);	glVertex2d(700, 50);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glDisable(GL_TEXTURE_2D);

}

void menu::desenhaMenuTournamentChoice(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_TORNEIOS]);
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(100, -500);
	glTexCoord2d (0.0,1.0);	glVertex2d(100, -400);
	glTexCoord2d (1.0,1.0);	glVertex2d(600, -400);
	glTexCoord2d (1.0,0.0);	glVertex2d(600, -500);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);

	if (selectedMenuItem==31){
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_ON]);
	}else{
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_OFF]);
	}
	glPushName(31); 
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(100, -200);
	glTexCoord2d (0.0,1.0);	glVertex2d(100, -100);
	glTexCoord2d (1.0,1.0);	glVertex2d(600, -100);
	glTexCoord2d (1.0,0.0);	glVertex2d(600, -200);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glColor3f(0.0f,0.0f,0.0f);
	strokeCenterString("Nome Torneio 1", 280, -120, 0, 0.3);
	glPopName();

	if (selectedMenuItem==32){
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_ON]);
	}else{
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_OFF]);
	}
	glPushName(32); 
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(100, 0);
	glTexCoord2d (0.0,1.0);	glVertex2d(100, 100);
	glTexCoord2d (1.0,1.0);	glVertex2d(600, 100);
	glTexCoord2d (1.0,0.0);	glVertex2d(600, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glColor3f(0.0f,0.0f,0.0f);
	strokeCenterString("Nome Torneio 2", 280, 80, 0, 0.3);
	glPopName();

	if (selectedMenuItem==33){
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_ON]);
	}else{
		glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BTN_OFF]);
	}
	glPushName(33); 
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d(100, 200);
	glTexCoord2d (0.0,1.0);	glVertex2d(100, 300);
	glTexCoord2d (1.0,1.0);	glVertex2d(600, 300);
	glTexCoord2d (1.0,0.0);	glVertex2d(600, 200);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glColor3f(0.0f,0.0f,0.0f);
	strokeCenterString("Nome Torneio 3", 280, 280, 0, 0.3);
	glPopName();

	glDisable(GL_TEXTURE_2D);

}

void menu::desenhaMenuScore(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR);

	int startY = -200;

	glColor3f(0.0f,0.0f,0.0f);

	strokeCenterString("RANKING", 300, startY, 0, 0.4);

	startY=-100;
	for (int i=0; i< resultados->size();i++){
		strokeCenterString(const_cast<char*>(resultados->at(i).c_str()), 300, startY + i * 60, 0, 0.3);
	}

	glDisable(GL_COLOR);
	glEnable(GL_TEXTURE_2D);

}

void menu::pickMenu(int x, int y, bool select)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int winWidth = glutGet(GLUT_WINDOW_WIDTH);

	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*  create 1x1 pixel picking region near cursor location      */
	gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
		1.0, 1.0, viewport);
	gluOrtho2D(-winWidth, winWidth, winHeight, -winHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glInitNames(); //Clears the selection name stack.

	glSelectBuffer (BUFSIZE, selectBuf);
	(void) glRenderMode (GL_SELECT);

	switch (menuLevel){
	case 1:
		desenhaMenuAllItems ();
		break;
	case 2:
		desenhaMenuMapChoice ();
		break;
	case 3:
		//if (loginWS()){
		//	loadTorneios();
		desenhaMenuTournamentChoice ();
		//} else {
		//	cout << "Erro a descarregar lista de torneios disponiveis";
		//}
		break;
	}

	hits = glRenderMode (GL_RENDER);

	processMenuHits (hits, selectBuf, select);

} 

void menu::draw() {

	int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int winWidth = glutGet(GLUT_WINDOW_WIDTH);

	// Altera viewport e projecção para 2D 
	glViewport(0, 0, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-winWidth, winWidth, winHeight, -winHeight);

	glDisable(GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//White BackGround 
	glEnable(GL_COLOR);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin (GL_QUADS);		
	glVertex2d (-winWidth,-winHeight);
	glVertex2d (winWidth,-winHeight);
	glVertex2d (winWidth,winHeight);
	glVertex2d (-winWidth,winHeight);
	glEnd ();
	glDisable(GL_COLOR);

	//BackGround Pic
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menuTextures[ID_TEXTURA_MENU_BACK]);
	glBegin (GL_QUADS);		
	glTexCoord2d (0.0,0.0);	glVertex2d (-winWidth,-winHeight);
	glTexCoord2d (1.0,0.0);	glVertex2d (800,-winHeight);
	glTexCoord2d (1.0,1.0);	glVertex2d (800,600);
	glTexCoord2d (0.0,1.0);	glVertex2d (-winWidth,600);
	glEnd ();
	glDisable(GL_TEXTURE_2D);

	//Menu Items
	switch (menuLevel){
	case 1:
		desenhaMenuAllItems ();
		break;
	case 2:
		desenhaMenuMapChoice ();
		break;
	case 3:
		desenhaMenuTournamentChoice ();
		break;
	case 4:
		desenhaMenuScore ();
		break;
	}

	// repõe estado
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}

void menu::strokeCenterString(char *str,double x, double y, double z, double s)
{
	int i,n;

	n = strlen(str);
	glPushMatrix();
	glTranslated(x-glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char*)str)*0.5*s,y-119.05*0.5*s,z);
	glScaled(s,s,s);
	glRotatef(180,1,0,0);
	for(i=0;i<n;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)str[i]);
	glPopMatrix();

}
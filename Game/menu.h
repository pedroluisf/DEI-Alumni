#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "dirent.h"
#include "Utilities.h"

#define MAX_MENU_TEXTURES 15
#define MAX_MAP_TEXTURES 10
#define BUFSIZE 512

#define ID_MENU_DEIALUMNI	5
#define ID_MENU_START		1
#define ID_MENU_TORNEIO		3
#define ID_MENU_VOLTAR		9
#define ID_MENU_SAIR		99

#define ID_TEXTURA_MENU_BACK				0
#define ID_TEXTURA_MENU_DEI					1
#define ID_TEXTURA_MENU_INICIAR_OFF			2
#define ID_TEXTURA_MENU_INICIAR_ON			3
#define ID_TEXTURA_MENU_SAIR_OFF			4
#define ID_TEXTURA_MENU_SAIR_ON				5
#define ID_TEXTURA_MENU_TORNEIO_OFF			6
#define ID_TEXTURA_MENU_TORNEIO_ON			7
#define ID_TEXTURA_MENU_VOLTAR_OFF			8
#define ID_TEXTURA_MENU_VOLTAR_ON			9
#define ID_TEXTURA_MENU_LEFT				10
#define ID_TEXTURA_MENU_RIGHT				11
#define ID_TEXTURA_MENU_BTN_OFF				12
#define ID_TEXTURA_MENU_BTN_ON				13
#define ID_TEXTURA_MENU_TORNEIOS			14

using namespace std;

class menu {
private: 

	int maxMapas;

	void desenhaMenuItem(int textureID, int itemID, int x, int y);

	void desenhaMenuAllItems();

	void desenhaMenuMapChoice();

	void desenhaMenuTournamentChoice();

	void desenhaMenuScore();

	void processMenuHits (GLint hits, GLuint buffer[], bool select);

	void strokeCenterString(char *str,double x, double y, double z, double s);
	
	void LoadMaps();

public:  

	int menuLevel;
	int selectedMenuItem;
	int selectedMapa;
	int action;
	vector<string>* resultados;

	menu() { } //constructor

	void Init();

	void initializeMenu();

	void draw();

	void selectMenuOption ();

	void selectMenuUp ();

	void selectMenuDown ();

	void selectMenuLeft ();

	void selectMenuRight ();

	void pickMenu(int x, int y, bool select);

	GLuint	menuTextures[MAX_MENU_TEXTURES];

	GLuint	mapasThumbnails[MAX_MAP_TEXTURES];

	char mapasThumbnailsNames[MAX_MAP_TEXTURES][261];
	char mapasNames[MAX_MAP_TEXTURES][261];

	bool onGame;

};
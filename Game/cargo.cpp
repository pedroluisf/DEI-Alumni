#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "cargo.h"
#include "Textures.h"

void cargo::Init(vector<Encomenda*>* jencomendas, vector<Encomenda*>* jencomendas_entregues) {

	//load textures
	Textures::Load_Texture(cargoTextures[ID_TEXTURA_CARGO_BACK],"images/cargo_dock.jpg", false, GL_REPLACE, true);
	Textures::Load_Texture(cargoTextures[ID_TEXTURA_CARGO_GO],"images/btn_off.jpg", false, GL_REPLACE, true);

	num_objectos = jencomendas->size() + NUM_MAX_BARRAS;

	//encomendas = new vector<Encomenda*>();
	this->encomendas = jencomendas;
	this->encomendas_entregues = jencomendas_entregues;
	frios = new vector<Encomenda*>();
	objectos = new vector<Encomenda*>();

	//Define o contentor do camião. Este procedimento poderia ser alterado se o camião mudasse mediante o jogo
	for (int i=0; i<CARGO_HEIGHT; i++){		
		if (i==0 || i==CARGO_HEIGHT-1){
			for (int k=0; k<CARGO_WIDTH; k++)		
				strcat(cargoHold[i], "*");
		} else {
			for (int k=0; k<CARGO_WIDTH-1; k++)		
				strcat(cargoHold[i], " ");
			strcat(cargoHold[i], "*");
		}
	}

	initModelo();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_NORMALIZE);  // para tratar as normais

	startDrag=false;

}

void cargo::initModelo(){
	// modo de jogo: inicia em carga
	cargo_mode = true;
	strcpy(msgUser, "");

	//Tetromino t1;
	//Encomenda* e1 = new Encomenda();
	//e1->setId(1);
	//e1->IsExplosivo(false);
	//e1->IsInflamavel(false);
	//e1->setForma(1);
	//e1->setOrientacao(0);
	//e1->setRGB(0.7,0.7,0.7);
	//e1->setPos(-22,0);
	//encomendas->push_back(e1);

	////Tetromino t2;
	//Encomenda* e2 = new Encomenda();
	//e2->setId(2);
	//e2->IsExplosivo(false);
	//e2->IsInflamavel(false);
	//e2->isLoaded(false);
	//e2->setForma(3);
	//e2->setOrientacao(0);
	//e2->setRGB(1,0,0);
	//e2->setPos(-22,13);
	//encomendas->push_back(e2);

	////Tetromino t3;
	//Encomenda* e3 = new Encomenda();
	//e3->setId(3);
	//e3->IsExplosivo(false);
	//e3->IsInflamavel(true);
	//e3->setForma(5);
	//e3->setOrientacao(0);
	//e3->setRGB(1,1,0);
	//e3->setPos(-22,8);
	//encomendas->push_back(e3);

	////Tetromino t4;
	//Encomenda* e4 = new Encomenda();
	//e4->setId(4);
	//e4->IsExplosivo(false);
	//e4->IsInflamavel(false);
	//e4->setForma(7);
	//e4->setOrientacao(0);
	//e4->setRGB(0.8,1,0);
	//e4->setPos(-22,-9);
	//encomendas->push_back(e4);

	////Tetromino t5;
	//Encomenda* e5 = new Encomenda();
	//e5->setId(5);
	//e5->IsExplosivo(false);
	//e5->IsInflamavel(false);
	//e5->setForma(7);
	//e5->setOrientacao(0);
	//e5->setRGB(1,1,0.5);
	//e5->setPos(-22,-13);
	//encomendas->push_back(e5);

	////Tetromino t6;
	//Encomenda* e6 = new Encomenda();
	//e6->setId(6);
	//e6->IsExplosivo(false);
	//e6->IsInflamavel(false);
	//e6->setForma(4);
	//e6->setOrientacao(0);
	//e6->setRGB(1,0,1);
	//e6->setPos(-22,-18);
	//encomendas->push_back(e6);

	// barras de frio
	//Tetromino t7;
	Encomenda* b1 = new Encomenda();
	b1->setId(7);
	b1->IsExplosivo(false);
	b1->IsInflamavel(false);
	b1->setTipoObj(9);
	b1->setForma(8);
	b1->setOrientacao(0);
	b1->setRGB(0.7,0.7,0.7);
	b1->setPos(-18,-18);
	frios->push_back(b1);

	//Tetromino t8;
	Encomenda* b2 = new Encomenda();
	b2->setId(8);
	b2->IsExplosivo(false);
	b2->IsInflamavel(false);
	b2->setTipoObj(9);
	b2->setForma(8);
	b2->setOrientacao(0);
	b2->setRGB(0.7,0.7,0.7);
	b2->setPos(-18,-18);
	frios->push_back(b2);
	//Tetromino t9;
	Encomenda* b3 = new Encomenda();
	b3->setId(9);
	b3->IsExplosivo(false);
	b3->IsInflamavel(false);
	b3->setTipoObj(9);
	b3->setForma(8);
	b3->setOrientacao(0);
	b3->setRGB(0.7,0.7,0.7);
	b3->setPos(-18,-18);
	frios->push_back(b3);

	//Tetromino t10;
	Encomenda* b4 = new Encomenda();
	b4->setId(10);
	b4->IsExplosivo(false);
	b4->IsInflamavel(false);
	b4->setTipoObj(9);
	b4->setForma(8);
	b4->setOrientacao(0);
	b4->setRGB(0.7,0.7,0.7);
	b4->setPos(-18,-18);
	frios->push_back(b4);

	if(encomendas->size() > 27) exit(1);
	int xvec[27];
	int yvec[27];
	int nvec = 0;

	for(int j = 0; j < 9; j++)
	{
		for(int x = 0; x < 3; x++)
		{
			xvec[nvec] = MIN_X + 3 + 4*x;
			yvec[nvec] = MAX_Y - 1 - 4*j;
			nvec++;
		}
	}
	nvec = 0;

	for(int i = 0; i < this->encomendas->size(); i++)
	{
		Encomenda* e = encomendas->at(i);
		e->setId(i+1);
		e->setPos(xvec[nvec], yvec[nvec]);
		nvec++;
	}

	// mergir tudo no vector objectos -> as encomendas primeiro
	for (int i=0; i<encomendas->size(); i++)
	{
		objectos->push_back(encomendas->at(i));
	}
	for (int i=0; i<frios->size(); i++)
	{
		objectos->push_back(frios->at(i));
	}
	// encomenda seleccionada inicialmente
	selIdx = 0;

	// criar a área de jogo para os objectos
	// feito aqui para poupar desenhos
	for (int y=MIN_Y; y<=MAX_Y; y++)
	{
		for (int x=CARGO_X; x<=MAX_X; x++)
		{
			if (!(x>=CARGO_X && x<CARGO_X+CARGO_WIDTH && y>=CARGO_Y && y<CARGO_Y+CARGO_HEIGHT))
				matObjectos[y+MAX_Y][x+MAX_X] = 1;
		}
	}

	// actualizar a matriz de objectos
	//for (int i=0; i<NUM_ENCOMENDAS; i++)
	for (int i=0; i<num_objectos; i++)
	{
		//updateMatObjectos(i, 1);
		updateMatObjectos(i, objectos->at(i)->getTipoObj());
	}

}

void cargo::initObjectos(){
	objectos->clear();
	for (int i=0; i<encomendas->size(); i++)
	{
		objectos->push_back(encomendas->at(i));
	}
	for (int i=0; i<frios->size(); i++)
	{
		objectos->push_back(frios->at(i));
	}

}

void cargo::updateMatObjectos(int idx, int val)
{
	int x0 = objectos->at(idx)->getTetromino()->getX() + MAX_X; // correcao para a origem
	int y0 = objectos->at(idx)->getTetromino()->getY() + MAX_Y; // correcao para a origem	


	for (int i=0; i<4; i++) //  introduzi overhead para o 1º - desnecessário
	{
		int x = x0 + objectos->at(idx)->getTetromino()->getCubo(i)->getX();
		int y = y0 + objectos->at(idx)->getTetromino()->getCubo(i)->getY();
		matObjectos[y][x] = val;
	}
}

bool cargo::checkLoaded()
{
	bool loaded = true;
	GLint x0 = objectos->at(selIdx-1)->getTetromino()->getX();
	GLint y0 =  objectos->at(selIdx-1)->getTetromino()->getY();

	for (int i=0; i<4; i++) //  introduzi overhead para o 1º - desnecessário
	{
		int x = x0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(i)->getX();
		int y = y0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(i)->getY();
		// verificar se está dentro
		if (!(x>CARGO_X && x<CARGO_X+CARGO_WIDTH && y>CARGO_Y && y<CARGO_Y+CARGO_HEIGHT))
			loaded = false;
	}

	objectos->at(selIdx-1)->isLoaded(loaded);

	return loaded;
}

bool cargo::checkAllLoaded()
{
	bool allLoaded = true;
	//só verifica as encomendas porque estão no início do vector
	for (int i=0; i<encomendas->size(); i++)
	{
		if (!objectos->at(i)->isLoaded())
			allLoaded = false;
	}

	return allLoaded;
}

void cargo::entregaEncomendas(string no){
	int n=encomendas->size();
	for (int i=n-1; i>=0; i--){
		if (!objectos->at(i)->isLoaded() && objectos->at(i)->No().compare(no)==0){
			encomendas_entregues->push_back(objectos->at(i));
			updateMatObjectos(i, 0);
			encomendas->erase(encomendas->begin()+i);
			initObjectos();
		}
	}
	num_objectos = encomendas->size() + NUM_MAX_BARRAS;

	// actualizar a matriz de objectos
	//for (int i=0; i<NUM_ENCOMENDAS; i++)
	for (int i=0; i<num_objectos; i++)
	{
		//updateMatObjectos(i, 1);
		updateMatObjectos(i, objectos->at(i)->getTipoObj());
	}

}

bool cargo::checkTodasEncomendasEntreguesEmNo(string no)
{
	bool flag = true;
	entregaEncomendas(no);
	//só verifica as encomendas porque estão no início do vector
	for (int i=0; i<encomendas->size(); i++)
	{
		if (objectos->at(i)->isLoaded() && objectos->at(i)->No().compare(no)==0)
			flag = false;
	}
	return flag;
}


bool cargo::checkAllUnloaded()
{
	bool allUnloaded = true;
	//só verifica as encomendas porque estão no início do vector
	for (int i=0; i<encomendas->size(); i++)
	{
		if (objectos->at(i)->isLoaded())
			allUnloaded = false;
	}

	return allUnloaded;
}

bool cargo::checkSelfCubo(GLint x, GLint y, GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3)
{
	// verifica se o cubo não é do próprio tetromino
	bool same = false;

	if ((x==x0 && y==y0) || (x==x1 && y==y1) || (x==x2 && y==y2) || (x==x3 && y==y3))
		same = true;

	return same;
}

bool cargo::validaCarga()
{
	bool valida = true;
	// percorrer todas as encomendas e ver se não tem inflamadas 
	//for ()
	return valida;
}

bool cargo::checkColisao(GLint nx0, GLint ny0, GLint no)
{
	bool colisao = false;
	bool rotacao = false;
	GLint orientacao =  objectos->at(selIdx-1)->getTetromino()->getOrientacao();

	// coordenadas actuais
	GLint x0 =  objectos->at(selIdx-1)->getTetromino()->getX();
	GLint y0 =  objectos->at(selIdx-1)->getTetromino()->getY();
	GLint x1 = x0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(1)->getX();
	GLint y1 = y0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(1)->getY();
	GLint x2 = x0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(2)->getX();
	GLint y2 = y0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(2)->getY();
	GLint x3 = x0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(3)->getX();
	GLint y3 = y0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(3)->getY();

	// verifica se é uma rotacao e roda temporariamente
	if (x0==nx0 && y0==ny0)
	{
		rotacao = true;
		objectos->at(selIdx-1)->getTetromino()->setOrientacao(no);
	}
	// coordenadas para onde se pretende mover
	GLint nx1 = nx0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(1)->getX();
	GLint ny1 = ny0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(1)->getY();
	GLint nx2 = nx0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(2)->getX();
	GLint ny2 = ny0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(2)->getY();
	GLint nx3 = nx0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(3)->getX();
	GLint ny3 = ny0 +  objectos->at(selIdx-1)->getTetromino()->getCubo(3)->getY();

	// verifica limites de jogo -> ver MAX e MIN nos defines
	if (nx0>MAX_X || nx0<MIN_X || ny0>MAX_Y || ny0<MIN_Y ||
		nx1>MAX_X || nx1<MIN_X || ny1>MAX_Y || ny1<MIN_Y ||
		nx2>MAX_X || nx2<MIN_X || ny2>MAX_Y || ny2<MIN_Y ||
		nx3>MAX_X || nx3<MIN_X || ny3>MAX_Y || ny3<MIN_Y)
		colisao = true;

	// verifica colisão com outros tetrominos
	if ((matObjectos[ny0+MAX_Y][nx0+MAX_X]>0 && !checkSelfCubo(nx0,ny0,x0,y0,x1,y1,x2,y2,x3,y3)) || 
		(matObjectos[ny1+MAX_Y][nx1+MAX_X]>0 && !checkSelfCubo(nx1,ny1,x0,y0,x1,y1,x2,y2,x3,y3)) ||
		(matObjectos[ny2+MAX_Y][nx2+MAX_X]>0 && !checkSelfCubo(nx2,ny2,x0,y0,x1,y1,x2,y2,x3,y3)) || 
		(matObjectos[ny3+MAX_Y][nx3+MAX_X]>0 && !checkSelfCubo(nx3,ny3,x0,y0,x1,y1,x2,y2,x3,y3)))
		colisao = true;

	// coloca na orientação original
	if (rotacao)
		objectos->at(selIdx-1)->getTetromino()->setOrientacao(orientacao);

	return colisao;
}

void cargo::moveTetromino(GLint nx, GLint ny)
{
	if (!checkColisao(nx,ny, 0))
	{
		updateMatObjectos(selIdx-1, 0);
		objectos->at(selIdx-1)->setPos(nx,ny);
		updateMatObjectos(selIdx-1, objectos->at(selIdx-1)->getTipoObj());
		checkLoaded();
		if (cargo_mode && checkAllLoaded())
		{
			cargo_mode = false;
			printf("\nAll loaded!!!\n");
		}
		if (!cargo_mode && checkAllUnloaded())
		{
			cargo_mode = true;
			printf("\nAll Unloaded!!!\n");
		}
	} else {
		startDrag=false;
	}
}

void cargo::rodaTetromino()
{
	int novaOrientacao = objectos->at(selIdx-1)->getTetromino()->getOrientacao() + 90;
	printf("Nova Orientacao %d", novaOrientacao);
	if (novaOrientacao >= 360){
		novaOrientacao=0;
	}
	GLint x =  objectos->at(selIdx-1)->getTetromino()->getX();
	GLint y =  objectos->at(selIdx-1)->getTetromino()->getY();

	if (!checkColisao(x,y,novaOrientacao))
	{
		updateMatObjectos(selIdx-1, 0);
		//printf("Nova orientação: %d\n",novaOrientacao);
		objectos->at(selIdx-1)->getTetromino()->setOrientacao(novaOrientacao);
		updateMatObjectos(selIdx-1, objectos->at(selIdx-1)->getTipoObj());
		//printf("( %d , %d )\n",nx,ny);
		checkLoaded();
		if (cargo_mode && checkAllLoaded())
		{
			cargo_mode = false;
			printf("\nAll loaded!!!\n");
		}
		if (!cargo_mode && checkAllUnloaded())
		{
			cargo_mode = true;
			printf("\nAll Unloaded!!!\n");
		}
	}
}

void cargo::pickPackage (GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr;

	ptr = (GLuint *) buffer;

	if (hits>0){
		selIdx = ptr[3];
		startDrag = true;
	} else {
		selIdx = 0;
		startDrag = false;
	}

}

void cargo::dragPackage (int x, int y, int z)
{
	for (int i=0; i<num_objectos; i++)
	{
		if (objectos->at(i)->getId()==selIdx){
			moveTetromino(x, y);
		}
	}

}

void cargo::strokeCenterString(char *str,double x, double y, double z, double s)
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

void cargo::picking(int x, int y)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint vp[4];
	GLdouble proj[16], mv[16];
	GLdouble newx, newy, newz;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setVisualArea(true, x, y);

	glInitNames(); //Clears the selection name stack.

	glSelectBuffer (BUFSIZE, selectBuf);
	(void) glRenderMode (GL_SELECT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Desenha encomendas
	drawCargoBoxs();	

	//Desenha GO button
	drawGOButton();

	hits = glRenderMode (GL_RENDER);

	if (startDrag) {
		glGetIntegerv(GL_VIEWPORT, vp);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, (double) selectBuf[2] / UINT_MAX, mv, proj, vp, &newx, &newy, &newz);
		moveTetromino(newx, newy);
	}else{
		pickPackage (hits, selectBuf);
	}

} 

void cargo::GetOGLPos(int x, int y, int nx, int ny) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	printf("\nposx=%d, posy=%d", posX, posY);
	nx = posX;
	ny = posY;
	//nz = posZ;
}

void cargo::desenhaCargoHold()
{
	glPushMatrix();
	// código para desenhar a local de carga
	for (int y=0; y<CARGO_HEIGHT; y++){
		for (int x=0; x<CARGO_WIDTH; x++){
			// guardar os na matriz de objectos
			int px = x + CARGO_X;
			int py = y + CARGO_Y;
			if (cargoHold[y][x] == '*'){
				//glPushMatrix();
				//glTranslatef(px, py, 0.0f);
				//Cubo c;
				//c.setCor(0.5,0.5,0.5);
				//c.setPos(px,py);
				//c.desenha();
				matObjectos[py+MAX_Y][px+MAX_X] = 1;
				//glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

void cargo::drawGOButton(){
	
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	glEnable(GL_TEXTURE_2D);

	glPushName(999); 
	glBindTexture(GL_TEXTURE_2D, cargoTextures[ID_TEXTURA_CARGO_GO]);
	glBegin(GL_QUADS);
	glTexCoord2d (0.0,1.0);	glVertex2d(width / 2 - 200, 90);
	glTexCoord2d (0.0,0.0);	glVertex2d(width / 2 - 200, 10);
	glTexCoord2d (1.0,0.0);	glVertex2d(width / 2 + 200, 10);
	glTexCoord2d (1.0,1.0);	glVertex2d(width / 2 + 200, 90);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopName();

	glDisable(GL_TEXTURE_2D);

}

void cargo::drawCargoBoxs() {

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR);

	// desenhar todas Encomendas
	for (int i=0; i<num_objectos; i++)
	{
////		glPushName(objectos->at(i)->getId());
		glPushName(i+1);
		objectos->at(i)->desenha();
		glPopName();
	}

	// desenha cargoHold
	desenhaCargoHold();

	glDisable(GL_COLOR);
	glEnable(GL_TEXTURE_2D);

}
void cargo::drawUserFeedBack(){

	if (msgUser[0]!=0){

		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		// Altera viewport e projecção
		glViewport(0, height-60, width, 60);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-200, 200, 0, 60);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Blending (transparencias)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		//BackGround
		glColor4f(1.0,1.0,1.0,0.8);
		glBegin(GL_POLYGON);
			glVertex2d(-150,10);
			glVertex2d(-150,50);
			glVertex2d(150,50);
			glVertex2d(150,10);
		glEnd();

		glColor4f(0.0,0.0,0.0,1.0);
		strokeCenterString(msgUser, 0, 30, 0, 0.08); // string, x ,y ,z ,scale

		// ropõe estado
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

	}

}

void cargo::mostraTempoJogo(){
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Altera viewport e projecção
	glViewport(width/2-100, 0, 200, 60);
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

	GLuint horas, minutos,segundos;
	horas = timeElapsed / 3600;
	minutos = (timeElapsed % 3600) / 60;
	segundos = timeElapsed % 60;

	sprintf(tmp, "Tempo decorrido: %dh %dm %ds", horas, minutos, segundos);
	strokeCenterString(tmp, 0, 20, 0, 0.08); // string, x ,y ,z ,scale

	sprintf(tmp, "Hora Actual: %dh %dm %ds", hourStarted + horas, minuteStarted + minutos, segundos);
	strokeCenterString(tmp, 0, 40, 0, 0.08); // string, x ,y ,z ,scale

	// ropõe estado
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}

void cargo::draw(string no) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setVisualArea(false, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);

	//Desenha background
	glMatrixMode(GL_MODELVIEW);
	glBindTexture(GL_TEXTURE_2D, cargoTextures[ID_TEXTURA_CARGO_BACK]);
	glBegin (GL_QUADS);
	glTexCoord2d (0.0,0.0);	glVertex2d (-25,-25);
	glTexCoord2d (1.0,0.0);	glVertex2d (25,-25);
	glTexCoord2d (1.0,1.0);	glVertex2d (25,25);
	glTexCoord2d (0.0,1.0);	glVertex2d (-25,25);
	glEnd ();

	//Desenha Encomendas
	drawCargoBoxs();	

	//Desenha GO button
	drawGOButton();

	//Desenha Mensagens para o Utilizador
	mostraTempoJogo();
	drawUserFeedBack();

	// repõe estado
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}

void cargo::setVisualArea(bool pick, int x, int y) {

	GLint viewport[4];
	int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int winWidth = glutGet(GLUT_WINDOW_WIDTH);

	glViewport(0, 0, winWidth, winHeight);
	//glViewport((winWidth-winHeight)/2, 0, winHeight, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (pick){
		//Go picking
		glGetIntegerv(GL_VIEWPORT, viewport);
		/*  create 1x1 pixel picking region near cursor location      */
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y-1), 
			1.0, 1.0, viewport);
	}

	gluOrtho2D(-30,30,-20,20);

}
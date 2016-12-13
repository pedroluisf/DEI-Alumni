/*
 * MAM
 */

/* include headers */
#include "Tetromino.h"

//construtor
Tetromino::Tetromino(void)
{
	tipo = 1;
	orientacao = 0;
}

//destrutor
Tetromino::~Tetromino(void)
{
}

// métodos
void Tetromino::desenha()
{
	setCubos();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(posX, posY, 0.0);
	for (int i=0; i<4; i++){
		glPushMatrix();
		glTranslatef(cubos[i].getX(), cubos[i].getY(), 0.0);
		cubos[i].setCor(r,g,b);
		cubos[i].desenha();
		glPopMatrix();
	}
	glPopMatrix();
}

void Tetromino::setPos(GLint x, GLint y)
{
	posX = x;
	posY = y;
}

int Tetromino::getX()
{
	return posX;
}

int Tetromino::getY()
{
	return posY;
}

float Tetromino::getR()
{
	return r;
}

float Tetromino::getG()
{
	return g;
}

float Tetromino::getB()
{
	return b;
}

int Tetromino::getTipo()
{
	return tipo;
}

int Tetromino::getOrientacao()
{
	return orientacao;
}

void Tetromino::setCor(GLfloat red, GLfloat green, GLfloat blue)
{
	r = red;
	g = green;
	b = blue;
}

void Tetromino::setTipo(int t)
{
	tipo = t;
}

void Tetromino::setOrientacao(int o)
{
	orientacao = o;
	setCubos();
}

Cubo* Tetromino::getCubo(int c)
{
	return &cubos[c];
}

void Tetromino::setCubos()
{
	switch (tipo)
	{
		// Tipo 1 - I
		case 1:
			switch (orientacao)
			{
				// Orientação - 0 e 180
				case 0: case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(0,-2);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90 e 270
				case 90: case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(-1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-2,0);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;

		// Tipo 2 - O
		case 2:
			cubos[0].setPos(0,0);
			cubos[0].setCor(r,g,b);
			cubos[1].setPos(-1,0);
			cubos[1].setCor(r,g,b);
			cubos[2].setPos(-1,-1);
			cubos[2].setCor(r,g,b);
			cubos[3].setPos(0,-1);
			cubos[3].setCor(r,g,b);
			break;

		// Tipo 3 - T
		case 3:
			switch (orientacao)
			{
				// Orientação - 0
				case 0: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,0);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90
				case 90: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(0,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 180
				case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,0);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 270
				case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(-1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(0,-1);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;

		// Tipo 4 - S
		case 4:
			switch (orientacao)
			{
				// Orientação - 0 e 180
				case 0: case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(1,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90 e 270
				case 90: case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,-1);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;
		// Tipo 5 - Z
		case 5:
			switch (orientacao)
			{
				// Orientação - 0 e 180
				case 0: case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(1,1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(0,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90 e 270
				case 90: case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(-1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(1,-1);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;

		// Tipo 6 - J
		case 6:
			switch (orientacao)
			{
				// Orientação - 0
				case 0: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90
				case 90: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(-1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 180
				case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(1,1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(0,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 270
				case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(-1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(1,-1);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;

		// Tipo 7 - L
		case 7:
			switch (orientacao)
			{
				// Orientação - 0
				case 0: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(1,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 90
				case 90: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(-1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,-1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 180
				case 180: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(0,1);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(0,-1);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(-1,1);
					cubos[3].setCor(r,g,b);
					break;
				// Orientação - 270
				case 270: 
					cubos[0].setPos(0,0);
					cubos[0].setCor(r,g,b);
					cubos[1].setPos(-1,0);
					cubos[1].setCor(r,g,b);
					cubos[2].setPos(1,0);
					cubos[2].setCor(r,g,b);
					cubos[3].setPos(1,1);
					cubos[3].setCor(r,g,b);
					break;
			}
			break;

		// Tipo 8 - .
		case 8:
			cubos[0].setPos(0,0);
			cubos[0].setCor(r,g,b);
			cubos[1].setPos(0,0);
			cubos[1].setCor(r,g,b);
			cubos[2].setPos(0,0);
			cubos[2].setCor(r,g,b);
			cubos[3].setPos(0,0);
			cubos[3].setCor(r,g,b);
			break;

	}

}
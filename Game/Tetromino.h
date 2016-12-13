/*
 * MAM
 */

/* include headers */
#pragma once
#include <GL/glut.h>
#include "Cubo.h"


class Tetromino
{
	public:
		Tetromino(void);
		~Tetromino(void);

		void setTipo(int t);
		int getTipo();
		void setOrientacao(int o);
		int getOrientacao();
		void setPos(GLint x, GLint y);
		int getX();
		int getY();
		void setCor(GLfloat red, GLfloat green, GLfloat blue);
		float getR();
		float getG();
		float getB();
		Cubo* getCubo(int c);
		void desenha();

	private:
		//posicao
		int posX, posY;
		GLfloat r,g,b;
		Cubo cubos[4];
		//Tipo e orientação
		int orientacao;
		int tipo;
		void setCubos();
};
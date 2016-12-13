/*
 * MAM
 */

/* include headers */
#pragma once
#include <GL/glut.h>

class Cubo
{
	public:
		Cubo(void);
		~Cubo(void);

		void desenha();
		void setCor(GLfloat red, GLfloat green, GLfloat blue);
		void setPos(GLint x, GLint y);
		int getX();
		int getY();

	private:
		GLint posX,posY;
		GLfloat r,g,b;
		void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[]);
};
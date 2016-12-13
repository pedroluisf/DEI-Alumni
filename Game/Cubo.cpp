/*
 * MAM
 */

/* include headers */
#include "Cubo.h"

//construtor
Cubo::Cubo(void)
{
	r = 1.0;
	g = 1.0;
	b = 1.0;
}

//destrutor
Cubo::~Cubo(void)
{
}

// métodos
void Cubo::setCor(GLfloat red, GLfloat green, GLfloat blue)
{
	r = red;
	g = green;
	b = blue;
}

void Cubo::desenha()
{
    GLfloat vertices[][3] = {
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5, 0.5}
    };

    desenhaPoligono(vertices[1], vertices[0], vertices[3], vertices[2]);
    desenhaPoligono(vertices[2], vertices[3], vertices[7], vertices[6]);
    desenhaPoligono(vertices[3], vertices[0], vertices[4], vertices[7]);
    desenhaPoligono(vertices[6], vertices[5], vertices[1], vertices[2]);
    desenhaPoligono(vertices[4], vertices[5], vertices[6], vertices[7]);
    desenhaPoligono(vertices[5], vertices[4], vertices[0], vertices[1]);
}

void Cubo::setPos(GLint x, GLint y)
{
	posX = x;
	posY = y;
}

int Cubo::getX()
{
	return posX;
}

int Cubo::getY()
{
	return posY;
}

void Cubo::desenhaPoligono(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[])
{
    glBegin(GL_POLYGON);
    glColor3f(r,g,b);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v4);
    glEnd();
}
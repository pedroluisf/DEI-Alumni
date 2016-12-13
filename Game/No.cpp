#include "No.h"


No::No(void)
{
}

No::No(float x, float y, float z, float raio)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = 1;
	this->g = 1;
	this->b = 1;
	this->raio = raio;
	this->aberturas;
}

No::No(const vector<string>& properties)
{
	int size = properties.size();

	if(size == 10) 
	{
		m_nome = properties[0];
		x = atoi(properties[1].c_str());
		y = atoi(properties[2].c_str());
		z = atoi(properties[3].c_str());

		m_ponto_entrega = properties[4].compare("0") == 0 ? false : true;
		m_nome_ponto_entrega = properties[5];

		raio = atoi(properties[6].c_str());
		r = atoi(properties[7].c_str());
		g =atoi(properties[8].c_str());
		b=atoi(properties[9].c_str());
	}
}


No::~No(void)
{
}

float No::X()
{
	return this->x;
}

void No::X(float val)
{
	this->x = val;
}

float No::Y()
{
	return this->y;
}

void No::Y(float val)
{
	this->y = val;
}

float No::Z()
{
	return this->z;
}

void No::Z(float val)
{
	this->z = val;
}

float No::R()
{
	return this->r;
}

void No::R(float val)
{
	this->r = val;
}

float No::G()
{
	return this->g;
}

void No::G(float val)
{
	this->g = val;
}

float No::B()
{
	return this->b;
}

void No::B(float val)
{
	this->b = val;
}

float No::Raio()
{
	return this->raio;
}

void No::Raio(float val)
{
	this->raio = val;
}

int No::Aberturas()
{
	return this->aberturas.size();
}

bool No::IsPontoEntrega()
{
	return m_ponto_entrega;
}

void No::IsPontoEntrega(bool val)
{
	m_ponto_entrega = val;
}

string No::NomePontoEntrega()
{
	return m_nome_ponto_entrega;
}

void No::NomePontoEntrega(string val)
{
	m_nome_ponto_entrega = val;
}

string No::Nome()
{
	return m_nome;
}

void No::Nome(string val)
{
	m_nome = val;
}
#include "StdAfx.h"
#include "Veiculo.h"

Veiculo::Veiculo(void)
{
}

Veiculo::Veiculo(vector<string> properties)
{
	int size = properties.size();
	double peso = 0, largura = 0, altura = 0, veloc = 0;

	if(size == 6)
	{
		m_matricula = properties[0];
		m_no_inicio = properties[1];

		peso = atof(properties[2].c_str());
		largura = atof(properties[3].c_str());
		altura = atof(properties[4].c_str());
		veloc = atof(properties[5].c_str());

		m_peso = peso > 0 ? peso : 0;
		m_largura = largura > 0 ? largura : 0;
		m_altura = altura > 0 ? altura : 0;
		m_veloc_real = veloc > 0 ? veloc : 0;
		m_veloc = 0;
		m_veloc_max = 0.1;
	}
}


Veiculo::~Veiculo(void)
{
}

string Veiculo::Matricula()
{
	return m_matricula;
}

void Veiculo::Matricula(string val)
{
	m_matricula = val;
}

string Veiculo::NoInicio()
{
	return m_no_inicio;
}

void Veiculo::NoInicio(string val)
{
	m_no_inicio = val;
}

double Veiculo::Peso()
{
	return m_peso;
}

void Veiculo::Peso(double val)
{
	m_peso = val > 0 ? val : 0;;
}

double Veiculo::Largura()
{
	return m_largura;
}

void Veiculo::Largura(double val)
{
	m_peso = val > 0 ? val : 0;;
}

double Veiculo::Altura()
{
	return m_altura;
}

void Veiculo::Altura(double val)
{
	m_altura = val > 0 ? val : 0;
}

double Veiculo::VelocidadeMax()
{
	return m_veloc_max;
}

void Veiculo::VelocidadeMax(double val)
{
	m_veloc_max = val > 0 ? val : 0;
}

double Veiculo::X()
{
	return this->x;
}

void Veiculo::X(double val)
{
	this->x = val;
}

double Veiculo::Y()
{
	return this->y;
}

void Veiculo::Y(double val)
{
	this->y = val;
}

double Veiculo::Z()
{
	return this->z;
}

void Veiculo::Z(double val)
{
	this->z = val;
}

double Veiculo::Pitch()
{
	return this->pitch;
}

void Veiculo::Pitch(double val)
{
	this->pitch = val;
}

double Veiculo::Yaw()
{
	return this->yaw;
}

void Veiculo::Yaw(double val)
{
	this->yaw = val;
}

void Veiculo::IncrementYaw(double val)
{
	this->yaw += val;
}
void Veiculo::IncrementPitch(double val)
{
	this->pitch += val;
}

void Veiculo::DecrementYaw(double val)
{
	this->yaw -= val;
}
void Veiculo::DecrementPitch(double val)
{
	this->pitch -= val;
}

void Veiculo::IncrementX(double val)
{
	this->x += val;
}
void Veiculo::IncrementY(double val)
{
	this->y += val;
}
void Veiculo::IncrementZ(double val)
{
	this->z += val;
}


void Veiculo::DecrementX(double val)
{
	this->x -= val;
}
void Veiculo::DecrementY(double val)
{
	this->y -= val;
}
void Veiculo::DecrementZ(double val)
{
	this->z -= val;
}

double Veiculo::Velocidade()
{
	return this->m_veloc;
}
void Veiculo::Velocidade(double val)
{
	this->m_veloc = val;
}


void Veiculo::Accelerate(double factor)
{
	if(this->m_veloc + factor < m_veloc_max)
	{
		this->m_veloc += factor;
	}
	else
	{
		this->m_veloc = m_veloc_max;
	}
}

void Veiculo::Brake(double factor)
{
	if(this->m_veloc - factor > 0)
	{
		this->m_veloc -= factor;
	}
	else
	{
		this->m_veloc = 0;
	}
}

double Veiculo::VelocidadeReal()
{
	return this->m_veloc_real;
}
void Veiculo::VelocidadeReal(double val)
{
	this->m_veloc_real = val;
}
#include "Arco.h"


Arco::Arco(void)
{
}

Arco::Arco(vector<string> properties)
{
	int size = properties.size();
	float largura = 0, altura = 0, peso = 0;

	if(size == 3 || size == 6)
	{

		this->nome = properties[0];
		this->m_origem = properties[1].c_str();
		this->m_destino = properties[2].c_str();	
		this->m_largura = 1; // por definicao a largura e 1
		this->m_altura = 0;
		this->m_peso = 1; // por definicao o peso e 1

		if(size == 6) 
		{
			largura = (float)atof(properties[3].c_str());
			altura = (float)atof(properties[4].c_str());
			peso = (float)atof(properties[5].c_str());

			this->m_largura = largura > 0 ? largura : 1; // por definicao a largura e 1
			this->m_altura = altura > 0 ? altura : 0;
			this->m_peso = peso > 0 ? peso : 1; // por definicao o peso e 1
		}
	}
}

Arco::Arco(int noi, int nof, float peso, float largura)
{
	this->noi=noi;
	this->nof=nof;
	this->m_peso=peso;
	this->m_largura=largura;
}

Arco::~Arco(void)
{
}

string Arco::Nome()
{
	return nome;
}

void Arco::Nome(string val)
{
	nome = val;
}

int Arco::NoInicial()
{
	return this->noi;
}

void Arco::NoInicial(int val)
{
	this->noi = val;
}

int Arco::NoFinal()
{
	return this->nof;
}

void Arco::NoFinal(int val)
{
	this->nof = val;
}

float Arco::Peso()
{
	return this->m_peso;
}

void Arco::Peso(float val)
{
	this->m_peso = val;
}

float Arco::Largura()
{
	return this->m_largura;
}

void Arco::Largura(float val)
{
	this->m_largura = val;
}

string Arco::Origem()
{
	return m_origem;
}

void Arco::Origem(string val)
{
	m_origem = val;
}

string Arco::Destino()
{
	return m_destino;
}

float Arco::Distancia(const vector<No*>& nos)
{
	No* norg = NULL;
	No* ndest = NULL;
	float difX = 0, difY = 0, difZ = 0;
	float dist = 0;

	norg = nos[this->NoInicial()];
	ndest = nos[this->NoFinal()];

	difX = ndest->X() - norg->X();
	difY = ndest->Y() - norg->Y();
	difZ = ndest->Z() - norg->Z();
	dist = sqrt(pow(difX, 2) + pow(difY, 2) + pow(difZ, 2));

	return dist;
}
#include <vector>
#include "No.h"

using namespace std;

#pragma once

class Arco
{
public:
	Arco(void);
	Arco(vector<string> properties);
	Arco(int noi, int nof, float peso, float largura);
	~Arco(void);

	string Nome();
	void Nome(string val);
	int NoInicial();
	void NoInicial(int val);
	int NoFinal();
	void NoFinal(int val);
	string Origem();
	void Origem(string val);
	string Destino();
	void Destino(string val);
	float Peso();
	void Peso(float val);
	float Largura();
	void Largura(float val);
	float Altura();
	void Altura(float val);
	float Distancia(const vector<No*>& nos);

private:
	string nome, m_origem, m_destino;
	int noi, nof;
	float m_peso, m_largura, m_altura;
};


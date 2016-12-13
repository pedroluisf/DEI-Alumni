#pragma once
#include <string>
#include <vector>

using namespace std;

class Restricao
{
public:
	Restricao(void);
	Restricao(vector<string> properties);
	~Restricao(void);

	string NomeRamo();
	void NomeRamo(string val);
	bool IsInicio();
	void IsInicio(bool val);
	string Tipo();
	void Tipo(string val);
	double Valor();
	void Valor(double val);
	int Hora();
	void Hora(int val);
	int Minuto();
	void Minuto(int val);

private:
	string m_nome_ramo, m_tipo;
	int m_hora, m_minuto;
	bool m_inicio;
	double m_valor;
};
#include "Restricao.h"

Restricao::Restricao(void)
{
}

Restricao::Restricao(vector<string> properties)
{
	int size = properties.size();
	int hora, minuto;

	if(size == 6)
	{
		m_nome_ramo = properties[0];
		m_inicio = properties[1] == "0" ? false : true;
		m_tipo = properties[2];
		m_valor = atof(properties[3].c_str());
		m_hora = 0;
		m_minuto = 0;

		hora = atoi(properties[4].c_str());
		minuto = atoi(properties[5].c_str());

		if(hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60)
		{
			m_hora = hora;
			m_minuto = minuto;
		}
	}
}

Restricao::~Restricao(void)
{
}

string Restricao::NomeRamo()
{
	return m_nome_ramo;
}

void Restricao::NomeRamo(string val)
{
	m_nome_ramo = val;
}

bool Restricao::IsInicio()
{
	return m_inicio;
}

void Restricao::IsInicio(bool val)
{
	m_inicio = val;
}

string Restricao::Tipo()
{
	return m_tipo;
}

void Restricao::Tipo(string val)
{
	m_tipo = val;
}

double Restricao::Valor()
{
	return m_valor;
}

void Restricao::Valor(double val)
{
	m_valor = val;
}

int Restricao::Hora()
{
	return m_hora;
}

void Restricao::Hora(int val)
{
	m_hora = val;
}

int Restricao::Minuto()
{
	return m_minuto;
}

void Restricao::Minuto(int val)
{
	m_minuto = val;
}
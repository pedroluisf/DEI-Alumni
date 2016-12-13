#include "CondicoesAtmosfericas.h"

CondicoesAtmosfericas::CondicoesAtmosfericas(void)
{
}

CondicoesAtmosfericas::CondicoesAtmosfericas(vector<string> properties)
{
	int size = properties.size();

	if(size == 2)
	{
		m_nevoeiro = properties[0] == "0" ? false : true;
		m_chuva = properties[1] == "0" ? false : true;
	}
}

CondicoesAtmosfericas::~CondicoesAtmosfericas(void)
{
}

bool CondicoesAtmosfericas::IsNevoeiro()
{
	return m_nevoeiro;
}

void CondicoesAtmosfericas::IsNevoeiro(bool val)
{
	m_nevoeiro = val;
}

bool CondicoesAtmosfericas::IsChuva()
{
	return m_chuva;
}

void CondicoesAtmosfericas::IsChuva(bool val)
{
	m_chuva = val;
}
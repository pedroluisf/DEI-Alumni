#include "Relogio.h"

Relogio::Relogio(void)
{
}

Relogio::Relogio(vector<string> properties)
{
	int size = properties.size(), hora = 0, minuto = 0;

	if(size == 2)
	{
		hora = atoi(properties[0].c_str());
		minuto = atoi(properties[1].c_str());

		m_hora = hora > 0 ? hora : 0;
		m_minuto = minuto > 0 ? minuto : 0;
	}
}

Relogio::~Relogio(void)
{
}

int Relogio::Hora()
{
	return m_hora;
}

void Relogio::Hora(int val)
{
	m_hora = val;
}

int Relogio::Minuto()
{
	return m_minuto;
}

void Relogio::Minuto(int val)
{
	m_minuto = val;
}
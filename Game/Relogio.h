#pragma once
#include <string>
#include <vector>

using namespace std;

class Relogio
{
public:
	Relogio(void);
	Relogio(vector<string> properties);
	~Relogio(void);

	int Hora();
	void Hora(int val);
	int Minuto();
	void Minuto(int val);

private:
	int m_hora, m_minuto;
};
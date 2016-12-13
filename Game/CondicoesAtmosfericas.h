#pragma once
#include <string>
#include <vector>

using namespace std;

class CondicoesAtmosfericas
{
public:
	CondicoesAtmosfericas(void);
	CondicoesAtmosfericas(vector<string> properties);
	~CondicoesAtmosfericas(void);

	bool IsNevoeiro();
	void IsNevoeiro(bool val);
	bool IsChuva();
	void IsChuva(bool val);

private:
	bool m_nevoeiro, m_chuva;
};
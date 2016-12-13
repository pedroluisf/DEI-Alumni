#pragma once

#include <vector>
#include <string>
#include "soapWsApiSoap12Proxy.h"

using namespace std;

class Website
{
public:
	Website(void);
	~Website(void);

	bool Login(int username,char* password);
	vector<string>* SetResultados(int utilizador, int mapa, int torneio, double pontuacao);
	vector<string>* GetTorneios(int utilizador, int mapa);

private:
	WsApiSoap12Proxy* proxy;
};


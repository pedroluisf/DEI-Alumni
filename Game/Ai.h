#define _WINSOCKAPI_
#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>
#include "Utilities.h"
#include "Encomenda.h"
#include "No.h"
#include "includes\INT386W.HPP"

using namespace std;

class Ai
{
public:
	Ai(void);
	~Ai(void);

	vector<string>* GPS(No* no_actual, vector<Encomenda*>* encomendas_entregues, int minutos_decorridos);
private:
	Int386w* prolog;
	void init();
	void initBaseConhecimento();
	void ActualizarEncomendas(vector<Encomenda*>* encomendas_entregues);
};


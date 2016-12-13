#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include "Jogo.h"
#include "No.h"
#include "Arco.h"
#include "Restricao.h"
#include "Veiculo.h"
#include "Encomenda.h"
#include "Relogio.h"
#include "CondicoesAtmosfericas.h"
#include "Utilities.h"

using namespace std;

class Parser
{
public:
	Parser(void);
	Parser(string mapa, string prolog);
	~Parser(void);

	void Populate(vector<No*>* JogoNos, vector<Arco*>* JogoRamos, vector<Restricao*>* JogoRestricoes, vector<Veiculo*>* JogoVeiculos, vector<Encomenda*>* JogoEncomendas, vector<Relogio*>* JogoRelogios, vector<CondicoesAtmosfericas*>* JogoCondicoes);

private:
	string m_mapa, m_prolog;
	vector<string> &split(const string &s, char delim, vector<string> &elems);
	vector<string> split(const string &s, char delim);
	void OpenGL(const vector<No*>& nos, const vector<Arco*>& ramos);
	void Prolog(const vector<No*>& nos, const vector<Arco*>& ramos, const vector<Restricao*>& restricoes, const vector<Veiculo*>& veiculos, const vector<Encomenda*>& encomendas, const vector<Relogio*>& relogios);

	template <class T>
	void Fill(vector<T*>* original, vector<T*>* copy);

	template <class T>
	vector<T*> parse(ifstream& testFile);
};

#endif
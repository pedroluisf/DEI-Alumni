#include <vector>
#include "Arco.h"
#include "No.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

#define __GRAFO__FILE__ "exemplo.grafo"

using namespace std;

#pragma once

class Grafo
{
public:
	Grafo(void);
	~Grafo(void);

	vector<No*>* Nos();
	vector<Arco*>* Arcos();
	int NumNos();
	int NumArcos();
	int ArcoEntre(int noi, int nof);
	void leGrafo();
	int GetNoByName(string name);

private:
	vector<No*>* nos;
	vector<Arco*>* arcos;
};
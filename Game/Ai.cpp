#include "Ai.h"


Ai::Ai(void)
{
	prolog = new Int386w("", 0, 0, 0);
}


Ai::~Ai(void)
{
}

void Ai::init()
{
	this->prolog->initGoal("consult('exemplo.pl').\n");
	this->prolog->callGoal();
	this->prolog->exitGoal();
}

void Ai::initBaseConhecimento()
{
	this->prolog->initGoal("consult('bc.pl').\n");
	this->prolog->callGoal();
	this->prolog->exitGoal();
}

void Ai::ActualizarEncomendas(vector<Encomenda*>* encomendas_entregues)
{	
	int size = encomendas_entregues->size();

	for(int i = 0; i < size; i++)
	{
		Utilities u;
		
		string nome_encomenda = encomendas_entregues->at(i)->Nome();
		u.ToLowerString(nome_encomenda);

		string s = "retract(encomenda(" + nome_encomenda + ",_,_)).\n";		
		LPSTR goal = const_cast<char*>(s.c_str());

		u.ToLowerString(nome_encomenda);

		this->prolog->initGoal(goal);
		this->prolog->callGoal();
		this->prolog->exitGoal();
	}
}

vector<string>* Ai::GPS(No* no_actual, vector<Encomenda*>* encomendas_entregues, int minutos_decorridos)
{
	Utilities u;
	LPSTR result;
	vector<string>* gps_nos = new vector<string>();

	string nome_no = no_actual->Nome();
	u.ToLowerString(nome_no);

	string str = "inicio_no_tempo_clean_nos(" + nome_no + "," + u.IntToString(minutos_decorridos) + ").\n";
	LPSTR goal = const_cast<char*>(str.c_str());

	init();
	initBaseConhecimento();

	ActualizarEncomendas(encomendas_entregues);
	this->prolog->initGoal(goal);
	result = this->prolog->callGoal();

	vector<string> s = u.split(result, '\n');
	u.Trim(s[2], "[] \f\n\r\t\v");
	s = u.split(s[2], ',');
	this->prolog->exitGoal();

	int size = s.size();
	for(int i=0; i<size; i++)
	{
		gps_nos->push_back(s[i]);
	}

	return gps_nos;
}
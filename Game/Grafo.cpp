#include "Grafo.h"

Grafo::Grafo(void)
{
	this->nos = new vector<No*>();
	this->arcos = new vector<Arco*>();
}


Grafo::~Grafo(void)
{
}

int Grafo::ArcoEntre(int noi, int nof)
{
	int n = arcos->size();

	for(int i = 0; i < n; i++)
	{
		if(arcos->at(i)->NoInicial() == noi && arcos->at(i)->NoFinal() == nof)
		{
			return i;
		}
	}

	return -1;
}

int Grafo::NumArcos()
{
	return arcos->size();
}

int Grafo::NumNos()
{
	return nos->size();
}

vector<No*>* Grafo::Nos()
{
	return this->nos;
}

vector<Arco*>* Grafo::Arcos()
{
	return this->arcos;
}

void Grafo::leGrafo(){
	ifstream myfile;
	int numNos,numArcos;

	myfile.open (__GRAFO__FILE__, ios::in);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para ler" <<endl;
		exit(1);
	}
	myfile >> numNos;
	for(int i=0; i<numNos;i++){
		float x,y,z,raio;
		myfile >> x >> y >> z >> raio;
		No* nolido= new No(x,y,z,raio);
		nos->push_back(nolido);
	}
	myfile >> numArcos ;
	for(int i=0; i<numArcos;i++){
		int noi, nof, peso, largura;
		myfile >> noi >> nof >> peso >> largura ;
		Arco* arcolido=new Arco(noi,nof,peso,largura);
		arcos->push_back(arcolido);
	}
	myfile.close();
	// calcula a largura de cada no = maior largura dos arcos que divergem/convergem desse/nesse no	
	//for(int i=0; i<numNos;i++){
	//	nos[i].largura=0;
	//	for(int j=0; j<numArcos; j++)
	//		if ((arcos[j].noi == i || arcos[j].nof == i) && nos[i].largura < arcos[j].largura)
	//			nos[i].largura = arcos[j].largura*2;
	//}		
}

int Grafo::GetNoByName(string name)
{
	Utilities u;
	string nome = "";
	for(int i = 0; i < nos->size(); i++)
	{
		nome = nos->at(i)->Nome();
		u.ToLowerString(nome);
		if(nome.compare(name) == 0 || nos->at(i)->Nome().compare(name) == 0)
			return i;
	}

	return -1;
}
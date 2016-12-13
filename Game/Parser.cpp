#include "Parser.h"

Parser::Parser(void)
{
	Parser("mapa.mapa", "bc.pl");
}

Parser::Parser(string mapa, string prolog)
{
	m_mapa = mapa;
	m_prolog = prolog;
}

Parser::~Parser(void)
{
}

void Parser::Populate(vector<No*>* JogoNos, vector<Arco*>* JogoRamos, vector<Restricao*>* JogoRestricoes, vector<Veiculo*>* JogoVeiculos, vector<Encomenda*>* JogoEncomendas, vector<Relogio*>* JogoRelogios, vector<CondicoesAtmosfericas*>* JogoCondicoes)
{
	int size_of_mapa = m_mapa.length();
	int size_of_prolog = m_prolog.length();
	vector<No*> nos;
	vector<Arco*> ramos;
	vector<Restricao*> restricoes;
	vector<Veiculo*> veiculos;
	vector<Encomenda*> encomendas;
	vector<Relogio*> relogios;
	vector<CondicoesAtmosfericas*> condicoes;

	if(size_of_mapa > 0 && size_of_prolog > 0)
	{
		ifstream file(m_mapa);

		nos = parse<No>(file);
		ramos = parse<Arco>(file);
		restricoes = parse<Restricao>(file);
		veiculos = parse<Veiculo>(file);
		encomendas = parse<Encomenda>(file);
		relogios = parse<Relogio>(file);
		condicoes = parse<CondicoesAtmosfericas>(file);

		// criar o ficheiro para o opengl
		this->Fill(&nos, JogoNos);
		this->Fill(&ramos, JogoRamos);
		// os arcos nao trazem a posicao dos nos, logo iremos actualizar os arcos apos temos carregado os nos e arcos
		
		for(int i = 0; i < JogoRamos->size(); i++)
		{
			int pos_org = -1, pos_dest = -1;
			for(int j = 0; j < nos.size(); j++)
			{
				if(JogoRamos->at(i)->Origem() == nos[j]->Nome())
				{
					JogoRamos->at(i)->NoInicial(j);
					pos_org = j;
				}

				if(JogoRamos->at(i)->Destino() == nos[j]->Nome())
				{
					JogoRamos->at(i)->NoFinal(j);
					pos_dest = j;
				}

				if(pos_org != -1 && pos_dest != -1)
				{				
					break;
				}
			}
		}
		this->Fill(&restricoes, JogoRestricoes);
		this->Fill(&veiculos, JogoVeiculos);
		this->Fill(&encomendas, JogoEncomendas);
		// as encomendas nao tem cor portanto iremos actualizar com a cor do no de destino
		for(int i = 0; i < encomendas.size(); i++)
		{
			for(int j = 0; j < nos.size(); j++)
			{
				if(nos[j]->Nome().compare(JogoEncomendas->at(i)->No()) == 0)
				{
					JogoEncomendas->at(i)->setRGB(nos[j]->R(), nos[j]->G(), nos[j]->B());
					break;
				}				
			}			
		}

		this->Fill(&relogios, JogoRelogios);
		this->Fill(&condicoes, JogoCondicoes);

		//		OpenGL(nos, ramos);

		// criar o ficheiro para o prolog
		Prolog(nos, ramos, restricoes, veiculos, encomendas, relogios);
	}
	else
	{
		exception* e = new exception("Nome de ficheiros em falta.");
		throw &e;
	}
}

vector<string>& Parser::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> Parser::split(const string &s, char delim) {
	vector<string> elems;
	return split(s, delim, elems);
}

//void Parser::OpenGL(const vector<No*>& nos, const vector<Arco*>& ramos)
//{
//
//	ofstream file(m_opengl);
//	int n_nos = nos.size(), n_ramos = ramos.size();
//
//	file << n_nos << endl;
//	for(int i = 0; i < n_nos; i++)
//	{
//		file << nos[i]->X() << " " << nos[i]->Y() << " " << nos[i]->Z() << endl;
//	}
//
//	file << n_ramos << endl;
//	for(int i = 0; i < n_ramos; i++)
//	{
//
//		for(int j = 0; j < n_nos; j++)
//		{
//			file << ramos[i]->NoInicial() << " " << ramos[i]->NoFinal() << " " << ramos[i]->Peso() << " " << ramos[i]->Largura() << endl;
//			break;
//		}		
//	}
//
//	file.close();
//}

void Parser::OpenGL(const vector<No*>& nos, const vector<Arco*>& ramos)
{

}

void Parser::Prolog(const vector<No*>& nos, const vector<Arco*>& ramos, const vector<Restricao*>& restricoes, const vector<Veiculo*>& veiculos, const vector<Encomenda*>& encomendas, const vector<Relogio*>& relogios)
{
	Utilities u;
	ofstream file(m_prolog);

	// escrever os comentarios iniciais e os dynamic
	file << "%------------------------------------------------------------------------------------" << endl;
	file << "% kick-off p/LAPR5 e ALGAV" << endl;
	file << "%------------------------------------------------------------------------------------" << endl;

	file << ":-dynamic nodo/4,ramo/4." << endl;
	file << ":-dynamic restricao/6,ponto_entrega/2,camiao/5,encomenda/3,relogio/2." << endl;


	file << "%------------------------------------------------------------------------------------" << endl;
	file << "% Caracterização grafo" << endl;
	file << "%------------------------------------------------------------------------------------" << endl;

	file << "%-----------------------------------------------------------" << endl;
	file << "% nodo(IdNodo,PosX,PosY)" << endl;
	file << "%-----------------------------------------------------------" << endl;

	// escrever os nos
	int n_nos = nos.size();
	for(int i = 0; i < n_nos; i++)
	{
		string IdNodo = nos[i]->Nome();
		u.ToLowerString(IdNodo);
		file << "nodo(" << IdNodo << "," << nos[i]->X() << "," << nos[i]->Y() << "," << nos[i]->Z() << ")." << endl;
	}

	file << "%-----------------------------------------------------------" << endl;
	file << "% ramo(IdRamo,IdNodo1,IdNodo2,Distancia)" << endl;
	file << "%-----------------------------------------------------------" << endl;

	// escrever os ramos
	int n_ramos = ramos.size();
	for(int i = 0; i < n_ramos; i++)
	{
		string IdRamo = ramos[i]->Nome();
		string IdNodo1 = nos[ramos[i]->NoInicial()]->Nome();
		string IdNodo2 = nos[ramos[i]->NoFinal()]->Nome();

		u.ToLowerString(IdRamo);
		u.ToLowerString(IdNodo1);
		u.ToLowerString(IdNodo2);

		file << "ramo(" << IdRamo << "," << IdNodo1 << "," << IdNodo2 << "," << ramos[i]->Distancia(nos) << ")." << endl;
	}


	file << "%-----------------------------------------------------------" << endl;
	file << "% restricao(IdRamo,InicoOuFim,Tipo,Valor,Hora,Minuto)" << endl;
	file << "%" << endl;
	file << "% Tipo: velocidade, largura, altura, explosivo, inflamavel, peso, ..." << endl;
	file << "%-----------------------------------------------------------" << endl;

	// escrever as restricoes
	int n_restricoes = restricoes.size();
	for(int i = 0; i < n_restricoes; i++)
	{
		string IdRamo = restricoes[i]->NomeRamo();
		string InicioOuFim = restricoes[i]->IsInicio() ? "inicio" : "fim";
		string Tipo = restricoes[i]->Tipo();

		u.ToLowerString(IdRamo);
		u.ToLowerString(InicioOuFim);
		u.ToLowerString(Tipo);

		file << "restricao(" << IdRamo << "," << InicioOuFim << "," << Tipo;
		if(restricoes[i]->Valor() == -1 || !restricoes[i]->IsInicio())
		{
			file << ",_,";
		}
		else
		{
			file << "," << restricoes[i]->Valor() << ",";
		}
		file << restricoes[i]->Hora() << "," << restricoes[i]->Minuto() << ")." << endl;		
	}

	file << "%------------------------------------------------------------------------" << endl;
	file << "% ponto_entrega(IdPontoEntrega,IdNodo)" << endl;
	file << "% - IdNodo: define qual o nodo do grafo em que se localiza a ponto_entrega" << endl;
	file << "%------------------------------------------------------------------------" << endl;

	// escrever os pontos de entrega
	int n_pes = nos.size();
	for(int i = 0; i < n_pes; i++)
	{
		string IdNodo = nos[i]->Nome();
		string IdPontoEntrega = nos[i]->NomePontoEntrega();
		u.ToLowerString(IdNodo);
		u.ToLowerString(IdPontoEntrega);

		if(nos[i]->IsPontoEntrega())
		{
			file << "ponto_entrega(" << IdPontoEntrega << "," << IdNodo << ")." << endl;
		}		
	}

	file << "%-----------------------------------------------------------------------------" << endl;
	file << "% camiao(Matricula,NoInicio,Peso,Largura, Altura,VelocidadeMax)" << endl;
	file << "%-----------------------------------------------------------------------------" << endl;

	// escrever a info do camiao
	int n_veiculos = veiculos.size();
	for(int i = 0; i < n_veiculos; i++)
	{
		string Matricula = veiculos[i]->Matricula();
		string NoInicio = veiculos[i]->NoInicio();

		u.ToLowerString(Matricula);
		u.ToLowerString(NoInicio);

		file << "camiao('" << Matricula << "', " << NoInicio << "," << veiculos[i]->Peso() << ", " << veiculos[i]->Largura() << ", " << veiculos[i]->Altura() << ", " << veiculos[i]->VelocidadeReal() << ")." << endl;
	}

	file << "%------------------------------------------------------------------------" << endl;
	file << "% encomenda(IdEmissor,Tipo,PontoEntrega)" << endl;
	file << "%------------------------------------------------------------------------" << endl;

	// escrever as encomendas
	int n_encomendas = encomendas.size();
	for(int i = 0; i < n_encomendas; i++)
	{
		string IdEmissor = encomendas[i]->Nome();
		string Tipo = "";
		string PontoEntrega = encomendas[i]->No();

		for(int j = 0; j < n_nos; j++)
		{
			if(nos[j]->Nome() == encomendas[i]->No())
			{
				PontoEntrega = nos[j]->NomePontoEntrega();
			}
		}

		u.ToLowerString(IdEmissor);
		u.ToLowerString(PontoEntrega);

		if(encomendas[i]->IsInflamavel() && encomendas[i]->IsExplosivo())
		{
			Tipo = "[inflamavel,explosivo]";
		} 
		else if(encomendas[i]->IsInflamavel())
		{
			Tipo = "[inflamavel]";
		}
		else if(encomendas[i]->IsExplosivo())
		{
			Tipo = "[explosivo]";
		} 
		else
		{
			Tipo = "[]";
		}

		file << "encomenda(" << IdEmissor << "," << Tipo << "," << PontoEntrega << ")." << endl;
	}

	file << "%------------------------------------------------------------------------" << endl;
	file << "% relogio(Hora,Minuto)" << endl;
	file << "%------------------------------------------------------------------------" << endl;

	// escrever o relogio
	int n_relogios = relogios.size();
	for(int i = 0; i < n_relogios; i++)
	{
		file << "relogio(" << relogios[i]->Hora() << "," << relogios[i]->Minuto() << ")." << endl;
	}

	file.close();
}

template <class T>
vector<T*> Parser::parse(ifstream& testFile)
{
	Utilities u;
	string line;
	vector<T*> v;
	vector<string> strings;

	int n = -1;

	if(testFile.good())
	{
		getline(testFile, line);
		u.Trim(line);
		n = atoi(line.c_str());

		int i = 0;
		while(i < n)
		{
			getline(testFile, line);
			if(line.length() > 0)
			{
				strings = split(line, ',');
				u.TrimVector(strings);
				T* r = new T(strings);
				v.push_back(r);

				i++;
			}
		}		
	}

	return v;
}

template <class T>
void Parser::Fill(vector<T*>* original, vector<T*>* copy)
{
	int size = original->size();
	for(int i = 0; i < size; i++)
	{
		copy->push_back(original->at(i));
	}
}

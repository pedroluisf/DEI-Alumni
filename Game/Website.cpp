#include "Website.h"


Website::Website(void)
{
	proxy = new WsApiSoap12Proxy("http://uvm101.dei.isep.ipp.pt/WS/WsAPI.php");
}


Website::~Website(void)
{
}

bool Website::Login(int username,char* password)
{
	int errCode = 0;
	_ns1__login* login = new _ns1__login();
	_ns1__loginResponse* lgResponse = new _ns1__loginResponse();

	// preenchimento de parametros de entrada do metodo login(int utilizador, string md5password)
	login->utilizador = username;
	login->md5password = password;
	// chama o metodo login
	errCode = proxy->login(login, lgResponse);

	//cout << "Servico respondeu com codigo: " << errCode << endl;
	if( errCode == 0)
	{
		// como é devolvido um tipo simples (neste caso um int) mostramos directamente
		//cout << "O id do jogador e: " << lgResponse->loginResult << endl;
		return lgResponse->loginResult > 0;
	}
	else
	{
		proxy->soap_stream_fault(cout);
		return false;
	}

}

vector<string>* Website::SetResultados(int utilizador, int mapa, int torneio, double pontuacao)
{
	vector<string>* v = new vector<string>();
	int errCode = 0;
	_ns1__setResultados* setResultados = new _ns1__setResultados();
	_ns1__setResultadosResponse* srResponse = new _ns1__setResultadosResponse();
	ns1__ArrayOfClassificacao* arrayOfClassificacao = new ns1__ArrayOfClassificacao();
	ns1__Classificacao* classificacao = new ns1__Classificacao();

	// preenchimento parametros de entrada do metodo getTorneio(int utilizador, int mapa)
	setResultados->utilizador = utilizador;
	setResultados->mapa = mapa;
	setResultados->torneio = torneio;
	setResultados->pontuacao = pontuacao;
	errCode = proxy->setResultados(setResultados, srResponse);

	//cout << "Servico respondeu com codigo: " << errCode << endl;
	if( errCode == 0)
	{
		// neste caso e devolvido um tipo complexo (array de classe Classificacao)
		arrayOfClassificacao = srResponse->setResultadosResult;

		for(int i = 0; i < arrayOfClassificacao->__sizeClassificacao; i++)
		{
			// dentro do objecto arrayOfClassificacao podemos encontrar os torneios individuais dentro da propriedade Torneio
			// acessível por indices numericos arrayOfClassificacao->Classificacao[i];
			classificacao = arrayOfClassificacao->Classificacao[i];
			string nome = classificacao->Nome;
			float tmp = classificacao->Pontuacao;
			char score[20];
			sprintf(score, "%8.2f", tmp);
			string s = classificacao->Posicao + " " + nome + " " + score;
			v->push_back(s);
		}

	}
	else
	{
		proxy->soap_stream_fault(cout);
	}

	return v;

}

vector<string>* Website::GetTorneios(int utilizador, int mapa)
{
	int errCode = 0;
	vector<string>* nomesTorneios = new vector<string>();
	_ns1__getTorneio* getTorneio = new _ns1__getTorneio();
	_ns1__getTorneioResponse* gtResponse = new _ns1__getTorneioResponse();
	ns1__ArrayOfTorneio* arrayOfTorneio = new ns1__ArrayOfTorneio();
	ns1__Torneio* torneio = new ns1__Torneio();

	// preenchimento parametros de entrada do metodo getTorneio(int utilizador, int mapa)
	getTorneio->utilizador = utilizador;
	getTorneio->mapa = mapa;
	errCode = proxy->getTorneio(getTorneio, gtResponse);

	if( errCode == 0)
	{
		// neste caso e devolvido um tipo complexo (array de classe Torneio)
		arrayOfTorneio = gtResponse->getTorneioResult;

		for(int i = 0; i < arrayOfTorneio->__sizeTorneio; i++)
		{
			// dentro do objecto arrayOfTorneio podemos encontrar os torneios individuais dentro da propriedade Torneio
			// acessível por indices numericos arrayOfTorneio->Torneio[i]
			torneio = arrayOfTorneio->Torneio[i];
			nomesTorneios->push_back(torneio->Nome);
		}

	}
	else
	{
		proxy->soap_stream_fault(cout);
	}

	return nomesTorneios;
}
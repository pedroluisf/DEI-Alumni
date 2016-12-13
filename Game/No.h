#include <vector>

using namespace std;

#pragma once
class No
{
public:
	No(void);
	No(const vector<string>& properties);
	No(float x, float y, float z, float raio);
	~No(void);

	string Nome();
	void Nome(string val);
	string NomePontoEntrega();
	void NomePontoEntrega(string val);
	float X();
	void X(float val);
	float Y();
	void Y(float val);
	float Z();
	void Z(float val);
	float R();
	void R(float val);
	float G();
	void G(float val);
	float B();
	void B(float val);
	float Raio();
	void Raio(float val);
	bool IsPontoEntrega();
	void IsPontoEntrega(bool val);
	int Aberturas(void);
	int Conexoes(void);
	void AddConexao(int no);
	void AddAbertura(float angulo);

private:
	float x, y, z, raio, r, g, b;
	string m_nome, m_nome_ponto_entrega;
	bool m_ponto_entrega;
	vector<float> aberturas;
	vector<int> conexoes;
};


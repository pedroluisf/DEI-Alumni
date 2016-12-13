#pragma once
#include <string>
#include <vector>

using namespace std;

class Veiculo
{
public:
	Veiculo(void);
	Veiculo(vector<string> properties);
	~Veiculo(void);

	string Matricula();
	void Matricula(string val);
	string NoInicio();
	void NoInicio(string val);
	double Peso();
	void Peso(double val);
	double Largura();
	void Largura(double val);
	double Altura();
	void Altura(double val);
	double VelocidadeMax();
	void VelocidadeMax(double val);
	double X();
	void X(double val);
	double Y();
	void Y(double val);
	double Z();
	void Z(double val);
	double Pitch();
	void Pitch(double val);
	double Yaw();
	void Yaw(double val);
	double Velocidade();
	void Velocidade(double val);
	double VelocidadeReal();
	void VelocidadeReal(double val);

	void IncrementYaw(double val);
	void IncrementPitch(double val);
	void DecrementYaw(double val);
	void DecrementPitch(double val);
	void IncrementX(double val);
	void IncrementY(double val);
	void IncrementZ(double val);
	void DecrementX(double val);
	void DecrementY(double val);
	void DecrementZ(double val);

	void Accelerate(double factor);
	void Brake(double factor);

private:
	double x, y, z;
	double pitch, yaw;
	string m_matricula, m_no_inicio;
	double m_peso, m_largura, m_altura, m_veloc, m_veloc_max, m_veloc_real;
};
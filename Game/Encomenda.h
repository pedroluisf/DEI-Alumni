#pragma once
#include <string>
#include <vector>
#include "Tetromino.h"

using namespace std;

class Encomenda
{
public:
	Encomenda(void);
	Encomenda(vector<string> properties);
	~Encomenda(void);

	string Nome();
	void Nome(string val);
	string No();
	void No(string val);
	bool IsExplosivo();
	void IsExplosivo(bool val);
	bool IsInflamavel();
	void IsInflamavel(bool val);

	bool isLoaded();
	void isLoaded(bool val);
	void setForma(int val);
	void setOrientacao(int val);
	float R();
	void R(float val);
	float G();
	void G(float val);
	float B();
	void B(float val);
	void setRGB(float val_r, float val_g, float val_b);
	void setPos(int val_x, int val_y);
	void desenha();
	Tetromino* getTetromino();
	void setId(int val);
	int getId();
	void setTipoObj(int val);
	int getTipoObj();

private:
	int m_id;
	string m_nome, m_no;
	bool m_explosivo, m_inflamavel, m_loaded;
	Tetromino m_tetromino;
	// tipo de objecto na matriz
	int m_obj;
};
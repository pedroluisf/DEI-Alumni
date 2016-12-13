#include "Encomenda.h"

Encomenda::Encomenda(void)
{
	m_loaded = false;
	m_inflamavel = false;
	m_explosivo = false;
	m_obj = 1;
	m_tetromino.setOrientacao(0);
}

Encomenda::Encomenda(vector<string> properties)
{
	int size = properties.size();

	if(size == 5)
	{

		m_nome = properties[0];
		m_no = properties[1];
		m_explosivo = properties[2] == "0" ? false : true;
		m_inflamavel = properties[3] == "0" ? false : true;

		string aux = properties[4];
		int m_forma = atoi(aux.c_str());
		setForma(m_forma);
	}
	
	// do modo
	m_loaded = false;
	if (m_inflamavel)
		m_obj = 5;
	else
		m_obj = 1;
	m_tetromino.setOrientacao(0);
}

Encomenda::~Encomenda(void)
{
}

string Encomenda::Nome()
{
	return m_nome;
}

void Encomenda::Nome(string val)
{
	m_nome = val;
}

string Encomenda::No()
{
	return m_no;
}

void Encomenda::No(string val)
{
	m_no = val;
}

void Encomenda::setId(int val)
{
	m_id = val;
}

int Encomenda::getId()
{
	return m_id;
}

void Encomenda::setTipoObj(int val)
{
	m_obj = val;
}

int Encomenda::getTipoObj()
{
	return m_obj;
}

bool Encomenda::IsExplosivo()
{
	return m_explosivo;
}

void Encomenda::IsExplosivo(bool val)
{
	m_explosivo = val;
}

bool Encomenda::IsInflamavel()
{
	return m_inflamavel;
}

bool Encomenda::isLoaded()
{
	return m_loaded;
}

void Encomenda::isLoaded(bool val)
{
	m_loaded = val;
}

void Encomenda::IsInflamavel(bool val)
{
	m_inflamavel = val;
	// tipo de objecto
	if (m_inflamavel)
		m_obj = 5;
	else
		m_obj = 1;
}

void Encomenda::setForma(int val)
{
	m_tetromino.setTipo(val);
}

void Encomenda::setOrientacao(int val)
{
	m_tetromino.setOrientacao(val);
}

float Encomenda::R()
{
	return m_tetromino.getR();
}

float Encomenda::G()
{
	return m_tetromino.getG();
}

float Encomenda::B()
{
	return m_tetromino.getB();
}

void Encomenda::setRGB(float val_r, float val_g, float val_b)
{
	m_tetromino.setCor(val_r,val_g,val_b);
}

void Encomenda::setPos(int val_x, int val_y)
{
	m_tetromino.setPos(val_x, val_y);
}

void Encomenda::desenha()
{
	m_tetromino.desenha();
}

Tetromino* Encomenda::getTetromino()
{
	return &m_tetromino;
}
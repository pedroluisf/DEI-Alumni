#pragma once

#ifndef JOGO_H
#define JOGO_H
#define MODO_MENU 1
#define MODO_ANIMACAO 2
#define MODO_CARGA 3
#define MODO_DESTINO 4

#define DISTANCIA_PARAGEM_NO_FRACAO 0.9
#define DISTANCIA_RODAGEM_NO_FRACAO 0.6

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Encomenda.h"
#include "No.h"
#include "Parser.h"
#include "Grafo.h"
#include "Relogio.h"
#include "Restricao.h"
#include "Veiculo.h"
#include "Ai.h"
#include "CondicoesAtmosfericas.h"

using namespace std;

class Jogo
{
public:
	Jogo();
	~Jogo(void);

	vector<Encomenda*>* GetEncomendas();
	vector<Encomenda*>* GetEncomendasEntregues();
	vector<Relogio*>* GetRelogios();
	vector<Restricao*>* GetRestricoes();
	vector<Veiculo*>* GetVeiculos();	
	vector<CondicoesAtmosfericas*>* GetCondicoes();
	vector<No*>* GetPercurso();
	vector<string>* GPS();
	void GPS(vector<string>* val);
	void setPercursoByGPS();
	Ai* ai;
	No* NoAnterior();
	void NoAnterior(No* val);
	No* NoActual();
	void NoActual(No* val);
	No* NoSeguinte();
	void NoSeguinte(No* val);
	string NomeMapa();
	int ModoJogo();
	void ModoJogo(int val);
	bool IsActivo();
	void Activar();
	void Desactivar();
	int Temporizador();	
	Grafo* GetGrafo();
	void Load(string mapa);
	int Hora();
	int Minuto();
	void Hora(int val);
	void Minuto(int val);
	void Temporizador(int val);
	void IncrementTemporizador(int val);

private:
	vector<Encomenda*>* m_Encomendas;
	vector<Encomenda*>* m_EncomendasEntregues;
	vector<Relogio*>* m_Relogios;
	vector<Restricao*>* m_Restricoes;
	vector<Veiculo*>* m_Veiculos;
	vector<CondicoesAtmosfericas*>* m_Condicoes;
	vector<No*>* percurso;
	vector<string>* gps;

	No* no_ant;
	No* no_act;
	No* no_seg;

	string m_NomeMapa;
	int m_ModoJogo;
	bool m_Activo;
	int m_Temporizador;
	int m_Hora;
	int m_Minuto;
	Grafo* m_grafo;

	void InitVeiculo();
};

#endif
#include "Jogo.h"
#define M_PI       3.14159265358979323846
#define graus(X) (double)((X)*180./M_PI)
#define rad(X)   (double)((X)*M_PI/180.)
#define round(X) (int) (X+0.5)
#define darco(X,R) (double) X*R //X em radianos

double getAnguloRotacaoPlanoJ(float xi, float yi,float xf, float yf){
	double length=sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
	double angulo_rotacao=asin((yf-yi)/length);
	if ( (xf-xi) < 0 && (yf-yi) > 0 ) 
		angulo_rotacao=acos((yf-yi)/length);
	else if ( (xf-xi) < 0 && (yf-yi) < 0 ) 
		angulo_rotacao=M_PI/2. + asin((yi-yf)/length);
	else if ( (xf-xi) > 0 && (yf-yi) < 0 ) 
		angulo_rotacao=M_PI + asin((xf-xi)/length);
	else if ( (xf-xi) > 0 && (yf-yi) > 0 ) 
		angulo_rotacao=3.*M_PI/2. + acos((xf-xi)/length);
	else if (xf-xi == 0)
		if (yf-yi>=0) angulo_rotacao=0;
		else angulo_rotacao=M_PI;
	else if (yf-yi == 0)
		if (xf-xi >= 0) angulo_rotacao=3.*M_PI/2.;
		else angulo_rotacao=M_PI/2.;

		return angulo_rotacao;
}

Jogo::Jogo()
{
	this->m_Encomendas = new vector<Encomenda*>();
	this->m_EncomendasEntregues = new vector<Encomenda*>();
	this->m_Restricoes = new vector<Restricao*>();
	this->m_Veiculos = new vector<Veiculo*>();
	this->m_Relogios = new vector<Relogio*>();
	this->m_Condicoes = new vector<CondicoesAtmosfericas*>();
	this->m_grafo = new Grafo();
	this->percurso = new vector<No*>();
	this->gps = new vector<string>();
	this->ai = new Ai();

	this->m_Temporizador = 0;
	this->m_ModoJogo = MODO_MENU;
	this->m_Activo = false;
}

Jogo::~Jogo(void)
{
}

vector<Encomenda*>* Jogo::GetEncomendas()
{
	return this->m_Encomendas;
}

vector<Encomenda*>* Jogo::GetEncomendasEntregues()
{
	return this->m_EncomendasEntregues;
}

No* Jogo::NoActual()
{
	return this->no_act;
}
string Jogo::NomeMapa()
{
	return this->m_NomeMapa;
}
int Jogo::ModoJogo()
{
	return this->m_ModoJogo;
}
void Jogo::ModoJogo(int val)
{
	this->m_ModoJogo = val;
}
bool Jogo::IsActivo()
{
	return this->m_Activo;
}
int Jogo::Temporizador()
{
	return this->m_Temporizador;
}

void Jogo::Temporizador(int val)
{
	this->m_Temporizador = val;
}

vector<Restricao*>* Jogo::GetRestricoes()
{
	return this->m_Restricoes;
}

vector<Veiculo*>* Jogo::GetVeiculos()
{
	return this->m_Veiculos;
}

vector<CondicoesAtmosfericas*>* Jogo::GetCondicoes()
{
	return this->m_Condicoes;
}

vector<Relogio*>* Jogo::GetRelogios()
{
	return this->m_Relogios;
}

Grafo* Jogo::GetGrafo()
{
	return this->m_grafo;
}

void Jogo::NoActual(No* val)
{
	this->no_act = val;
}

No* Jogo::NoSeguinte()
{
	return this->no_seg;
}

void Jogo::NoSeguinte(No* val)
{
	this->no_seg = val;
}

vector<No*>* Jogo::GetPercurso()
{
	return this->percurso;
}

void Jogo::Activar()
{
	this->m_Activo = true;
}

void Jogo::Desactivar()
{
	this->m_Activo = true;
}

void Jogo::Load(string mapa)
{
	Parser* p = new Parser(mapa, "bc.pl");
	p->Populate(this->GetGrafo()->Nos(), this->GetGrafo()->Arcos(), this->GetRestricoes(), this->GetVeiculos(), this->GetEncomendas(), this->GetRelogios(), this->GetCondicoes());

	string noi = this->GetVeiculos()->at(0)->NoInicio();
	int pos = this->GetGrafo()->GetNoByName(noi);
	No* nact = this->GetGrafo()->Nos()->at(pos);
	No* nant;
	if (pos == 0) nant = this->GetGrafo()->Nos()->at(1);
	else nant = this->GetGrafo()->Nos()->at(0);
	this->no_act = nact;
	this->no_seg = NULL;
	this->no_ant = nant;
	this->m_NomeMapa = mapa;
	this->m_Activo=true;
	this->m_ModoJogo = MODO_DESTINO;
	this->m_Hora=this->m_Relogios->at(0)->Hora();
	this->m_Minuto=this->m_Relogios->at(0)->Minuto();


	InitVeiculo();
}

void Jogo::InitVeiculo()
{
	//this->GetPercurso()->push_back(this->GetGrafo()->Nos()->at(1));
	//this->GetPercurso()->push_back(this->GetGrafo()->Nos()->at(2));
	//this->GetPercurso()->push_back(this->GetGrafo()->Nos()->at(5));
	//this->GetPercurso()->push_back(this->GetGrafo()->Nos()->at(6));
	//this->GetPercurso()->push_back(this->GetGrafo()->Nos()->at(3));
	//this->NoSeguinte(this->GetPercurso()->at(0));
	//this->GetPercurso()->erase(this->GetPercurso()->begin());

	//Esta parte é necessária para por o camiao no inicio do primeiro no do jogo.
	No* nant = this->NoAnterior();
	No* nact = this->NoActual();
	Veiculo* v = this->GetVeiculos()->at(0);
	double angxy=getAnguloRotacaoPlanoJ(nact->X(),nact->Y(),nant->X(),nant->Y())+M_PI/2;
	v->X(nact->X()+nact->Raio()*DISTANCIA_PARAGEM_NO_FRACAO*0.99*cos(angxy));
	v->Y(nact->Y()+nact->Raio()*DISTANCIA_PARAGEM_NO_FRACAO*0.99*sin(angxy));
	v->Z(nact->Z());
	v->Pitch(0);
	v->Yaw(graus(angxy+M_PI/2));
	v->Accelerate(0.1);
}

void Jogo::setPercursoByGPS(){
	No* noiGPS;
	//No seguinte ou actual no inicio de jogo
	if (no_seg==NULL){
		noiGPS = no_act; 
	} else {
		noiGPS = no_seg;
	}

	vector<string>* percursos = ai->GPS(noiGPS, m_EncomendasEntregues, m_Temporizador / 60);

	string tmp = percursos->at(0);
	if (percursos->size()==0 || tmp.c_str()[0]=='!'){ 
		cout << "GPS não retornou nenhum nó";
	}
	else{
		percurso->clear();
		for (int i=0; i< percursos->size(); i++){
			string id = percursos->at(i);
			int pos = m_grafo->GetNoByName(id);
			No* n = m_grafo->Nos()->at(pos);
			percurso->push_back(n);
		}
	}

}

int Jogo::Hora()
{
	return this->m_Hora;
}

int Jogo::Minuto()
{
	return this->m_Minuto;
}

void Jogo::IncrementTemporizador(int val)
{
	this->m_Temporizador += val;
}

No* Jogo::NoAnterior()
{
	return this->no_ant;
}

void Jogo::NoAnterior(No* val)
{
	this->no_ant = val;
}

vector<string>* Jogo::GPS()
{
	return this->gps;
}
void Jogo::GPS(vector<string>* val)
{
	this->gps = val;
}

void Jogo::Hora(int val)
{
	this->m_Hora = val;
}

void Jogo::Minuto(int val)
{
	this->m_Minuto = val;
}
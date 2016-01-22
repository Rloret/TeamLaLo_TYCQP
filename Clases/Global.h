#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "cocos2d.h"
#include "Arma.h"
#include "ObjetoEscenario.h"
#include "Nivel.h"
#include "ZerrinClass.h"
#include "KatahiClass.h"
//Singleton

class Global 
{
public:
	static Global* getInstance();
	cocos2d::Scene* nivel;
	cocos2d::Layer* layerObjects;
	cocos2d::Scene* levelsMenuScene;
	//cocos2d::Scene* tienda;

	std::vector<Arma*> armasTotales;
	std::vector<Arma*> armasArsenal;
	std::vector<Arma*> ArmasNivel;

	std::vector<std::string> BateriaFrasesKatahi;
	std::vector<std::string> BateriaFrasesZerrin;

	ZerrinClass* zerrin;
	KatahiClass* katahi;

	cocos2d::TTFConfig letraPersonajes;

	std::vector<ObjetoEscenario*> ObjetosTotalesEscenarios;
	std::vector<std::pair<int, int>> PosicionObjetos;
	std::vector<int> nivelesJugados;


	cocos2d::Size visibleSize;

	Arma* armaAComprar;

	void añadeArmasANivel(Arma* a);
	void vaciaArmasNivel();
	void quitaArmaDeNivel(Arma* a);
	void colocaObjetos(int i_objetos, int u_objetos);
	void colocaFondo(std::vector<std::string> fondos);
	void abreEstanteria();
	void recolocaArmasNivel();

	void CreaFrases();
	
	bool juegoEnCurso;

	int ContadorArmas=0;
	float currentTime =0.0;
	float ellapsedTime=999.0;
	int currentSongID;

	int inicioObj;
	int finalObj;
	int RecompensaOro;
	int RecompensaMechones;
	int nivelActualID;

	//std::vector<Vec2*> ObjetosTotalesEscenarioPosiciones;
	


private:
	Global();
	~Global();
	void creaArmas();
	void creaObjetosEscenario();
	//void creaCamara();
	//cocos2d::Action* Camara;


};

#endif //ARMA


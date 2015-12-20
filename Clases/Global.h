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
	cocos2d::Scene* levelsMenuScene;
	//cocos2d::Scene* tienda;

	std::vector<Arma*> armasTotales;
	std::vector<Arma*> armasArsenal;
	std::vector<Arma*> ArmasNivel;

	ZerrinClass* zerrin;
	KatahiClass* katahi;

	std::vector<ObjetoEscenario*> ObjetosTotalesEscenarios;
	cocos2d::Size visibleSize;

	Arma* armaAComprar;

	void añadeArmasANivel(Arma* a);
	void vaciaArmasNivel();
	void quitaArmaDeNivel(Arma* a);
	void colocaObjetos(int i_objetos, int u_objetos);
	void abreEstanteria();
	void recolocaArmasNivel();
	
	bool juegoEnCurso;

	int ContadorArmas=0;
	float currentTime =0.0;
	float ellapsedTime=0.0;

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


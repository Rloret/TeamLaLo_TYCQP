#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "cocos2d.h"
#include "Arma.h"
#include "ObjetoEscenario.h"
#include "ZerrinClass.h"
#include "KatahiClass.h"
//Singleton

class Global 
{
public:
	static Global* getInstance();
	cocos2d::Scene* nivel;
	cocos2d::Scene* levelsMenuScene;
	cocos2d::Scene* tienda;

	std::vector<Arma*> armasTotales;
	std::vector<Arma*> armasArsenal;
	std::vector<Arma*> ArmasNivel;

	ZerrinClass* zerrin;
	KatahiClass* katahi;

	std::vector<ObjetoEscenario*> ObjetosTotalesEscenarios;
	cocos2d::Size visibleSize;

	void añadeArmasANivel(Arma* a);
	void vaciaArmasNivel();
	void quitaArmaDeNivel(Arma* a);
	bool juegoEnCurso;

	Arma* armaAComprar;

	//std::vector<Vec2*> ObjetosTotalesEscenarioPosiciones;
	


private:
	Global();
	~Global();
	void creaArmas();
	void creaObjetosEscenario();
	


};

#endif //ARMA


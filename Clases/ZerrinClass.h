
#ifndef __ZERRIN_CLASS_H__
#define __ZERRIN_CLASS_H__
#include "cocos2d.h"
#include "Arma.h"
#include "ObjetoEscenario.h"

//Singleton

class ZerrinClass :public cocos2d::Sprite
{
public:

	ZerrinClass();
	static ZerrinClass* create();

	void setVelocidad(int v);
	void setVida(int v);
	int getVelocidad();
	int getVida();
	bool haLlegado = false;
	bool corriendo = false;
	void setCorrer(bool c);

	cocos2d::Sprite aspecto;

private:
	int velocidad;
	int vida;
	void update(float dt);
	void correr();

	//Size visibleSize;
};

#endif
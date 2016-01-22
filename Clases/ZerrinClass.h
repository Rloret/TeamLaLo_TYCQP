
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
	~ZerrinClass();
	static ZerrinClass* create();

	//Sprite* ObjetivoCamara;

	void setVelocidad(int v);
	void setVida(int v);
	int getVelocidad();
	int getVida();
	float posicionAnterior = 0.0;

	bool haLlegado = false;
	bool corriendo = false;
	void setCorrer(bool c);
	void muestraDa�o(int da�o);
	void setCurrentAnimation(cocos2d::Node* anim);
	void accionColision(bool atras,int objeto,int tipoObjeto);
	cocos2d::Vector<cocos2d::SpriteFrame *> getAnimation(const char *format, int count);
	cocos2d::Sprite aspecto;

	cocos2d::Vector<cocos2d::String*> SonidosZerrin;

	void PlayZerrinSound(int inicio,int final);

	enum ZERRINFSM
	{
		IDLE,
		ENTRANDO,
		SALIENDO,
		HA_LLEGADO,
		CORRIENDO,
		GOLPEADO_ATRAS,
		GOLPEADO_ALANTE,
		SUELO,
	};
	void setState(ZERRINFSM estado);
	ZERRINFSM getEstado();

private:
	float velocidad;
	int vida;
	void update(float dt);
	void correr();
	cocos2d::Sprite* currentAnimation=nullptr;
	ZERRINFSM estadoz;

	//Size visibleSize;
};

#endif
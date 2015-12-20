#ifndef __ARMA_H__
#define __ARMA_H__
#include "cocos2d.h"



class Arma : public cocos2d::Sprite
{
public:
	Arma(int da�o, std::string nombre, int tipo,int precio,int mechones);
	~Arma();
	static Arma* create(cocos2d::Texture2D* t, int da�o, std::string nombre, int tipo,int precio,int mechones);

	//void initOptions(cocos2d::Rect area);

	void AddListener();
	void EnableListener(bool b);
	void EnableSwallow(bool b);
	void arrastraArma(cocos2d::Vec2 vector);

	void setPointY(int y);
	void setDesdeTienda(bool estado);
	void setArma(Arma* arma);

	void accion(Arma* a);

	void intervalo(int signo);
	Arma* clon;
	Arma* getArma();
	Arma* ClonarArma(Arma*a);

	int getTipo();
	std::string getNombre();
	int getDa�o();
	int getPrecio();
	int getMechones();
	int parpadeo=1;

	bool getDesdeTienda();
	bool enNivel = false; 
	bool colocada = false;
	bool childEnTienda = false; //esta activa en tienda
	bool childEnNivel = false; 
	bool arrastrando = false;

	

private:
	bool desdeTienda;
	int da�o;
	int toqueY;
	int precio;
	int mechones;
    
	cocos2d::EventListenerTouchOneByOne* listener;

	int tipo; // 0- las que caen   1-punzantes

	std::string nombre;
	
	Arma* esteArma;

	void accionTouch();

	//void caer(float dt);
};

#endif //ARMA


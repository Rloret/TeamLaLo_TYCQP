#ifndef __ARMA_H__
#define __ARMA_H__
#include "cocos2d.h"



class Arma : public cocos2d::Sprite
{
public:
	Arma(int daño, std::string nombre, int tipo,int precio);
	~Arma();
	static Arma* create(cocos2d::Texture2D* t, int daño, std::string nombre, int tipo,int precio);

	//void initOptions(cocos2d::Rect area);

	void AddListener();
	void EnableListener(bool b);
	void EnableSwallow(bool b);
	void arrastraArma(cocos2d::Vec2 vector);

	void setPointY(int y);
	void setDesdeTienda(bool estado);
	void setArma(Arma* arma);

	void accion(Arma* a);

	Arma* clon;
	Arma* getArma();
	Arma* ClonarArma(Arma*a);

	int getTipo();
	std::string getNombre();
	int getDaño();
	int getPrecio();
	bool getDesdeTienda();
	bool enNivel = false; 
	bool colocada = false;
	bool childEnTienda = false; //esta activa en tienda
	bool childEnNivel = false; 
	
private:
	bool desdeTienda;
	int daño;
	int toqueY;
	int precio;
    
	cocos2d::EventListenerTouchOneByOne* listener;

	int tipo; // 0- las que caen   1-punzantes

	std::string nombre;
	
	Arma* esteArma;

	void accionTouch();

	void caer(float dt);
};

#endif //ARMA


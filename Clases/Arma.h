#ifndef __ARMA_H__
#define __ARMA_H__
#include "cocos2d.h"



class Arma : public cocos2d::Sprite
{
public:
	Arma(int daño, std::string nombre, int tipo,int precio,int mechones);
	~Arma();
	static Arma* create(cocos2d::Texture2D* t, int daño, std::string nombre, int tipo,int precio,int mechones);

	//void initOptions(cocos2d::Rect area);

	void AddListener();
	void EnableListener(bool b);
	void EnableSwallow(bool b);
	void arrastraArma(cocos2d::Vec2 vector);

	void setPointY(int y);
	void setDesdeTienda(bool estado);
	//void setArma(Arma* arma);

	void accion(Arma* a, cocos2d::Touch* touch);
	void accionColision(int tipoDelArma);
	void intervalo(int tipo);
	void reactivaBitmasks();
	void compruebaSitio(Arma* a);

	Arma* clon;
	Arma* getArma();
	Arma* ClonarArma(Arma*a);

	int getTipo();
	int getDaño();
	int getPrecio();
	int getMechones();
	int parpadeo=1;

	std::string getNombre();

	bool getDesdeTienda();
	bool enNivel = false; 
	bool colocada = false;
	bool childEnTienda = false; //esta activa en tienda
	bool childEnNivel = false; 
	bool arrastrando = false;

	cocos2d::Sprite* pivote;
	cocos2d::PhysicsJointDistance* jointDemolicion;
	Arma* bolaDemolicion;

	

private:
	bool desdeTienda;
	int daño;
	int toqueY;
	int precio;
	int mechones;
    
	cocos2d::EventListenerTouchOneByOne* listener;

	int tipo; 

	std::string nombre;
	
	//Arma* esteArma;

	void accionTouch(cocos2d::Touch* touch);


	//void caer(float dt);
};

#endif //ARMA


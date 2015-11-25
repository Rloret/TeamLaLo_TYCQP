#ifndef __ARMA_H__
#define __ARMA_H__
#include "cocos2d.h"



class Arma : public cocos2d::Sprite
{
public:
	Arma(int da�o, std::string nombre, std::string tipo,int precio);
	~Arma();
	static Arma* create(cocos2d::Texture2D* t, int da�o, std::string nombre, std::string tipo,int precio);

	//void initOptions(cocos2d::Rect area);

	void AddListener();
	void EnableListener(bool b);
	void TouchEvent(cocos2d::Touch* touch, cocos2d::Point _p);
	void arrastraArma(cocos2d::Vec2 vector);
	void CreateMenuCompra();
	void CloseMenuCompra();
	void HacerCompra();
	void setPointY(int y);
	void setDesdeTienda(bool estado);

	void setArma(Arma* arma);

	Arma* clon;
	Arma* getArma();
	Arma* ClonarArma(Arma*a);

	std::string getTipo();
	std::string getNombre();
	int getDa�o();
	bool getDesdeTienda();
	bool enNivel = false; 
	bool colocada = false;
	bool childEnTienda = false; //esta activa en tienda
	bool childEnNivel = false; 


private:
	bool desdeTienda;
	bool armaComprada = false;
	int da�o;
	int toqueY;
	int precio;
	cocos2d::EventListenerTouchOneByOne* listener;
	//cocos2d::Rect areaArma;
	std::string tipo;
	std::string nombre;
	Arma* esteArma;

	void accionTouch();


};

#endif //ARMA


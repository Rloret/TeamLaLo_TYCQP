#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"

USING_NS_CC;



ZerrinClass::ZerrinClass() {
	velocidad = 2;
	vida = 10;
	//this->setPositionY(Director::getInstance()->getVisibleSize().height);
	//visibleSize = Director::getInstance()->getVisibleSize();
	this->retain();
}

ZerrinClass::~ZerrinClass()
{
}

ZerrinClass * ZerrinClass::create()
{
	ZerrinClass* zerrin = new ZerrinClass();
	//Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	zerrin->initWithFile("images/Zerrin/zerrin.PNG");
	
	return zerrin;
}


void ZerrinClass::setVelocidad(int v)
{
	velocidad = v;
}

void ZerrinClass::setVida(int v)
{
	vida = v;
}

int ZerrinClass::getVelocidad()
{
	return velocidad;
}

int ZerrinClass::getVida()
{
	return vida;
}

void ZerrinClass::setCorrer(bool c)
{
	if (c) {
		correr();
	}
	else {
	
		CCLOG("paro de correr");
		haLlegado = true;
	}
}



void ZerrinClass::correr()
{
	CCLOG("Voy a correr");
	corriendo = true;

	this->scheduleUpdate();
	//Global::getInstance()->nivel->scheduleUpdate();
}


void ZerrinClass::update(float dt)
{
	
	if (corriendo) {
		if (this->getPositionX() > Director::getInstance()->getVisibleSize().width/2 && (((Nivel *)Global::getInstance()->nivel)->getPosXFondo() >Director::getInstance()->getVisibleSize().width)) {
			((Nivel *)Global::getInstance()->nivel)->mueveFondo(velocidad);
			//((Nivel *)Global::getInstance()->nivel)->mueveNubes(-velocidad*1.5);

		}

		else if (this->getPositionX()> Director::getInstance()->getVisibleSize().width-50) {
			this->corriendo = false;
			Global::getInstance()->zerrin->haLlegado = true;
			CCLOG("jhiuh");

			((Nivel*)Global::getInstance()->nivel)->goToGameOver(this);
		}
		
		else {
			this->setPositionX(this->getPositionX() + velocidad);
			//((Nivel *)Global::getInstance()->nivel)->mueveNubes(-velocidad/2);
		}



	}
}
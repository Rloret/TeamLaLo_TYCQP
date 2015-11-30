#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"

USING_NS_CC;


static ZerrinClass * zerrin = nullptr;

ZerrinClass::ZerrinClass() {
	velocidad = 10; // es el tiempo que tarda en llegar al final
	vida = 10;
	this->retain();
}

ZerrinClass * ZerrinClass::create()
{
	ZerrinClass* zerrin = new ZerrinClass();
	//Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	zerrin->initWithFile("images/Zerrin/zerrin.PNG");
	zerrin->setScale(0.5,0.5);
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
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCLOG("Voy a correr");
	corriendo = true;

	this->scheduleUpdate();
}


void ZerrinClass::update(float dt)
{
	int v = getVelocidad();
	if (corriendo) {
		this->setPositionX(this->getPositionX() + v);
		if (this->getPositionX()> 750) {
			this->corriendo = false;
			Global::getInstance()->zerrin->haLlegado = true;
			CCLOG("jhiuh");

			((Nivel*)Global::getInstance()->nivel)->goToGameOver(this);
		}
	}
}
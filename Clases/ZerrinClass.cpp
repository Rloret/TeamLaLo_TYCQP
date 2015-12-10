#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"

USING_NS_CC;



ZerrinClass::ZerrinClass() {
	velocidad = 0.2;
	vida = 10;
	//ObjetivoCamara = Sprite::create();
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
	zerrin->setPhysicsBody(PhysicsBody::createBox(zerrin->getBoundingBox().size));
	zerrin->getPhysicsBody()->setDynamic(true);
	
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

		/*if (this->getPositionX() >  ((Nivel*)Global::getInstance()->nivel)->getBackgroundWidth()-Director::getInstance()->getVisibleSize().width/2
			&& this->getPositionX() <  ((Nivel*)Global::getInstance()->nivel)->getBackgroundWidth() - Director::getInstance()->getVisibleSize().width / 2+velocidad) {
			//((Nivel*)Global::getInstance()->nivel)->stopCamara();
			this->setPositionX(this->getPositionX() + velocidad * Director::getInstance()->getVisibleSize().width * dt);

		}*/
		/*else*/ //if ((this->getPositionX())  >  (((Nivel*)Director::getInstance()->getRunningScene())->getBackgroundWidth() - this->getBoundingBox().size.width) ) {
		if ((this->getPositionX())  >  3072 - this->getBoundingBox().size.width) {
			this->corriendo = false;
			Global::getInstance()->zerrin->haLlegado = true;
			CCLOG("Zerrin esta burladisimo %d",this->getRotation());
			((Nivel*)Director::getInstance()->getRunningScene())->goToGameOver(this);
		}
		else {
			this->setPositionX(this->getPositionX() + velocidad * Director::getInstance()->getVisibleSize().width * dt);
		}
		//this->ObjetivoCamara->setPosition(this->getPositionX(), Director::getInstance()->getVisibleSize().height / 2);
		((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidad * Director::getInstance()->getVisibleSize().width * dt);

	}
}
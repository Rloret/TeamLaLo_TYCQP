#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"

USING_NS_CC;



ZerrinClass::ZerrinClass() {
	velocidad = 0.2;
<<<<<<< HEAD
	vida = 1000;
=======
	vida = 10;
>>>>>>> origin/master
	this->retain();
	this->setName("Zerrin");
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
	
		//CCLOG("paro de correr");
		haLlegado = true;
	}
}

void ZerrinClass::muestraDa�o(int da�o)
{
	auto da�oLabel = Label::createWithSystemFont((String::createWithFormat("- %d",da�o)->getCString()), "Arial", 35);
	da�oLabel->setColor(Color3B::RED);
	da�oLabel->enableShadow();
	da�oLabel->retain();
	this->addChild(da�oLabel);
	auto seq = Sequence::create(MoveTo::create(4.0, Vec2(this->getParent()->getParent()->getPositionX(), this->getParent()->getContentSize().height)),NULL);
	da�oLabel->runAction(seq);
}





void ZerrinClass::correr()
{
	//CCLOG("Voy a correr");
	corriendo = true;

	this->scheduleUpdate();
	//Global::getInstance()->nivel->scheduleUpdate();
}



void ZerrinClass::update(float dt)
{
	
	if (corriendo) {

		if ((this->getPositionX())  >  3072 - this->getBoundingBox().size.width) {
			this->corriendo = false;
			Global::getInstance()->zerrin->haLlegado = true;
<<<<<<< HEAD
			//CCLOG("Zerrin esta burladisimo %d",this->getRotation());
=======
			CCLOG("Zerrin esta burladisimo %d",this->getRotation());
>>>>>>> origin/master
			((Nivel*)Director::getInstance()->getRunningScene())->goToGameOver(this);

		}
		else {
			this->setPositionX(this->getPositionX() + velocidad * Director::getInstance()->getVisibleSize().width * dt);
			//Global::getInstance()->zerrin->getPhysicsBody()->setVelocity(Vec2(100, 0));
		}


		((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidad * Director::getInstance()->getVisibleSize().width * dt);

	}
}
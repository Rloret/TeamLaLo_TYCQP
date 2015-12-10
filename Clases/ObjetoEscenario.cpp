#include "ObjetoEscenario.h"

USING_NS_CC;

ObjetoEscenario::ObjetoEscenario(const std::string & fileName, int daño, std::string nombre,int tipo)
{
	this->daño = daño;
	this->nombre = nombre;
	this->initWithFile(fileName);
	this->tipo = tipo;
	this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));
	this->getPhysicsBody()->setDynamic(false);
	this->getPhysicsBody()->setCollisionBitmask(0x03);
	this->getPhysicsBody()->setCategoryBitmask(0x01);
	this->getPhysicsBody()->setContactTestBitmask(false);

	this->AddListener();
}

ObjetoEscenario::~ObjetoEscenario()
{
}

ObjetoEscenario * ObjetoEscenario::create(const std::string & fileName, int daño, std::string nombre,int tipo)
{
	ObjetoEscenario* objeto = new ObjetoEscenario(fileName,daño,nombre, tipo);

	objeto->retain();
	return objeto;

	/*CC_SAFE_DELETE(arma);
	return NULL;*/
}

void ObjetoEscenario::AddListener()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		cocos2d::Point p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p)&& this->isVisible())
		{
			return true;
		}

		return false;
	};
	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		ObjetoEscenario::TouchEvent(touch, touch->getLocation());
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

}

void ObjetoEscenario::TouchEvent(cocos2d::Touch * touch, cocos2d::Point _p)
{
	CCLOG("Has tocado un objeto");
}





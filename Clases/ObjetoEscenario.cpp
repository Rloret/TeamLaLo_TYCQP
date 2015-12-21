#include "ObjetoEscenario.h"
#include "Global.h"

USING_NS_CC;

ObjetoEscenario::ObjetoEscenario(const std::string & fileName, int daño, std::string nombre,int tipo)
{
	this->daño = daño;
	this->nombre = nombre;
	this->initWithFile(fileName);
	this->tipo = tipo;


	this->setName("Objeto");

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
	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		cocos2d::Point p = convertToWorldSpace(touch->getLocation());
		cocos2d::Point pprueba = convertToNodeSpace(Vec2(touch->getLocation()));
		cocos2d::Rect rect2 = this->getBoundingBox();
		rect2.origin = convertToWorldSpace(rect2.origin);
		cocos2d::Rect rectprueba = this->getBoundingBox();
		rectprueba.origin = Vec2(convertToNodeSpace(rectprueba.origin));
		
		if (this->isVisible() && (rectprueba.containsPoint(pprueba)))
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

void ObjetoEscenario::TouchEvent(cocos2d::Touch * touch, cocos2d::Point _p){assignBody();}

int ObjetoEscenario::getDaño(){	return daño;}

void ObjetoEscenario::enableListener(bool estado)
{
	listener->setEnabled(estado);
}

void ObjetoEscenario::accionColision(Node* objeto)
{
	auto cuerpoFisicas = objeto->getPhysicsBody();
	//CCLOG("obj con tipo %d" , ((ObjetoEscenario*)objeto)->getTipo());

	switch (((ObjetoEscenario*)objeto)->tipo) {
		
	case 1: //abajo
		CCLOG("Arma tipo 1/abajo y quito fisicas");
		objeto->setPhysicsBody(nullptr);
		break;

	case 2://arriba
		CCLOG("Arma tipo 2/arriba , quito fisicas y listner");

		objeto->runAction(FadeOut::create(0.4));
		objeto->setPhysicsBody(nullptr);
		((ObjetoEscenario*)objeto)->enableListener(false);
		break;

	default:
		CCLOG("Arma default y quito fisicas");
		objeto->setPhysicsBody(nullptr);
		break;
	}
}



void ObjetoEscenario::assignBody()
{
	cocos2d::PhysicsBody* body;
	switch (this->tipo) {
	case 1:
		body = cocos2d::PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		this->setPhysicsBody(body);
		this->getPhysicsBody()->setDynamic(false);
		break;
	case 2:
		body = cocos2d::PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		this->setPhysicsBody(body);
		this->nombre = "maceta";
		this->getPhysicsBody()->setDynamic(true);
		this->getPhysicsBody()->setVelocity(Vec2(0,-400));
		break;
	case 3:
		break;
	}

	this->getPhysicsBody()->setCollisionBitmask(false);
	this->getPhysicsBody()->setContactTestBitmask(true);
}

int ObjetoEscenario::getTipo()
{
	return tipo;
}





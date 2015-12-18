#include "Arma.h"
#include "Nivel.h"
#include"Global.h"
#include "TiendaScene.h"

USING_NS_CC;

Arma::Arma( int daño, std::string nombre, int tipo,int precio,int mechones)
{

	this->daño = daño;
	this->nombre = nombre;
	this->tipo = tipo;
	this->precio = precio;
	this->mechones = mechones;
	this->setArma(this);
	this->AddListener();
	desdeTienda = false;

	this->setName("Arma");

	this->retain();



	//meter en función

}

Arma::~Arma()
{
}

Arma * Arma::create(cocos2d::Texture2D* t, int daño, std::string nombre,int tipo,int precio,int mechones)
{
	Arma* arma = new Arma(daño,nombre,tipo,precio,mechones);
	//Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	arma->initWithTexture(t);
	return arma;

		
	
	/*CC_SAFE_DELETE(arma);
	return NULL;*/
}

void Arma::EnableListener(bool b){
	listener->setEnabled(b);
}
void Arma::EnableSwallow(bool b)
{
	this->listener->setSwallowTouches(b);
}
void Arma::AddListener()
{
	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		cocos2d::Point p = touch->getLocation();
		cocos2d::Point pprueba = convertToWorldSpace(Vec2(touch->getLocation()));
		cocos2d::Rect rect2 = this->getBoundingBox();
		//cocos2d::Rect rectprueba = this->getBoundingBox();
		cocos2d::Rect rectprueba = Rect(this->getPositionX(),this->getPositionY(),this->getBoundingBox().size.width,this->getBoundingBox().size.height);
		

		rectprueba.origin = Vec2(convertToWorldSpace(rect2.origin));
		//CCLOG("rect prueba origin %f %f y mide %f %f", rectprueba.origin.x, rectprueba.origin.y, rectprueba.size.width, rectprueba.size.height);
		//CCLOG("toque originalen   %f %f",p.x,p.y);
		//CCLOG("toque convertido   %f %f", pprueba.x, pprueba.y);

		if (this->isVisible() && rectprueba.containsPoint(pprueba))
		{

			return true;
		}

		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		cocos2d::Point p = touch->getLocation();
		if (Global::getInstance()->juegoEnCurso && /*this->getPosition().y >50 &&*/ !this->colocada && !this->getDesdeTienda()) {
			arrastrando = true;
			Arma::arrastraArma(p);

			
		}
	};
	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		Arma::accionTouch();
		arrastrando = false;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 32);

}


void Arma::arrastraArma(cocos2d::Vec2 vector)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto zerrinpos = Global::getInstance()->zerrin->getPosition();
	
	if (vector.y >768 - this->getBoundingBox().size.height) vector.y = 768-this->getBoundingBox().size.height/2;
	else if (vector.y < 200+ this->getBoundingBox().size.height/2) vector.y = 200+ this->getBoundingBox().size.height/2;

	if (vector.x > visibleSize.width- this->getBoundingBox().size.width) vector.x = visibleSize.width- this->getBoundingBox().size.width/2;
	else if (vector.x < this->getBoundingBox().size.width) vector.x = this->getBoundingBox().size.height/2;

	this->setPosition(vector);
	//CCLOG("ARMAA %f %f",vector.x,vector.y);
	//CCLOG("visible size %f %f", visibleSize.width, visibleSize.height);

}

void Arma::accionTouch(){
	Point p = this->getPosition();
	if (desdeTienda) {
		Global::getInstance()->armaAComprar = this;
		//CCLOG("Desde tienda");
	}
	else{
		if (p.y < 500 && !Global::getInstance()->juegoEnCurso) {
			if (Global::getInstance()->ContadorArmas < 5 && !this->enNivel) {
				Global::getInstance()->ContadorArmas += 1;
				//llamar a global
				Arma* a = this->ClonarArma(this);
				CCLOG("size antes %d", Global::getInstance()->ArmasNivel.size());
				Global::getInstance()->añadeArmasANivel(a);
				a->colocada = false;
				//a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 80 + 500,Director::getInstance()->getVisibleSize().height-70));
				CCLOG("size despues %d",Global::getInstance()->ArmasNivel.size());
				a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 512 /5  +512 -this->getContentSize().width/2, Director::getInstance()->getVisibleSize().height -this->getBoundingBox().size.height/2-20));
				this->enNivel = true;
				Global::getInstance()->recolocaArmasNivel();
			}
			else if (this->enNivel) CCLOG("ya esta metida");

			else {

				CCLOG("No puedes usar más");
			}
		}
		else if (!Global::getInstance()->juegoEnCurso) Global::getInstance()->quitaArmaDeNivel(this);

		else if (Global::getInstance()->juegoEnCurso) {
			if (!colocada) this->colocada = true;
			accion(this);
		}
	}
}

/*void Arma::caer(float dt)
{
	this->setPositionY(this->getPositionY()-5);

}*/





void Arma::setPointY(int y)
{
	this->toqueY = y;
}

void Arma::setArma(Arma* arma)
{
	esteArma = arma;
}

void Arma::accion(Arma * a)
{
	switch (a->tipo)
	{
	case 0:  //las que caen
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10000, 1, 0.5)));
		/*a->getPhysicsBody()->setCollisionBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x01);
		a->getPhysicsBody()->setCategoryBitmask(0x03);*/
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;
	case 1:  //las que caen
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10.0, 0.2, 1)));
		/*a->getPhysicsBody()->setCollisionBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x01);*/
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;

	case 2: //bola demolicion
		//a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10.0, 0.2, 1)));
		a->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.width / 2));
		a->getPhysicsBody()->setContactTestBitmask(true);

		break;
	default:
		break;
	}
	a->getPhysicsBody()->setVelocity(Vec2(0, -100));

}

Arma* Arma::getArma()
{
	return esteArma;
}

int Arma::getTipo()
{
	return tipo;
}

std::string Arma::getNombre()
{
	return nombre;
}

int Arma::getDaño()
{
	return 15;
}

int Arma::getPrecio()
{
	return precio;
}

int Arma::getMechones()
{
	return mechones;
}

bool Arma::getDesdeTienda()
{
	return desdeTienda;
}

bool Arma::soyObjeto()
{
	return false;
}


void Arma::setDesdeTienda(bool estado)
{
	desdeTienda = estado;
}


Arma* Arma::ClonarArma(Arma* a){

	Arma* nueva = Arma::create(a->getTexture(),a->daño,a->getNombre(),a->tipo,a->precio,a->mechones);
	nueva->clon = a;
	return nueva;
}


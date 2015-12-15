#include "Arma.h"
#include "Nivel.h"
#include"Global.h"
#include "TiendaScene.h"

USING_NS_CC;

Arma::Arma( int da�o, std::string nombre, int tipo,int precio,int mechones)
{

	this->da�o = da�o;
	this->nombre = nombre;
	this->tipo = tipo;
	this->precio = precio;
	this->mechones = mechones;
	this->setArma(this);
	this->AddListener();
	desdeTienda = false;

	this->setName("Arma");

	this->retain();



	//meter en funci�n

}

Arma::~Arma()
{
}

Arma * Arma::create(cocos2d::Texture2D* t, int da�o, std::string nombre,int tipo,int precio,int mechones)
{
	Arma* arma = new Arma(da�o,nombre,tipo,precio,mechones);
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
		cocos2d::Point p2 = Point(0, 0);
		auto posi = this->getPosition();
		cocos2d::Rect rect = Rect(this->getPosition().x- this->getBoundingBox().size.width/2, this->getPosition().y- this->getBoundingBox().size.height/2,
							this->getBoundingBox().size.width, this->getBoundingBox().size.height);


		if (Global::getInstance()->juegoEnCurso) {
			p2 = Point(Global::getInstance()->zerrin->getPosition().x-Director::getInstance()->getVisibleSize().width/2 + p.x, p.y);
			//CCLOG("(%f,%f)",p.x, p2.x);
		}

		if (this->isVisible() && (rect.containsPoint(p)|| rect.containsPoint(p2)))
		{
			//CCLOG("He tocado el arma que cuesta:  %d ", this->getPrecio());
			setPointY(p.y);

			return true;
		}

		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		cocos2d::Point p = touch->getLocation();
		if (Global::getInstance()->juegoEnCurso && this->getPosition().y >50 && !this->colocada && !this->getDesdeTienda()) {
			arrastrando = true;
			if (Global::getInstance()->juegoEnCurso)	//Arma::arrastraArma(p);
				if(Global::getInstance()->zerrin->getPositionX()>1024){
					Arma::arrastraArma(Point(Global::getInstance()->zerrin->getPosition().x -
										Director::getInstance()->getVisibleSize().width / 2 + p.x, p.y));

				}
				
				else		Arma::arrastraArma(p);
			
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
	
	if (vector.y >768 - this->getBoundingBox().size.height) vector.y = 768-this->getBoundingBox().size.height;
	else if (vector.y < 200+ this->getBoundingBox().size.height/2) vector.y = 200+ this->getBoundingBox().size.height/2;

	if (vector.x > visibleSize.width-50) vector.x = visibleSize.width- 50;
	else if (vector.x < 50) vector.x = 50;
	//if (vector.x < zerrinpos.x-visibleSize.width/2+20) vector.x = zerrinpos.x - visibleSize.width / 2+20;
	//else if (vector.x>zerrinpos.x + visibleSize.width / 2-20) vector.x = zerrinpos.x + visibleSize.width / 2-20;

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
				Global::getInstance()->a�adeArmasANivel(a);
				a->colocada = false;
				a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 80 + 500,Director::getInstance()->getVisibleSize().height-70));
				this->enNivel = true;
			}
			else if (this->enNivel) CCLOG("ya esta metida");

			else {

				CCLOG("No puedes usar m�s");
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
		a->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.height / 2, cocos2d::PhysicsMaterial(100000000000000, 1, 0.5)));
		/*a->getPhysicsBody()->setCollisionBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x01);
		a->getPhysicsBody()->setCategoryBitmask(0x03);*/
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;
	case 1:  //las que caen
		a->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.height / 2, cocos2d::PhysicsMaterial(10.0, 0.2, 1)));
		/*a->getPhysicsBody()->setCollisionBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x02);
		a->getPhysicsBody()->setCategoryBitmask(0x01);*/
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;
	default:
		break;
	}

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

int Arma::getDa�o()
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

	Arma* nueva = Arma::create(a->getTexture(),a->da�o,a->getNombre(),a->tipo,a->precio,a->mechones);
	nueva->clon = a;
	return nueva;
}


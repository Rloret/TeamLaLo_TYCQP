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
		cocos2d::Point p2 = Point(0, 0);
		auto posi = this->getPosition();
		cocos2d::Rect rect = Rect(this->getPosition().x- this->getBoundingBox().size.width/2, this->getPosition().y- this->getBoundingBox().size.height/2,
							this->getBoundingBox().size.width, this->getBoundingBox().size.height);


		if (Global::getInstance()->juegoEnCurso) {
			p2 = Point(Global::getInstance()->zerrin->getPosition().x-Director::getInstance()->getVisibleSize().width/2 + p.x, p.y);
			CCLOG("(%f,%f)",p.x, p2.x);
		}

		if (this->isVisible() && (rect.containsPoint(p)|| rect.containsPoint(p2)))
		{
			CCLOG("He tocado el arma que cuesta:  %d ", this->getPrecio());
			setPointY(p.y);

			return true;
		}

		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		cocos2d::Point p = touch->getLocation();
		if (Global::getInstance()->juegoEnCurso && this->getPosition().y >50 && !this->colocada && !this->getDesdeTienda()) {
			if(Global::getInstance()->juegoEnCurso)	Arma::arrastraArma(Point(Global::getInstance()->zerrin->getPosition().x - Director::getInstance()->getVisibleSize().width / 2 + p.x, p.y));
			else		Arma::arrastraArma(p);
			

		}
	};
	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		Arma::accionTouch();
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 32);

}


void Arma::arrastraArma(cocos2d::Vec2 vector)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto zerrinpos = Global::getInstance()->zerrin->getPosition();
	/*if (vector.y > 768) vector.y = 768;
	if (vector.x < zerrinpos.x-visibleSize.width/2+20) vector.x = zerrinpos.x - visibleSize.width / 2+20;
	else if (vector.x>zerrinpos.x + visibleSize.width / 2-20) vector.x = zerrinpos.x + visibleSize.width / 2-20;*/
	this->setPosition(vector);
}

void Arma::accionTouch(){
	Point p = this->getPosition();
	if (desdeTienda) {
		Global::getInstance()->armaAComprar = this;
		CCLOG("Desde tienda");
	}
	else{
		if (p.y < 500 && !Global::getInstance()->juegoEnCurso) {
			CCLOG("El arma con daño : %d", this->daño);
			//CCLOG("Es para añadir a la lista de armas que vamos a usar");
			if (((Nivel*)Global::getInstance()->nivel)->ContadorArmas < 5 && !this->enNivel) {

				//CCLOG("Se puede añadir");

				((Nivel*)Global::getInstance()->nivel)->ContadorArmas += 1;
				//llamar a global
				Arma* a = this->ClonarArma(this);
				Global::getInstance()->añadeArmasANivel(a);
				a->colocada = false;
				a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 80 + 500,Director::getInstance()->getVisibleSize().height-70));
				this->enNivel = true;
			}
			else if (this->enNivel) CCLOG("ya esta metida");

			else {

				CCLOG("No puedes usar más");
			}
		}
	}


	if (Global::getInstance()->juegoEnCurso){
		 if (!colocada) this->colocada = true;
		// accion(this);
	}

	else if (!Global::getInstance()->juegoEnCurso) Global::getInstance()->quitaArmaDeNivel(this);
	

}

void Arma::caer(float dt)
{
	this->setPositionY(this->getPositionY()-5);

}





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
		a->schedule(schedule_selector(Arma::caer), 0.5);
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

int Arma::getDaño()
{
	return this->daño;
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


void Arma::setDesdeTienda(bool estado)
{
	desdeTienda = estado;
}


Arma* Arma::ClonarArma(Arma* a){

	Arma* nueva = Arma::create(a->getTexture(),a->daño,a->getNombre(),a->tipo,a->precio,a->mechones);
	nueva->clon = a;
	return nueva;
}


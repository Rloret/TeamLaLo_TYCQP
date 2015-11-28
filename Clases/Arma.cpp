#include "Arma.h"
#include "Nivel.h"
#include"Global.h"
#include "TiendaScene.h"

USING_NS_CC;

Arma::Arma( int da�o, std::string nombre, std::string tipo,int precio)
{

	this->da�o = da�o;
	this->nombre = nombre;
	this->tipo = tipo;
	this->precio = precio;
	this->setArma(this);
	this->AddListener();
	desdeTienda = false;
	this->retain();


	//meter en funci�n

}

Arma::~Arma()
{
}

Arma * Arma::create(cocos2d::Texture2D* t, int da�o, std::string nombre, std::string tipo,int precio)
{
	Arma* arma = new Arma(da�o,nombre,tipo,precio);
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
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			setPointY(p.y);

			return true;
		}

		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		if (Global::getInstance()->juegoEnCurso && this->getPosition().y >50 && !this->colocada && !this->getDesdeTienda()) {
			Arma::arrastraArma(touch->getLocation());

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

	if (vector.y > 520) vector.y = 520;
	if (vector.x < 20) vector.x = 20;
	else if (vector.x>780) vector.x = 780;
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
			CCLOG("El arma con da�o : %d", this->da�o);
			//CCLOG("Es para a�adir a la lista de armas que vamos a usar");
			if (((Nivel*)Global::getInstance()->nivel)->ContadorArmas < 5 && !this->enNivel) {

				//CCLOG("Se puede a�adir");

				((Nivel*)Global::getInstance()->nivel)->ContadorArmas += 1;
				//llamar a global
				Global::getInstance()->a�adeArmasANivel(this->ClonarArma(this));
				this->enNivel = true;
			}
			else if (this->enNivel) CCLOG("ya esta metida");

			else {

				CCLOG("No puedes usar m�s");
			}
		}
	}


	if (Global::getInstance()->juegoEnCurso){
		 if (!colocada) this->colocada = true;
	}

	else if (!Global::getInstance()->juegoEnCurso) Global::getInstance()->quitaArmaDeNivel(this);
	

}





void Arma::setPointY(int y)
{
	this->toqueY = y;
}

void Arma::setArma(Arma* arma)
{
	esteArma = arma;
}

Arma* Arma::getArma()
{
	return esteArma;
}

std::string Arma::getTipo()
{
	return tipo;
}

std::string Arma::getNombre()
{
	return nombre;
}

int Arma::getDa�o()
{
	return this->da�o;
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

	Arma* nueva = Arma::create(a->getTexture(),a->da�o,a->getNombre(),a->tipo,a->precio);
	nueva->clon = a;
	return nueva;
}


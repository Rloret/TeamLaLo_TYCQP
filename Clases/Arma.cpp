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
		cocos2d::Point pprueba = convertToWorldSpace(Vec2(touch->getLocation()));
		cocos2d::Rect rect2 = this->getBoundingBox();
		cocos2d::Rect rectprueba = Rect(this->getPositionX(),this->getPositionY(),this->getBoundingBox().size.width,this->getBoundingBox().size.height);
	
		rectprueba.origin = Vec2(convertToWorldSpace(rect2.origin));

		if (this->isVisible() && rectprueba.containsPoint(pprueba))
		{

			return true;
		}

		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		cocos2d::Point p = touch->getLocation();
		if (Global::getInstance()->juegoEnCurso && !this->colocada && !this->getDesdeTienda()) {
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

	//Checkar el tipo por si necesita escalado ->funcion que segun el tipo devuelve un factor de escala
	//configurar arma como desactivada si el tipo lo requiere
	//A�adir sprites auxiliares;-> funcion que segfun el a�ade y coloca sprites auxiliares
	auto zerrinpos = Global::getInstance()->zerrin->getPosition();
	switch (tipo) {
	case 3:
		vector.y = 270;

		if (vector.x > visibleSize.width - this->getBoundingBox().size.width) vector.x = visibleSize.width - this->getBoundingBox().size.width / 2;
		else if (vector.x < this->getBoundingBox().size.width) vector.x = this->getBoundingBox().size.height / 2;
		break;
	case 0:
	case 1:
	case 2:
	default:

		if (vector.y >768 - this->getBoundingBox().size.height) vector.y = 768 - this->getBoundingBox().size.height / 2;
		else if (vector.y < 200 + this->getBoundingBox().size.height / 2) vector.y = 200 + this->getBoundingBox().size.height / 2;

		if (vector.x > visibleSize.width - this->getBoundingBox().size.width) vector.x = visibleSize.width - this->getBoundingBox().size.width / 2;
		else if (vector.x < this->getBoundingBox().size.width) vector.x = this->getBoundingBox().size.height / 2;
		break;

	}


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
				Global::getInstance()->a�adeArmasANivel(a);
				a->colocada = false;
				//a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 80 + 500,Director::getInstance()->getVisibleSize().height-70));
				CCLOG("size despues %d",Global::getInstance()->ArmasNivel.size());
				a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 512 /5  +512 -this->getContentSize().width/2, Director::getInstance()->getVisibleSize().height -this->getBoundingBox().size.height/2-20));
				this->enNivel = true;
				Global::getInstance()->recolocaArmasNivel();
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
			//segun el tipo configurar timers o no->
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
	cocos2d::CallFunc* accion;
	cocos2d::RepeatForever* secuencia;
	cocos2d::Vector<cocos2d::Node*> hijos;
	//cocos2d::Sequence* secuencia;
	switch (a->tipo)
	{
	case 0:  //las que caen
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10000, 1, 0.5)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;
	case 1:  //las que caen ligeras
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10.0, 0.2, 1.0)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		break;

	case 2: //bola demolicion
		a->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.width / 2));
		a->getPhysicsBody()->setContactTestBitmask(true);

		break;
	case 3:
		hijos = Director::getInstance()->getRunningScene()->getChildren();
		for (int i = 0; i < Director::getInstance()->getRunningScene()->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Director::getInstance()->getRunningScene()->removeChild(a);
				Director::getInstance()->getRunningScene()->getChildByTag(102)->addChild(a, 3);
				break;
			}
		}
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size/2 ));
		a->getPhysicsBody()->setCollisionBitmask(false);
		a->getPhysicsBody()->setContactTestBitmask(true);
		a->getPhysicsBody()->setDynamic(false);
		a->setScale(231 / 84);

		accion = CallFunc::create(CC_CALLBACK_0(Arma::intervalo,this,-1));//funcion del negativo;
		secuencia = RepeatForever::create(Sequence::create(DelayTime::create(1.5), accion,nullptr));
		//secuencia = Sequence::create(DelayTime::create(0.5), accion,nullptr);
		this->runAction(secuencia);
		break;
	default:
		break;
	}
	a->getPhysicsBody()->setVelocity(Vec2(0, -100));

}

void Arma::intervalo(int signo)
{
	parpadeo *= signo;
	CCLOG("ENTROOOO %d", signo);
	if (parpadeo < 0) {
		this->setTexture(Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_activos.png"));
		this->getPhysicsBody()->setContactTestBitmask(true);
	}
	else {
		this->setTexture(Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_no_activos.png"));
		this->getPhysicsBody()->setContactTestBitmask(false);
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




void Arma::setDesdeTienda(bool estado)
{
	desdeTienda = estado;
}


Arma* Arma::ClonarArma(Arma* a){

	Arma* nueva = Arma::create(a->getTexture(),a->da�o,a->getNombre(),a->tipo,a->precio,a->mechones);
	nueva->clon = a;
	return nueva;
}


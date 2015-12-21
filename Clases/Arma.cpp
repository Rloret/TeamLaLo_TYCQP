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

}

Arma::~Arma()
{
}

Arma * Arma::create(cocos2d::Texture2D* t, int daño, std::string nombre,int tipo,int precio,int mechones)
{
	Arma* arma = new Arma(daño,nombre,tipo,precio,mechones);
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
		Arma::accionTouch(touch);
		arrastrando = false;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 32);

}


void Arma::arrastraArma(cocos2d::Vec2 vector)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Checkar el tipo por si necesita escalado ->funcion que segun el tipo devuelve un factor de escala
	//configurar arma como desactivada si el tipo lo requiere
	//Añadir sprites auxiliares;-> funcion que segfun el añade y coloca sprites auxiliares
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

}

void Arma::accionTouch(cocos2d::Touch* touch){
	Point p = this->getPosition();
	if (desdeTienda) {
		Global::getInstance()->armaAComprar = this;
	}
	else{
		if (p.y < 500 && !Global::getInstance()->juegoEnCurso) {
			if (Global::getInstance()->ContadorArmas < 5 && !this->enNivel) {
				Global::getInstance()->ContadorArmas += 1;
				//llamar a global
				Arma* a = this->ClonarArma(this);
				Global::getInstance()->añadeArmasANivel(a);
				a->colocada = false;
				//a->setPosition(Point(Global::getInstance()->ArmasNivel.size() * 80 + 500,Director::getInstance()->getVisibleSize().height-70));
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
			accion(this,touch);
			//segun el tipo configurar timers o no->
		}
	}
}

void Arma::setPointY(int y)
{
	this->toqueY = y;
}

void Arma::setArma(Arma* arma)
{
	esteArma = arma;
}

void Arma::accion(Arma * a, cocos2d::Touch* touch)
{
	cocos2d::CallFunc* accion;
	cocos2d::RepeatForever* secuencia;
	cocos2d::Vector<cocos2d::Node*> hijos = Global::getInstance()->layerObjects->getChildren();;
	auto punto = convertToWorldSpace(touch->getLocation());
	//cocos2d::Sequence* secuencia;
	switch (a->tipo)
	{
	case 0:  //las que caen
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10000, 1, 0.5)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		a->getPhysicsBody()->setVelocity(Vec2(0, -100));
		break;
	case 1:  //las que caen ligeras
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10.0, 0.2, 1.0)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		a->getPhysicsBody()->setVelocity(Vec2(0, -100));
		break;

	case 2: //bola demolicion
		a->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.width / 2,PhysicsMaterial(1000,0.5,0.1)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		a->getPhysicsBody()->setVelocity(Vec2(0, 100));
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		a->getPhysicsBody()->setVelocity(Vec2(0, -100));
		break;
	case 3:	
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size/2,PhysicsMaterial(100,0.7,0.0)));
		a->getPhysicsBody()->setCollisionBitmask(false);
		a->getPhysicsBody()->setContactTestBitmask(true);
		a->getPhysicsBody()->setDynamic(false);
		a->setScale(231 / 84);
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		a->getPhysicsBody()->setVelocity(Vec2(0, -100));
		accion = CallFunc::create(CC_CALLBACK_0(Arma::intervalo,this,-1));//funcion del negativo;
		secuencia = RepeatForever::create(Sequence::create(DelayTime::create(1.5), accion,nullptr));
		//secuencia = Sequence::create(DelayTime::create(0.5), accion,nullptr);
		this->runAction(secuencia);
		break;
	default:
		break;
	}

	a->setPositionX(((Global::getInstance()->zerrin->getPositionX() - 1024 / 2) / 1024) * 1024 + touch->getLocation().x);

}

void Arma::intervalo(int signo)
{
	parpadeo *= signo;
	//CCLOG("ENTROOOO %d", signo);
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

void Arma::accionColision()
{
	auto cuerpoFisicas = this->getPhysicsBody();
	this->EnableListener(false);
	switch (tipo) {
	case 3:
		break;
	case 0:
	case 1:
		cuerpoFisicas->setCollisionBitmask(false);
		cuerpoFisicas->setContactTestBitmask(false);
		this->getPhysicsBody()->setVelocity(Vec2(-10,0));
		cuerpoFisicas->setAngularVelocity(-20);
		this->runAction(FadeOut::create(1.5));
		break;
	case 2:
		cuerpoFisicas->setCollisionBitmask(true);
		cuerpoFisicas->setContactTestBitmask(false);
		break;
	default:
		break;

	}
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


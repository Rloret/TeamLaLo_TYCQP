#include "Arma.h"
#include "Nivel.h"
#include"Global.h"
#include "TiendaScene.h"
#include "Animacion.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

USING_NS_CC;


Arma::Arma( int daño, std::string nombre, int tipo,int precio,int mechones)
{

	this->daño = daño;
	this->nombre = nombre;
	this->tipo = tipo;
	this->precio = precio;
	this->mechones = mechones;
	//this->setArma(this);
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
	case 4:
	case 5:
		vector.y = 270;

		if (vector.x > visibleSize.width - this->getBoundingBox().size.width) vector.x = visibleSize.width - this->getBoundingBox().size.width / 2;
		else if (vector.x < this->getBoundingBox().size.width) vector.x = this->getBoundingBox().size.height / 2;
		break;
	case 2:
		vector.y = 640;

		if (vector.x > visibleSize.width - this->getBoundingBox().size.width) vector.x = visibleSize.width - this->getBoundingBox().size.width / 2;
		else if (vector.x < this->getBoundingBox().size.width) vector.x = this->getBoundingBox().size.height / 2;
		break;
		break;
	case 0:
	case 1:
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
				Arma* a = this->ClonarArma(this);
				Global::getInstance()->añadeArmasANivel(a);
				a->colocada = false;
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
			this->EnableListener(false);
		}
	}
}

void Arma::setPointY(int y)
{
	this->toqueY = y;
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
		a->getPhysicsBody()->setCollisionBitmask(false);
		SoundCaer = AudioEngine::play2d("sounds/Objeto_cae.mp3", false, 0.7);

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
		a->getPhysicsBody()->setCollisionBitmask(false);
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
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a,10000);

				break;
			}
		}
		bolaDemolicion = this->ClonarArma(this);
		this->setTexture(Director::getInstance()->getTextureCache()->addImage("images/Armas/senuelo.png"));
		pivote = Sprite::create("images/Armas/pivote.png");
		pivote->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(bolaDemolicion);
		bolaDemolicion->setAnchorPoint(Vec2(-3.0, 0));
		pivote->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.width / 2, PhysicsMaterial(1000, 0.5, 0.1)));
		pivote->getPhysicsBody()->setContactTestBitmask(false);
		pivote->getPhysicsBody()->setCollisionBitmask(false);
		pivote->getPhysicsBody()->setDynamic(false);
		pivote->runAction(RepeatForever::create(RotateBy::create(1/360,1)));

		this->addChild(pivote);

		bolaDemolicion->setPhysicsBody(PhysicsBody::createCircle(a->getBoundingBox().size.width / 2, PhysicsMaterial(10000, 0.0, 0.0)));
		bolaDemolicion->getPhysicsBody()->setContactTestBitmask(true);
		bolaDemolicion->getPhysicsBody()->setCollisionBitmask(true);
		bolaDemolicion->getPhysicsBody()->setVelocity(Vec2(0, -400));
		bolaDemolicion->getPhysicsBody()->setLinearDamping(0.1f);
		bolaDemolicion->setName("Arma");
		bolaDemolicion->colocada = true;
		bolaDemolicion->enNivel = true;
		
		this->setPhysicsBody(nullptr);
		jointDemolicion = PhysicsJointDistance::construct(pivote->getPhysicsBody(), bolaDemolicion->getPhysicsBody(), Point::ZERO, Point::ZERO);

		Global::getInstance()->zerrin->getPhysicsBody()->getWorld()->addJoint(jointDemolicion);
		bolaDemolicion->setScale(1.2);
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
		accion = CallFunc::create(CC_CALLBACK_0(Arma::intervalo,this,this->tipo));//funcion del negativo;
		secuencia = RepeatForever::create(Sequence::create(DelayTime::create(1.5), accion,nullptr));
		this->runAction(secuencia);
		break;
	case 4:
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size / 2, PhysicsMaterial(100, 0.0, 0.0)));
		a->getPhysicsBody()->setCollisionBitmask(false);
		a->getPhysicsBody()->setContactTestBitmask(true);
		a->getPhysicsBody()->setDynamic(false);
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		a->getPhysicsBody()->setVelocity(Vec2(0, -100));
		accion = CallFunc::create(CC_CALLBACK_0(Arma::intervalo, this, this->tipo));//funcion del negativo;
		secuencia = RepeatForever::create(Sequence::create(DelayTime::create(1.0), accion, nullptr));
		this->runAction(secuencia);
		break;

	case 5:  //trampilla
		a->setTexture("images/Armas/trampilla.png");
		a->setPhysicsBody(PhysicsBody::createBox(a->getBoundingBox().size, cocos2d::PhysicsMaterial(10.0, 1, 1.0)));
		a->getPhysicsBody()->setContactTestBitmask(true);
		a->getPhysicsBody()->setCollisionBitmask(false);
		a->getPhysicsBody()->setDynamic(false);
		for (int i = 0; i < Global::getInstance()->layerObjects->getChildrenCount(); i++) {
			if (hijos.at(i) == a) {
				Global::getInstance()->layerObjects->removeChild(a);
				Global::getInstance()->nivel->getChildByTag(102)->addChild(a);

				break;
			}
		}
		break;
	default:
		break;
	}
	a->setPositionX(((Global::getInstance()->zerrin->getPositionX() - 1024 / 2) / 1024) * 1024 + touch->getLocation().x);
	if (a->getPositionX() > 3072 - 300)a->setPositionX(3072 - 300 - a->getBoundingBox().size.width);
	if (a->getPositionX() < 307)a->setPositionX(307);
	compruebaSitio(a);

}

void Arma::intervalo(int tipo)
{
	parpadeo *= -1;
	Texture2D *t_Activa;
	Texture2D *t_No_Activa;
	bool hayTransicionDeFisicasEntreTexturas;
	switch (tipo) {
		case 3:
			t_Activa = Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_activos.png");
			t_No_Activa	=Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_no_activos.png");
			hayTransicionDeFisicasEntreTexturas = true;
			break;
		case 4:
			t_Activa = Director::getInstance()->getTextureCache()->addImage("images/Armas/mina_activa.png");
			t_No_Activa = Director::getInstance()->getTextureCache()->addImage("images/Armas/mina_no_activa.png");
			hayTransicionDeFisicasEntreTexturas =false;

			break;
		default:
			break;		
	}
	if (parpadeo < 0) {
		this->setTexture(t_Activa);
		if(hayTransicionDeFisicasEntreTexturas)this->getPhysicsBody()->setContactTestBitmask(true);
		if (tipo == 3) AudioEngine::play2d("sounds/Pinchos.mp3", false, 0.8);
	}
	else {
		this->setTexture(t_No_Activa);
		if (hayTransicionDeFisicasEntreTexturas)this->getPhysicsBody()->setContactTestBitmask(false);
	}
}

void Arma::reactivaBitmasks()
{
	if (this->tipo == 2) {
		this->getPhysicsBody()->setCollisionBitmask(true);
		this->getPhysicsBody()->setContactTestBitmask(true);
	}
	else if (this->tipo == 5) {
		this->getPhysicsBody()->setContactTestBitmask(true);
		this->setTexture("images/Armas/trampilla.png");
	}


}

void Arma::compruebaSitio(Arma* a)
{
	for (int i = 0; i < Global::getInstance()->ArmasNivel.size(); i++) {
		if (Global::getInstance()->ArmasNivel[i]->colocada && a->getBoundingBox().intersectsRect(Global::getInstance()->ArmasNivel[i]->getBoundingBox())) {
			auto nuevolugar = Global::getInstance()->ArmasNivel[i]->getPositionX() + Global::getInstance()->ArmasNivel[i]->getBoundingBox().size.width;
			a->getPositionX()<1024 * 3 ? a->setPositionX(nuevolugar) : a->setPositionX(nuevolugar - Global::getInstance()->ArmasNivel[i]->getBoundingBox().size.width * 2);
		}
	}
}

/*Arma* Arma::getArma()
{
	return esteArma;
}*/

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
	return daño;
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



void Arma::accionColision(int tipoDelArma)
{
	PhysicsBody* cuerpoFisicas; 
	cuerpoFisicas = this->getPhysicsBody();
	this->EnableListener(false);
	Animacion* animacionArma;
	cocos2d::Sprite* animacionSprite;

	switch (tipo) {
	case 3:
		break;
	case 0:
	case 1:
		cuerpoFisicas->setCollisionBitmask(false);
		cuerpoFisicas->setContactTestBitmask(false);
		this->getPhysicsBody()->setVelocity(Vec2(-40,-40));
		cuerpoFisicas->setAngularVelocity(-20);
		this->runAction(FadeOut::create(1.5));
		break;
	case 2:
		this->getPhysicsBody()->setCollisionBitmask(false);
		this->getPhysicsBody()->setContactTestBitmask(false);
		this->runAction(cocos2d::Sequence::create(cocos2d:: DelayTime::create(3.0), cocos2d::CallFunc::create(CC_CALLBACK_0(Arma::reactivaBitmasks, this)), NULL));
		break;
	case 4: 
		cuerpoFisicas->setCollisionBitmask(false);
		cuerpoFisicas->setContactTestBitmask(false);
		animacionArma = new Animacion("mina_detonacion_%03d.png", 7, 2.0, "images/Armas/Armas.plist", false);
		this->runAction(FadeOut::create(0.5));
		animacionSprite = animacionArma->getAnimacionCreada();
		this->addChild(animacionSprite);
		animacionSprite->setPositionX(animacionSprite->getPositionX() - this->getBoundingBox().size.width*1.5);
		break;
	case 5:
		cuerpoFisicas->setCollisionBitmask(false);
		cuerpoFisicas->setContactTestBitmask(false);
		if (Global::getInstance()->zerrin->getPositionX() > this->getPositionX()) { //dcha
			this->setTexture("images/Armas/trampilla_activa_dcha.png");
		}
		else {
			this->setTexture("images/Armas/trampilla_activa_izq.png");;
		}
		//EXPERIMENTAL!!!!!!!
		this->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(7.0), cocos2d::CallFunc::create(CC_CALLBACK_0(Arma::reactivaBitmasks, this)), NULL));
		//this->getPhysicsBody()->setVelocity(Vec2(-40, -40));
		//cuerpoFisicas->setAngularVelocity(-20);
		//this->runAction(FadeOut::create(1.5));
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
	//nueva->rutaSonido[0] = a->rutaSonido[0];
	a->GetRutaSonido() == nullptr ? CCLOG("ES NULL") : CCLOG("NO ES NULL");
	nueva->SetRutaSonido(a->GetRutaSonido());
	return nueva;
}

void Arma::PlayArmaSound()
{
	if(this->rutaSonido !=NULL)AudioEngine::play2d(rutaSonido->getCString(), false, 0.8);
}

void Arma::SetRutaSonido(cocos2d::String* c)
{
	rutaSonido=c;
	rutaSonido->retain();
}
cocos2d::String* Arma::GetRutaSonido()
{
	return rutaSonido;
}

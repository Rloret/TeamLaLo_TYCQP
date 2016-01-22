#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"
#include "Animacion.h"
#include"AudioEngine.h"

using namespace cocos2d::experimental;
USING_NS_CC;



ZerrinClass::ZerrinClass() {
	velocidad = 0.2;
	vida = 1;

	//gritos
	SonidosZerrin.pushBack(cocos2d::String::create("sounds/Zerrin_Uh_1.mp3"));
	SonidosZerrin.pushBack(cocos2d::String::create("sounds/Zerrin_Uh_2.mp3"));

	//hablar
	SonidosZerrin.pushBack(cocos2d::String::create("sounds/Zerrin_Habla.mp3"));
	SonidosZerrin.pushBack(cocos2d::String::create("sounds/zerrin_habla_1.mp3"));
	SonidosZerrin.pushBack(cocos2d::String::create("sounds/zerrin_habla_3.mp3"));


	this->retain();
	this->setName("Zerrin");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Zerrin/Zerrin_Spritesheet.plist");

}

ZerrinClass::~ZerrinClass()
{
}

ZerrinClass * ZerrinClass::create()
{
	ZerrinClass* zerrin = new ZerrinClass();
	zerrin->initWithFile("images/Zerrin/Senuelo.png");
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

void ZerrinClass::muestraDaño(int daño)
{
	auto dañoLabel = Label::createWithTTF(Global::getInstance()->letraPersonajes, (String::createWithFormat("- %d", daño)->getCString()));
	dañoLabel->setColor(Color3B::RED);
	dañoLabel->enableShadow();
	dañoLabel->retain();
	dañoLabel->setPosition(this->getParent()->getParent()->getPositionX() + 1024 / 2, this->getPositionY());
	this->getParent()->getParent()->addChild(dañoLabel,90);
	auto seq = Sequence::create(MoveTo::create(4.0, Vec2(this->getParent()->getParent()->getPositionX()+1024/2, this->getParent()->getContentSize().height+dañoLabel->getContentSize().height)),NULL);
	dañoLabel->runAction(seq);
}

void ZerrinClass::setCurrentAnimation(cocos2d::Node * anim)
{
	this->currentAnimation = (Sprite*)anim;
}

void ZerrinClass::accionColision(bool atras,int objeto, int tipoObjeto) // 1 armas 0 objetos
{
	int direccion;
	if (atras) {
		direccion = -1;
		this->setState(GOLPEADO_ATRAS);
	}
	else {
		direccion = 1;
		this->setState(GOLPEADO_ALANTE);
	}
	if (objeto == 0) {
		switch (tipoObjeto)
		{
		case 1:
			this->getPhysicsBody()->setVelocity(Vec2(-300, 200));
			this->getPhysicsBody()->setAngularVelocity(-30);
			break;
		case 2:
			this->getPhysicsBody()->setVelocity(Vec2(-100, 200));
			this->getPhysicsBody()->setAngularVelocity(-10);
			break;
		case 3:
			this->getPhysicsBody()->setVelocity(Vec2(0, 10));
			break;
		default:
			break;
		}
	}
	else if (objeto == 1) {
	
		switch (tipoObjeto)
		{
		case 2:
			this->getPhysicsBody()->setVelocity(Vec2(0, 200));
			break;
		case 3:

			this->getPhysicsBody()->setVelocity(Vec2(0, 100));
			break;
		case 4:
			this->getPhysicsBody()->setAngularVelocity(100 * direccion);
			this->getPhysicsBody()->setVelocity(Vec2(1000 * direccion, 400));
			break;
		case 5:
			this->getPhysicsBody()->setVelocity(Vec2(300*direccion, 200));
			this->getPhysicsBody()->setAngularVelocity(direccion *30);
			break;
		case 1:
		default:
			this->getPhysicsBody()->setVelocity(Vec2(0, 30));
			break;
		}
	}

}





void ZerrinClass::correr()
{
	estadoz = ENTRANDO;
	this->scheduleUpdate();
}


cocos2d::Vector<cocos2d::SpriteFrame*> ZerrinClass::getAnimation(const char * format, int count)
{
	auto spritecache = cocos2d::SpriteFrameCache::getInstance();
	cocos2d::Vector<cocos2d::SpriteFrame *> animFrames;
	char str[100];
	for (int i = 0; i < count; i++)
	{
		sprintf(str, format, i);
		auto framedeturno = spritecache->getSpriteFrameByName(str);
		animFrames.pushBack(framedeturno);
	}
	return animFrames;
}

void ZerrinClass::PlayZerrinSound(int inicio,int final)
{
	int ran=(int)random(inicio,final);
	CCLOG("random es %d", ran);
	auto s = SonidosZerrin.at(ran);
	AudioEngine::play2d(s->getCString(), false,1.0);
}



void ZerrinClass::setState(ZERRINFSM estado)
{
	if (estadoz == estado) return;
	estadoz = estado;
	Animacion* animacionDeTurno;
	switch (estadoz) {
	case SUELO:
		//CCLOG("SUELO");

		this->getPhysicsBody()->setContactTestBitmask(false);
		//CCLOG("me levantare y esas cosis y empiezo a correr");
		this->getPhysicsBody()->setVelocity(Vec2(0.0,0.0));
		this->getPhysicsBody()->setAngularVelocity(0);
		this->runAction(RotateTo::create(0.5, 0));
		this->getPhysicsBody()->setContactTestBitmask(true);
		setState(CORRIENDO);

		break;
	case IDLE:
		//CCLOG("IDLEEEEEEEEEEEEEEEEEEEE");
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation,true);
		}
		animacionDeTurno = new Animacion("Idle__%03d.png", 9, 1.0, "images/Zerrin/Zerrin_Spritesheet.plist",true);
		currentAnimation = animacionDeTurno->getAnimacionCreada();
		this->addChild(currentAnimation);
		break;
		
	case CORRIENDO:
		//CCLOG("CORRIENDOOOOOOOOOOOO");
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation, true);
		}
		animacionDeTurno = new Animacion("Walk__%03d.png", 9, 12 / 9, "images/Zerrin/Zerrin_Spritesheet.plist", true);
		currentAnimation = animacionDeTurno->getAnimacionCreada();
		this->addChild(currentAnimation);
		velocidad = 0.2;
		break;
	case HA_LLEGADO:
		setState(IDLE);
		((Nivel*)Director::getInstance()->getRunningScene())->goToGameOver(this);
	case SALIENDO:
		velocidad = 0.15;
		break;
	case GOLPEADO_ALANTE:
		//CCLOG("GOLPE ALANTE");
		Global::getInstance()->ellapsedTime = Global::getInstance()->currentTime;
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation, true);
		}
		animacionDeTurno = new Animacion("cannon__%03d.png", 9, 1.0, "images/Zerrin/Zerrin_Spritesheet.plist",true);
		currentAnimation = animacionDeTurno->getAnimacionCreada();
		this->addChild(currentAnimation);
		break;
	case GOLPEADO_ATRAS:
		//CCLOG("GOLPE ATRAS");
		Global::getInstance()->ellapsedTime = Global::getInstance()->currentTime;
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation, true);
		}
		animacionDeTurno = new Animacion("cannon__%03d.png", 9, 1.0, "images/Zerrin/Zerrin_Spritesheet.plist",true);
		currentAnimation = animacionDeTurno->getAnimacionCreada();
		this->addChild(currentAnimation);
		break;
	default:
		break;
	}
}

ZerrinClass::ZERRINFSM ZerrinClass::getEstado()
{
	return estadoz;
}

void ZerrinClass::update(float dt)
{
	Global::getInstance()->currentTime += dt;
	auto zbody = this->getPhysicsBody();
	//CCLOG("Velocidad: %f %f, momento: %f restitucion %f", zbody->getVelocity().x, zbody->getVelocity().y, zbody->getMoment(), zbody->getFirstShape()->getRestitution());
	float velocidadactual = velocidad * Director::getInstance()->getVisibleSize().width * dt;
	if (estadoz == ENTRANDO) {
		//CCLOG("ENTRANDO");
		velocidad = 0.15;
		velocidadactual = velocidad * Director::getInstance()->getVisibleSize().width * dt;
		posicionAnterior = this->getPositionX();
		this->setPositionX(this->getPositionX() + velocidadactual);
		if (this->getPositionX() >= 1024 / 4) {
			//CCLOG("lo pongo a correr");
			setState(CORRIENDO);
		}
		
	}
	if (estadoz == SALIENDO) {
		//CCLOG("SALIENDOIENDO");
		velocidad = 0.15;
		velocidadactual = velocidad * Director::getInstance()->getVisibleSize().width * dt;
		this->setPositionX(this->getPositionX() + velocidadactual);
		if ((this->getPositionX()) > 3072 - this->getBoundingBox().size.width){
			setState(HA_LLEGADO);
		}
	}
	if (estadoz==CORRIENDO /*|| estadoz==GOLPEADO_ALANTE*/) {
		//if (this->getPhysicsBody()->getVelocity().y > 0)this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		if ((this->getPositionX())  >  3072-1024/2.65 - this->getBoundingBox().size.width) {
			setState(SALIENDO);
		}
		else {
			posicionAnterior = this->getPositionX();
			this->setPositionX(this->getPositionX()+velocidadactual);
			((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidadactual);
			//CCLOG("me muevo");
			
		}
	}

	if (estadoz == GOLPEADO_ATRAS) {
		velocidad = (this->getPositionX() - this->posicionAnterior) / (dt*1000);
			velocidadactual = velocidad * Director::getInstance()->getVisibleSize().width * dt;
			((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidadactual);
			posicionAnterior = this->getPositionX();
			//CCLOG("rotation %f", this->getRotation());
		
	}
	if (estadoz == GOLPEADO_ALANTE) {
		velocidad = (this->getPositionX() - this->posicionAnterior) / (dt * 1000);
		velocidadactual = velocidad * Director::getInstance()->getVisibleSize().width * dt;
		((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidadactual);
		posicionAnterior = this->getPositionX();

	}



}
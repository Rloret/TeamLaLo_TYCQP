#include "ZerrinClass.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "Global.h"
#include "Nivel.h"

USING_NS_CC;



ZerrinClass::ZerrinClass() {
	velocidad = 0.2;
	vida = 1000;
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
	//Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	zerrin->initWithFile("images/Zerrin/Senuelo.png");
	//zerrin->initWithSpriteFrame(zerrin->creaAnimacionesZerrin()->getSpriteFrame());
	//zerrin->setVisible(false);
	
	
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

void ZerrinClass::muestraDa�o(int da�o)
{
	auto da�oLabel = Label::createWithSystemFont((String::createWithFormat("- %d",da�o)->getCString()), "Arial", 35);
	da�oLabel->setColor(Color3B::RED);
	da�oLabel->enableShadow();
	da�oLabel->retain();
	da�oLabel->setPosition(this->getParent()->getParent()->getPositionX() + 1024 / 2, this->getPositionY());
	this->getParent()->getParent()->addChild(da�oLabel,90);
	auto seq = Sequence::create(MoveTo::create(4.0, Vec2(this->getParent()->getParent()->getPositionX()+1024/2, this->getParent()->getContentSize().height+da�oLabel->getContentSize().height)),NULL);
	da�oLabel->runAction(seq);
}

void ZerrinClass::setCurrentAnimation(cocos2d::Node * anim)
{
	this->currentAnimation = (Sprite*)anim;
}

void ZerrinClass::accionColision(bool atras,int objeto, int tipoObjeto) // 1 armas 0 objetos
{
	//Si interesa a�adir un tipo y seg�n si es arma o objeto y su tipo  hacer x cosa
	if (atras) {
		this->setState(GOLPEADO_ATRAS);
	}
	else {
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
			CCLOG("HELLLO?");
			this->getPhysicsBody()->setVelocity(Vec2(0, 200));
			break;
		case 3:

			this->getPhysicsBody()->setVelocity(Vec2(0, 100));
			break;
		case 1:
		case 4:
		default:
			this->getPhysicsBody()->setVelocity(Vec2(0, 30));
			break;
		}
	}

}





void ZerrinClass::correr()
{
	//CCLOG("Voy a correr");
	estadoz = ENTRANDO;

	this->scheduleUpdate();
	//Global::getInstance()->nivel->scheduleUpdate();
}

cocos2d::Sprite* ZerrinClass::creaAnimacionesZerrin(const char * format, int count,float multiplicadorvelocidad)
{
	auto animFrames = this->getAnimation(format,count);
	auto sprite = cocos2d::Sprite::createWithSpriteFrame(animFrames.front());

	if (sprite == nullptr) CCLOG("Nulooo");
	else { this->addChild(sprite);
	}
	sprite->setAnchorPoint(Vec2(0, 0));

	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 1.0/(count*multiplicadorvelocidad));
	sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
	this->currentAnimation = sprite;
	return sprite;
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



void ZerrinClass::setState(ZERRINFSM estado)
{
	if (estadoz == estado) return;
	estadoz = estado;
	cocos2d::Sprite*zerrinani;
	switch (estadoz) {
	case SUELO:
		this->getPhysicsBody()->setContactTestBitmask(false);
		CCLOG("me levantare y esas cosis y empiezo a correr");
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
		currentAnimation =creaAnimacionesZerrin("Idle__%03d.png", 9,1.0);
		break;
		
	case CORRIENDO:
		//CCLOG("CORRIENDOOOOOOOOOOOO");
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation, true);
		}
		currentAnimation = creaAnimacionesZerrin("Walk__%03d.png", 9,12 / 9);
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
		currentAnimation = creaAnimacionesZerrin("cannon__%03d.png", 9, 1.0);
		break;
	case GOLPEADO_ATRAS:
		//CCLOG("GOLPE ATRAS");
		Global::getInstance()->ellapsedTime = Global::getInstance()->currentTime;
		if (currentAnimation != nullptr) {
			currentAnimation->stopAllActions();
			this->removeChild(currentAnimation, true);
		}
		currentAnimation = creaAnimacionesZerrin("cannon__%03d.png", 9, 1.0);
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
		if ((this->getPositionX())  >  3072-1024/2.65 - this->getBoundingBox().size.width) {
			setState(SALIENDO);

		}
		else {
			posicionAnterior = this->getPositionX();
			this->setPositionX(this->getPositionX()+velocidadactual);
			((Nivel*)(Director::getInstance()->getRunningScene()))->mueveFondo(velocidadactual);
			//CCLOG("CORRIENDO");
			
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
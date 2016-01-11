#include "KatahiClass.h"

USING_NS_CC;



KatahiClass::KatahiClass() {
	oro= 350;
	mechones = 10;
	//this->setPositionY(Director::getInstance()->getVisibleSize().height);
	//visibleSize = Director::getInstance()->getVisibleSize();
	this->retain();
}

KatahiClass::~KatahiClass()
{
}

KatahiClass * KatahiClass::create()
{
	KatahiClass* katahi = new KatahiClass();
	//Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	katahi->initWithFile("images/Katahi/katahi.PNG");

	return katahi;
}

void KatahiClass::modificaOro(int o)
{
	oro += o;
}

void KatahiClass::modificaMechones(int m)
{
	mechones += m;
}

int KatahiClass::getOro()
{
	return oro;
}

int KatahiClass::getMechones()
{
	return mechones;
}


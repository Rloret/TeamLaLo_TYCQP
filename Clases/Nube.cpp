#include "Nube.h"
#include "Nivel.h"
#include"Global.h"


USING_NS_CC;

Nube::Nube(int nube)
{
	String* filepath = String::createWithFormat("images/Nivel/nube_%d.png",nube);
	Texture2D* t = Director::getInstance()->getTextureCache()->addImage(filepath->getCString());
	this->initWithTexture(t);
}

Nube::~Nube()
{
}

Nube * Nube::create()
{
	return new Nube(random(1, 6));
}

void Nube::spawnNube(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto rand = random(this->getContentSize().height, this->getContentSize().height + 80);
	//this->setPosition(Point(visibleSize.width,rand));

	auto rand = random(5, 7);
	auto *move = (FiniteTimeAction *)MoveBy::create(rand, //mueve una nube hasta -width en un tiempo random
	Point(-visibleSize.width-this->getContentSize().width,0));
	move->retain();

	auto *seq = Sequence::create(move,
	CallFuncN::create(CC_CALLBACK_1(Nube::nubeDone, this)),	NULL);
	seq->retain();

	this->runAction(seq);
}

void Nube::nubeDone(Node* pSender) {
	Global::getInstance()->nivel->removeChild(pSender);
	this->stopAllActions();

}
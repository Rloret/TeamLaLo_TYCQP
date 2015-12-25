#include "Animacion.h"
#include "Arma.h"
#include "ZerrinClass.h"

USING_NS_CC;


Animacion::Animacion(const char * format, int count, float multiplicadorvelocidad, const std::string & plist,bool repeatForever)
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	this->repeatForever = repeatForever;
	auto spritecache = cocos2d::SpriteFrameCache::getInstance();
	cocos2d::Vector<cocos2d::SpriteFrame *> animFrames;
	char str[100];
	for (int i = 0; i < count; i++)
	{
		sprintf(str, format, i);
		auto framedeturno = spritecache->getSpriteFrameByName(str);
		animFrames.pushBack(framedeturno);
	}

	auto sprite = cocos2d::Sprite::createWithSpriteFrame(animFrames.front());

	sprite->setAnchorPoint(Vec2(0, 0));

	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 1.0 / (count*multiplicadorvelocidad));
	if (this->repeatForever)sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
	else {
		animation->setLoops(1);
		sprite->runAction(cocos2d::Sequence::create(cocos2d::Animate::create(animation), CallFunc::create(CC_CALLBACK_0(Animacion::onAnimationEnd, this)), NULL));
	}			
	animacionCreada = sprite;
	animacionCreada->setAnchorPoint(Vec2(0, 0));
}


Animacion::~Animacion()
{
}

cocos2d::Vector<cocos2d::SpriteFrame*> Animacion::getFramesAnimation(const char * format, int count)
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

cocos2d::Sprite * Animacion::getAnimacionCreada()
{
	return animacionCreada;
}

void Animacion::onAnimationEnd()
{	
	animacionCreada->stopAllActions();
	animacionCreada->setVisible(false);
}

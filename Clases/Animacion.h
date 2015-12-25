#pragma once
#ifndef __ANIMACION_H__
#define __ANIMACION_H__

#include "cocos2d.h"
class Animacion
{
private:
	cocos2d::Sprite* animacionCreada;
	bool repeatForever;
public:
	Animacion(const char * format, int count, float multiplicadorvelocidad,const std::string & plist,bool repeatForever);
	~Animacion();
	cocos2d::Vector<cocos2d::SpriteFrame *> getFramesAnimation(const char * format, int count);
	cocos2d::Sprite* getAnimacionCreada();
	void onAnimationEnd();
};

#endif //ARMA
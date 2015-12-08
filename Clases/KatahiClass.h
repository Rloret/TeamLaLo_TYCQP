#pragma once
#ifndef __KATAHI_CLASS_H__
#define __KATAHI_CLASS_H__
#include "cocos2d.h"



class KatahiClass :public cocos2d::Sprite
{
public:

	KatahiClass();
	~KatahiClass();
	static KatahiClass* create();

	void modificaOro(int o);
	void modificaMechones(int m);
	int getOro();
	int getMechones();
	

	cocos2d::Sprite aspecto;

private:
	int oro;
	int mechones;
};

#endif
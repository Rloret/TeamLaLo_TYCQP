#ifndef __NUBE_H__
#define __NUBE_H__
#include "cocos2d.h"



class Nube : public cocos2d::Sprite
{
public:
	Nube(int nube);
	~Nube();
	static Nube* create();
	void spawnNube(float dt);
	void nubeDone(Node* pSender);

private:

};

#endif //Nube



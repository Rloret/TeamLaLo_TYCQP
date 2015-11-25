#ifndef __Vestuario_SCENE_H__
#define __Vestuario_SCENE_H__
#include "cocos2d.h"

class VestuarioScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

 
	void returnToScene(Ref *pSender);


	// implement the "static create()" method manually
	CREATE_FUNC(VestuarioScene);
};

#endif  

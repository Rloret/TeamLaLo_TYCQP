
#ifndef __Creditos_SCENE_H__
#define __Creditos_SCENE_H__
#include "cocos2d.h"

class CreditosScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

 
	void goToMainMenuScene(Ref *pSender);


	// implement the "static create()" method manually
	CREATE_FUNC(CreditosScene);
};

#endif  

#ifndef __Ajustes_SCENE_H__
#define __Ajustes_SCENE_H__
#include "cocos2d.h"

class AjustesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void goToMainMenuScene(Ref *pSender);



	// implement the "static create()" method manually
	CREATE_FUNC(AjustesScene);
};

#endif  

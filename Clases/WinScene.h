#ifndef __WinScene_SCENE_H__
#define __WinScene_SCENE_H__
#include "cocos2d.h"















class WinScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void goToMenuStartScene(Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(WinScene);
};

#endif  //winscene
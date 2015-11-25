#ifndef __Pause_SCENE_H__
#define __Pause_SCENE_H__
#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
 
	void resumeGameScene(Ref *pSender);
	void goToMainMenuScene(Ref *pSender);
	void goToLogrosScene(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);
};

#endif  

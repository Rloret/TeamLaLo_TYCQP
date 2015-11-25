#ifndef __Logros_SCENE_H__
#define __Logros_SCENE_H__
#include "cocos2d.h"

class LogrosScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

 
	void returnToScene(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(LogrosScene);


};

#endif  

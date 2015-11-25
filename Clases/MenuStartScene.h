#ifndef __MenuStart_SCENE_H__
#define __MenuStart_SCENE_H__
#include "cocos2d.h"

class MenuStartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	int prueba;
 
	void goToMainMenuScene(Ref *pSender);
	void goToLogrosScene(Ref* pSender);
	void goToVestuarioScene(Ref *pSender);
	void goToTiendaScene(Ref *pSender);
	void goToLevelsScene(Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MenuStartScene);
};

#endif  

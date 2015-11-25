#ifndef __Tienda_SCENE_H__
#define __Tienda_SCENE_H__
#include "cocos2d.h"
#include "Arma.h"

class TiendaScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
 
	void returnToScene(Ref *pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(TiendaScene);
private:

	void colocaArmasTotales();
	//virtual void onEnterTransitionDidFinish();
};

#endif  

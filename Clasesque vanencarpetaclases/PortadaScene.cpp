#include "PortadaScene.h"
#include"MainMenuScene.h"

USING_NS_CC;

Scene* PortadaScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PortadaScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PortadaScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto Portada = Sprite::create("images/Portada/portada_good_res.png");
	Portada->setAnchorPoint(Vec2(0, 0));
	Portada->setOpacity(0);
	this->addChild(Portada);
	Portada->runAction(Sequence::create(FadeIn::create(2), DelayTime::create(2), FadeOut::create(2), NULL));
	this->runAction(Sequence::create(DelayTime::create(6.0),CallFunc::create(CC_CALLBACK_0(PortadaScene::goToMainMenuScene, this)), NULL));
	Size visibleSize = Director::getInstance()->getVisibleSize();


}


void PortadaScene::goToMainMenuScene() {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0,scene));

}
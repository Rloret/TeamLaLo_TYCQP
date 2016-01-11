#include "AjustesScene.h"
#include"MainMenuScene.h"

USING_NS_CC;

Scene* AjustesScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AjustesScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AjustesScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	
	//menu
	auto back_btn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(AjustesScene::goToMainMenuScene, this));
	auto menu = Menu::create(back_btn, NULL);
	menu->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(menu, 1);


	//fondo
	auto background = Sprite::create("images/AjustesScene/enconstruccion.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	auto prompt = cocos2d::Sprite::create("images/AjustesScene/prompt.png");
	prompt->setPosition(Point(80,480));
	addChild(prompt, 1);

	prompt->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5),FadeIn::create(0.5),NULL)));

	return true;
}


void AjustesScene::goToMainMenuScene(Ref *pSender){

	Director::getInstance()->popScene();

}
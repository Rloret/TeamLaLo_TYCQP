
#include "LogrosScene.h"


USING_NS_CC;

Scene* LogrosScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = LogrosScene ::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogrosScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();


	//menu
	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha.png",
		CC_CALLBACK_1(LogrosScene::returnToScene, this));
	auto menu = Menu::create(backBtn, NULL);
	menu->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(menu, 2);

	//Fondo
	auto background = Sprite::create("images/AjustesScene/enconstruccion.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	auto prompt = cocos2d::Sprite::create("images/AjustesScene/prompt.png");
	prompt->setPosition(Point(80, 480));
	addChild(prompt, 1);
	prompt->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5), FadeIn::create(0.5), NULL)));

	
	return true;
}



void LogrosScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
}



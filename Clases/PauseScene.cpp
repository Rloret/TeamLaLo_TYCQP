#include "PauseScene.h"
#include "proj.win32\LogrosScene.h"
#include"MainMenuScene.h"
#include"Global.h"
#include"Nivel.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//menu
	auto backBtn = MenuItemImage::create("images/PauseScene/back_btn.png", "images/VestuarioScene/back_btn.png",
		CC_CALLBACK_1(PauseScene::resumeGameScene, this));

	auto menuBtn = MenuItemImage::create("images/PauseScene/back_btn.png", "images/VestuarioScene/back_btn.png",
		CC_CALLBACK_1(PauseScene::goToMainMenuScene, this));
	//menuBtn->setColor(Color3B(100,40,2));

	auto menu = Menu::create(backBtn,menuBtn, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(menu, 2);


	//Fondo
	auto background = Sprite::create("images/PauseScene/fondo_VestuarioScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	return true;
}


void PauseScene::resumeGameScene(Ref *pSender){

	Director::getInstance()->popScene();
}


void PauseScene::goToMainMenuScene(Ref *pSender){
	CCLOG("me voy a mainmenuScene");
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Global::getInstance()->nivel->removeAllChildren();
	
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	
}


void PauseScene::goToLogrosScene(Ref *pSender){

	auto scene = LogrosScene::createScene();

	Director::getInstance()->replaceScene(scene);
}
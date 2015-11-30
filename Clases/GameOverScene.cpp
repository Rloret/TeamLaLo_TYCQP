#include "GameOverScene.h"
#include"Global.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto menuBtn = MenuItemImage::create("images/PauseScene/back_btn.png", "images/VestuarioScene/back_btn.png",
		CC_CALLBACK_1(GameOverScene::goToMenuStartScene, this));
	

	auto menu = Menu::create( menuBtn, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(menu, 2);

	//Fondo
	auto background = Sprite::create("images/MainMenuScene/fondo_mainMenu.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	return true;
}

void GameOverScene::goToMenuStartScene(Ref * pSender)
{
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Global::getInstance()->nivel->removeAllChildren();

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}



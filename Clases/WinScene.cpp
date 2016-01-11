#include "WinScene.h"
#include"Global.h"
#include "Nivel.h"
USING_NS_CC;

Scene* WinScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto menuBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha.png",
		CC_CALLBACK_1(WinScene::goToMenuStartScene, this));


	auto menu = Menu::create(menuBtn, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(menu, 2);

	auto goLabel = Label::createWithSystemFont("HAS GANADO.", "Arial", 60);
	goLabel->setColor(Color3B::GREEN);
	goLabel->enableShadow();
	goLabel->setPosition(Global::getInstance()->visibleSize.width / 2, Global::getInstance()->visibleSize.height / 2 + goLabel->getContentSize().height * 2);

	this->addChild(goLabel, 4);
	//Fondo
	auto background = Sprite::create("images/MainMenuScene/fondo_mainMenu.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	return true;
}

void WinScene::goToMenuStartScene(Ref * pSender)
{
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Director::getInstance()->popToRootScene();
}



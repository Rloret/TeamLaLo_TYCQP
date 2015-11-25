#include "MenuStartScene.h"
#include "MainMenuScene.h"
#include "proj.win32\LogrosScene.h"
#include "proj.win32\VestuarioScene.h"
#include"proj.win32\TiendaScene.h"
#include"proj.win32\LevelsMenuScene.h"
#include "proj.win32\Arma.h"
#include "proj.win32\ObjetoEscenario.h"
#include "proj.win32\Global.h"

USING_NS_CC;

Scene* MenuStartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuStartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuStartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Menu
	
	auto logrosBtn = MenuItemImage::create("images/MenuStartScene/logros_btn.png", "images/MenuStartScene/logros_btn.png",
		CC_CALLBACK_1(MenuStartScene::goToLogrosScene, this));
	auto vestuarioBtn = MenuItemImage::create("images/MenuStartScene/vestuario_btn.png", "images/MenuStartScene/vestuario_btn.png",
		CC_CALLBACK_1(MenuStartScene::goToVestuarioScene, this));
	auto tiendaBtn = MenuItemImage::create("images/MenuStartScene/tienda_btn.png", "images/MenuStartScene/tienda_btn.png",
		CC_CALLBACK_1(MenuStartScene::goToTiendaScene, this));
	auto levelsBtn = MenuItemImage::create("images/MenuStartScene/levels_btn.png", "images/MenuStartScene/levels_btn.png",
		CC_CALLBACK_1(MenuStartScene::goToLevelsScene, this));
	//Los listener revientan en funcion de las transiciones, como de momento no vamos a realizar nada con los listenrs y este fragmento de codigo era una prueba
	//se comenta y se debugueará más adelante


	auto menu1 = Menu::create( logrosBtn,vestuarioBtn,tiendaBtn,levelsBtn,NULL);
	menu1->alignItemsVertically();
	addChild(menu1, 1);
	
	auto backBtn = MenuItemImage::create("images/MenuStartScene/back_btn.png", "images/MenuStartScene/back_btn.png",
			CC_CALLBACK_1(MenuStartScene::goToMainMenuScene,this));
	auto menu2 = Menu::create(backBtn,NULL);
	menu2->setPosition(Point(visibleSize.width - 20, visibleSize.height - 20));
	addChild(menu2, 2);
	



	//Fondo
	auto background = Sprite::create("images/MenuStartScene/fondo_MenuStartScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	return true;
}


void MenuStartScene::goToMainMenuScene(Ref *pSender){

	Director::getInstance()->popScene();

}


void MenuStartScene::goToLogrosScene(Ref *pSender){

	auto scene = LogrosScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MenuStartScene::goToVestuarioScene(Ref *pSender){

	auto scene = VestuarioScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MenuStartScene::goToTiendaScene(Ref *pSender){

	auto scene = TiendaScene::createScene();
	Director::getInstance()->pushScene(scene);
	//Director::getInstance()->pushScene((Scene*)Global::getInstance()->tienda);
}


void MenuStartScene::goToLevelsScene(Ref *pSender){

	//Scene* escena= Global::getInstance()->levelsMenuScene;
	Director::getInstance()->pushScene((Scene*)Global::getInstance()->levelsMenuScene);
	/*auto scene = LevelsMenuScene::createScene();
	Director::getInstance()->pushScene(scene);*/
	

}
#include "MenuStartScene.h"
#include "MainMenuScene.h"
#include "proj.win32\LogrosScene.h"
#include "proj.win32\VestuarioScene.h"
#include"proj.win32\TiendaScene.h"
#include"proj.win32\LevelsMenuScene.h"
#include "proj.win32\Arma.h"
#include "proj.win32\ObjetoEscenario.h"
#include "proj.win32\Global.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;
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
	
	auto logrosBtn = MenuItemImage::create("images/MenuStartScene/logros_btn.png", "images/MenuStartScene/logros_Btn_Idle.png",
		CC_CALLBACK_1(MenuStartScene::goToLogrosScene, this));
	auto vestuarioBtn = MenuItemImage::create("images/MenuStartScene/vestuario_btn.png", "images/MenuStartScene/vestuario_Btn_Idle.png",
		CC_CALLBACK_1(MenuStartScene::goToVestuarioScene, this));
	auto tiendaBtn = MenuItemImage::create("images/MenuStartScene/tienda_btn.png", "images/MenuStartScene/tienda_Btn_Idle.png",
		CC_CALLBACK_1(MenuStartScene::goToTiendaScene, this));
	auto levelsBtn = MenuItemImage::create("images/MenuStartScene/niveles_Btn.png", "images/MenuStartScene/niveles_Btn_Idle.png",
		CC_CALLBACK_1(MenuStartScene::goToLevelsScene, this));


	auto menu1 = Menu::create( logrosBtn,NULL);
	addChild(menu1, 1);
	menu1->setPosition(Point(menu1->getContentSize().width/2-60,512));
	auto menu2 = Menu::create(vestuarioBtn, NULL);
	addChild(menu2, 1);
	menu2->setPosition(Point(90 + menu2->getContentSize().width / 2,363));
	auto menu3 = Menu::create(tiendaBtn, NULL);
	addChild(menu3, 1);
	menu3->setPosition(Point( menu3->getContentSize().width / 2,208));
	auto menu4 = Menu::create(levelsBtn, NULL);
	addChild(menu4, 1);
	menu4->setPosition(Point(50 + menu4->getContentSize().width / 2,65));


	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
			CC_CALLBACK_1(MenuStartScene::goToMainMenuScene,this));
	auto menu6 = Menu::create(backBtn,NULL);
	menu6->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(menu6, 2);
	

	//Fondo
	auto background = Sprite::create("images/MenuStartScene/fondo_mainMenu.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	

	auto b2 = Sprite::create("images/MenuStartScene/menustartscene_torres.png");
	b2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(b2,1);

	auto sombra = Sprite::create("images/MenuStartScene/s.png");
	sombra->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(sombra, 2);
	
	sombra->runAction(RepeatForever::create(Sequence::create(FadeTo::create(4, 80), FadeTo::create(4, 255),NULL)));

	songMenuStartID=AudioEngine::play2d("sounds/MenuStartScene_Ambiente.mp3",false,0.0);
	AudioEngine::pause(songMenuStartID);
	return true;
}


void MenuStartScene::goToMainMenuScene(Ref *pSender){
	AudioEngine::stopAll();
	Director::getInstance()->popScene();
	AudioEngine::play2d("sounds/Back_Btn.mp3", false, 0.8);
	
}


void MenuStartScene::goToLogrosScene(Ref *pSender){
	AudioEngine::stopAll();

	AudioEngine::play2d("sounds/Botones_MenuStartScene.mp3", false, 0.9);

	auto scene = LogrosScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MenuStartScene::goToVestuarioScene(Ref *pSender){
	AudioEngine::stopAll();

	AudioEngine::play2d("sounds/Botones_MenuStartScene.mp3", false, 0.9);

	auto scene = VestuarioScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MenuStartScene::goToTiendaScene(Ref *pSender){
	AudioEngine::stopAll();

	AudioEngine::play2d("sounds/Botones_MenuStartScene.mp3", false, 0.9);

	auto scene = TiendaScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MenuStartScene::goToLevelsScene(Ref *pSender){
	AudioEngine::stopAll();

	AudioEngine::play2d("sounds/Botones_MenuStartScene.mp3", false, 0.9);

	Director::getInstance()->pushScene(Global::getInstance()->levelsMenuScene);

}

void MenuStartScene::onEnterTransitionDidFinish()
{
	AudioEngine::setVolume(songMenuStartID, 1.0);
	AudioEngine::resume(songMenuStartID);
}

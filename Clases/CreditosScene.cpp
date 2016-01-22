#include "CreditosScene.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

USING_NS_CC;

Scene* CreditosScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CreditosScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CreditosScene::init()
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
			CC_CALLBACK_1(CreditosScene::goToMainMenuScene,this));
	auto menu = Menu::create(back_btn, NULL);
	menu->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(menu, 1);

	//fondo
	auto background = Sprite::create("images/CreditosScene/fondo_CreditosScene.png");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(background, 0);

	AudioEngine::play2d("sounds/Under_Development.mp3", true, 1.0);

	return true;
}

void CreditosScene::goToMainMenuScene(Ref *pSender){
	AudioEngine::stopAll();
	AudioEngine::play2d("sounds/Back_Btn.mp3", false,1.0);

	Director::getInstance()->popScene();
}

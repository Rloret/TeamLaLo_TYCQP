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
	auto back_btn = MenuItemImage::create("images/AjustesScene/back_btn.png", "images/AjustesScene/back_btn.png",
		CC_CALLBACK_1(AjustesScene::goToMainMenuScene, this));
	auto menu = Menu::create(back_btn, NULL);

	addChild(menu, 1);


	//fondo
	auto background = Sprite::create("images/AjustesScene/fondo_AjustesScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	return true;
}


void AjustesScene::goToMainMenuScene(Ref *pSender){

	Director::getInstance()->popScene();

}
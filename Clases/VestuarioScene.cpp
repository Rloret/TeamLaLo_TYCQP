#include "VestuarioScene.h"
USING_NS_CC;

Scene* VestuarioScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = VestuarioScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool VestuarioScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//menu
	auto backBtn = MenuItemImage::create("images/VestuarioScene/back_btn.png", "images/VestuarioScene/back_btn.png",
		CC_CALLBACK_1(VestuarioScene::returnToScene, this));
	auto menu = Menu::create(backBtn, NULL);
	menu->setPosition(Point(visibleSize.width - 20, visibleSize.height - 20));
	addChild(menu, 2);


	//Fondo
	auto background = Sprite::create("images/VestuarioScene/fondo_VestuarioScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	return true;
}


void VestuarioScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
}
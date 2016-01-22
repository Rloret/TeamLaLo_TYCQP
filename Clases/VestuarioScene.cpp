#include "VestuarioScene.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;
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
	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(VestuarioScene::returnToScene, this));
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

	
	AudioEngine::play2d("sounds/Under_Development.mp3", true, 1.0);

	return true;
}


void VestuarioScene::returnToScene(Ref *pSender){
	AudioEngine::stopAll();
	AudioEngine::play2d("sounds/Back_Btn.mp3", false, 1.0);
	Director::getInstance()->popScene();
}
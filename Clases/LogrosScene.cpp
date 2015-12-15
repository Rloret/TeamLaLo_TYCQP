
#include "LogrosScene.h"


USING_NS_CC;

Scene* LogrosScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = LogrosScene ::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

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
	auto backBtn = MenuItemImage::create("images/LogrosScene/back_btn.png", "images/LogrosScene/back_btn.png",
		CC_CALLBACK_1(LogrosScene::returnToScene, this));
	auto menu = Menu::create(backBtn, NULL);
	menu->setPosition(Point(visibleSize.width - 20, visibleSize.height - 20));
	addChild(menu, 2);

	auto pruebaZ = cocos2d::Sprite::create("images/LogrosScene/fondo_LogrosScene.png");
	pruebaZ->setPhysicsBody(PhysicsBody::createCircle(pruebaZ->getBoundingBox().size.width / 2));
	pruebaZ->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(pruebaZ, 0);


	//Fondo
	/*auto background = Sprite::create("images/LogrosScene/fondo_LogrosScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);*/

	return true;
}



void LogrosScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
}

void LogrosScene::setPhysicsWorld(cocos2d::PhysicsWorld * world)
{

		nivelPhysics = world;
		nivelPhysics->setGravity(Vec2(0, -9.8));
}

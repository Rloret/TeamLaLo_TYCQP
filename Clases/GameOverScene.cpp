#include "GameOverScene.h"
#include"Global.h"
#include "Nivel.h"
#include "Animacion.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

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

	auto menuBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(GameOverScene::goToMenuStartScene, this));
	

	auto menu = Menu::create( menuBtn, NULL);
	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, 50));
	addChild(menu, 2);

	//Fondo
	auto background = Sprite::create("images/GameOverScene/gameover_fondo.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	
	auto KatahiRaptadaAnim = new Animacion("secuestro_%03d.png", 16, 0.8, "images/GameOverScene/ZerrinyKatahi.plist", true);
	auto KatahiRaptada = KatahiRaptadaAnim->getAnimacionCreada();
	KatahiRaptada->setPosition(0, 0);
	this->addChild(KatahiRaptada, 1);
	KatahiRaptada->runAction(Sequence::create(MoveBy::create(5,Vec2(1300,0)),CallFuncN::create(CC_CALLBACK_1(GameOverScene::borraObjetoTemporal,this)),NULL));

	auto sombra = Sprite::create("images/GameOverScene/gameover_fondo_sombra.png");
	sombra->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(sombra, 2);
	sombra->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.5, 255 / 2), FadeTo::create(2.5, 255), NULL)));

	AudioEngine::stopAll();
	
	return true;
}

void GameOverScene::goToMenuStartScene(Ref * pSender)
{
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Director::getInstance()->popToRootScene();
}

void GameOverScene::borraObjetoTemporal(Node * Sender)
{
	Sender->removeFromParentAndCleanup(true);
}



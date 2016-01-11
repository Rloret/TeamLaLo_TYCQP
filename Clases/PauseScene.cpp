#include "PauseScene.h"
#include "proj.win32\LogrosScene.h"
#include"MainMenuScene.h"
#include"Global.h"
#include"Nivel.h"
#include "Animacion.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(PauseScene::resumeGameScene, this));

	auto menuBtn = MenuItemImage::create( "images/PauseScene/home_idle.png", "images/PauseScene/home_idle_pressed.png",
		CC_CALLBACK_1(PauseScene::goToMainMenuScene, this));

	auto menu = Menu::create(backBtn,menuBtn, NULL);
	menu->alignItemsHorizontallyWithPadding(visibleSize.width / 1.5);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height-100));
	addChild(menu, 2);
	
	auto KatahiAnim = new Animacion("katahipause_%03d.png", 7, 1, "images/GameOverScene/ZerrinyKatahi.plist", true);
	auto KatahiPause = KatahiAnim->getAnimacionCreada();
	KatahiPause->setPosition(0, 0);
	this->addChild(KatahiPause, 7);
	
	
	auto animacionZerrin = new Animacion("Walk__%03d.png", 9, 12 / 9, "images/Zerrin/Zerrin_Spritesheet.plist", true);
	auto zerrin = animacionZerrin->getAnimacionCreada();
	zerrin->setScale(KatahiPause->getBoundingBox().size.height/zerrin->getBoundingBox().size.height*0.8);
	
	this->addChild(zerrin, 6);

	KatahiPause->setPosition(-300,0);
	zerrin->setPosition(-400, 85);
	auto background = Sprite::create("images/PauseScene/fondo_pause.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	KatahiPause->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5, Vec2(100, 0)),CallFunc::create(CC_CALLBACK_0(PauseScene::activaZerrin,this,zerrin)), MoveTo::create(3, Vec2(1324, 0)),
		ScaleBy::create(0, -1, 1), MoveTo::create(3, Vec2(-300, 0)),
		ScaleBy::create(0, -1, 1)
		, NULL)));


	auto sombra = Sprite::create("images/PauseScene/foco_pause.png");
	sombra->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(sombra, 2);
	sombra->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.5, 255 / 2), FadeTo::create(2.5, 255), NULL)));

	return true;
}


void PauseScene::resumeGameScene(Ref *pSender){

	Director::getInstance()->popScene();
}


void PauseScene::goToMainMenuScene(Ref *pSender){
	CCLOG("me voy a mainmenuScene");
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Director::getInstance()->popToRootScene();

	
}


void PauseScene::goToLogrosScene(Ref *pSender){

	auto scene = LogrosScene::createScene();

	Director::getInstance()->replaceScene(scene);
}

void PauseScene::activaZerrin(Node * sender)
{
	if (contador < 1) {
		sender->runAction(RepeatForever::create(Sequence::create(MoveTo::create(3.5, Vec2(1324, 85)),
			ScaleBy::create(0, -1, 1), MoveTo::create(3, Vec2(-300, 85)),
			ScaleBy::create(0, -1, 1)
			, NULL)));
	}
	contador += 1;
}

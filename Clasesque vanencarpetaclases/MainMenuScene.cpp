#include "MainMenuScene.h"
#include "proj.win32/CreditosScene.h"
#include"proj.win32/AjustesScene.h"
#include "proj.win32/MenuStartScene.h"
#include "ui\UIButton.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    

	//Menu
	
	auto creditosBtn = MenuItemImage::create("images/MainMenuScene/CreditosBtn.png", "images/MainMenuScene/CreditosBtn.png",
			CC_CALLBACK_1(MainMenuScene::goToCreditos,this));
	auto ajustesBtn = MenuItemImage::create("images/MainMenuScene/AjustesBtn.png", "images/MainMenuScene/AjustesBtn.png",
			CC_CALLBACK_1(MainMenuScene::goToAjustes,this));
	auto startBtn = MenuItemImage::create("images/MainMenuScene/PlayBtn.png", "images/MainMenuScene/PlayBtn.png",
			CC_CALLBACK_1(MainMenuScene::goToMenuStart,this));
	startBtn->setPosition(Vec2(-visibleSize.width / 2+ startBtn->getBoundingBox().size.width/2, -visibleSize.height / 2 + startBtn->getBoundingBox().size.height/2));
	ajustesBtn->setPosition(Vec2(-visibleSize.width / 2 + ajustesBtn->getBoundingBox().size.width / 2, visibleSize.height / 2 - ajustesBtn->getBoundingBox().size.height/2));
	creditosBtn->setPosition(Vec2(visibleSize.width / 2 - creditosBtn->getBoundingBox().size.width / 2, -visibleSize.height / 2 + creditosBtn->getBoundingBox().size.height / 2));
	auto menu1 = Menu::create(creditosBtn, NULL);
	auto menu2 = Menu::create(startBtn, NULL);
	auto menu3 = Menu::create(ajustesBtn, NULL);

	addChild(menu2, 2);
	addChild(menu3, 2);
	addChild(menu1, 2);
	Luces_1 = Sprite::create("images/MainMenuScene/luces_1.png");
	Luces_2 = Sprite::create("images/MainMenuScene/luces_2.png");
	Luces_1->setPosition(Vec2(visibleSize.width-Luces_1->getBoundingBox().size.width*3/4, visibleSize.height - Luces_1->getBoundingBox().size.height/2));
	Luces_1->setVisible(false);

	Luces_2->setPosition(Vec2(visibleSize.width - Luces_2->getBoundingBox().size.width*3/4, visibleSize.height - Luces_2->getBoundingBox().size.height/2));
	Luces_2->setVisible(false);
	this->addChild(Luces_1, 2);
	this->addChild(Luces_2, 2);
	cocos2d::CallFunc* accion;
	cocos2d::RepeatForever* secuencia;

	accion = CallFunc::create(CC_CALLBACK_0(MainMenuScene::intervalo, this));//funcion del negativo;
	secuencia = RepeatForever::create(Sequence::create(DelayTime::create(0.2), accion, nullptr));

	//Fondo
	auto background = Sprite::create("images/MainMenuScene/fondo_mainMenu.png");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(background, 0);
	background->runAction(secuencia);
	background->runAction(RepeatForever::create(Sequence::create(DelayTime::create(cocos2d::random(5,15)/10.0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::generaNota,this)),nullptr)));

	songMainMenuID=AudioEngine::play2d("sounds/MenuStartScene.mp3", true, 0.0);
	AudioEngine::pause(songMainMenuID);

	return true;
}
void MainMenuScene::goToCreditos(Ref *pSender){
	AudioEngine::pause(songMainMenuID);
	AudioEngine::play2d("sounds/Boton_MainMenuScene_1.mp3", false, 0.8);
	auto scene = CreditosScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MainMenuScene::goToAjustes(Ref *pSender){
	AudioEngine::pause(songMainMenuID);
	AudioEngine::play2d("sounds/Boton_MainMenuScene_1.mp3", false, 0.8);
	auto scene = AjustesScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MainMenuScene::goToMenuStart(Ref *pSender){
	AudioEngine::pause(songMainMenuID);
	AudioEngine::play2d("sounds/Boton_MainMenuScene_2.mp3", false, 0.8);
	auto scene = MenuStartScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MainMenuScene::intervalo()
{
	this->parpadeo *= -1;
	if (parpadeo < 1) {
		Luces_1->setVisible(true);
		Luces_2->setVisible(false);
	}
	else {
		Luces_1->setVisible(false);
		Luces_2->setVisible(true);
	}
}

void MainMenuScene::generaNota()
{
	cocos2d::String* notaString = String::createWithFormat("images/MainMenuScene/nota_%d.png",cocos2d::random(1,3));
	auto nota = Sprite::create(notaString->getCString());
	this->addChild(nota, 3);
	nota->setPosition(650+nota->getContentSize().width,400);
	nota->runAction(MoveTo::create(random(30, 40) / 10.0, Vec2(1024+nota->getContentSize().width*2,768+nota->getContentSize().height*2)));
}

void MainMenuScene::onEnterTransitionDidFinish()
{
	AudioEngine::setVolume(songMainMenuID ,1.0);
	AudioEngine::resume(songMainMenuID);
	
}

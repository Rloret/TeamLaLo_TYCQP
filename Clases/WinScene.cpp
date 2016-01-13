#include "WinScene.h"
#include"Global.h"
#include "Nivel.h"
#include "AudioEngine.h"
#include "Animacion.h"
using namespace cocos2d::experimental;

USING_NS_CC;

Scene* WinScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Fondo
	auto background = Sprite::create("images/Nivel/Escenarios/Castillo_Fondo.png");
	background->setAnchorPoint(Vec2(1, 0));
	background->setPosition(Point(visibleSize.width, 0));
	auto zerrinAnimacion = new Animacion("cannon__%03d.png", 9, 1.0, "images/Zerrin/Zerrin_Spritesheet.plist", true);
	auto zerrinVolando = zerrinAnimacion->getAnimacionCreada();
	zerrinVolando->setPosition(Vec2(visibleSize.width - zerrinVolando->getBoundingBox().size.width, zerrinVolando->getBoundingBox().size.height));
	addChild(background, 0);
	addChild(zerrinVolando, 1);
	
	auto secuencia =Sequence::create(MoveTo::create(4,Vec2(zerrinVolando->getBoundingBox().size.width,visibleSize.height-zerrinVolando->getBoundingBox().size.height)),
		CallFuncN::create(CC_CALLBACK_1(WinScene::muestraMenu,this)),NULL);
	zerrinVolando->runAction(secuencia);
	AudioEngine::stopAll();
	return true;
}

void WinScene::goToMenuStartScene(Ref * pSender)
{
	Global::getInstance()->vaciaArmasNivel();
	Global::getInstance()->juegoEnCurso = false;
	Director::getInstance()->popToRootScene();
}

void WinScene::muestraMenu(Node * sender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto destello = Sprite::create("images/VFX/Destello_1.png");
	this->addChild(destello, 4);
	destello->setPosition(Vec2(sender->getPositionX()+sender->getBoundingBox().size.width/2,sender->getPositionY()+sender->getBoundingBox().size.height/2));
	destello->setColor(Color3B::ORANGE);
	destello->setOpacity(255);
	destello->setScale(sender->getBoundingBox().size.height / destello->getBoundingBox().size.height);
	auto secuencia1 = Sequence::create(FadeTo::create(0.4, 0.8 / 255), FadeOut::create(0.2), NULL);
	auto accion = ScaleBy::create(0.3, 1.5);
	//destello->runAction(Sequence::create(FadeTo::create(0.2,0.8/255),FadeOut::create(0.1),NULL));
	destello->runAction(Spawn::createWithTwoActions(secuencia1, accion));
	sender->removeFromParent();
	
	TTFConfig letraGotica;
	letraGotica.fontFilePath = "fonts/OldLondon.ttf";
	letraGotica.fontSize = 60;
	letraGotica.glyphs = GlyphCollection::DYNAMIC;
	letraGotica.outlineSize = 0;
	letraGotica.customGlyphs = nullptr;
	letraGotica.distanceFieldEnabled = false;
	//auto fraseDelMenu = String::createWithFormat("Parece que mientras\nvapuleabas a Zerrin\nse le han caido:\n\n     %d oros.\n     %d mechones.\n\nEl mayordomo
	//los ha recogido por ti.",Global::getInstance()->RecompensaOro, Global::getInstance()->RecompensaMechones);
	
	auto cartel = Sprite::create("images/WinScene/cartel_vacio.png");
	cartel->setAnchorPoint(Vec2(0.5, 0.5));
	cartel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cartel,2);
	auto FraseMenu = Label::createWithTTF(letraGotica,/*fraseDelMenu*/ "Parece que mientras\n vapuleabas a Zerrin\nse le han caido\nasd oros\nasd mechones\ntu criado los\n ha recogido por ti.", cocos2d::CCTextAlignment::CENTER);
	FraseMenu->setAnchorPoint(Vec2(0.5, 0.5));
	FraseMenu->setColor(Color3B(188, 116, 11));
	bool entra = false;
	while (!entra) {
		if (FraseMenu->getBoundingBox().size.width > cartel->getBoundingBox().size.width-20 || FraseMenu->getBoundingBox().size.height > cartel->getBoundingBox().size.height-20) {
			FraseMenu->setScale(FraseMenu->getScale() - 0.01);
		}
		else entra = true;
	}
	FraseMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(FraseMenu,4);


	auto menuBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha.png",
		CC_CALLBACK_1(WinScene::goToMenuStartScene, this));


	auto menu = Menu::create(menuBtn, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
	addChild(menu, 2);

}



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

	auto secuencia = Sequence::create(MoveTo::create(4, Vec2(zerrinVolando->getBoundingBox().size.width, visibleSize.height - zerrinVolando->getBoundingBox().size.height)),
		CallFuncN::create(CC_CALLBACK_1(WinScene::muestraMenu, this)), NULL);
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
	AudioEngine::play2d("sounds/Win_Scene.mp3", false, 1.0);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto destello = Sprite::create("images/VFX/Destello_1.png");
	this->addChild(destello, 4);
	destello->setPosition(Vec2(sender->getPositionX() + sender->getBoundingBox().size.width / 2, sender->getPositionY() + sender->getBoundingBox().size.height / 2));
	destello->setColor(Color3B::ORANGE);
	destello->setOpacity(255);
	destello->setScale(sender->getBoundingBox().size.height / destello->getBoundingBox().size.height);
	auto secuencia1 = Sequence::create(FadeTo::create(0.4, 0.8 / 255), FadeOut::create(0.2), NULL);
	auto accion = ScaleBy::create(0.3, 1.5);
	destello->runAction(Spawn::createWithTwoActions(secuencia1, accion));
	sender->removeFromParent();



	auto menuBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha.png",
		CC_CALLBACK_1(WinScene::goToMenuStartScene, this));


	auto menu = Menu::create(menuBtn, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 2);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
	addChild(menu, 5);
	defineRecompensa(Global::getInstance()->nivelActualID);
}

void WinScene::defineRecompensa(int n)
{
	int recompensaO;
	int recompensaM;
	CCLOG("%d el nivel", n);

	if (Global::getInstance()->nivelesJugados[n] == 0) { 
		CCLOG("primera vez", n);
		recompensaO = Global::getInstance()->RecompensaOro;
		recompensaM = Global::getInstance()->RecompensaMechones;
	}
	else if (Global::getInstance()->nivelesJugados[n] == 1) {
		CCLOG("segunda vez", n);
		recompensaO = Global::getInstance()->RecompensaOro/2;
		recompensaM = Global::getInstance()->RecompensaMechones/2;
	}
	else if (Global::getInstance()->nivelesJugados[n] == 2) {
		CCLOG("tercera vez", n);
		recompensaO = Global::getInstance()->RecompensaOro/4;
		recompensaM = Global::getInstance()->RecompensaMechones/4;
	}
	else {
		recompensaO=10;
		recompensaM=10;
	}
	switch (n) {
		case 0:
			if (Global::getInstance()->nivelesJugados[n] == 0) {
				desbloqueaArma("bola");
				desbloqueaArma("pinchos");
			}
			break;
		case 1:
			break;
		case 2:
			if (Global::getInstance()->nivelesJugados[n] == 0) {
				desbloqueaArma("trampilla");
			}
			break;
		case 3:
			if (Global::getInstance()->nivelesJugados[n] == 0) {
				desbloqueaArma("mina");
			}
			break;
		case 4:
			break;


	}

	Global::getInstance()->nivelesJugados[n]++;
	TTFConfig letraGotica;
	letraGotica.fontFilePath = "fonts/OldLondon.ttf";
	letraGotica.fontSize = 60;
	letraGotica.glyphs = GlyphCollection::DYNAMIC;
	letraGotica.outlineSize = 0;
	letraGotica.customGlyphs = nullptr;
	letraGotica.distanceFieldEnabled = false;
	auto fraseDelMenu = String::createWithFormat("Parece que mientras\ngolpeabas a Zerrin\nse le han caido:\n\n     %d oros.\n     %d mechon/es.\n\nEl mayordomo los ha recogido por ti.",
		recompensaO,recompensaM);

	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto cartel = Sprite::create("images/WinScene/cartel_vacio.png");
	cartel->setAnchorPoint(Vec2(0.5, 0.5));
	cartel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cartel, 2);
	auto FraseMenu = Label::createWithTTF(letraGotica, fraseDelMenu->getCString(), cocos2d::CCTextAlignment::CENTER);
	FraseMenu->setAnchorPoint(Vec2(0.5, 0.5));
	FraseMenu->setColor(Color3B(188, 116, 11));
	bool entra = false;
	while (!entra) {
		if (FraseMenu->getBoundingBox().size.width > cartel->getBoundingBox().size.width - 20 || FraseMenu->getBoundingBox().size.height > cartel->getBoundingBox().size.height - 50) {
			FraseMenu->setScale(FraseMenu->getScale() - 0.01);
		}
		else entra = true;
	}
	FraseMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 30);

	Global::getInstance()->katahi->modificaOro(recompensaO);
	Global::getInstance()->katahi->modificaMechones(recompensaM);
	this->addChild(FraseMenu, 4);
}

void WinScene::desbloqueaArma(std::string nombre)
{
	for (int i = 0; Global::getInstance()->armasTotales.size(); i++) {
		if (Global::getInstance()->armasTotales[i]->getNombre() == nombre){
			Global::getInstance()->armasTotales[i]->disponible = true;
			break;
		}
	}
}


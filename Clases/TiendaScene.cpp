#include "TiendaScene.h"
#include "Arma.h"
#include "Global.h"
#include "Nivel.h"
USING_NS_CC;

Scene* TiendaScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TiendaScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TiendaScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//menu
	auto backBtn = MenuItemImage::create("images/TiendaScene/back_btn.png", "images/TiendaScene/back_btn.png",
		CC_CALLBACK_1(TiendaScene::returnToScene, this));

	auto menu = Menu::create(backBtn, NULL);
	menu->setPosition(Point(visibleSize.width - 20, visibleSize.height - 20));
	addChild(menu, 2);

	/*auto añadeArmaBtn = MenuItemImage::create("images/Armas/arma.png", "images/Armas/arma.png",
		CC_CALLBACK_0(TiendaScene::compraArma, this));
	auto menu2 = Menu::create(añadeArmaBtn, NULL);
	addChild(menu2, 2);*/



	//Fondo
	auto background = Sprite::create("images/TiendaScene/fondo_TiendaScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);

	colocaArmasTotales();
	return true;
}

void TiendaScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		(Global::getInstance()->armasTotales[i])->setDesdeTienda(false);
	}

}



void TiendaScene::colocaArmasTotales()
{
	int posY = 200;
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		Arma* arma = Global::getInstance()->armasTotales[i];
		if (!arma->childEnTienda) {
			this->addChild(arma, 3);
			arma->setPosition(i * 50 + 100, posY);
			if (i+1 % 5 == 0) posY += 100;
			arma->setColor(Color3B(i * 50, i * 10 + 60, 10));

		}
		arma->setDesdeTienda(true);
		CCLOG("%d", i);
	}
	CCLOG("numero de hijos de tienda es : %d ", this->getChildren().size());
}



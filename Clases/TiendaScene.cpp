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
	menu->setPosition(Point(visibleSize.width- 20, visibleSize.height- 20));
	addChild(menu, 2);


	//Fondo
	auto background = Sprite::create("images/TiendaScene/fondo_TiendaScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	this->addListener();

	//menu Compra
	colocaArmasTotales();
	this->preparaBotones();
	listenerTienda->setEnabled(true);
	return true;
}

void TiendaScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		(Global::getInstance()->armasTotales[i])->setDesdeTienda(false);
		(Global::getInstance()->armasTotales[i])->EnableSwallow(false);
	}
	this->removeAllChildren();
	_eventDispatcher->removeEventListener(this->listenerTienda);

}



void TiendaScene::createMenuCompra()
{
	activaDesactivaBotones(this->yesButton, true);
	activaDesactivaBotones(this->cerrarMenuButton, true);

}

void TiendaScene::closeMenuCompra(Ref *pSender)
{
	activaDesactivaBotones(this->yesButton, false);
	activaDesactivaBotones(this->cerrarMenuButton, false);
	Global::getInstance()->armaAComprar = nullptr;
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) Global::getInstance()->armasTotales[i]->EnableListener(true);
	this->listenerTienda->setEnabled(true);
}

void TiendaScene::hacerCompra(Ref *pSender)
{

	Global::getInstance()->armaAComprar->childEnTienda = true;
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		if (Global::getInstance()->armasTotales[i] == Global::getInstance()->armaAComprar) {
			Global::getInstance()->armasTotales[i]->setDesdeTienda(false);
			Global::getInstance()->armasTotales.erase(Global::getInstance()->armasTotales.begin() + i);
			break;
		}
	}
	Global::getInstance()->armasArsenal.push_back(Global::getInstance()->armaAComprar);
	Global::getInstance()->armaAComprar->setVisible(false);
	closeMenuCompra(this);
}

void TiendaScene::colocaArmasTotales()
{
	int iterador = 0;
	int margenesX = 200;
	int margenesY = 140;
	auto anchoCorrespondiente = 0;
	auto altoCorrespondiente = 0;
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		
		Arma* arma = Global::getInstance()->armasTotales[i];

		if (!arma->childEnTienda) {
			this->addChild(arma, 3);
			arma->EnableSwallow(true);
			if (i >= 5) {
				iterador = floor(i / 5);
				anchoCorrespondiente = ((i - (iterador * 5))*arma->getContentSize().width) * 2;
				altoCorrespondiente = arma->getContentSize().height *floor(i / 5);
			}
			else {
				anchoCorrespondiente = (i*arma->getContentSize().width * 2);
				altoCorrespondiente = arma->getContentSize().height *floor(i / 5);
			}
			arma->setPosition(margenesX + anchoCorrespondiente, margenesY + altoCorrespondiente + altoCorrespondiente *0.5);
			arma->setColor(Color3B(i * 50, i * 10 + 60, 10));
		}
		arma->setDesdeTienda(true);
		CCLOG("%d", i);
	}
	CCLOG("numero de hijos de tienda es : %d ", this->getChildren().size());
}

void TiendaScene::activaDesactivaBotones(cocos2d::MenuItemImage * boton, bool estado)
{
	CCLOG("los activo o desactivo");
	textoCompra->setVisible(estado);
	rectangulo->setVisible(estado);
	boton->setVisible(estado);
	boton->setEnabled(estado);
}

void TiendaScene::preparaBotones()
{
	auto ancho = (Global::getInstance()->visibleSize.width * 4) / 6;
	auto alto = (Global::getInstance()->visibleSize.height) / 2;
	rectangulo = Sprite::create("images/Nivel/rectangle.png");
	rectangulo->setScaleX(ancho / rectangulo->getContentSize().width);
	rectangulo->setScaleY(alto / rectangulo->getContentSize().height);
	rectangulo->setPosition(Point(Global::getInstance()->visibleSize.width/2, Global::getInstance()->visibleSize.height / 2));
	addChild(rectangulo, 3);

	textoCompra = Label::createWithSystemFont("QUIERES COMPRAR?", "Arial", 40);
	textoCompra->setColor(Color3B::ORANGE);
	textoCompra->enableShadow();
	textoCompra->setPosition(Global::getInstance()->visibleSize.width / 2, Global::getInstance()->visibleSize.height / 2+textoCompra->getContentSize().height*1.5);

	addChild(textoCompra,3);
	textoCompra->setVisible(false);
	yesButton = MenuItemImage::create("images/Armas/yes.png", "images/Armas/yes.png",
		CC_CALLBACK_1(TiendaScene::hacerCompra, this));
	cerrarMenuButton = MenuItemImage::create("images/Armas/no.png", "images/Armas/no.png",
		CC_CALLBACK_1(TiendaScene::closeMenuCompra, this));
	cerrarMenuButton->setScale(0.3);
	yesButton->setScale(0.6);

	activaDesactivaBotones(this->yesButton, false);
	activaDesactivaBotones(this->cerrarMenuButton, false);


	yesButton->setPosition(-yesButton->getContentSize().width / 2, 0);
	cerrarMenuButton->setPosition(cerrarMenuButton->getContentSize().width / 4, 0);

	menuCompra = Menu::create(yesButton, cerrarMenuButton, NULL);
	menuCompra->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(menuCompra, 3);
}

void TiendaScene::addListener()
{
		listenerTienda = cocos2d::EventListenerTouchOneByOne::create();
		listenerTienda->setSwallowTouches(false);

		listenerTienda->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
				return true;
		};
		listenerTienda->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			CallFunc* runCallback = CallFunc::create(CC_CALLBACK_0(TiendaScene::gestionaToque, this));
			runAction(Sequence::create(DelayTime::create(0.09), runCallback, nullptr));
		};

		cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerTienda, 30);

	
}

void TiendaScene::gestionaToque()
{

	if (Global::getInstance()->armaAComprar != nullptr) {
		createMenuCompra();
		this->listenerTienda->setEnabled(false);
		for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) Global::getInstance()->armasTotales[i]->EnableListener(false);
		CCLOG("si es en un arma");
	}
	else {
		CCLOG("no es en un arma");
	}
}



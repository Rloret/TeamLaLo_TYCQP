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
	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(TiendaScene::returnToScene, this));

	auto menu = Menu::create(backBtn, NULL);
	menu->setPosition(Point(visibleSize.width- 50, visibleSize.height- 50));
	addChild(menu, 2);

	
	//Fondo
	auto background = Sprite::create("images/TiendaScene/fondo_TiendaScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);
	this->addListener();

	//menu Compra
	colocaArmasTotales();
	this->preparaBotones();
	this->preparaLabels();
	listenerTienda->setEnabled(true);

	return true;

}

void TiendaScene::returnToScene(Ref *pSender){

	Director::getInstance()->popScene();
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		(Global::getInstance()->armasTotales[i])->setDesdeTienda(false);
		(Global::getInstance()->armasTotales[i])->EnableSwallow(false);
		Global::getInstance()->armasTotales[i]->setVisible(false);
	}
	this->removeAllChildren();
	_eventDispatcher->removeEventListener(this->listenerTienda);

}



void TiendaScene::createMenuCompra()
{
	activaDesactivaBotones(this->yesButton, true);
	activaDesactivaBotones(this->cerrarMenuButton, true);

	textoCompra->setString(String::createWithFormat("Quieres comprar por \n el modico precio de \n %d lingotes de oro \n y tan solo %d mechones", Global::getInstance()->armaAComprar->getPrecio(), Global::getInstance()->armaAComprar->getMechones())->getCString());

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
			if (Global::getInstance()->katahi->getOro() >= Global::getInstance()->armaAComprar->getPrecio() && Global::getInstance()->katahi->getMechones() >= Global::getInstance()->armaAComprar->getMechones()) {
				Global::getInstance()->armasTotales[i]->setDesdeTienda(false);
				Global::getInstance()->armasTotales.erase(Global::getInstance()->armasTotales.begin() + i);
				
				Global::getInstance()->armasArsenal.push_back(Global::getInstance()->armaAComprar);
				Global::getInstance()->armaAComprar->setVisible(false);
				Global::getInstance()->katahi->modificaOro(-Global::getInstance()->armaAComprar->getPrecio());
				Global::getInstance()->katahi->modificaMechones(-Global::getInstance()->armaAComprar->getMechones());
				//CCLOG("oro: %d", Global::getInstance()->katahi->getOro());
				
				closeMenuCompra(this);
				this->modificaTextoOro(dinero_oro_int);
			
				
				break;
			}
			else {
				//MessageBox("No tienes suficiente dinero", "Aviso");

				activaDesactivaBotones(yesButton,false);
				rectangulo->setVisible(true);
				textoCompra->setString("Pero...si no tienes \nsuficiente dinero.\nNo me hagas perder \nel tiempo.");
				textoCompra->setVisible(true);
				bocadillo->setVisible(true);
				Global::getInstance()->armaAComprar->childEnTienda = false;
			}	
		}
	}	
}

void TiendaScene::colocaArmasTotales()
{
	int iterador = 0;
	int margenesX = 280;
	int margenesY = 170;
	auto anchoCorrespondiente = 0;
	auto altoCorrespondiente = 0;
	for (int i = 0; i < Global::getInstance()->armasTotales.size(); i++) {
		
		Arma* arma = Global::getInstance()->armasTotales[i];
		if (!arma->childEnTienda) {
			this->addChild(arma, 3);
			arma->setVisible(true);
			arma->EnableSwallow(true);
			if (i >= 5) {
				iterador = floor(i / 5);
				anchoCorrespondiente = ((i - (iterador * 5))*84*1.2);
				altoCorrespondiente = arma->getContentSize().height *floor(i / 5);
			}
			else {
				anchoCorrespondiente = (i*84 * 1.2);
				altoCorrespondiente = arma->getContentSize().height *floor(i / 5);
			}
			arma->setPosition(margenesX + anchoCorrespondiente, margenesY + altoCorrespondiente + altoCorrespondiente *0.5);
			CCLOG("arma colocada en %f, %f", arma->getPositionX(), arma->getPositionY());
			//arma->setColor(Color3B(i * 50, i * 10 + 60, 10));
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
	bocadillo->setVisible(estado);
	rectangulo->setVisible(estado);
	boton->setVisible(estado);
	boton->setEnabled(estado);
}

void TiendaScene::preparaBotones()
{
	auto ancho = (Global::getInstance()->visibleSize.width * 4) / 6;
	auto alto = (Global::getInstance()->visibleSize.height) / 2;
	rectangulo = Sprite::create("images/TiendaScene/cartel_compra.png");
	rectangulo->setPosition(Point(Global::getInstance()->visibleSize.width / 2, Global::getInstance()->visibleSize.height / 2 +50));
	
	addChild(rectangulo, 3);

	yesButton = MenuItemImage::create("images/TiendaScene/si.png", "images/TiendaScene/si.png",
		CC_CALLBACK_1(TiendaScene::hacerCompra, this));

	cerrarMenuButton = MenuItemImage::create("images/TiendaScene/no.png", "images/TiendaScene/no.png",
		CC_CALLBACK_1(TiendaScene::closeMenuCompra, this));

	menuCompra = Menu::create(yesButton, cerrarMenuButton, NULL);
	menuCompra->alignItemsHorizontallyWithPadding(rectangulo->getContentSize().width / 4);
	menuCompra->setPosition(rectangulo->getPositionX(),rectangulo->getPositionY()-170);
	this->addChild(menuCompra, 3);

	
	bocadillo = cocos2d::Sprite::create("images/Nivel/Bocadillo_Zerrin.png");
	addChild(bocadillo, 3);
	bocadillo->setPosition(Point(Global::getInstance()->visibleSize.width*3/4+bocadillo->getContentSize().width/2-20, Global::getInstance()->visibleSize.height*3/4-bocadillo->getContentSize().height/2));
	bocadillo->setScale(1.7, 1.8);

	textoCompra = Label::createWithSystemFont("QUIERES COMPRAR?", "Arial", 30);
	textoCompra->setColor(Color3B::GRAY);
	textoCompra->enableShadow();
	
	textoCompra->setPosition(Point(bocadillo->getPositionX(),bocadillo->getPositionY()+textoCompra->getContentSize().height/2));
	addChild(textoCompra, 4);
	textoCompra->setVisible(false);

	activaDesactivaBotones(this->yesButton, false);
	activaDesactivaBotones(this->cerrarMenuButton, false);
}

void TiendaScene::preparaLabels()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	int y = visibleSize.height - 25;

	dinero_oro_int = Label::createWithSystemFont((String::createWithFormat("Dinero : %i", Global::getInstance()->katahi->getOro())->getCString()), "Arial", 40);
	dinero_oro_int->setColor(Color3B::BLACK);
	dinero_oro_int->enableShadow();

	dinero_mechones_int = Label::createWithSystemFont((String::createWithFormat("Mechones : %i", Global::getInstance()->katahi->getMechones())->getCString()), "Arial", 40);
	dinero_mechones_int->setColor(Color3B::BLACK);
	dinero_mechones_int->enableShadow();

	this->addChild(dinero_oro_int, 2);
	this->addChild(dinero_mechones_int, 2); 
	dinero_oro_int->setPosition(Point(220, y));
	dinero_mechones_int->setPosition(Point(670, y));
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
		//CCLOG("si es en un arma");
	}
	else {
		//CCLOG("no es en un arma");
	}
}

void TiendaScene::modificaTextoOro(cocos2d::Label * l)
{
	auto aux1 = CCString::createWithFormat("%i", Global::getInstance()->katahi->getOro());
	CCLOG("Katahi tiene : %d", Global::getInstance()->katahi->getOro());
	dinero_oro_int->setString((String::createWithFormat("Dinero = %d", Global::getInstance()->katahi->getOro())->getCString()));
	
	dinero_mechones_int->setString((String::createWithFormat("Mechones = %d", Global::getInstance()->katahi->getMechones())->getCString()));
	//l->setVisible(false);
}



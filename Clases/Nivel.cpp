
#include "Nivel.h"
#include "proj.win32\TiendaScene.h"
#include "proj.win32\VestuarioScene.h"
#include "proj.win32\PauseScene.h"
#include "Global.h"
#include "ZerrinClass.h"
#include "GameOverScene.h"
#include "Nube.h"
USING_NS_CC;

#define ANCHOARSENAL ((Global::getInstance()->visibleSize.width*4)/6);
#define ALTOARSENAL ((Global::getInstance()->visibleSize.height)/8);



Scene* Nivel::createScene(std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->setName("Padre");
	auto layer = Nivel::create(fondos, i_objetos, u_objetos);
	scene->addChild(layer);

	// 'layer' is an autorelease object
/*	auto layer= Nivel::create();
	layer->setName("Hijo");
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene*/
	return scene;
}


Nivel * Nivel::create(std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	Nivel *pRet = new(std::nothrow)Nivel(fondos, i_objetos, u_objetos); \
		if (pRet && pRet->init()) \
		{ \
			pRet->autorelease(); \
			return pRet; \
		} \
		else \
		{ \
			delete pRet; \
			pRet = NULL; \
			return NULL; \
		} \

		//Global::getInstance()->modificaNivel((cocos2d::Scene*)pRet);
}



// on "init" you need to initialize your instance
bool Nivel::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	CCLOG("devuelvo true");
	return true;
}


void Nivel::preparaNivel(std::vector<std::string> fondos, int i_objetos, int u_objetos) {  // nivel=numero nivel para colocar
	Size visibleSize = Director::getInstance()->getVisibleSize();
	vueltasArsenal = 0;
	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;

	Global::getInstance()->ContadorArmas = 0;
	Global::getInstance()->juegoEnCurso = false;
	colocaBotones();
	displayArmasArsenal();

	colocaFondo(fondos);

	colocaObjetos(i_objetos, u_objetos);
	addChild(Global::getInstance()->zerrin, 3);

	Global::getInstance()->zerrin->setPosition(Point(450 + Global::getInstance()->zerrin->getContentSize().width / 2
		, visibleSize.height / 3 + Global::getInstance()->zerrin->getContentSize().height / 2));
	Global::getInstance()->zerrin->setRotation(0);
	CCLOG("Zerrin esta burladisimo %d", Global::getInstance()->zerrin->getRotation());
	this->setPosition(0, 0);
	Global::getInstance()->zerrin->haLlegado = false;
	this->schedule(schedule_selector(Nivel::spawnNube), 1.5);

	
}

void Nivel::displayArmasArsenal()
{

	for (int i = 0; i < Global::getInstance()->armasArsenal.size(); i++) {
		CCLOG("arma con daño: %d", Global::getInstance()->armasArsenal[i]->getDaño());
		Arma* arma = Global::getInstance()->armasArsenal[i];
		if (!this->getChildren().contains(arma)) {
			arma->enNivel = false;
			arma->childEnNivel = true;
			CCLOG("el daño de este arma, que no esta añadida es = %d", Global::getInstance()->armasArsenal[i]->getDaño());
			this->addChild(arma, 5);
			arma->setVisible(false);
		}

	}
}



void Nivel::muestraUnoMas(Ref *pSender)
{

	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;

	auto iterador = 0;
	auto posicion = 0;

	if (Global::getInstance()->armasArsenal.size()>5) {		
		borraArsenal(-5);
		recorreArmas(iterador, posicion, ancho, alto,5);
	}
	else {
		recorreArmas(iterador, posicion, ancho, alto, Global::getInstance()->armasArsenal.size());
	}
	CCLOG("vueltasarsenal vale %d", vueltasArsenal);
}

void Nivel::muestraUnoMenos(Ref *pSender,int i)
{
	auto iterador = 0;
	auto posicion = 0;

	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;
	Global::getInstance()->armasArsenal.size() > 5 ? CCLOG("true") : CCLOG("false");
	if(Global::getInstance()->armasArsenal.size()>5){
		CCLOG("Si entro");

		int max = 0;
		Global::getInstance()->armasArsenal.size() >10 ?  max = 10: max =5;
		borraArsenal(5);

		((vueltasArsenal - max) <= 0) ? vueltasArsenal = Global::getInstance()->armasArsenal.size() - 5 : vueltasArsenal -= 10;
		(vueltasArsenal < 0) ? vueltasArsenal = Global::getInstance()->armasArsenal.size()- vueltasArsenal*(-1):vueltasArsenal;

		recorreArmas(iterador, posicion, ancho, alto,5);
		if (vueltasArsenal > Global::getInstance()->armasArsenal.size()) vueltasArsenal = 0;
		CCLOG("vueltasarsenal vale %d", vueltasArsenal);
	}



}

void Nivel::borraArsenal(int superiorinferior)
{
	auto aux = 0;


		(vueltasArsenal ==0) ? aux = Global::getInstance()->armasArsenal.size()-1 : aux = vueltasArsenal-1;
		auto iterador = aux;
		auto armasborradas = 0;;

		while (armasborradas<5){
			if (iterador <0){
				iterador = Global::getInstance()->armasArsenal.size()-1;
			}
			Arma* arma = Global::getInstance()->armasArsenal[iterador];
			activaDesactivaArma(arma,false);
			CCLOG("borro la %d", iterador);
			iterador--;
			armasborradas++;

		}

}

void Nivel::goToTienda(Ref *pSender){
	if (!Global::getInstance()->juegoEnCurso){

		if (rectangulo->isVisible())abrirArsenal(this);
		vueltasArsenal = 0;
		auto scene = TiendaScene::createScene();
		Director::getInstance()->pushScene(scene);
	}
	
}


void Nivel::goToVestuario(Ref *pSender){
	if (!Global::getInstance()->juegoEnCurso){
		auto scene = VestuarioScene::createScene();
		Director::getInstance()->pushScene(scene);
	}
}

void Nivel::goToPause(Ref *pSender){

	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void Nivel::goToGameOver(Ref * pSender)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Nivel::abrirArsenal(Ref *pSender){

	if (!Global::getInstance()->juegoEnCurso){
		displayArmasArsenal();
		if (Global::getInstance()->armasArsenal.size() > 5) {
			activaDesactivaBoton(masBtn, true);
			activaDesactivaBoton(menosBtn, true);
		}
		else {
			activaDesactivaBoton(masBtn, false);
			activaDesactivaBoton(menosBtn, false);
		}

		if (rectangulo->isVisible()) {
			rectangulo->setVisible(false);
			auto aux = 0;

			quitaArmas();

			vueltasArsenal = 0;
			menuArsenal->setVisible(false);
		}
		else {
			menuArsenal->setVisible(true);
			rectangulo->setVisible(true);
			muestraUnoMas(this);
		}
	}
	
}


void Nivel::simulacion(Ref *pSender){

	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (!Global::getInstance()->juegoEnCurso){
		Global::getInstance()->juegoEnCurso = true;
		CCLOG("Empieza la simulacion");
		menu1->setVisible(false);
		if(menu2!=nullptr)menu2->setVisible(false);
		quitaArmas();

		if (rectangulo->isVisible()){
			rectangulo->setVisible(false);
			activaDesactivaBoton(masBtn, false);
			activaDesactivaBoton(menosBtn,false);
			
		}
		
		
		((ZerrinClass *)Global::getInstance()->zerrin)->setCorrer(true);


		this->runAction(Follow::create(Global::getInstance()->zerrin,background->getBoundingBox()));

		
	}
	else{
		CCLOG("Ya estas en simulacion");
	}
	
}

void Nivel::activaDesactivaBoton(MenuItemImage* boton, bool estado)
{
	boton->setEnabled(estado);
	boton->setVisible(estado);
}

void Nivel::recorreArmas(int iterador,int posicion,int ancho,int alto,int iteraciones)
{

	while (iterador < iteraciones) {
		posicion++;
		if (vueltasArsenal == Global::getInstance()->armasArsenal.size()) vueltasArsenal = 0;
		Arma* arma = Global::getInstance()->armasArsenal[vueltasArsenal];
		//arma->setPosition((((posicion + 1)*ancho) / 7) - arma->getContentSize().width, alto / 2 + 2 * vueltasArsenal);
		arma->setPosition((((posicion + 1)*ancho) / 7) /*+ arma->getContentSize().width*/, alto / 2 + 2 * vueltasArsenal);
		activaDesactivaArma(arma, true);
		CCLOG("muestro la %d", vueltasArsenal);

		iterador++;
		vueltasArsenal++;


	}
}

void Nivel::activaDesactivaArma(Arma * arma, bool estado)
{
	arma->setVisible(estado);
	arma->EnableListener(estado);
}

void Nivel::quitaArmas(){
	for (int i = 0; i < Global::getInstance()->armasArsenal.size(); i++) {
		Arma* arma = Global::getInstance()->armasArsenal[i];
		if (arma->isVisible())arma->setVisible(false);
		arma->EnableListener(false);
	}
}

void Nivel::colocaObjetos(int i_objetos, int u_objetos)
{
	for (int i = i_objetos; i < u_objetos; i++) {
		addChild(Global::getInstance()->ObjetosTotalesEscenarios[i],3);
		Global::getInstance()->ObjetosTotalesEscenarios[i]->setVisible(true);
		Vec2 punto = Vec2(((i + 1)*Director::getInstance()->getVisibleSize().width) / 10 - 
					Global::getInstance()->ObjetosTotalesEscenarios[i]->getContentSize().width,
					Director::getInstance()->getVisibleSize().height / 2);
		Global::getInstance()->ObjetosTotalesEscenarios[i]->setPosition(punto);
	}
}

void Nivel::colocaBotones()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	rectangulo = Sprite::create("images/Nivel/rectangle.png");
	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;

	rectangulo->setScaleX(ancho / rectangulo->getContentSize().width);
	rectangulo->setScaleY(alto / rectangulo->getContentSize().height);
	rectangulo->setPosition(Point(ancho / 2, alto / 2));
	rectangulo->setVisible(false);
	addChild(rectangulo, 5);

	auto pauseBtn = MenuItemImage::create("images/Nivel/pause_btn.png", "images/Nivel/pause_btn.png", CC_CALLBACK_1(Nivel::goToPause, this));

	auto tiendaBtn = MenuItemImage::create("images/Nivel/tienda_btn.png", "images/Nivel/tienda_btn.png", CC_CALLBACK_1(Nivel::goToTienda, this));
	auto vestuarioBtn = MenuItemImage::create("images/Nivel/vestuario_btn.png", "images/Nivel/vestuario_btn.png", CC_CALLBACK_1(Nivel::goToVestuario, this));

	auto listenerPause = EventListenerKeyboard::create();
	listenerPause->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Nivel::goToPause(this);
		}

	};
	menu1 = Menu::create(pauseBtn, tiendaBtn, vestuarioBtn, NULL);
	menu1->setPosition(Point(150, visibleSize.height - pauseBtn->getContentSize().height));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerPause, this);
	menu1->alignItemsHorizontally();
	addChild(menu1, 5);

	



	auto arsenalBtn = MenuItemImage::create("images/Nivel/back_btn.png", "images/Nivel/back_btn.png", CC_CALLBACK_1(Nivel::abrirArsenal, this));
	arsenalBtn->setColor(Color3B(100, 100, 100));
	auto simulacionBtn = MenuItemImage::create("images/Nivel/back_btn.png", "images/Nivel/back_btn.png", CC_CALLBACK_1(Nivel::simulacion, this));
	simulacionBtn->setColor(Color3B(150, 50, 150));

	menu2 = Menu::create(arsenalBtn, simulacionBtn, NULL);
	menu2->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 3, arsenalBtn->getContentSize().height/2));
	menu2->alignItemsHorizontally();
	addChild(menu2, 5);


	masBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha.png", CC_CALLBACK_1(Nivel::muestraUnoMas, this));

	auto ancho1 = rectangulo->getContentSize().width;
	auto alto1 = Global::getInstance()->visibleSize.height / 16;

	masBtn->setScaleX(-ancho1 / (masBtn->getContentSize().width * 11));
	masBtn->setScaleY(alto1 / masBtn->getContentSize().height);
	masBtn->setPosition((-visibleSize.width / 2.0) + ancho - 45, -visibleSize.height / 2.0 + 30);
	
	menosBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha.png", CC_CALLBACK_1(Nivel::muestraUnoMenos, this, vueltasArsenal));

	menosBtn->setScaleX(ancho1 / (menosBtn->getContentSize().width * 11));
	menosBtn->setScaleY(alto1 / menosBtn->getContentSize().height);
	menosBtn->setPosition((-visibleSize.width / 2.0) + 40, -visibleSize.height / 2.0 + 30);

	menuArsenal = Menu::create(masBtn, menosBtn, NULL);
	addChild(menuArsenal, 5);
	menuArsenal->setVisible(false);
}

void Nivel::colocaFondo(std::vector<std::string> fondos){

	Size visibleSize = Director::getInstance()->getVisibleSize();

	background = Sprite::create(fondos[0]);

	auto limitesEscenario = PhysicsBody::createEdgeBox(Size(background->getContentSize().width,568), PHYSICSBODY_MATERIAL_DEFAULT,0.3);
	limitesEscenario->setPositionOffset(Vec2(0, 200));
	background->retain();
	background->setPosition(background->getContentSize().width, visibleSize.height);
	background->setAnchorPoint(Vec2(1, 1));
	background->setPhysicsBody(limitesEscenario);
	addChild(background,0);

	/*cocos2d::Sprite* limites = cocos2d::Sprite::create();
	limites->setPhysicsBody(limitesEscenario);
	addChild(limites, 1);*/


	//background->retain();

	background1 = Sprite::create(fondos[1]);

	addChild(background1, 1);

	background1->setPosition(background1->getContentSize().width, visibleSize.height);
	background1->setAnchorPoint(Vec2(1, 1));
	background1->retain();


	background2 = Sprite::create(fondos[3]);
	addChild(background2, 3);

	background2->setPosition(background2->getContentSize().width, visibleSize.height);
	background2->setAnchorPoint(Vec2(1, 1));
	background2->retain();

	muralla = Sprite::create(fondos[4]);
	addChild(muralla, 4);

	muralla->setPosition(muralla->getContentSize().width, visibleSize.height);
	muralla->setAnchorPoint(Vec2(1, 1));
	muralla->retain();
}

void Nivel::setPhysicsWorld(cocos2d::PhysicsWorld * world)
{
	nivelPhysics = world;
	nivelPhysics->setGravity(Vec2(0, -9.8));
}


int Nivel::getBackgroundWidth()
{
	auto s =background2->getContentSize();
	return s.width;
}

Nivel::Nivel(std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	preparaNivel(fondos, i_objetos, u_objetos);
}

Nivel::~Nivel()
{
}

cocos2d::Rect Nivel::getBackgroundSize()
{
	return 	background->getBoundingBox();

}
void Nivel::spawnNube(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto Nubecita = Nube::create();
	auto limitesEscenario = PhysicsBody::createEdgeBox(Nubecita->getBoundingBox().size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//Nubecita->setPhysicsBody(limitesEscenario);
	this->addChild(Nubecita, 1);
	auto rand = random(1, 3);
	Nubecita->setPosition(Point(Global::getInstance()->zerrin->getPosition().x +visibleSize.width/2 +Nubecita->getContentSize().width,
						visibleSize.height - Nubecita->getContentSize().height*rand));
	Nubecita->spawnNube(dt);

}

/*void Nivel::stopCamara()
{
	this->stopAction(Global::getInstance()->getCamara());
}*/


void Nivel::mueveFondo(int v) {
	
	for (auto a : Global::getInstance()->ArmasNivel) {
		if(a->colocada ) a->setPositionX(a->getPositionX()-v);
	}

}


int Nivel::getPosXFondo()
{
	return background->getPositionX();
}






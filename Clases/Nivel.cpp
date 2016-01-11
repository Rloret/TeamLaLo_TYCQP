
#include "Nivel.h"
#include "proj.win32\TiendaScene.h"
#include "proj.win32\VestuarioScene.h"
#include "proj.win32\PauseScene.h"
#include "Global.h"
#include "ZerrinClass.h"
#include "GameOverScene.h"
#include "Nube.h"
#include "ObjetoEscenario.h"
#include "Arma.h"
#include "WinScene.h"
#include "chipmunk.h"
#include "Animacion.h"

USING_NS_CC;

#define ANCHOARSENAL ((Global::getInstance()->visibleSize.width*4)/6);
#define ALTOARSENAL ((Global::getInstance()->visibleSize.height)/8);




Scene* Nivel::createScene(int nivel, std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->setTag(101);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layerObjects = Layer::create();
	layerObjects->setTag(103);
	
	scene->addChild(layerObjects,20);
	Global::getInstance()->layerObjects = layerObjects;

	CCLOG("scene mide : %f, %f", scene->getBoundingBox().size.width, scene->getBoundingBox().size.height);
	auto layer = Nivel::create(nivel, fondos, i_objetos, u_objetos);
	layer->setTag(102);
	
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	Global::getInstance()->nivel = scene;

	CCLOG("Layer mide : %f, %f", layer->getBoundingBox().size.width, layer->getBoundingBox().size.height);
	scene->addChild(layer,10);

	return scene;
}


Nivel * Nivel::create(int nivel, std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	Nivel *pRet = new(std::nothrow)Nivel(nivel, fondos, i_objetos, u_objetos); \
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


void Nivel::preparaNivel(int nivel, std::vector<std::string> fondos, int i_objetos, int u_objetos) {  // nivel=numero nivel para colocar
	Global::getInstance()->ellapsedTime = 999.0;
	Global::getInstance()->currentTime = 0.0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	vueltasArsenal = 0;
	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;
	Global::getInstance()->ContadorArmas = 0;
	Global::getInstance()->juegoEnCurso = false;
	colocaFondo(fondos);
	colocaZerrin();

	this->addContactListener();
	
	addChild(Global::getInstance()->zerrin, 4);

	auto KatahiAnimacion = new Animacion("katahi_%03d.png", 2, 4.0, "images/GameOverScene/ZerrinyKatahi.plist", true);
	Katahi = KatahiAnimacion->getAnimacionCreada();
	this->addChild(Katahi,4);
	Katahi->setPosition(2600,Global::getInstance()->zerrin->getPositionY()-Katahi->getBoundingBox().size.height/2);
	if (nivel>=2) this->schedule(schedule_selector(Nivel::spawnNube), 2.0);
	
	//sprite vacio
	cocos2d::Sprite *señuelo = cocos2d::Sprite::create();
	addChild(señuelo, 4);
	
	señuelo->setPosition(Point(350 + Global::getInstance()->zerrin->getContentSize().width / 2
		, visibleSize.height / 3 + señuelo->getContentSize().height / 2));
	
	this->runAction(Follow::create(señuelo, muralla->getBoundingBox()));


	switch (nivel) {
		case 0:
			señuelo->runAction(Sequence::create(CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 0)), 
				DelayTime::create(3.0),
				MoveBy::create(2, Point(3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 0)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 1)),
				DelayTime::create(3.0), MoveBy::create(2, Point(-3000, 0)), 
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 1)), 
				DelayTime::create(3.0), MoveBy::create(2, Point(3000, 0)),
				CallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 2)),
				DelayTime::create(3.0), MoveBy::create(2, Point(-3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 2)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 3)),
				DelayTime::create(3.0), MoveBy::create(2, Point(3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 4)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 5)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 6)),
				DelayTime::create(3.0), MoveBy::create(2, Point(-3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::colocaHUD, this)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::removeKatahi, this)),
				NULL));

			break;
		case 1:
			señuelo->runAction(Sequence::create(CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 4)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 7)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 8)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 9)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(-3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::colocaHUD, this)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::removeKatahi, this)),
				NULL));

			break;
		case 2:
			señuelo->runAction(Sequence::create(CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 5)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 10)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(-3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::colocaHUD, this)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::removeKatahi, this)), NULL));

			break;
		case 3:
			colocaHUD();
			removeKatahi();
			break;

		case 4:
			señuelo->runAction(Sequence::create(CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 6)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 7)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesKatahi, this, 11)),
				DelayTime::create(3.0),
				MoveBy::create(2, Point(-3000, 0)),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 8)),
				DelayTime::create(3.0),
				CCCallFunc::create(CC_CALLBACK_0(Nivel::cargaFrasesZerrin, this, 9)),
				DelayTime::create(3.0),

				CCCallFunc::create(CC_CALLBACK_0(Nivel::colocaHUD, this)), CCCallFunc::create(CC_CALLBACK_0(Nivel::removeKatahi, this)), NULL));

			break;
		default:
			señuelo->runAction(CCCallFunc::create(CC_CALLBACK_0(Nivel::colocaHUD, this)));
			break;
	
	}
	
}

void Nivel::displayArmasArsenal()
{

	for (int i = 0; i < Global::getInstance()->armasArsenal.size(); i++) {
		//CCLOG("arma con daño: %d", Global::getInstance()->armasArsenal[i]->getDaño());
		Arma* arma = Global::getInstance()->armasArsenal[i];
		if (!this->getChildren().contains(arma)) {
			arma->enNivel = false;
			arma->childEnNivel = true;
			//CCLOG("el daño de este arma, que no esta añadida es = %d", Global::getInstance()->armasArsenal[i]->getDaño());
			this->addChild(arma, 7);
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

void Nivel::goToWinScene()
{
	auto scene = WinScene::createScene();
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
	

		this->runAction(Follow::create(Global::getInstance()->zerrin,muralla->getBoundingBox()));

		
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
		arma->setPosition(((rectangulo->getPositionX()+(posicion)*554) / 6), alto / 2 +30);
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


void Nivel::colocaBotones()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	rectangulo = Sprite::create("images/Nivel/Arsenal.png");
	auto ancho = ANCHOARSENAL;
	auto alto = ALTOARSENAL;

	//rectangulo->setScaleX(ancho / rectangulo->getContentSize().width);
	//rectangulo->setScaleY(alto / rectangulo->getContentSize().height);
	rectangulo->setPosition(Point(ancho / 2, alto / 2+30));
	rectangulo->setVisible(false);
	addChild(rectangulo, 8);

	auto pauseBtn = MenuItemImage::create("images/Nivel/Botones/pause_btn_good_res_idle.png", "images/Nivel/Botones/pause_btn_good_res.png", CC_CALLBACK_1(Nivel::goToPause, this));
	auto tiendaBtn = MenuItemImage::create("images/Nivel/Botones/tienda_btn_good_res_idle.png", "images/Nivel/Botones/tienda_btn_good_res.png", CC_CALLBACK_1(Nivel::goToTienda, this));
	auto vestuarioBtn = MenuItemImage::create("images/Nivel/Botones/vestuario_btn_good_res_idle.png", "images/Nivel/Botones/vestuario_btn_good_res.png", CC_CALLBACK_1(Nivel::goToVestuario, this));

	auto listenerPause = EventListenerKeyboard::create();
	listenerPause->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Nivel::goToPause(this);
			break;
		case EventKeyboard::KeyCode::KEY_I:
			Global::getInstance()->zerrin->getPhysicsBody()->applyImpulse(Vec2(-100000000,0));
			break;
		case EventKeyboard::KeyCode::KEY_F:
			Global::getInstance()->zerrin->getPhysicsBody()->applyForce(Vec2(-100000, 100000));
			break;
		case EventKeyboard::KeyCode::KEY_V:
			
			Global::getInstance()->zerrin->getPhysicsBody()->setAngularVelocity(20);
			Global::getInstance()->zerrin->setState(Global::getInstance()->zerrin->ZERRINFSM::GOLPEADO_ALANTE);
			break;
		case EventKeyboard::KeyCode::KEY_X:
			auto armadeturno = Global::getInstance()->armasTotales[random(0, 10)];
			auto armadeturno2 = armadeturno->ClonarArma(armadeturno);
			armadeturno2->setName("Arma");
			this->addChild(armadeturno2,3);
			armadeturno2->setPosition(Global::getInstance()->zerrin->getPositionX()+ 1024/random(1, 5), visibleSize.height);
			armadeturno2->setPhysicsBody(PhysicsBody::createBox(armadeturno2->getContentSize(), PhysicsMaterial(random(1,10)*10000,random(0,10)/10, random(0, 10)/10)));
			armadeturno2->getPhysicsBody()->setCollisionBitmask(true);
			armadeturno2->getPhysicsBody()->setContactTestBitmask(true);
			break;
		}

	};
	menu1 = Menu::create(pauseBtn, tiendaBtn, vestuarioBtn, NULL);
	menu1->setPosition(Point(180, visibleSize.height - pauseBtn->getContentSize().height/2));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerPause, this);
	menu1->alignItemsHorizontally();
	addChild(menu1, 6);

	auto arsenalBtn = MenuItemImage::create("images/Nivel/Botones/arsenal_btn_good_res_idle.png", "images/Nivel/Botones/arsenal_btn_good_res.png", CC_CALLBACK_1(Nivel::abrirArsenal, this));
	auto simulacionBtn = MenuItemImage::create("images/Nivel/Botones/play_btn_good_res_idle.png", "images/Nivel/Botones/play_btn_good_res.png", CC_CALLBACK_1(Nivel::simulacion, this));


	menu2 = Menu::create(arsenalBtn, simulacionBtn, NULL);
	menu2->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 3, arsenalBtn->getContentSize().height-15));
	menu2->alignItemsHorizontally();
	addChild(menu2, 6);

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
	addChild(menuArsenal, 6);
	menuArsenal->setVisible(false);
}

void Nivel::colocaFondo(std::vector<std::string> fondos){

	Size visibleSize = Director::getInstance()->getVisibleSize();

	background = Sprite::create(fondos[0]);

	
	background->retain();
	background->setPosition(background->getContentSize().width, visibleSize.height);
	background->setAnchorPoint(Vec2(1, 1));
	background->setName("Limites");
	addChild(background,0);

	background1 = Sprite::create(fondos[1]);

	addChild(background1, 1);

	background1->setPosition(background1->getContentSize().width, visibleSize.height);
	background1->setAnchorPoint(Vec2(1, 1));
	background1->retain();


	background2 = Sprite::create(fondos[2]);
	addChild(background2, 3);

	background2->setPosition(background2->getContentSize().width, visibleSize.height);
	background2->setAnchorPoint(Vec2(1, 1));
	background2->retain();

	muralla = Sprite::create(fondos[3]);
	addChild(muralla, 5);
	auto limitesEscenario = PhysicsBody::createEdgeBox(Size(background->getContentSize().width, 668), PhysicsMaterial(0.5f, 0.0f, 0.5f), 0.3);
	limitesEscenario->setPositionOffset(Vec2(0, 200));
	muralla->setPhysicsBody(limitesEscenario);
	muralla->getPhysicsBody()->setContactTestBitmask(true);
	muralla->getPhysicsBody()->setCollisionBitmask(true);
	muralla->getPhysicsBody()->setDynamic(false);
	muralla->setName("Limites");

	muralla->setPosition(muralla->getContentSize().width, visibleSize.height);
	muralla->setAnchorPoint(Vec2(1, 1));
	muralla->retain();

}

void Nivel::colocaZerrin()
{
	auto zerrin = Global::getInstance()->zerrin;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	zerrin->setPosition(Point(350 + Global::getInstance()->zerrin->getContentSize().width / 2
		, visibleSize.height / 3 + zerrin->getContentSize().height/2));
	zerrin->setRotation(0);
	zerrin->setPhysicsBody(PhysicsBody::createBox(Global::getInstance()->zerrin->getBoundingBox().size, PhysicsMaterial(70.0, 0.0f, 0)));
	zerrin->getPhysicsBody()->setDynamic(true);
	zerrin->getPhysicsBody()->setCollisionBitmask(true);
	zerrin->getPhysicsBody()->setContactTestBitmask(true);
	zerrin->getPhysicsBody()->setVelocity(Vec2(0.0, 0.0));
	zerrin->getPhysicsBody()->setVelocityLimit(1500.0);
	zerrin->getPhysicsBody()->setAngularDamping(0.2);
	zerrin->getPhysicsBody()->setLinearDamping(0.3);
	zerrin->setState(zerrin->ZERRINFSM::IDLE);
	zerrin->setVida(10000);
	zerrin->haLlegado = false;
}

void Nivel::colocaHUD()
{
	colocaBotones();
	displayArmasArsenal();
}

void Nivel::cargaFrasesKatahi(int n)
{
	auto bocadillo = Sprite::create("images/Nivel/Bocadillo_Zerrin.png");
	bocadillo->setAnchorPoint(Vec2(0.5, 0.5));
	bocadillo->setScaleX(-1);
	Label* fraseKatahi = Label::create();
	fraseKatahi->setString(Global::getInstance()->BateriaFrasesKatahi[n]);
	fraseKatahi->setAnchorPoint(Vec2(0.5,0.5));
	fraseKatahi->setTextColor(Color4B(138,31,114,255));
	fraseKatahi->setSystemFontSize(50.0);
	fraseKatahi->setPosition(Katahi->getPositionX(),Katahi->getPositionY()+Katahi->getBoundingBox().size.height+bocadillo->getBoundingBox().size.height/2);
	bocadillo->setPosition(fraseKatahi->getPosition());

	colocaFrase(bocadillo, fraseKatahi);
}

void Nivel::cargaFrasesZerrin(int n)
{
	Label* fraseZerrin = Label::create();
	auto bocadillo = Sprite::create("images/Nivel/Bocadillo_Zerrin.png");
	bocadillo->setAnchorPoint(Vec2(0.5, 0.5));
	bocadillo->setScaleX(-1);

	fraseZerrin->setString(Global::getInstance()->BateriaFrasesZerrin[n]);

	fraseZerrin->setPosition(Vec2(Global::getInstance()->zerrin->getPositionX(),Global::getInstance()->zerrin->getPositionY()+bocadillo->getBoundingBox().size.height));
	fraseZerrin->setTextColor(Color4B(19,33,138,255));
	fraseZerrin->setSystemFontSize(50.0);
	bocadillo->setPosition(fraseZerrin->getPosition());


	colocaFrase(bocadillo,fraseZerrin);

	
}

void Nivel::colocaFrase(Sprite * Bocadillo, Label * Frase)
{
	float altmax = Bocadillo->getBoundingBox().size.height;
	float anchmax = Bocadillo->getBoundingBox().size.width;
	bool entra = false;
	while (!entra) {
		if (Frase->getBoundingBox().size.width > anchmax || Frase->getBoundingBox().size.height > altmax) {
			Frase->setSystemFontSize(Frase->getSystemFontSize() / 2);
		}
		else entra = true;
	}
	addChild(Bocadillo, 5);
	addChild(Frase, 5);

	Bocadillo->setPosition(Frase->getPosition());
	Frase->runAction(Sequence::create(ScaleBy::create(0.5, 1.5), ScaleBy::create(1.5, 1), FadeOut::create(0.5),
		CallFuncN::create(CC_CALLBACK_1(Nivel::borraElementoTemporal, this, true)), NULL));
	Bocadillo->runAction(Sequence::create(DelayTime::create(2), FadeOut::create(0.5), CallFuncN::create(CC_CALLBACK_1(Nivel::borraElementoTemporal, this, true)), NULL));
}




void Nivel::setPhysicsWorld(cocos2d::PhysicsWorld * world)
{
	nivelPhysics = world;
	nivelPhysics->setGravity(Vec2(0, -200.0));
	nivelPhysics->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

}


int Nivel::getBackgroundWidth()
{
	auto s =muralla->getContentSize();
	return s.width;
}

Nivel::Nivel(int nivel, std::vector<std::string> fondos, int i_objetos, int u_objetos)
{
	preparaNivel(nivel, fondos, i_objetos, u_objetos);
}

Nivel::~Nivel()
{
}

cocos2d::PhysicsWorld * Nivel::getPhysicsWorld()
{
	return nivelPhysics;
}

cocos2d::Rect Nivel::getBackgroundSize()
{
	return 	background->getBoundingBox();

}
void Nivel::spawnNube(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto Nubecita = Nube::create();
	this->addChild(Nubecita, 1);
	auto rand = random(1, 3);
	if (Global::getInstance()->juegoEnCurso) {
		Nubecita->setPosition(background->getContentSize().width + Nubecita->getContentSize().width,
			visibleSize.height - Nubecita->getContentSize().height*rand);
		Nubecita->spawnNube(dt);
	}
	else {
		for (int i = 0; i < 2; i++) {
			auto Nubecita = Nube::create();
			this->addChild(Nubecita, 1);
			Nubecita->setPosition(visibleSize.width*random(100,300) / 100.0 + Nubecita->getContentSize().width,
				visibleSize.height - Nubecita->getContentSize().height*rand);
			Nubecita->spawnNube(dt);
		}

	}


}


void Nivel::mueveFondo(float v) {
	
	if ((Global::getInstance()->zerrin->getEstado()!=Global::getInstance()->zerrin->ZERRINFSM::IDLE) && Global::getInstance()->zerrin->getEstado() != Global::getInstance()->zerrin->ZERRINFSM::SALIENDO) {
		for (int i = 0; i < 10; i++) {
			//CCLOG("los objetos se mueven %f", - (v));
			Global::getInstance()->ObjetosTotalesEscenarios[i]->setPositionX(Global::getInstance()->ObjetosTotalesEscenarios[i]->getPositionX() - (v));
		}
	}
}


int Nivel::getPosXFondo()
{
	return muralla->getPositionX();
}

bool Nivel::onContactBegin(cocos2d::PhysicsContact & contact) {
	PhysicsBody*a = contact.getShapeA()->getBody();
	PhysicsBody*b = contact.getShapeB()->getBody();
	cocos2d::String* sa = cocos2d::String::create(a->getNode()->getName());
	cocos2d::String* sb = cocos2d::String::create(b->getNode()->getName());
	auto nombrea = a->getNode()->getName();
	auto nombreb = b->getNode()->getName();
	auto zerrin = Global::getInstance()->zerrin;
	if (a->getNode()->getName() == "Limites") {
		if (b->getNode()->getName() == "Zerrin") {
			if ((zerrin->getEstado() == zerrin->ZERRINFSM::GOLPEADO_ALANTE) || (zerrin->getEstado() == zerrin->ZERRINFSM::GOLPEADO_ATRAS)) {
				if(zerrin->getPositionY()<=768/2)zerrin->setState(zerrin->ZERRINFSM::SUELO);
			}
			else zerrin->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		else if (b->getNode()->getName() == "Arma") return false;

	}
	else if (b->getNode()->getName() == "Limites") {
		if (a->getNode()->getName() == "Zerrin") {
			if ((zerrin->getEstado() == zerrin->ZERRINFSM::GOLPEADO_ALANTE) || (zerrin->getEstado() == zerrin->ZERRINFSM::GOLPEADO_ATRAS)) {
				if (zerrin->getPositionY()<=768 / 2)zerrin->setState(zerrin->ZERRINFSM::SUELO);
			}
			else zerrin->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		else if (a->getNode()->getName() == "Arma") return false;

	}
	else if (a->getNode()->getName() == "Arma") {
		if (b->getNode()->getName() == "Zerrin") {
			zerrin->muestraDaño(((Arma*)a->getNode())->getDaño());
			zerrin->setVida(zerrin->getVida() - ((Arma*)b->getNode())->getDaño());
			((Arma*)a->getNode())->accionColision(((Arma*)a->getNode())->getTipo());
			zerrin->accionColision(a->getNode()->getPositionX() >= zerrin->getPositionX(),1, ((Arma*)a->getNode())->getTipo());

			if (zerrin->getVida() <= 0) {
				if (zerrin->getChildrenCount() > 0) zerrin->removeAllChildren();
				Global::getInstance()->katahi->modificaOro(100);
				goToWinScene();
			}
		}
	}
	else if (b->getNode()->getName() == "Arma") {
		if (a->getNode()->getName() == "Zerrin") {
			zerrin->muestraDaño(((Arma*)b->getNode())->getDaño());
			zerrin->setVida(zerrin->getVida() - ((Arma*)b->getNode())->getDaño());
			((Arma*)b->getNode())->accionColision(((Arma*)b->getNode())->getTipo());
			zerrin->accionColision(b->getNode()->getPositionX() >= zerrin->getPositionX(), 1, ((Arma*)b->getNode())->getTipo());
			if (zerrin->getVida() <= 0) {
				if (zerrin->getChildrenCount() > 0) Global::getInstance()->zerrin->removeAllChildren();
				Global::getInstance()->katahi->modificaOro(100);
				goToWinScene();
			}
		}
	}
	else if (b->getNode()->getName() == "Zerrin") {
		if (a->getNode()->getName() == "Objeto") {

			zerrin->posicionAnterior =zerrin->getPositionX();
			zerrin->muestraDaño(((ObjetoEscenario*)a->getNode())->getDaño());
			zerrin->setVida(zerrin->getVida() - ((ObjetoEscenario*)a->getNode())->getDaño());

			zerrin->accionColision(a->getNode()->getPositionX() >= zerrin->getPositionX(), 0, ((ObjetoEscenario*)a->getNode())->getTipo());
			((ObjetoEscenario *)a)->accionColision(a->getNode());

			if (zerrin->getVida() <= 0) {
				if (zerrin->getChildrenCount() > 0) Global::getInstance()->zerrin->removeAllChildren();
				Global::getInstance()->katahi->modificaOro(100);
				goToWinScene();
			}
		} 
	}
	else if (a->getNode()->getName() == "Zerrin") {
		if (b->getNode()->getName() == "Objeto") {
			zerrin->posicionAnterior =zerrin->getPositionX();
			zerrin->muestraDaño(((ObjetoEscenario*)b->getNode())->getDaño());
			zerrin->setVida(zerrin->getVida() - ((ObjetoEscenario*)b->getNode())->getDaño());

			zerrin->accionColision(b->getNode()->getPositionX() >= zerrin->getPositionX(), 0, ((ObjetoEscenario*)b->getNode())->getTipo());
			((ObjetoEscenario *)b)->accionColision(b->getNode());

			

			if (zerrin->getVida() <= 0) {
				if (zerrin->getChildrenCount() > 0) zerrin->removeAllChildren();
				Global::getInstance()->katahi->modificaOro(100);
				goToWinScene();
			}
		}
		
	}

	CCLOG("contacto de %s con %s", sa->getCString(), sb->getCString());
	return true;
}

bool Nivel::onContactPreSolve(cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
	PhysicsBody*a = contact.getShapeA()->getBody();
	PhysicsBody*b = contact.getShapeB()->getBody();
	cocos2d::String* sa = cocos2d::String::create(a->getNode()->getName());
	cocos2d::String* sb = cocos2d::String::create(b->getNode()->getName());
	auto zerrin = Global::getInstance()->zerrin;
	if ((a->getNode()->getName() == "Zerrin"&& b->getNode()->getName() == "Limites") || (b->getNode()->getName() == "Zerrin"&& a->getNode()->getName() == "Limites")) {
		solve.setRestitution(0.0);
	}
	return true;
}

void Nivel::onContactPostSolve(PhysicsContact & contact, const PhysicsContactPostSolve & solve)
{
	PhysicsBody*a = contact.getShapeA()->getBody();
	PhysicsBody*b = contact.getShapeB()->getBody();
	if (((a->getNode()->getName() == "Zerrin"&& b->getNode()->getName() == "Limites") || (b->getNode()->getName() == "Zerrin"&& a->getNode()->getName() == "Limites"))
		&& (Global::getInstance()->zerrin->getEstado() == Global::getInstance()->zerrin->ZERRINFSM::CORRIENDO ||
			Global::getInstance()->zerrin->getEstado() == Global::getInstance()->zerrin->ZERRINFSM::IDLE)) {
		if (Global::getInstance()->zerrin->getPhysicsBody()->getVelocity().y > 0)
			Global::getInstance()->zerrin->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

void Nivel::removeKatahi()
{
	if (Katahi != nullptr)Katahi->removeFromParentAndCleanup(true);
}



void Nivel::addContactListener()
{
	this->listenerColision = EventListenerPhysicsContact::create();

	this->listenerColision->onContactBegin = CC_CALLBACK_1(Nivel::onContactBegin, this);
	this->listenerColision->onContactPreSolve = CC_CALLBACK_2(Nivel::onContactPreSolve, this);
	this->listenerColision->onContactPostSolve = CC_CALLBACK_2(Nivel::onContactPostSolve, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerColision, this);
}


void Nivel::borraElementoTemporal(Node * emisor, bool limpia)
{
	emisor->removeFromParentAndCleanup(limpia);
}



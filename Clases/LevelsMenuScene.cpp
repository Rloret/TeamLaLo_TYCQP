#include "LevelsMenuScene.h"
#include "proj.win32\Nivel.h"
#include "proj.win32\Global.h"
#include "Arma.h"
#include "SimpleAudioEngine.h"
#include"AudioEngine.h"

using namespace cocos2d::experimental;
USING_NS_CC;

Scene* LevelsMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelsMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	scene->setTag(100);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelsMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//meter imagenes mundos en array
	Sprite* mundo1 = Sprite::create("images/LevelsMenuScene/mundo1.png");
	imagenesMundos.push_back(mundo1);
	Sprite* mundo2 = Sprite::create("images/LevelsMenuScene/mundo_development.png");
	imagenesMundos.push_back(mundo2);
	Sprite* mundo3 = Sprite::create("images/LevelsMenuScene/mundo_development.png");
	imagenesMundos.push_back(mundo3);
	Sprite* mundo4 = Sprite::create("images/LevelsMenuScene/mundo_development.png");
	imagenesMundos.push_back(mundo4);
	Sprite* mundo5 = Sprite::create("images/LevelsMenuScene/mundo_development.png");
	imagenesMundos.push_back(mundo5);


	mundoSeleccionado = 0;

	for (int i = 0; i < 5; i++){
		imagenesMundos[i]->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
		addChild(imagenesMundos[i],2);
		if (i+1 != 1) imagenesMundos[i]->setVisible(false);
	}

	auto bolaBackground = Sprite::create("images/LevelsMenuScene/Bola_Bckgrnd.png");
	bolaBackground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bolaBackground->setScale(0.95);
	this->addChild(bolaBackground, 1);
	// array btn
	auto itemimgaux = MenuItemImage::create("images/LevelsMenuScene/nivel_nosign_0_btn.png", "images/LevelsMenuScene/nivel_nosign_0_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this, 10));
	auto menuaux = Menu::create(itemimgaux, NULL);
	std::string auxstring = "Nivel" + ((char)0);
	menuaux->setName(auxstring);
	this->vectorNiveles.push_back(menuaux);
	this->addChild(vectorNiveles[0], 3);
	vectorNiveles[0]->setVisible(false);


	itemimgaux = MenuItemImage::create("images/LevelsMenuScene/nivel_3_idle_btn.png", "images/LevelsMenuScene/nivel_3_pressed_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this, 3));
	menuaux = Menu::create(itemimgaux, NULL);
	auxstring = "Nivel" + ((char)1);
	menuaux->setName(auxstring);
	this->vectorNiveles.push_back(menuaux);
	this->addChild(vectorNiveles[1], 3);
	vectorNiveles[1]->setVisible(false);

	itemimgaux = MenuItemImage::create("images/LevelsMenuScene/nivel_2_idle_btn.png", "images/LevelsMenuScene/nivel_2_pressed_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this, 2));
	menuaux = Menu::create(itemimgaux, NULL);
	auxstring = "Nivel" + ((char)2);
	menuaux->setName(auxstring);
	this->vectorNiveles.push_back(menuaux);
	this->addChild(vectorNiveles[2], 3);
	vectorNiveles[2]->setVisible(false);

	itemimgaux = MenuItemImage::create("images/LevelsMenuScene/nivel_nosign_3_btn.png", "images/LevelsMenuScene/nivel_nosign_3_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this, 10));
	menuaux = Menu::create(itemimgaux, NULL);
	auxstring = "Nivel" + ((char)3);
	menuaux->setName(auxstring);
	this->vectorNiveles.push_back(menuaux);
	this->addChild(vectorNiveles[3], 3);
	vectorNiveles[3]->setVisible(false);

	itemimgaux = MenuItemImage::create("images/LevelsMenuScene/nivel_0_idle_btn.png", "images/LevelsMenuScene/nivel_0_pressed_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this, 0));
	menuaux = Menu::create(itemimgaux, NULL);
	auxstring = "Nivel" + ((char)4);
	menuaux->setName(auxstring);
	this->vectorNiveles.push_back(menuaux);
	this->addChild(vectorNiveles[4], 3);
	vectorNiveles[4]->setVisible(false);

	for (int i = 5; i < 25;i++){

		String * imagen;
		if (i >= 5) {
			imagen = String::createWithFormat("images/LevelsMenuScene/nivel_nosign_%d_btn.png", (i % 5));
			int iteradorimg = (i % 5);
			
		}
		else {
			imagen = String::createWithFormat("images/LevelsMenuScene/nivel_nosign_%d_btn.png", i);
		}
		auto itemimgaux = MenuItemImage::create(imagen->getCString(), imagen->getCString(),
												CC_CALLBACK_1(LevelsMenuScene::goToNivel,this,10));
		auto menuaux = Menu::create(itemimgaux, NULL);
		std::string auxstring = "Nivel" + ((char)i);
		menuaux->setName(auxstring);
		this->vectorNiveles.push_back(menuaux);
		this->addChild(menuaux,3);
		vectorNiveles[i]->setVisible(false);
	}
	
	auto backBtn = MenuItemImage::create("images/AjustesScene/flecha.png", "images/AjustesScene/flecha2.png",
		CC_CALLBACK_1(LevelsMenuScene::goToMenuStart, this));

	auto menu1 = Menu::create(backBtn, NULL);
	menu1->alignItemsHorizontallyWithPadding(visibleSize.width / 2);
	menu1->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(menu1, 2);

	brightEffect = Sprite::create("images/LevelsMenuScene/Bola_Bckgrnd.png_light.png");
	
	auto masBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha2.png", 
		CC_CALLBACK_1(LevelsMenuScene::muestraUnoMas,this));
	masBtn->setScaleX(-1);
	//masBtn->setPosition(brightEffect->getBoundingBox().size.width*0.75,384);

	auto menosBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha2.png",
		CC_CALLBACK_1(LevelsMenuScene::muestraUnoMenos, this));
	//menosBtn->setPosition(- brightEffect->getBoundingBox().size.width*0.75, 384);
	auto menu2 = Menu::create( menosBtn,masBtn, NULL);
	menu2->alignItemsHorizontallyWithPadding(visibleSize.width / 2);
	menu2->setPosition(Point(visibleSize.width / 2-70,visibleSize.height/2));
	addChild(menu2, 2);
	//Fondo
	auto background = Sprite::create("images/LevelsMenuScene/fondo_LevelsScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);


	fadingEffect = Sprite::create("images/LevelsMenuScene/Fading_effect.png");
	fadingEffect->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(fadingEffect, 5);
	
	brightEffect->setOpacity(0);
	brightEffect->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(brightEffect, 5);
	this->activaBrightEffect();


	songLevelsMenuID=AudioEngine::play2d("sounds/LevelsMenuScene.mp3", true, 0.0);
	AudioEngine::pause(songLevelsMenuID);

	return true;
}


void LevelsMenuScene::goToMenuStart(Ref *pSender){
	AudioEngine::play2d("sounds/Back_Btn.mp3", false, 0.8);
	AudioEngine::pause(songLevelsMenuID);
	
	Director::getInstance()->popScene();
}


void  LevelsMenuScene::muestraUnoMas(Ref *pSender){
	AudioEngine::play2d("sounds/Boton_MainMenuScene_1.mp3", false, 0.7);

	if (mundoSeleccionado < 4){
	
		imagenesMundos[mundoSeleccionado]->setVisible(false);
		ocultaNivelesVisibles(mundoSeleccionado);
		mundoSeleccionado += 1;
		imagenesMundos[mundoSeleccionado]->setVisible(true);
	}
	else {
		imagenesMundos[mundoSeleccionado]->setVisible(false);
		ocultaNivelesVisibles(mundoSeleccionado);
		mundoSeleccionado = 0;
		imagenesMundos[mundoSeleccionado]->setVisible(true);

	}
	if (mundoSeleccionado == 0) 
		brightEffect->setColor(Color3B::WHITE);
	else brightEffect->setColor(Color3B::Color3B(243, 216, 160));
	addListener();
}


void  LevelsMenuScene::muestraUnoMenos(Ref *pSender){
	AudioEngine::play2d("sounds/Boton_MainMenuScene_1.mp3",false,0.7);
	if (mundoSeleccionado > 0){

		imagenesMundos[mundoSeleccionado]->setVisible(false);
		ocultaNivelesVisibles(mundoSeleccionado);
		mundoSeleccionado -= 1;
		imagenesMundos[mundoSeleccionado]->setVisible(true);
	}
	else {
		imagenesMundos[mundoSeleccionado]->setVisible(false);
		ocultaNivelesVisibles(mundoSeleccionado);
		mundoSeleccionado = 4;
		imagenesMundos[mundoSeleccionado]->setVisible(true);

	}
	if (mundoSeleccionado == 0) brightEffect->setColor(Color3B::WHITE);
	else brightEffect->setColor(Color3B::Color3B(243, 216, 160));
	addListener();

}

void LevelsMenuScene::addListener(){
	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
	
	cocos2d::Point p = touch->getLocation();
	cocos2d::Rect rect = Rect(Director::getInstance()->getVisibleSize().width/2-568/2, Director::getInstance()->getVisibleSize().height / 2-222,
											568, 444);

		if (rect.containsPoint(p)){
				return true;
		}

		return false;
	};


	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event){
			LevelsMenuScene::touchEvent(touch, touch->getLocation());
			Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

}

void LevelsMenuScene::touchEvent(cocos2d::Touch * touch, cocos2d::Point _p)
{
	AudioEngine::play2d("sounds/LevelsMenuSceneTap_Nivel.mp3", false, 0.8);
	LevelsMenuScene::muestraNivelesBtn();
	imagenesMundos[mundoSeleccionado]->setVisible(false);
}

void LevelsMenuScene::ocultaNivelesVisibles(int mundoseleccionado)
{
	for (int i = mundoSeleccionado * 5; i < ((mundoSeleccionado * 5) + 5); i++) {
		vectorNiveles[i]->setVisible(false);
	}
}

void LevelsMenuScene::activaBrightEffect()
{
	fadingEffect->runAction(RepeatForever::create(Sequence::create(FadeTo::create(3, 0), FadeTo::create(3, 255), NULL)));
	brightEffect->runAction(RepeatForever::create(Sequence::create(FadeTo::create(3, 180), FadeTo::create(3, 0), NULL)));
}

void LevelsMenuScene::borraElementoTemporal(Node * emisor, bool limpia)
{
	emisor->removeFromParentAndCleanup(limpia);
}

void LevelsMenuScene::añadeNivel(cocos2d::Scene * nivel, int inicioObjetos, int finObjetos)
{
	Global::getInstance()->inicioObj = inicioObjetos;
	Global::getInstance()->finalObj = finObjetos;
	Director::getInstance()->pushScene(nivel);
	Global::getInstance()->abreEstanteria();
	Global::getInstance()->colocaFondo(fondosPasar);

}

void LevelsMenuScene::onEnterTransitionDidFinish()
{
	if (nivelpulsado != nullptr) nivelpulsado->setEnabled(true);
	addListener();
	activaBrightEffect();
	brightEffect->setOpacity(0);
	
	
	AudioEngine::setVolume(songLevelsMenuID ,0.9);
	AudioEngine::resume(songLevelsMenuID);
}

void LevelsMenuScene::goToNivel(Ref *psender,int i){
	Label*	notAvailableLabel;
	nivelpulsado = (MenuItemImage*)psender;
	nivelpulsado->setEnabled(false);

	cocos2d::Scene* cene;
	switch (i)
	{
	case 0:
		_eventDispatcher->removeEventListener(this->listener);
		if(fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Escenarios/Habitacion_fondo.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Habitacion_segundo_plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Habitacion_tercer_plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Habitacion_primer_plano.png");
		cene = Nivel::createScene(0,fondosPasar, 0, 0);

		Global::getInstance()->RecompensaOro = 80;
		Global::getInstance()->RecompensaMechones = 2;
		Global::getInstance()->zerrin->setVida(20);
		añadeNivel(cene, 0, 0);
		AudioEngine::pause(songLevelsMenuID);
		break;


	case 2:
		_eventDispatcher->removeEventListener(this->listener);
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(2,fondosPasar, 0, 1);
		Global::getInstance()->zerrin->setVida(140);
		Global::getInstance()->RecompensaOro =50;
		Global::getInstance()->RecompensaMechones = 0;

		añadeNivel(cene, 0, 1);
		AudioEngine::pause(songLevelsMenuID);
		break;

	case 3:
		_eventDispatcher->removeEventListener(this->listener);
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Escenarios/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(3,fondosPasar, 1, 3);
		Global::getInstance()->zerrin->setVida(260);
		Global::getInstance()->RecompensaOro = 50;
		Global::getInstance()->RecompensaMechones = 0;

		añadeNivel(cene, 1,3);
		AudioEngine::pause(songLevelsMenuID);
		break;

	default:
		AudioEngine::play2d("sounds/LevelsMenuSceneTap_No_Signal.mp3", false, 1.0);

		notAvailableLabel = Label::createWithSystemFont("NOT AVAILABLE YET.", "Arial", 60);
		notAvailableLabel->setColor(Color3B::RED);
		notAvailableLabel->enableShadow();
		notAvailableLabel->setPosition(Global::getInstance()->visibleSize.width / 2, Global::getInstance()->visibleSize.height / 2 + notAvailableLabel->getContentSize().height * 2);
		this->addChild(notAvailableLabel,8);
		notAvailableLabel->runAction(Sequence::create(ScaleBy::create(0.5, 1.5), ScaleBy::create(0.5, 0.5), FadeOut::create(0.2), CallFuncN::create(CC_CALLBACK_1(LevelsMenuScene::borraElementoTemporal, this, true)), NULL));
		nivelpulsado->setEnabled(true);
		break;
	}
	
}


void LevelsMenuScene::muestraNivelesBtn(){
	int posant = 0;

	for (int i = mundoSeleccionado*5; i < ((mundoSeleccionado * 5)+5); i++) {

		if(i == mundoSeleccionado * 5){
			vectorNiveles[i]->setPositionY(imagenesMundos[mundoSeleccionado]->getPosition().y -
				imagenesMundos[mundoSeleccionado]->getContentSize().height / 2 + vectorNiveles[i]->getContentSize().height / 25+3);
		}
		else {
			vectorNiveles[i]->setPositionY(posant + (imagenesMundos[mundoSeleccionado]->getContentSize().height / 5));
		}
		posant = vectorNiveles[i]->getPositionY();
		vectorNiveles[i]->setVisible(true);	

	}


}
                      

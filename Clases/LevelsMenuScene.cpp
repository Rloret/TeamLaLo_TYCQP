#include "LevelsMenuScene.h"
#include "proj.win32\Nivel.h"
#include "proj.win32\Global.h"
#include "Arma.h"
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
	Sprite* mundo2 = Sprite::create("images/LevelsMenuScene/mundo2.png");
	imagenesMundos.push_back(mundo2);
	Sprite* mundo3 = Sprite::create("images/LevelsMenuScene/mundo3.png");
	imagenesMundos.push_back(mundo3);
	Sprite* mundo4 = Sprite::create("images/LevelsMenuScene/mundo1.png");
	imagenesMundos.push_back(mundo4);
	Sprite* mundo5 = Sprite::create("images/LevelsMenuScene/mundo2.png");
	imagenesMundos.push_back(mundo5);


	mundoSeleccionado = 0;

	for (int i = 0; i < 5; i++){
		imagenesMundos[i]->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
		addChild(imagenesMundos[i],2);
		if (i+1 != 1) imagenesMundos[i]->setVisible(false);
	}

	// array btn
	for (int i = 0; i < 25;i++){

		auto itemimgaux = MenuItemImage::create("images/LevelsMenuScene/back_btn.png", "images/LevelsMenuScene/back_btn.png",
												CC_CALLBACK_1(LevelsMenuScene::goToNivel,this,i));
		auto menuaux = Menu::create(itemimgaux, NULL);
		auto rand = cocos2d::RandomHelper::random_int(100, 230);
		menuaux->setColor(Color3B( rand, rand, 100));
		std::string auxstring = "Nivel" + ((char)i);
		menuaux->setName(auxstring);
		this->vectorNiveles.push_back(menuaux);
		this->addChild(vectorNiveles[i],3);
		vectorNiveles[i]->setVisible(false);
		//CCLOG("i vale %d", i);
	}
	//CCLOG("vector ocupa: %d", vectorNiveles.capacity());
	
	
	//menu
	
	auto backBtn = MenuItemImage::create("images/LevelsMenuScene/back_btn.png", "images/LevelsScene/back_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToMenuStart, this));

	/*auto startNivelBtn = MenuItemImage::create("images/LevelsMenuScene/back_btn.png", "images/LevelsScene/back_btn.png",
		CC_CALLBACK_1(LevelsMenuScene::goToNivel, this));
	startNivelBtn->setColor(Color3B(1,1,1));*/

	auto menu1 = Menu::create(backBtn/*,startNivelBtn*/, NULL);
	menu1->alignItemsHorizontallyWithPadding(visibleSize.width / 2);
	menu1->setPositionY(10);
	addChild(menu1, 2);

	
	auto masBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha.png", 
		CC_CALLBACK_1(LevelsMenuScene::muestraUnoMas,this));
	masBtn->setScaleX(-1);

	auto menosBtn = MenuItemImage::create("images/LevelsMenuScene/Flecha.png", "images/LevelsMenuScene/Flecha.png",
		CC_CALLBACK_1(LevelsMenuScene::muestraUnoMenos, this));

	auto menu2 = Menu::create( menosBtn,masBtn, NULL);
	menu2->alignItemsHorizontallyWithPadding(visibleSize.width / 2);
	menu2->setPositionY(visibleSize.height-50);
	addChild(menu2, 2);
	//Fondo
	auto background = Sprite::create("images/LevelsScene/fondo_LevelsScene.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background, 0);


	return true;
}


void LevelsMenuScene::goToMenuStart(Ref *pSender){

	Director::getInstance()->popScene();
}


void  LevelsMenuScene::muestraUnoMas(Ref *pSender){
	CCLOG("%d", mundoSeleccionado);
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
	addListener();
}


void  LevelsMenuScene::muestraUnoMenos(Ref *pSender){
	CCLOG("%d", mundoSeleccionado);

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
			CCLOG("QUITO LISTENER");
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

}

void LevelsMenuScene::touchEvent(cocos2d::Touch * touch, cocos2d::Point _p)
{

	//CCLOG("no hay listener")
	LevelsMenuScene::muestraNivelesBtn();
}

void LevelsMenuScene::ocultaNivelesVisibles(int mundoseleccionado)
{
	for (int i = mundoSeleccionado * 5; i < ((mundoSeleccionado * 5) + 5); i++) {
		vectorNiveles[i]->setVisible(false);
	}
}

void LevelsMenuScene::onEnterTransitionDidFinish()
{
	addListener();
}

void LevelsMenuScene::goToNivel(Ref *psender,int i){
	//cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	_eventDispatcher->removeEventListener(this->listener);

	cocos2d::Scene* cene;
	//Aqui SWITCH con el numero de nivel que es para saber que objetos tenemos que pasarle
	switch (i)
	{
	case 0:

		if(fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar,0, 10);	
		break;

	case 1:

		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);	
		break;

	case 2:
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);

		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);	
		break;

	case 3:
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);	
		break;

	case 4:

		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);		
		break;

	case 5:
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);
		break;

	default:
		if (fondosPasar.size()>0)fondosPasar.clear();
		fondosPasar.push_back("images/Nivel/Castillo_Fondo.png");
		fondosPasar.push_back("images/Nivel/Castillo_Tercer_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Nubes.png");
		fondosPasar.push_back("images/Nivel/Castillo_Segundo_Plano.png");
		fondosPasar.push_back("images/Nivel/Castillo_Primer_Plano.png");
		cene = Nivel::createScene(fondosPasar, 0, 10);
		Director::getInstance()->pushScene(cene);
		Global::getInstance()->colocaObjetos(0, 10);
		//((Nivel*)Global::getInstance()->nivel)->preparaNivel(fondosPasar, 0, 10);
		break;
	}
	//Director::getInstance()->pushScene(Global::getInstance()->nivel);
	//Director::getInstance()->pushScene(cene);
	
}


void LevelsMenuScene::muestraNivelesBtn(){
	int posant = 0;
	for (int i = mundoSeleccionado*5; i < ((mundoSeleccionado * 5)+5); i++) {
		CCLOG("desde %d hasta %d", i, ((mundoSeleccionado * 5) + 5));
		if(i == mundoSeleccionado * 5){
			vectorNiveles[i]->setPositionX(imagenesMundos[mundoSeleccionado]->getPosition().x -
				imagenesMundos[mundoSeleccionado]->getContentSize().width / 2 + vectorNiveles[i]->getContentSize().width / 25);
				//(i-mundoSeleccionado*5))/5); //((i / 5) * 568)
		}
		else {
			vectorNiveles[i]->setPositionX(posant + (imagenesMundos[mundoSeleccionado]->getContentSize().width / 5));
		}
		posant = vectorNiveles[i]->getPositionX();
		vectorNiveles[i]->setVisible(true);	

	}


}
                      

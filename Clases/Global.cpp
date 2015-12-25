#include "Global.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "TiendaScene.h"
#include "KatahiClass.h"

USING_NS_CC;


static Global* global = nullptr;

Global::Global(){
	//inicializar escenas a null
	 nivel = nullptr;
	 layerObjects = nullptr;
	 levelsMenuScene = LevelsMenuScene::createScene();

	 zerrin = ZerrinClass::create();
	 katahi = KatahiClass::create();
	 
	// nivel->retain();
	 levelsMenuScene->retain();

	 creaArmas();
	 creaObjetosEscenario();
	 visibleSize = Director::getInstance()->getVisibleSize();
	 armaAComprar = nullptr;
//	 Camara = nullptr;

	// CCLOG("me he iniciado por primera vez");
}
void Global::añadeArmasANivel(Arma* a){
	layerObjects->addChild(a, 3);
	//CCLOG("tag de la current sin type %d tag de la current con type %d", Director::getInstance()->getRunningScene()->getTag(), ((Nivel*)Director::getInstance()->getRunningScene())->getTag());
	//CCLOG("tag de la almacenada en global %d ", this->nivel->getTag());
	ArmasNivel.push_back(a);
	//CCLOG("tamaño %d", ArmasNivel.size());
}

void Global::creaArmas()
{
	//TAMAÑO ESTANDARD ARMAS 84x84

	//Prueba dagas
	Texture2D* d = Director::getInstance()->getTextureCache()->addImage("images/Armas/dagas.png");
	Arma* dagas = Arma::create(d,20,"dagas",0,50, random(0, 1));
	dagas->setVisible(false);
	dagas->setPosition(-200, -200);
	armasTotales.push_back(dagas);

	//Bola de demolicion
	Texture2D *b= Director::getInstance()->getTextureCache()->addImage("images/Armas/bola.png");
	Arma* bola = Arma::create(b, 100, "bola", 2, 0, 0);
	bola->setVisible(false);
	bola->setPosition(-200, -200);
	armasTotales.push_back(bola);

	Texture2D *c = Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_activos.png");
	Arma* pinchos = Arma::create(c, 100, "pinchos", 3, 0, 0);
	pinchos->setVisible(false);
	pinchos->setPosition(-200, -200);
	armasTotales.push_back(pinchos);

	Texture2D *e = Director::getInstance()->getTextureCache()->addImage("images/Armas/mina_no_activa.png");
	Arma* mina = Arma::create(e, 100, "mina", 4, 0, 0);
	mina->setVisible(false);
	mina->setPosition(-200, -200);
	armasTotales.push_back(mina);

	Texture2D *f = Director::getInstance()->getTextureCache()->addImage("images/Armas/trampilla.png");
	Arma* trampilla = Arma::create(f, 100, "trampilla", 5, 0, 0);
	trampilla->setVisible(false);
	trampilla->setPosition(-200, -200);
	armasTotales.push_back(trampilla);


	Texture2D* t = Director::getInstance()->getTextureCache()->addImage("images/Armas/arma.png");

	//provisional crea un array genérico, en un futuro hay que meter las armas 1 a una
	for (int i = 5; i <20; i++){
		char* nombre = "espada Bastarda numero: ";
		nombre += i;
		Arma* armaaux = Arma::create(t, 15+i, nombre, 1,i*10+1,random(0,1));
		armaaux->setColor(Color3B(i * 25, i * 25, i * 25));
		armaaux->setPosition(-200, -200);
		//armaaux->setAnchorPoint(Vec2(0.5, 0.5));
		//armaaux->setScale(84 / armaaux->getContentSize().width, 84 / armaaux->getContentSize().height);
		armasTotales.push_back(armaaux);
		armaaux->setVisible(false);
	}

}

void Global::creaObjetosEscenario()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	//provisional crea un array genérico, en un futuro hay que meter los objetos 1 a 1
	for (int i = 0; i < 10; i++) {
		char* nombre = "Objeto Escenario numero: ";
		nombre += i;

		//ObjetosTotalesEscenarioPosiciones.push_back(&Vec2(((i + 1)*visiblesize.width) / 10, visiblesize.height / 2));
		ObjetoEscenario* objetoaux = ObjetoEscenario::create("images/ObjetosEscenario/Baul.png", random(9,12), nombre,i%2==0?1:2);
		Vec2 punto = Vec2(((i*5 + 100)*visiblesize.width) / 10 - objetoaux->getContentSize().width, visiblesize.height / 2);
		objetoaux->setPosition(punto);
		objetoaux->setColor(Color3B(i * 25, i * 25, i * 25));
		ObjetosTotalesEscenarios.push_back(objetoaux);
	}
}

Global* Global::getInstance(){

	if (!global){
		global = new Global();
	}

	return global;
}

void Global::vaciaArmasNivel(){
	ArmasNivel.clear();
}

void Global::quitaArmaDeNivel(Arma*a){

	for (int i = 0; i<ArmasNivel.size(); i++) {
		if (ArmasNivel[i] == a) {
			layerObjects->removeChild(a);
			a->clon->enNivel = false;
			a->clon = nullptr;
			ArmasNivel.erase(ArmasNivel.begin() + i);
			ContadorArmas--;
		}
	}
	recolocaArmasNivel();

}

void Global::colocaObjetos(int i_objetos, int u_objetos)
{
	for (int i = i_objetos; i < u_objetos; i++) {
		//CCLOG("Posicion antes %f %f ", Global::getInstance()->ObjetosTotalesEscenarios[i]->getPositionX(), Global::getInstance()->ObjetosTotalesEscenarios[i]->getPositionY());
		auto objetodeturno = Global::getInstance()->ObjetosTotalesEscenarios[i];
		objetodeturno->setVisible(true);
		Vec2 punto = Vec2(((i + 1) * 1024 * 1.5) / (u_objetos - i_objetos)
			+ 1024 
			- Global::getInstance()->ObjetosTotalesEscenarios[i]->getContentSize().width
			,(objetodeturno->getTipo()==1)? Director::getInstance()->getVisibleSize().height / 2: Director::getInstance()->getVisibleSize().height -objetodeturno->getContentSize().height*1.5);
		objetodeturno->setPosition(punto);
		objetodeturno->setPhysicsBody(nullptr);
		layerObjects->addChild(objetodeturno, 3);
		
		//CCLOG("Posicion dsps %f %f ", Global::getInstance()->ObjetosTotalesEscenarios[i]->getPositionX(), Global::getInstance()->ObjetosTotalesEscenarios[i]->getPositionY());

	}
}

void Global::colocaFondo(std::vector<std::string> fondos) {

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create(fondos[0]);

	//CCLOG("COLOCOLOSFONDOSSSS");
	background->retain();
	background->setPosition(background->getContentSize().width, visibleSize.height);
	background->setAnchorPoint(Vec2(1, 1));
	background->setName("Limites");
	nivel->addChild(background,0);

	auto background1 = Sprite::create(fondos[1]);

	nivel->addChild(background1, 1);

	background1->setPosition(background1->getContentSize().width, visibleSize.height);
	background1->setAnchorPoint(Vec2(1, 1));
	background1->retain();


	auto background2 = Sprite::create(fondos[3]);
	nivel->addChild(background2, 3);

	background2->setPosition(background2->getContentSize().width, visibleSize.height);
	background2->setAnchorPoint(Vec2(1, 1));
	background2->retain();

}


void Global::abreEstanteria()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto rectangulo2 = cocos2d::Sprite::create("images/Nivel/rectangle.png");

	rectangulo2->setScale((visibleSize.width *0.5)/rectangulo2->getContentSize().width,( visibleSize.height / 8)/rectangulo2->getContentSize().height);
	rectangulo2->setAnchorPoint(Point(1, 1));
	//rectangulo2->setPosition(Point(visibleSize.width / 2, visibleSize.height - rectangulo2->getBoundingBox().size.height / 2));
	rectangulo2->setPosition(Point(visibleSize.width,visibleSize.height));
	rectangulo2->setVisible(true);
	layerObjects->addChild(rectangulo2, 2);
}

void Global::recolocaArmasNivel()
{
	for (int i = 0; i< ArmasNivel.size(); i++) {
		ArmasNivel[i]->setPositionX((i+1) * 512 / 5 + 512 - ArmasNivel[i]->getContentSize().width / 2);
	}
}




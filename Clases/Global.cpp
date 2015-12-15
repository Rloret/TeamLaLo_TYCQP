#include "Global.h"
#include"proj.win32\Nivel.h"
#include"proj.win32\levelsMenuScene.h"
#include "TiendaScene.h"
#include "KatahiClass.h"

USING_NS_CC;


static Global* global = nullptr;

Global::Global(){
	//inicializar escenas a null
	 //nivel = nullptr;
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
	((Nivel*)Director::getInstance()->getRunningScene())->addChild(a, 2);
	auto rand = random(0, 19);
	a->setPosition(Point(200+rand*10, 500));
	ArmasNivel.push_back(a);
	//CCLOG("tamaño %d", ArmasNivel.size());
}

void Global::creaArmas()
{

	//Prueba dagas
	Texture2D* d = Director::getInstance()->getTextureCache()->addImage("images/Armas/dagas.png");
	Arma* dagas = Arma::create(d,20,"dagas",0,50, random(0, 1));
	dagas->setVisible(false);
	armasTotales.push_back(dagas);

	Texture2D* t = Director::getInstance()->getTextureCache()->addImage("images/Armas/arma.png");
	//provisional crea un array genérico, en un futuro hay que meter las armas 1 a una
	for (int i = 1; i < 20; i++){
		char* nombre = "espada Bastarda numero: ";
		nombre += i;
		Arma* armaaux = Arma::create(t, 15+i, nombre, 1,i*10+1,random(0,1));
		armaaux->setColor(Color3B(i * 25, i * 25, i * 25));
		armaaux->setPosition(-200, -200);
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
		ObjetoEscenario* objetoaux = ObjetoEscenario::create("images/ObjetosEscenario/Baul.png", random(9,12), nombre,1);
		Vec2 punto = Vec2(((i*5 + 100)*visiblesize.width) / 10 - objetoaux->getContentSize().width, visiblesize.height / 2);
		objetoaux->setPosition(punto);
		objetoaux->setColor(Color3B(i * 25, i * 25, i * 25));
		ObjetosTotalesEscenarios.push_back(objetoaux);
	}
}
/*
void Global::creaCamara()
{
	Camara = Follow::create(Global::getInstance()->zerrin,Rect(0,0,3072,768));
	Camara->retain();
}*/

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
			Director::getInstance()->getRunningScene()->removeChild(a);
			a->clon->enNivel = false;
			a->clon = nullptr;
			ArmasNivel.erase(ArmasNivel.begin() + i);
			//((Nivel*)nivel)->ContadorArmas--;
		}
	}
}


void Global::modificaNivel(Nivel* elnivel)
{
	nivel = elnivel;
}


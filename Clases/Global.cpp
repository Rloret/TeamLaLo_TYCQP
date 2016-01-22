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
	 
	 levelsMenuScene->retain();
	 creaArmas();
	 creaObjetosEscenario();
	 visibleSize = Director::getInstance()->getVisibleSize();
	 armaAComprar = nullptr;

	 letraPersonajes.fontFilePath = "fonts/Slackey.ttf";
	 letraPersonajes.fontSize = 120;
	 letraPersonajes.glyphs = GlyphCollection::DYNAMIC;
	 letraPersonajes.outlineSize = 0;
	 letraPersonajes.customGlyphs = nullptr;
	 letraPersonajes.distanceFieldEnabled = false;

	 for (int i = 0; i < 10; i++) {
		 nivelesJugados.push_back(0);
	 }
	
	 CreaFrases();

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

	Texture2D* d1 = Director::getInstance()->getTextureCache()->addImage("images/Armas/daga1.png");
	Arma* daga1 = Arma::create(d1,10,"daga_simple",0,5,0);
	armasTotales.push_back(daga1);
	daga1->SetRutaSonido(cocos2d::String::create("sounds/Daga_1.mp3"));
	daga1->disponible = true;


	Texture2D* d3 = Director::getInstance()->getTextureCache()->addImage("images/Armas/daga3.png");
	Arma* daga3 = Arma::create(d3, 10, "daga_cara", 0,5, 0);
	armasTotales.push_back(daga3);
	daga3->SetRutaSonido(cocos2d::String::create("sounds/Daga_1.mp3"));
	daga3->disponible = true;


	Texture2D* d2 = Director::getInstance()->getTextureCache()->addImage("images/Armas/daga2.png");
	Arma* daga2 = Arma::create(d2, 10, "daga_dientes", 0, 20, 0);
	armasTotales.push_back(daga2);
	daga2->SetRutaSonido(cocos2d::String::create("sounds/Daga_1.mp3"));
	daga2->disponible = true;

	Texture2D* d4 = Director::getInstance()->getTextureCache()->addImage("images/Armas/daga4.png");
	Arma* daga4 = Arma::create(d4, 10, "daga_serpientes", 0, 20, 0);
	armasTotales.push_back(daga4);
	daga4->SetRutaSonido (cocos2d::String::create("sounds/Daga_1.mp3"));
	daga4->disponible = true;

	Texture2D *b = Director::getInstance()->getTextureCache()->addImage("images/Armas/bola.png");
	Arma* bola = Arma::create(b, 40, "bola", 2, 90, 2);
	armasTotales.push_back(bola);
	bola->SetRutaSonido(cocos2d::String::create("sounds/Bola.mp3"));

	Texture2D *c = Director::getInstance()->getTextureCache()->addImage("images/Armas/pinchos_activos.png");
	Arma* pinchos = Arma::create(c, 20, "pinchos", 3, 60, 0);
	armasTotales.push_back(pinchos);
	pinchos->SetRutaSonido(cocos2d::String::create("sounds/Pinchos.mp3"));

	Texture2D *f = Director::getInstance()->getTextureCache()->addImage("images/Armas/trampilla_activa_izq.png");
	Arma* trampilla = Arma::create(f, 15, "trampilla", 5, 30, 5);
	armasTotales.push_back(trampilla);
	trampilla->SetRutaSonido(cocos2d::String::create("sounds/Trampilla.mp3"));

	Texture2D *e = Director::getInstance()->getTextureCache()->addImage("images/Armas/mina_no_activa.png");
	Arma* mina = Arma::create(e, 100, "mina", 4, 100, 1);
	armasTotales.push_back(mina);
	mina->SetRutaSonido(cocos2d::String::create("sounds/Mina.mp3"));

	

	for (int i = 0; i <armasTotales.size(); i++){
		armasTotales[i]->setPosition(-200, -200);
		armasTotales[i]->setVisible(false);
	}
}

void Global::creaObjetosEscenario()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	std::vector<std::string> macetas;

	ObjetoEscenario* ancla = ObjetoEscenario::create("images/ObjetosEscenario/ancla.png", 100, "ancla",2);
	ObjetosTotalesEscenarios.push_back(ancla);
	PosicionObjetos.push_back(std::make_pair(1700,650));
	ancla->SetRutaSonido(cocos2d::String::create("sounds/Ancla.mp3"));

	ObjetoEscenario* cactus = ObjetoEscenario::create("images/ObjetosEscenario/cactus.png", 40, "cactus", 2);
	ObjetosTotalesEscenarios.push_back(cactus);
	macetas.push_back("images/ObjetosEscenario/cactus.png");
	PosicionObjetos.push_back(std::make_pair(1600, 650));
	cactus->SetRutaSonido(cocos2d::String::create("sounds/Maceta.mp3"));

	ObjetoEscenario* flor = ObjetoEscenario::create("images/ObjetosEscenario/flor.png", 40, "flor", 2);
	ObjetosTotalesEscenarios.push_back(flor);
	macetas.push_back("images/ObjetosEscenario/flor.png");
	PosicionObjetos.push_back(std::make_pair(2000, 550));
	flor->SetRutaSonido(cocos2d::String::create("sounds/Maceta2.mp3"));

	ObjetoEscenario* planta = ObjetoEscenario::create("images/ObjetosEscenario/planta.png", 40, "planta", 2);
	ObjetosTotalesEscenarios.push_back(planta);
	macetas.push_back("images/ObjetosEscenario/planta.png");
	PosicionObjetos.push_back(std::make_pair(2500, 650));
	planta->SetRutaSonido(cocos2d::String::create("sounds/Maceta2.mp3"));


	/*for (int i = 4; i < 10; i++) {
		char* nombre = "Objeto Escenario numero: ";
		nombre += i;
		auto cadena = macetas[random(0, 2)];
		ObjetoEscenario* objetoaux = ObjetoEscenario::create(cadena, random(9,12), nombre,2);
		Vec2 punto = Vec2(((i*5 + 100)*visiblesize.width) / 10 - objetoaux->getContentSize().width, visiblesize.height / 2);
		objetoaux->setPosition(punto);
		objetoaux->setColor(Color3B(i * 25, i * 25, i * 25));
		ObjetosTotalesEscenarios.push_back(objetoaux);
	}*/
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

		auto objetodeturno = Global::getInstance()->ObjetosTotalesEscenarios[i];
		objetodeturno->setOpacity(255);
		objetodeturno->setVisible(true);
		objetodeturno->enableListener(true);
		/*Vec2 punto = Vec2(((i + 1) * 1024 * 1.5) / (u_objetos - i_objetos)
			+ 1024 
			- Global::getInstance()->ObjetosTotalesEscenarios[i]->getContentSize().width
			,Director::getInstance()->getVisibleSize().height -objetodeturno->getContentSize().height*1.5);*/

		Point p = Point(PosicionObjetos[i].first/1.0, PosicionObjetos[i].second/1.0);

		objetodeturno->setPosition(p);
		objetodeturno->setPhysicsBody(nullptr);
		float v;
		if (objetodeturno->isVisible()) {
			v = 1;
		}
		else v = 0;
		nivel->getChildByTag(102)->addChild(objetodeturno, 3);
	}
}

void Global::colocaFondo(std::vector<std::string> fondos) {

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create(fondos[0]);
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

	auto rectangulo2 = cocos2d::Sprite::create("images/Nivel/Arsenal.png");

	rectangulo2->setAnchorPoint(Point(1, 1));
	rectangulo2->setPosition(Point(visibleSize.width,visibleSize.height));
	rectangulo2->setVisible(true);
	layerObjects->addChild(rectangulo2, 8);
}

void Global::recolocaArmasNivel()
{
	for (int i = 0; i< ArmasNivel.size(); i++) {
		ArmasNivel[i]->setPositionX((i+1) * 470 / 5 + 470 +32);
	}
}

void Global::CreaFrases()
{
	//Katahi 0-6
	BateriaFrasesKatahi.push_back("Eeeh...yo no he pedido\nningun rescate.");
	BateriaFrasesKatahi.push_back("Sal de mi propiedad o \ntendre que matarte.");
	BateriaFrasesKatahi.push_back("Comprando en la tienda.");
	BateriaFrasesKatahi.push_back("No, bruto! Mejor me callo...");
	BateriaFrasesKatahi.push_back("*pensando* Deberia abrir mi\narsenal y...");
	BateriaFrasesKatahi.push_back("elegir las armas para\nponerlas en mi estanteria...");
	BateriaFrasesKatahi.push_back("...y cuando\nempiece a correr,\nponerlas en su camino.");

	//Katahi 7-9
	BateriaFrasesKatahi.push_back("Pero tu...\nno te enteras.");
	BateriaFrasesKatahi.push_back("Ojala pudiera \ntirarte este ancla\n a la cabeza.");
	BateriaFrasesKatahi.push_back("*Pensando*\n Esque como se ponga\n a correr le tiro\n hasta el piano.");

	//Katahi 10
	BateriaFrasesKatahi.push_back("Por favor...");
	//Katahi 11
	BateriaFrasesKatahi.push_back("Si,Si...mejor ya\n nos vemos en los bosques\n de Memsuficaland");

	//Zerrin 0-3
	BateriaFrasesZerrin.push_back("Princeza Katahi,\n he venio' al RESCATE.");
	BateriaFrasesZerrin.push_back("Como vaz a hacer ezo,\n si zoy tu principe?");
	BateriaFrasesZerrin.push_back("Pero... no puedez\n matarme con una tienda.");
	BateriaFrasesZerrin.push_back("Me la vaz a tirar encima?");
	//Zerrin 4
	BateriaFrasesZerrin.push_back("No ze preocupe\n princesa katahi,\n yo te salvare.");
	//Zerrin 5
	BateriaFrasesZerrin.push_back("Ze que zolo te haces\n la dura pa sedusirme!");
	//Zerrin 6-9
	BateriaFrasesZerrin.push_back("Nunca imagine yo\nque me fueses a querer tanto.");
	BateriaFrasesZerrin.push_back("Como para tener\n una cita fuera del castillo.");
	BateriaFrasesZerrin.push_back("Seguro...? no\nprefierez que vuelva");
	BateriaFrasesZerrin.push_back("A tu habitacion ?\nSe que te gusta jugar\n con las dagas");

}




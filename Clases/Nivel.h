#ifndef __NIVEL_SCENE_H__
#define __NIVEL_SCENE_H__
#include "cocos2d.h"
#include "Arma.h"




class Nivel : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	// es int temporalmente debe ser de 
	virtual bool init();
	//int ContadorArmas;



	cocos2d::Sprite* rectangulo;
	void preparaNivel(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	void displayArmasArsenal();
	void goToGameOver(Ref *pSender);
	void goToPause(Ref *pSender);
	void goToWinScene();
	void spawnNube(float dt);
	void mueveFondo(float v);
	void addContactListener();
	//void colocaObjetos(int i_objetos, int u_objetos);

	cocos2d::Rect getBackgroundSize();



	int getPosXFondo();
	int getBackgroundWidth();
	int vueltasArsenal;

	bool onContactBegin(cocos2d::PhysicsContact & contact);
	bool onContactPreSolve(cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve);

	cocos2d::EventListenerPhysicsContact * listenerColision;

	static Nivel* create(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	Nivel(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	~Nivel();
	cocos2d::PhysicsWorld *nivelPhysics;
	cocos2d::PhysicsWorld * getPhysicsWorld();
	cocos2d::Sprite* background;



private:
	static int tiempoDelNivel;
	static int puntosDelNivel;
	cocos2d::Menu* menuArsenal;
	

	//bool juegoEnCurso;

	void muestraUnoMas(Ref *pSender);
	void muestraUnoMenos(Ref *pSender,int i);
	void borraArsenal(int superiorinferior);
	void goToTienda(Ref *pSender);
	void goToVestuario(Ref *pSender);
	void abrirArsenal(Ref *pSender);
	void simulacion(Ref *pSender);

	void activaDesactivaBoton(cocos2d::MenuItemImage* boton, bool estado);

	void recorreArmas(int iterador, int posicion, int ancho, int alto, int iteraciones);
	void activaDesactivaArma(Arma* arma, bool estado);
	void quitaArmas();


	void colocaBotones();
	void colocaFondo(std::vector<std::string> fondos);
	void colocaZerrin();


	cocos2d::MenuItemImage* masBtn;
	cocos2d::MenuItemImage* menosBtn;
	cocos2d::MenuItemImage* tiendaBtn;
	cocos2d::MenuItemImage* pauseBtn;
	cocos2d::MenuItemImage* vestuarioBtn;
	cocos2d::MenuItemImage* arsenalBtn;
	cocos2d::MenuItemImage* simulacionBtn;

	cocos2d::Menu* menu1;
	cocos2d::Menu* menu2;



	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	cocos2d::Sprite* muralla;
	cocos2d::Sprite* nubes;
	

	
	void setPhysicsWorld(cocos2d::PhysicsWorld* world);


};

#endif  

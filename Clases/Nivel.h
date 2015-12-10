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


	int vueltasArsenal;
	cocos2d::Sprite* rectangulo;
	void preparaNivel(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	void displayArmasArsenal();
	void goToGameOver(Ref *pSender);
	void goToPause(Ref *pSender);
	void spawnNube(float dt);
	//void stopCamara();
	cocos2d::Rect getBackgroundSize();
	//void removeScheduler();

	void mueveFondo(int v);
	int getPosXFondo();
	int getBackgroundWidth();

	static Nivel* nivelActual;
	static Nivel* create(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	Nivel(std::vector<std::string> fondos, int i_objetos, int u_objetos);
	~Nivel();



	cocos2d::Sprite* background;


	// implement the "static create()" method manually
	//CREATE_FUNC(Nivel);

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
	//void displayArmasNivel();
	void activaDesactivaBoton(cocos2d::MenuItemImage* boton, bool estado);

	void recorreArmas(int iterador, int posicion, int ancho, int alto, int iteraciones);
	void activaDesactivaArma(Arma* arma, bool estado);
	void quitaArmas();

	void colocaObjetos(int i_objetos, int u_objetos);
	void colocaBotones();
	void colocaFondo(std::vector<std::string> fondos);

	/*void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);*/
	
	//void update(float dt);

	//std::list<cocos2d::Node *> Nubes;
	//virtual void update(float dt);

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
	
	cocos2d::PhysicsWorld *nivelPhysics;
	
	void setPhysicsWorld(cocos2d::PhysicsWorld* world);


};

#endif  

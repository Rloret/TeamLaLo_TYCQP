#ifndef __Tienda_SCENE_H__
#define __Tienda_SCENE_H__
#include "cocos2d.h"
#include "Arma.h"

#include <time.h>

class TiendaScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void createMenuCompra();
	void closeMenuCompra(Ref *pSender);
	void returnToScene(Ref *pSender);
	cocos2d::Sprite* rectangulo;


	clock_t* tiempoPasado;
	cocos2d::EventListenerTouchOneByOne* listenerTienda;
	// implement the "static create()" method manually
	CREATE_FUNC(TiendaScene);
private:

	void hacerCompra(Ref *pSender);
	void colocaArmasTotales();

	void activaDesactivaBotones(cocos2d::MenuItemImage* boton, bool estado);
	void preparaBotones();

	void addListener();
	void gestionaToque();

	void modificaTextoOro(cocos2d::Label * l);

	cocos2d::MenuItemImage* yesButton;
	cocos2d::MenuItemImage* cerrarMenuButton;
	cocos2d::Label* textoCompra;
	cocos2d::Menu* menuCompra;

	cocos2d::Label* dinero_oro_int;
	cocos2d::Label* dinero_mechones_int;

	//virtual void onEnterTransitionDidFinish();
};

#endif  

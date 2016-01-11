#ifndef __LevelsMenu_SCENE_H__
#define __LevelsMenu_SCENE_H__
#include "cocos2d.h"

class LevelsMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(LevelsMenuScene);

	void goToMenuStart(Ref *pSender);
	void goToNivel(Ref *pSender,int i);
	void addListener();
	void touchEvent(cocos2d::Touch * touch, cocos2d::Point _p);
	void ocultaNivelesVisibles(int mundoseleccionado);
	void activaBrightEffect();
	void borraElementoTemporal(Node* emisor,bool limpia);
	void añadeNivel(cocos2d::Scene* nivel,int inicioObjetos, int finObjetos);
	virtual void onEnterTransitionDidFinish();
	int mundoSeleccionado; //Será la posicion del sprite del nivel en el array
	// sirve para identificar el nivel
	cocos2d::EventListenerTouchOneByOne* listener;
	std::vector<cocos2d::Sprite*> imagenesMundos;
	//std::vector<cocos2d::Sprite*> matrizNivelesBtn;
	std::vector<cocos2d::Menu*> vectorNiveles;
	std::vector<std::string> fondosPasar;
	cocos2d::Sprite * brightEffect;
	cocos2d::Sprite * fadingEffect;
	std::vector<cocos2d::String*> bateriaDeFrases;
	cocos2d::MenuItemImage* nivelpulsado = nullptr;
	void muestraUnoMas(Ref *pSender);
	void muestraUnoMenos(Ref *pSender); //funciones para la seleccion del nivel con dos botones fleacha
	void muestraNivelesBtn();

private:
	int songLevelsMenuID;
};

#endif  

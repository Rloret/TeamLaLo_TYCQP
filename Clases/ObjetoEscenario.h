#ifndef __ObjetoEscenario_H__
#define __ObjetoEscenario_H__
#include "cocos2d.h"



class ObjetoEscenario : public cocos2d::Sprite
{
public:
	ObjetoEscenario(const std::string & fileName, int daño, std::string nombre,int tipo);
	~ObjetoEscenario();
	static ObjetoEscenario* create(const std::string &fileName, int daño, std::string nombre, int tipo);

	void AddListener();
	void TouchEvent(cocos2d::Touch* touch, cocos2d::Point _p);
	void assignBody();

	int getTipo();
	int getDaño();
	std::string getNombre();
	void accionColision(Node* objeto);
	void enableListener(bool estado);

	void PlayObjetoSound();
	void SetRutaSonido(cocos2d::String* c);
	cocos2d::String* GetRutaSonido();
	int SoundCaer;


private:
	int daño;
	int tipo;
	std::string nombre;
	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::String* rutaSonido;


};

#endif //ARMA


#ifndef __ObjetoEscenario_H__
#define __ObjetoEscenario_H__
#include "cocos2d.h"



class ObjetoEscenario : public cocos2d::Sprite
{
public:
	ObjetoEscenario(const std::string & fileName, int da�o, std::string nombre,int tipo);
	~ObjetoEscenario();
	static ObjetoEscenario* create(const std::string &fileName, int da�o, std::string nombre, int tipo);

	void AddListener();
	void TouchEvent(cocos2d::Touch* touch, cocos2d::Point _p);
	void assignBody();

	int getTipo();
	int getDa�o();
	std::string getNombre();
	void accionColision(Node* objeto);
	void enableListener(bool estado);


private:
	int da�o;
	int tipo;
	std::string nombre;
	cocos2d::EventListenerTouchOneByOne* listener;


};

#endif //ARMA


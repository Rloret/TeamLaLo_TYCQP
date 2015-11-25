#ifndef __ObjetoEscenario_H__
#define __ObjetoEscenario_H__
#include "cocos2d.h"



class ObjetoEscenario : public cocos2d::Sprite
{
public:
	ObjetoEscenario(const std::string & fileName, int daño, std::string nombre);
	~ObjetoEscenario();
	static ObjetoEscenario* create(const std::string &fileName, int daño, std::string nombre);

	//void initOptions();

	void AddListener();
	void TouchEvent(cocos2d::Touch* touch, cocos2d::Point _p);

private:
	int daño;
	std::string tipo;
	std::string nombre;

};

#endif //ARMA


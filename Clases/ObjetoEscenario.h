#ifndef __ObjetoEscenario_H__
#define __ObjetoEscenario_H__
#include "cocos2d.h"



class ObjetoEscenario : public cocos2d::Sprite
{
public:
	ObjetoEscenario(const std::string & fileName, int daño, std::string nombre,int tipo);
	~ObjetoEscenario();
	static ObjetoEscenario* create(const std::string &fileName, int daño, std::string nombre, int tipo);

	//void initOptions();
	bool soyObjeto();

	void AddListener();
	void TouchEvent(cocos2d::Touch* touch, cocos2d::Point _p);
	void assignBody();

	int getTipo();
	int getDaño();

private:
	int daño;
	int tipo;
	std::string nombre;


};

#endif //ARMA


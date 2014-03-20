#ifndef _MAIN_GAME_H

#define _MAIN_GAME_H

#include "cocos2d.h"
USING_NS_CC;

class MainGame : public Layer{
public:
	MainGame();
	virtual ~MainGame();

	CREATE_FUNC(MainGame);

	static Scene* createScene();

	virtual bool init();

	void loadTowerPositions();

private:
	Vector<Ref*>  _towers;
};

#endif
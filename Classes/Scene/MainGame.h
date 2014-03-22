#ifndef _MAIN_GAME_H

#define _MAIN_GAME_H

#include "cocos2d.h"
USING_NS_CC;

#include "../Enemy/Enemy.h"



class Tower;

class MainGame : public Layer{
public:
	MainGame();
	virtual ~MainGame();

	CREATE_FUNC(MainGame);

	static Scene* createScene();

	virtual bool init();

	void loadTowerPositions();
	bool loadWave();

	virtual void onEnter() override;
	virtual void onExit() override;

	bool canBuyTower();

	void addWayPoint();

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;

	bool circle(Point circlePointOne, float radiusOne, Point circlePointTwo, float radiusTwo);

	void ccFillPoly(Point poli, int points, bool closePolygon);
	
	void enemyGotKilled();
	void getHpDamage();

	void doGameOver();

	void awardGold(int gold);

	CC_SYNTHESIZE(unsigned int, _wave, Wave);

	Vector<Ref*>& getWayPoints(){ return _wayPoints; }
	Vector<Enemy*>& getEnemies(){ return _vectEnemies; }

private:
	Vector<Ref*>  _towers;
	Vector<Ref*> _towerBases;
	Vector<Ref*> _wayPoints;
	Vector<Enemy*> _vectEnemies;
	LabelBMFont* ui_wave_lbl;

	int _nPlayerHp;
	LabelBMFont *ui_hp_lbl = nullptr;
	bool _bIsGameEnded = false;

	int _nPlayerGold = 1000;
	LabelBMFont* ui_gold_lbl;

	const int KTOWER_COST = 220;
};

#endif
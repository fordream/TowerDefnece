#ifndef _CREEP_H

#define _CREEP_H

#include "cocos2d.h"
USING_NS_CC;

class WayPoint;

class Creep : public Sprite
{
public:
	Creep();
	virtual ~Creep();

	CC_SYNTHESIZE(int, _curHp, CurHp);
	CC_SYNTHESIZE(int, _moveDuration, MoveDuration);
	CC_SYNTHESIZE(int, _curWayPoint, CurWayPoint);

	Creep* initWithCreap(Creep*);
	WayPoint* getNextWayPoint();
};

class FastRedCreep : public Creep
{
};

class StrongGreenCreep : public Creep
{

};
#endif
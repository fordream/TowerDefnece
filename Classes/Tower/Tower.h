#ifndef _TOWER_H

#define _TOWER_H

#include "cocos2d.h"
USING_NS_CC;

class Tower : public Node{
public:
	Tower();
	virtual ~Tower();

	CC_SYNTHESIZE(int, _attackRange, AttackRange);
	CC_SYNTHESIZE(int, _damage, Damage);
	CC_SYNTHESIZE(float, _fireRate, FireRate);

	CC_SYNTHESIZE(Layer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE(CCSprite*, m_ptrSprite, Sprite);
};
#endif
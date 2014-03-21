#ifndef _ENEMY_H

#define _ENEMY_H

#include "cocos2d.h"
USING_NS_CC;

class WayPoint;

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_ORIGIN 10

class Enemy : public Node{
public:
	Enemy();
	virtual ~Enemy();

	static Enemy* create(Layer* gameLayer);

	CC_SYNTHESIZE(Layer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE(int, _maxHp, MaxHp);
	CC_SYNTHESIZE(int, _currentHp, CurrentHp);
	CC_SYNTHESIZE(float, _walkingspeed, WalkingSpeed);
	CC_SYNTHESIZE(WayPoint*, _destinationWayPoint, DestinationWayPoint);
	CC_SYNTHESIZE(bool, _active, Active);
	CC_SYNTHESIZE(Sprite*, _ptrSprite, Sprite);
	CC_SYNTHESIZE(Point, _spritePosition, SpritePosition);

	virtual void update(float dt) override;

	void doActive(float dt);
	void getRemoved();

	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated) override;


private:
	bool initwithGame(Layer* gameLayer);
};
#endif
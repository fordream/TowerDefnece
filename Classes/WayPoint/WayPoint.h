#ifndef _WAY_POINT_H

#define _WAY_POINT_H

#include "cocos2d.h"
USING_NS_CC;

class WayPoint : public Node{
public:
	WayPoint();
	virtual ~WayPoint();

	CREATE_FUNC(WayPoint);

	static WayPoint* create(Layer* gameLayer, Point location);


	CC_SYNTHESIZE(WayPoint*, _nextWayPoint, NextWayPoint);
	CC_SYNTHESIZE(Layer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE(Point, _wayPosition, WayPosition);

	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated) override;


private:
	bool initwithTheGame(Layer* gameLayer, Point location);
};
#endif
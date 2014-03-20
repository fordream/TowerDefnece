#ifndef _WAY_POINT_H

#define _WAY_POINT_H

#include "cocos2d.h"
USING_NS_CC;

class WayPoint : public Node{
public:
	WayPoint();
	virtual ~WayPoint();

	CREATE_FUNC(WayPoint);

	virtual bool init();
};
#endif
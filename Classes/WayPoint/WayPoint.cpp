#include "WayPoint.h"
WayPoint::WayPoint()
{

}

WayPoint::~WayPoint()
{

}

bool WayPoint::init()
{
	if (!Node::init())
		return false;

	return true;
}


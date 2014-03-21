#include "WayPoint.h"
WayPoint::WayPoint()
{
	_nextWayPoint = nullptr;
}

WayPoint::~WayPoint()
{

}

WayPoint* WayPoint::create(Layer* gameLayer, Point location)
{
	WayPoint* pRet = new WayPoint();
	if (pRet&&pRet->initwithTheGame(gameLayer, location))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool WayPoint::initwithTheGame(Layer* gameLayer, Point location)
{
	if (!Node::init())
	{
		return false;
	}

	_gameLayer = gameLayer;
	this->setPosition(Point::ZERO);
	_wayPosition = location;
	_gameLayer->addChild(this);

	return true;
}

void WayPoint::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	ccDrawColor4B(0, 255, 2, 255);
	ccDrawCircle(_wayPosition, 6, 360, 30, true);
	ccDrawCircle(_wayPosition, 2, 360, 30, false);

	if (_nextWayPoint)
		ccDrawLine(_wayPosition, _nextWayPoint->getWayPosition());
}




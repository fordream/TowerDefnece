#include "Tower.h"
Tower::Tower()
{

}

Tower::~Tower()
{

}


Tower* Tower::create(Layer* gameLayer, Point location)
{
	Tower* pRet = new Tower();
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


bool Tower::nodewithTheGame(Layer* ptrGame, Point location)
{
	return initwithTheGame(ptrGame, location);
}

bool Tower::initwithTheGame(Layer* ptrGame, Point location)
{
	if (Node::init())
	{
		_gameLayer = ptrGame;
		_attackRange = 70;
		_damage = 10;
		_fireRate = 1;

		m_ptrSprite = Sprite::create("images/tower.png");
		m_ptrSprite->setPosition(location);
		this->addChild(m_ptrSprite);
		_gameLayer->addChild(this);
		scheduleUpdate();
		return true;
	}
	return false;
}

void Tower::update(float dt)
{

}

void Tower::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	ccDrawColor4B(255, 255, 255, 255);
	ccDrawCircle(m_ptrSprite->getPosition(), _attackRange, 360, 30, false);
}


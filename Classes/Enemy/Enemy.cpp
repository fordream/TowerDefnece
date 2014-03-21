#include "Enemy.h"
#include "../Scene/MainGame.h"
#include "../WayPoint/WayPoint.h"
Enemy::Enemy()
{
	_active = false;
}

Enemy::~Enemy()
{

}

Enemy* Enemy::create(Layer* gameLayer)
{
	Enemy* pRet = new Enemy();
	if (pRet&&pRet->initwithGame(gameLayer))
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

bool Enemy::initwithGame(Layer* gameLayer)
{
	if (!Node::init())
		return false;

	_gameLayer = gameLayer;
	_maxHp = 40;
	_currentHp = _maxHp;
	_walkingspeed = 3.0f;

	_ptrSprite = Sprite::create("images/enemy.png");
	this->addChild(_ptrSprite);

	
	MainGame* layer = static_cast<MainGame*>(_gameLayer);
	unsigned int count = layer->getWayPoints().size();
	WayPoint* wayPoint = static_cast<WayPoint*>(layer->getWayPoints().at(count - 1));
	_destinationWayPoint = wayPoint->getNextWayPoint();
	_spritePosition = wayPoint->getWayPosition();
	_ptrSprite->setPosition(_spritePosition);

	_gameLayer->addChild(this);

	scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	Node::update(dt);

	if (!_active)
		return;

	MainGame* layer = static_cast<MainGame*>(_gameLayer);

	if (layer->circle(_spritePosition, 1.0f, _destinationWayPoint->getWayPosition(), 1.0f))
	{
		if (_destinationWayPoint->getNextWayPoint())
		{
			_destinationWayPoint = _destinationWayPoint->getNextWayPoint();
		}
		else
		{
			layer->getHpDamage();
			getRemoved();
			return;
		}
	}

	Point targetPoint = _destinationWayPoint->getWayPosition();
	float movementSpeed = _walkingspeed;

	
	Point normalized = ccpNormalize(Point(targetPoint.x - _spritePosition.x, targetPoint.y - _spritePosition.y));
	_ptrSprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)));

	_spritePosition = Point(_spritePosition.x+normalized.x*movementSpeed,
		_spritePosition.y+normalized.y*movementSpeed);

	_ptrSprite->setPosition(_spritePosition);

	
}

void Enemy::doActive(float dt)
{
	_active = true;
}

void Enemy::getRemoved()
{
	this->removeFromParentAndCleanup(true);

	MainGame* layer = static_cast<MainGame*>(_gameLayer);
	layer->getEnemies().eraseObject(this, true);
	unsigned int rcount = this->getReferenceCount();
	unsigned int count = layer->getEnemies().size();
	layer->enemyGotKilled();
}

void Enemy::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{

	Point myPosition = _spritePosition;
	ccDrawSolidRect(ccp(myPosition.x + HEALTH_BAR_ORIGIN,
		myPosition.y + 16),
		ccp(myPosition.x + HEALTH_BAR_ORIGIN + HEALTH_BAR_WIDTH,
		myPosition.y + 14),
		ccc4f(1.0, 0, 0, 1.0));

	ccDrawSolidRect(ccp(myPosition.x + HEALTH_BAR_ORIGIN,
		myPosition.y + 16),
		ccp(myPosition.x + HEALTH_BAR_ORIGIN + (float)(_currentHp * HEALTH_BAR_WIDTH) / _maxHp,
		myPosition.y + 14),
		ccc4f(0, 1.0, 0, 1.0));
}


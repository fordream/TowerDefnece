#include "Tower.h"
#include "../Enemy/Enemy.h"
#include "../Scene/MainGame.h"
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
		_attackRange = 100;
		_damage = 10;
		_fireRate = 0.1f;

		m_ptrSprite = Sprite::create("images/tower.png");
		_spritePosition = location;
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
	MainGame* gameLayer = static_cast<MainGame*>(_gameLayer);
	if (_chosenEnemy)
	{
		Point normalized = Point(_chosenEnemy->getSpritePosition().x - _spritePosition.x,
			_chosenEnemy->getSpritePosition().y - _spritePosition.y);
		normalized.normalize();

		m_ptrSprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)) + 90);

		
		if (!gameLayer->circle(m_ptrSprite->getPosition(), _attackRange, _chosenEnemy->getSprite()->getPosition(), 1))
		{
			lostSightOfEnemy();
		}
	}
	else
	{
		for (auto enemy : gameLayer->getEnemies())
		{
			if (gameLayer->circle(m_ptrSprite->getPosition(), _attackRange, enemy->getSprite()->getPosition(), 1))
			{
				chosenEnemyForAttack(enemy);
				break;
			}
		}
	}
}

void Tower::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	ccDrawColor4B(255, 255, 255, 255);
	ccDrawCircle(m_ptrSprite->getPosition(), _attackRange, 360, 30, false);
}

void Tower::attackEnemy()
{
	schedule(schedule_selector(Tower::shootWeapon), _fireRate);
}



void Tower::shootWeapon(float dt)
{
	auto bullet = Sprite::create("images/bullet.png");
	addChild(bullet);
	bullet->setPosition(_spritePosition);

	auto moveTo = MoveTo::create(0.1f, _chosenEnemy->getSpritePosition());
	auto sequence = Sequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(Tower::damageEnemy, this)),
		CallFuncN::create(CC_CALLBACK_0(Tower::removeBullet, this, bullet)), NULL);
	bullet->runAction(sequence);

}

void Tower::chosenEnemyForAttack(Enemy* enemy)
{
	_chosenEnemy = nullptr;
	_chosenEnemy = enemy;
	attackEnemy();
	enemy->getAttacked(this);
}

void Tower::damageEnemy()
{
	if (_chosenEnemy)
		_chosenEnemy->getDamaged(_damage);
}

void Tower::targetKilled()
{
	if (_chosenEnemy)
		_chosenEnemy = nullptr;

	this->unschedule(schedule_selector(Tower::shootWeapon));
}

void Tower::lostSightOfEnemy()
{
	if (_chosenEnemy)
		_chosenEnemy->getLostSight(this);

	if (_chosenEnemy)
		_chosenEnemy = nullptr;

	this->unschedule(schedule_selector(Tower::shootWeapon));
}

void Tower::removeBullet(Node* object)
{
	object->removeFromParentAndCleanup(true);
}





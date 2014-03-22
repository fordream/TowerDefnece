#ifndef _TOWER_H

#define _TOWER_H

#include "cocos2d.h"
USING_NS_CC;

class Enemy;

class Tower : public cocos2d::Node{
public:
	Tower();
	virtual ~Tower();

	static Tower* create(Layer* gameLayer, Point location);

	CC_SYNTHESIZE(int, _attackRange, AttackRange);
	CC_SYNTHESIZE(int, _damage, Damage);
	CC_SYNTHESIZE(float, _fireRate, FireRate);

	CC_SYNTHESIZE(Layer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE(Sprite*, m_ptrSprite, Sprite);
	CC_SYNTHESIZE(Point, _spritePosition, SpritePosition);

	bool nodewithTheGame(Layer* ptrGame, Point location);

	virtual void update(float dt) override;

	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated) override;
	
	void targetKilled();
	
	void attackEnemy();
	void shootWeapon(float dt);

	void chosenEnemyForAttack(Enemy* enemy);
	void damageEnemy();
	void lostSightOfEnemy();

	void removeBullet(Node* object);

private:
	 bool initwithTheGame(Layer* ptrGame, Point location);
	 bool _bIsAttck;
	 Enemy* _chosenEnemy = nullptr;

};
#endif
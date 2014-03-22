#include "MainGame.h"
#include "../Tower/Tower.h"
#include "../WayPoint/WayPoint.h"
#include <string>
MainGame::MainGame()
{
	_wave = 0;
}

MainGame::~MainGame()
{

}

Scene* MainGame::createScene()
{
	MainGame* pRet = MainGame::create();
	Scene* ptrScene = Scene::create();
	ptrScene->addChild(pRet);
	return ptrScene;
}

bool MainGame::init()
{
	if (!Layer::init())
		return false;

	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(960.0f, 640.0f, ResolutionPolicy::NO_BORDER);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("images/bg-hd.png");
	bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(bg, -10000);

	addWayPoint();

	loadTowerPositions();
	



	ui_wave_lbl = LabelBMFont::create();
	String* str = String::createWithFormat("Wave: %d", _wave);
	ui_wave_lbl->setString(str->getCString());
	ui_wave_lbl->setFntFile("images/font_red_14.fnt");

	this->addChild(ui_wave_lbl);
	ui_wave_lbl->setPosition(Point(400, visibleSize.height - 12));
	ui_wave_lbl->setAnchorPoint(Point(0.0f, 0.5f));

	loadWave();

	_nPlayerHp = 5;

	ui_hp_lbl = LabelBMFont::create();
	String* str1 = String::createWithFormat("Hp: %d", _nPlayerHp);
	ui_hp_lbl->setString(str1->getCString());
	ui_hp_lbl->setFntFile("images/font_red_14.fnt");
	this->addChild(ui_hp_lbl);
	ui_hp_lbl->setPosition(Point(70, visibleSize.height - 12));

	ui_gold_lbl = LabelBMFont::create();
	String* str2 = String::createWithFormat("Gold: %d", _nPlayerHp);
	ui_gold_lbl->setString(str1->getCString());
	ui_gold_lbl->setFntFile("images/font_red_14.fnt");
	this->addChild(ui_gold_lbl);
	ui_gold_lbl->setPosition(Point(135, visibleSize.height - 12));

	return true;
}

void MainGame::loadTowerPositions()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("images/TowersPosition.plist");
	ValueVector positionVector = FileUtils::getInstance()->getValueVectorFromFile(path);

	for (auto &e : positionVector)
	{
		auto txt_map = e.asValueMap();
		int x = txt_map.at("x").asInt();
		int y = txt_map.at("y").asInt();

		log("(%d, %d)", x, y);

		auto sprite = Sprite::create("images/open_spot.png");
		sprite->setPosition(Point(x * 2, y * 2));
		this->addChild(sprite);

		_towerBases.pushBack(sprite);
	}
}

void MainGame::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (Touch* touch : touches)
	{
		if (!touch)
			return;

		for (Ref* tb : _towerBases)
		{
			Sprite* sprite = static_cast<Sprite*>(tb);
			Rect rect = sprite->boundingBox();
			if (rect.containsPoint(touch->getLocation()))
			{
				if (canBuyTower())
				{
					if (!sprite->getUserData())
					{
						Tower* tower = Tower::create(this, sprite->getPosition());
						sprite->setUserData(tower);
						_nPlayerGold -= KTOWER_COST;
						String* str = String::createWithFormat("Gold: %d", _nPlayerGold);
						ui_gold_lbl->setString(str->getCString());
					}

				}
			}
		}
	}
}

void MainGame::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MainGame::onTouchesBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainGame::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	Layer::onExit();
}

bool MainGame::canBuyTower()
{
	if (_nPlayerGold - KTOWER_COST >= 0)
	{
		return true;
	}
	return false;
}

void MainGame::addWayPoint()
{
	WayPoint* waypoint1 = WayPoint::create(this, Point(420 * 2, 35 * 2));
	_wayPoints.pushBack(waypoint1);

	WayPoint* waypoint2 = WayPoint::create(this, Point(35 * 2, 35 * 2));
	_wayPoints.pushBack(waypoint2);
	waypoint2->setNextWayPoint(waypoint1);

	WayPoint* waypoint3 = WayPoint::create(this, Point(35 * 2, 130 * 2));
	_wayPoints.pushBack(waypoint3);
	waypoint3->setNextWayPoint(waypoint2);

	WayPoint* waypoint4 = WayPoint::create(this, Point(455 * 2, 130 * 2));
	_wayPoints.pushBack(waypoint4);
	waypoint4->setNextWayPoint(waypoint3);

	WayPoint* waypoint5 = WayPoint::create(this, Point(455 * 2, 220 * 2));
	_wayPoints.pushBack(waypoint5);
	waypoint5->setNextWayPoint(waypoint4);

	WayPoint* waypoint6 = WayPoint::create(this, Point(10 * 2, 220 * 2));
	_wayPoints.pushBack(waypoint6);
	waypoint6->setNextWayPoint(waypoint5);
}

bool MainGame::circle(Point circlePointOne, float radiusOne, Point circlePointTwo, float radiusTwo)
{
	float xdif = circlePointOne.x - circlePointTwo.x;
	float ydif = circlePointOne.y - circlePointTwo.y;

	float distance = sqrt(xdif*xdif + ydif* ydif);

	if (distance <= radiusOne + radiusTwo)
		return true;

	return false;
}

void MainGame::ccFillPoly(Point poli, int points, bool closePolygon)
{

}

void MainGame::enemyGotKilled()
{
	if (_vectEnemies.size() <= 0)
	{
		if (!loadWave())
		{
			Director::getInstance()->replaceScene(MainGame::createScene());
		}
	}
}

void MainGame::getHpDamage()
{
	--_nPlayerHp;
	String* str = String::createWithFormat("Hp: %d", _nPlayerHp);
	ui_hp_lbl->setString(str->getCString());
	if (_nPlayerHp <= 0)
	{
		doGameOver();
	}
};

bool MainGame::loadWave()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("images/Waves.plist");
	ValueVector vector = FileUtils::getInstance()->getValueVectorFromFile(path);

	if (_wave >= vector.size())
		return false;

	ValueVector vecotrSecond = vector[_wave].asValueVector();

	for (auto e1 : vecotrSecond)
	{
		auto txt_map = e1.asValueMap();
		std::string data = txt_map.at("data").asString();
		float spwan = txt_map.at("spawnTime").asFloat();
		log("(data=>%s, spwantime=>%f", data.c_str(), spwan);

		Enemy* enemy = Enemy::create(this);
		_vectEnemies.pushBack(enemy);
		enemy->schedule(schedule_selector(Enemy::doActive), spwan);
	}

	++_wave;
	ui_wave_lbl->setString(String::createWithFormat("Wave %d", _wave)->getCString());
	return true;
}

void MainGame::doGameOver()
{
	if (!_bIsGameEnded)
	{
		_bIsGameEnded = true;
		Director::getInstance()->replaceScene(MainGame::createScene());
	}
}

void MainGame::awardGold(int gold)
{
	_nPlayerGold += gold;
	String* str = String::createWithFormat("Gold: %d", _nPlayerGold);
	ui_gold_lbl->setString(str->getCString());
}


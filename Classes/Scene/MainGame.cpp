#include "MainGame.h"
#include <string>
MainGame::MainGame()
{

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

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("images/bg-hd.png");
	bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	loadTowerPositions();

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
		sprite->setPosition(Point(x*2, y*2));
		this->addChild(sprite);
	}
}


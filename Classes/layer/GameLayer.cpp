#include "GameLayer.h"
#include "utils/Constant.h"

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();
	initUI();

	return true;
}

void GameLayer::initData()
{

}

void GameLayer::initUI()
{
	auto bg_sp = Sprite::create("zhuomian.png");
	addChild(bg_sp);

	if (bg_sp)
	{
		float w = bg_sp->getContentSize().width;
		float h = bg_sp->getContentSize().height;

		bg_sp->setScale(VISIBLESIZE.width / w, VISIBLESIZE.height / h);

		bg_sp->setPosition(VISIBLESIZE / 2);
	}
}
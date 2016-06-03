#include "GUILayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"

GUILayer::GUILayer()
{

}

GUILayer::~GUILayer()
{

}

bool GUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();
	initUI();

	return true;
}

void GUILayer::initData()
{

}

void GUILayer::initUI()
{
	//头像
	auto icon_left = Sprite::create("icon_girl_1.png");

	auto width = icon_left->getContentSize().width / 2 + 10;

	if (icon_left)
	{
		addChild(icon_left);
		icon_left->setPosition(CommonFunction::getVisibleAchor(0, 1, this, Vec2(width, -width)));
	}

	auto icon_leftDown = Sprite::create("icon_girl_2.png");
	if (icon_leftDown)
	{
		addChild(icon_leftDown);
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0, this, Vec2(width, width)));
	}

	auto icon_right = Sprite::create("icon_boy_1.png");
	if (icon_right)
	{
		addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(1, 1, this, Vec2(-width, -width)));
	}
	
}
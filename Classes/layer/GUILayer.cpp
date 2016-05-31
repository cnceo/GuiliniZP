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
	//边框
	auto bg_sp_left = Sprite::create("renwu_1.png");
	addChild(bg_sp_left);
	if (bg_sp_left)
	{
		bg_sp_left->setPosition(CommonFunction::getVisibleAchor(0, 1, this, Vec2(bg_sp_left->getContentSize().width / 2+20 , -bg_sp_left->getContentSize().height / 2 -20)));
	}

	auto bg_sp_leftDown = Sprite::create("renwu_1.png");
	addChild(bg_sp_leftDown);
	if (bg_sp_leftDown)
	{
		bg_sp_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0, this, Vec2(bg_sp_leftDown->getContentSize().width / 2+ 20, bg_sp_leftDown->getContentSize().height / 2+ 20)));

	}

	auto bg_sp_right = Sprite::create("renwu_2.png");
	addChild(bg_sp_right);
	if (bg_sp_right)
	{
		bg_sp_right->setPosition(CommonFunction::getVisibleAchor(1, 1, this, Vec2(-bg_sp_right->getContentSize().width / 2-20, -bg_sp_right->getContentSize().height / 2 -20)));

	}
	//头像
	auto icon_left = Sprite::create("icon_girl_1.png");
	if (bg_sp_left && icon_left)
	{
		bg_sp_left->addChild(icon_left);
		icon_left->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, bg_sp_left, Vec2(-58, 0)));
	}

	auto icon_leftDown = Sprite::create("icon_girl_2.png");
	if (bg_sp_leftDown && icon_leftDown)
	{
		bg_sp_leftDown->addChild(icon_leftDown);
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, bg_sp_leftDown, Vec2(-58, 0)));
	}

	auto icon_right = Sprite::create("icon_boy_1.png");
	if (bg_sp_right && icon_right)
	{
		bg_sp_right->addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, bg_sp_right, Vec2(58, 0)));
	}
	
}
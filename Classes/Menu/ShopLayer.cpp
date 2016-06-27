#include "ShopLayer.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"

ShopLayer::ShopLayer()
{

}

ShopLayer::~ShopLayer()
{

}

bool ShopLayer::init()
{
	if (!Pop::init()) return false;
		
	initUI();
	return true;
}

void ShopLayer::initUI()
{
	auto bg_sp = Sprite::create("menu/shop_bg.png");
	if (bg_sp)
	{
		bg_sp->setTag(99);
		m_popNode->addChild(bg_sp);
	}

	auto bag_sp = Sprite::create("menu/shop.png");
	if (bag_sp && bg_sp)
	{
		bg_sp->addChild(bag_sp);
		bag_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, bg_sp, Vec2(0, -bag_sp->getContentSize().height)));
	}
	/*
	auto good_sp_1 = Sprite::create("menu/eyeGlass.png");
	auto good_sp_2 = Sprite::create("menu/eyeGlass.png");
	auto good_sp_3 = Sprite::create("menu/eyeGlass.png");
	if (good_sp_1 && good_sp_2 && good_sp_3 && bg_sp)
	{
		bg_sp->addChild(good_sp_1);
		good_sp_1->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, bg_sp, Vec2(0, 0)));

		good_sp_1->addChild(good_sp_2);
		good_sp_2->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, good_sp_1, Vec2(good_sp_2->getContentSize().width + 20, 0)));

		good_sp_1->addChild(good_sp_3);
		good_sp_3->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, good_sp_1, Vec2(-good_sp_2->getContentSize().width - 20, 0)));
	}*/

	auto close_btn = ui::Button::create("backBtn.png");
	if (close_btn && bg_sp)
	{
		bg_sp->addChild(close_btn);
		close_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::RightTop, bg_sp, Vec2(-close_btn->getContentSize().width,-close_btn->getContentSize().height / 2 - 10)));
		close_btn->addClickEventListener([this](Ref*){
			close();
		});
	}
}
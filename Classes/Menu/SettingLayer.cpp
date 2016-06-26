#include "SettingLayer.h"
#include "utils/CommonFunction.h"

SettingLayer::SettingLayer()
{

}

SettingLayer::~SettingLayer()
{

}

bool SettingLayer::init()
{
	if (!Pop::init()) return false;
		
	initUI();
	return true;
}

void SettingLayer::initUI()
{
	auto bg_sp = Sprite::create("menu/menu_bg.png");
	if (bg_sp)
	{
		bg_sp->setTag(99);
		m_popNode->addChild(bg_sp);
	}

	auto bag_sp = Sprite::create("menu/setting.png");
	if (bag_sp && bg_sp)
	{
		bg_sp->addChild(bag_sp);
		bag_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, bg_sp, Vec2(0, -bag_sp->getContentSize().height)));
	}

	auto close_btn = ui::Button::create("backBtn.png");
	if (close_btn && bg_sp)
	{
		bg_sp->addChild(close_btn);
		close_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::RightTop, bg_sp, Vec2(-close_btn->getContentSize().width, -close_btn->getContentSize().height / 2 - 10)));
		close_btn->addClickEventListener([this](Ref*){
			close();
		});
	}

	auto yinLiang_sp = Sprite::create("menu/btn_yinlinag.png");
	auto yinxiao_sp = Sprite::create("menu/btn_yinxiao.png");
	auto yinyue_sp = Sprite::create("menu/btn_music.png");
	auto tiaozi_sp = Sprite::create("menu/tiaozi.png");

	auto switch1_sp = Sprite::create("menu/switch.png");
	auto switch2_sp = Sprite::create("menu/switch.png");

	if (yinLiang_sp && yinxiao_sp && yinyue_sp && switch1_sp && switch2_sp && bg_sp && tiaozi_sp)
	{
		bg_sp->addChild(yinLiang_sp);
		bg_sp->addChild(yinxiao_sp);
		bg_sp->addChild(yinyue_sp);
		bg_sp->addChild(switch1_sp);
		bg_sp->addChild(switch2_sp);
		bg_sp->addChild(tiaozi_sp);
		tiaozi_sp->setScale(0.5f);

		yinLiang_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp,Vec2(170,80)));
		tiaozi_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp, Vec2(370, 80)));

		yinxiao_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp, Vec2(120, -60)));
		switch1_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp, Vec2(250, -60)));

		yinyue_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp, Vec2(470, -60)));
		switch2_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_sp, Vec2(600, -60)));
	}

}
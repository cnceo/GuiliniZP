#include "MissionLayer.h"
#include "utils/CommonFunction.h"

MissionLayer::MissionLayer()
{

}

MissionLayer::~MissionLayer()
{

}

bool MissionLayer::init()
{
	if (!Pop::init()) return false;
		
	initUI();
	return true;
}

void MissionLayer::initUI()
{
	auto bg_sp = Sprite::create("menu/menu_bg.png");
	if (bg_sp)
	{
		bg_sp->setTag(99);
		m_popNode->addChild(bg_sp);
	}

	auto bag_sp = Sprite::create("menu/mission.png");
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
}
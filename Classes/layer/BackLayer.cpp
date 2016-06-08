#include "BackLayer.h"
#include "ui/UIButton.h"
#include "utils/CommonFunction.h"
#include "WelcomeScene.h"

BackLayer::BackLayer()
{

}

BackLayer::~BackLayer()
{

}

bool BackLayer::init()
{
	if (!Pop::init())
	{
		return false;
	}

	initData();
	initUI();
	return true;
}


void BackLayer::initData()
{

}

void BackLayer::initUI()
{
	auto start_btn = ui::Button::create("back.png");
	if (start_btn)
	{
		m_popNode->addChild(start_btn);
		//start_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
		start_btn->addClickEventListener([=](Ref*){
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, WelcomeScene::createScene()));
	});
	}
}
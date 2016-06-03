#include "WelcomeScene.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"
#include "GameScene.h"

using namespace ui;

WelcomeScene::WelcomeScene()
{

}

WelcomeScene::~WelcomeScene()
{

}

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initUI();
	return true;
}

void WelcomeScene::initUI()
{
	auto start_btn = Button::create("menu_start.png");
	addChild(start_btn);
	if (!start_btn)return;
	start_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,Vec2(0,0)));
	start_btn->addClickEventListener([=](Ref*){
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::createScene()));
	});
}
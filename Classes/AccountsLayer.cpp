
#include "AccountsLayer.h"
#include "ui/UIButton.h"
#include <iostream>
#include "utils/CommonFunction.h"
#include "layer/GameScene.h"
#include "layer/WelcomeScene.h"
#include "utils/GetLayer.h"
#include "utils/Constant.h"

using namespace std;
using namespace ui;

#define WIN_DATA Win::getInstance()

AccountsLayer::AccountsLayer()
{

}

AccountsLayer::~AccountsLayer()
{
	
}

Scene* AccountsLayer::createScene()
{
	auto s = Scene::create();
	auto l = AccountsLayer::create();
	s->addChild(l);
	return s;
}

void AccountsLayer::onEnter()
{
	Layer::onEnter();
	// 屏蔽触摸
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [](Touch *, Event *){return true; };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void AccountsLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
		{
			if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
			{
				//close();
			}
		}
	}
}

bool AccountsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addUI();
	return true;
}

void AccountsLayer::addUI()
{
	auto bg_sp = Sprite::create("zm_bg.png");
	if (bg_sp)
	{
		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,Vec2::ZERO));
	}

	auto layercolor = LayerColor::create(Color4B(0, 0, 0, 150));
	addChild(layercolor);

	auto gray_sp = Sprite::create("account/ima_gray_1.png");
	if (gray_sp)
	{
		addChild(gray_sp);
		gray_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
	}
	//返回
	auto backBtn = Button::create("account/btn_back.png");
	if (backBtn)
	{
		addChild(backBtn);
		backBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::quiteCallback, this));
		float _width = backBtn->getContentSize().width / 2 + 15;
		float _heignt = backBtn->getContentSize().height / 2 + 15 ;

		backBtn->setPosition(CommonFunction::getVisibleAchor(1, 1, Vec2(-_width, -_heignt)));
	}
	//重新开始
	auto restartBtn = Button::create("account/btn_again.png");
	if (restartBtn)
	{
		restartBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::restartCallback, this));
		auto _he = restartBtn->getContentSize().height / 2 +15;
		restartBtn->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, Vec2(0, _he)));
		addChild(restartBtn);
	}

	//结算
	auto jiesuan_sp = Sprite::create("account/zi_jiesuan.png");
	if (jiesuan_sp)
	{
		addChild(jiesuan_sp);
		jiesuan_sp->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(jiesuan_sp->getContentSize().width /2, -85)));

	}
	//底牌
	auto dipai_sp = Sprite::create("account/zi_dipai.png");	
	if (dipai_sp)
	{
		addChild(dipai_sp);
		dipai_sp->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(300, -100)));
	}

	//头像
	auto icon_left = Sprite::create("icon_image/icon_girl_1.png");
	auto width = icon_left->getContentSize().width / 2 + 10;

	if (icon_left)
	{
		gray_sp->addChild(icon_left);
		icon_left->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, gray_sp ,Vec2(width, -width)));
	}

	auto icon_leftDown = Sprite::create("icon_image/icon_girl_2.png");
	if (icon_leftDown)
	{
		gray_sp->addChild(icon_leftDown);
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0,gray_sp,Vec2(width+ 80, width+50)));
	}

	auto icon_right = Sprite::create("icon_image/icon_boy_1.png");
	if (icon_right)
	{
		gray_sp->addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, gray_sp, Vec2(width, -width -85)));
	}
	if (UserDefault::getInstance()->getBoolForKey(ISHZ))
	{
		auto huangz_sp = Sprite::create("huangzhuang.png");
		addChild(huangz_sp);
		huangz_sp->setPosition(CommonFunction::getVisibleAchor(0, 0.5, Vec2(340, 40)));
	}

}

void AccountsLayer::quiteCallback(Ref* sender)
{
	if (this->getParent())
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::createScene()));
		//this->removeFromParent();
	}
}

void AccountsLayer::restartCallback(Ref* sender)
{
	if (this->getParent())
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
		//this->removeFromParent();
	}
}
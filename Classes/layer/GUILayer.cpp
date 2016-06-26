#include "GUILayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "utils/TimeCounter.h"
#include "ui/UIText.h"
#include "utils/GetLayer.h"
#include "PlayerOneState.h"

using namespace ui;

#define GAMELAYER 	GetLayer::getInstance()->getgameLayer()

GUILayer::GUILayer() : 
icon_left(nullptr), 
icon_right(nullptr),
icon_leftDown(nullptr), 
_light(nullptr),
_timecount(nullptr)
{
	auto _listener_1 = EventListenerCustom::create(PLAYERBLINK_0, [=](EventCustom*event){
		playerBlink_0();
	});

	auto _listener_2 = EventListenerCustom::create(PLAYERBLINK_1, [=](EventCustom*event){
		playerBlink_1();
	});

	auto _listener_3 = EventListenerCustom::create(PLAYERBLINK_2, [=](EventCustom*event){
		playerBlink_2();
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_3, 1);
}

GUILayer::~GUILayer()
{
	_eventDispatcher->removeCustomEventListeners(PLAYERBLINK_0);
	_eventDispatcher->removeCustomEventListeners(PLAYERBLINK_1);
	_eventDispatcher->removeCustomEventListeners(PLAYERBLINK_2);
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
	icon_left = Sprite::create("icon_girl_1.png");
	auto width = icon_left->getContentSize().width / 2 + 10;

	if (icon_left)
	{
		addChild(icon_left);
		icon_left->setPosition(CommonFunction::getVisibleAchor(0, 1, this, Vec2(width, -width)));
	}

	icon_leftDown = Sprite::create("icon_girl_2.png");
	if (icon_leftDown)
	{
		addChild(icon_leftDown);
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0, this, Vec2(width, width + 100)));
	}

	icon_right = Sprite::create("icon_boy_1.png");
	if (icon_right)
	{
		addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(1, 1, this, Vec2(-width, -width)));
	}
	//庄家
	auto zj_sp = Sprite::create("zhuangjia.png");
	if (zj_sp && icon_leftDown)
	{
		icon_leftDown->addChild(zj_sp);
		zj_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, icon_leftDown, Vec2(3, -50)));
	}

	_timecount = TimeCounter::create();
	addChild(_timecount);
	_timecount->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,this,Vec2(0,0)));
	_timecount->setVisible(false);
	_timecount->setScale(0.7f);

	_light = Sprite::create("icon_image/light.png");
	if (_light)
	{
		_light->setScale(0.8f);
		addChild(_light, -1);
		_light->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftTop, Vec2(0, 640)));
	}
	showNameAndMoney();
}

void GUILayer::showNameAndMoney()
{
	if (icon_left)
	{
		auto name_str = CommonFunction::WStrToUTF8(L"杨二狗");
		auto name_lb = Label::createWithSystemFont(name_str, "arial", 20);
		if (name_lb)
		{
			icon_left->addChild(name_lb);
			name_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, icon_left, Vec2(0, -20)));
		}

		auto square_sp = Sprite::create("square.png");
		if (square_sp)
		{
			icon_left->addChild(square_sp);
			square_sp->setScale(0.7);
			square_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::RightButtom, icon_left, Vec2(-20, -45)));

			auto gold_sp = Sprite::create("gold.png");
			if (gold_sp)
			{
				square_sp->addChild(gold_sp);
				gold_sp->setScale(0.3f);
				gold_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, square_sp,Vec2(25,0)));
			}

			auto gold_lb =Label::createWithBMFont("fonts/huangshe.fnt", "5000", TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (gold_lb)
			{
				gold_lb->setScale(0.5f);
				square_sp->addChild(gold_lb);
				gold_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, square_sp, Vec2(0, 0)));
			}
		}

	}
	if (icon_leftDown)
	{
		auto name_str = CommonFunction::WStrToUTF8(L"王铁柱");
		auto name_lb = Label::createWithSystemFont(name_str, "arial", 20);
		if (name_lb)
		{
			icon_leftDown->addChild(name_lb);
			name_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, name_lb, Vec2(5, -50)));
		}

		auto square_sp = Sprite::create("square.png");
		if (square_sp)
		{
			icon_leftDown->addChild(square_sp);
			square_sp->setScale(0.7);
			square_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::RightButtom, icon_leftDown, Vec2(-20, -75)));

			auto gold_sp = Sprite::create("gold.png");
			if (gold_sp)
			{
				square_sp->addChild(gold_sp);
				gold_sp->setScale(0.3f);
				gold_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, square_sp, Vec2(25, 0)));
			}

			auto gold_lb = Label::createWithBMFont("fonts/huangshe.fnt", "1000", TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (gold_lb)
			{
				gold_lb->setScale(0.5f);
				square_sp->addChild(gold_lb);
				gold_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, square_sp, Vec2(0, 0)));
			}
		}
	}
	if (icon_right)
	{
		auto name_str = CommonFunction::WStrToUTF8(L"雁子飞人");
		auto name_lb = Label::createWithSystemFont(name_str, "arial", 20);
		if (name_lb)
		{
			icon_right->addChild(name_lb);
			name_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, icon_right, Vec2(0, -20)));
		}

		auto square_sp = Sprite::create("square.png");
		if (square_sp)
		{
			icon_right->addChild(square_sp);
			square_sp->setScale(0.7);
			square_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftButtom, icon_right, Vec2(23, -45)));

			auto gold_sp = Sprite::create("gold.png");
			if (gold_sp)
			{
				square_sp->addChild(gold_sp);
				gold_sp->setScale(0.3f);
				gold_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, square_sp, Vec2(25, 0)));
			}

			auto gold_lb = Label::createWithBMFont("fonts/huangshe.fnt", "1500", TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (gold_lb)
			{
				gold_lb->setScale(0.5f);
				square_sp->addChild(gold_lb);
				gold_lb->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, square_sp, Vec2(0, 0)));
			}
		}
	}
}

void GUILayer::playerBlink_0()	//上家
{
	if (_timecount)
	{
		_timecount->setPosition(icon_left->getPosition() + Vec2(100, 0));
		_timecount->start(15, [=](){
			if (GAMELAYER->getChildByName(CHOOSELAYER))
			{
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TIMEOUT_CLOSE);
				if (GAMELAYER->getChildByName(CHICARDLAYER))
				{
					GAMELAYER->removeChildByName(CHICARDLAYER);
				}
			}
			log("0 timeout........"); 
		});
	}

	if (_light)
	{
		_light->setPosition(icon_left->getPosition());
		auto fadeout = FadeOut::create(0.5f);
		auto fadein = FadeIn::create(0.5f);
		auto repeat = RepeatForever::create(Sequence::create(fadeout, fadein, nullptr));
		_light->runAction(repeat);
	}
}

void GUILayer::playerBlink_1()//下家
{
	if (_timecount)
	{
		_timecount->setPosition(icon_right->getPosition() + Vec2(-100, 0));
		_timecount->start(15, [=](){
			
			if (GAMELAYER->getChildByName(CHOOSELAYER))
			{
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TIMEOUT_CLOSE);
				if (GAMELAYER->getChildByName(CHICARDLAYER))
				{
					GAMELAYER->removeChildByName(CHICARDLAYER);
				}
			}
			log("1 timeout........"); 
		
		});
	}

	if (_light)
	{
		_light->setPosition(icon_right->getPosition());
		auto fadeout = FadeOut::create(0.5f);
		auto fadein = FadeIn::create(0.5f);
		auto repeat = RepeatForever::create(Sequence::create(fadeout, fadein, nullptr));
		_light->runAction(repeat);
	}

}

void GUILayer::playerBlink_2()
{
	if (_timecount)
	{
		_timecount->setVisible(true);
		_timecount->setPosition(icon_leftDown->getPosition() + Vec2(0, 100));
		_timecount->start(15, [=](){
			
			//若是我吃牌或碰牌，默认过
			if (!UserDefault::getInstance()->getBoolForKey(ISFIRSTPLAY))
			{
				//第一次打牌  若过了15秒自动出一张牌
				GAMELAYER->t_Player[2].delACard(0);
				GAMELAYER->refrishCardPos();
				GAMELAYER->PopPai = GAMELAYER->t_Player[2].popCard;
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CREATE_CARD);
				UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, true);
				UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//打完牌后我可以摸牌
				UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, false);	//打完牌后我不能出牌
				GAMELAYER->changeState(new PlayerOneState());
				GAMELAYER->setActionVisible(false);
			}
			else
			{
				if (!UserDefault::getInstance()->getBoolForKey(ISGETORPLAY))
				{
					//若是我打牌 默认出一张牌
					GAMELAYER->t_Player[2].delACard(0);
					GAMELAYER->refrishCardPos();
					GAMELAYER->PopPai = GAMELAYER->t_Player[2].popCard;
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CREATE_CARD);
					UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, true);
					UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//打完牌后我可以摸牌
					UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, false);	//打完牌后我不能出牌
					GAMELAYER->changeState(new PlayerOneState());
					GAMELAYER->setActionVisible(false);
				}
			}

			if (GAMELAYER->getChildByName(CHOOSELAYER))
			{
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TIMEOUT_CLOSE);
				if (GAMELAYER->getChildByName(CHICARDLAYER))
				{
					GAMELAYER->removeChildByName(CHICARDLAYER);
				}
			}
			log("2 timeout........"); 
		});
	}

	if (_light)
	{
		_light->setPosition(icon_leftDown->getPosition());
		auto fadeout = FadeOut::create(0.5f);
		auto fadein = FadeIn::create(0.5f);
		auto repeat = RepeatForever::create(Sequence::create(fadeout, fadein, nullptr));
		_light->runAction(repeat);
	}
}
#include "GUILayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "utils/TimeCounter.h"

GUILayer::GUILayer() : icon_left(nullptr), icon_right(nullptr), icon_leftDown(nullptr), _timecount(nullptr)
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
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0, this, Vec2(width, width)));
	}

	icon_right = Sprite::create("icon_boy_1.png");
	if (icon_right)
	{
		addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(1, 1, this, Vec2(-width, -width)));
	}

	_timecount = TimeCounter::create();
	addChild(_timecount);
	_timecount->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,this,Vec2(0,0)));
	_timecount->setVisible(false);
	_timecount->setScale(0.7f);
}

void GUILayer::playerBlink_0()	//上家
{
	if (!_timecount)
	{
		return;
	}
	cout << "playerBlink_0" << endl;

	_timecount->setPosition(icon_left->getPosition() + Vec2(0, -100));
	_timecount->start(5, [](){log("0 timeout........"); });

}

void GUILayer::playerBlink_1()//下家
{
	if (!_timecount)
	{
		return;
	}
	cout << "playerBlink_1" << endl;

	_timecount->setPosition(icon_right->getPosition() + Vec2(0, -100));
	_timecount->start(5, [](){log("1 timeout........"); });
}

void GUILayer::playerBlink_2()
{
	if (!_timecount)
	{
		return;
	}
	cout << "playerBlink_2" << endl;
	_timecount->setVisible(true);
	_timecount->setPosition(icon_leftDown->getPosition() + Vec2(0,100));
	_timecount->start(5, [](){log("2 timeout........"); });
}
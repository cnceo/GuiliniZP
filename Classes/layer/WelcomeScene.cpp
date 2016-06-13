#include "WelcomeScene.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"
#include "GameScene.h"
#include "utils/Constant.h"

using namespace ui;

WelcomeScene::WelcomeScene():
m_goldLabel(nullptr),
m_diamLabel(nullptr)
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

void WelcomeScene::onEnter()
{
	Layer::onEnter();

	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(WelcomeScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
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
	//背景
	auto bg_sp = Sprite::create("hall/bg_image.png");
	if (bg_sp)
	{
		float w = bg_sp->getContentSize().width;
		float h = bg_sp->getContentSize().height;

		bg_sp->setScale(VISIBLESIZE.width / w, VISIBLESIZE.height / h);

		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
	}

	//中间
	auto item_0 = MenuItemSprite::create(Sprite::create("hall/ima_two.png"), Sprite::create("hall/ima_two.png"));
	auto item_1 = MenuItemSprite::create(Sprite::create("hall/ima_seven.png"),Sprite::create("hall/ima_seven.png"));
	auto item_2 = MenuItemSprite::create(Sprite::create("hall/ima_ten.png"), Sprite::create("hall/ima_ten.png"));

	if (item_0 && item_1 && item_2)
	{
		item_0->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(-300, 0)));
		item_1->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
		item_2->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(300, 0)));

		auto menu = Menu::create(item_0, item_1, item_2, nullptr);
		addChild(menu);
		menu->setPosition(Vec2::ZERO);

		item_0->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));
		item_1->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));
		item_2->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));
	}

	auto room_0 = MenuItemSprite::create(Sprite::create("hall/room_ct.png"), Sprite::create("hall/room_ct.png"));
	auto room_1 = MenuItemSprite::create(Sprite::create("hall/room_ziyou.png"), Sprite::create("hall/room_ziyou.png"));
	auto room_2 = MenuItemSprite::create(Sprite::create("hall/room_bisai.png"), Sprite::create("hall/room_bisai.png"));

	if (room_0 && room_1 && room_2)
	{
		room_0->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(-300, -175)));
		room_1->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, -175)));
		room_2->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(300, -175)));

		auto menu_1 = Menu::create(room_0, room_1, room_2, nullptr);
		addChild(menu_1);
		menu_1->setPosition(Vec2::ZERO);
	}
	//右上角
	auto water_sp = Sprite::create("hall/water.png");
	if (!water_sp) return;

	addChild(water_sp);
	float _width = water_sp->getContentSize().width / 2 ;
	float _height = water_sp->getContentSize().height / 2 + 20;
	water_sp->setPosition(CommonFunction::getVisibleAchor(1, 1, Vec2(-_width, -_height)));

	auto shop_btn =		Button::create("hall/lab_shop.png");
	auto mission_btn =	Button::create("hall/lab_mission.png");
	auto bag_btn=		Button::create("hall/lab_bag.png");
	auto setting_btn =	Button::create("hall/lab_setting.png");

	if (shop_btn && mission_btn && bag_btn && setting_btn)
	{
		auto _node = Node::create();
		water_sp->addChild(_node);
		_node->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,water_sp,Vec2(0,0)));

		_node->addChild(shop_btn);
		_node->addChild(mission_btn);
		_node->addChild(bag_btn);
		_node->addChild(setting_btn);

		shop_btn->setPosition(CommonFunction::getVisibleAchor(0, 0, _node, Vec2(-175, 0)));
		mission_btn->setPosition(CommonFunction::getVisibleAchor(0, 0, _node, Vec2(-75, 0)));
		bag_btn->setPosition(CommonFunction::getVisibleAchor(0, 0, _node, Vec2(15, 0)));
		setting_btn->setPosition(CommonFunction::getVisibleAchor(0, 0, _node, Vec2(100, 0)));
	}

	//左上角
	auto hero_icon = Button::create("icon_girl_2.png");
	if (hero_icon)
	{
		addChild(hero_icon);
		float _height = hero_icon->getContentSize().height;
		hero_icon->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(_height, -_height)));
	}

	auto gold_sp = Sprite::create("hall/blab_conit.png");
	auto diam_sp = Sprite::create("hall/blab_diam.png");

	if (gold_sp && diam_sp && hero_icon)
	{
		hero_icon->addChild(gold_sp);
		hero_icon->addChild(diam_sp);

		gold_sp->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(75, 25)));
		diam_sp->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(75, -25)));
	}

	auto gold_bg = Sprite::create("hall/square.png");
	auto diam_bg = Sprite::create("hall/square.png");

	if (gold_bg && diam_bg && hero_icon)
	{
		hero_icon->addChild(gold_bg);
		hero_icon->addChild(diam_bg);

		gold_bg->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(175, 25)));
		diam_bg->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(175, -25)));
	}

	m_goldLabel = Label::createWithTTF("20000","fonts/Roboto-Medium.ttf",32);
	m_diamLabel = Label::createWithTTF("100000", "fonts/Roboto-Medium.ttf", 32);
	if (m_goldLabel && m_diamLabel && gold_bg && diam_bg)
	{
		gold_bg->addChild(m_goldLabel);
		diam_bg->addChild(m_diamLabel);

		m_goldLabel->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, gold_bg, Vec2(0, 0)));
		m_diamLabel->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, diam_bg, Vec2(0, 0)));
	}
}

void WelcomeScene::startGameCBK(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::createScene()));
}

void WelcomeScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
		{
			if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
			{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

				JniMethodInfo info;
				bool ret = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "exitGame", "()V");
				if (ret)
				{
					jobject jobj = info.env->CallStaticObjectMethod(info.classID, info.methodID);
				}
				LOGD("end game<<<<");
#else
				//Director::getInstance()->end();
#endif
			}
		}
	}
}
#include "WelcomeScene.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"
#include "GameScene.h"
#include "utils/Constant.h"
#include "layerUtils/RotateMenu.h"

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
		//float w = bg_sp->getContentSize().width;
		//float h = bg_sp->getContentSize().height;
		//bg_sp->setScale(VISIBLESIZE.width / w, VISIBLESIZE.height / h);

		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
	}
	//中间
	auto item_0 = MenuItemSprite::create(Sprite::create("hall/ima_bisai.png"), Sprite::create("hall/ima_bisai.png"));
	auto item_1 = MenuItemSprite::create(Sprite::create("hall/ima_ct.png"),Sprite::create("hall/ima_ct.png"));
	auto item_2 = MenuItemSprite::create(Sprite::create("hall/ima_ziyou.png"), Sprite::create("hall/ima_ziyou.png"));
	//auto item_3 = MenuItemSprite::create(Sprite::create("hall/ima_ziyou.png"), Sprite::create("hall/ima_ziyou.png"));

	if (item_0 && item_1 && item_2)
	{
		auto rotateMenu = RotateMenu::create();
		rotateMenu->addMenuItem(item_0);
		rotateMenu->addMenuItem(item_1);
		rotateMenu->addMenuItem(item_2);
		//rotateMenu->addMenuItem(item_3);

		addChild(rotateMenu);
		rotateMenu->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(-150, 20)));

		item_0->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));
		item_1->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));
		item_2->setCallback(CC_CALLBACK_1(WelcomeScene::startGameCBK, this));

		item_0->setTag(0);
		item_1->setTag(1);
		item_2->setTag(2);
	}

	auto shop_btn =		Button::create("hall/lab_shop.png");
	auto mission_btn =	Button::create("hall/lab_mission.png");
	auto bag_btn=		Button::create("hall/lab_bag.png");
	auto setting_btn =	Button::create("hall/lab_setting.png");

	if (shop_btn && mission_btn && bag_btn && setting_btn)
	{
		auto _node = Node::create();
		_node->setContentSize(Size(477, 82));
		addChild(_node);

		_node->setPosition(CommonFunction::getVisibleAchor(1, 1, Vec2(-477 / 2, -82 / 2)));


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

		gold_bg->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(200, 25)));
		diam_bg->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, hero_icon, Vec2(200, -25)));
	}

	m_goldLabel = Label::createWithTTF("2000","fonts/Roboto-Medium.ttf",32);
	m_diamLabel = Label::createWithTTF("1000", "fonts/Roboto-Medium.ttf", 32);
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
	int _tag = ((MenuItemSprite*)pSender)->getTag();
	if (_tag == 0)
	{
		std::cout << "二二二二二二二二" << std::endl;
	}
	else if (_tag == 1)
	{
		std::cout << "七七七七七七七七七" << std::endl;
	}
	else if (_tag == 2)
	{
		std::cout << "十十十十十十十十" << std::endl;
	}
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
﻿#include "GameLayer.h"
#include "utils/Constant.h"
#include "CCPlatformConfig.h"
#include "utils/CommonFunction.h"
#include "layerUtils/Base.h"
#include "TestPopLayer.h"
#include "utils/Constant.h"
#include "layerUtils/ToastLayer/ToastManger.h"
#include "ShowLayer.h"
#include "ChooseLayer.h"
#include "BackLayer.h"
#include "ChiCardLayer.h"
#include "WelcomeScene.h"
#include "PlayerTwoState.h"
#include "PlayerOneState.h"
#include "PlayerZeroState.h"
#include "../AccountsLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else
#include <unistd.h>
#endif

GameLayer::GameLayer() :
m_isStartGame(true),
m_line(nullptr),
m_TempMoveCard(nullptr),
m_GameState(MyTurn),
m_CurrState(nullptr)
{
	auto _listener_1 = EventListenerCustom::create(PLAYER_PENG, [=](EventCustom*event){
		doPengACard();
	});

	auto _listener_2 = EventListenerCustom::create(CLOSE_CHOOSELAYER, [=](EventCustom*event){
		chooseLayerClose();
	});

	auto _listener_3 = EventListenerCustom::create(SHOW_CHICARDLAYER, [=](EventCustom*event){
		showChiCardLayer();
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_3, 1);
}

GameLayer::~GameLayer()
{
	_eventDispatcher->removeCustomEventListeners(PLAYER_PENG);
	_eventDispatcher->removeCustomEventListeners(CLOSE_CHOOSELAYER);
	_eventDispatcher->removeCustomEventListeners(SHOW_CHICARDLAYER);
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	scheduleUpdate();
	initData();
	initUI();

	addChild(ShowLayer::create(this));

	UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, false);	//是否第一次打牌
	UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//只摸牌不打牌
	UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//我是否可以出牌（能否触摸）
	UserDefault::getInstance()->setBoolForKey(ISHZ, false);			//没有黄庄	
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE,2);		//设置当前状态(我)

	changeState(new PlayerTwoState());
	return true;
}

void GameLayer::update(float dt)
{
	/*
		我(2)->下家(1)->上家(0)  逆时针
	*/

	if (m_CurrState)
	{
		m_CurrState->Update();
	}

	switch (m_GameState)
	{
	case GameLayer::NPCTurn_1:	//我下家
		
		//_eventDispatcher->dispatchCustomEvent(PLAYERBLINK_1);

		/*
			下家起一张牌
			我检测是否有：碰 ，开舵，重舵
		*/
		/*
		std::cout << "下家起牌~~~~~~~~~~~~~~~~" << std::endl;
		getANewCard();

		if (checkChongDuo())
		{
			std::cout << "重舵" << std::endl;
		}
		else if (checkKaiduo())
		{
			std::cout << "开舵" << std::endl;
		}
		else if (checkPeng())
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(2);
		}
		
		//logAllCard();
		m_GameState = GameLayer::NPCTurn_0;
		*/
		break;
	case GameLayer::NPCTurn_0:	//我上家
		//_eventDispatcher->dispatchCustomEvent(PLAYERBLINK_0);

		/*
			上家起一张牌
			我检测是否有：吃，碰，开舵，重舵
		*/

		/*
		std::cout << "上家起牌~~~~~~~~~~~~~~~~" << std::endl;

		getANewCard();

		if (checkChongDuo())
		{
			std::cout << "重舵" << std::endl;
		}
		else if (checkKaiduo())
		{
			std::cout << "开舵" << std::endl;
		}
		else if (checkChi() && checkPeng())	//可吃可碰
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(4);
		}
		else if (checkChi() && !checkPeng())	//可吃不能碰
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(1);
		}
		else if (!checkChi() && checkPeng())	//可碰不能吃
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(2);
		}
		
		logAllCard();
		
		m_GameState = GameLayer::MyTurn;
		*/
		break;
	case GameLayer::MyTurn:		//我出牌
		break;
	case GameLayer::OFF:		//轮到我起牌
		/*
		我起一张牌
		我检测是否有：吃，碰，扫，过扫，扫穿，开舵，重舵
		*/
		/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//::_sleep(2000);
#else
		usleep(2000000);
#endif
		std::cout << "我起牌~~~~~~~~~~~~~~~~" << std::endl;

		getANewCard();
		if (checkChongDuo())
		{
			std::cout << "重舵" << std::endl;
		}
		else if (checkSaochuan())
		{
			std::cout << "扫穿" << std::endl;
		}
		else if (checkKaiduo())
		{
			std::cout << "开舵" << std::endl;
		}
		//else if (true)	//过扫 (可碰未碰)
		//{

		//}
		else if (checkSao())	//扫
		{
			std::cout << "扫" << std::endl;
		}
		else if (checkChi() && checkPeng())	//碰 吃
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(4);
		}
		else if (checkChi() && !checkPeng())	//可吃不能碰
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(1);
		}
		else if (!checkChi() && checkPeng())	//可碰不能吃
		{
			unscheduleUpdate();
			auto chooseLayer = ChooseLayer::create();
			addChild(chooseLayer);
			chooseLayer->setBtnEnable(2);
		}
		logAllCard();
		m_GameState = GameLayer::MyTurn;
		*/
		break;
	default:
		break;
	}
}

void GameLayer::changeState(StateManager* _state)
{
	if (m_CurrState)
	{
		delete m_CurrState;
		m_CurrState = _state;
		return;
	}
	m_CurrState = _state;
}

bool GameLayer::checkPeng()
{
	//下家摸的牌，我检测
	if (t_Player[2].checkPengACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		return true;
	}
	return false;
}

void GameLayer::doPengACard()
{
	t_Player[2].doPengACard(m_newCard.m_Type, m_newCard.m_Value);
	ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我碰！！！"));

	UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//碰完后我打牌
	UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
	changeState(new PlayerTwoState());								//碰完后我打牌

	createMyCardWall();		//重新显示牌面
	_eventDispatcher->dispatchCustomEvent(SHOW_PENGCARD);	//显示层显示碰的牌
}

bool GameLayer::checkChi()
{
	bool isAction = false;	//有可吃的

	if (!m_TempChiCard.empty())
	{
		m_TempChiCard.clear();
	}

	if (!m_TempChiList.empty())
	{
		m_TempChiList.clear();
	}

	/*if (t_Player[2].checkChiACard1_2_3(m_newCard.m_Type, m_newCard.m_Value))
	{
		for (auto &_data:t_Player[2].m_TempChiCardVec)
		{
			m_TempChiCard.push_back(_data);
		}
		isAction = true;
	}*/

	if (t_Player[2].checkChiACard2_7_10(m_newCard.m_Type, m_newCard.m_Value))
	{
		for (auto &_data : t_Player[2].m_TempChiCardVec)
		{
			m_TempChiCard.push_back(_data);
		}
		isAction = true;
	}

	if (t_Player[2].checkChiA_B_C(m_newCard.m_Type, m_newCard.m_Value))
	{
		for (auto &_data : t_Player[2].m_TempChiCardVec)
		{
			m_TempChiCard.push_back(_data);
		}

		isAction = true;
	}

	if (t_Player[2].checkChiACardA_A_a(m_newCard.m_Type, m_newCard.m_Value))
	{
		for (auto &_data : t_Player[2].m_TempChiCardList)
		{
			m_TempChiList.push_back(_data);
		}

		isAction = true;
	}

	if (t_Player[2].checkChiACardA_A_a_a(m_newCard.m_Type, m_newCard.m_Value))
	{
		for (auto &_data : t_Player[2].m_TempChiCardList)
		{
			m_TempChiList.push_back(_data);
		}

		isAction = true;
	}

	if (isAction)
	{
		return true;
	}

	return false;
}

void GameLayer::doChiACard(int num)
{
	/*t_Player[2].doChi1_2_3(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChi2_7_10(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChiA_B_C(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChiA_A_a(m_newCard.m_Type, m_newCard.m_Value);
	t_Player[2].doChiA_A_a_a(m_newCard.m_Type, m_newCard.m_Value);*/
}

void GameLayer::showChiCardLayer()
{
	//显示吃的牌层
	addChild(ChiCardLayer::create(this));
}

bool GameLayer::checkSaochuan()
{
	//自己摸的牌 检测
	bool isAction = false;
	if (t_Player[2].checkSaoChuanACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"起手牌扫穿！！！"));
		t_Player[2].doSaoChuanACard(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCHUANCARD);
		isAction = true;

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫穿完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
	}

	if (t_Player[2].checkSao_saoChuanACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫的扫穿！！！"));
		t_Player[2].doSao_SaoChuan(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCHUANCARD);
		isAction = true;

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫穿完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
	}

	if (isAction)
	{
		return true;
	}
	return false;
}

bool GameLayer::checkSao()
{
	if (t_Player[2].checkSaoACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫！！！"));
		t_Player[2].doSaoACard(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCARD);

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

		return true;
	}
	return false;
}

void GameLayer::chooseLayerClose()
{
	ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我不想碰也不想吃！！"));
	int _state = UserDefault::getInstance()->getIntegerForKey(GAMESTATE, 0);
	if (_state == 0)
	{
		changeState(new PlayerTwoState());
	}
	else if (_state == 1)
	{
		changeState(new PlayerZeroState());
	}
	else if (_state == 2)
	{
		changeState(new PlayerOneState());
	}
	else
	{
		changeState(new PlayerTwoState());
	}
}

bool GameLayer::checkKaiduo()
{
	//别人摸的牌，我检测
	bool isAction = false;
	if (t_Player[2].checkKaiduoACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"起手牌开舵！！！"));
		t_Player[2].doKaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}

	if (t_Player[2].checkKaiDuo_Sao(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫的开舵！！！"));
		t_Player[2].doSao_KaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}

	if (t_Player[2].checkKaiDuo_peng(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"碰的开舵！！！"));
		t_Player[2].doPeng_kaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}
	if (isAction)
	{
		return true;
	}
	return false;

}

bool GameLayer::checkChongDuo()
{
	//重舵以后无需出牌，下家直接摸牌

	bool isAction = false;
	if (t_Player[2].checkChongDuo_kaiDuo(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"!!开舵的重舵！！！"));
		t_Player[2].doChongDuo_kaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();
		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);

		isAction = true;
		changeState(new PlayerOneState());
	}
	//扫穿还没处理好
	if (t_Player[2].checkChongDuo_saoChuan(m_newCard.m_Type, m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫穿的重舵！！！"));
		t_Player[2].doChongDuo_saoChuan(m_newCard.m_Type, m_newCard.m_Value);
		createMyCardWall();

		isAction = true;
		changeState(new PlayerOneState());
	}

	if (isAction)
	{
		return true;
	}
	return false;
}

void GameLayer::initData()
{

}

void GameLayer::onEnter()
{
	Layer::onEnter();

	auto listenerEvent = EventListenerTouchOneByOne::create();
	listenerEvent->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (m_GameState != GameLayer::GameState::MyTurn)
	{
		return false;
	}
	if (!UserDefault::getInstance()->getBoolForKey(ISPLAYCAED))
	{
		return false;
	}

	vector <CardSprite*>::iterator iter = m_CardList.begin();
	for (; iter != m_CardList.end(); ++iter)
	{
		CardSprite* _card = static_cast<CardSprite*>(*iter);
		Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

		Size s = _card->getContentSize();
		Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			m_TempMoveCard = _card;
			m_OldPos = _card->getPosition(); 
			m_TempMoveCard->setLocalZOrder(CARD_ZORDER_2);

			if (_card->getState() == CardSprite::CardState::ONTouch)
			{
				//画线
				m_line = DrawNode::create();
				addChild(m_line);
				if (m_line)
				{
					m_line->drawSegment(Point(0, VISIBLESIZE.height / 2 - 50), Point(VISIBLESIZE.width, VISIBLESIZE.height / 2 - 50), 2, Color4F(0, 1, 0, 1));
				}
				return true;
			}
			else
			{
				return false;
			}

			return true;
		}
	}

	return false;
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (m_TempMoveCard)
	{
		m_TempMoveCard->setPosition(touch->getLocation());
	}
}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (m_line)
	{
		m_line->clear();
	}
	if (!m_TempMoveCard)
	{
		return;
	}

	m_TempMoveCard->setLocalZOrder(CARD_ZORDER_1);

	if (touch->getLocation().y > VISIBLESIZE.height / 2 - 50)
	{
		int _type = m_TempMoveCard->getCardData()->m_Type;
		int _value = m_TempMoveCard->getCardData()->m_Value;
		
		if (_type == 0)
		{
			cout << "打了张：小"  << _value << endl;
			ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张小") + Value(_value).asString());
		}
		else
		{
			cout << "打了张：大" << _value << endl;
			ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张大") + Value(_value).asString());
		}

		t_Player[2].delACard(_type, _value);

		createMyCardWall();
	
		PopPai[2] = t_Player[2].popCard;
		_eventDispatcher->dispatchCustomEvent(CREATE_CARD);

		UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY,true);
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//打完牌后我可以摸牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, false);	//打完牌后我不能出牌
		changeState(new PlayerOneState());
	}
	else
	{
		m_TempMoveCard->setPosition(m_OldPos);
	}

	if (m_TempMoveCard)
	{
		m_TempMoveCard = nullptr;
	}
}

void GameLayer::initUI()
{
	auto bg_sp = Sprite::create("zm_bg.png");
	if (bg_sp)
	{
		addChild(bg_sp);

		//float w = bg_sp->getContentSize().width;
		//float h = bg_sp->getContentSize().height;
		//bg_sp->setScale(VISIBLESIZE.width / w, VISIBLESIZE.height / h);

		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,this,Vec2::ZERO));
	}

	auto back_btn = Button::create("backBtn.png");
	if (back_btn)
	{
		addChild(back_btn);
		back_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 1, Vec2(-135, -back_btn->getContentSize().height / 2 - 10)));
		back_btn->addClickEventListener([this](Ref*){
			Director::getInstance()->replaceScene(WelcomeScene::createScene());
		});
	}

	//开始游戏
	auto startButton = Button::create("CloseSelected.png", "CloseNormal.png");
	startButton->setPosition(CommonFunction::getVisibleAchor(1,0.2,this,Vec2(-50,50)));
	addChild(startButton);
	if (startButton && m_isStartGame)
	{
		startButton->addClickEventListener(CC_CALLBACK_1(GameLayer::startCallBack, this));
	}
	else
	{
		startButton->addClickEventListener(CC_CALLBACK_1(GameLayer::overCallBack, this));
	}
}

void GameLayer::startCallBack(Ref* ref)
{
	UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, false);
	_eventDispatcher->dispatchCustomEvent(PLAYERBLINK_2);
	xipai();
	//addChild(AccountsLayer::create());
	_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);			/****/
	_eventDispatcher->dispatchCustomEvent(SHOW_SAOCHUANCARD);		/****/
	_eventDispatcher->dispatchCustomEvent(SHOW_SAOCARD);		/****/
	_eventDispatcher->dispatchCustomEvent(SHOW_PENGCARD);		/****/
}

void GameLayer::overCallBack(Ref* ref)
{

}

void GameLayer::getANewCard()
{
	CardEx t_newCard = t_ZPManage.GetAPai();

	if (t_newCard.m_CardNum <= 0)
	{
		cout << "黄庄" << endl;
		UserDefault::getInstance()->setBoolForKey(ISHZ, true);			//黄庄	

		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, AccountsLayer::createScene()));
		return;
	}

	if (t_newCard.IsHz == true)
	{
		m_newCard = t_newCard.m_NewCard;
		_eventDispatcher->dispatchCustomEvent(NEW_CARD);

	}
	else
	{
		m_newCard = t_newCard.m_NewCard;
		cout << "剩" << t_newCard.m_CardNum << "张牌" << endl;
		_eventDispatcher->dispatchCustomEvent(NEW_CARD);
	}
}

void GameLayer::xipai()
{
	t_ZPManage.InitPai(0);

	for (int i = 0; i < 3; i++)
	{
		t_Player[i].CleanUp();
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CardEx t_pai2 = t_ZPManage.GetAPai();
			t_Player[j].addCard(t_pai2.m_NewCard.m_Type, t_pai2.m_NewCard.m_Value);
		}
	}

	CardEx t_pai = t_ZPManage.GetAPai();	//档低牌
	t_Player[2].addCard(t_pai.m_NewCard.m_Type, t_pai.m_NewCard.m_Value);

	logAllCard();
	createMyCardWall();
}

void GameLayer::logAllCard()
{
	cout << "自己的牌（2）" << endl;
	t_Player[2].logAllCard();
	cout << "下家的牌（1）" << endl;
	t_Player[1].logAllCard();
	cout << "上家的牌（0）" << endl;
	t_Player[0].logAllCard();
	cout << "----------------------------------------" << endl;
}

void GameLayer::createMyCardWall()
{
	removeMyCardWall();

	float x = 200;
	float y = 110;
	int count = 0;

	if (t_Player[2].m_MyCard[0].size() > 0)
	{
		for (int i = 0; i < t_Player[2].m_MyCard[0].size(); i++)
		{
			CardSprite* _card = CardSprite::create(0, t_Player[2].m_MyCard[0][i]);
			addChild(_card);
			if (_card)
			{
				m_CardList.pushBack(_card);
			}
		}
	}
	if (t_Player[2].m_MyCard[1].size() > 0)
	{
		for (int i = 0; i < t_Player[2].m_MyCard[1].size(); i++)
		{
			CardSprite* _card = CardSprite::create(1, t_Player[2].m_MyCard[1][i]);
			addChild(_card);
			if (_card)
			{
				m_CardList.pushBack(_card);
			}
		}
	}

	if (!m_CardList.empty())
	{
		for (int i = 0; i < m_CardList.size();++i)
		{
			if (m_CardList.at(i))
			{
				m_CardList.at(i)->setPosition(CommonFunction::getVisibleAchor(0.13f, 0, Vec2(42 * i, 80)));
			}
		}
	}

	setCardState();
	refrishCardPos();	//跟新位置
}

void GameLayer::refrishCardPos()
{
	Vector<CardSprite*> _tempCardList;

	for (auto &_card: m_CardList)
	{
		if (_card->getState() == CardSprite::CardState::OFFTouch)
		{
			//_card->setVisible(false);
		}
	}
}

void GameLayer::removeMyCardWall()
{
	vector<CardSprite*> ::iterator it = m_CardList.begin();
	for (it; it != m_CardList.end(); ++it)
	{
		if (*it && (*it)->getParent())
		{
			(*it)->removeFromParent();
		}
	}
	m_CardList.clear();
}

void GameLayer::setCardState()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _temp_0;

	for (auto& _card : m_CardList)
	{
		_tempList.push_back(_card);
	}

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : m_CardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 0 && _type == 0)
			{
				if (_tvalue == _value)
				{
					_count ++;
					if (_count>=3)
					{
						_temp_0.push_back(_card);
					}
				}
	
			}
		}
	}

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : m_CardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 1 && _type == 1)
			{
				if (_tvalue == _value)
				{
					_count++;
					if (_count >= 3)
					{
						_temp_0.push_back(_card);
					}
				}

			}
		}
	}

	auto Iter = std::unique(std::begin(_temp_0), std::end(_temp_0));
	_temp_0.erase(Iter, _temp_0.end());

	for (auto &_tcard : _temp_0)
	{
		for (auto& _card : m_CardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setState(CardSprite::CardState::OFFTouch);
				}
			}
		}
	}
}
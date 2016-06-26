#include "GameLayer.h"
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
#include "utils/GetScore.h"
#include "ShowOneLayer.h"
#include "ShowZeroLayer.h"
#include "utils/GetLayer.h"
#include "RatioLayer.h"
#include "MyCardWall.h"
#include "Effect/CardEffect.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else
#include <unistd.h>
#endif

GameLayer::GameLayer() :
m_isStartGame(true),
m_line(nullptr),
m_TempMoveCard(nullptr),
m_GameState(MyTurn),
m_CurrState(nullptr),
m_beilv(nullptr),
_beilv(1000),
m_dipai(nullptr),
score(nullptr),
_hand(nullptr),
_note(nullptr),
_needVisible(false),
_SumTime(0),
_cardCount(0)
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

	auto _listener_4 = EventListenerCustom::create(PLAYER_CHI, [=](EventCustom*event){
	
	});

	auto _listener_5 = EventListenerCustom::create(SHOW_RATIOLAYER, [=](EventCustom*event){
		auto delayTime = DelayTime::create(1.0f);
		auto callfunc = CallFunc::create([=]{
			RatioLayer* ratiolayer = RatioLayer::create(this);
			addChild(ratiolayer);
		});
		this->runAction(Sequence::create(delayTime, callfunc, nullptr));
	});

	//REPLACE_ACCOUNTS //跳转到结算
	auto _listener_6 = EventListenerCustom::create(REPLACE_ACCOUNTS, [=](EventCustom*event){
		auto delayTime = DelayTime::create(3.0f);
		auto callfunc = CallFunc::create([](){
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, AccountsLayer::createScene()));
		});
		this->runAction(Sequence::create(delayTime,callfunc,nullptr));
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_3, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_4, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_5, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_6, 1);
}

GameLayer::~GameLayer()
{
	_eventDispatcher->removeCustomEventListeners(PLAYER_PENG);
	_eventDispatcher->removeCustomEventListeners(CLOSE_CHOOSELAYER);
	_eventDispatcher->removeCustomEventListeners(SHOW_CHICARDLAYER);
	_eventDispatcher->removeCustomEventListeners(PLAYER_CHI);
	_eventDispatcher->removeCustomEventListeners(SHOW_RATIOLAYER);
	_eventDispatcher->removeCustomEventListeners(REPLACE_ACCOUNTS);

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

	auto showlayer = ShowLayer::create(this);
	addChild(showlayer);		//自己显示操作的牌
	GetLayer::getInstance()->setShowLayer(showlayer);

	//下家显示
	auto _oneLayer = ShowOneLayer::create(this);
	addChild(_oneLayer);	
	GetLayer::getInstance()->setOneLayer(_oneLayer);

	//上家显示
	auto _zeroLayer = ShowZeroLayer::create(this);
	addChild(_zeroLayer);
	GetLayer::getInstance()->setZeroLayer(_zeroLayer);

	UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, false);	//是否第一次打牌
	UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//只摸牌不打牌
	UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, false);	//我是否可以出牌（能否触摸）
	UserDefault::getInstance()->setBoolForKey(ISHZ, false);			//没有黄庄	
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE,2);		//设置当前状态(我)

	changeState(new PlayerTwoState());

	auto _delay_1 = DelayTime::create(1.0f);
	auto _delay_2 = DelayTime::create(5.5f);

	auto _callfunc_1 = CallFunc::create([=](){
	
		UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, false);
		xipai();
		_needVisible = true;
		//log("visible=%d", _needVisible?true:false);
		//addChild(MyCardWall::create(this));
	});
	auto _callfunc_2 = CallFunc::create([=](){
		creatAction();
	});
	auto _callfunc_3 = CallFunc::create([=](){
		_eventDispatcher->dispatchCustomEvent(PLAYERBLINK_2);
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);
	});
	auto _seq = Sequence::create(_delay_1, _callfunc_1, _delay_2, _callfunc_2, _callfunc_3, nullptr);
	runAction(_seq);

	addChild(CardEffect::create());
	return true;
}

void GameLayer::update(float dt)
{
	if (_needVisible)
	{
		_SumTime += dt;
		if (_SumTime > 0.07)
		{
			setVisibleOneByOne();		//一行行显示
			_SumTime = 0;
		}
	}

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

bool GameLayer::checkHu()
{
	if (t_Player[2].checkHuPai(m_newCard.m_Type, m_newCard.m_Value))
	{
		refrishCardPos();
		return true;
	}
	return false;
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
	//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我碰！！！"));

		//特效
	string str = "effect/peng.png";
	addEffect(str);

	UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//碰完后我打牌
	UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
	changeState(new PlayerTwoState());								//碰完后我打牌

	refrishCardPos();		//重新显示牌面
	_eventDispatcher->dispatchCustomEvent(SHOW_PENGCARD);	//显示层显示碰的牌

	//测试
	if (m_newCard.m_Type == 0)
	{
		GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 1); //修改胡数
		refreshHuShu();		//刷新胡数
	}
	if (m_newCard.m_Type == 1)
	{
		GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3); //修改胡数
		refreshHuShu();		//刷新胡数
	}
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

void GameLayer::doChiACard()
{
	/*
	int num = UserDefault::getInstance()->getIntegerForKey(CHIWHAT,0);

	t_Player[2].doChi1_2_3(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChi2_7_10(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChiA_B_C(m_newCard.m_Type, m_newCard.m_Value, num);
	t_Player[2].doChiA_A_a(m_newCard.m_Type, m_newCard.m_Value);
	t_Player[2].doChiA_A_a_a(m_newCard.m_Type, m_newCard.m_Value);
	*/
}

void GameLayer::showChiCardLayer()
{
	//显示吃的牌层
	auto chiCardLayer = ChiCardLayer::create(this);
	chiCardLayer->setName(CHICARDLAYER);
	addChild(chiCardLayer);
}

void GameLayer::addEffect(string str)
{
	auto image = Sprite::create(str);
	if (image)
	{
		image->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
		addChild(image,2);
		image->setScale(0.5f);
		
		auto scaleTo = ScaleTo::create(0.5f, 1.2f);
		auto ease = EaseSineOut::create(scaleTo);
		auto delayTime = DelayTime::create(0.5f);
		auto fadeOut = FadeOut::create(0.5f);

		auto spa = Spawn::create(fadeOut, ease, nullptr);
		auto callFun = CallFunc::create([=]{
			image->removeFromParent();
		});

		auto seq = Sequence::create(ease, delayTime, spa, callFun, nullptr);
		image->runAction(seq);
		
	}
}

bool GameLayer::checkSaochuan()
{
	//自己摸的牌 检测
	bool isAction = false;
	if (t_Player[2].checkSaoChuanACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"起手牌扫穿！！！"));
		t_Player[2].doSaoChuanACard(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

		//特效
		string str = "effect/saochuan.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCHUANCARD);
		isAction = true;

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫穿完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
		setActionVisible(true);
	}

	if (t_Player[2].checkSao_saoChuanACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫的扫穿！！！"));
		t_Player[2].doSao_SaoChuan(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

				//特效
		string str = "effect/saochuan.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCHUANCARD);
		isAction = true;

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫穿完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
		setActionVisible(true);
	}

	if (isAction)
	{
		//测试自己摸的牌 检测 扫穿
		if (m_newCard.m_Type == 0)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 9); //修改胡数
			refreshHuShu();		//刷新胡数
		}
		if (m_newCard.m_Type == 1)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 12); //修改胡数
			refreshHuShu();		//刷新胡数
		}

		return true;
	}
	return false;
}

bool GameLayer::checkSao()
{
	if (t_Player[2].checkSaoACard(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫！！！"));
		t_Player[2].doSaoACard(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

		//特效
		string str = "effect/sao.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_SAOCARD);

		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//扫完后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

		changeState(new PlayerTwoState());
		setActionVisible(true);

		//扫
		if (m_newCard.m_Type == 0)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3); //修改胡数
			refreshHuShu();		//刷新胡数
		}
		if (m_newCard.m_Type == 1)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6); //修改胡数
			refreshHuShu();		//刷新胡数
		}

		return true;
	}
	return false;
}

void GameLayer::chooseLayerClose()
{
	//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"！！"));
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
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"起手牌开舵！！！"));
		t_Player[2].doKaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

				//特效
		string str = "effect/kaiduo.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}

	if (t_Player[2].checkKaiDuo_Sao(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫的开舵！！！"));
		t_Player[2].doSao_KaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

				//特效
		string str = "effect/kaiduo.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}

	if (t_Player[2].checkKaiDuo_peng(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"碰的开舵！！！"));
		t_Player[2].doPeng_kaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

				//特效
		string str = "effect/kaiduo.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);
		isAction = true;
		UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//开舵后我打牌
		UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌
		changeState(new PlayerTwoState());
	}
	if (isAction)
	{
		//测试别人摸的牌，我检测 开舵
		if (m_newCard.m_Type == 0)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6); //修改胡数
			refreshHuShu();		//刷新胡数
		}
		if (m_newCard.m_Type == 1)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 9); //修改胡数
			refreshHuShu();		//刷新胡数
		}
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
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"!!开舵的重舵！！！"));
		t_Player[2].doChongDuo_kaiDuo(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

				//特效
		string str = "effect/chongduo.png";
		addEffect(str);

		_eventDispatcher->dispatchCustomEvent(SHOW_KAIDUOCARD);

		isAction = true;
		changeState(new PlayerOneState());

		if (m_newCard.m_Type == 0)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6); //修改胡数
			refreshHuShu();		//刷新胡数
		}
		if (m_newCard.m_Type == 1)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 9); //修改胡数
			refreshHuShu();		//刷新胡数
		}
	}
	//扫穿还没处理好
	if (t_Player[2].checkChongDuo_saoChuan(m_newCard.m_Type, m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"扫穿的重舵！！！"));
		t_Player[2].doChongDuo_saoChuan(m_newCard.m_Type, m_newCard.m_Value);
		refrishCardPos();

		//特效
		string str = "effect/chongduo.png";
		addEffect(str);

		isAction = true;
		changeState(new PlayerOneState());

		if (m_newCard.m_Type == 0)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 9); //修改胡数
			refreshHuShu();		//刷新胡数
		}
		if (m_newCard.m_Type == 1)
		{
			GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 12); //修改胡数
			refreshHuShu();		//刷新胡数
		}
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
				/*m_line = DrawNode::create();
				addChild(m_line);
				if (m_line)
				{
					m_line->drawSegment(Point(0, VISIBLESIZE.height / 2 - 50), Point(VISIBLESIZE.width, VISIBLESIZE.height / 2 - 50), 2, Color4F(0.5, 0.5, 0.1, 1));
				}*/
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
	/*if (m_line)
	{
		m_line->clear();
	}*/

	if (!m_TempMoveCard)
	{
		return;
	}
	m_TempMoveCard->setLocalZOrder(CARD_ZORDER_1);

	if (touch->getLocation().y > VISIBLESIZE.height / 2 - 50)
	{
			//打牌不摸牌
			_eventDispatcher->removeCustomEventListeners(HIDE_TIMECOUNT);
			int _type = m_TempMoveCard->getCardData()->m_Type;
			int _value = m_TempMoveCard->getCardData()->m_Value;

			if (_type == 0)
			{
				cout << "打了张：小" << _value << endl;
				//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张小") + Value(_value).asString());
			}
			else
			{
				cout << "打了张：大" << _value << endl;
				//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张大") + Value(_value).asString());
			}

			t_Player[2].delACard(_type, _value);

			refrishCardPos();

			PopPai = t_Player[2].popCard;
			_eventDispatcher->dispatchCustomEvent(CREATE_CARD);
			UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, true);
			UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, true);	//打完牌后我可以摸牌
			UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, false);	//打完牌后我不能出牌
			changeState(new PlayerOneState());
			setActionVisible(false);
	}
	else
	{
		auto moveTo = MoveTo::create(0.2, m_OldPos);
		auto ease = EaseSineOut::create(moveTo);
		m_TempMoveCard->runAction(ease);
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
		back_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 1, Vec2(-135, -back_btn->getContentSize().height / 2 - 5)));
		back_btn->addClickEventListener([this](Ref*){
			Director::getInstance()->replaceScene(WelcomeScene::createScene());
			GetScore::getInstance()->setScore(0);
		});
	}

	//开始游戏
	auto startButton = Button::create("CloseSelected.png", "CloseNormal.png");
	startButton->setPosition(CommonFunction::getVisibleAchor(1,0.2,this,Vec2(-50,50)));
	addChild(startButton);
	if (startButton && m_isStartGame)
	{
		startButton->setVisible(false);
		startButton->addClickEventListener(CC_CALLBACK_1(GameLayer::startCallBack, this));
	}
	else
	{
		startButton->addClickEventListener(CC_CALLBACK_1(GameLayer::overCallBack, this));
	}
	//倍率
	auto beilv_str = CommonFunction::WStrToUTF8(L"倍率  ");
	m_beilv = Label::createWithTTF(beilv_str + Value(_beilv).asString(), "fonts/Roboto-Medium.ttf", 20);
	if (m_beilv)
	{
		addChild(m_beilv);
		m_beilv->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(-5, -m_beilv->getContentSize().height - 6)));
	}
	//底牌
	auto dipai_str = CommonFunction::WStrToUTF8(L"底牌:20");
	m_dipai = Label::createWithTTF(dipai_str, "fonts/Roboto-Medium.ttf", 24);
	if (m_dipai)
	{
		addChild(m_dipai);
		m_dipai->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(80, -75)));
	}

	//机器人
	auto robot_btn = Button::create("robot.png");
	if (robot_btn)
	{
		addChild(robot_btn);
		robot_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(130,  -robot_btn->getContentSize().height / 2 -5)));
		robot_btn->addClickEventListener([](Ref*){std::cout << "托管" << std::endl;; });
	}

	//添加胡数
	Label* hushu = Label::createWithTTF(CommonFunction::WStrToUTF8(L"胡数:"), "fonts/Roboto-Medium.ttf", 20);
	hushu->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, Vec2(-30, -100)));
	addChild(hushu);
	log("%d", GetScore::getInstance()->getScore());

	score = Label::createWithTTF(Value(GetScore::getInstance()->getScore()).asString(), "fonts/arial.ttf", 25);
	score->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, Vec2(10, -100)));
	addChild(score);
}

void GameLayer::startCallBack(Ref* ref)
{
	UserDefault::getInstance()->setBoolForKey(ISFIRSTPLAY, false);
	_eventDispatcher->dispatchCustomEvent(PLAYERBLINK_2);
	xipai();
	creatAction();
}

void GameLayer::overCallBack(Ref* ref)
{

}

void GameLayer::getANewCard()
{
	CardEx t_newCard = t_ZPManage.GetAPai();

	if (t_newCard.m_CardNum <= 0)
	{
			//特效
		string str = "huangzhuang.png";
		addEffect(str);
		
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

		auto dipai_str = CommonFunction::WStrToUTF8(L"底牌:");
		if (m_dipai)
		{
			m_dipai->setString(dipai_str + Value(t_newCard.m_CardNum).asString());
		}
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

	//CardEx t_pai = t_ZPManage.GetAPai();	//档低牌
	//t_Player[2].addCard(t_pai.m_NewCard.m_Type, t_pai.m_NewCard.m_Value);

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

	float _width = m_CardList.at(0)->getContentSize().width;
	int _leftSize = 21 - m_CardList.size();

	if (!m_CardList.empty())
	{
		for (int i = 0; i < m_CardList.size();++i)
		{
			if (m_CardList.at(i))
			{
				m_CardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftButtom, 0, Vec2(45 * i + 180 + _leftSize * ( 45 /2), 95)));
				//m_CardList.at(i)->setVisible(false);
				m_CardList.at(i)->setCardOpacity(0);
			}
		}
	}

	setCardState();
}

void GameLayer::setVisibleOneByOne()
{
	 if (_cardCount < m_CardList.size())
	{
		 if (m_CardList.at(_cardCount))
		{
			 for (auto &_child : m_CardList.at(_cardCount)->getChildren())
			 {
				 _child->runAction(FadeIn::create(0.2));
			 }
		}
		 _cardCount++;
	}
	else
	{
		_needVisible = false;
		_cardCount = 0;
	}
}

void GameLayer::refrishCardPos()
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

	float _width = m_CardList.at(0)->getContentSize().width;
	int _leftSize = 21 - m_CardList.size();

	if (!m_CardList.empty())
	{
		for (int i = 0; i < m_CardList.size(); ++i)
		{
			if (m_CardList.at(i))
			{
				m_CardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftButtom, 0, Vec2(45 * i + 180 + _leftSize * (45 / 2), 95)));
			}
		}
	}
	setCardState();
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

void GameLayer::creatAction()
{
	/* _line = DrawNode::create();
	 addChild(_line);
	 if (_line)
	{
		 _line->drawSegment(Point(0, VISIBLESIZE.height / 2 - 50), Point(VISIBLESIZE.width, VISIBLESIZE.height / 2 - 50), 2, Color4F(0, 1, 0, 1));
	}*/
	 _note = Label::createWithTTF(CommonFunction::WStrToUTF8(L"滑动出牌"), "fonts/Roboto-Medium.ttf", 30);
	 _note->setPosition(Vec2(850, 320));
	 addChild(_note);

	 _hand = Sprite::create("finger.png");
	 if (_hand)
	{
		 addChild(_hand);
		 _hand->setAnchorPoint(Vec2(0, 0));
		 _hand->setPosition(Vec2(850, 150)); //开始位置
		 auto delay = DelayTime::create(0.1);
		 auto callf = CallFunc::create([=]{
			 _hand->setPosition(Vec2(850, 150));
		 });
		MoveTo* move = MoveTo::create(0.8, Vec2(930, 300));
		auto ease = EaseSineOut::create(move);
		_hand->runAction(RepeatForever::create(Sequence::create(delay, ease, callf, ease, nullptr)));
	}
}

void GameLayer::setActionVisible(bool _visible)
{
	if (_visible)
	{
		//if (_line && _note && _hand)
		if ( _note && _hand)
		{
			//_line->setVisible(true);
			_note->setVisible(true);
			_hand->setVisible(true);
		}
	}
	else
	{
		//if (_line && _note && _hand)
		if ( _note && _hand)
		{
			//_line->setVisible(false);
			_note->setVisible(false);
			_hand->setVisible(false);
		}
	}
}

//添加刷新胡数label
void GameLayer::refreshHuShu()
{
	if (score)
	{
		score->setString(Value(GetScore::getInstance()->getScore()).asString());
	}
}
#include "GameLayer.h"
#include "utils/Constant.h"
#include "CCPlatformConfig.h"
#include "utils/CommonFunction.h"
#include "layerUtils/Base.h"
#include "TestPopLayer.h"
#include "utils/Constant.h"
#include "layerUtils/ToastLayer/ToastManger.h"
#include "ShowLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else

#include <pthread.h>
#include <unistd.h>

#endif

GameLayer::GameLayer():
m_isStartGame(true),
m_line(nullptr),
m_TempMoveCard(nullptr)
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();

	initUI();

	addChild(ShowLayer::create(this));

	return true;
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
	m_line = DrawNode::create();
	addChild(m_line);
	if (m_line)
	{
		m_line->drawSegment(Point(0, VISIBLESIZE.height / 2 - 50), Point(VISIBLESIZE.width, VISIBLESIZE.height / 2 - 50), 2, Color4F(0, 1, 0, 1));
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
			cout << "T:" << _card->getCardData()->m_Type << "V:" << _card->getCardData()->m_Value << endl;

			return true;
		}
	}

	return true;
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

		logAllCard();

		createMyCardWall();
	
		PopPai[2] = t_Player[2].popCard;
		_eventDispatcher->dispatchCustomEvent(CREATE_CARD);
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
	auto bg_sp = Sprite::create("zhuomian.png");
	addChild(bg_sp);

	if (bg_sp)
	{
		float w = bg_sp->getContentSize().width;
		float h = bg_sp->getContentSize().height;

		bg_sp->setScale(VISIBLESIZE.width / w, VISIBLESIZE.height / h);

		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,this,Vec2::ZERO));
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
	xipai();
}

void GameLayer::overCallBack(Ref* ref)
{

}

void GameLayer::xipai()
{
	t_ZPManage.InitPai();

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
	cout << "上家的牌（0）" << endl;
	t_Player[0].logAllCard();
	cout << "下家的牌（1）" << endl;
	t_Player[1].logAllCard();
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
				_card->setPosition(Point(x + 35 * count, y));
				m_CardList.pushBack(_card);
			}
			count++;
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
				_card->setPosition(Point(x + 35 * count, y));
				m_CardList.pushBack(_card);
			}
			count++;
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
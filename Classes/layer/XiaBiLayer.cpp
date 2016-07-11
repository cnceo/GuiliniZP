#include "XiaBiLayer.h"
#include "GameLayer.h"
#include "utils/CommonFunction.h"

#define MYPLAYER _ChiLayer->_gameLayer->t_Player[2]

XiaBiLayer::XiaBiLayer() :
_ChiLayer(nullptr)
{

}

XiaBiLayer::~XiaBiLayer()
{

}

void XiaBiLayer::onEnter()
{
	Layer::onEnter();

	auto listenerEvent = EventListenerTouchOneByOne::create();
	//listenerEvent->setSwallowTouches(true);
	listenerEvent->onTouchBegan = CC_CALLBACK_2(XiaBiLayer::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(XiaBiLayer::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(XiaBiLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);
}

bool XiaBiLayer::init(ChiCardLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	_ChiLayer = _layer;

	initData();
	initUI();
	checkXiabi();
	return true;
}

XiaBiLayer* XiaBiLayer::create(ChiCardLayer* _layer)
{
	XiaBiLayer *pRet = new(std::nothrow) XiaBiLayer();
	if (pRet && pRet->init(_layer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool XiaBiLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return false;
}

void XiaBiLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void XiaBiLayer::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void XiaBiLayer::initData()
{

}

void XiaBiLayer::initUI()
{
	/*auto bg_sp = Sprite::create("chi_kuang.png");
	if (bg_sp)
	{
		bg_sp->setColor(Color3B::MAGENTA);
		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(270, -93)));
	}*/
}

void XiaBiLayer::checkXiabi()
{
	//if (m_allChiCardVec.empty())return;


	/*
	Vector<SmallCard*> tmpVec_1;
	std::vector<int >	tmp_1;
	tmpVec_1.clear();
	tmp_1.clear();

	for (int i = 0; i < m_allChiCardVec.size(); i++)
	{
		int _index = m_allChiCardVec.at(i)->getTag() / 3;
		if (_index == 0)
		{
			tmpVec_1.pushBack(m_allChiCardVec.at(i));
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_gameLayer->t_Player[2].m_MyCard[i].empty())
		{
			for (auto iter = _gameLayer->t_Player[2].m_MyCard[i].begin(); iter != _gameLayer->t_Player[2].m_MyCard[i].end(); iter++)
			{
				if (*iter == _gameLayer->m_newCard.m_Value)
				{
					tmp_1 = _gameLayer->t_Player[2].m_MyCard[i];
					break;
				}
			}
			break;
		}
	}

	for (auto &_card : tmpVec_1)
	{
		int _chiNum = _card->getCardData().m_Value;
		for (auto iter = tmp_1.begin(); iter != tmp_1.end();)
		{
			int _handNum = *iter;
			if (_chiNum == _handNum)
			{
				tmp_1.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
	*/
}

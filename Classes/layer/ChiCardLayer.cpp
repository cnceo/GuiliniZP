#include "ChiCardLayer.h"
#include "GameLayer.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"
#include "utils/Constant.h"

ChiCardLayer::ChiCardLayer():
_gameLayer(nullptr)
{

}

ChiCardLayer::~ChiCardLayer()
{

}

ChiCardLayer* ChiCardLayer::create(GameLayer* _layer)
{
	ChiCardLayer *pRet = new(std::nothrow) ChiCardLayer(); 
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

bool ChiCardLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	_gameLayer = _layer;

	initData();
	initUI();
	return true;
}

void ChiCardLayer::onEnter()
{
	Layer::onEnter();

	auto listenerEvent = EventListenerTouchOneByOne::create();
	listenerEvent->setSwallowTouches(true);
	listenerEvent->onTouchBegan = CC_CALLBACK_2(ChiCardLayer::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(ChiCardLayer::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(ChiCardLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);
}

bool ChiCardLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ChiCardLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void ChiCardLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	std::vector <Sprite*>::iterator iter = m_tmpChiCardList.begin();
	for (; iter != m_tmpChiCardList.end(); ++iter)
	{
		Sprite* _card = static_cast<Sprite*>(*iter);
		Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

		Size s = _card->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			log("tag=%d", _card->getTag());
			//选择吃什么牌
		}
	}
}

void ChiCardLayer::initData()
{
	auto layercolor = LayerColor::create(Color4B(0, 0, 0, 150));
	addChild(layercolor, -1);

	auto closeBtn = Button::create("guo.png");

	if (closeBtn)
	{
		addChild(closeBtn);
		closeBtn->setScale(0.5f);
		closeBtn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,Vec2(340,155)));
		closeBtn->addClickEventListener([=](Ref* pSender){
			if (getParent())
			{
				removeFromParent();
			}
		});
	}
}

void ChiCardLayer::initUI()
{
	if (m_tmpChiCardList.size()>0)
	{
		for (auto &_card : m_tmpChiCardList)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpChiCardList.clear();
	}

	for (int i = 0; i < _gameLayer->m_TempChiCard.size();i++)
	{
		auto _card_1 = createSmallCardSprite(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value1);
		auto _card_2 = createSmallCardSprite(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value2);
		auto _card_3 = createSmallCardSprite(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value3);

		if (_card_1 && _card_2 && _card_3)
		{ 
			addChild(_card_1);
			addChild(_card_2);
			addChild(_card_3);

			m_tmpChiCardList.pushBack(_card_1);
			m_tmpChiCardList.pushBack(_card_2);
			m_tmpChiCardList.pushBack(_card_3);
		}
	}

	for (int i = 0; i < _gameLayer->m_TempChiList.size(); i++)
	{
		auto _card = createSmallCardSprite(_gameLayer->m_TempChiList[i].m_Type, _gameLayer->m_TempChiList[i].m_Value);
		if (_card)
		{
			addChild(_card);
			m_tmpChiCardList.pushBack(_card);
		}
	}

	if (m_tmpChiCardList.size()>0)
	{
		for (int i = 0; i < m_tmpChiCardList.size(); i++)
		{
			int _height = m_tmpChiCardList.at(i)->getContentSize().height;
			//m_tmpChiCardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i % 3)*(_height)+100, i / 3 * (_height - 73))));
			m_tmpChiCardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height+15)+150, i % 3 * (_height - 83)+100)));
			m_tmpChiCardList.at(i)->setTag(i);
		}
	}
}

Sprite* ChiCardLayer::createSmallCardSprite(int p_Type, int p_Value)
{
	Sprite* card = nullptr;
	if (p_Type == 0)
	{
		card = Sprite::create(StringUtils::format("xiaopai_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		card = Sprite::create(StringUtils::format("xiaopai_d%0d.png", p_Value));
	}

	if (card)
	{
		return card;
	}
	return nullptr;
}

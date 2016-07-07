#include "ChiCardLayer.h"
#include "GameLayer.h"
#include "utils/CommonFunction.h"
#include "ui/UIButton.h"
#include "utils/Constant.h"
#include "utils/GetScore.h"
#include "utils/GetLayer.h"
#include "layerUtils/ToastLayer/ToastManger.h"

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
	if (!m_tmpChiCardList.empty())
	{
		int _cardTag_0 = -1;
		for (auto iter = m_tmpChiCardList.begin(); iter != m_tmpChiCardList.end(); ++iter)
		{
			SmallCard* _card = static_cast<SmallCard*>(*iter);
			Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

			Size s = _card->getContentSize();
			Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("---------tag=%d", _card->getTag());
				//log("tag/3==%d",_card->getTag() / 3);
				//log("T:%d,V:%d", _card->getCardData().m_Type, _card->getCardData().m_Value);
				_cardTag_0 = _card->getTag() / 3;
			}
		}

		if (_cardTag_0 >= 0)
		{
			int record = -1;
			//先把新牌添加到手里，再删除
			_gameLayer->t_Player[2].addCard(_gameLayer->m_newCard.m_Type, _gameLayer->m_newCard.m_Value);
			//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我吃牌！"));
			GetLayer::getInstance()->getgameLayer()->addEffect("effect/chi.png");
			for (auto &_scard : m_tmpChiCardList)
			{
				if (_scard->getTag() / 3 == _cardTag_0)
				{
					log("___T:%d,___V:%d", _scard->getCardData().m_Type, _scard->getCardData().m_Value);
					if (_gameLayer)
					{
						int _type = _scard->getCardData().m_Type;
						int _value = _scard->getCardData().m_Value;
						_gameLayer->t_Player[2].m_ChiCardVec[_type].push_back(_value);			//连续的
						//log("___size =%d", _gameLayer->t_Player[2].m_ChiCardVec[_type].size());
						_gameLayer->t_Player[2].delACard(_type, _value);
						//修改123的胡数
						if (_value == 1)
						{
							if (_type == 0)
							{
								GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3);
								GetLayer::getInstance()->getgameLayer()->refreshHuShu();
							}
							if (_type == 1)
							{
								GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6);
								GetLayer::getInstance()->getgameLayer()->refreshHuShu();
							}
						}

						//给2，7，10记录胡数
						if (record == -1)
						{
							record = _value;
							log("***t = %d", record);
						}
						if (record == 2 || record == 7 || record == 10)
						{
							log("**2*t = %d", record);
							if (record == 2 && (_value == 7 || _value == 10))
							{
								log("record == 2,%d", _value);
								if (_type == 0)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								if (_type == 1)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								record = 0;
							}
							if (record == 7 && (_value == 2 || _value == 10))
							{
								log("record == 7,%d", _value);
								if (_type == 0)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								if (_type == 1)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								record = 0;
							}
							if (record == 10 && (_value == 7 || _value == 12))
							{
								log("record == 10,%d", _value);
								if (_type == 0)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 3);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								if (_type == 1)
								{
									GetScore::getInstance()->setScore(GetScore::getInstance()->getScore() + 6);
									GetLayer::getInstance()->getgameLayer()->refreshHuShu();
								}
								record = 0;
							}
						}
					}
				}
			}
			_gameLayer->refrishCardPos();
			_eventDispatcher->dispatchCustomEvent(SHOW_CHICARD);

			if (getParent())
			{
				_gameLayer->removeChildByName(CHOOSELAYER);

				UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);
				UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//吃完后我打牌
				UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

				_gameLayer->chooseLayerClose();
				removeFromParent();
			}
		}
	}
	
	if (!m_tmpChiCardVec.empty())
	{
		int _cardTag_1 = -1;
		for (auto iter = m_tmpChiCardVec.begin(); iter != m_tmpChiCardVec.end(); ++iter)
		{
			SmallCard* _card = static_cast<SmallCard*>(*iter);
			Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

			Size s = _card->getContentSize();
			Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("tag=%d---------", _card->getTag());
				//log("tag/3==%d",_card->getTag() / 3);
				//log("T:%d,V:%d", _card->getCardData().m_Type, _card->getCardData().m_Value);
				_cardTag_1 = _card->getTag() / 3;
			}
		}

		if (_cardTag_1 >= 0)
		{
			_gameLayer->t_Player[2].addCard(_gameLayer->m_newCard.m_Type, _gameLayer->m_newCard.m_Value);
			//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我吃牌！"));
			GetLayer::getInstance()->getgameLayer()->addEffect("effect/chi.png");

			for (auto &_scard : m_tmpChiCardVec)
			{
				if (_scard->getTag() / 3 == _cardTag_1)
				{
					//log("T:___%d,V___:%d", _scard->getCardData().m_Type, _scard->getCardData().m_Value);
					if (_gameLayer)
					{
						int _type = _scard->getCardData().m_Type;
						int _value = _scard->getCardData().m_Value;
						_gameLayer->t_Player[2].m_ChiCardList[_type].push_back(_value);
						//log("type__=%d,size___ =%d", _type, _gameLayer->t_Player[2].m_ChiCardList[_type].size());	//A_A_a_a
						_gameLayer->t_Player[2].delACard(_type, _value);
					}
				}
			}
			_gameLayer->refrishCardPos();
			_eventDispatcher->dispatchCustomEvent(SHOW_CHICARD);
			
			if (getParent())
			{
				_gameLayer->removeChildByName(CHOOSELAYER);
				UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);
				UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//吃完后我打牌
				UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

				_gameLayer->chooseLayerClose();
				removeFromParent();
			}
		}
	}
}

/*
void ChiCardLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!m_tmpChiCardList.empty())
	{
		int _cardTag_0 = -1;
		for (auto iter = m_tmpChiCardList.begin(); iter != m_tmpChiCardList.end(); ++iter)
		{
			SmallCard* _card = static_cast<SmallCard*>(*iter);
			Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

			Size s = _card->getContentSize();
			Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("---------tag=%d", _card->getTag());
				//log("tag/3==%d",_card->getTag() / 3);
				//log("T:%d,V:%d", _card->getCardData().m_Type, _card->getCardData().m_Value);
				_cardTag_0 = _card->getTag() / 3;
			}
		}

		if (_cardTag_0 >= 0)
		{
			int record = -1;
			//先把新牌添加到手里，再删除
			_gameLayer->t_Player[2].addCard(_gameLayer->m_newCard.m_Type, _gameLayer->m_newCard.m_Value);
			//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我吃牌！"));
			GetLayer::getInstance()->getgameLayer()->addEffect("effect/chi.png");
			for (auto &_scard : m_tmpChiCardList)
			{
				if (_scard->getTag() / 3 == _cardTag_0)
				{
					log("___T:%d,___V:%d", _scard->getCardData().m_Type, _scard->getCardData().m_Value);
					if (_gameLayer)
					{
						int _type = _scard->getCardData().m_Type;
						int _value = _scard->getCardData().m_Value;
						_gameLayer->t_Player[2].m_ChiCardVec[_type].push_back(_value);			//连续的
						//log("___size =%d", _gameLayer->t_Player[2].m_ChiCardVec[_type].size());
						_gameLayer->t_Player[2].delACard(_type, _value);
					}
				}
			}
			_gameLayer->refrishCardPos();
			_eventDispatcher->dispatchCustomEvent(SHOW_CHICARD);

			if (getParent())
			{
				_gameLayer->removeChildByName(CHOOSELAYER);

				UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);
				UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//吃完后我打牌
				UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

				_gameLayer->chooseLayerClose();
				removeFromParent();
			}
		}
	}

	if (!m_tmpChiCardVec.empty())
	{
		int _cardTag_1 = -1;
		for (auto iter = m_tmpChiCardVec.begin(); iter != m_tmpChiCardVec.end(); ++iter)
		{
			SmallCard* _card = static_cast<SmallCard*>(*iter);
			Point locationInNode = _card->convertToNodeSpace(touch->getLocation());

			Size s = _card->getContentSize();
			Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("tag=%d---------", _card->getTag());
				//log("tag/3==%d",_card->getTag() / 3);
				//log("T:%d,V:%d", _card->getCardData().m_Type, _card->getCardData().m_Value);
				_cardTag_1 = _card->getTag() / 3;
			}
		}

		if (_cardTag_1 >= 0)
		{
			_gameLayer->t_Player[2].addCard(_gameLayer->m_newCard.m_Type, _gameLayer->m_newCard.m_Value);
			//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我吃牌！"));
			GetLayer::getInstance()->getgameLayer()->addEffect("effect/chi.png");

			for (auto &_scard : m_tmpChiCardVec)
			{
				if (_scard->getTag() / 3 == _cardTag_1)
				{
					//log("T:___%d,V___:%d", _scard->getCardData().m_Type, _scard->getCardData().m_Value);
					if (_gameLayer)
					{
						int _type = _scard->getCardData().m_Type;
						int _value = _scard->getCardData().m_Value;
						_gameLayer->t_Player[2].m_ChiCardList[_type].push_back(_value);
						//log("type__=%d,size___ =%d", _type, _gameLayer->t_Player[2].m_ChiCardList[_type].size());	//A_A_a_a
						_gameLayer->t_Player[2].delACard(_type, _value);
					}
				}
			}
			_gameLayer->refrishCardPos();
			_eventDispatcher->dispatchCustomEvent(SHOW_CHICARD);

			if (getParent())
			{
				_gameLayer->removeChildByName(CHOOSELAYER);
				UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);
				UserDefault::getInstance()->setBoolForKey(ISGETORPLAY, false);	//吃完后我打牌
				UserDefault::getInstance()->setBoolForKey(ISPLAYCAED, true);	//可以打牌

				_gameLayer->chooseLayerClose();
				removeFromParent();
			}
		}
	}
}
*/
void ChiCardLayer::initData()
{
	auto layercolor = LayerColor::create(Color4B(0, 0, 0, 150));
	addChild(layercolor, -1);

	auto closeBtn = Button::create("guo.png");

	if (closeBtn)
	{
		closeBtn->setScale(0.8);
		addChild(closeBtn);
		closeBtn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,Vec2(360,190)));
		closeBtn->addClickEventListener([=](Ref* pSender){
			if (getParent())
			{
				removeFromParent();
			}
		});
	}

	auto bg_sp = Sprite::create("chi_kuang.png");
	if (bg_sp)
	{
		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(270, 60)));
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

	if (m_tmpChiCardVec.size()>0)
	{
		for (auto &_card : m_tmpChiCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpChiCardVec.clear();
	}

	if (!m_allChiCardVec.empty())
	{
		m_allChiCardVec.clear();
	}

	for (int i = 0; i < _gameLayer->m_TempChiCard.size(); i++)
	{
		auto _card_1 = SmallCard::create(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value1);
		auto _card_2 = SmallCard::create(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value2);
		auto _card_3 = SmallCard::create(_gameLayer->m_TempChiCard[i].m_Type, _gameLayer->m_TempChiCard[i].m_Value3);

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
		auto _card = SmallCard::create(_gameLayer->m_TempChiList[i].m_Type, _gameLayer->m_TempChiList[i].m_Value);
		if (_card)
		{
			addChild(_card);
			m_tmpChiCardVec.pushBack(_card);
		}
	}

	m_allChiCardVec.pushBack(m_tmpChiCardList);
	m_allChiCardVec.pushBack(m_tmpChiCardVec);

	if (!m_allChiCardVec.empty())
	{
		for (int i = 0; i < m_allChiCardVec.size();i++)
		{
			int _height = m_allChiCardVec.at(i)->getContentSize().height;
			m_allChiCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height + 15) + 150, i % 3 * (_height - 83) + 100)));
			m_allChiCardVec.at(i)->setTag(i);
		}
	}

	checkXiabi();
}

void ChiCardLayer::checkXiabi()
{
	/*if (m_allChiCardVec.empty())return;

	for (int i = 0; i < m_allChiCardVec.size();i++)
	{
		int _index = m_allChiCardVec.at(i)->getTag() / 3;
	}*/
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


//--------------------SmallCard类--------------------------//

SmallCard* SmallCard::create(int p_Type, int p_Value)
{
	SmallCard *pRet = new(std::nothrow) SmallCard();
	if (pRet && pRet->init(p_Type,p_Value))
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
	return nullptr;
}

bool SmallCard::init(int p_Type, int p_Value)
{
	if (!Node::init())
	{
		return false;
	}

	CardData _data = { p_Type ,p_Value};
	setCardData(_data);
	
	Sprite* _card = nullptr;
	if (p_Type == 0)
	{
		_card = Sprite::create(StringUtils::format("xiaopai_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		_card = Sprite::create(StringUtils::format("xiaopai_d%0d.png", p_Value));
	}

	if (_card)
	{
		addChild(_card);
		setContentSize(_card->getContentSize());
	}

	return true;
}

void SmallCard::setCardData(CardData _data)
{
	m_cardData = _data;
}

CardData SmallCard::getCardData()
{
	return m_cardData;
}
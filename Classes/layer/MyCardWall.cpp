#include "MyCardWall.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "layerUtils/ToastLayer/ToastManger.h"

MyCardWall::MyCardWall():
m_GameLayer(nullptr),
m_TempMoveCard(nullptr)
{

}

MyCardWall::~MyCardWall()
{

}

MyCardWall* MyCardWall::create(GameLayer* _layer)
{
	MyCardWall* ret = new MyCardWall();
	if (ret && ret->init(_layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MyCardWall::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	m_GameLayer = _layer;
	initData();
	initUI();
	setSortState();
	createCardWall();
	return true;
}

void MyCardWall::onEnter()
{
	Layer::onEnter();

	auto listenerEvent = EventListenerTouchOneByOne::create();
	listenerEvent->onTouchBegan = CC_CALLBACK_2(MyCardWall::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(MyCardWall::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(MyCardWall::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);
}

void MyCardWall::initData()
{

}

void MyCardWall::initUI()
{

}

void MyCardWall::removeCardWall()
{
	for (auto it = _cardList.begin(); it != _cardList.end(); ++it)
	{
		if (*it && (*it)->getParent())
		{
			(*it)->removeFromParent();
		}
	}
	_cardList.clear();
}

void MyCardWall::createCardWall()
{
	removeCardWall();

	float x = 200;
	float y = 110;
	int count = 0;

	if (m_GameLayer->t_Player[2].m_MyCard[0].size() > 0)
	{
		for (int i = 0; i < m_GameLayer->t_Player[2].m_MyCard[0].size(); i++)
		{
			CardSprite* _card = CardSprite::create(0, m_GameLayer->t_Player[2].m_MyCard[0][i]);
			addChild(_card);
			if (_card)
			{
				_cardList.pushBack(_card);
			}
		}
	}
	if (m_GameLayer->t_Player[2].m_MyCard[1].size() > 0)
	{
		for (int i = 0; i < m_GameLayer->t_Player[2].m_MyCard[1].size(); i++)
		{
			CardSprite* _card = CardSprite::create(1, m_GameLayer->t_Player[2].m_MyCard[1][i]);
			addChild(_card);
			if (_card)
			{
				_cardList.pushBack(_card);
			}
		}
	}

	float _width = _cardList.at(0)->getContentSize().width;
	int _leftSize = 21 - _cardList.size();

	if (!_cardList.empty())
	{
		for (int i = 0; i < _cardList.size(); ++i)
		{
			_cardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, 0, Vec2(45 * i + 180 + _leftSize * (45 / 2), 0)));
		}
		//int _middle = _cardList.size() / 2;
		//_cardList.at(_middle)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 30)));
	}

	setSortState();
	setCardState();
	//refrishCardPos();	//位置
}

bool MyCardWall::onTouchBegan(Touch *touch, Event *unused_event)
{

	for (auto iter = _cardList.begin(); iter != _cardList.end(); ++iter)
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

			if (_card->getsortState() == CardSprite::SortState::FOUR_CARD)
			{
				log("FOUR_CARD");
			}
			else if (_card->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
			{
				log("THREE_SAME_CARD");
			}
			else if (_card->getsortState() == CardSprite::SortState::ONE_CARD)
			{
				log("ONE_CARD");
			}

			if (_card->getState() == CardSprite::CardState::ONTouch)
			{
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

void MyCardWall::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (m_TempMoveCard)
	{
		m_TempMoveCard->setPosition(touch->getLocation());
	}
}

void MyCardWall::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!m_TempMoveCard)
	{
		return;
	}
	if (touch->getLocation().y > VISIBLESIZE.height / 2 + 150)
	{
		int _type = m_TempMoveCard->getCardData()->m_Type;
		int _value = m_TempMoveCard->getCardData()->m_Value;

		if (_type == 0)
		{
			cout << "打了张：小" << _value << endl;
			ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张小") + Value(_value).asString());
		}
		else
		{
			cout << "打了张：大" << _value << endl;
			ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"我打了张大") + Value(_value).asString());
		}

		m_GameLayer->t_Player[2].delACard(_type, _value);

		createCardWall();
	}
	else
	{
		m_TempMoveCard->setLocalZOrder(CARD_ZORDER_1);
		auto moveTo = MoveTo::create(0.2, m_OldPos);
		m_TempMoveCard->runAction(moveTo);
	}

	if (m_TempMoveCard)
	{
		m_TempMoveCard = nullptr;
	}
}

void MyCardWall::setCardState()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _temp_0;

	for (auto& _card : _cardList)
	{
		_tempList.push_back(_card);
	}

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : _cardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 0 && _type == 0)
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

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : _cardList)
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
		for (auto& _card : _cardList)
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

void MyCardWall::setSortState()
{
	check_Four_Card();
	check_Three_Same_Card();
	check_Three_Diff_Card();
	check_Two_card();
	check_One_card();
}

bool MyCardWall::check_Four_Card()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _tempVec[2];

	for (auto& _card : _cardList)
	{
		_tempList.push_back(_card);
	}

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : _cardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 0 && _type == 0)
			{
				if (_tvalue == _value)
				{
					_count++;
					if (_count == 4)
					{
						_tempVec[0].push_back(_card);
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

		for (auto &_card : _cardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 1 && _type == 1)
			{
				if (_tvalue == _value)
				{
					_count++;
					if (_count == 4)
					{
						_tempVec[1].push_back(_card);
					}
				}

			}
		}
	}

	//auto Iter = std::unique(std::begin(_temp_0), std::end(_temp_0));
	//_temp_0.erase(Iter, _temp_0.end());

	for (auto &_tcard : _tempVec[0])
	{
		for (auto& _card : _cardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setsortState(CardSprite::SortState::FOUR_CARD);
					//_four_CardList[0].pushBack(_card);
				}
			}
		}
	}

	for (auto &_tcard : _tempVec[1])
	{
		for (auto& _card : _cardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setsortState(CardSprite::SortState::FOUR_CARD);
					//_four_CardList[0].pushBack(_card);
				}
			}
		}
	}
	return true;
}

bool MyCardWall::check_Three_Same_Card()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _tempVec[2];

	for (auto& _card : _cardList)
	{
		_tempList.push_back(_card);
	}

	for (auto& _tcard : _tempList)
	{
		int _ttype = _tcard->getCardData()->m_Type;
		int _tvalue = _tcard->getCardData()->m_Value;
		int _count = 0;

		for (auto &_card : _cardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 0 && _type == 0)
			{
				if (_tvalue == _value)
				{
					_count++;
					if (_count == 3)
					{
						_tempVec[0].push_back(_card);
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

		for (auto &_card : _cardList)
		{
			int _type = _card->getCardData()->m_Type;
			int _value = _card->getCardData()->m_Value;

			if (_ttype == 1 && _type == 1)
			{
				if (_tvalue == _value)
				{
					_count++;
					if (_count == 3)
					{
						_tempVec[1].push_back(_card);
					}
				}

			}
		}
	}

	for (auto &_tcard : _tempVec[0])
	{
		for (auto& _card : _cardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setsortState(CardSprite::SortState::THREE_SAME_CARD);
				}
			}
		}
	}

	for (auto &_tcard : _tempVec[1])
	{
		for (auto& _card : _cardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setsortState(CardSprite::SortState::THREE_SAME_CARD);
				}
			}
		}
	}
	return true;
}

bool MyCardWall::check_Three_Diff_Card()
{

	return false;
}

bool MyCardWall::check_Two_card()
{
	return false;

}

bool MyCardWall::check_One_card()
{

	return false;
}
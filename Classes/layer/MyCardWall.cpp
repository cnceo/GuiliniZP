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
	refrishCardPos();
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
			m_OldZorder = _card->getLocalZOrder();
			m_TempMoveCard->setLocalZOrder(CARD_ZORDER_2);

			if (_card->getsortState() == CardSprite::SortState::FOUR_CARD)
			{
				std::cout << "四张一样" << std::endl;
			}
			else if (_card->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
			{
				std::cout << "三张一样" << std::endl;
			}
			else if (_card->getsortState() == CardSprite::SortState::THREE_DIFF_CARD)
			{
				std::cout << "三张不同" << std::endl;

			}
			else if (_card->getsortState() == CardSprite::SortState::TWO_CARD)
			{
				std::cout << "两张一样" << std::endl;

			}
			else if (_card->getsortState() == CardSprite::SortState::ONE_CARD)
			{
				std::cout << "单张" << std::endl;

			}

			/*if (_card->getState() == CardSprite::CardState::ONTouch)
			{
				return true;
			}
			else
			{
				return false;
			}*/
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
		//m_TempMoveCard->setLocalZOrder(CARD_ZORDER_1);
		m_TempMoveCard->setLocalZOrder(m_OldZorder);
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

	_tempList.clear();
	_temp_0.clear();
}

void MyCardWall::setSortState()
{
	check_Four_Card();
	check_Three_Same_Card();
	check_Two_card();

	check_Three_Diff_Card();
	check_One_card();
}

void MyCardWall::refrishCardPos()
{
	float _width = _cardList.at(0)->getContentSize().width;
	auto _height = _cardList.at(0)->getContentSize().height;
	int _leftSize = 21 - _cardList.size();
	
	if (!_cardList.empty())
	{
		for (int i = 0; i < _cardList.size(); ++i)
		{


			//_cardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, 0, Vec2(45 * i + 180 + _leftSize * (45 / 2), 0)));
			if (_cardList.at(i)->getsortState() == CardSprite::SortState::FOUR_CARD)
			{
				//_card->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 4)*(_height - 8) + m_ThreeCardVec.back()->getPosition().x + _height, i % 4 * (_height - 70) - 30)));

				//_cardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, 0, Vec2((i / 4)*(_height - 8) + 180 + _leftSize * (45 / 2), i % 4 * (_height - 70) - 30)));
				//_cardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, 0, Vec2(45 * i + 180 + _leftSize * (45 / 2), 0)));
			}
			if (_cardList.at(i)->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
			{
				if (_cardList.at(i)->getCardData()->m_Type == 0)
				{
					if (_cardList.at(i + 1)->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
					{
						//_cardList.at(i+1)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, 0, Vec2((i / 3)*(_height - 8) + 180 + _leftSize * (45 / 2), i % 3 * (_height - 70) - 30)));
						_cardList.at(i + 1)->setPosition(Vec2(_cardList.at(i)->getPositionX() + (i / 3)*(_height - 8), _cardList.at(i)->getPositionY() + i % 3 + _height / 2));
					}
				}

			}
			if (_cardList.at(i)->getsortState() == CardSprite::SortState::TWO_CARD)
			{

			}
		}
	}
	

}

bool MyCardWall::check_Four_Card()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _tempVec[2];

	_four_CardList[0].clear();
	_four_CardList[1].clear();

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

	for (auto &_tcard : _tempVec[0])
	{
		for (auto& _card : _cardList)
		{
			if (_tcard->getCardData()->m_Type == _card->getCardData()->m_Type)
			{
				if (_tcard->getCardData()->m_Value == _card->getCardData()->m_Value)
				{
					_card->setsortState(CardSprite::SortState::FOUR_CARD);
					_four_CardList[0].pushBack(_card);
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
					_four_CardList[1].pushBack(_card);
				}
			}
		}
	}
	_tempList.clear();
	_tempVec[0].clear();
	_tempVec[1].clear();
	return true;
}

bool MyCardWall::check_Three_Same_Card()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _tempVec[2];

	_three_Same_CardList[0].clear();
	_three_Same_CardList[1].clear();

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
					if (_card->getsortState() == CardSprite::SortState::TWO_CARD ||
						_card->getsortState() == CardSprite::SortState::FOUR_CARD)
					{
						continue;
					}
						_card->setsortState(CardSprite::SortState::THREE_SAME_CARD);
						_three_Same_CardList[0].pushBack(_card);
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
					if (_card->getsortState() == CardSprite::SortState::TWO_CARD ||
						_card->getsortState() == CardSprite::SortState::FOUR_CARD)
					{
						continue;
					}
					_card->setsortState(CardSprite::SortState::THREE_SAME_CARD);
					_three_Same_CardList[1].pushBack(_card);
				}
			}
		}
	}
	_tempList.clear();
	_tempVec[0].clear();
	_tempVec[1].clear();
	return true;
}

bool MyCardWall::check_Three_Diff_Card()
{

	return false;
}

bool MyCardWall::check_Two_card()
{
	vector<CardSprite*> _tempList;
	vector<CardSprite*> _tempVec[2];

	_two_CardList[0].clear();
	_two_CardList[1].clear();

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
					if (_count == 2)
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
					if (_count == 2)
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
					if (_card->getsortState() == CardSprite::SortState::FOUR_CARD ||
						_card->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
					{
						continue;
					}
					_card->setsortState(CardSprite::SortState::TWO_CARD);
					_two_CardList[0].pushBack(_card);
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
					if (_card->getsortState() == CardSprite::SortState::FOUR_CARD ||
						_card->getsortState() == CardSprite::SortState::THREE_SAME_CARD)
					{
						continue;
					}
					_card->setsortState(CardSprite::SortState::TWO_CARD);
					_two_CardList[1].pushBack(_card);
				}
			}
		}
	}
	_tempList.clear();
	_tempVec[0].clear();
	_tempVec[1].clear();
	return false;
}

bool MyCardWall::check_One_card()
{
	_one_CardList[0].clear();
	_one_CardList[1].clear();

	for (auto &_card:_cardList)
	{
		if (_card->getCardData()->m_Type == 0)
		{
			if (_card->getsortState() == CardSprite::SortState::ONE_CARD)
			{
				_one_CardList[0].pushBack(_card);
			}
		}

		if (_card->getCardData()->m_Type == 1)
		{
			if (_card->getsortState() == CardSprite::SortState::ONE_CARD)
			{
				_one_CardList[0].pushBack(_card);
			}
		}
	}
	return false;
}
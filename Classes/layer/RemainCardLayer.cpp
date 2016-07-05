#include "RemainCardLayer.h"
#include "utils\CommonFunction.h"

RemainCardLayer::RemainCardLayer():
_gameLayer(nullptr),
count(0),
bg_left(nullptr),
bg_right(nullptr),
_needVisible(false),
_SumTime(0),
_cardCount_0(0),
_cardCount_1(1)
{
}

RemainCardLayer ::~RemainCardLayer()
{
}

RemainCardLayer* RemainCardLayer::create(GameLayer* _layer)
{
	RemainCardLayer *pRet = new(std::nothrow) RemainCardLayer();
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

bool RemainCardLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}
	_gameLayer = _layer;

	addUI();
	scheduleUpdate();
	addOtherPlayerCard();

	return true;
}

//显示其他玩家的牌
void RemainCardLayer::addOtherPlayerCard()
{
	//的到牌墙
	_gameLayer->t_Player[0].m_MyCard;
	for (int i = 0; i < 2; i++)
	{
		if (!playerCardWall_0[i].empty())
		{
			playerCardWall_0[i].clear();
		}
	}
	for (int  i= 0; i < 2; i++)
	{
		if (!playerCardWall_1[i].empty())
		{
			playerCardWall_1[i].clear();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_gameLayer->t_Player[0].m_MyCard[i].empty())
		{
			for (int j = 0; j < _gameLayer->t_Player[0].m_MyCard[i].size(); j++)
			{
				playerCardWall_0[i].push_back(_gameLayer->t_Player[0].m_MyCard[i].at(j));
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_gameLayer->t_Player[1].m_MyCard[i].empty())
		{
			for (int j = 0; j < _gameLayer->t_Player[1].m_MyCard[i].size(); j++)
			{
				playerCardWall_1[i].push_back(_gameLayer->t_Player[1].m_MyCard[i].at(j));
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!playerCardWall_0[i].empty())
		{
			for (int j = 0; j < playerCardWall_0[i].size(); j++)
			{
				auto _card = ShowCard::create(i, playerCardWall_0[i].at(j));
				if (_card)
				{
					/*addChild(_card);*/
					showCardSprite_0.push_back(_card);
				}
			}
		}

		if (!playerCardWall_1[i].empty())
		{
			for (int j = 0; j < playerCardWall_1[i].size(); j++)
			{
				auto _card = ShowCard::create(i, playerCardWall_1[i].at(j));
				/*addChild(_card);*/
				showCardSprite_1.push_back(_card);
			}
		}
	}
	//创建初始添加的位置。。。在移动到目的位置，实现动画效果
	showCardPoint();

}

void RemainCardLayer::showCardPoint()
{
	if (!showCardSprite_0.empty())
	{
		int count = 0;
		for (int i = 0; i < showCardSprite_0.size(); i++)
		{
			if ((i % 3) == 0)
			{
				count++;
			}
			int height = showCardSprite_0.at(i)->getContentSize().height;
			showCardSprite_0.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, bg_left, Vec2(15 + height*count, i % 3 * (height - 14) +85)));
			bg_left->addChild(showCardSprite_0.at(i));
			showCardSprite_0.at(i)->setOpacity(0);//
		}
		_needVisible = true;
	}
	if (!showCardSprite_1.empty())
	{
		int count = 0;
		for (int i = 0; i < showCardSprite_1.size(); i++)
		{
			if ((i%3) == 0)
			{
				count++;
			}
			int height = showCardSprite_1.at(i)->getContentSize().height;
			showCardSprite_1.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::RightMid, bg_right, Vec2(-(height*count-20), i % 3 * (height - 14) + 85)));
			bg_right->addChild(showCardSprite_1.at(i));
		}
	}
}

//add ui
void RemainCardLayer::addUI()
{
	 bg_left = Sprite::create("chi_kuang.png");
	if (bg_left)
	{
		bg_left->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(0,-20)));
		bg_left->setAnchorPoint(Vec2(0, 0.5));
		addChild(bg_left);
	}
	bg_right = Sprite::create("chi_kuang.png");
	if (bg_right)
	{
		bg_right->setPosition(CommonFunction::getVisibleAchor(Anchor::RightMid, Vec2(0, -20)));
		bg_right->setAnchorPoint(Vec2(1, 0.5));
		addChild(bg_right);
	}
}

void RemainCardLayer::update(float dt)
{
	log("update");
	if (_needVisible)
	{
		_SumTime += dt;
		if (_SumTime > 0.05)
		{
			setCardMoveEffect_0();		//一行行显示
			setCardMoveEffect_1();
			
			_SumTime = 0;
		}
	}
}

void RemainCardLayer::setCardMoveEffect_0()
{
	if (_cardCount_0 < showCardSprite_0.size())
	{
		if (showCardSprite_0.at(_cardCount_0))
		{
			for (auto &_child : showCardSprite_0.at(_cardCount_0)->getChildren())
			{
				//获得精灵当前位置，移动
				auto moveTo = MoveTo::create(0.5, Vec2(_child->getPositionX(),_child -> getPositionY()-100));
				auto fadein = FadeIn::create(0.2);
				auto delayTime = DelayTime::create(0.1);
				/*auto spawn = Spawn::create(moveTo, fadein, nullptr);*/
				auto seq = Sequence::create(fadein, delayTime,moveTo, nullptr);
			
				_child->runAction(seq);

			}
		}
		_cardCount_0++;

	}
	else
	{
		_needVisible = false;
		_cardCount_0 = 0;

	}
}

void RemainCardLayer::setCardMoveEffect_1()
{
	if (_cardCount_1 < showCardSprite_1.size())
	{
		if (showCardSprite_1.at(_cardCount_1))
		{
			for (auto &_child : showCardSprite_1.at(_cardCount_1)->getChildren())
			{
				//获得精灵当前位置，移动
				auto moveTo = MoveTo::create(0.5, Vec2(_child->getPositionX(), _child->getPositionY() - 100));
				auto fadein = FadeIn::create(0.5);
				auto delayTime = DelayTime::create(0.1);
				/*auto spawn = Spawn::create(moveTo, fadein, nullptr);*/
					auto seq = Sequence::create(fadein, delayTime,moveTo, nullptr);

					_child->runAction(seq);

			}
		}
		_cardCount_1++;
	}
	else
	{
		_needVisible = false;
		_cardCount_1 = 0;
	}
}
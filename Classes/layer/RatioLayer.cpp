#include "RatioLayer.h"
#include "utils/CommonFunction.h"
#include "ZiPai.h"
#include "utils/Constant.h"
#include "utils/GetScore.h"
#include "utils/GetLayer.h"

int RatioLayer::count = 0;

RatioLayer::RatioLayer():
_gameLayer(nullptr),
ratioNum(0),
runNumber(nullptr),
_needVisible(false),
_SumTime(0),
_cardCount(0)
{

}

RatioLayer::~RatioLayer()
{

}

RatioLayer* RatioLayer::create(GameLayer* _layer)
{
	RatioLayer *pRet = new(std::nothrow) RatioLayer();
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

bool RatioLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	scheduleUpdate();
	_gameLayer = _layer;

	AddUI();

	checkRatio();

	return true;
}

void RatioLayer:: AddUI()
{
	//创建一个番醒label
	auto layercolor = LayerColor::create(Color4B(0, 0, 0, 150));
	addChild(layercolor, -1);

	Label * label = Label::createWithTTF(CommonFunction::WStrToUTF8(L"翻醒:"), "fonts/Roboto-Medium.ttf", 30);
	if (label)
	{
		label->setPosition(CommonFunction::getVisibleAchor(0.6,0.8,Vec2(0,0)));
		addChild(label);
	}

	runNumber = RunNumLabel::create(CommonFunction::getString(0), "fonts/baishe.fnt", 0.2f, 0, TextHAlignment::LEFT, Vec2::ZERO);
	if (runNumber)
	{
		runNumber->setAnchorPoint(Vec2(0, 0.5));
		runNumber->setPosition(CommonFunction::getVisibleAchor(1, 0.5, label, Vec2(+15, 0)));
		label->addChild(runNumber);
	}


}
void RatioLayer::calculateRatio(CardData _card)  //计算翻新
{

	//获得胡牌用户手里的牌墙

	if (_card.m_Type == 0)
	{
		for (int i = 0; i < _gameLayer->t_Player[2].m_MyCard[0].size(); i++)
		{

			int value = _gameLayer->t_Player[2].m_MyCard[0][i];
			log("m_MyCard【0】t : %d, v : %d", 0, value);
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}

		}
		//peng
		for (int i = 0; i < _gameLayer->t_Player[2].m_PengCardVec[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_PengCardVec[0][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}

		}
		// iduo
		for (int i = 0; i < _gameLayer->t_Player[2].m_KaiDuoCardVec[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_KaiDuoCardVec[0][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}

		}
		//m_SaoChuanCardVec[0]
		for (int i = 0; i < _gameLayer->t_Player[2].m_SaoChuanCardVec[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_SaoChuanCardVec[0][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}
		}
		//m_SaoCardVec[0]
		for (int i = 0; i < _gameLayer->t_Player[2].m_SaoCardVec[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_SaoCardVec[0][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}
		}
		//m_ChiCardVec[0]
		for (int i = 0; i < _gameLayer->t_Player[2].m_ChiCardVec[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_ChiCardVec[0][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}
		}
	}
	if (_card.m_Type == 1)
	{
		for (int i = 0; i < _gameLayer->t_Player[2].m_MyCard[1].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_MyCard[1][i];
			log("m_MyCard【1】t : %d, v : %d", 1, value);
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}
				}
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
						ratioNum++;
				}
			}
		}
			//peng
		for (int i = 0; i < _gameLayer->t_Player[2].m_PengCardVec[1].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_PengCardVec[1][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)
					{
						ratioNum++;
					}				
				}			
			}
			else
			{
				if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
				{
					ratioNum++;
				}
			}
		}
			// iduo
		for (int i = 0; i < _gameLayer->t_Player[2].m_KaiDuoCardVec[1].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_KaiDuoCardVec[1][i];
			if (_card.m_Value == 1 || _card.m_Value == 10)
			{
				if (_card.m_Value == 1)
				{
					if (_card.m_Value == (value - 1) || value == 10)
					{
						ratioNum++;
					}
				}
				if (_card.m_Value == 10)
				{
					if (_card.m_Value == (value + 1) || value == 1)				
					{
						ratioNum++;
					}
				}
			}
			else
			{
					if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
					{
						ratioNum++;
					}
				}
			}
			//m_SaoChuanCardVec[0]
			for (int i = 0; i < _gameLayer->t_Player[2].m_SaoChuanCardVec[1].size(); i++)
			{
				int value = _gameLayer->t_Player[2].m_SaoChuanCardVec[1][i];
				if (_card.m_Value == 1 || _card.m_Value == 10)
				{
					if (_card.m_Value == 1)
					{
						if (_card.m_Value == (value - 1) || value == 10)
						{
							ratioNum++;
						}
					}
					if (_card.m_Value == 10)
					{
						if (_card.m_Value == (value + 1) || value == 1)
						{
							ratioNum++;
						}
					}
				}
				else
				{
					if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
					{
						ratioNum++;
					}
				}
			}
			//m_SaoCardVec[0]
			for (int i = 0; i < _gameLayer->t_Player[2].m_SaoCardVec[1].size(); i++)
			{
				int value = _gameLayer->t_Player[2].m_SaoCardVec[1][i];
				if (_card.m_Value == 1 || _card.m_Value == 10)
				{
					if (_card.m_Value == 1)
					{
						if (_card.m_Value == (value - 1) || value == 10)
						{
							ratioNum++;
						}
					}
					if (_card.m_Value == 10)
					{
						if (_card.m_Value == (value + 1) || value == 1)
						{
							ratioNum++;
						}
					}
				}
				else
				{
					if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
					{
						ratioNum++;
					}
				}
			}
			//m_ChiCardVec[0]
			for (int i = 0; i < _gameLayer->t_Player[2].m_ChiCardVec[1].size(); i++)
			{
				int value = _gameLayer->t_Player[2].m_ChiCardVec[1][i];
				if (_card.m_Value == 1 || _card.m_Value == 10)
				{
					if (_card.m_Value == 1)
					{
						if (_card.m_Value == (value - 1) || value == 10)
						{
							ratioNum++;
						}
					}
					if (_card.m_Value == 10)
					{
						if (_card.m_Value == (value + 1) || value == 1)
						{
							ratioNum++;
						}
					}
				}
				else
				{
					if (_card.m_Value == (value + 1) || _card.m_Value == (value - 1))
					{
						ratioNum++;
					}
				}
			}
		}

	
}

void RatioLayer::checkRatio()
{
	//起一张剩余的牌
	auto _card = _gameLayer->t_ZPManage.GetAPai().m_NewCard;
	GetScore::getInstance()->showCardList.push_back(_card);
	CardSprite* fanpai = CardSprite::create(_card.m_Type,_card.m_Value);
	if (fanpai)
	{
		addChild(fanpai);
		float height = fanpai->getContentSize().height;
		fanpai->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(0,height / 2 )));

		auto delayTime = DelayTime::create(0.8f);
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, height + 40)));
		auto sqe = Sequence::create(moveTo,delayTime,nullptr);
		fanpai->runAction(sqe);
	}

	//获得胡牌用户手里的牌墙
	calculateRatio(_card);

	count++;

	//刷新一下ratioLabel
	runNumber->setString(Value(ratioNum).asString());
	GetScore::getInstance()->setFanXin(ratioNum);
	/*runNumber_1->setString(Value(ratioNum).asString());*/

	log("ratio = %d", ratioNum);
	log("count = %d", count);

	if (ratioNum >= (count * 4))
	{
		log("****");
		auto delayTime = DelayTime::create(1.0f);
		//yanshi 
		auto callFun = CallFunc::create([=]{
			checkRatio();
		});
		auto seq = Sequence::create(delayTime,callFun,nullptr);
		this->runAction(seq);
	}
	else
	{
		//显示所有剩余底牌
		int num = _gameLayer->t_ZPManage.getSize();
		for (int i = 0; i < num; i++)
		{
			CardEx c = _gameLayer->t_ZPManage.GetAPai();
			GetScore::getInstance()->showCardList.push_back(c.m_NewCard);
			log("sheyu:%d", num);
			if (c.m_NewCard.m_Type == 0)
			{
				CardSprite* _card = CardSprite::create(0, c.m_NewCard.m_Value);
				/*_card->setPosition(CommonFunction::getVisibleAchor(0.4, 0.5, Vec2(50 * i, 0)));*/
				addChild(_card);
				m_CardList.push_back(_card);

			}
			if (c.m_NewCard.m_Type == 1)
			{
				CardSprite* _card = CardSprite::create(1, c.m_NewCard.m_Value);
			/*	_card->setPosition(CommonFunction::getVisibleAchor(0.4, 0.5, Vec2(50 * i, 0)));*/
				addChild(_card);
				m_CardList.push_back(_card);
			}
		}
		showAllCard();
	}
	_eventDispatcher->dispatchCustomEvent(REPLACE_ACCOUNTS);
}

void RatioLayer::showAllCard()
{
	if (m_CardList.empty())
	{
		return;
	}
	if (!m_CardList.empty())
	{
		float _width = m_CardList.at(0)->getContentSize().width;
		int _leftSize = 21 - m_CardList.size();

		for (int i = 0; i < m_CardList.size(); ++i)
		{
			if (m_CardList.at(i))
			{
				m_CardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(45 * i + 130 + _leftSize * (45 / 2),0)));
				//m_CardList.at(i)->setVisible(false);
				m_CardList.at(i)->setCardOpacity(0);//
				
			}
		}

		_needVisible = true;
	}
}

void RatioLayer:: update(float dt)
{
	log("update");
	if (_needVisible)
	{
		_SumTime += dt;
		if (_SumTime > 0.07)
		{
			setVisibleOneByOne();		//一行行显示
			_SumTime = 0;
		}
	}
}

void RatioLayer::setVisibleOneByOne()
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
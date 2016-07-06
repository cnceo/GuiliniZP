#include "ShowLayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "GameLayer.h"
#include "ShowCard.h"

ShowLayer::ShowLayer():
m_GameLayer(nullptr),
m_ACard(nullptr),
m_NewCard(nullptr),
m_backCard(nullptr)
{
	//显示卡牌
	auto _listener_1 = EventListenerCustom::create(CREATE_CARD, [=](EventCustom*event){
		createACard();
	});
	
	//新的牌
	auto _listener_2 = EventListenerCustom::create(NEW_CARD, [=](EventCustom*event){
		createANewCard();
	});

	//碰的牌
	auto _listener_3 = EventListenerCustom::create(SHOW_PENGCARD, [=](EventCustom*event){
		showPengCard();
	});

	//开舵的牌
	auto _listener_4 = EventListenerCustom::create(SHOW_KAIDUOCARD, [=](EventCustom*event){
		showKaiduoCard();
	});

	//扫穿的牌
	auto _listener_5 = EventListenerCustom::create(SHOW_SAOCHUANCARD, [=](EventCustom*event){
		showSaochuanCard();
	});

	//扫的牌
	auto _listener_6 = EventListenerCustom::create(SHOW_SAOCARD, [=](EventCustom*event){
		showSaoCard();
	});

	//扫的牌
	auto _listener_7 = EventListenerCustom::create(SHOW_CHICARD, [=](EventCustom*event){
		showChiCard();
	});

	//显示弃牌
	auto _listener_8 = EventListenerCustom::create(SHOW_QIPAI, [=](EventCustom*event){
		moveToQiPai();
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_3, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_4, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_5, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_6, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_7, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_8, 1);
}

ShowLayer::~ShowLayer()
{
	_eventDispatcher->removeCustomEventListeners(CREATE_CARD);
	_eventDispatcher->removeCustomEventListeners(NEW_CARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_PENGCARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_KAIDUOCARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_SAOCHUANCARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_SAOCARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_CHICARD);
	_eventDispatcher->removeCustomEventListeners(SHOW_QIPAI);
}

ShowLayer* ShowLayer::create(GameLayer* _layer)
{
	ShowLayer* ret = new ShowLayer();
	if (ret && ret->init(_layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ShowLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}
	m_GameLayer = _layer;

	initData();

	initUI();

	return true;
}

void ShowLayer::initData()
{
	auto layercolor = LayerColor::create(Color4B::BLACK);
	layercolor->setOpacity(100);
	addChild(layercolor);

}

void ShowLayer::initUI()
{

}

//创建长的牌card
Sprite* ShowLayer::createBigCardSprite(int p_Type, int p_Value)
{
	Sprite* card =nullptr;
	if (p_Type == 0)
	{
		//小写 
		card = Sprite::create(StringUtils::format("chang_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		//大写 1-10.png	
		card = Sprite::create(StringUtils::format("chang_d%0d.png", p_Value));
	}
	if (card)
	{
		card->setScale(0.7f);
		return card;
	}
	return nullptr;
}

//短牌创建
Sprite* ShowLayer::createSmallCardSprite(int p_Type, int p_Value)
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
		card->setScale(0.7f);
		return card;
	}
	return nullptr;
}

void ShowLayer::createACard()
{
	int gameState = UserDefault::getInstance()->getIntegerForKey(GAMESTATE, 1);

	int _type = m_GameLayer->PopPai.m_Type;
	int _value = m_GameLayer->PopPai.m_Value;

	if (_type < 0 || _type > 1 || _value <= 0 || _value > 10)
	{
		log("_value or _type error0");
		return;
	}

	if (m_ACard)
	{
		if (m_ACard->getParent())
		{
			m_ACard->removeFromParent();
		}
	}

	m_ACard = createBigCardSprite(_type, _value);
	if (m_ACard)
	{
		addChild(m_ACard);
		m_ACard->setScale(0.1f);
		auto moveTo = MoveTo::create(0.3, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
		auto scaleTo = ScaleTo::create(0.3f,0.6f);
		auto spawn = Spawn::create(moveTo, scaleTo,nullptr);

		auto delay = DelayTime::create(1.0f);
		auto callfunc = CallFunc::create([=](){
			m_ACard->setVisible(false);
		});
		auto seq = Sequence::create(spawn,delay,callfunc,nullptr);

		if (gameState == 0)
		{
			if (m_ACard)
			{
				m_ACard->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftTop, Vec2::ZERO));

				auto moveTo = MoveTo::create(0.3, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(-300, 200)));
				auto scaleTo = ScaleTo::create(0.3f, 0.6f);
				auto spawn = Spawn::create(moveTo, scaleTo, nullptr);

				auto delay = DelayTime::create(1.0f);
				auto callfunc = CallFunc::create([=](){
					m_ACard->setVisible(false);
				});
				auto _seq = Sequence::create(spawn, delay, callfunc, nullptr);

				m_ACard->runAction(_seq);
			}
		}
		else if (gameState == 1)
		{
			if (m_ACard)
			{
				m_ACard->setPosition(CommonFunction::getVisibleAchor(Anchor::RightTop, Vec2::ZERO));

				auto moveTo = MoveTo::create(0.3, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(300, 200)));
				auto scaleTo = ScaleTo::create(0.3f, 0.6f);
				auto spawn = Spawn::create(moveTo, scaleTo, nullptr);

				auto delay = DelayTime::create(1.0f);
				auto callfunc = CallFunc::create([=](){
					m_ACard->setVisible(false);
				});
				auto _seq = Sequence::create(spawn, delay, callfunc, nullptr);

				m_ACard->runAction(_seq);
			}
		}
		else if (gameState == 2)
		{
			if (m_ACard)
			{
				m_ACard->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, Vec2(0, 95)));
				m_ACard->runAction(seq);
			}
		}
	}

	//auto fadeOut = FadeOut::create(3.0f);
	/*auto callfunc = CallFunc::create([=](){
		m_ACard->setVisible(false);
	});
	auto delay = DelayTime::create(1.0f);
	auto seq = Sequence::create(delay,callfunc,nullptr);
	if (m_ACard)
	{
		m_ACard->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
		m_ACard->runAction(seq);
	}*/
}

void ShowLayer::flyToHand()
{
	if (m_NewCard)
	{
		auto delay = DelayTime::create(1.0f);
		auto move = MoveTo::create(0.3f,CommonFunction::getVisibleAchor(Anchor::MidButtom,Vec2(0,95)));
		auto callfun = CallFunc::create([=](){
			m_NewCard->setVisible(false);
		});

		auto callfun_1 = CallFunc::create([=](){
			m_GameLayer->t_Player[2].addCard(m_GameLayer->m_newCard.m_Type, m_GameLayer->m_newCard.m_Value);
			m_GameLayer->refrishCardPos();
			m_GameLayer->t_Player[2].notChi();
		});
		auto seq = Sequence::create(delay, move, callfun, callfun_1, nullptr);
		m_NewCard->runAction(seq);
	}
}

void ShowLayer::createANewCard()
{
	int _type = m_GameLayer->m_newCard.m_Type;
	int _value = m_GameLayer->m_newCard.m_Value;

	if (_type < 0 || _type > 1 || _value <= 0 || _value > 10)
	{
		log("_value or _type error1");
		return;
	}

	if (m_NewCard)
	{
		if (m_NewCard->getParent())
		{
			m_NewCard->removeFromParent();
		}
	}

	if (m_backCard)
	{
		if (m_backCard->getParent())
		{
			m_backCard->removeFromParent();
		}
	}

	m_backCard = Sprite::create("card_back.png");
	if (m_backCard)
	{
		addChild(m_backCard,10);
		m_backCard->setScaleX(0.7f);
		m_backCard->setScaleY(0.7f);
		float height = m_backCard->getContentSize().height;
		m_backCard->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(0, height / 2)));
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, height - 50)));
		auto fadeout = FadeOut::create(0.01);
		auto seq = Sequence::create(moveTo,fadeout,nullptr);
		m_backCard->runAction(seq);
	}

	m_NewCard = createBigCardSprite(_type, _value);
	if (m_NewCard)
	{
		m_NewCard->setScale(0.6f);
		m_NewCard->setVisible(true);
		addChild(m_NewCard);
		float height = m_NewCard->getContentSize().height;
		m_NewCard->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(0, height / 2)));
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, height - 50)));
		m_NewCard->runAction(moveTo);
	}
}

void ShowLayer::showPengCard()
{
	if (m_tmpPengCardVec.size()>0)
	{
		for (auto &_card : m_tmpPengCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpPengCardVec.clear();
	}

	std::vector<int > _pengList[2];
	_pengList[0] = m_GameLayer->t_Player[2].m_PengCardVec[0];
	_pengList[1] = m_GameLayer->t_Player[2].m_PengCardVec[1];

	if (_pengList[0].size()>0)
	{
		for (int i = 0; i < _pengList[0].size(); i++)
		{
			auto _card = ShowCard::create(0, _pengList[0][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpPengCardVec.pushBack(_card);
			}
		}
	}

	if (_pengList[1].size()>0)
	{
		for (int i = 0; i < _pengList[1].size(); i++)
		{
			auto _card = ShowCard::create(1, _pengList[1][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpPengCardVec.pushBack(_card);
			}
		}
	}

	if (m_tmpPengCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpPengCardVec.size(); i++)
		{
			int _height = m_tmpPengCardVec.at(i)->getContentSize().height;
			m_tmpPengCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 3)*(_height - 8) + 50, i % 3 * (_height - 70) - 60)));
			//_tmpSpriteList.at(i)->setPosition(Vec2((i % 3)*(_height / 4) + 100, (i / 3)*(_height- 73) + 200));
		}
	}
	refrishCardPos();
}

void ShowLayer::showKaiduoCard()
{
	showPengCard();
	showSaoCard();
	if (m_tmpKaiDuoCardVec.size()>0)
	{
		for (auto &_card : m_tmpKaiDuoCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpKaiDuoCardVec.clear();
	}

	std::vector<int > _kaiduoList[2];
	_kaiduoList[0] = m_GameLayer->t_Player[2].m_KaiDuoCardVec[0];
	_kaiduoList[1] = m_GameLayer->t_Player[2].m_KaiDuoCardVec[1];

	if (_kaiduoList[0].size()>0)
	{
		for (int i = 0; i < _kaiduoList[0].size(); i++)
		{
			auto _card = ShowCard::create(0, _kaiduoList[0][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpKaiDuoCardVec.pushBack(_card);
			}
		}
	}

	if (_kaiduoList[1].size()>0)
	{
		for (int i = 0; i < _kaiduoList[1].size(); i++)
		{
			auto _card = ShowCard::create(1, _kaiduoList[1][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpKaiDuoCardVec.pushBack(_card);
			}
		}
	}

	if (m_tmpKaiDuoCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpKaiDuoCardVec.size(); i++)
		{
			int _height = m_tmpKaiDuoCardVec.at(i)->getContentSize().height;
			m_tmpKaiDuoCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 4)*(_height - 8) + 152, i % 4 * (_height - 70) - 30)));
			//_tmpSpriteList.at(i)->setPosition(Vec2((i % 3)*(_height / 4) + 100, (i / 3)*(_height- 73) + 200));
		}
	}
	refrishCardPos();
}

void ShowLayer::showSaochuanCard()
{
	showSaoCard();
	if (m_tmpSaoChuanCardVec.size()>0)
	{
		for (auto &_card : m_tmpSaoChuanCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpSaoChuanCardVec.clear();
	}

	std::vector<int > _saochuanList[2];
	_saochuanList[0] = m_GameLayer->t_Player[2].m_SaoChuanCardVec[0];
	_saochuanList[1] = m_GameLayer->t_Player[2].m_SaoChuanCardVec[1];

	if (_saochuanList[0].size()>0)
	{
		for (int i = 0; i < _saochuanList[0].size(); i++)
		{
			auto _card = ShowCard::create(0, _saochuanList[0][i]);
			if (_card)
			{
				_card->setCardState(ShowCard::ISSAO::YES);
				_card->turnToBack();
				addChild(_card);
				m_tmpSaoChuanCardVec.pushBack(_card);
			}
		}
	}

	if (_saochuanList[1].size()>0)
	{
		for (int i = 0; i < _saochuanList[1].size(); i++)
		{
			auto _card = ShowCard::create(1, _saochuanList[1][i]);
			if (_card)
			{
				_card->setCardState(ShowCard::ISSAO::YES);
				_card->turnToBack();
				addChild(_card);
				m_tmpSaoChuanCardVec.pushBack(_card);
			}
		}
	}

	if (m_tmpSaoChuanCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpSaoChuanCardVec.size(); i++)
		{
			int _height = m_tmpSaoChuanCardVec.at(i)->getContentSize().height;
			m_tmpSaoChuanCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 4)*(_height - 8) + 200, i % 4 * (_height - 70) - 30)));
			//_tmpSpriteList.at(i)->setPosition(Vec2((i % 3)*(_height / 4) + 100, (i / 3)*(_height- 73) + 200));
		}
	}
	refrishCardPos();
}

void ShowLayer::showSaoCard()
{
	if (m_tmpSaoCardVec.size()>0)
	{
		for (auto &_card : m_tmpSaoCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpSaoCardVec.clear();
	}

	std::vector<int > _saoList[2];
	_saoList[0] = m_GameLayer->t_Player[2].m_SaoCardVec[0];
	_saoList[1] = m_GameLayer->t_Player[2].m_SaoCardVec[1];

	if (_saoList[0].size()>0)
	{
		for (int i = 0; i < _saoList[0].size(); i++)
		{
			auto _card = ShowCard::create(0, _saoList[0][i]);
			if (_card)
			{
				_card->setCardState(ShowCard::ISSAO::YES);
				_card->turnToBack();
				addChild(_card);
				m_tmpSaoCardVec.pushBack(_card);
			}
		}
	}

	if (_saoList[1].size()>0)
	{
		for (int i = 0; i < _saoList[1].size(); i++)
		{
			auto _card = ShowCard::create(1, _saoList[1][i]);
			if (_card)
			{
				_card->setCardState(ShowCard::ISSAO::YES);
				_card->turnToBack();
				addChild(_card);
				m_tmpSaoCardVec.pushBack(_card);
			}
		}
	}

	if (m_tmpSaoCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpSaoCardVec.size(); i++)
		{
			int _height = m_tmpSaoCardVec.at(i)->getContentSize().height;
			m_tmpSaoCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height - 8) - 120, i % 3 * (_height - 70) - 60)));
			//_tmpSpriteList.at(i)->setPosition(Vec2((i % 3)*(_height / 4) + 100, (i / 3)*(_height- 73) + 200));
		}
	}
	refrishCardPos();
}

void ShowLayer::showChiCard()
{
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

	{
		std::vector<int > _chiList[2];
		_chiList[0] = m_GameLayer->t_Player[2].m_ChiCardVec[0];
		_chiList[1] = m_GameLayer->t_Player[2].m_ChiCardVec[1];

		for (int i = 0; i < 2; i++)
		{
			if (!_chiList[i].empty())
			{
				for (int j = 0; j < _chiList[i].size(); j++)
				{
					auto _card = ShowCard::create(i, _chiList[i][j]);
					if (_card)
					{
						addChild(_card);
						m_tmpChiCardVec.pushBack(_card);
					}
				}
			}
		}
	}

	{
		//A_A_a_a显示有问题
		std::vector<int > _chiListA_A_a_a[2];
		_chiListA_A_a_a[0] = m_GameLayer->t_Player[2].m_ChiCardList[0];
		_chiListA_A_a_a[1] = m_GameLayer->t_Player[2].m_ChiCardList[1];

		/*for (int i = 0; i < 2; i++)
		{
		if (!_chiListA_A_a_a[i].empty())
		{
		for (int j = 0; j < _chiListA_A_a_a[i].size(); j++)
		{
		auto _card = ShowCard::create(i, _chiListA_A_a_a[i][j]);
		if (_card)
		{
		addChild(_card);
		m_tmpChiCardVec.pushBack(_card);
		}
		}
		}
		}
		}*/

		int value = 0;
		for (int i = 0; i < _chiListA_A_a_a[0].size(); i++)
		{
			if (i == 0)
			{
				value = _chiListA_A_a_a[0][i];
				auto _card = ShowCard::create(0, _chiListA_A_a_a[0][i]);//1 
				if (_card)
				{
					addChild(_card);
					m_tmpChiCardVec.pushBack(_card);
					m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
				}
				if (1 == _chiListA_A_a_a[0].size())
				{
					for (int j = 0; j < _chiListA_A_a_a[1].size(); j++)
					{
						if (_chiListA_A_a_a[1][j] == value)
						{
							auto _card = ShowCard::create(1, _chiListA_A_a_a[1][j]);//3 4 5 7
							if (_card)
							{
								addChild(_card);
								m_tmpChiCardVec.pushBack(_card);
								m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
							}
						}
					}//
				}
			}
			else
			{
				value = _chiListA_A_a_a[0][i - 1];
				if (value != _chiListA_A_a_a[0][i])
				{
					for (int j = 0; j < _chiListA_A_a_a[1].size(); j++)
					{
						if (_chiListA_A_a_a[1][j] == _chiListA_A_a_a[0][i - 1])
						{
							auto _card = ShowCard::create(1, _chiListA_A_a_a[1][j]);//3 4 5 7
							if (_card)
							{
								addChild(_card);
								m_tmpChiCardVec.pushBack(_card);
								m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
							}
						}
					}//
					auto _card = ShowCard::create(0, _chiListA_A_a_a[0][i]);//6  8
					if (_card)
					{
						addChild(_card);
						m_tmpChiCardVec.pushBack(_card);
						m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
					}
					if (i + 1 == _chiListA_A_a_a[0].size())  //shi fou shi xiaoxie lest
					{
						for (int j = 0; j < _chiListA_A_a_a[1].size(); j++)
						{
							if (_chiListA_A_a_a[1][j] == _chiListA_A_a_a[0][i])
							{
								auto _card = ShowCard::create(1, _chiListA_A_a_a[1][j]);//3 4 5 7
								if (_card)
								{
									addChild(_card);
									m_tmpChiCardVec.pushBack(_card);
									m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
								}
							}
						}//
					}
				}
				else
				{
					auto _card = ShowCard::create(0, _chiListA_A_a_a[0][i]);//2 9
					if (_card)
					{
						addChild(_card);
						m_tmpChiCardVec.pushBack(_card);
						m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
					}
					if (i + 1 == _chiListA_A_a_a[0].size())  //shi fou shi xiaoxie lest
					{
						for (int j = 0; j < _chiListA_A_a_a[1].size(); j++)
						{
							if (_chiListA_A_a_a[1][j] == _chiListA_A_a_a[0][i])
							{
								auto _card = ShowCard::create(1, _chiListA_A_a_a[1][j]);//3 4 5 7
								if (_card)
								{
									addChild(_card);
									m_tmpChiCardVec.pushBack(_card);
									m_GameLayer->t_Player[2].AAaaCardSprite.push_back(_card);
								}
							}
						}//
					}
				}

			}

		}
	}

	{
		std::vector<int > _chiSpecialList[2];
		_chiSpecialList[0] = m_GameLayer->t_Player[2].m_ChiSpeclal[0];
		_chiSpecialList[1] = m_GameLayer->t_Player[2].m_ChiSpeclal[1];

		if (_chiSpecialList[0].size()>0)
		{
			for (int i = 0; i < _chiSpecialList[0].size(); i++)
			{
				auto _card = ShowCard::create(0, _chiSpecialList[0][i]);
				if (_card)
				{
					addChild(_card);
					m_tmpChiCardVec.pushBack(_card);
				}
			}
		}

		if (_chiSpecialList[1].size() > 0)
		{
			for (int i = 0; i < _chiSpecialList[1].size(); i++)
			{
				auto _card = ShowCard::create(1, _chiSpecialList[1][i]);
				if (_card)
				{
					addChild(_card);
					m_tmpChiCardVec.pushBack(_card);
				}
			}
		}
	}

	if (m_tmpChiCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpChiCardVec.size(); i++)
		{
			int _height = m_tmpChiCardVec.at(i)->getContentSize().height;
			m_tmpChiCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height - 8), i % 3 * (_height - 70) - 60)));
			//_tmpSpriteList.at(i)->setPosition(Vec2((i % 3)*(_height / 4) + 100, (i / 3)*(_height- 73) + 200));
			//m_tmpSaoCardList.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height - 8) - 120, i % 3 * (_height - 70) - 60)));
		}
	}
	refrishCardPos();
}

void ShowLayer::refrishCardPos()
{
	if (!m_ThreeCardVec.empty())
	{
		m_ThreeCardVec.clear();
	}

	if (!m_FourCardVec.empty())
	{
		m_FourCardVec.clear();
	}

	m_ThreeCardVec.pushBack(m_tmpPengCardVec);
	m_ThreeCardVec.pushBack(m_tmpSaoCardVec);
	m_ThreeCardVec.pushBack(m_tmpChiCardVec);

	m_FourCardVec.pushBack(m_tmpKaiDuoCardVec);
	m_FourCardVec.pushBack(m_tmpSaoChuanCardVec);

	if (!m_ThreeCardVec.empty())
	{
		for (int i = 0; i < m_ThreeCardVec.size(); i++)
		{
			auto _card = m_ThreeCardVec.at(i);
			auto _height = _card->getContentSize().height;
			//if (_card->getState() == ShowCard::STATE::Peng || _card->getState() == ShowCard::STATE::Sao || _card->getState() == ShowCard::STATE::Chi)
			{
				_card->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 3)*(_height - 8) + 152, i % 3 * (_height - 70) - 60)));
			}
		}
		
		if (!m_ThreeCardVec.empty())
		{
			for (int i = 0; i < m_FourCardVec.size(); i++)
			{
				auto _card = m_FourCardVec.at(i);
				auto _height = _card->getContentSize().height;
				//if (_card->getState() == ShowCard::STATE::Kaiduo || _card->getState() == ShowCard::STATE::Saochuan)
				{
					_card->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 4)*(_height - 8) + m_ThreeCardVec.back()->getPosition().x + _height / 2 + 15 , i % 4 * (_height - 70) - 30)));
				}
			}
		}
	}
}

void ShowLayer::moveToQiPai()
{
	/*if (!m_TwoQipai.empty())
	{
		m_TwoQipai.clear();
	}

	if (!m_ZeroQipai.empty())
	{
		m_ZeroQipai.clear();
	}

	if (!m_OneQipai.empty())
	{
		m_OneQipai.clear();
	}*/
	
	if (UserDefault::getInstance()->getIntegerForKey(GAMESTATE) == 0)		//下家操作
	{
		/*auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::RightMid, Vec2(-250, 70)));
		auto ease = EaseSineOut::create(moveTo);
		auto scaleTo = ScaleTo::create(0.5f, 0.1f);
		auto spawn = Spawn::create(ease, scaleTo, nullptr);

		auto callfunc = CallFunc::create([=](){
			m_NewCard->setVisible(false);
		});
		auto seq = Sequence::create(spawn, callfunc, nullptr);
		if (m_NewCard)
		{
			m_NewCard->runAction(seq);
		}

		int _type = m_GameLayer->m_newCard.m_Type;
		int _value = m_GameLayer->m_newCard.m_Value;
		auto _card = ShowCard::create(_type, _value);
		if (_card)
		{
			addChild(_card);
			m_OneQipai.pushBack(_card);
		}

		for (int i = 0; i < m_OneQipai.size(); i++)
		{
			float width = m_OneQipai.at(i)->getContentSize().width;
			m_OneQipai.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i % 4)*(width - 14) + 300, 50)));
		}*/
	}
	else if (UserDefault::getInstance()->getIntegerForKey(GAMESTATE) == 2)	//上家操作
	{

	}
	else if (UserDefault::getInstance()->getIntegerForKey(GAMESTATE) == 1)  //我自己操作
	{
		
		auto moveTo = MoveTo::create(0.5f,CommonFunction::getVisibleAchor(Anchor::RightMid,Vec2(-250,-70)));
		auto ease = EaseSineOut::create(moveTo);
		auto scaleTo = ScaleTo::create(0.5f,0.1f);
		auto spawn = Spawn::create(ease, scaleTo,nullptr);

		auto callfunc = CallFunc::create([=](){
			m_NewCard->setVisible(false);
		});
		auto seq = Sequence::create(spawn, callfunc, nullptr);
		if (m_NewCard)
		{
			m_NewCard->runAction(seq);
		}
		
		int _type = m_GameLayer->m_newCard.m_Type;
		int _value = m_GameLayer->m_newCard.m_Value;
		auto _card = ShowCard::create(_type, _value);
		if (_card)
		{
			addChild(_card);
			CommonFunction::setNodeOpacity(_card,0);
			m_TwoQipai.pushBack(_card);
		}
		
	}

	for (int i = 0; i < m_TwoQipai.size();i++)
	{
		float width = m_TwoQipai.at(i)->getContentSize().width;
		m_TwoQipai.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i)*(width - 14) + 300, -50 )));
		CommonFunction::nodeFadeIn(m_TwoQipai.at(i), 0.5f);
	}
}
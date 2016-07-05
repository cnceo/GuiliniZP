
#include "AccountsLayer.h"
#include "ui/UIButton.h"
#include <iostream>
#include "utils/CommonFunction.h"
#include "layer/GameScene.h"
#include "layer/WelcomeScene.h"
#include "utils/GetLayer.h"
#include "utils/Constant.h"
#include "utils/GetScore.h"
#include "layer/RatioLayer.h"


#include "utils/GetLayer.h"

using namespace std;
using namespace ui;

#define WIN_DATA Win::getInstance()

int AccountsLayer::count = 0;

AccountsLayer::AccountsLayer()
{

}

AccountsLayer::~AccountsLayer()
{
	
}

Scene* AccountsLayer::createScene()
{
	auto s = Scene::create();
	auto l = AccountsLayer::create();
	s->addChild(l);
	return s;
}

void AccountsLayer::onEnter()
{
	Layer::onEnter();
	// 屏蔽触摸
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [](Touch *, Event *){return true; };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void AccountsLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
		{
			if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
			{
				//close();
			}
		}
	}
}

bool AccountsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addUI();

	return true;
}

void AccountsLayer::addUI()
{
	auto bg_sp = Sprite::create("zm_bg.png");
	if (bg_sp)
	{
		addChild(bg_sp);
		bg_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center,Vec2::ZERO));
	}

	auto layercolor = LayerColor::create(Color4B(0, 0, 0, 150));
	addChild(layercolor);

	auto gray_sp = Sprite::create("account/ima_gray_1.png");
	if (gray_sp)
	{
		addChild(gray_sp);
		gray_sp->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
	}

	//返回
	auto backBtn = Button::create("account/btn_back.png");
	if (backBtn)
	{
		addChild(backBtn);
		backBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::quiteCallback, this));
		float _width = backBtn->getContentSize().width / 2 + 15;
		float _heignt = backBtn->getContentSize().height / 2 + 15 ;

		backBtn->setPosition(CommonFunction::getVisibleAchor(1, 1, Vec2(-_width, -_heignt)));
	}
	//重新开始
	auto restartBtn = Button::create("account/btn_again.png");
	if (restartBtn)
	{
		restartBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::restartCallback, this));
		auto _he = restartBtn->getContentSize().height / 2 +15;
		restartBtn->setPosition(CommonFunction::getVisibleAchor(Anchor::MidButtom, Vec2(0, _he)));
		addChild(restartBtn);

		//effect
		float X = restartBtn->getContentSize().height / 2;
		auto path = MyPathFun(X+10, restartBtn->getContentSize().height - 10, restartBtn->getContentSize().width - 75);
		auto _emitter2 = particleInit();
		_emitter2->setPosition(Point(restartBtn->getPosition().x - 100 , restartBtn->getPosition().y - 30));//130,25 restartBtn->getContentSize().height/2
		_emitter2->runAction(path);

	}


	//结算
	auto jiesuan_sp = Sprite::create("account/zi_jiesuan.png");
	if (jiesuan_sp)
	{
		addChild(jiesuan_sp);
		jiesuan_sp->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(jiesuan_sp->getContentSize().width /2, -85)));

	}
	//底牌
	auto dipai_sp = Sprite::create("account/zi_dipai.png");	
	if (dipai_sp)
	{
		addChild(dipai_sp);
		dipai_sp->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(300, -100)));

	}

	//头像
	auto icon_left = Sprite::create("icon_image/icon_girl_1.png");
	auto width = icon_left->getContentSize().width / 2 + 10;

	if (icon_left)
	{
		gray_sp->addChild(icon_left);
		icon_left->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, gray_sp ,Vec2(width, -width)));
	}

	auto icon_leftDown = Sprite::create("icon_image/icon_girl_2.png");
	if (icon_leftDown)
	{
		gray_sp->addChild(icon_leftDown);
		icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0, 0,gray_sp,Vec2(width+ 80, width+50)));
	}

	auto icon_right = Sprite::create("icon_image/icon_boy_1.png");
	if (icon_right)
	{
		gray_sp->addChild(icon_right);
		icon_right->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, gray_sp, Vec2(width, -width -85)));
	}
	if (UserDefault::getInstance()->getBoolForKey(ISHZ))
	{
		auto huangz_sp = Sprite::create("huangzhuang.png");
		addChild(huangz_sp);
		huangz_sp->setPosition(CommonFunction::getVisibleAchor(0, 0.5, Vec2(340, 40)));
		//test
		//showDiPai(dipai_sp);
		//showWinCard(2);
		//AddLabel();
		//addWinUI();

		addHZUI(icon_left);
		addHZUI(icon_leftDown);
		addHZUI(icon_right);
	}
	else
	{
		log("no huangzhuang");
		showDiPai(dipai_sp);
		showWinCard( 2);
		AddLabel();
		addWinUI();
	}

}

//添加winui
void AccountsLayer::addWinUI()
{
	auto m_win = Sprite::create("account/win_big.png");
	if (m_win)
	{
		m_win->setAnchorPoint(Vec2(0, 0.5));
		m_win->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(0, -90)));
		addChild(m_win);
		auto win = Sprite::create("account/zi_win.png");
		if (win)
		{
			win->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_win, Vec2(0, 0)));
			win->setScale(1.5);
			m_win->addChild(win);
			auto add = Label::createWithTTF("+ ", "fonts/Roboto-Medium.ttf", 60);
			if (add)
			{
				add->setColor(Color3B::YELLOW);
				add->setAnchorPoint(Vec2(0, 0.5));
				add->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, win, Vec2(30, 15)));
				win->addChild(add);
			}
			auto money = Label::createWithBMFont("fonts/huangshe.fnt", Value(GetScore::getInstance()->getMoney()).asString(), TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (money)
			{
				money->setAnchorPoint(Vec2(0, 0.7));
				money->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, add, Vec2(20, 0)));
				add->addChild(money);
			}

		}
		auto icon_left = Sprite::create("icon_image/icon_girl_1.png");
		if (icon_left)
		{
			icon_left->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_win, Vec2(-150, 15)));
			m_win->addChild(icon_left);
		}
	}

	auto m_los_1 = Sprite::create("account/lose_xiao.png");
	if (m_los_1)
	{
		m_los_1->setAnchorPoint(Vec2(1, 0.5));
		m_los_1->setPosition(CommonFunction::getVisibleAchor(Anchor::RightMid, Vec2(0, -45)));
		addChild(m_los_1);
		auto los = Sprite::create("account/zi_shu.png");
		if (los)
		{
			los->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_los_1, Vec2(0, 0)));
			m_los_1->addChild(los);
			auto add = Label::createWithTTF("- ", "fonts/Roboto-Medium.ttf", 60);
			if (add)
			{
				add->setAnchorPoint(Vec2(0, 0.5));
				add->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, los, Vec2(50, 0)));
				los->addChild(add);
			}
			auto money = Label::createWithBMFont("fonts/baishe.fnt", Value(GetScore::getInstance()->getMoney() / 2).asString(), TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (money)
			{
				money->setAnchorPoint(Vec2(0, 0.7));
				money->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, add, Vec2(20, 0)));
				add->addChild(money);

			}
		}
		auto icon_right = Sprite::create("icon_image/icon_boy_1.png");
		if (icon_right)
		{
			icon_right->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_los_1, Vec2(-225, 0)));
			m_los_1->addChild(icon_right);
		}

	}
	auto m_los_2 = Sprite::create("account/lose_xiao.png");
	if (m_los_2)
	{
		m_los_2->setAnchorPoint(Vec2(1, 0.5));
		m_los_2->setPosition(CommonFunction::getVisibleAchor(Anchor::RightMid, Vec2(0, -130)));
		addChild(m_los_2);
		auto los = Sprite::create("account/zi_shu.png");
		if (los)
		{
			los->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_los_2, Vec2(0, 0)));
			m_los_2->addChild(los);
			auto add = Label::createWithTTF("- ", "fonts/Roboto-Medium.ttf", 60);
			if (add)
			{
				add->setAnchorPoint(Vec2(0, 0.5));
				add->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, los, Vec2(50, 0)));
				los->addChild(add);
			}
			auto money = Label::createWithBMFont("fonts/baishe.fnt", Value(GetScore::getInstance()->getMoney() / 2).asString(), TextHAlignment::LEFT, 0, Vec2::ZERO);
			if (money)
			{
				money->setAnchorPoint(Vec2(0, 0.7));
				money->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, add, Vec2(20, 0)));
				add->addChild(money);

			}
		}
		auto icon_leftDown = Sprite::create("icon_image/icon_girl_2.png");
		if (icon_leftDown)
		{
			icon_leftDown->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_los_2, Vec2(-225, 0)));
			m_los_2->addChild(icon_leftDown);
		}
	}

}

//添加label
void AccountsLayer::AddLabel()
{
	//添加胡数，番醒等label
	auto fanXin = Label::createWithTTF(Value(GetScore::getInstance()->getFanXin()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (fanXin)
	{
		fanXin->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid,Vec2(860,70)));
		addChild(fanXin);
	}
	auto huShu = Label::createWithTTF(Value(GetScore::getInstance()->getHuDuo()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (huShu)
	{
		huShu->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(860, 160)));
		addChild(huShu);
	}
	auto ziMo = Label::createWithTTF(Value(GetScore::getInstance()->getZiMo()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (ziMo)
	{
		ziMo->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(860, 115)));
		addChild(ziMo);
	}
	auto tianHu = Label::createWithTTF(Value(GetScore::getInstance()->getTianHu()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (tianHu)
	{
		tianHu->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(1050, 105)));
		addChild(tianHu);
	}
	auto diHu = Label::createWithTTF(Value(GetScore::getInstance()->getDiHu()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (diHu)
	{
		diHu->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(1050, 145)));
		addChild(diHu);
	}
	auto sanLWK = Label::createWithTTF(Value(GetScore::getInstance()->getSanLongWuK()).asString(), "fonts/Roboto-Medium.ttf", 35);
	if (sanLWK)
	{
		sanLWK->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(1050, 55)));
		addChild(sanLWK);
	}
	auto beiShu = Label::createWithTTF(Value(GetScore::getInstance()->getBeiShu()).asString(), "fonts/Roboto-Medium.ttf", 40);
	if (beiShu)
	{
		beiShu->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(860, 25)));
		addChild(beiShu);
	}
}

void AccountsLayer::quiteCallback(Ref* sender)
{
	if (this->getParent())
	{
		GetScore::getInstance()->showCardList.clear();
		GetScore::getInstance()->setFanXin(0);
		GetScore::getInstance()->setScore(0);
		GetScore::getInstance()->setHuDuo(0);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::createScene()));

	}
}

void AccountsLayer::restartCallback(Ref* sender)
{
	if (this->getParent())
	{
		GetScore::getInstance()->showCardList.clear();
		GetScore::getInstance()->setFanXin(0);
		GetScore::getInstance()->setScore(0);
		GetScore::getInstance()->setHuDuo(0);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
	}
}

//显示底牌
void  AccountsLayer::showDiPai(Node* node)
{
	//获得底牌，以及番醒的牌
	//RatioLayer* ratiolayer;
	if (GetScore::getInstance()->showCardList.size() > 0)
	{
		//创建小牌
		for (int i = 0; i < GetScore::getInstance()->showCardList.size(); i++)
		{
			ShowCard* card = ShowCard::create(GetScore::getInstance()->showCardList[i].m_Type, GetScore::getInstance()->showCardList[i].m_Value);
			card->setPosition(CommonFunction::getVisibleAchor(1.7,1.2,node,Vec2(i * 30,0)));
			node->addChild(card);
		}	
	}
}

//显示赢家胡牌牌型
void AccountsLayer::showWinCard(int player)
{
	showThreeVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_PengCardVec);
	showThreeVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_SaoCardVec);
	showThreeVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_ChiCardVec);
	showFourVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_KaiDuoCardVec);
	showFourVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_SaoChuanCardVec);
	showFourVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_ChiSpeclal);

	addAAaaUI(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_ChiCardList);

	showMyCardWall(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_MyCard);

	
	setCardVerPoint();
	count = 0;

}



void AccountsLayer::addAAaaUI(vector<int> ver[2])
{
	vector<ShowCard* > m_AAaaSprite;//m_ChiCardList[0]

	int value = 0;
	for (int i = 0; i < ver[0].size(); i++)
	{
		if (i == 0)
		{
			value = ver[0].at(i);
			auto _card = ShowCard::create(0, ver[0].at(i));//1 
			if (_card)
			{
				addChild(_card);
				m_AAaaSprite.push_back(_card);
			}
			if (1 == ver[0].size())
			{
				for (int j = 0; j < ver[1].size(); j++)
				{
					if (ver[1].at(j) == value)
					{
						auto _card = ShowCard::create(1, ver[1].at(j));//3 4 5 7
						if (_card)
						{
							addChild(_card);
							m_AAaaSprite.push_back(_card);
						}
					}
				}//
			}
		}
		else
		{
			value = ver[0].at(i - 1);
			if (value != ver[0].at(i))
			{
				for (int j = 0; j < ver[1].size(); j++)
				{
					if (ver[1].at(j) == ver[0].at(i - 1))
					{
						auto _card = ShowCard::create(1, ver[1].at(j));//3 4 5 7
						if (_card)
						{
							addChild(_card);
							m_AAaaSprite.push_back(_card);
						}
					}
				}//
				auto _card = ShowCard::create(0, ver[0].at(i));//6  8
				if (_card)
				{
					addChild(_card);
					m_AAaaSprite.push_back(_card);
				}
				if (i + 1 == ver[0].size())  //shi fou shi xiaoxie lest
				{
					for (int j = 0; j < ver[1].size(); j++)
					{
						if (ver[1].at(j) == ver[0].at(i))
						{
							auto _card = ShowCard::create(1, ver[1].at(j));//3 4 5 7
							if (_card)
							{
								addChild(_card);
								m_AAaaSprite.push_back(_card);
							}
						}
					}//
				}
			}
			else
			{
				auto _card = ShowCard::create(0, ver[0].at(i));//2 9
				if (_card)
				{
					addChild(_card);
					m_AAaaSprite.push_back(_card);
				}
				if (i + 1 == ver[0].size())  //shi fou shi xiaoxie lest
				{
					for (int j = 0; j < ver[1].size(); j++)
					{
						if (ver[1].at(j) == ver[0].at(i))
						{
							auto _card = ShowCard::create(1, ver[1].at(j));//3 4 5 7
							if (_card)
							{
								addChild(_card);
								m_AAaaSprite.push_back(_card);

							}
						}
					}
				}
			}

		}

	}
	for (int i = 0; i < m_AAaaSprite.size(); i++)
	{
		CardPoint cardpoint;

		cardpoint.card_1 = m_AAaaSprite.at(i);
		i++;
		cardpoint.card_2 = m_AAaaSprite.at(i);
		i++;
		cardpoint.card_3 = m_AAaaSprite.at(i);

		showCard.push_back(cardpoint);
	}


}

void  AccountsLayer::showThreeVer( vector<int> ver[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (!ver[i].empty())
		{
			for (int j = 0; j < ver[i].size(); j++)
			{
				CardPoint cardpoint;
				auto _card_1 = ShowCard::create(i, ver[i].at(j));
				if (_card_1)
				{
					addChild(_card_1);
					cardpoint.card_1 = _card_1;
				}
				j++;
				auto _card_2 = ShowCard::create(i, ver[i].at(j));
				if (_card_2)
				{
					addChild(_card_2);
					cardpoint.card_2 = _card_2;
				}
				j++;
				auto _card_3 = ShowCard::create(i, ver[i].at(j));
				if (_card_3)
				{
					addChild(_card_3);
					cardpoint.card_3 = _card_3;
				}
				showCard.push_back(cardpoint);
				
			}
		}
	}
}

void  AccountsLayer::showFourVer( vector<int> ver[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (!ver[i].empty())
		{
			for (int j = 0; j < ver[i].size(); j++)
			{
				CardPoint cardpoint;
				auto _card_1 = ShowCard::create(i, ver[i].at(j));
				if (_card_1)
				{
					addChild(_card_1);
					cardpoint.card_1 = _card_1;
				}
				j++;
				auto _card_2 = ShowCard::create(i, ver[i].at(j));
				if (_card_2)
				{
					addChild(_card_2);
					cardpoint.card_2 = _card_2;
				}
				j++;
				auto _card_3 = ShowCard::create(i, ver[i].at(j));
				if (_card_3)
				{
					addChild(_card_3);
					cardpoint.card_3 = _card_3;
				}
				j++;
				auto _card_4 = ShowCard::create(i, ver[i].at(j));
				if (_card_4)
				{
					addChild(_card_4);
					cardpoint.card_4 = _card_4;
				}
				showCard.push_back(cardpoint);

			}
		}
	}
}
////一定要优化
void AccountsLayer::showMyCardWall(vector<int> ver[2])
{
	vector<int> mycard[2];
	if (ver[0].size() > 0)
	{
		for (int i = 0; i < ver[0].size(); i++)
		{
			mycard[0].push_back(ver[0].at(i));
		}
	}
	if (ver[1].size() > 0)
	{
		for (int i = 0; i < ver[1].size(); i++)
		{
			mycard[1].push_back(ver[1].at(i));
		}
	}

	if (ver[0].size() > 0)
	{
		for (int k = 0; k < ver[0].size(); k++)
		{
			int count = 0;
			for (int y = 0; y < mycard[0].size(); y++)
			{
				if (ver[0].at(k) == mycard[0].at(y))
				{
					count++;
				}
				else
				{
					continue;
				}
			}
			if (count == 4)
			{
				Card_4[0].push_back(ver[0].at(k));
			}if (count == 3)
			{
				Card_3[0].push_back(ver[0].at(k));
			}
			if (count == 2)
			{
				Card_2[0].push_back(ver[0].at(k));
			}
			if (count == 1)
			{
				Card_1[0].push_back(ver[0].at(k));  
			}
		}
	}
	if (ver[1].size() > 0)
	{
		for (int k = 0; k < ver[1].size(); k++)
		{
			int count = 0;
			for (int y = 0; y < mycard[1].size(); y++)
			{
				if (ver[1].at(k) == mycard[1].at(y))
				{
					count++;
				}
				else
				{
					continue;
				}
			}
			if (count == 4)
			{
				Card_4[1].push_back(ver[1].at(k));
			}if (count == 3)
			{
				Card_3[1].push_back(ver[1].at(k));
			}
			if (count == 2)
			{
				Card_2[1].push_back(ver[1].at(k));
			}
			if (count == 1)
			{
				Card_1[1].push_back(ver[1].at(k));
			}
		}
	}

	showCardPVer();

}

void AccountsLayer::showCardPVer()
{
	if (Card_4[0].size() > 0)
	{
		for (int i = 0; i < Card_4[0].size(); i++)
		{
			CardPoint  cardpoint;
			auto _card_1 = ShowCard::create(0, Card_4[0].at(i));
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;
			}
			i++;
			auto _card_2 = ShowCard::create(0, Card_4[0].at(i));
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			i++;
			auto _card_3 = ShowCard::create(0, Card_4[0].at(i));
			if (_card_3)
			{
				addChild(_card_3);
				cardpoint.card_3 = _card_3;
			}
			i++;
			auto _card_4 = ShowCard::create(0, Card_4[0].at(i));
			if (_card_4)
			{
				addChild(_card_4);
				cardpoint.card_4 = _card_4;
			}
			showCard.push_back(cardpoint);
		}

	}
	if (Card_4[1].size() > 0)
	{
		for (int i = 0; i < Card_4[1].size(); i++)
		{
			CardPoint  cardpoint;
			auto _card_1 = ShowCard::create(1, Card_4[1].at(i));
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;
			}
			i++;
			auto _card_2 = ShowCard::create(1, Card_4[1].at(i));
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			i++;
			auto _card_3 = ShowCard::create(1, Card_4[1].at(i));
			if (_card_3)
			{
				addChild(_card_3);
				cardpoint.card_3 = _card_3;
			}
			i++;
			auto _card_4 = ShowCard::create(1, Card_4[1].at(i));
			if (_card_4)
			{
				addChild(_card_4);
				cardpoint.card_4 = _card_4;
			}
			showCard.push_back(cardpoint);
		}
	}

	if (Card_3[0].size() > 0)
	{
		for (int i = 0; i < Card_3[0].size(); i++)
		{
			CardPoint  cardpoint;
			auto _card_1 = ShowCard::create(0, Card_3[0].at(i)); //*1
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;
			}
			i++;
			auto _card_2 = ShowCard::create(0, Card_3[0].at(i)); //*1
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			i++;
			auto _card_3 = ShowCard::create(0, Card_3[0].at(i)); //*1
			if (_card_3)
			{
				addChild(_card_3);
				cardpoint.card_3 = _card_3;
			}
			showCard.push_back(cardpoint);
		}
	}
	if (Card_3[1].size() > 0)
	{
		for (int i = 0; i < Card_3[1].size(); i++)
		{
			CardPoint  cardpoint;
			auto _card_1 = ShowCard::create(1, Card_3[1].at(i));
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;
			}
			i++;
			auto _card_2 = ShowCard::create(1, Card_3[1].at(i));
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			i++;
			auto _card_3 = ShowCard::create(1, Card_3[1].at(i));
			if (_card_3)
			{
				addChild(_card_3);
				cardpoint.card_3 = _card_3;
			}
			showCard.push_back(cardpoint);
		}
	}
	////liangzhang
	if (Card_2[0].size() > 0)
	{
		for (int i = 0; i < Card_2[0].size(); i++)
		{
			CardPoint cardpoint;
			auto _card_1 = ShowCard::create(0, Card_2[0].at(i));
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;
			}
			i++;
			auto _card_2 = ShowCard::create(0, Card_2[0].at(i));
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			if (i % 2 == 1)
			{
				if (Card_1[1].size() > 0)
				{
					for (auto iter = Card_1[1].begin(); iter != Card_1[1].end();)
					{
						if (*iter == Card_2[0].at(i))
						{
							auto _card = ShowCard::create(1, *iter);
							if (_card)
							{
								addChild(_card);
								cardpoint.card_3 = _card;
							}
							iter = Card_1[1].erase(iter);
						}
						else
						{
							iter++;

						}
					}
				}

			}
			showCard.push_back(cardpoint);
		}
	}
	if (Card_2[1].size() > 0)
	{
		for (int i = 0; i < Card_2[1].size(); i++) //0123 //0
		{
			CardPoint cardpoint;
			auto _card_1 = ShowCard::create(1, Card_2[1].at(i)); //0  
			if (_card_1)
			{
				addChild(_card_1);
				cardpoint.card_1 = _card_1;

			}
			i++;
			auto _card_2 = ShowCard::create(1, Card_2[1].at(i)); //1 3
			if (_card_2)
			{
				addChild(_card_2);
				cardpoint.card_2 = _card_2;
			}
			if (i % 2 == 1)
			{
				if (Card_1[0].size() > 0)
				{
					for (auto iter = Card_1[0].begin(); iter != Card_1[0].end();)
					{
						if (*iter == Card_2[1].at(i))
						{
							auto _card = ShowCard::create(0, *iter);
							if (_card)
							{
								addChild(_card);
								cardpoint.card_3 = _card;
							}
							iter = Card_1[0].erase(iter);
						}
						else
						{
							iter++;
						}
					}
				}

			}
			showCard.push_back(cardpoint);
		}
	}
	if (Card_1[0].size() > 0)
	{
		for (int j = 0; j < Card_1[0].size(); j++)
		{
			CardPoint cardpoint;
			if (j != Card_1[0].size())
			{
				auto _card_1 = ShowCard::create(0, Card_1[0].at(j));
				if (_card_1)
				{
					addChild(_card_1);
					cardpoint.card_1 = _card_1;
				}
				j++;
			}
			if (j != Card_1[0].size())
			{
				auto _card_2 = ShowCard::create(0, Card_1[0].at(j));
				if (_card_2)
				{
					addChild(_card_2);
					cardpoint.card_2 = _card_2;
				}
				j++;
			}
			if (j != Card_1[0].size())
			{
				auto _card_3 = ShowCard::create(0, Card_1[0].at(j));
				if (_card_3)
				{
					addChild(_card_3);
					cardpoint.card_3 = _card_3;
				}
			}
			showCard.push_back(cardpoint);
		}
	}
	if (Card_1[1].size() > 0)
	{
		for (int j = 0; j < Card_1[1].size(); j++)
		{
			CardPoint cardpoint;
			if (j != Card_1[1].size())
			{
				auto _card_1 = ShowCard::create(1, Card_1[1].at(j));
				if (_card_1)
				{
					addChild(_card_1);
					cardpoint.card_1 = _card_1;
				}
				j++;
			}
			if (j != Card_1[1].size())
			{
				auto _card_2 = ShowCard::create(1, Card_1[1].at(j));
				if (_card_2)
				{
					addChild(_card_2);
					cardpoint.card_2 = _card_2;
				}
				j++;
			}
			if (j != Card_1[1].size())
			{
				auto _card_3 = ShowCard::create(1, Card_1[1].at(j));
				if (_card_3)
				{
					addChild(_card_3);
					cardpoint.card_3 = _card_3;
				}
			}
			showCard.push_back(cardpoint);

		}
	}

	/***********************/
	for (int i = 0; i < 2; i++)
	{
		if (!Card_4[i].empty())
		{
			for (int j = 0; j < Card_4[i].size(); j++)
			{
				log("Card_4: t:%d ,v：%d", i, Card_4[i].at(j));
				log("Card_4.size:%d", Card_4[i].size());
			}
		}
		if (!Card_3[i].empty())
		{
			for (int j = 0; j < Card_3[i].size(); j++)
			{
				log("Card_3: t:%d ,v：%d", i, Card_3[i].at(j));
				log("Card_3.size:%d", Card_3[i].size());
			}
		}
		if (!Card_2[i].empty())
		{
			for (int j = 0; j < Card_2[i].size(); j++)
			{
				log("Card_2: t:%d ,v：%d", i, Card_2[i].at(j));
				log("Card_2.size:%d", Card_2[i].size());
			}
		}
		if (!Card_1[i].empty())
		{
			for (int j = 0; j < Card_1[i].size(); j++)
			{
				log("Card_1: t:%d ,v：%d", i, Card_1[i].at(j));
				log("Card_1.size:%d", Card_1[i].size());
			}
		}
	}

}

void AccountsLayer::setCardVerPoint()
{
	for (int i = 0; i < showCard.size(); i++)
	{
		if (showCard.at(i).card_1 != nullptr)
		{
			int height = showCard.at(i).card_1->getContentSize().height;
			int width = showCard.at(i).card_1->getContentSize().width;
			showCard.at(i).card_1->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(110 + width * i, 100)));
			/*addChild(showCard.at(i).card_1);*/
		}
		if (showCard.at(i).card_2 != nullptr)
		{
			int height = showCard.at(i).card_2->getContentSize().height;
			int width = showCard.at(i).card_2->getContentSize().width;
			showCard.at(i).card_2->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(110 + width * i, ((height - 15) * 1)+ 100)));
			/*addChild(showCard.at(i).card_2);*/
		}
		if (showCard.at(i).card_3 != nullptr)
		{
			int height = showCard.at(i).card_3->getContentSize().height;
			int width = showCard.at(i).card_3->getContentSize().width;
			showCard.at(i).card_3->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(110 + width * i, ((height - 15) * 2) + 100)));
			/*addChild(showCard.at(i).card_3);*/
		}
		if (showCard.at(i).card_4 != nullptr)
		{
			int height = showCard.at(i).card_4->getContentSize().height;
			int width = showCard.at(i).card_4->getContentSize().width;
			showCard.at(i).card_4->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2(110 + width * i, ((height - 15) * 3) + 100)));
			/*addChild(showCard.at(i).card_4);*/
		}

	}
}

RepeatForever* AccountsLayer::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.8f, bezier1);

	auto move1 = MoveBy::create(0.8f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.8f, bezier2);
	auto move2 = MoveBy::create(0.8f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}


ParticleSystem* AccountsLayer::particleInit()
{
	auto _emitter = new ParticleSystemQuad();
	_emitter->initWithTotalParticles(50);
	addChild(_emitter, 10);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("particle/point.png"));
	_emitter->setAnchorPoint(Point(0, 0));
	// duration
	_emitter->setDuration(ParticleSystem::DURATION_INFINITY);

	// radius mode
	_emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

	// radius mode: start and end radius in pixels
	_emitter->setStartRadius(4);
	_emitter->setStartRadiusVar(1);
	_emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
	_emitter->setEndRadiusVar(0);

	// radius mode: degrees per second
	_emitter->setRotatePerSecond(100);
	_emitter->setRotatePerSecondVar(0);

	// angle
	_emitter->setAngle(90);
	_emitter->setAngleVar(0);

	// emitter position
	auto size = Director::getInstance()->getWinSize();
	_emitter->setPosVar(Point::ZERO);

	// life of particles
	_emitter->setLife(0.5);
	_emitter->setLifeVar(0);

	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);

	// color of particles
	Color4F startColor(1.0f, 1.0f, 1.0f, 1.0f);
	_emitter->setStartColor(startColor);

	Color4F startColorVar(0, 0, 0, 1.0f);
	_emitter->setStartColorVar(startColorVar);

	Color4F endColor(1.0f, 1.0f, 1.0f, 1.0f);
	_emitter->setEndColor(endColor);

	Color4F endColorVar(0, 0, 0, 0.1f);
	_emitter->setEndColorVar(endColorVar);
	Color4F setStartColor(Color4F(Color4B(50, 50, 50, 50)));
	Color4F setEndColor(Color4F(Color4B(0, 0, 0, 0)));
	// size, in pixels
	_emitter->setStartSize(20);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);

	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

	// additive
	_emitter->setBlendAdditive(false);

	return _emitter;
}

void AccountsLayer::addHZUI(Node* node)
{
	auto add = Label::createWithTTF("+ ", "fonts/Roboto-Medium.ttf", 60);
	if (add)
	{
		/*add->setColor(Color3B::YELLOW);*/
		add->setAnchorPoint(Vec2(0, 0.5));
		add->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, node, Vec2(50, 5)));
		node->addChild(add);
	}
	auto money = Label::createWithBMFont("fonts/baishe.fnt", "0", TextHAlignment::LEFT, 0, Vec2::ZERO);
	if (money)
	{
		money->setAnchorPoint(Vec2(0, 0.7));
		money->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, add, Vec2(20, 0)));
		add->addChild(money);
	}

}
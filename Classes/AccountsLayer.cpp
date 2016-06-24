
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
		m_win->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid,Vec2(0,-90)));
		addChild(m_win);
		auto win = Sprite::create("account/zi_win.png");
		if (win)
		{
			win->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, m_win, Vec2(0, 0)));
			win->setScale(1.5);
			m_win->addChild(win);
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
void AccountsLayer::showWinCard( int player)
{
	//GetLayer::getInstance()->getgameLayer()->t_Player[player]
	vector<ShowCard*> m_PengCardSprite;  //碰牌m_PengCardVec[0]
	vector<ShowCard*> m_KaiDuoCardSprite;  //m_KaiDuoCardVec[0]
	vector<ShowCard*> m_tmpSaoChuanCardSprite;	//m_SaoChuanCardVec[0]
	vector<ShowCard* > m_tmpSaoCardSprite;	//m_SaoCardVec[0]
	vector<ShowCard* > m_tmpChiCardSprite;	//m_ChiCardVec[0]
	vector<ShowCard* > m_ChiSpeclalSprite;//m_ChiSpeclal[2]

	showThreeVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_PengCardVec, m_PengCardSprite); 
	showThreeVer( GetLayer::getInstance()->getgameLayer()->t_Player[player].m_SaoCardVec, m_tmpSaoCardSprite);
	showThreeVer( GetLayer::getInstance()->getgameLayer()->t_Player[player].m_ChiCardVec, m_tmpChiCardSprite);
	showFourVer( GetLayer::getInstance()->getgameLayer()->t_Player[player].m_KaiDuoCardVec, m_KaiDuoCardSprite);
	showFourVer( GetLayer::getInstance()->getgameLayer()->t_Player[player].m_SaoChuanCardVec, m_tmpSaoChuanCardSprite);
	showFourVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].m_ChiSpeclal, m_ChiSpeclalSprite);

	//showThreeCardVer(GetLayer::getInstance()->getgameLayer()->t_Player[player].AAaaCardSprite);

}

void  AccountsLayer::showThreeVer( vector<int> ver[2], vector<ShowCard*> verCard)
{
	if (ver[0].size() > 0)
	{
		for (int i = 0; i < ver[0].size(); i++)
		{
			auto _card = ShowCard::create(0, ver[0][i]);
			if (_card)
			{
				addChild(_card);
				verCard.push_back(_card);
			}
		}
	}
	if (ver[1].size() > 0)
	{
		for (int i = 0; i < ver[1].size(); i++)
		{
			auto _card = ShowCard::create(1, ver[1][i]);
			if (_card)
			{
				addChild(_card);
				verCard.push_back(_card);
			}
		}
	}
	showThreeCardVer(verCard);
}

void  AccountsLayer::showFourVer( vector<int> ver[2], vector<ShowCard*> verCard)
{
	if (ver[0].size() > 0)
	{
		for (int i = 0; i < ver[0].size(); i++)
		{
			auto _card = ShowCard::create(0, ver[0][i]);
			if (_card)
			{
				addChild(_card);
				verCard.push_back(_card);
			}
		}
	}
	if (ver[1].size() > 0)
	{
		for (int i = 0; i < ver[1].size(); i++)
		{
			auto _card = ShowCard::create(1, ver[1][i]);
			if (_card)
			{
				addChild(_card);
				verCard.push_back(_card);
			}
		}
	}
	showFourCardVer(verCard);
}

void  AccountsLayer::showThreeCardVer(vector<ShowCard*> verCard)
{
	if (verCard.size() > 0)
	{
		count++;
		log("count3:%d", count);
		for (int i = 0; i < verCard.size(); i++)
		{
			int _height = verCard.at(i)->getContentSize().height;
			//Vec2((i / 3)*(_height - 8) - 120, i % 3 * (_height - 70) - 60))
			verCard.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 3)*(_height - 8) + (35 * count) + 100, i % 3 * (_height - 70) + 150)));
		}
	}
}

void  AccountsLayer::showFourCardVer(vector<ShowCard*> verCard)
{
	if (verCard.size() > 0)
	{
		count++;
		log("count4:%d", count);
		for (int i = 0; i < verCard.size(); i++)
		{
			int _height = verCard.at(i)->getContentSize().height;
			verCard.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::LeftMid, Vec2((i / 4)*(_height - 8) + (35 * count) + 100, i % 4 * (_height - 70) + 177)));
		}
	}
}
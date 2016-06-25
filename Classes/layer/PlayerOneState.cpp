﻿#include "PlayerOneState.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"
#include "PlayerZeroState.h"
#include "ChooseLayer.h"
#include "GameLayer.h"
#include "layerUtils/ToastLayer/ToastManger.h"
#include "utils/CommonFunction.h"
#include "PlayerZeroState.h"

USING_NS_CC;
#define GAMELAYER  GetLayer::getInstance()->getgameLayer()

PlayerOneState::PlayerOneState()
{
	std::cout << "下家[1]摸牌打牌" << std::endl;
	//检测，起牌

	/*
	
		下家检测我打的牌
		若有牌型，做动作，打一张牌
		若无牌型，摸一张牌
		
		上家只检测我打的牌
		下家只检测他自己摸的牌
		我检测下家，上家摸的牌，打的牌
	*/
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 1);
	if (oneCheck())
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_1);
		GAMELAYER->t_Player[1].delACard(0);
		GAMELAYER->PopPai = GAMELAYER->t_Player[1].popCard;

		//打一张牌，显示出来

		auto _callf_1 = CallFunc::create([](){
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CREATE_CARD);
			ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家打一张牌"));
		});

		auto _callf_2 = CallFunc::create([](){
			GAMELAYER->changeState(new PlayerZeroState());
		});

		auto delay = DelayTime::create(1.5f);

		GAMELAYER->runAction(Sequence::create(delay, _callf_1, _callf_2, nullptr));

		std::cout << "下家打一张牌" << std::endl;
	}
	else
	{
		auto callfunc = CallFunc::create([this](){
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_1);
		});

		auto callfunc_1 = CallFunc::create([this](){
			GAMELAYER->getANewCard();
			myCheck();
		});
		auto delayTime = DelayTime::create(1.5f);
		auto seq = Sequence::create(delayTime, callfunc, delayTime->clone(), callfunc_1, nullptr);
		GAMELAYER->runAction(seq);
	}
}

PlayerOneState::~PlayerOneState()
{

}

void PlayerOneState::Update()
{
	//cocos2d::log("one Update");
}

void PlayerOneState::myCheck()
{
	if (GAMELAYER->checkHu())
	{
		std::cout << "=======胡========" << std::endl;

		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(3);
		chooseLayer->setName(CHOOSELAYER);
	}
	else if (GAMELAYER->checkChongDuo())
	{
		std::cout << "重舵" << std::endl;
	}
	else if (GAMELAYER->checkKaiduo())
	{
		std::cout << "开舵" << std::endl;
	}
	else if (GAMELAYER->checkPeng())
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(2);
		chooseLayer->setName(CHOOSELAYER);
	}
	else
	{
		GAMELAYER->changeState(new PlayerZeroState());
	}
}

bool PlayerOneState::oneCheck()	
{
	/*
	if (GAMELAYER->t_Player[1].checkChongDuo_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家重舵"));
		GAMELAYER->t_Player[1].doChongDuo_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	else if (GAMELAYER->t_Player[1].checkKaiduoACard(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家开舵"));
		GAMELAYER->t_Player[1].doKaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	else if (GAMELAYER->t_Player[1].checkKaiDuo_peng(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家开舵"));
		GAMELAYER->t_Player[1].doPeng_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	*/	
	if (GAMELAYER->t_Player[1].checkPengACard(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家碰"));
		GAMELAYER->t_Player[1].doPengACard(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value);
		//下家显示碰的牌
		GetLayer::getInstance()->getOneLayer()->showPengCard();	//做到这里
		return true;
	}
	else if (GAMELAYER->t_Player[1].checkChiACard2_7_10(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家吃牌"));
		GAMELAYER->t_Player[1].doChi2_7_10(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value,0);
		GetLayer::getInstance()->getOneLayer()->showChiCard();
		return true;


	}else if (GAMELAYER->t_Player[1].checkChiA_B_C(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家吃牌"));
		GAMELAYER->t_Player[1].doChiA_B_C(GAMELAYER->PopPai.m_Type, GAMELAYER->PopPai.m_Value,0);
		GetLayer::getInstance()->getOneLayer()->showChiCard();
		return true;
	}
	return false;
}

void PlayerOneState::zeroCheck()
{
	/*
	if (GAMELAYER->t_Player[0].checkKaiduoACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家开舵"));
		//GAMELAYER->t_Player[0].doKaiDuo(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);
	}
	else if (GAMELAYER->t_Player[0].checkKaiDuo_peng(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家开舵"));
		//GAMELAYER->t_Player[0].doPeng_kaiDuo(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);
	}
	*/
	/*
	if (GAMELAYER->t_Player[0].checkPengACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家碰"));
		GAMELAYER->t_Player[0].doPengACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);
		GetLayer::getInstance()->getZeroLayer()->showPengCard();
	}
	else if (GAMELAYER->t_Player[0].checkChiACard2_7_10(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家吃牌"));
		GAMELAYER->t_Player[0].doChi2_7_10(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value, 0);
		GetLayer::getInstance()->getZeroLayer()->showChiCard();
	}
	else if (GAMELAYER->t_Player[0].checkChiA_B_C(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家吃牌"));
		GAMELAYER->t_Player[0].doChiA_B_C(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value, 0);
		GetLayer::getInstance()->getZeroLayer()->showChiCard();
	}
	*/
}
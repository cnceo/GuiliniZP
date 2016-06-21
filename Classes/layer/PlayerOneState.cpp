#include "PlayerOneState.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"
#include "PlayerZeroState.h"
#include "ChooseLayer.h"
#include "GameLayer.h"
#include "layerUtils/ToastLayer/ToastManger.h"
#include "utils/CommonFunction.h"

USING_NS_CC;
#define GAMELAYER  GetLayer::getInstance()->getgameLayer()

PlayerOneState::PlayerOneState()
{
	std::cout << "下家[1]摸牌打牌" << std::endl;
	//检测，起牌
	oneCheck();
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 1);

	auto callfunc = CallFunc::create([this](){
		GAMELAYER->getANewCard();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_1);

		myCheck();
	});
	auto delayTime = DelayTime::create(1.5f);
	auto seq = Sequence::create(delayTime,callfunc, nullptr);
	GAMELAYER->runAction(seq);
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

void PlayerOneState::oneCheck()	
{
	if (GAMELAYER->t_Player[1].checkChongDuo_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家重舵"));
		GAMELAYER->t_Player[1].doChongDuo_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	else if (GAMELAYER->t_Player[1].checkKaiduoACard(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家开舵"));
		GAMELAYER->t_Player[1].doKaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	else if (GAMELAYER->t_Player[1].checkKaiDuo_peng(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家开舵"));
		GAMELAYER->t_Player[1].doPeng_kaiDuo(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
	}
	else if (GAMELAYER->t_Player[1].checkPengACard(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家碰"));
		GAMELAYER->t_Player[1].doPengACard(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value);
		//下家显示碰的牌
		GetLayer::getInstance()->getOneLayer()->showPengCard();	//做到这里
	}
	else if (GAMELAYER->t_Player[1].checkChiACard2_7_10(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家吃牌"));
		GAMELAYER->t_Player[1].doChi2_7_10(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value,0);

	}else if (GAMELAYER->t_Player[1].checkChiA_B_C(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value))
	{
		ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"下家吃牌"));
		GAMELAYER->t_Player[1].doChiA_B_C(GAMELAYER->PopPai[2].m_Type, GAMELAYER->PopPai[2].m_Value,0);
	}
}

void PlayerOneState::zeroCheck()
{

}
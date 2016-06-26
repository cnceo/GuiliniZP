#include "PlayerZeroState.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"
#include "ChooseLayer.h"
#include "PlayerTwoState.h"
#include "GameLayer.h"
#include "utils/CommonFunction.h"
#include "layerUtils/ToastLayer/ToastManger.h"

USING_NS_CC;

#define GAMELAYER  GetLayer::getInstance()->getgameLayer()

PlayerZeroState::PlayerZeroState()
{
	std::cout << "上家[0]摸牌打牌" << std::endl;
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);

	auto callfunc = CallFunc::create([this](){
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_0);
	});

	auto callfunc_1 = CallFunc::create([this](){
		GAMELAYER->getANewCard();

		if (myCheck())
		{
			std::cout << "我有操作" << std::endl;
		}
		else if (zeroCheck())
		{
			GAMELAYER->t_Player[0].delACard(0);
			GAMELAYER->PopPai = GAMELAYER->t_Player[0].popCard;

			//打一张牌，显示出来

			auto _callf_1 = CallFunc::create([](){
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CREATE_CARD);
				//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家打一张牌"));

			});

			auto _callf_2 = CallFunc::create([](){
				GAMELAYER->changeState(new PlayerTwoState());
			});
			auto delay = DelayTime::create(1.5f);
			GAMELAYER->runAction(Sequence::create(delay, _callf_1, _callf_2, nullptr));
		}
		else
		{
			auto delay = DelayTime::create(1.5f);
			auto _callf = CallFunc::create([](){
				GAMELAYER->changeState(new PlayerTwoState());
			});
			GAMELAYER->runAction(Sequence::create(delay, _callf, nullptr));

		}

	});

	auto delayTime = DelayTime::create(1.5f);
	auto seq = Sequence::create(delayTime, callfunc, delayTime->clone(), callfunc_1, nullptr);
	GAMELAYER->runAction(seq);
}

PlayerZeroState::~PlayerZeroState()
{

}

void PlayerZeroState::Update()
{
	//cocos2d::log("zero Update");
}

bool PlayerZeroState::myCheck()
{
	if (GAMELAYER->checkHu())
	{
		std::cout << "=======胡========" << std::endl;

		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(3);
		chooseLayer->setName(CHOOSELAYER);
		return true;
	}
	else if (GAMELAYER->checkChongDuo())
	{
		std::cout << "重舵" << std::endl;
		return true;
	}
	else if (GAMELAYER->checkKaiduo())
	{
		std::cout << "开舵" << std::endl;
		return true;
	}
	else if (GAMELAYER->checkChi() && GAMELAYER->checkPeng())//可吃可碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(4);
		chooseLayer->setName(CHOOSELAYER);
		return true;
	}
	else if (GAMELAYER->checkChi() && !GAMELAYER->checkPeng())	//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(1);
		chooseLayer->setName(CHOOSELAYER);
		return true;
	}
	else if (!GAMELAYER->checkChi() && GAMELAYER->checkPeng())//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(2);
		chooseLayer->setName(CHOOSELAYER);
		return true;
	}
	return false;
}

bool PlayerZeroState::zeroCheck()
{
	//if (GAMELAYER->t_Player[0].checkKaiduoACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	//{
	//	//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家开舵"));
	//	//GAMELAYER->t_Player[0].doKaiDuo(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);

	//}
	//else if (GAMELAYER->t_Player[0].checkKaiDuo_peng(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	//{
	//	//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家开舵"));
	//	//GAMELAYER->t_Player[0].doPeng_kaiDuo(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);
	//}
	
	if (GAMELAYER->t_Player[0].checkPengACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家碰"));
		GAMELAYER->t_Player[0].doPengACard(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value);
		GetLayer::getInstance()->getZeroLayer()->showPengCard();
		return true;
	}
	else if (GAMELAYER->t_Player[0].checkChiACard2_7_10(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家吃牌"));
		GAMELAYER->t_Player[0].doChi2_7_10(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value, 0);
		GetLayer::getInstance()->getZeroLayer()->showChiCard();
		return true;
	}
	else if (GAMELAYER->t_Player[0].checkChiA_B_C(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value))
	{
		//ToastManger::getInstance()->createToast(CommonFunction::WStrToUTF8(L"上家吃牌"));
		GAMELAYER->t_Player[0].doChiA_B_C(GAMELAYER->m_newCard.m_Type, GAMELAYER->m_newCard.m_Value, 0);
		GetLayer::getInstance()->getZeroLayer()->showChiCard();
		return true;
	}
	return false;
}
#include "PlayerTwoState.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"
#include "ChooseLayer.h"
#include "PlayerOneState.h"
#include "GameLayer.h"

USING_NS_CC;

#define GAMELAYER  GetLayer::getInstance()->getgameLayer()

PlayerTwoState::PlayerTwoState()
{
	std::cout << "我[2]摸牌打牌" << std::endl;
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 2);
	if (!UserDefault::getInstance()->getBoolForKey(ISFIRSTPLAY))
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_2);
		/*
			false:庄家，第一次打牌，不摸牌
			true:第二圈开始，摸牌
		*/
		std::cout << "第一次打牌，不摸牌" << std::endl;
	}
	else
	{
		if (UserDefault::getInstance()->getBoolForKey(ISGETORPLAY))
		{
			//摸牌不打牌
			auto callfunc = CallFunc::create([](){
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_2);
			});

			auto callfunc_1 = CallFunc::create([this](){
				GAMELAYER->getANewCard();
				myCheck();
			});
			auto delayTime = DelayTime::create(1.5f);
			auto delayTime_1 = DelayTime::create(0.8f);
			auto seq = Sequence::create(delayTime, callfunc, delayTime_1, callfunc_1, nullptr);
			GAMELAYER->runAction(seq);
		}
		else
		{
			//打牌不摸牌
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_2);
			GetLayer::getInstance()->getgameLayer()->setActionVisible(true);
		}
	}
}

PlayerTwoState::~PlayerTwoState()
{

}

void PlayerTwoState::Update()
{
	//cocos2d::log("two Update");

	//GetLayer::getInstance()->getgameLayer()->logAllCard();
}

void PlayerTwoState::myCheck()
{
	if (GAMELAYER->checkHu())
	{
		std::cout << "=======胡========" << std::endl;

		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(3);
		chooseLayer->setName(CHOOSELAYER);
	}
	else if(GAMELAYER->checkChongDuo())
	{
		std::cout << "重舵" << std::endl;
	}
	else if (GAMELAYER->checkSaochuan())
	{
		std::cout << "扫穿" << std::endl;
	}
	else if (GAMELAYER->checkKaiduo())
	{
		std::cout << "开舵" << std::endl;
	}		
	//else if (true)	//过扫 (可碰未碰)
	//{

	//}
	else if (GAMELAYER->checkSao())
	{
		std::cout << "扫" << std::endl;
	}
	else if (GAMELAYER->checkChi() && GAMELAYER->checkPeng())//可吃可碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(4);
		chooseLayer->setName(CHOOSELAYER);
	}
	else if (GAMELAYER->checkChi() && !GAMELAYER->checkPeng())	//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(1);
		chooseLayer->setName(CHOOSELAYER);
	}
	else if (!GAMELAYER->checkChi() && GAMELAYER->checkPeng())//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(2);
		chooseLayer->setName(CHOOSELAYER);
	}
	else
	{
		//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(SHOW_QIPAI);
		GAMELAYER->changeState(new PlayerOneState());
	}
}
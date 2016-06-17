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
			auto callfunc = CallFunc::create([this](){
				GAMELAYER->getANewCard();
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_2);

				myCheck();
			});
			auto delayTime = DelayTime::create(1.5f);
			auto seq = Sequence::create(delayTime, callfunc, nullptr);
			GAMELAYER->runAction(seq);
		}
		else
		{
			//打牌不摸牌
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_2);
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
	if (GAMELAYER->checkChongDuo())
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
	}
	else if (GAMELAYER->checkChi() && !GAMELAYER->checkPeng())	//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(1);
	}
	else if (!GAMELAYER->checkChi() && GAMELAYER->checkPeng())//可吃不能碰
	{
		auto chooseLayer = ChooseLayer::create();
		GAMELAYER->addChild(chooseLayer);
		chooseLayer->setBtnEnable(2);
	}
	else
	{
		GAMELAYER->changeState(new PlayerOneState());
	}
}
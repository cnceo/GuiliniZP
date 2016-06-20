#include "PlayerZeroState.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"
#include "ChooseLayer.h"
#include "PlayerTwoState.h"
#include "GameLayer.h"

USING_NS_CC;

#define GAMELAYER  GetLayer::getInstance()->getgameLayer()

PlayerZeroState::PlayerZeroState()
{
	std::cout << "上家[0]摸牌打牌" << std::endl;
	UserDefault::getInstance()->setIntegerForKey(GAMESTATE, 0);

	auto callfunc = CallFunc::create([this](){
		GAMELAYER->getANewCard();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PLAYERBLINK_0);

		myCheck();
	});
	auto delayTime = DelayTime::create(1.5f);
	auto seq = Sequence::create(delayTime, callfunc, nullptr);
	GAMELAYER->runAction(seq);
}

PlayerZeroState::~PlayerZeroState()
{

}

void PlayerZeroState::Update()
{
	//cocos2d::log("zero Update");
}

void PlayerZeroState::myCheck()
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
		GAMELAYER->changeState(new PlayerTwoState());
	}
}
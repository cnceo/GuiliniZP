#include "CardEffect.h"
#include "Card/CardSprite.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"

#define GAMELAYER GetLayer::getInstance()->getgameLayer()

CardEffect::CardEffect():
_dangDi(nullptr), 
_timeCount(nullptr)
{
	auto _listener_1 = EventListenerCustom::create(SHOW_TIMECOUNT, [=](EventCustom*event){
		showTimeCount();
	});

	auto _listener_2 = EventListenerCustom::create(HIDE_TIMECOUNT, [=](EventCustom*event){
		hideTimeCount();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
}

CardEffect::~CardEffect()
{
	_eventDispatcher->removeCustomEventListeners(SHOW_TIMECOUNT);
	_eventDispatcher->removeCustomEventListeners(HIDE_TIMECOUNT);
}

bool CardEffect::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_midIndex = 0;
	_ritIndex = 0;
	_leftIndex = 0;

	_SumTime_1 = 0;
	_SumTime_2 = 0;
	_SumTime_3 = 0;

	_isActoin_1 = false;
	_isActoin_2 = false;
	_isActoin_3 = false;

	scheduleUpdate();

	for (int i = 0; i < 16;i++)
	{
		auto _card_1 = Sprite::create("card_back.png");
		if (_card_1)
		{
			addChild(_card_1);
			_card_1->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(0, 0)));
			_card_1->setScale(0.8f);
			_cardList_1.pushBack(_card_1);
			_card_1->setOpacity(0);
		}

		auto _card_2 = Sprite::create("card_back.png");
		if (_card_2)
		{
			addChild(_card_2);
			_card_2->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(_card_2->getContentSize().width + 40, -_card_2->getContentSize().width / 2 - 30)));
			_card_2->setScale(0.8f);
			_cardList_2.pushBack(_card_2);
			_card_2->setRotation(90.0f);
			_card_2->setOpacity(0);
		}

		auto _card_3 = Sprite::create("card_back.png");
		if (_card_3)
		{
			addChild(_card_3);
			_card_3->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(-_card_2->getContentSize().width - 40, -_card_3->getContentSize().width / 2 - 30)));
			_card_3->setScale(0.8f);
			_cardList_3.pushBack(_card_3);
			_card_3->setRotation(90.0f);
			_card_3->setOpacity(0);
		}

	}

	auto callfunc = CallFunc::create([=](){ 
		_isActoin_1 = true;
		_isActoin_2 = true;
		_isActoin_3 = true;

	});
	auto delay = DelayTime::create(1.0f);
	this->runAction(Sequence::create(delay, callfunc, nullptr));

	showDangdi();
	return true;
}

void CardEffect::midAction()
{
	if (!_cardList_1.empty())
	{
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 100)));
		auto fadeOut = FadeOut::create(0.5f);
		auto fadeIn = FadeIn::create(0.1f);
		auto spawn = Spawn::create(moveTo, fadeOut, nullptr);
		auto seq = Sequence::create(fadeIn, spawn, nullptr);

		if (_midIndex < _cardList_1.size())
		{
			_cardList_1.at(_midIndex)->runAction(seq);
			_midIndex++;
		}
		else
		{
			_isActoin_1 = false;
			_midIndex = 0;
		}
	}
}

void CardEffect::update(float dt)
{
	if (_isActoin_1)
	{
		_SumTime_1 += dt;
		if (_SumTime_1 > 0.11)
		{
			midAction();
			_SumTime_1 = 0;
		}
	}

	if (_isActoin_2)
	{
		_SumTime_2 += dt;
		if (_SumTime_2 > 0.11)
		{
			rightActoin();
			_SumTime_2 = 0;
		}
	}

	if (_isActoin_3)
	{
		_SumTime_3 += dt;
		if (_SumTime_3 > 0.11)
		{
			leftAcrion();
			_SumTime_3 = 0;
		}
	}
}

void CardEffect::rightActoin()
{
	if (!_cardList_2.empty())
	{
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(250, -_cardList_2.at(0)->getContentSize().width / 2 -30)));
		auto fadeOut = FadeOut::create(0.5f);
		auto fadeIn = FadeIn::create(0.1f);
		auto spawn = Spawn::create(moveTo, fadeOut, nullptr);
		auto seq = Sequence::create(fadeIn,spawn,nullptr);
		if (_ritIndex < _cardList_2.size())
		{
			_cardList_2.at(_ritIndex)->runAction(seq);
			_ritIndex++;
		}
		else
		{
			_isActoin_2 = false;
			_ritIndex = 0;
		}
	}
}

void CardEffect::leftAcrion()
{
	if (!_cardList_3.empty())
	{
		auto moveTo = MoveTo::create(0.5f, CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(-250, -_cardList_3.at(0)->getContentSize().width / 2 - 30)));
		auto fadeOut = FadeOut::create(0.5f);
		auto fadeIn = FadeIn::create(0.1f);
		auto spawn = Spawn::create(moveTo, fadeOut, nullptr);
		auto seq = Sequence::create(fadeIn, spawn, nullptr);

		if (_leftIndex < _cardList_2.size())
		{
			_cardList_3.at(_leftIndex)->runAction(seq);
			_leftIndex++;
		}
		else
		{
			_isActoin_3 = false;
			_leftIndex = 0;
		}
	}
}

void CardEffect::showDangdi()
{
	//_dangDi = Label::create(CommonFunction::WStrToUTF8(L"档底"),"fonts/DFYuanW7.ttf",80);
	_dangDi = Sprite::create("dangdi.png");
	if (_dangDi)
	{
		addChild(_dangDi);
		_dangDi->setPosition(CommonFunction::getVisibleAchor(0.2,0.5,Vec2(0,-40)));
		_dangDi->setVisible(false);

		auto delay = DelayTime::create(3.0f);
		auto call_1 = CallFunc::create([=](){_dangDi->setVisible(true); });
		auto scaleTo_1 = ScaleTo::create(0.5f,1.5f);
		auto scaleTo_2 = ScaleTo::create(0.3f, 1.0f);
		auto fadeout = FadeOut::create(0.3f);
		auto call_3 = CallFunc::create([=](){getDangdi();});
		auto seq = Sequence::create(delay, call_1, scaleTo_1, scaleTo_2, fadeout, call_3, nullptr);

		_dangDi->runAction(seq);
	}
}

void  CardEffect::getDangdi()
{
	auto delay = DelayTime::create(0.2f);
	auto call_1 = CallFunc::create([=](){GAMELAYER->getANewCard();});
	auto delay_1 = DelayTime::create(0.2f);
	auto call_2 = CallFunc::create([=](){
		GetLayer::getInstance()->getShowLayer()->flyToHand();
	});
	auto seq = Sequence::create(delay, call_1, delay_1,call_2, nullptr);
	runAction(seq);
}

void CardEffect::showTimeCount()
{
	schedule(schedule_selector(CardEffect::refrishTimeCount), 1.0f);

	_timeCt = 3;
	_timeCount = Label::createWithBMFont("fonts/baishe.fnt", Value(_timeCt).asString(), TextHAlignment::LEFT,0,Vec2::ZERO);
	if (_timeCount)
	{
		_timeCount->setColor(Color3B::WHITE);
		_timeCount->setVisible(true);
		_timeCount->setSystemFontSize(80);
		addChild(_timeCount);
		_timeCount->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(-100,70)));

		auto ease_1 = EaseSineOut::create(ScaleTo::create(0.3f, 2.0f));
		auto ease_2 = EaseSineOut::create(ScaleTo::create(0.1f, 1.0f));
		auto seq = Sequence::create(ease_1, ease_2, nullptr);
		_timeCount->runAction(seq);
	}
}

void CardEffect::refrishTimeCount(float dt)
{
	_timeCt--;
	if (_timeCt <= 0 )
	{
		if (_timeCount)
		{
			_timeCount->setVisible(false);
			_timeCount->removeFromParent();
			_timeCount = nullptr;
		}
		unschedule(schedule_selector(CardEffect::refrishTimeCount));
		return;
	}

	if (_timeCount)
	{
		_timeCount->setString(Value(_timeCt).asString());
		auto ease_1 = EaseSineOut::create(ScaleTo::create(0.3f, 2.0f));
		auto ease_2 = EaseSineOut::create(ScaleTo::create(0.1f, 1.0f));
		auto seq = Sequence::create(ease_1, ease_2, nullptr);
		_timeCount->runAction(seq);
	}
}

void CardEffect::hideTimeCount()
{
	if (_timeCount)
	{
		_timeCount->setVisible(false);
	}
}
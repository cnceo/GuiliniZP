#include "CardEffect.h"
#include "Card/CardSprite.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"

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

	for (int i = 0; i < 15;i++)
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
		if (_SumTime_1 > 0.07)
		{
			midAction();
			_SumTime_1 = 0;
		}
	}

	if (_isActoin_2)
	{
		_SumTime_2 += dt;
		if (_SumTime_2 > 0.07)
		{
			rightActoin();
			_SumTime_2 = 0;
		}
	}

	if (_isActoin_3)
	{
		_SumTime_3 += dt;
		if (_SumTime_3 > 0.07)
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
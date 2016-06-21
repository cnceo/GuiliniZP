#include "ShowCard.h"

ShowCard::ShowCard()
{
}

ShowCard::~ShowCard()
{
}

ShowCard* ShowCard::create(int p_Type, int p_Value)
{
	ShowCard *pRet = new(std::nothrow) ShowCard();
	if (pRet && pRet->init(p_Type, p_Value))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool ShowCard::init(int p_Type, int p_Value)
{
	if (!Sprite::init())
	{
		return false;
	}

	Sprite* _card = nullptr;

	if (p_Type == 0)
	{
		_card = Sprite::create(StringUtils::format("xiaopai_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		_card = Sprite::create(StringUtils::format("xiaopai_d%0d.png", p_Value));
	}

	if (_card)
	{
		_card->setScale(0.7f);
		addChild(_card);
		this->setContentSize(_card->getContentSize());
	}
	return true;
}

void ShowCard::onEnter()
{
	Sprite::onEnter();

	auto listenerEvent = EventListenerTouchOneByOne::create();
	listenerEvent->onTouchBegan = CC_CALLBACK_2(ShowCard::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(ShowCard::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(ShowCard::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);
}

bool ShowCard::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ShowCard::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void ShowCard::onTouchEnded(Touch *touch, Event *unused_event)
{

}

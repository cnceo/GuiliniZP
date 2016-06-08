#include "CardSprite.h"

CardSprite::CardSprite()
{

}

CardSprite::~CardSprite()
{

}
CardSprite* CardSprite::create(int type, int value)
{
	CardSprite *pRet = new(std::nothrow) CardSprite();
	if (pRet && pRet->init(type, value))
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = nullptr; 
		return nullptr; 
	} 
	return nullptr;
}

bool	CardSprite::init(int type, int value)
{
	if (!Node::init())
	{
		return false;
	}
	_cardData.m_Type = type;
	_cardData.m_Value = value;

	initUI(type, value);

	this->setState(CardSprite::CardState::ONTouch);		//都能触摸

	return true;
}

void CardSprite::initUI(int type, int value)
{
	Sprite *card;
	if (type == 0)
	{
		card = Sprite::create(StringUtils::format("chang_x%d.png", value));
		card->setScale(0.6f);
	}
	else if (type == 1)
	{
		card = Sprite::create(StringUtils::format("chang_d%d.png", value));
		card->setScale(0.6f);
	}
	addChild(card);

	this->setContentSize(card->getContentSize() *0.6f);
}

CardData*	CardSprite::getCardData()
{
	return &_cardData;
}
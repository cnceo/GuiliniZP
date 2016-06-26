#include "ShortCardSprite.h"

ShortCardSprite::ShortCardSprite()
{

}

ShortCardSprite::~ShortCardSprite()
{

}
ShortCardSprite* ShortCardSprite::create(int type, int value)
{
	ShortCardSprite *pRet = new(std::nothrow) ShortCardSprite();
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

bool	ShortCardSprite::init(int type, int value)
{
	if (!Node::init())
	{
		return false;
	}
	_cardData.m_Type = type;
	_cardData.m_Value = value;

	initUI(type, value);

	this->setState(ShortCardSprite::CardState::ONTouch);		//都能触摸
	this->setsortState(ShortCardSprite::SortState::ONE_CARD);//默认单张牌

	return true;
}

void ShortCardSprite::initUI(int type, int value)
{
	Sprite *card;
	if (type == 0)
	{
		card = Sprite::create(StringUtils::format("duanpai_x%d.png", value));
		card->setScale(0.6f);
	}
	else if (type == 1)
	{
		card = Sprite::create(StringUtils::format("duanpai_d%d.png", value));
		card->setScale(0.6f);
	}
	addChild(card);

	this->setContentSize(card->getContentSize() *0.6f);
}

CardData*	ShortCardSprite::getCardData()
{
	return &_cardData;
}

void ShortCardSprite::setCardOpacity(GLubyte opacity)
{
	for (auto &_child : getChildren())
	{
		_child->setOpacity(opacity);
	}
}
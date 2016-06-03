#pragma once

#include	"cocos2d.h"
#include	"ZiPai.h"

USING_NS_CC;

//一张牌
class CardSprite : public Node
{
public:

	CardSprite();
	~CardSprite();

	static CardSprite* create(int type, int value);
	virtual bool	init(int type, int value);

	void initUI(int type, int value);
public:
	 CardData*	getCardData();

private:
	CardData	_cardData;
};
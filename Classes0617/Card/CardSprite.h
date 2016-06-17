#pragma once

#include	"cocos2d.h"
#include	"ZiPai.h"

USING_NS_CC;

//一张牌
class CardSprite : public Node
{
public:

	enum CardState
	{
		ONTouch,		//能打
		OFFTouch		//不能打
	};

	CardSprite();
	~CardSprite();

	static CardSprite* create(int type, int value);
	virtual bool	init(int type, int value);

	void initUI(int type, int value);

	CC_SYNTHESIZE(CardState,_state,State);
public:
	 CardData*	getCardData();

private:
	CardData	_cardData;
};
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

	enum SortState
	{
		FOUR_CARD,			//四张相同
		THREE_SAME_CARD,	//三张相同
		THREE_DIFF_CARD,	//三张不同
		TWO_CARD,			//两张相同
		ONE_CARD			//单张
	};

	CardSprite();
	~CardSprite();

	static CardSprite* create(int type, int value);
	virtual bool	init(int type, int value);

	void initUI(int type, int value);
	void setCardOpacity(GLubyte opacity);

	CC_SYNTHESIZE(CardState, _state, State);
	CC_SYNTHESIZE(SortState, _sortState, sortState);

public:
	 CardData*	getCardData();

private:
	CardData	_cardData;
};
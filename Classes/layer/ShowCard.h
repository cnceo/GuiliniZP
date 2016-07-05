#pragma once

#include "cocos2d.h"

using namespace cocos2d;
/*
	显示的小牌
*/
class ShowCard : public Sprite
{
public:

	enum ISSAO
	{
		YES,
		NO
	};

	ShowCard();
	~ShowCard();
	static ShowCard* create(int p_Type, int p_Value);
	bool init(int p_Type, int p_Value);
	virtual void onEnter();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	void setCardState(ISSAO _state);
	ISSAO getCardState();
	void turnToBack();

private:
	ISSAO _issao;
};
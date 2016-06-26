#pragma once

#include "cocos2d.h"

USING_NS_CC;
/*
发牌效果
*/
class CardSprite;

class CardEffect : public Layer
{
public:
	CardEffect();
	~CardEffect();

	virtual bool init();
	CREATE_FUNC(CardEffect);
	virtual void update(float dt);
public:
	void midAction();
	void rightActoin();
	void leftAcrion();

	void showDangdi();		//档低字体显示
	void getDangdi();		//显示档低的牌

	void showTimeCount();	//显示倒计时
	void refrishTimeCount(float dt);
	void hideTimeCount();

private:
	Vector<Sprite*> _cardList_1;
	Vector<Sprite*> _cardList_2;
	Vector<Sprite*> _cardList_3;

	int _midIndex;
	int _leftIndex;
	int _ritIndex;
	int _timeCt;

	float _SumTime_1;
	float _SumTime_2;
	float _SumTime_3;

	bool _isActoin_1;
	bool _isActoin_2;
	bool _isActoin_3;

	Sprite* _dangDi;
	Label* _timeCount;
};

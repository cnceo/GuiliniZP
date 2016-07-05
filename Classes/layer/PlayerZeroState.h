#pragma once 

#include "StateManager.h"
#include "cocos2d.h"

class PlayerZeroState : public StateManager
{
public:
	PlayerZeroState();
	~PlayerZeroState();

	virtual void Update();
	bool myCheck();
	bool zeroCheck();
	bool myCheckZeroPop();	//我检测上家打出的牌
	bool checkChi();		//检测吃上家的牌
	bool checkPeng();		//检测碰上家打的牌
};

#pragma once 

#include "StateManager.h"
#include "cocos2d.h"

class PlayerZeroState : public StateManager
{
public:
	PlayerZeroState();
	~PlayerZeroState();

	virtual void Update();
	void myCheck();
};

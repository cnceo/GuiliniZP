#pragma once 

#include "StateManager.h"
#include "cocos2d.h"

class PlayerTwoState : public StateManager
{
public:
	PlayerTwoState();
	~PlayerTwoState();

	virtual void Update();
	void myCheck();
};

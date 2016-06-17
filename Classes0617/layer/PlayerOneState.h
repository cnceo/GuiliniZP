#pragma once 

#include "StateManager.h"
#include "cocos2d.h"

class PlayerOneState : public StateManager
{
public:

	PlayerOneState();
	~PlayerOneState();

	virtual void Update();
	void myCheck();
};

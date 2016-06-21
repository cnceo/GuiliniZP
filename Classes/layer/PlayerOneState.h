#pragma once 

#include "StateManager.h"
#include "cocos2d.h"

class PlayerOneState : public StateManager
{
public:

	PlayerOneState();
	~PlayerOneState();

	virtual void Update();

	void myCheck();			//我检测
	void oneCheck();		//下家检测
	void zeroCheck();		//上家检测
};

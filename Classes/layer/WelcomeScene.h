#pragma once

#include "cocos2d.h"
using namespace cocos2d;

/*
欢迎场景
*/

class WelcomeScene :public Layer
{
public:

	WelcomeScene();
	~WelcomeScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
public:
	void initUI();
};


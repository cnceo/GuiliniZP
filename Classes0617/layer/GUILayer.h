#pragma once

#include "cocos2d.h"
using namespace cocos2d;

/*
ui显示层 玩家信息等
*/

class GUILayer :public Layer
{
public:

	GUILayer();
	~GUILayer();

	virtual bool init();
	CREATE_FUNC(GUILayer);

private:

	void initData();
	void initUI();

	void playerBlink_0();
	void playerBlink_1();
	void playerBlink_2();
private:
	Sprite* icon_left;
	Sprite* icon_leftDown;
	Sprite* icon_right;
};


﻿#pragma once

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

private:

};


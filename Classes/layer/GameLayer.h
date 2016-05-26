#pragma once

#include "cocos2d.h"
#include "ZiPai.h"
#include "ZiPaiManage.h"

using namespace cocos2d;

class GameLayer :public Layer
{
public:

	GameLayer();
	~GameLayer();

	virtual bool init();
	CREATE_FUNC(GameLayer);

private:

	void initData();

	void initUI();

};


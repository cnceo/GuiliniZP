#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;

/*
	返回层
*/

class BackLayer :public Pop
{
public:

	BackLayer();
	~BackLayer();

	virtual bool init();
	CREATE_FUNC(BackLayer);

private:
	void initData();
	void initUI();

};


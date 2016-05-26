#pragma once

#include "cocos2d.h"

using namespace cocos2d;

/*
菜单选择层
*/

class ChooseLayer :public Layer
{
public:

	ChooseLayer();
	~ChooseLayer();

	virtual bool init();
	CREATE_FUNC(ChooseLayer);

private:

	void initData();

	void initUI();

};


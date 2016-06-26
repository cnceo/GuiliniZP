#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;

class SettingLayer :public Pop
{
public:

	SettingLayer();
	~SettingLayer();

	virtual bool init();
	CREATE_FUNC(SettingLayer);

private:
	void initUI();

};


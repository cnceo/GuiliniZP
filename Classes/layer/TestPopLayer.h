#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"
using namespace cocos2d;

class TestPopLayer :public Pop
{
public:

	TestPopLayer();
	~TestPopLayer();

	virtual bool init();
	CREATE_FUNC(TestPopLayer);

private:

	void initData();
	void initUI();

private:

};


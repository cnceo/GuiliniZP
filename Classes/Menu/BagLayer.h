#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;

class BagLayer :public Pop
{
public:

	BagLayer();
	~BagLayer();

	virtual bool init();
	CREATE_FUNC(BagLayer);

private:
	void initUI();

};


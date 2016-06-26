#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;

class ShopLayer :public Pop
{
public:

	ShopLayer();
	~ShopLayer();

	virtual bool init();
	CREATE_FUNC(ShopLayer);

private:
	void initUI();

};


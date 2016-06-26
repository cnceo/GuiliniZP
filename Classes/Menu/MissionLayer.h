#pragma once

#include "cocos2d.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;

class MissionLayer :public Pop
{
public:

	MissionLayer();
	~MissionLayer();

	virtual bool init();
	CREATE_FUNC(MissionLayer);

private:
	void initUI();

};


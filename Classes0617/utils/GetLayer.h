#pragma once
#include "cocos2d.h"
#include "../layer/GameLayer.h"

class GetLayer
{
public:

	static GetLayer* getInstance();
	bool purgeInstance();

	void setgameLayer(GameLayer* _gLayer);
	GameLayer* getgameLayer();

private:
	GetLayer();
	~GetLayer();
	static GetLayer* _instance;
	GameLayer* _gameLayer;
};

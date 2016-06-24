#pragma once
#include "cocos2d.h"
#include "../layer/GameLayer.h"
#include "../layer/ShowOneLayer.h"
#include "../layer/ShowZeroLayer.h"

class GetLayer
{
public:

	static GetLayer* getInstance();
	bool purgeInstance();

	void setgameLayer(GameLayer* _gLayer);
	GameLayer* getgameLayer();

	void setOneLayer(ShowOneLayer* _sLayer);
	ShowOneLayer* getOneLayer();

	void setZeroLayer(ShowZeroLayer* _sLayer);
	ShowZeroLayer* getZeroLayer();

private:
	GetLayer();
	~GetLayer();
	static GetLayer* _instance;
	GameLayer* _gameLayer;
	ShowOneLayer* _oneLayer;
	ShowZeroLayer* _zeroLayer;
};

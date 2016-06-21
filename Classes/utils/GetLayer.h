#pragma once
#include "cocos2d.h"
#include "../layer/GameLayer.h"
#include "../layer/ShowOneLayer.h"

class GetLayer
{
public:

	static GetLayer* getInstance();
	bool purgeInstance();

	void setgameLayer(GameLayer* _gLayer);
	GameLayer* getgameLayer();

	void setOneLayer(ShowOneLayer* _sLayer);
	ShowOneLayer* getOneLayer();
private:
	GetLayer();
	~GetLayer();
	static GetLayer* _instance;
	GameLayer* _gameLayer;
	ShowOneLayer* _oneLayer;
};

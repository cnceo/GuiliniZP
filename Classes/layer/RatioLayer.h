#pragma once

#include "cocos2d.h"
#include "ZiPaiManage.h"
#include "layer/GameLayer.h"

#include "utils/RunNumLabel.h"

using namespace cocos2d;

/*
	翻醒
*/
class RatioLayer : public Layer
{
public:
	RatioLayer();
	~RatioLayer();

	virtual bool init(GameLayer* _layer);
	static RatioLayer* create(GameLayer* _layer);

public:

	void AddUI();

	void checkRatio();

private:
	GameLayer* _gameLayer;

	int ratioNum;

	static int count;

	RunNumLabel* runNumber;
};

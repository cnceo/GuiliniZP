#pragma once

#include "cocos2d.h"
using namespace cocos2d;

/*
	显示吃的牌
*/

class GameLayer;

class ChiCardLayer :public Layer
{
public:

	ChiCardLayer();
	~ChiCardLayer();

	virtual void onEnter();

	virtual bool init(GameLayer* _layer);
	static ChiCardLayer* create(GameLayer* _layer);

private:

	void initData();
	void initUI();

	Sprite* createSmallCardSprite(int p_Type, int p_Value);

private:
	GameLayer* _gameLayer;
	Vector<Sprite* > m_tmpChiCardList;
};


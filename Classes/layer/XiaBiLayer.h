#pragma once

#include "cocos2d.h"
#include "ZiPai.h"
#include "ShowCard.h"
#include "ChiCardLayer.h"

using namespace cocos2d;

/*
	显示下比的牌
*/

class XiaBiLayer :public Layer
{
public:

	XiaBiLayer();
	~XiaBiLayer();

	virtual void onEnter();

	virtual bool init(ChiCardLayer* _layer);
	static XiaBiLayer* create(ChiCardLayer* _layer);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

private:

	void initData();
	void initUI();
	void checkXiabi();	//检测下比

private:
	ChiCardLayer* _ChiLayer;
};

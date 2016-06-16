#pragma once

#include "cocos2d.h"  
/*
	旋转菜单
*/

class RotateMenu :public cocos2d::Layer
{
public:
	CREATE_FUNC(RotateMenu);
	//添加菜单项  
	void addMenuItem(cocos2d::MenuItem *item);
	void updatePosition();
	void updatePositionWithAnimation();
	//true 为正向  false 负  
	void rectify(bool forward);
	virtual bool init();
	void reset();

private:
	void setAngle(float angle);
	float getAngle();
	void setUnitAngle(float angle);
	float getUnitAngle();
	float disToAngle(float dis);
	cocos2d::MenuItem * getCurrentItem();

	void actionEndCallBack(float dx);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	float _angle;
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	float _unitAngle;
	cocos2d::MenuItem *_selectedItem;
	float animationDuration = 0.3f;
}; 
#pragma once

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;
/*
计时器
*/
class TimeCounter:public Node
{

public:
	CREATE_FUNC(TimeCounter);

	virtual bool init();
	virtual void myupdate(float dt);
	/*开始计时，指定回调时间和回调函数*/
	void start(int fCBTime,std::function<void()>func = nullptr);

public:
	TimeCounter();
	~TimeCounter();

private:
	int  m_fCBTime;					/*回调时间*/
	bool m_isCounting;				/*标记是否正在计时*/
	std::function<void()> m_func;	/*回调函数*/
	Label* m_timeLabel;

	Sprite* _clock_sp;
};


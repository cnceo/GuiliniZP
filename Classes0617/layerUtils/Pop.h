#pragma once

#include "Base.h"
#include "cocos2d.h"

USING_NS_CC;

class Pop : public Base
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void close();

protected:
	virtual void onEnterAnimComplete();
	virtual void onExitAnimComplete();
};
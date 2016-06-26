#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Audio
{
public:
	static Audio* getInstance();
	void prepare();

private:
	static Audio* m_instance;
};

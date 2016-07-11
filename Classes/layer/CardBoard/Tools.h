#pragma once

#include <cocos2d.h>
USING_NS_CC;

class Tools : public Node
{
public:
	static Point getPosByIndex(int index);
	static int getCellZOrder(int index);
	static int getIndexByPos(Point pos);
	static int getXValueByPos(Point pos);
	static int getXValueByIndex(int index);
};
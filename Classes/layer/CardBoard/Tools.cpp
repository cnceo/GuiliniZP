#include "Tools.h"

//返回坐标

Point Tools::getPosByIndex(int index){
	return Point(150 + (index % 10) * 78, 200 + 97 * (index / 10));
}

int Tools::getCellZOrder(int index){
	return 5 - index / 10;//越往上图层越低
}

int Tools::getIndexByPos(Point pos){
	int x = (pos.x - 150 + 39) / 78;
	int y = (pos.y - 100 + 48.5) / 97;
	return y * 10 + x;
}

int Tools::getXValueByPos(Point pos){
	int x = (pos.x - 150 + 39) / 78;
	return x;
}

int Tools::getXValueByIndex(int index){
	return index % 10;
}
#pragma once
#include "cocos2d.h"

class GetScore
{
public:

	static GetScore* getInstance();
	bool purgeInstance();

	int getScore();
	void setScore(int num);

private:
	GetScore();
	~GetScore();

	static GetScore* _instance;
	int score;

};
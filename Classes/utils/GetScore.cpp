
#include "GetScore.h"

GetScore* GetScore::_instance = nullptr;

GetScore::GetScore() :
score(0),
fanXin(0),
tianHu(0),
diHu(0),
sanLongWuK(0),
ziMo(0)
{
}


GetScore::~GetScore()
{
	purgeInstance();
}

GetScore* GetScore::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) GetScore();
	}
	return _instance;
}

int GetScore:: getScore()
{
	return score;
}

void GetScore::setScore(int num)
{
	score = num;
}

int GetScore::getFanXin()
{
	return fanXin;
}
void GetScore::setFanXin(int num)
{
	fanXin = num;
}

bool GetScore::purgeInstance()
{
	CCASSERT(_instance, "instance can not emptoy");
	if (_instance){
		delete _instance;
		_instance = nullptr;
	}
	return true;
}

int GetScore::getTianHu()
{
	return tianHu;
}

void GetScore::setTianHu(int num)
{
	tianHu = num;
}

int GetScore::getZiMo()
{
	return ziMo;
}
void GetScore::setZiMo(int num)
{
	ziMo = num;
}

int GetScore::getDiHu()
{
	return diHu;
}
void GetScore::setDiHu(int num)
{
	diHu = num;
}

int GetScore::getSanLongWuK()
{
	return sanLongWuK;
}
void GetScore::setSanLongWuK(int num)
{
	sanLongWuK = num;
}

//获得胡舵数
int GetScore::getHuDuo()
{
	if (getScore() >= 10)
	{
		int num = ((getScore() - 10) / 5) + 1;
		return num;
	}
	else
	{
		int num = 0;
		return num;
	}
}

int GetScore::getBeiShu()
{
	int num = getHuDuo() + getZiMo() + getFanXin() + getTianHu() + getDiHu() + getSanLongWuK();
	return num;
}

int GetScore::getMoney()
{
	int money = getBeiShu() * 1000;
	return money;
}
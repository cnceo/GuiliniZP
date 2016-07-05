#pragma once
#include "cocos2d.h"
#include <vector>
#include "ZiPaiManage.h"

using namespace std;

class GetScore
{
public:

	static GetScore* getInstance();
	bool purgeInstance();

	int getScore();
	void setScore(int num);

	int getFanXin();
	void setFanXin(int num);

	int getTianHu();
	void setTianHu(int num);

	int getZiMo();
	void setZiMo(int num);

	int getDiHu();
	void setDiHu(int num);

	int getSanLongWuK();
	void setSanLongWuK(int num);

	//获得胡舵数
	int getHuDuo();
	void setHuDuo(int num);
	//
	int getBeiShu();

	vector<CardData> showCardList; //要显示的底牌

	int getMoney();

private:
	GetScore();
	~GetScore();

	static GetScore* _instance;
	int score;

	int fanXin;

	int tianHu;
	int ziMo;
	int  diHu;
	int  sanLongWuK;

	int huDuo;

};
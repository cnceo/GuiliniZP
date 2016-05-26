#pragma once
//#include <windows.h>  
#include <iostream>  
#include <vector>  
#include <algorithm> 
#include "ZiPai.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//剩余牌墙
struct CardEx
{
	CardData m_NewCard;		//起新的牌
	int		 m_CardNum;		//剩余牌数量
	bool	 IsHz;			//是否黄庄
};

class ZiPaiManage
{
private:
	vector <CardData> m_ZPVec;      //
	int				  m_HZPaiNum;   //

public:
	ZiPaiManage();
	~ZiPaiManage();

	void InitPai(int p_HZPaiNum = 0);

	CardEx  GetAPai();

private:

	void   XiPai();

};


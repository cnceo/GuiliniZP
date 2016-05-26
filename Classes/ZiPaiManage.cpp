#include "ZiPaiManage.h"
//#include <windows.h>

ZiPaiManage::ZiPaiManage()
{

}
ZiPaiManage::~ZiPaiManage()
{

}

//初始化牌 
void ZiPaiManage::InitPai(int p_HZPaiNum)
{
	m_HZPaiNum = p_HZPaiNum;
	m_ZPVec.clear();
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 10; ++j)
		{
			CardData d;
			d.m_Type = 0;
			d.m_Value = j;
			m_ZPVec.push_back(d);
		}
	}
	//大写
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 10; ++j)
		{
			CardData d;
			d.m_Type = 1;
			d.m_Value = j;
			m_ZPVec.push_back(d);
		}
	}

	XiPai();
}

//起牌
CardEx ZiPaiManage::GetAPai()
{
	CardEx t_pai;
	t_pai.m_NewCard.m_Type = m_ZPVec.back().m_Type;
	t_pai.m_NewCard.m_Value = m_ZPVec.back().m_Value;
	t_pai.m_CardNum = m_ZPVec.size() - 1;

	if (t_pai.m_CardNum == m_HZPaiNum)
	{
		t_pai.IsHz = true;
	}
	else
	{
		t_pai.IsHz = false;
	}
	//扔去一个
	m_ZPVec.pop_back();

	return t_pai;
}

//洗牌 
void  ZiPaiManage::XiPai()
{
	srand((unsigned int)time(NULL));
	random_shuffle(m_ZPVec.begin(), m_ZPVec.end());
}
#include "ZiPai.h"
#include "layerUtils/ToastLayer/ToastManger.h"
#include "utils/CommonFunction.h"

ZiPai::ZiPai():
m_Score(0),
state(0)
{
	
}
ZiPai::~ZiPai()
{

}

//获取，设置用户状态
void ZiPai:: setState(int x)
{
	state = x;
}

int ZiPai:: getState()
{
	return state;
}

//检测吃顺牌
bool ZiPai::checkChiA_B_C(int p_type, int p_value)			//吃顺牌	
{
	if (m_TempChiCardVec.size()>0)
	{
		m_TempChiCardVec.clear();
	}
	std::vector<int > vec1;		//小两位
	std::vector<int > vec2;
	std::vector<int > vec4;
	std::vector<int > vec5;		//大两位

	if (m_MyCard[p_type].size() >= 2)
	{
		std::vector<int >::iterator iter = m_MyCard[p_type].begin();
		for (; iter != m_MyCard[p_type].end(); ++iter)
		{
			if ((*iter) == p_value - 2)
			{
				vec1.push_back(*iter);
			}

			if ((*iter) == p_value - 1)
			{
				vec2.push_back(*iter);
			}

			if ((*iter) == p_value)
			{
				CardData card;
				card.m_Type = p_type;
				card.m_Value = (*iter);
				vec3.push_back(card);
			}

			if ((*iter) == p_value + 1)
			{
				vec4.push_back(*iter);
			}

			if ((*iter) == p_value + 2)
			{
				vec5.push_back(*iter);
			}
		}
	}

	//摸的牌最大
	if (vec1.size()>0 && vec2.size()>0)
	{
		ChiCard t_Chi;
		t_Chi.m_Type = p_type;
		t_Chi.m_Value1 = vec1[0];		//手牌
		t_Chi.m_Value2 = vec2[0];		//手牌
		t_Chi.m_Value3 = p_value;		//摸的牌 或上家的牌
		m_TempChiCardVec.push_back(t_Chi);
	}

	//摸的牌中等
	if (vec2.size()>0 && vec4.size()>0)
	{
		ChiCard t_Chi;
		t_Chi.m_Type = p_type;
		t_Chi.m_Value1 = vec2[0];		//手牌
		t_Chi.m_Value2 = p_value;		//手牌
		t_Chi.m_Value3 = vec4[0];		//摸的牌 或上家的牌
		m_TempChiCardVec.push_back(t_Chi);
	}

	//摸的牌最小
	if (vec4.size()>0 && vec5.size()>0)
	{
		ChiCard t_Chi;
		t_Chi.m_Type = p_type;
		t_Chi.m_Value1 = p_value;		//手牌
		t_Chi.m_Value2 = vec4[0];		//手牌
		t_Chi.m_Value3 = vec5[0];		//摸的牌 或上家的牌
		m_TempChiCardVec.push_back(t_Chi);
	}

	if (m_TempChiCardVec.size()>0)
	{
		return true;
	}

	return false;
}

//吃顺牌			
bool ZiPai::doChiA_B_C(int p_type, int p_value, int num)
{
	addCard(p_type, p_value);

	m_ChiCardVec[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value1);
	m_ChiCardVec[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value2);
	m_ChiCardVec[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value3);

	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value1);
	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value2);
	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value3);

	return true;
}

bool	ZiPai::checkChiACard2_7_10(int p_type, int p_value)
{
	if (m_TempChiCardVec.size()>0)
	{
		m_TempChiCardVec.clear();
	}
	//特殊牌型（2, 7, 10）
	std::vector<int> chiVec_1[2];
	std::vector<int> chiVec_2[2];
	for (int i = 0; i < 2; i++)
	{
		if (chiVec_1[i].size()>0)
		{
			chiVec_1[i].clear();
		}
		if (chiVec_2[i].size()>0)
		{
			chiVec_2[i].clear();
		}
	}

	if (p_value == 2 || p_value == 7 || p_value == 10)
	{
		std::vector<int>::iterator iter = m_MyCard[p_type].begin();
		for (; iter != m_MyCard[p_type].end(); ++iter)
		{
			if (p_value == 2)
			{
				if ((*iter) == 7)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 10)
				{
					chiVec_2[p_type].push_back(*iter);
				}

			}

			if (p_value == 7)
			{
				if ((*iter) == 2)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 10)
				{
					chiVec_2[p_type].push_back(*iter);
				}
			}

			if (p_value == 10)
			{
				if ((*iter) == 2)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 7)
				{
					chiVec_2[p_type].push_back(*iter);
				}

			}
		}

		if (chiVec_1[p_type].size()>0 && chiVec_2[p_type].size()>0)
		{
			ChiCard t_Chi;
			t_Chi.m_Type = p_type;
			t_Chi.m_Value1 = chiVec_1[p_type][0];
			t_Chi.m_Value2 = chiVec_2[p_type][0];
			t_Chi.m_Value3 = p_value;
			m_TempChiCardVec.push_back(t_Chi);
			//log("chi..2.7.10");
		}
	}

	if (m_TempChiCardVec.size()>0)
	{
		return true;
	}

	return false;
}

bool	ZiPai::doChi2_7_10(int p_type, int p_value, int num)
{
	addCard(p_type, p_value);

	m_ChiSpeclal[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value1);
	m_ChiSpeclal[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value2);
	m_ChiSpeclal[m_TempChiCardVec[num].m_Type].push_back(m_TempChiCardVec[num].m_Value3);

	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value1);
	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value2);
	delACard(m_TempChiCardVec[num].m_Type, m_TempChiCardVec[num].m_Value3);

	return true;
}

//吃1 2 3
bool	ZiPai::checkChiACard1_2_3(int p_type, int p_value)
{
	if (m_TempChiCardVec.size()>0)
	{
		m_TempChiCardVec.clear();
	}
	//特殊牌型（1, 2, 3）
	std::vector<int> chiVec_1[2];
	std::vector<int> chiVec_2[2];
	for (int i = 0; i < 2; i++)
	{
		if (chiVec_1[i].size()>0)
		{
			chiVec_1[i].clear();
		}
		if (chiVec_2[i].size()>0)
		{
			chiVec_2[i].clear();
		}
	}

	if (p_value == 1 || p_value == 2 || p_value == 3)
	{
		std::vector<int>::iterator iter = m_MyCard[p_type].begin();
		for (; iter != m_MyCard[p_type].end(); ++iter)
		{
			if (p_value == 1)
			{
				if ((*iter) == 2)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 3)
				{
					chiVec_2[p_type].push_back(*iter);
				}

			}

			if (p_value == 2)
			{
				if ((*iter) == 1)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 3)
				{
					chiVec_2[p_type].push_back(*iter);
				}
			}

			if (p_value == 3)
			{
				if ((*iter) == 1)
				{
					chiVec_1[p_type].push_back(*iter);
				}
				if ((*iter) == 2)
				{
					chiVec_2[p_type].push_back(*iter);
				}

			}
		}

		if (chiVec_1[p_type].size()>0 && chiVec_2[p_type].size()>0)
		{

			ChiCard t_Chi;
			t_Chi.m_Type = p_type;
			t_Chi.m_Value1 = chiVec_1[p_type][0];
			t_Chi.m_Value2 = chiVec_2[p_type][0];
			t_Chi.m_Value3 = p_value;
			m_TempChiCardVec.push_back(t_Chi);
			//log("chi..1.2.3");
		}
	}

	if (m_TempChiCardVec.size()>0)
	{
		return true;
	}

	return false;
}

bool	ZiPai::doChi1_2_3(int p_type, int p_value, int num)
{
	addCard(p_type, p_value);

	for (std::vector<ChiCard>::iterator it = m_TempChiCardVec.begin(); it != m_TempChiCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value1);
		delACard((*it).m_Type, (*it).m_Value2);
		delACard((*it).m_Type, (*it).m_Value3);

		m_ChiSpeclal[(*it).m_Type].push_back((*it).m_Value1);
		m_ChiSpeclal[(*it).m_Type].push_back((*it).m_Value2);
		m_ChiSpeclal[(*it).m_Type].push_back((*it).m_Value3);
	}

	return true;
}

//手里2个大写，来了一张小写 或 手里2个小写  来了一张大写
bool	ZiPai::checkChiACardA_A_a(int p_type, int p_value)
{
	//a  AA ,  a  aA

	if (m_TempChiCardVec.size()>0)
	{
		m_TempChiCardVec.clear();
	}

	std::vector<int> vec[2];
	for (int i = 0; i < 2; ++i)
	{
		vec[i].clear();
	}

	if (p_type == 0)
	{
		std::vector<int>::iterator iter = m_MyCard[1].begin();
		for (; iter != m_MyCard[1].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec[1].push_back(p_value);	//手中大写的
			}
		}
	}

	if (p_type == 1)
	{
		std::vector<int>::iterator iter = m_MyCard[0].begin();
		for (; iter != m_MyCard[0].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec[0].push_back(p_value);	//手中小写的
			}
		}
	}

	if (vec[1].size() == 2)	//手里2个大写  来了一张小写
	{
		/*T = 0; V = p_value;

		T = 1; V = vec1[0];
		T = 1; V = vec1[0];*/

		ChiCard t_Chi;
		t_Chi.m_Type = 1;
		t_Chi.m_Value1 = vec[1][0];
		t_Chi.m_Value2 = vec[1][0];
		m_TempChiCardVec.push_back(t_Chi);
	}

	if (vec[0].size() == 2) //手里2个小写  来了一张大写
	{
		ChiCard t_Chi;
		t_Chi.m_Type = 0;
		t_Chi.m_Value1 = vec[0][0];
		t_Chi.m_Value2 = vec[0][0];
		m_TempChiCardVec.push_back(t_Chi);
	}

	if (m_TempChiCardVec.size() > 0)
	{
		return true;
	}

	return false;
}

bool	ZiPai::doChiA_A_a(int p_type, int p_value)
{
	for (std::vector<ChiCard>::iterator it = m_TempChiCardVec.begin(); it != m_TempChiCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value1);
		delACard((*it).m_Type, (*it).m_Value2);

		m_ChiCardVec[(*it).m_Type].push_back((*it).m_Value1);
		m_ChiCardVec[(*it).m_Type].push_back((*it).m_Value2);
		m_ChiCardVec[p_type].push_back(p_value);
	}
	return true;
}
//来了张a  手里有A a, 来了张A 手里有A a
bool	ZiPai::checkChiACardA_A_a_a(int p_type, int p_value)
{
	if (m_TempChiCardVec.size()>0)
	{
		m_TempChiCardVec.clear();
	}

	std::vector<int> vec1[2];
	std::vector<int> vec2[2];

	for (int i = 0; i < 2; ++i)
	{
		vec1[i].clear();
		vec2[i].clear();
	}

	if (p_type == 0)
	{

		for (std::vector<int>::iterator iter = m_MyCard[0].begin(); iter != m_MyCard[0].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec1[0].push_back(p_value);	//手中小写的
			}
		}

		for (std::vector<int>::iterator iter = m_MyCard[1].begin(); iter != m_MyCard[1].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec1[1].push_back(p_value);	//手中大写的
			}
		}

	}

	if (p_type == 1)
	{
		for (std::vector<int>::iterator iter = m_MyCard[0].begin(); iter != m_MyCard[0].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec2[0].push_back(p_value);
			}
		}

		for (std::vector<int>::iterator iter = m_MyCard[1].begin(); iter != m_MyCard[1].end(); ++iter)
		{
			if (*iter == p_value)
			{
				vec2[1].push_back(p_value);
			}
		}
	}

	if (vec1[0].size()>0 && vec1[1].size()>0)//来了张小写的
	{
		ChiCard t_Chi;
		t_Chi.m_Type = 1;
		t_Chi.m_Value1 = vec1[1][0];
		m_TempChiCardVec.push_back(t_Chi);
	}

	if (vec2[0].size()>0 && vec2[1].size()>0)//来了张大写的
	{
		ChiCard t_Chi;
		t_Chi.m_Type = 0;
		t_Chi.m_Value1 = vec2[0][0];
		m_TempChiCardVec.push_back(t_Chi);
	}

	if (m_TempChiCardVec.size()>0)
	{
		return true;
	}
	return false;
}

bool	ZiPai::doChiA_A_a_a(int p_type, int p_value)
{
	for (std::vector<ChiCard>::iterator it = m_TempChiCardVec.begin(); it != m_TempChiCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value1);
		delACard(p_type, p_value);

		m_ChiCardVec[(*it).m_Type].push_back((*it).m_Value1);
		m_ChiCardVec[p_type].push_back(p_value);
		m_ChiCardVec[p_type].push_back(p_value);
	}
	return true;
}

//下比
bool	ZiPai::checkXiaBiACard(int p_type, int p_value)
{
	if (vec3.size()>0 && checkChiA_B_C(p_type, p_value))
	{
		return true;
	}

	return false;
}
//执行下比
bool	ZiPai::doXiaBiCard(int p_type, int p_value, int num)
{

	return true;
}
//清空牌  
void ZiPai::CleanUp()
{
	for (int i = 0; i < 2; i++)
	{
		m_MyCard[i].clear();
		m_ChiCardVec[i].clear();  
	}
}

//加入新牌,并排序  
void  ZiPai::addCard(int p_type, int p_value)
{
	bool t_Find = false;
	vector<  int >::iterator Iter;
	for (Iter = m_MyCard[p_type].begin(); Iter != m_MyCard[p_type].end(); Iter++)
	{
		if ((*Iter)>p_value)
		{
			m_MyCard[p_type].insert(Iter, p_value);
			t_Find = true;
			break;
		}
	}

	if (t_Find == false)
	{
		m_MyCard[p_type].push_back(p_value);
	}
}

//打印手上所有的牌
void ZiPai:: logAllCard()
{
	cout << "牌数量=" << (m_MyCard[0].size() + m_MyCard[1].size()) << endl;
	int length = m_MyCard[0].size() + m_MyCard[1].size();
	int icount = 0;

	if (m_MyCard[0].size()>0)
	{
		for (int i = 0; i < m_MyCard[0].size(); i++)
		{
			cout << "(0" << "," << "" << m_MyCard[0][i]<<"),";
			icount++;
		}
	}
	cout << endl;
	if (m_MyCard[1].size()>0)
	{
		for (int i = 0; i < m_MyCard[1].size(); i++)
		{
			cout << "(1" << "," << "" << m_MyCard[1][i]<<"),";
			icount++;
		}
	}
	cout << endl;
	cout << endl;
}
//打印所有碰的牌
void	ZiPai::logAllPengCard()
{
	if ((m_PengCardVec[0].size()>0))
	{
		for (int i = 0; i < m_PengCardVec[0].size(); i++)
		{
			//log("MPeng=%d", m_PengCardVec[0][i]);
		}

	}

	if ((m_PengCardVec[1].size()>0))
	{
		for (int i = 0; i < m_PengCardVec[1].size(); i++)
		{
			//log("LPeng=%d", m_PengCardVec[1][i]);
		}
	}
}

//打印所有吃的牌
void	ZiPai::logAllChiCard()
{
	if ((m_ChiCardVec[0].size()>0))
	{
		for (int i = 0; i < m_ChiCardVec[0].size(); i++)
		{
			//log("M_chi=%d", m_ChiCardVec[0][i]);
		}

	}

	if ((m_ChiCardVec[1].size()>0))
	{
		for (int i = 0; i < m_ChiCardVec[1].size(); i++)
		{
			//log("L_chi=%d", m_ChiCardVec[1][i]);
		}
	}
}

//打出一张手里的牌
bool ZiPai::delACard(int PaiIndex)
{
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		vector<int>::iterator Iter;
		for (Iter = m_MyCard[i].begin(); Iter != m_MyCard[i].end(); Iter ++)
		{
			if (count == PaiIndex)
			{
				popCard.m_Type = i;
				popCard.m_Value = (*Iter);
				m_MyCard[i].erase(Iter);
				return true;
			}
			count++;
		}
	}
	return false;
}

//所有可以吃的牌
void ZiPai::logAllTempCard()
{
	//log("-----------------------------------");
	if (!m_TempChiCardVec.empty())
	{
		for (int i = 0; i < m_TempChiCardVec.size(); ++i)
		{
			//log("[%d],%d,%d,%d", i, m_TempChiCardVec[i].m_Value1, m_TempChiCardVec[i].m_Value2, m_TempChiCardVec[i].m_Value3);
			//log("\n");
		}
	}
	else
	{
		//log("size <=0");
	}
	//log("-----------------------------------");

}
//打一张牌 删除牌
bool	ZiPai::delACard(int p_type, int p_value)
{
	for (std::vector<int>::iterator it = m_MyCard[p_type].begin(); it != m_MyCard[p_type].end(); ++it)
	{
		if ((*it) == p_value)
		{
			popCard.m_Type = p_type;
			popCard.m_Value = p_value;

			m_MyCard[p_type].erase(it);

			return true;
		}
	}
	return false;

}

//碰
bool	ZiPai::checkPengACard(int p_type, int p_value)
{
	if (m_TempPengCardVec.size()>0)
	{
		m_TempPengCardVec.clear();
	}

	if (m_MyCard[p_type].empty() == false)
	{
		int iSize = m_MyCard[p_type].size();
		if (iSize >= 2)
		{
			for (int i = 0; i < iSize - 1; i++)
			{
				if ((m_MyCard[p_type][i] == p_value) && (m_MyCard[p_type][i + 1] == p_value))
				{
					CardData t_peng;
					t_peng.m_Type = p_type;
					t_peng.m_Value = p_value;
					m_TempPengCardVec.push_back(t_peng);
					//log(" have pengpai.....");
					break;
				}
			}
		}
	}

	if (m_TempPengCardVec.size()>0)
	{
		return true;
	}
	return false;
}

bool	ZiPai::doPengACard(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempPengCardVec.begin(); it != m_TempPengCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);

		m_PengCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_PengCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_PengCardVec[(*it).m_Type].push_back((*it).m_Value);
	}

	return true;
}

//扫
bool	ZiPai::checkSaoACard(int p_type, int p_value)
{
	if (m_TempSaoCardVec.size()>0)
	{
		m_TempSaoCardVec.clear();
	}

	if (m_MyCard[p_type].empty() == false)
	{
		int iSize = m_MyCard[p_type].size();
		if (iSize >= 2)
		{
			for (int i = 0; i < iSize - 1; i++)
			{
				if ((m_MyCard[p_type][i] == p_value) && (m_MyCard[p_type][i + 1] == p_value))
				{
					CardData t_sao;
					t_sao.m_Type = p_type;
					t_sao.m_Value = p_value;
					m_TempSaoCardVec.push_back(t_sao);
					//log(" have saopai.....");
					break;
				}
			}
		}
	}

	if (m_TempSaoCardVec.size()>0)
	{
		return true;
	}

	return false;
}

//执行扫牌
bool	ZiPai::doSaoACard(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempSaoCardVec.begin(); it != m_TempSaoCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);

		m_SaoCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_SaoCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_SaoCardVec[(*it).m_Type].push_back((*it).m_Value);
	}

	return true;
}
//扫穿
bool	ZiPai::checkSaoChuanACard(int p_type, int p_value)
{
	//自己手中有三张牌  自己摸到一张牌
	//桌子上扫的三张牌  自己摸到一张

	if (m_TempSaoChuanCardVec.size()>0)
	{
		m_TempSaoChuanCardVec.clear();
	}

	if (m_MyCard[p_type].empty() == false)
	{
		int iSize = m_MyCard[p_type].size();
		if (iSize >= 3)
		{
			for (int i = 0; i < iSize - 2; i++)
			{
				if ((m_MyCard[p_type][i] == p_value) && (m_MyCard[p_type][i + 1] == p_value) && (m_MyCard[p_type][i + 2] == p_value))
				{
					CardData t_card;
					t_card.m_Type = p_type;
					t_card.m_Value = p_value;
					m_TempSaoChuanCardVec.push_back(t_card);
					//log("shoupai_saochuan......");
					break;
				}
			}
		}

		if (m_TempSaoChuanCardVec.size()>0)
		{
			return true;
		}
	}
	return false;
}

bool	ZiPai::doSaoChuanACard(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempSaoChuanCardVec.begin(); it != m_TempSaoChuanCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);

		m_SaoChuanCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_SaoChuanCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_SaoChuanCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_SaoChuanCardVec[(*it).m_Type].push_back((*it).m_Value);

	}

	return true;
}

//扫的扫穿
bool	ZiPai::checkSao_saoChuanACard(int p_type, int p_value)
{
	if (m_TempSaoChuanCardVec.size()>0)
	{
		m_TempSaoChuanCardVec.clear();
	}

	if (m_SaoCardVec[p_type].size()>0)
	{
		for (int i = 0; i < m_SaoCardVec[p_type].size(); i++)
		{
			if (m_SaoCardVec[p_type][i] == p_value)
			{
				CardData t_card;
				t_card.m_Type = p_type;
				t_card.m_Value = p_value;
				m_TempSaoChuanCardVec.push_back(t_card);
				//log("sao_saochuang......");
				break;
			}
		}
	}

	if (m_TempSaoChuanCardVec.size()>0)
	{
		return true;
	}
	return false;
}
//执行扫的扫穿
bool	ZiPai::doSao_SaoChuan(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempSaoChuanCardVec.begin(); it != m_TempSaoChuanCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);

		m_SaoChuanCardVec[(*it).m_Type].push_back((*it).m_Value);
	}

	return true;
}

//过扫
bool	ZiPai::checkGuoSaoACard(int p_type, int p_value)
{
	if (m_TempSaoCardVec.size()>0)
	{
		m_TempSaoCardVec.clear();
	}

	if (m_MyCard[p_type].empty() == false)
	{
		int iSize = m_MyCard[p_type].size();
		if (iSize >= 2)
		{
			for (int i = 0; i < iSize - 1; i++)
			{
				if ((m_MyCard[p_type][i] == p_value) && (m_MyCard[p_type][i + 1] == p_value))
				{
					CardData t_sao;
					t_sao.m_Type = p_type;
					t_sao.m_Value = p_value;
					m_TempSaoCardVec.push_back(t_sao);
					//log(" have guo_sao.....");
					break;
				}
			}
		}
	}

	if (m_TempSaoCardVec.size()>0)
	{
		return true;
	}
	return false;
}
//执行过扫
bool	ZiPai::do_guoSao(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempSaoCardVec.begin(); it != m_TempSaoCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);

		m_GuoSaoCardBVec[(*it).m_Type].push_back((*it).m_Value);
		m_GuoSaoCardBVec[(*it).m_Type].push_back((*it).m_Value);
		m_GuoSaoCardBVec[(*it).m_Type].push_back((*it).m_Value);
	}
	return true;
}

//起手牌开舵
bool	ZiPai::checkKaiduoACard(int p_type, int p_value)
{
	/*
	1.手牌 别人摸出或打出一张
	2.碰的牌 别人或自己 摸出一张  不能是别家打出的牌
	3.扫过之后，别家摸出一张 或打出一张
	*/

	if (m_TempKaiDuoCardVec.size()>0)
	{
		m_TempKaiDuoCardVec.clear();
	}

	if (m_MyCard[p_type].empty() == false)
	{
		int iSize = m_MyCard[p_type].size();
		if (iSize >= 3)
		{
			for (int i = 0; i < iSize - 2; i++)
			{
				if ((m_MyCard[p_type][i] == p_value) && (m_MyCard[p_type][i + 1] == p_value) && (m_MyCard[p_type][i + 2] == p_value))
				{
					CardData t_card;
					t_card.m_Type = p_type;
					t_card.m_Value = p_value;
					m_TempKaiDuoCardVec.push_back(t_card);
					//log("shoupai_kaiduo......");
					break;
				}
			}
		}

		if (m_TempKaiDuoCardVec.size()>0)
		{
			return true;
		}
	}
	return false;
}

//执行开舵  
bool	ZiPai::doKaiDuo(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempKaiDuoCardVec.begin(); it != m_TempKaiDuoCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);
		delACard((*it).m_Type, (*it).m_Value);

		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);
		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);

	}
	return true;
}

//扫的开舵
bool	ZiPai::checkKaiDuo_Sao(int p_type, int p_value)
{
	if (m_TempKaiDuoCardVec.size()>0)
	{
		m_TempKaiDuoCardVec.clear();
	}

	if (m_SaoCardVec[p_type].size()>0)
	{
		for (int i = 0; i < m_SaoCardVec[p_type].size(); i++)
		{
			if (m_SaoCardVec[p_type][i] == p_value)
			{
				CardData t_card;
				t_card.m_Type = p_type;
				t_card.m_Value = p_value;
				m_TempKaiDuoCardVec.push_back(t_card);
				//log("sao_kaiduo......");
				break;
			}
		}
	}

	if (m_TempKaiDuoCardVec.size()>0)
	{
		return true;
	}
	return false;
}

//执行扫的开舵
bool	ZiPai::doSao_KaiDuo(int p_type, int p_value)
{
	//扫过之后，别家摸出一张 或打出一张
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempKaiDuoCardVec.begin(); it != m_TempKaiDuoCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);

		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);
	}

	return true;
}

//碰的开舵
bool	ZiPai::checkKaiDuo_peng(int p_type, int p_value)
{
	if (m_TempKaiDuoCardVec.size()>0)
	{
		m_TempKaiDuoCardVec.clear();
	}

	if (m_PengCardVec[p_type].size()>0)
	{
		for (int i = 0; i < m_PengCardVec[p_type].size(); i++)
		{
			if (m_PengCardVec[p_type][i] == p_value)
			{
				CardData t_card;
				t_card.m_Type = p_type;
				t_card.m_Value = p_value;
				m_TempKaiDuoCardVec.push_back(t_card);
				//log("peng_kaiduo......");
				break;
			}
		}
	}

	if (m_TempKaiDuoCardVec.size()>0)
	{
		return true;
	}
	return false;
}
//执行碰的开舵
bool	ZiPai::doPeng_kaiDuo(int p_type, int p_value)
{
	addCard(p_type, p_value);

	for (std::vector<CardData>::iterator it = m_TempKaiDuoCardVec.begin(); it != m_TempKaiDuoCardVec.end(); ++it)
	{
		delACard((*it).m_Type, (*it).m_Value);

		m_KaiDuoCardVec[(*it).m_Type].push_back((*it).m_Value);
	}

	return true;
}
//重舵 扫穿
bool	ZiPai::checkChongDuo_saoChuan(int p_type, int p_value)
{
	//重舵实现扫穿的功能（放到扫穿的vec）  重舵实现开舵的功能(放到开舵的vec)  
	//手里三张一样的牌   碰的牌   扫的牌
	if (m_SaoChuanCardVec[0].size()>0 ||
		m_KaiDuoCardVec[0].size()>0 ||
		m_SaoChuanCardVec[1].size()>0 ||
		m_KaiDuoCardVec[1].size()>0)
	{
		if (checkSaoChuanACard(p_type, p_value))		//手牌扫穿
		{
			m_type.saoChuan_chongDuo = 0;
			//log("chongduo_saochuan");
			return true;
		}

		if (checkSao_saoChuanACard(p_type, p_value))	//扫的扫穿
		{
			m_type.saoChuan_chongDuo = 1;
			//log("chongduo_sao_saochuan");
			return true;
		}
	}
	return false;
}

bool	ZiPai::doChongDuo_saoChuan(int p_type, int p_value)
{
	if (m_type.saoChuan_chongDuo == 0)
	{
		doSaoChuanACard(p_type, p_value);
	}
	else if (m_type.saoChuan_chongDuo == 1)
	{
		doSao_SaoChuan(p_type, p_value);
	}
	return true;
}

//重舵 开舵
bool	ZiPai::checkChongDuo_kaiDuo(int p_type, int p_value)
{
	if (m_SaoChuanCardVec[0].size()>0 ||
		m_KaiDuoCardVec[0].size()>0 ||
		m_SaoChuanCardVec[1].size()>0 ||
		m_KaiDuoCardVec[1].size()>0)
	{
		if (checkKaiduoACard(p_type, p_value))	//重舵 起手牌开舵
		{
			m_type.kaiDuo_chongDuo = 0;
			//log("chongduo_kaiduo");
			return true;
		}

		if (checkKaiDuo_Sao(p_type, p_value))	//重舵 扫的开舵
		{
			m_type.kaiDuo_chongDuo = 1;
			//log("chongduo_sao_kaiduo");
			return true;
		}

		if (checkKaiDuo_peng(p_type, p_value))	 //碰的开舵
		{
			m_type.kaiDuo_chongDuo = 2;
			//log("chongduo_peng_kaiDuo");
			return true;
		}
	}
	return false;
}

bool	ZiPai::doChongDuo_kaiDuo(int p_type, int p_value)
{
	if (m_type.kaiDuo_chongDuo == 0)
	{
		doKaiDuo(p_type, p_value);
	}
	else if (m_type.kaiDuo_chongDuo == 1)
	{
		doSao_KaiDuo(p_type, p_value);
	}
	else if (m_type.kaiDuo_chongDuo == 2)
	{
		doPeng_kaiDuo(p_type, p_value);
	}
	return true;
}
//是否臭牌
bool	ZiPai::checkChouPai(int p_type, int p_value)
{
	if (m_Not_Chi[p_type].size() > 0)
	{
		for (int i = 0; i < m_Not_Chi[p_type].size(); i++)
		{
			if (m_Not_Chi[p_type][i] == p_value)
			{
				return true;
				break;
			}
		}
	}
	return false;
}
//是否过扫（可以碰的没有碰）
bool	ZiPai::checkGuoSao(int p_type, int p_value)
{
	if (m_Not_Peng[p_type].size()>0)
	{
		for (int i = 0; i < m_Not_Peng[p_type].size(); i++)
		{
			if (m_Not_Peng[p_type][i] == p_value)
			{
				return true;
				break;
			}
		}
	}
	return false;
}

bool ZiPai::check(ZiPai &player,int t_Type, int t_Value)
{
	// 扫穿的重舵
	if (player.checkChongDuo_saoChuan(t_Type, t_Value))
	{
		player.doChongDuo_saoChuan(t_Type, t_Value);

		return true;
	}
	// 开舵的重舵
	if (player.checkChongDuo_kaiDuo(t_Type, t_Value))
	{
		player.doChongDuo_kaiDuo(t_Type, t_Value);
		return true;
	}
	/*------------------------------------------*/
	//起手牌开舵
	if (player.checkKaiduoACard(t_Type, t_Value))
	{
		player.doKaiDuo(t_Type, t_Value);
		return true;
	}
	//扫的开舵
	if (player.checkKaiDuo_Sao(t_Type, t_Value))
	{
		player.doSao_KaiDuo(t_Type, t_Value);
		return true;
	}
	//碰的开舵
	if (player.checkKaiDuo_peng(t_Type, t_Value))
	{
		player.doPeng_kaiDuo(t_Type, t_Value);
		return true;
	}

	/*------------------------------------------*/
	//起手三张 扫穿
	if (player.checkSaoChuanACard(t_Type, t_Value))
	{
		player.doSaoChuanACard(t_Type, t_Value);
		return true;
	}
	//扫的扫穿
	if (player.checkSao_saoChuanACard(t_Type, t_Value))
	{
		player.doSao_SaoChuan(t_Type, t_Value);
		return true;
	}
	/*------------------------------------------*/
	//检测扫
	if (player.checkSaoACard(t_Type, t_Value))
	{
		player.doSaoACard(t_Type, t_Value);
		return true;
	}
	//检测过扫
	if (player.checkGuoSao(t_Type, t_Value))
	{
		if (player.checkGuoSaoACard(t_Type, t_Value))
		{
			player.do_guoSao(t_Type, t_Value);
			return true;
		}
	}
	/*------------------------------------------*/
	/*
	if (player.checkPengACard(t_Type, t_Value))
	{
		player.logAllPengCard();
		char str[2];
		cin >> str;
		if (str == "y" && str == "Y")
		{
			player.doPengACard(t_Type, t_Value);
			return true;
		}
		else
		{
			cout << "no" << endl;
			m_Not_Peng[t_Type].push_back(t_Value);		//放入可以碰但是没有碰的牌
		}
		
	}
	else
	{
		//检测吃牌
		if (player.checkChiACard2_7_10(t_Type, t_Value))
		{
			player.logAllTempCard();
			int num;
			cin >> num;
			player.doChi2_7_10(t_Type, t_Value, num);
			return true;
		}
		if (player.checkChiA_B_C(t_Type, t_Value))
		{
			player.logAllTempCard();
			int num;
			cin >> num;
			//if (player.checkChiACard1_2_3(t_Type, t_Value) && num == 0)
			//{
			//	player.doChi1_2_3(t_Type, t_Value, num);
			//}
			player.doChiA_B_C(t_Type, t_Value, num);
			return true;
		}
		if (player.checkChiACardA_A_a(t_Type, t_Value))
		{
			player.logAllTempCard();
			int num;
			cin >> num;
			player.doChiA_A_a(t_Type, t_Value); //没改
			return true;
		}
		if (player.checkChiACardA_A_a_a(t_Type, t_Value))
		{
			int num;
			cin >> num;
			player.doChiA_A_a_a(t_Type, t_Value);
			return true;
		}

	}
	*/
	//检测胡牌
	if (player.checkHuPai())
	{
		//cout << "胡牌了~！" << endl;
		return true;
	}
	
	return false;
}

bool ZiPai::checkHuPai()
{
	return false;
}

bool	ZiPai::checkHuPai(int p_type, int p_value)
{
	//胡数  10或以上
	//基本牌型

	//1.手里的牌 2.桌面上吃碰扫的牌

	m_MyCard_Temp[0].clear();
	m_MyCard_Temp[1].clear();

	for (int i = 0; i < m_MyCard[0].size(); i++)
	{
		m_MyCard_Temp[0].push_back(m_MyCard[0][i]);
	}
	for (int i = 0; i < m_MyCard[1].size(); i++)
	{
		m_MyCard_Temp[1].push_back(m_MyCard[1][i]);
	}

	////先放到临时数组，排序，检测
	bool t_Find = false;
	vector<  int >::iterator Iter;
	for (Iter = m_MyCard_Temp[p_type].begin(); Iter != m_MyCard_Temp[p_type].end(); Iter++)
	{
		if ((*Iter)>p_value)
		{
			m_MyCard_Temp[p_type].insert(Iter, p_value);
			t_Find = true;
			break;
		}

	}
	if (t_Find == false)
	{
		m_MyCard_Temp[p_type].push_back(p_value);
	}

	/*for (int i = 0; i < 2; i++)
	{
	for (int j = 0; j < m_MyCard_Temp[i].size();j++)
	{
	log("-%d-", m_MyCard_Temp[i][j]);
	}
	}*/

	if (checkHu())	//若胡了
	{
		m_MyCard[p_type].push_back(p_value);//把那张能胡的牌放到手里

		int hushu = checkHushu();
		UserDefault::getInstance()->setIntegerForKey("HUSHU", hushu);	//保存胡数

		//手里的牌放到存储器
		{
			for (int i = 0; i < m_MyCard[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_MyCard[0][i]);
			}
			for (int j = 0; j < m_MyCard[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_MyCard[1][j]);
			}

			for (int i = 0; i < m_PengCardVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_PengCardVec[0][i]);
			}
			for (int j = 0; j < m_PengCardVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_PengCardVec[1][j]);
			}

			for (int i = 0; i < m_SaoCardVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_SaoCardVec[0][i]);
			}
			for (int j = 0; j < m_SaoCardVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_SaoCardVec[1][j]);
			}

			for (int i = 0; i < m_GuoSaoCardBVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_GuoSaoCardBVec[0][i]);
			}
			for (int j = 0; j < m_GuoSaoCardBVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_GuoSaoCardBVec[1][j]);
			}

			for (int i = 0; i < m_SaoChuanCardVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_SaoChuanCardVec[0][i]);
			}
			for (int j = 0; j < m_SaoChuanCardVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_SaoChuanCardVec[1][j]);
			}

			for (int i = 0; i < m_ChiCardVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_ChiCardVec[0][i]);
			}
			for (int j = 0; j < m_ChiCardVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_ChiCardVec[1][j]);
			}

			for (int i = 0; i < m_ChiSpeclal[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_ChiSpeclal[0][i]);
			}
			for (int j = 0; j < m_ChiSpeclal[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_ChiSpeclal[1][j]);
			}

			for (int i = 0; i < m_KaiDuoCardVec[0].size(); i++)
			{
				Win::getInstance()->setVector(0, m_KaiDuoCardVec[0][i]);
			}
			for (int j = 0; j < m_KaiDuoCardVec[1].size(); j++)
			{
				Win::getInstance()->setVector(1, m_KaiDuoCardVec[1][j]);
			}
		}

		return true;
	}

	return false;
}

bool	ZiPai::checkHu()
{
	/*
	先检测桌子上或手上有没有四张的：
	有四张的  手里一定要有2张重牌 才能胡
	没有四张的 手里都是三张牌型才能胡
	*/
	if (is_4_Card())	//有四张重牌  is_4_Card()
	{
		//std::cout << "有四重张的牌" << std::endl;

		//先遍历手里的牌，如果有四重张的，有三重张的，连牌，大小三搭，对子，都删掉，若零时数组为空，就胡了  这些方法可以随便组合

		//检测四张重牌
		check_4_card();
		//检测三张重牌
		check_3_card();
		//检测2 7 10
		check_2710_card();
		//检测大小三张
		check_shunzi_card();

		check_aaA_card();	//大小三张
		check_AAa_card();	//大小三张

		//检测对子
		check_2_card();
		//检测顺子
	}
	else  //没有四张的 不用检测对子，只检测都是三张的就好了
	{
		//std::cout << "没有四重张的牌" << std::endl;

		//检测三张重牌
		check_3_card();
		//检测2 7 10
		check_2710_card();
		//检测顺子
		check_shunzi_card();
		//检测大小三张
		check_aaA_card();	//大小三张
		check_AAa_card();	//大小三张
	}

	if (m_MyCard_Temp[0].empty() && m_MyCard_Temp[1].empty())
	{
		//std::cout << "恭喜你胡了" << std::endl;

		return true;
	}

	return false;
}

void	ZiPai::check_4_card()
{
	//log("-------------------------------------------------");
	if (m_MyCard_Temp[0].size() >= 4)
	{
		vector<int>::iterator it;
		vector<int> value;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end() - 3; ++it)
		{
			if (check_Hu_AAAA(*it, *(it + 1), *(it + 2), *(it + 3)))
			{
				//std::cout << "-------有四张小的重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), value[i]),
				m_MyCard_Temp[0].end()
				);
		}
		int temp_score = value.size() / 4 + 9;
		m_Score += temp_score;

		value.clear();
	}

	if (m_MyCard_Temp[1].size() >= 4)
	{
		vector<int>::iterator it;
		vector<int> value;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end() - 3; ++it)
		{
			if (check_Hu_AAAA(*it, *(it + 1), *(it + 2), *(it + 3)))
			{
				//std::cout << "-------有四张大的重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), value[i]),
				m_MyCard_Temp[1].end()
				);
		}

		int temp_score = value.size() / 4 + 12;
		m_Score += temp_score;

		value.clear();
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "-------检测完四重张-------" << endl;
}

void	ZiPai::check_3_card()
{
	log("-------------------------------------------------");

	if (m_MyCard_Temp[0].size() >= 3)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end() - 2; ++it)
		{
			if (check_Hu_AAA(*it, *(it + 1), *(it + 2)))
			{
				//std::cout << "-------发现三张小写重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), value[i]),
				m_MyCard_Temp[0].end()
				);
		}

		int temp_score = value.size() / 3 + 3;
		m_Score += temp_score;
		value.clear();
	}

	if (m_MyCard_Temp[1].size() >= 3)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end() - 2; ++it)
		{
			if (check_Hu_AAA(*it, *(it + 1), *(it + 2)))
			{
				//std::cout << "-------发现三张大写重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), value[i]),
				m_MyCard_Temp[1].end()
				);
		}
		int temp_score = value.size() / 3 + 6;
		m_Score += temp_score;
		value.clear();
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "-------检测完三重张-------" << endl;
}

void	ZiPai::check_2_card()
{
	if (m_MyCard_Temp[0].size() >= 2)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end() - 1; ++it)
		{
			if (check_Hu_AA(*it, *(it + 1)))
			{
				//std::cout << "-------发现两张小写重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), value[i]),
				m_MyCard_Temp[0].end()
				);
		}
		value.clear();
	}

	if (m_MyCard_Temp[1].size() >= 2)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end() - 1; ++it)
		{
			if (check_Hu_AA(*it, *(it + 1)))
			{
				//std::cout << "-------发现2张大写重牌--------" << std::endl;
				value.push_back(*it);
			}
		}

		for (int i = 0; i < value.size(); i++)
		{
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), value[i]),
				m_MyCard_Temp[1].end()
				);
		}
		value.clear();
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "-------检测完二重张-------" << endl;
}

void	ZiPai::check_shunzi_card()
{
	//小写三连张
	if (m_MyCard_Temp[0].size() >= 3)
	{
		std::vector<int > temp_vec_0;		//临时数组，去重用
		for (auto &num : m_MyCard_Temp[0])
		{
			temp_vec_0.push_back(num);
		}

		auto Iter_temp = std::unique(std::begin(temp_vec_0), std::end(temp_vec_0));	//去重
		temp_vec_0.erase(Iter_temp, temp_vec_0.end());

		for (auto &n : temp_vec_0)
		{
			//log("n=%d", n);
		}

		std::vector<int > value;
		vector<int>::iterator it;

		for (it = temp_vec_0.begin(); it != temp_vec_0.end() - 2; ++it)
		{

			if (check_Hu_A_B_C(*it, *(it + 1), *(it + 2)))
			{
				//log("lianpai=%d,%d,%d",*it,*(it+1),*(it +2));
				//std::cout << "小写连牌" << *it << "," << *(it + 1) << "," << *(it + 2) << endl;

				value.push_back(*it);
				value.push_back(*(it + 1));
				value.push_back(*(it + 2));
			}
		}

		std::sort(value.begin(), value.end(), [](int &a, int &b){
			return a<b;
		});

		auto Iter = std::unique(std::begin(value), std::end(value));
		value.erase(Iter, value.end());

		if (value.size() >= 3)
		{
		//	std::cout << "去重后:";
			for (int i = 0; i < value.size(); i++)
			{
				std::cout << value[i] << ",";
			}
			std::cout << endl;
			int temp;
			if (value.size() % 3 == 0)
			{
				for (int i = 0; i < value.size(); i++)
				{

					std::vector<int >::iterator iter;
					for (iter = m_MyCard_Temp[0].begin(); iter != m_MyCard_Temp[0].end();)
					{
						if (*iter == value[i])
						{
							iter = m_MyCard_Temp[0].erase(iter);

							break;
						}
						else
						{
							iter++;

						}
					}
				}
			}
			else
			{
				if (value.size() % 3 == 1)
				{
					for (int i = 0; i < value.size() - 1; i++)
					{
						std::vector<int >::iterator iter;
						for (iter = m_MyCard_Temp[0].begin(); iter != m_MyCard_Temp[0].end();)
						{
							if (*iter == value[i])
							{
								iter = m_MyCard_Temp[0].erase(iter);
								break;
							}
							else
							{
								iter++;
							}
						}
					}
				}
				else if (value.size() % 3 == 2)
				{
					for (int i = 0; i < value.size() - 2; i++)
					{
						std::vector<int >::iterator iter;
						for (iter = m_MyCard_Temp[0].begin(); iter != m_MyCard_Temp[0].end();)
						{
							if (*iter == value[i])
							{

								iter = m_MyCard_Temp[0].erase(iter);
								break;
							}
							else
							{
								iter++;
							}
						}
					}
				}
			}
		}

		value.clear();
	}
	//-------------------------------------------------------//
	//大写三连张

	if (m_MyCard_Temp[1].size() >= 3)
	{
		std::vector<int > temp_vec_1;		//临时数组，去重用
		for (auto &num : m_MyCard_Temp[1])
		{
			temp_vec_1.push_back(num);
		}

		auto Iter_temp = std::unique(std::begin(temp_vec_1), std::end(temp_vec_1));	//去重
		temp_vec_1.erase(Iter_temp, temp_vec_1.end());

		for (auto &n : temp_vec_1)
		{
			//log("n=%d", n);
		}

		std::vector<int > value;
		vector<int>::iterator it;

		for (it = temp_vec_1.begin(); it != temp_vec_1.end() - 2; ++it)
		{

			if (check_Hu_A_B_C(*it, *(it + 1), *(it + 2)))
			{
				//log("lianpai=%d,%d,%d",*it,*(it+1),*(it +2));
				//std::cout << "大写连牌" << *it << "," << *(it + 1) << "," << *(it + 2) << endl;

				value.push_back(*it);
				value.push_back(*(it + 1));
				value.push_back(*(it + 2));
			}
		}

		std::sort(value.begin(), value.end(), [](int &a, int &b){
			return a<b;
		});

		auto Iter = std::unique(std::begin(value), std::end(value));
		value.erase(Iter, value.end());

		if (value.size() >= 3)
		{
			//std::cout << "去重后:";
			for (int i = 0; i < value.size(); i++)
			{
				std::cout << value[i] << ",";
			}
			std::cout << endl;
			int temp;
			if (value.size() % 3 == 0)
			{
				for (int i = 0; i < value.size(); i++)
				{

					std::vector<int >::iterator iter;
					for (iter = m_MyCard_Temp[1].begin(); iter != m_MyCard_Temp[1].end();)
					{
						if (*iter == value[i])
						{
							iter = m_MyCard_Temp[1].erase(iter);
							break;
						}
						else
						{
							iter++;

						}
					}
				}
			}
			else
			{
				if (value.size() % 3 == 1)
				{
					for (int i = 0; i < value.size() - 1; i++)
					{
						std::vector<int >::iterator iter;
						for (iter = m_MyCard_Temp[1].begin(); iter != m_MyCard_Temp[1].end();)
						{
							if (*iter == value[i])
							{
								iter = m_MyCard_Temp[1].erase(iter);
								break;
							}
							else
							{
								iter++;
							}
						}
					}
				}
				else if (value.size() % 3 == 2)
				{
					for (int i = 0; i < value.size() - 2; i++)
					{
						std::vector<int >::iterator iter;
						for (iter = m_MyCard_Temp[1].begin(); iter != m_MyCard_Temp[1].end();)
						{
							if (*iter == value[i])
							{
								iter = m_MyCard_Temp[1].erase(iter);
								break;
							}
							else
							{
								iter++;
							}
						}
					}
				}
			}
		}

		value.clear();
	}

	//-------------------------------------------------------//
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "-------检测完大小写顺子-------" << endl;
}

void	ZiPai::check_2710_card()
{
	std::vector<int > vec_2;
	std::vector<int > vec_7;
	std::vector<int > vec_10;

	if (m_MyCard_Temp[0].size() >= 3)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end(); ++it)
		{
			if (*it == 2)
			{
				vec_2.push_back(*it);
			}

			if (*it == 7)
			{
				vec_7.push_back(*it);
			}

			if (*it == 10)
			{
				vec_10.push_back(*it);
			}
		}

		if (vec_2.size() == 2 && vec_7.size() == 2 && vec_10.size() == 2)//有两个2 7 10，全删掉
		{
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), 2),
				m_MyCard_Temp[0].end()
				);
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), 7),
				m_MyCard_Temp[0].end()
				);
			m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), 10),
				m_MyCard_Temp[0].end()
				);
			m_Score += 6;
		}
		else if (vec_2.size() >0 && vec_7.size()> 0 && vec_10.size()>0) //不是全部有两个，删掉一个2 7 10
		{
			for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end(); ++it)
			{
				if (*it == 2)
				{
					m_MyCard_Temp[0].erase(it);
					//cout << "删掉一个小2" << endl;

					break;
				}
			}
			for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end(); ++it)
			{
				if (*it == 7)
				{
					m_MyCard_Temp[0].erase(it);
					//cout << "删掉一个小7" << endl;

					break;
				}
			}
			for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end(); ++it)
			{
				if (*it == 10)
				{
					m_MyCard_Temp[0].erase(it);
					//cout << "删掉一个小10" << endl;

					break;
				}
			}
			m_Score += 3;
		}
	}
	vec_2.clear();
	vec_7.clear();
	vec_10.clear();
	//------------------------------------------------//
	//大写
	if (m_MyCard_Temp[1].size() >= 3)
	{
		std::vector<int > value;
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end(); ++it)
		{
			if (*it == 2)
			{
				vec_2.push_back(*it);
			}

			if (*it == 7)
			{
				vec_7.push_back(*it);
			}

			if (*it == 10)
			{
				vec_10.push_back(*it);
			}
		}
		if (vec_2.size() == 2 && vec_7.size() == 2 && vec_10.size() == 2)//有两个2 7 10，全删掉
		{
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), 2),
				m_MyCard_Temp[1].end()
				);
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), 7),
				m_MyCard_Temp[0].end()
				);
			m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), 10),
				m_MyCard_Temp[1].end()
				);
			m_Score += 12;
		}
		else if (vec_2.size() > 0 && vec_7.size() > 0 && vec_10.size() > 0)
		{
			for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end(); ++it)
			{
				if (*it == 2)
				{
					m_MyCard_Temp[1].erase(it);
					//cout << "删掉一个大2" << endl;
					break;
				}
			}
			for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end(); ++it)
			{
				if (*it == 7)
				{
					m_MyCard_Temp[1].erase(it);
					//cout << "删掉一个大7" << endl;
					break;
				}
			}
			for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end(); ++it)
			{
				if (*it == 10)
				{
					m_MyCard_Temp[1].erase(it);
					//cout << "删掉一个大10" << endl;
					break;
				}
			}
			m_Score += 6;

		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "-------检测完2710-------" << endl;
}

void	ZiPai::check_aaA_card()
{
	//两个小写，删一张大写
	std::vector<int > temp_vec;
	std::vector<int > erase_vec;
	if (m_MyCard_Temp[0].size() >= 2)
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end() - 1; ++it)
		{
			if (check_Hu_AA(*it, *(it + 1)))
			{
				temp_vec.push_back(*it);
			}
		}
	}
	//cout << "tempvecSize=" << temp_vec.size() << endl;

	if (m_MyCard_Temp[1].size() >= 1 && temp_vec.size() >0)//若有两个小写的
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end(); ++it)
		{
			for (int i = 0; i < temp_vec.size(); i++)
			{
				if (*it == temp_vec[i])		//若有一张大写的
				{
					//std::cout << "有大写的" << *it << "和俩小写的" << *it << "相等" << endl;
					erase_vec.push_back(*it);
				}
			}
		}
	}

	auto Iter_temp = std::unique(std::begin(erase_vec), std::end(erase_vec));	//去重
	erase_vec.erase(Iter_temp, erase_vec.end());

	for (int i = 0; i < erase_vec.size(); i++)
	{
		//cout << "erase." << erase_vec[i] << endl;
	}

	for (int i = 0; i < erase_vec.size(); i++)
	{
		m_MyCard_Temp[0].erase(std::remove(m_MyCard_Temp[0].begin(), m_MyCard_Temp[0].end(), erase_vec[i]),
			m_MyCard_Temp[0].end()
			);
	}

	for (int i = 0; i < erase_vec.size(); i++)
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end();)
		{
			if (erase_vec[i] == *it)
			{
				it = m_MyCard_Temp[1].erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
	}

	temp_vec.clear();
	erase_vec.clear();
	//--------------------------------------------------------------//

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "--------检测完大小三张,两小写一个大写----------" << endl;
}

void	ZiPai::check_AAa_card()		//大小三搭 两张大写一张小写	
{
	//两张大写，删一张小写
	std::vector<int > temp_vec;
	std::vector<int > erase_vec;

	if (m_MyCard_Temp[1].size() >= 2)
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[1].begin(); it != m_MyCard_Temp[1].end() - 1; ++it)
		{
			if (check_Hu_AA(*it, *(it + 1)))
			{
				temp_vec.push_back(*it);
			}
		}
	}

	if (m_MyCard_Temp[0].size() >= 1 && temp_vec.size() >0)//若有两个小写的
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end(); ++it)
		{
			for (int i = 0; i < temp_vec.size(); i++)
			{
				if (*it == temp_vec[i])		//若有一张大写的
				{
					//std::cout << "有小写的" << *it << "和俩大写的" << *it << "相等" << endl;
					erase_vec.push_back(*it);
				}
			}
		}
	}

	auto Iter_temp = std::unique(std::begin(erase_vec), std::end(erase_vec));	//去重
	erase_vec.erase(Iter_temp, erase_vec.end());

	for (int i = 0; i < erase_vec.size(); i++)
	{
		//cout << "erase." << erase_vec[i] << endl;

	}

	for (int i = 0; i < erase_vec.size(); i++)
	{
		m_MyCard_Temp[1].erase(std::remove(m_MyCard_Temp[1].begin(), m_MyCard_Temp[1].end(), erase_vec[i]),
			m_MyCard_Temp[1].end()
			);
	}

	for (int i = 0; i < erase_vec.size(); i++)
	{
		vector<int>::iterator it;
		for (it = m_MyCard_Temp[0].begin(); it != m_MyCard_Temp[0].end();)
		{
			if (erase_vec[i] == *it)
			{
				it = m_MyCard_Temp[0].erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
	}

	temp_vec.clear();
	erase_vec.clear();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_MyCard_Temp[i].size(); j++)
		{
			//log("%d_%d_", i, m_MyCard_Temp[i][j]);
		}
	}
	//cout << "--------检测完大小三张 两大写一个小写----------" << endl;
}

bool	ZiPai::is_4_Card()
{
	//手里的牌
	int iSize1 = m_MyCard_Temp[0].size();
	if (iSize1 >= 4)
	{
		for (int i = 0; i < m_MyCard_Temp[0].size() - 3; ++i)
		{
			if (check_Hu_AAAA(m_MyCard_Temp[0][i], m_MyCard_Temp[0][i + 1], m_MyCard_Temp[0][i + 2], m_MyCard_Temp[0][i + 3]))
			{
				return true;
			}
		}
	}

	int iSize2 = m_MyCard_Temp[1].size();
	if (iSize2 >= 4)
	{
		for (int i = 0; i < m_MyCard_Temp[1].size() - 3; ++i)
		{
			if (check_Hu_AAAA(m_MyCard_Temp[1][i], m_MyCard_Temp[1][i + 1], m_MyCard_Temp[1][i + 2], m_MyCard_Temp[1][i + 3]))
			{
				return true;
			}
		}
	}

	//桌面上的牌
	if (!m_SaoChuanCardVec[0].empty() || !m_SaoChuanCardVec[1].empty())
	{
		return true;
	}
	if (!m_KaiDuoCardVec[0].empty() || !m_KaiDuoCardVec[1].empty())
	{
		return true;
	}

	return false;
}

bool	ZiPai::check_Hu_AA(int iValue1, int iValue2)
{
	if (iValue1 == iValue2)return true;
	return false;
}

bool	ZiPai::check_Hu_AAA(int iValue1, int iValue2, int iValue3)
{
	if ((iValue1 == iValue2) && (iValue2 == iValue3))return true;
	return false;
}

bool	ZiPai::check_Hu_AAAA(int iValue1, int iValue2, int iValue3, int iValue4)
{
	if (iValue1 == iValue2&&iValue2 == iValue3&&iValue3 == iValue4)return true;

	return false;
}

bool	ZiPai::check_Hu_A_B_C(int iValue1, int iValue2, int iValue3)
{
	if (iValue1 + 1 == iValue2)
	{
		if (iValue2 + 1 == iValue3)
		{
			return true;
		}
	}
	return false;
}

int 	ZiPai::checkHushu()
{
	//胡数  手里的(已判断)，桌上
	//m_SaoChuanCardVec m_KaiDuoCardVec m_SaoCardVec m_GuoSaoCardBVec m_PengCardVec m_ChiSpeclal
	for (int i = 0; i < m_SaoChuanCardVec[0].size() / 4; i++)
	{
		m_Score += 9;
	}
	for (int i = 0; i < m_SaoChuanCardVec[1].size() / 4; i++)
	{
		m_Score += 12;
	}

	for (int i = 0; i < m_KaiDuoCardVec[0].size() / 4; i++)
	{
		m_Score += 6;
	}
	for (int i = 0; i < m_KaiDuoCardVec[1].size() / 4; i++)
	{
		m_Score += 9;

	}
	for (int i = 0; i < m_SaoCardVec[0].size() / 3; i++)
	{
		m_Score += 3;
	}
	for (int i = 0; i < m_SaoCardVec[1].size() / 3; i++)
	{
		m_Score += 6;
	}
	for (int i = 0; i < m_GuoSaoCardBVec[0].size() / 3; i++)
	{
		m_Score += 3;
	}
	for (int i = 0; i < m_GuoSaoCardBVec[1].size() / 3; i++)
	{
		m_Score += 6;
	}
	for (int i = 0; i < m_PengCardVec[0].size() / 3; i++)
	{
		m_Score += 1;
	}
	for (int i = 0; i < m_PengCardVec[1].size() / 3; i++)
	{
		m_Score += 3;
	}
	for (int i = 0; i < m_ChiSpeclal[0].size() / 3; i++)
	{
		m_Score += 3;
	}
	for (int i = 0; i < m_ChiSpeclal[1].size() / 3; i++)
	{
		m_Score += 6;
	}

	return m_Score;
}
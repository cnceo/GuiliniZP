#pragma once
#include"Win.h"
#include <iostream>  
#include <vector>  
using namespace std;

#include "cocos2d.h"

USING_NS_CC;

struct CardData
{
	int		m_Type;		//类型	
	int		m_Value;	//数值
};

//  m_Type				m_Value		每种四张牌  共80张牌
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//  
//  0  小写		 |      一 二 三 四 五 六 七 八 九 十                                      
//				 |  
//  1   大写		 |      壹 贰 叁 肆 伍 陆 柒 捌 玖 拾                           
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//  

//吃牌组合
struct ChiCard
{
	int     m_Type;             //牌类型  
	int     m_Value1;           //牌字  
	int     m_Value2;           //牌字  
	int     m_Value3;           //牌字  
};

struct ChongDuoType				//重舵类型
{
	int saoChuan_chongDuo;		//扫穿 重舵	(0 手牌扫穿，1扫的扫穿)
	int kaiDuo_chongDuo;		//开舵 重舵	(0 手牌开舵,1 扫的开舵,2 碰的开舵)
};

class ZiPai
{
public:
	ZiPai();
	~ZiPai();

public:
	std::vector<int >		m_Not_Peng[2];				//放入可以碰但是没有碰的牌
	std::vector<int >		m_Not_Chi[2];				//放入可以吃但是没有吃的牌(臭牌)

	std::vector<CardData>	m_TempPengCardVec;			//放入可碰的牌（别人打出的或摸出的）
	std::vector<int >		m_PengCardVec[2];			//放入已经碰的牌

	std::vector<CardData>	m_TempSaoCardVec;			//可扫的牌
	std::vector<int >		m_SaoCardVec[2];			//放入已经扫的牌

	std::vector<int >		m_GuoSaoCardBVec[2];		//已经过扫的牌

	std::vector<CardData>	m_TempSaoChuanCardVec;		//扫穿的牌
	std::vector<int >		m_SaoChuanCardVec[2];		//放入扫穿的牌

	std::vector<ChiCard>	m_TempChiCardVec;			//放入可吃的牌
	std::vector<CardData>	m_TempChiCardList;			//放入可吃的牌(只管A_A_a_a和A_A_a)
	std::vector<int >		m_ChiCardVec[2];			//放入已经吃的普通牌 无胡数
	//std::vector<ChiCard>    v_TempChiCardVec;			//第一个容器，显示第一层

	std::vector<int >		m_ChiSpeclal[2];			//放入吃的特殊牌型  1 2 3  ， 2 7 10

	std::vector<CardData >	m_TempKaiDuoCardVec;		//可开舵的牌
	std::vector<int >		m_KaiDuoCardVec[2];			//放入已经开舵的牌

public:

	void	logAllCard();							//打印所有手牌
	void	logAllPengCard();						//打印所有碰的牌
	void	logAllChiCard();						//打印所有吃的牌

	void	logAllTempCard();						//所有可以吃的牌

public:

	void	addCard(int p_type, int p_value);	//初始化手牌
	bool	delACard(int p_type, int p_value);	//打一张牌

public:

	//牌型检测
	bool	checkPengACard(int p_type, int p_value);			//碰
	bool	doPengACard(int p_type, int p_value);				//执行碰牌

	bool	checkSaoACard(int p_type, int p_value);				//扫
	bool	doSaoACard(int p_type, int p_value);				//执行扫牌

	bool	checkSaoChuanACard(int p_type, int p_value);		//起手三张 扫穿
	bool	doSaoChuanACard(int p_type, int p_value);			//执行起手三张扫穿

	bool	checkSao_saoChuanACard(int p_type, int p_value);	//扫的扫穿
	bool	doSao_SaoChuan(int p_type, int p_value);			//执行扫的扫穿

	bool	checkGuoSaoACard(int p_type, int p_value);			//过扫
	bool	do_guoSao(int p_type, int p_value);					//执行过扫

	bool	checkKaiduoACard(int p_type, int p_value);			//起手牌开舵
	bool	doKaiDuo(int p_type, int p_value);					//执行开舵

	bool	checkKaiDuo_Sao(int p_type, int p_value);			//扫的开舵
	bool	doSao_KaiDuo(int p_type, int p_value);				//执行扫的开舵---

	bool	checkKaiDuo_peng(int p_type, int p_value);			//碰的开舵
	bool	doPeng_kaiDuo(int p_type, int p_value);				//执行碰的开舵

	bool	checkChongDuo_saoChuan(int p_type, int p_value);	//重舵 扫穿
	bool	doChongDuo_saoChuan(int p_type, int p_value);

	bool	checkChongDuo_kaiDuo(int p_type, int p_value);		//重舵 开舵
	bool	doChongDuo_kaiDuo(int p_type, int p_value);

	bool	checkChouPai(int p_type, int p_value);				//是否臭牌（可以吃的没有吃）
	bool	checkGuoSao(int p_type, int p_value);				//是否过扫（可以碰的没有碰）

	//--------------------------------------------------//

	bool	checkChiA_B_C(int p_type, int p_value);				//吃顺牌（包括了123）
	bool	doChiA_B_C(int p_type, int p_value, int num);

	bool	checkChiACard2_7_10(int p_type, int p_value);		//吃 2， 7 ，10
	bool	doChi2_7_10(int p_type, int p_value, int num);

	bool	checkChiACard1_2_3(int p_type, int p_value);		//吃1 2 3
	bool	doChi1_2_3(int p_type, int p_value,int num);

	bool	checkChiACardA_A_a(int p_type, int p_value);		//手里两张同A.来了一张a  吃同牌
	bool	doChiA_A_a(int p_type, int p_value);

	bool	checkChiACardA_A_a_a(int p_type, int p_value);		//来了张a  手里有A a, 来了张A 手里有A a
	bool	doChiA_A_a_a(int p_type, int p_value);

	bool	checkXiaBiACard(int p_type, int p_value);			//下比
	bool    doXiaBiCard(int p_type, int p_value, int num);

	//--------------------------------------------------//

public:

	std::vector<int >	 m_MyCard[2];							//起的种牌型

	std::vector<int >	 m_DepCard[2];							//不要的牌

	std::vector<CardData > vec3;

	ChongDuoType m_type;										//重舵的类型

	//******************************************************************//
	void  CleanUp();  //清空牌 
	bool  delACard(int PaiIndex);   //打出一张手里的牌
	CardData popCard;				//打出的牌
	vector<CardData> giveUP;            //弃牌容器
	bool check(ZiPai &player, int t_Type,int t_Value);

	vector<Sprite*> ChiVec;						//吃好
	//用户状态
	int state;
	//获取，设置用户状态
	void setState(int x);
	int getState();

public:
	//--------------------------------------------------//

	bool	checkHuPai();
	bool	checkHuPai(int p_type, int p_value);										//是否胡牌
	bool	checkHu();

	void	check_4_card();	//在临时数组检测4重张 若有就从数组删掉
	void	check_3_card();	//在临时数组检测3重张 若有就从数组删掉
	void	check_2_card();	//在临时数组检测2重张 若有就从数组删掉

	void	check_shunzi_card();	//在临时数组检测顺子 若有就从数组删掉

	void	check_2710_card();		//在临时数组检2710 若有就从数组删掉

	void	check_aaA_card();		//在临时数组检大小三搭 若有就从数组删掉
	void	check_AAa_card();		//大小三搭 两张大写一张小写	

	bool	is_4_Card();			//有没有四张牌

	bool	check_Hu_AA(int iValue1, int iValue2);			//2重张
	bool	check_Hu_AAA(int iValue1, int iValue2, int iValue3);					//3重张
	bool	check_Hu_AAAA(int iValue1, int iValue2, int iValue3, int iValue4);		//4重张

	bool	check_Hu_A_B_C(int iValue1, int iValue2, int iValue3);					//三连张

	//--------------------------------------------------//

	int 	checkHushu();															//检测胡数

	std::vector<int >	 m_MyCard_Temp[2];			   			//临时牌型数组

private:
	int m_Score;

};
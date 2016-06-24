#pragma once

#include "cocos2d.h"

using namespace cocos2d;
/*
显示上家的牌
*/
class GameLayer;
class ShowCard;

class ShowZeroLayer : public Layer
{
public:

	ShowZeroLayer();
	~ShowZeroLayer();

	virtual bool init(GameLayer* _layer);
	static ShowZeroLayer* create(GameLayer* _layer);

	void initData();
	void initUI();
	GameLayer*	m_GameLayer;

public:
	void showPengCard();		//显示碰的牌
	void showKaiduoCard();		//显示开舵的牌
	void showSaochuanCard();	//显示扫穿的牌
	void showSaoCard();			//显示扫的牌
	void showChiCard();			//显示吃的牌

	void refrishCardPos();		//更新位置

private:
	Vector<ShowCard* > m_tmpPengCardVec;
	Vector<ShowCard* > m_tmpKaiDuoCardVec;
	Vector<ShowCard* > m_tmpSaoChuanCardVec;
	Vector<ShowCard* > m_tmpSaoCardVec;
	Vector<ShowCard* > m_tmpChiCardVec;

	Vector<ShowCard* > m_ThreeCardVec;		//存三张牌
	Vector<ShowCard* > m_FourCardVec;		//存四张牌
};
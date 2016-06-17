#pragma once

#include "cocos2d.h"

using namespace cocos2d;

/*
	显示玩家打的牌
*/

class GameLayer;

class ShowLayer :public Layer
{
public:

	ShowLayer();
	~ShowLayer();

	virtual bool init(GameLayer* _layer);
	static ShowLayer* create(GameLayer* _layer);
private:

	void initData();
	void initUI();

	Sprite* createBigCardSprite(int p_Type, int p_Value);
	Sprite* createSmallCardSprite(int p_Type, int p_Value);

	void createACard();

	void createANewCard();		//新摸的牌

private:
	void showPengCard();		//显示碰的牌
	void showKaiduoCard();		//显示开舵的牌
	void showSaochuanCard();	//显示扫穿的牌
	void showSaoCard();			//显示扫的牌
	void showChiCard();			//显示吃的牌

private:
	Sprite* m_ACard;
	Sprite* m_NewCard;
	GameLayer*	m_GameLayer;

	Vector<Sprite* > m_tmpPengCardList;
	Vector<Sprite* > m_tmpKaiDuoCardList;
	Vector<Sprite* > m_tmpSaoChuanCardList;
	Vector<Sprite* > m_tmpSaoCardList;
	Vector<Sprite* > m_tmpChiCardList;

};


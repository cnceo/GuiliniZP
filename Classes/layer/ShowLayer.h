#pragma once

#include "cocos2d.h"

using namespace cocos2d;

/*
	显示玩家的各种操作了的牌
*/

class GameLayer;
class ShowCard;

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

	void createACard();			//玩家出的牌

	void createANewCard();		//新摸的牌

private:
	void showPengCard();		//显示碰的牌
	void showKaiduoCard();		//显示开舵的牌
	void showSaochuanCard();	//显示扫穿的牌
	void showSaoCard();			//显示扫的牌
	void showChiCard();			//显示吃的牌

	void refrishCardPos();		//更新位置
private:
	Sprite* m_ACard;
	Sprite* m_NewCard;
	GameLayer*	m_GameLayer;

	Vector<ShowCard* > m_tmpPengCardVec;
	Vector<ShowCard* > m_tmpKaiDuoCardVec;
	Vector<ShowCard* > m_tmpSaoChuanCardVec;
	Vector<ShowCard* > m_tmpSaoCardVec;
	Vector<ShowCard* > m_tmpChiCardVec;

	Vector<ShowCard* > m_ThreeCardVec;		//存三张牌
	Vector<ShowCard* > m_FourCardVec;		//存四张牌
};

class ShowCard: public Sprite
{
	/*
		一个牌
	*/
public:
	//牌的状态
	enum STATE
	{
		Peng = 0,	//碰
		Chi,		//吃
		Sao,		//扫
		Kaiduo,		//开舵
		Saochuan,	//扫穿
		Default		//默认
	};
	ShowCard();
	~ShowCard();
	static ShowCard* create(int p_Type, int p_Value);
	bool init(int p_Type, int p_Value);
	void setState(STATE _state);
	STATE getState();
	virtual void onEnter();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

private:
	STATE m_state;
};


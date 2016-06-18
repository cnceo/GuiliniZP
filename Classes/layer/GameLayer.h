#pragma once

#include "cocos2d.h"
#include "ZiPai.h"
#include "ZiPaiManage.h"
#include "ui/UIButton.h"
#include "Card/CardSprite.h"
#include "utils/Actionstate.h"
#include "StateManager.h"

using namespace cocos2d;
using namespace ui;

/*
	0 上家
	1 下家
	2 自己
*/

class GameLayer :public Layer
{
public:

	enum GameState
	{
		NPCTurn_0=0,
		NPCTurn_1,
		MyTurn,
		OFF
	};

	GameLayer();
	~GameLayer();

	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void onEnter();

public:
	void startCallBack(Ref* ref);
	void overCallBack(Ref* ref);
	void logAllCard();
public:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

public:

	void initData();
	void initUI();

	void getANewCard();						//起一张新牌

	void xipai();

	void createMyCardWall();				//创建我的牌墙
	void removeMyCardWall();				//移除牌墙
	void setCardState();
	void refrishCardPos();					//更新位置

	virtual void update(float dt);

	void changeState(StateManager* _state);
	
public:
	//我自己检测
	bool checkPeng();
	void doPengACard();
	void chooseLayerClose();
	
	bool checkKaiduo();
	bool checkChongDuo();

	bool checkChi();
	void doChiACard();
	void showChiCardLayer();

	bool checkSaochuan();
	bool checkSao();

public:
	CardData	PopPai[3];					//玩家出的牌
	CardData    m_newCard;					//玩家起的牌

	ZiPai		t_Player[3];				//三个玩家(2是自己)

	std::vector<ChiCard>	m_TempChiCard;	//所有可吃的牌(不包括A_A_a_a和A_A_a)
	std::vector<CardData>	m_TempChiList;	//所有可吃的牌(只管A_A_a_a和A_A_a)

public:
	bool m_isStartGame;
	ZiPaiManage t_ZPManage;					//管理器

	DrawNode*	m_line;						//创建线
	CardSprite* m_TempMoveCard;		

	Vec2 m_OldPos;							//原来坐标

	Vector<CardSprite* > m_CardList;		//牌数组

	GameState m_GameState;
	StateManager* m_CurrState;
private:
	Label* m_beilv;							//倍率标签
	int _beilv;								//倍率
	Label* m_dipai;							//底牌
};


#pragma once

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

#include "GameLayer.h"

class RemainCardLayer :public Layer
{
public:
	RemainCardLayer();
	~RemainCardLayer();

	virtual bool init(GameLayer* _layer);
	static RemainCardLayer* create(GameLayer* _layer);

	//显示其他玩家的牌
	void addOtherPlayerCard();

	void showCardPoint();

	void update(float dt);
	void setCardMoveEffect_0();
	void setCardMoveEffect_1();

	//add ui
	void addUI();


private:

	//获得牌容器

	GameLayer* _gameLayer;

	//记录牌列数
	int count;
	//是否开启定时器
	bool _needVisible;
	float _SumTime;
	int			_cardCount_0;
	int			_cardCount_1;

	Sprite* bg_left;
	Sprite* bg_right;

	//存放两个对家剩余牌墙的容器
	vector<int> playerCardWall_0[2];
	vector<int> playerCardWall_1[2];

	vector<ShowCard* > showCardSprite_0;//three card
	vector<ShowCard* > showCardSprite_1;//three card

};


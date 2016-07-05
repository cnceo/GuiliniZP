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

	//��ʾ������ҵ���
	void addOtherPlayerCard();

	void showCardPoint();

	void update(float dt);
	void setCardMoveEffect_0();
	void setCardMoveEffect_1();

	//add ui
	void addUI();


private:

	//���������

	GameLayer* _gameLayer;

	//��¼������
	int count;
	//�Ƿ�����ʱ��
	bool _needVisible;
	float _SumTime;
	int			_cardCount_0;
	int			_cardCount_1;

	Sprite* bg_left;
	Sprite* bg_right;

	//��������Լ�ʣ����ǽ������
	vector<int> playerCardWall_0[2];
	vector<int> playerCardWall_1[2];

	vector<ShowCard* > showCardSprite_0;//three card
	vector<ShowCard* > showCardSprite_1;//three card

};


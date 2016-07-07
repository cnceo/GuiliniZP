#pragma once

#include "cocos2d.h"
#include "ZiPai.h"

using namespace cocos2d;

/*
	显示吃的牌
*/

class GameLayer;
class SmallCard;

class ChiCardLayer :public Layer
{
public:

	ChiCardLayer();
	~ChiCardLayer();

	virtual void onEnter();

	virtual bool init(GameLayer* _layer);
	static ChiCardLayer* create(GameLayer* _layer);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

private:

	void initData();
	void initUI();
	void checkXiabi();	//检测下比

	Sprite* createSmallCardSprite(int p_Type, int p_Value);

private:
	GameLayer* _gameLayer;
	Vector<SmallCard* > m_tmpChiCardList;		//只管连续的
	Vector<SmallCard* > m_tmpChiCardVec;		//只管A_A_a_a或A_A_a

	Vector<SmallCard*> m_allChiCardVec;			//所有能吃的

};

class SmallCard : public Node
{
public:
	bool init(int p_Type, int p_Value);
	static SmallCard* create(int p_Type, int p_Value);
	void setCardData(CardData _data);
	CardData getCardData();
private:
	CardData m_cardData;
};

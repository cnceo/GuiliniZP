#pragma once

#include "cocos2d.h"
#include "Win.h"

using namespace cocos2d;
/*
	结算界面
*/

class AccountsLayer: public LayerColor
{
public:
	AccountsLayer();
	~AccountsLayer();

	virtual bool init();
	CREATE_FUNC(AccountsLayer);
	virtual void onEnter();
public:

	void addUI();
	int getHushu();
	
public:

	void quiteCallback(Ref* sender);
	void restartCallback(Ref* sender);
	Sprite* createSmallCardSprite(int p_Type, int p_Value);
private:
	std::vector<Sprite*> SpriteVec;
};


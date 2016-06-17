#pragma once

#include "cocos2d.h"
#include "Win.h"
#include "layerUtils/Pop.h"

using namespace cocos2d;
/*
	结算界面
*/

class AccountsLayer: public Layer
{
public:
	AccountsLayer();
	~AccountsLayer();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AccountsLayer);
	virtual void onEnter();
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
public:

	void addUI();
	
public:

	void quiteCallback(Ref* sender);
	void restartCallback(Ref* sender);

private:
	std::vector<Sprite*> SpriteVec;
};


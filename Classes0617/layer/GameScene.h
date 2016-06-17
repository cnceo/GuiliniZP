#pragma once

#include "cocos2d.h"
using namespace cocos2d;

/*
游戏场景
*/

class GameScene :public Layer
{
public:

	GameScene();
	~GameScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	virtual void onEnter();

	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

private:

};


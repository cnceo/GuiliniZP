#pragma once

#include "cocos2d.h"
#include "ui/UIScrollView.h"

using namespace cocos2d;

/*
欢迎场景
*/

class WelcomeScene :public Layer
{
public:

	WelcomeScene();
	~WelcomeScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	virtual void onEnter();

	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	RepeatForever* MyPathFun(float controlX, float controlY, float w);
	ParticleSystem* particleInit();

public:
	void initUI();
	void startGameCBK(Ref* pSender);

private:
	Label* m_goldLabel;
	Label* m_diamLabel;

	ui::ScrollView*	m_scrollView;
};


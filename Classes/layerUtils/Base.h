#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Base : public Node
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void close();
	virtual void onEnterTransitionDidFinish();

public:
	virtual void createBg();

private:
	LayerColor* layercolor;

protected:
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual	void onTouchMoved(Touch *pTouch, Event  *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	Node* m_popNode;

};
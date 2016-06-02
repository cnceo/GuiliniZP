#include "Base.h"
#include "Utils/CommonFunction.h"

bool Base::init()
{
	createBg();

	m_popNode = Node::create();
	this->addChild(m_popNode, 10);

	this->setPosition(CommonFunction::getVisibleAchor(Center, Vec2::ZERO));

	return Layer::init();
}

void Base::onEnter()
{
	Layer::onEnter();

	// 屏蔽触摸
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);

	myListener->onTouchBegan = CC_CALLBACK_2(Base::onTouchBegan, this);
	myListener->onTouchMoved = CC_CALLBACK_2(Base::onTouchMoved, this);
	myListener->onTouchEnded = CC_CALLBACK_2(Base::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
	_eventDispatcher->setPriority(myListener, -128);

	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(Base::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
}

void Base::onEnterTransitionDidFinish()
{

}

void Base::createBg()
{
	/*
	1.透明
	2.不透明
	3.有渐变(没改好)
	*/
	
	auto layercolor = LayerColor::create(Color4B(0,0,0,150));
	layercolor->setOpacity(10);
	layercolor->ignoreAnchorPointForPosition(false);
	layercolor->setAnchorPoint(Vec2(0.5, 0.5));

	addChild(layercolor,-1);

	auto fadeIn = FadeIn::create(0.5f);

	layercolor->runAction(fadeIn);
}

bool Base::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void Base::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void Base::onTouchEnded(Touch *pTouch, Event *pEvent)
{

}

void Base::close()
{
	this->retain();
	if (getParent())
	{
		removeFromParent();
	}
	this->autorelease();
}

void Base::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
		{
			if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
			{
				close();
			}
		}
	}
}
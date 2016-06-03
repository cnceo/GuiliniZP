#include "Base.h"
#include "Utils/CommonFunction.h"

bool Base::init()
{
	createBg();

	m_popNode = Node::create();
	this->addChild(m_popNode, 10);
	m_popNode->setCascadeOpacityEnabled(true);
	this->setPosition(CommonFunction::getVisibleAchor(Center, Vec2::ZERO));

	return Node::init();
}

void Base::onEnter()
{
	Node::onEnter();

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
	layercolor = LayerColor::create(Color4B(0, 0, 0, 255));
	layercolor->setOpacity(0);
	layercolor->ignoreAnchorPointForPosition(false);
	layercolor->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(layercolor, -1);

	auto tintTo = FadeTo::create(0.3f, 150);
	layercolor->runAction(tintTo);
}

bool Base::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	//如果子节点的tag为99，说明是背景，点击外面背景外面移除此层，若不想用此功能可以重写此方法
	for (auto &child : m_popNode->getChildren())
	{
		if (child->getTag() == 99)
		{
			Size size = child->getContentSize();
			Rect rect = Rect(0, 0, size.width, size.height);
			Vec2 locationNode = child->convertToNodeSpace(pTouch->getLocation());

			if (!rect.containsPoint(locationNode))
			{
				close();
			}
		}
	}
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

	auto fadeTo = FadeTo::create(0.1f, 0);
	auto callFunc = CallFunc::create([this](){
		if (getParent())
		{
			removeFromParent();
		}
	});

	auto seq = Sequence::create(fadeTo, callFunc, nullptr);
	if (layercolor)
	{
		layercolor->runAction(seq);
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
#include "RotateMenu.h"  
#include <math.h>  

#define PI acos(-1)  

USING_NS_CC;

bool RotateMenu::init()
{
	if (!Layer::init())
		return false;
	_angle = 0.0;
	this->ignoreAnchorPointForPosition(false);
	_selectedItem = nullptr;
	Size winSize = Director::getInstance()->getWinSize();
	this->setContentSize(winSize / 3 * 2 + Size(100,50));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RotateMenu::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(RotateMenu::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(RotateMenu::onTouchEnded, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void RotateMenu::addMenuItem(cocos2d::MenuItem *item)
{
	if (!item){ return; }
	this->addChild(item);
	item->setPosition(this->getContentSize() / 2);
	_items.pushBack(item);
	setUnitAngle(2 * PI / _items.size());
	reset();
	updatePositionWithAnimation();
}

void RotateMenu::updatePosition()
{
	auto menuSize = getContentSize();
	auto disY = menuSize.height / 8;
	auto disX = menuSize.width / 3;

	for (int i = 0; i < _items.size(); i++)
	{
		float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
		float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
		_items.at(i)->setPosition(Vec2(x, y));
		_items.at(i)->setZOrder(-(int)y);
		//Opacity  129~255  
		_items.at(i)->setOpacity(192 + 63 * cos(i*_unitAngle + getAngle()));
		_items.at(i)->setScale(0.75 + 0.25*cos(i*_unitAngle + getAngle()));
	}
}

void RotateMenu::updatePositionWithAnimation()
{
	for (int i = 0; i < _items.size(); i++)
		_items.at(i)->stopAllActions();

	auto menuSize = getContentSize();
	auto disY = menuSize.height / 8;
	auto disX = menuSize.width / 3;
	for (int i = 0; i < _items.size(); i++)
	{
		float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
		float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
		auto moveTo = MoveTo::create(animationDuration, Vec2(x, y));
		//auto ease = EaseCircleActionOut::create(moveTo);
		//auto ease = EaseSineOut::create(moveTo);
		//auto ease = EaseQuarticActionOut::create(moveTo);
		_items.at(i)->runAction(moveTo);
		//Opacity  129~255  
		auto fadeTo = FadeTo::create(animationDuration, (192 + 63 * cos(i*_unitAngle + getAngle())));
		_items.at(i)->runAction(fadeTo);
		//缩放比例  0.5~1  
		auto scaleTo = ScaleTo::create(animationDuration, 0.75 + 0.25*cos(i*_unitAngle + getAngle()));
		_items.at(i)->runAction(scaleTo);
		_items.at(i)->setZOrder(-(int)y);
	}
	scheduleOnce(schedule_selector(RotateMenu::actionEndCallBack), animationDuration);
	return;
}
void RotateMenu::reset()
{
	_angle = 0;
}

void RotateMenu::setAngle(float angle)
{
	this->_angle = angle;
}

float RotateMenu::getAngle()
{
	return _angle;
}

void RotateMenu::setUnitAngle(float angle)
{
	_unitAngle = angle;
}

float RotateMenu::getUnitAngle()
{
	return _unitAngle;
}

float RotateMenu::disToAngle(float dis)
{
	float width = this->getContentSize().width / 2;
	return dis / width*getUnitAngle();
}

MenuItem * RotateMenu::getCurrentItem()
{
	if (_items.size() == 0)
		return nullptr;
	int  index = (int)((2 * PI - getAngle()) / getUnitAngle() + 0.1*getUnitAngle());
	index %= _items.size();
	return _items.at(index);
}

bool RotateMenu::onTouchBegan(Touch* touch, Event* event)
{
	for (int i = 0; i < _items.size(); i++)
		_items.at(i)->stopAllActions();
	if (_selectedItem)
		_selectedItem->unselected();
	auto position = this->convertToNodeSpace(touch->getLocation());
	auto size = this->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(position)){
		return true;
	}
	return false;
}

void RotateMenu::onTouchEnded(Touch* touch, Event* event)
{
	auto xDelta = touch->getLocation().x - touch->getStartLocation().x;
	rectify(xDelta>0);
	if (disToAngle(fabs(xDelta)) < getUnitAngle() / 15 && _selectedItem)	//设置灵敏度
	{
		_selectedItem->activate();
	}
	updatePositionWithAnimation();
	return;
}

void RotateMenu::onTouchMoved(Touch* touch, Event* event)
{
	auto angle = disToAngle(touch->getDelta().x);
	setAngle(getAngle() + angle);
	updatePosition();
	return;
}

void RotateMenu::rectify(bool forward)
{
	auto angle = getAngle();
	while (angle<0)
		angle += PI * 2;
	while (angle>PI * 2)
		angle -= PI * 2;
	if (forward>0)
		angle = ((int)((angle + getUnitAngle() / 3 * 2) / getUnitAngle()))*getUnitAngle();
	else
		angle = ((int)((angle + getUnitAngle() / 3) / getUnitAngle()))*getUnitAngle();
	setAngle(angle);
}

void RotateMenu::actionEndCallBack(float dx)
{
	_selectedItem = getCurrentItem();
	if (_selectedItem)
		_selectedItem->selected();
}
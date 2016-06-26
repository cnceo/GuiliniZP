#include "ChooseLayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "utils/GetLayer.h"

ChooseLayer::ChooseLayer():
m_chi_btn(nullptr),
m_peng_btn(nullptr),
m_hu_btn(nullptr),
m_close_btn(nullptr)
{
	auto _listener_1 = EventListenerCustom::create(TIMEOUT_CLOSE, [=](EventCustom*event){
		timeOutClose();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);

}

ChooseLayer::~ChooseLayer()
{
	_eventDispatcher->removeCustomEventListeners(TIMEOUT_CLOSE);
}

bool ChooseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();
	initUI();
	return true;
}

void ChooseLayer::onEnter()
{
	Layer::onEnter();

	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [](Touch*, Event*){return true; };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void ChooseLayer::initData()
{

}

void ChooseLayer::initUI()
{	
	 m_chi_btn	 = Button::create("chi.png");
	 m_peng_btn	 = Button::create("peng.png");
	 m_hu_btn		 = Button::create("hu.png");
	 m_close_btn	 = Button::create("guo.png");

	 auto node = Node::create();
	 addChild(node);
	 node->setPosition(CommonFunction::getVisibleAchor(0.6,0.5,this,Vec2(0,0)));
	 node->setScale(0.7);

	if (m_chi_btn)
	{
		m_chi_btn->setScale(0);
		node->addChild(m_chi_btn);
		m_chi_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, node, Vec2(-20, 0)));
		m_chi_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::chiBtnCbk,this));

		auto delay = DelayTime::create(0.5);
		auto scaleTo = ScaleTo::create(0.2f, 1.0f);
		auto ease = EaseBackOut::create(scaleTo);
		auto seq = Sequence::create(delay, ease, nullptr);
		m_chi_btn->runAction(seq);
	}

	if (m_peng_btn)
	{
		node->addChild(m_peng_btn);
		m_peng_btn->setScale(0);
		m_peng_btn->setPosition(CommonFunction::getVisibleAchor(0.5,0.5,node,Vec2(120,-100)));
		m_peng_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::pengBtnCbk, this));

		auto delay = DelayTime::create(0.6f);
		auto scaleTo = ScaleTo::create(0.2f, 1.0f);
		auto ease = EaseBackOut::create(scaleTo);
		auto seq = Sequence::create(delay, ease, nullptr);
		m_peng_btn->runAction(seq);
	}

	if (m_hu_btn)
	{
		node->addChild(m_hu_btn);
		m_hu_btn->setScale(0);
		m_hu_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, node, Vec2(255, -100)));
		m_hu_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::huBtnCbk, this));

		auto delay = DelayTime::create(0.7f);
		auto scaleTo = ScaleTo::create(0.2f, 1.0f);
		auto ease = EaseBackOut::create(scaleTo);
		auto seq = Sequence::create(delay, ease, nullptr);
		m_hu_btn->runAction(seq);
	}

	if (m_close_btn)
	{
		node->addChild(m_close_btn);
		m_close_btn->setScale(0);
		m_close_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, node, Vec2(380, 0)));
		m_close_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::closeBtnCbk, this));

		auto delay = DelayTime::create(0.8f);
		auto scaleTo = ScaleTo::create(0.2f, 1.2f);
		auto ease = EaseBackOut::create(scaleTo);
		auto seq = Sequence::create(delay, ease, nullptr);
		m_close_btn->runAction(seq);
	}
}

void ChooseLayer::chiBtnCbk(Ref* psender)
{
	log("chi");
	_eventDispatcher->dispatchCustomEvent(SHOW_CHICARDLAYER);
	_eventDispatcher->dispatchCustomEvent(HIDE_TIMECOUNT);

	//close();
}

void ChooseLayer::pengBtnCbk(Ref* psender)
{
	log("peng");
	//close();
	_eventDispatcher->dispatchCustomEvent(PLAYER_PENG);
	_eventDispatcher->dispatchCustomEvent(HIDE_TIMECOUNT);

	close();
}

void ChooseLayer::huBtnCbk(Ref* psender)
{
	log("hu");
	auto _newCard = GetLayer::getInstance()->getgameLayer()->m_newCard;
	GetLayer::getInstance()->getgameLayer()->t_Player[2].addCard(_newCard.m_Type, _newCard.m_Value);
	GetLayer::getInstance()->getgameLayer()->refrishCardPos();

	string str = "effect/hu.png";
	GetLayer::getInstance()->getgameLayer()->addEffect(str);

	_eventDispatcher->dispatchCustomEvent(SHOW_RATIOLAYER);
	_eventDispatcher->dispatchCustomEvent(HIDE_TIMECOUNT);

	close();
}

void ChooseLayer::closeBtnCbk(Ref* psender)
{
	log("close");
	_eventDispatcher->dispatchCustomEvent(CLOSE_CHOOSELAYER);
	_eventDispatcher->dispatchCustomEvent(HIDE_TIMECOUNT);

	close();
}

void ChooseLayer::setBtnEnable(int index)
{
	if (index <= 0 || index >4)
	{
		return;
	}

	if (index == 1) //吃牌
	{
		if (m_peng_btn && m_hu_btn )
		{
			m_peng_btn->setEnabled(false);
			m_hu_btn->setEnabled(false);
		}
	}
	else if (index == 2) //碰牌
	{
		if (m_chi_btn && m_hu_btn)
		{
			m_chi_btn->setEnabled(false);
			m_hu_btn->setEnabled(false);
		}
	}
	else if (index == 3) //胡牌
	{
		if (m_chi_btn && m_peng_btn && m_close_btn)
		{
			m_chi_btn->setEnabled(false);
			m_peng_btn->setEnabled(false);
			m_close_btn->setEnabled(false);
		}
	}
	else if (index == 4)	//可吃可碰
	{
		if (m_hu_btn)
		{
			m_hu_btn->setEnabled(false);

		}
	}
}

void ChooseLayer::close()
{
	if (this->getParent())
	{
		this->removeFromParent();
	}
}
//15秒倒计时后没有操作就过
void ChooseLayer::timeOutClose()
{
	log("time is out ,close chooseLayer");
	_eventDispatcher->dispatchCustomEvent(CLOSE_CHOOSELAYER);
	close();
}
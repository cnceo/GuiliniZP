#include "ChooseLayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"

ChooseLayer::ChooseLayer():
m_chi_btn(nullptr),
m_peng_btn(nullptr),
m_hu_btn(nullptr),
m_close_btn(nullptr)
{
	
}

ChooseLayer::~ChooseLayer()
{

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
	 m_close_btn	 = Button::create("x.png");

	 auto node = Node::create();
	 addChild(node);
	 node->setPosition(CommonFunction::getVisibleAchor(0.5,0.4,this,Vec2(100,0)));
	 node->setScale(0.7);

	if (m_chi_btn)
	{
		node->addChild(m_chi_btn);
		m_chi_btn->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, node, Vec2(0, 0)));
		m_chi_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::chiBtnCbk,this));
	}

	if (m_peng_btn)
	{
		node->addChild(m_peng_btn);
		m_peng_btn->setPosition(CommonFunction::getVisibleAchor(0.5,0.5,node,Vec2(100,0)));
		m_peng_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::pengBtnCbk, this));
	}

	if (m_hu_btn)
	{
		node->addChild(m_hu_btn);
		m_hu_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, node, Vec2(200, 0)));
		m_hu_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::huBtnCbk, this));
	}

	if (m_close_btn)
	{
		node->addChild(m_close_btn);
		m_close_btn->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, node, Vec2(300, 0)));
		m_close_btn->addClickEventListener(CC_CALLBACK_1(ChooseLayer::closeBtnCbk, this));

	}
}

void ChooseLayer::chiBtnCbk(Ref* psender)
{
	log("chi");
}

void ChooseLayer::pengBtnCbk(Ref* psender)
{
	log("peng");
	//close();
	_eventDispatcher->dispatchCustomEvent(PLAYER_PENG);
	close();
}

void ChooseLayer::huBtnCbk(Ref* psender)
{
	log("hu");
	//close();
}

void ChooseLayer::closeBtnCbk(Ref* psender)
{
	log("close");
	_eventDispatcher->dispatchCustomEvent(CLOSE_CHOOSELAYER);
	close();
}

void ChooseLayer::setBtnEnable(int index)
{
	if (index <= 0 || index >3)
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
}

void ChooseLayer::close()
{
	if (this->getParent())
	{
		this->removeFromParent();
	}
}
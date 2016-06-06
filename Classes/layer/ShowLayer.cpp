#include "ShowLayer.h"
#include "utils/CommonFunction.h"
#include "utils/Constant.h"
#include "GameLayer.h"

ShowLayer::ShowLayer():
m_GameLayer(nullptr),
m_ACard(nullptr),
m_NewCard(nullptr)
{
	//显示卡牌
	auto _listener_1 = EventListenerCustom::create(CREATE_CARD, [=](EventCustom*event){
		createACard();
	});
	
	//新的牌
	auto _listener_2 = EventListenerCustom::create(NEW_CARD, [=](EventCustom*event){
		createANewCard();
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener_1, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener_2, 1);
}

ShowLayer::~ShowLayer()
{
	_eventDispatcher->removeCustomEventListeners(CREATE_CARD);
	_eventDispatcher->removeCustomEventListeners(NEW_CARD);
}

ShowLayer* ShowLayer::create(GameLayer* _layer)
{
	ShowLayer* ret = new ShowLayer();
	if (ret && ret->init(_layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ShowLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}
	m_GameLayer = _layer;

	initData();

	initUI();

	return true;
}

void ShowLayer::initData()
{
	auto layercolor = LayerColor::create(Color4B::BLACK);
	layercolor->setOpacity(100);
	addChild(layercolor);

}

void ShowLayer::initUI()
{
	/*float x = 200;
	float y = 210;
	int count = 0;

	for (int i = 1; i <= 10;i++)
	{
		auto _card = createSmallCardSprite(0, i);
		addChild(_card);
		if (_card)
		{
			_card->setPosition(Point(x + 50 * count, y));
		}
		count++;
	}*/
}

//创建长的牌card
Sprite* ShowLayer::createBigCardSprite(int p_Type, int p_Value)
{
	Sprite* card =nullptr;
	if (p_Type == 0)
	{
		//小写 
		card = Sprite::create(StringUtils::format("chang_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		//大写 1-10.png	
		card = Sprite::create(StringUtils::format("chang_d%0d.png", p_Value));
	}
	return card;
}

//短牌创建
Sprite* ShowLayer::createSmallCardSprite(int p_Type, int p_Value)
{
	Sprite* card = nullptr;
	if (p_Type == 0)
	{
		card = Sprite::create(StringUtils::format("duanpai_x%0d.png", p_Value));
	}
	if (p_Type == 1)
	{
		card = Sprite::create(StringUtils::format("duanpai_d%0d.png", p_Value));
	}
	return card;
}

void ShowLayer::createACard()
{

	int _type = m_GameLayer->PopPai[2].m_Type;
	int _value = m_GameLayer->PopPai[2].m_Value;

	if (_type < 0 || _type > 1 || _value <= 0 || _value > 10)
	{
		log("_value or _type error0");
		return;
	}

	if (m_ACard)
	{
		if (m_ACard->getParent())
		{
			m_ACard->removeFromParent();
		}
	}

	m_ACard = createBigCardSprite(_type, _value);
	addChild(m_ACard);

	if (m_ACard)
	{
		m_ACard->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, 0)));
	}
}

void ShowLayer::createANewCard()
{
	int _type = m_GameLayer->m_newCard.m_Type;
	int _value = m_GameLayer->m_newCard.m_Value;

	if (_type < 0 || _type > 1 || _value <= 0 || _value > 10)
	{
		log("_value or _type error1");
		return;
	}

	if (m_NewCard)
	{
		if (m_NewCard->getParent())
		{
			m_NewCard->removeFromParent();
		}
	}

	m_NewCard = createBigCardSprite(_type, _value);
	addChild(m_NewCard);

	if (!m_NewCard)return;

	float height = m_NewCard->getContentSize().height;
	m_NewCard->setPosition(CommonFunction::getVisibleAchor(Anchor::MidTop, Vec2(0, height / 2)));

	auto moveTo = MoveTo::create(0.3f, CommonFunction::getVisibleAchor(Anchor::Center, Vec2(0, height + 25)));
	auto easeAction = EaseBackOut::create(moveTo);
	m_NewCard->runAction(easeAction);
}

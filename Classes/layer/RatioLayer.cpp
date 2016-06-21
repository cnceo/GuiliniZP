#include "RatioLayer.h"
#include "utils/CommonFunction.h"
#include "ZiPai.h"
#include "utils/Constant.h"

int RatioLayer::count = 0;

RatioLayer::RatioLayer():
ratio(nullptr),
_gameLayer(nullptr),
ratioNum(0)
{

}

RatioLayer::~RatioLayer()
{

}

RatioLayer* RatioLayer::create(GameLayer* _layer)
{
	RatioLayer *pRet = new(std::nothrow) RatioLayer();
	if (pRet && pRet->init(_layer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool RatioLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	_gameLayer = _layer;

	AddUI();

	checkRatio();

	return true;
}

void RatioLayer:: AddUI()
{
	//创建一个番醒label

	Label * label = Label::createWithTTF(CommonFunction::WStrToUTF8(L"翻醒:"), "fonts/Roboto-Medium.ttf", 30);
	if (label)
	{
		label->setPosition(CommonFunction::getVisibleAchor(0.6,0.8,Vec2(0,0)));
		addChild(label);
	}

	ratio = Label::createWithTTF(" ", "fonts/Roboto-Medium.ttf", 45);
	if (ratio)
	{
		ratio->setPosition(CommonFunction::getVisibleAchor(1, 0.5,label, Vec2(+15, 0)));
		label->addChild(ratio);
	}

}

void RatioLayer:: checkRatio()
{
	//起一张剩余的牌
	//CardEx r_Card = _gameLayer->t_ZPManage.GetAPai();
	_gameLayer->getANewCard();
	auto _card = _gameLayer->m_newCard;
	_eventDispatcher->dispatchCustomEvent(NEW_CARD);
	//_gameLayer->m_newCard = r_Card;
	//获得胡牌用户手里的牌墙

	if (_card.m_Type == 0)
	{
		for (int i = 0; i < _gameLayer->t_Player[2].m_MyCard[0].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_MyCard[0][i];
			if (_card.m_Value == value + 1 || _card.m_Value == value - 1)
			{
				ratioNum++;
			}
		}
	}
	if (_card.m_Type == 1)
	{
		for (int i = 0; i < _gameLayer->t_Player[2].m_MyCard[1].size(); i++)
		{
			int value = _gameLayer->t_Player[2].m_MyCard[1][i];
			if (_card.m_Value == value + 1 || _card.m_Value == value - 1)
			{
				ratioNum++;
			}
		}
	}
	count++;

	//刷新一下ratioLabel
	ratio->setString(Value(ratioNum).asString());

	log("ratio = %d", ratioNum);
	log("count = %d", count);

	if (ratioNum >= (count * 4))
	{
		log("****");
		checkRatio();
	}

}

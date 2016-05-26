
#include "AccountsLayer.h"
#include "ui/UIButton.h"
#include <iostream>
using namespace std;
using namespace ui;

#define visibleSize  Director::getInstance()->getVisibleSize()
#define WIN_DATA Win::getInstance()

AccountsLayer::AccountsLayer()
{

}

AccountsLayer::~AccountsLayer()
{
	
}

void AccountsLayer::onEnter()
{
	LayerColor::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* t,Event* e){
	
		return true;
	};
	listener->onTouchMoved = [](Touch* t, Event* e){};
	listener ->onTouchEnded = [](Touch* t, Event* e){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

bool AccountsLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}

	addUI();
	getHushu();
	return true;
}

void AccountsLayer::addUI()
{

	auto bg = Sprite::create("zhuomian.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bg);
	//胡数
	int hushu = getHushu();
	auto hushu_label = Label::createWithTTF(StringUtils::format("hushu:%d", hushu), "fonts/arial.ttf", 32);
	if (hushu_label)
	{
		hushu_label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 150);
		addChild(hushu_label);
	}


	//返回
	auto backBtn = Button::create("back.png");
	backBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::quiteCallback, this));
	backBtn->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 8));
	addChild(backBtn);

	//重新开始
	auto restartBtn = Button::create("again.png");
	restartBtn->addClickEventListener(CC_CALLBACK_1(AccountsLayer::restartCallback, this));
	restartBtn->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 8));
	addChild(restartBtn);

	for (int i = 0; i < WIN_DATA->m_vec[0].size();i++)
	{
		Sprite* card_1 = createSmallCardSprite(0, WIN_DATA->m_vec[0][i]);
		SpriteVec.push_back(card_1);
		//Sprite* a = Sprite::create("frontImage.png");
		//a->setScale(0.3f);
		SpriteVec.push_back(card_1);
		
	}

	for (int i = 0; i < WIN_DATA->m_vec[1].size(); i++)
	{
		Sprite* card_2 = createSmallCardSprite(0, WIN_DATA->m_vec[1][i]);
		SpriteVec.push_back(card_2);
		//Sprite* a = Sprite::create("bgImage.png");
		//a->setScale(0.3f);
		SpriteVec.push_back(card_2);
	}

	for (int i = 0; i < SpriteVec.size(); i++)
	{
		if (SpriteVec[i])
		{
			SpriteVec[i]->setPosition(Vec2(visibleSize.width / 3 + (i % 10)*SpriteVec[i]->getContentSize().width / 3, (i / 10)*SpriteVec[i]->getContentSize().height / 3 + 200));
			addChild(SpriteVec[i]);
		}

	}

}

int AccountsLayer::getHushu()
{
	int hushu = UserDefault::getInstance()->getIntegerForKey("HUSHU",0);
	return hushu;
}

void AccountsLayer::quiteCallback(Ref* sender)
{
	//log("back");
	WIN_DATA->clearVector();

	if (this->getParent())
	{
		this->removeFromParent();

	}
}

void AccountsLayer::restartCallback(Ref* sender)
{
	//log("again");
	WIN_DATA->clearVector();

	if (this->getParent())
	{
		this->removeFromParent();

	}
}

//短牌创建
Sprite* AccountsLayer::createSmallCardSprite(int p_Type, int p_Value)
{
	Sprite* card;
	if (p_Type == 0)
	{
		//小写 out_zipx0-10.png	
		card = Sprite::create(StringUtils::format("duanpai_x%d.png", p_Value));
		//card->setScale(0.5);
	}
	if (p_Type == 1)
	{
		//小写 out_zipx0-10.png	
		card = Sprite::create(StringUtils::format("duanpai_d%d.png", p_Value));
		//card->setScale(0.5);
	}
	return card;
}

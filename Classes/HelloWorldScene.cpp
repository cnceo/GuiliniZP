#include "HelloWorldScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else

#include <pthread.h>
#include <unistd.h>

#endif

using namespace ui;
using namespace cocostudio::timeline;
USING_NS_CC;

HelloWorld::HelloWorld():
line(nullptr),
time(nullptr),
moveCard(nullptr),
ACard(nullptr),
chupai(nullptr),
huangzhuang(nullptr),
isHzhuang(false),
isQi(false),
startGame(true)
{

}

HelloWorld::~HelloWorld()
{
	ChiVec.clear();
	m_CardWallSprite.clear();
}

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//初始化
	TimeNumber = 15;
	GetPai[0].m_NewCard.m_Value = -1; //玩家起的牌
	GetPai[0].m_NewCard.m_Type = -1; //玩家起的牌
	GetPai[1].m_NewCard.m_Type = -1;
	GetPai[1].m_NewCard.m_Value = -1; //玩家起的牌
	GetPai[2].m_NewCard.m_Type = -1;
	GetPai[2].m_NewCard.m_Value = -1; //玩家起的牌
	PopPai[0].m_Type = -1;	//玩家出的牌
	PopPai[0].m_Value = -1;	//玩家出的牌
	PopPai[1].m_Type = -1;	//玩家出的牌
	PopPai[1].m_Value = -1;	//玩家出的牌
	PopPai[2].m_Type = -1;	//玩家出的牌
	PopPai[2].m_Value = -1;	//玩家出的牌
    
   /* auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);*/

	auto bg_sp = Sprite::create("zhuomian.png");
	addChild(bg_sp);

	if (bg_sp)
	{
		float w = bg_sp->getContentSize().width;
		float h = bg_sp->getContentSize().height;

		bg_sp->setScale(visibleSize.width / w,visibleSize.height / h);

		bg_sp->setPosition(visibleSize / 2);
	}

	Label* label = Label::createWithTTF("", "fonts/arial.ttf", 30);
	label->setString("Time:");
	label->setPosition(ccp(420, 550));
	label->setColor(Color3B::YELLOW);
	//label->setFontFillColor(Color3B::YELLOW);
	//label->setFontSize(30);
	this->addChild(label);

	//time = LabelTTF::create();
	time = Label::createWithTTF("","fonts/arial.ttf",30);
	time->setString(StringUtils::format("%d", TimeNumber));
	time->setPosition(ccp(480, 550));
	//time->setFontFillColor(Color3B::YELLOW);
	//time->setFontSize(30);
	addChild(time);

	//初始化状态
	t_OtherPlayer[0].setState(-1);
	t_OtherPlayer[1].setState(-1);
	t_OtherPlayer[2].setState(-1);

	//开始游戏
	auto startButton = Button::create("CloseSelected.png", "CloseNormal.png");
	startButton->setPosition(Vec2(visibleSize.width-50,visibleSize.height/2-100));
	if (startGame)
	{
		startButton->addClickEventListener(CC_CALLBACK_1(HelloWorld::startCallBack, this));
		
	}
	else
	{
		startButton->addClickEventListener(CC_CALLBACK_1(HelloWorld::overCallBack, this));
	}
	addChild(startButton);

	chupai = Sprite::create("chupai.png");
	chupai->setPosition(Vec2(500,200));
	chupai->setVisible(false);
	addChild(chupai);

	huangzhuang = Sprite::create("huangzhuang.png");
	huangzhuang->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	huangzhuang->setVisible(false);
	addChild(huangzhuang);

	//触摸监听
	auto listenerEvent = EventListenerTouchOneByOne::create();
	listenerEvent->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listenerEvent->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listenerEvent->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEvent, this);

    return true;
}

//游戏退出回调
void HelloWorld::overCallBack(Ref* ref)
{
	//cout << "我退出" << endl;
	startGame = true;
}

//开始游戏按钮回调方法
void HelloWorld:: startCallBack(Ref* ref)
{
	if (!m_CardWallSprite.empty())
	{
		removeMyCardWall();
		m_CardWallSprite.clear();

	}

	if (startGame)
	{
		xiPai();
		startGame = false;
		huangzhuang->setVisible(false);

	}
	else
	{
		unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
		unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
		unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
		huangzhuang->setVisible(true);
		chupai->setVisible(false);
	}
}

//洗牌
void HelloWorld::xiPai()
{
	int	t_Score = 0;
	//初始化及洗牌  
	t_ZPManage.InitPai();//初始化
	//		清空牌	
	for (int i = 0; i < 3; i++)
	{
		t_OtherPlayer[i].CleanUp();
	}
	//cout << "洗牌完成" << endl;
	//cout << "起牌:========================================================" << endl;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CardEx t_pai2 = t_ZPManage.GetAPai();
			t_OtherPlayer[j].addCard(t_pai2.m_NewCard.m_Type, t_pai2.m_NewCard.m_Value);
		}
	}
	t_OtherPlayer[2].logAllCard();
	//自己做庄，起牌，显示，加入牌墙
	createMyCardWall();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//::_sleep(500);
#else
	//usleep(2000000);    
#endif
	//cout << "我坐庄" << endl;
	//打印起的牌
	CardEx t_pai = t_ZPManage.GetAPai();
	Card = t_pai.m_NewCard;
	//cout << "底牌" << t_pai.m_CardNum << endl;
	//createACard();   //显示起的牌

	t_OtherPlayer[2].addCard(t_pai.m_NewCard.m_Type, t_pai.m_NewCard.m_Value);
	removeMyCardWall();

	/*removeACard();*/
	createMyCardWall();
	t_OtherPlayer[2].logAllCard();
	//cout << "起牌:========================================================" << endl;
	t_OtherPlayer[0].logAllCard();
	//cout << "起牌:========================================================" << endl;
	t_OtherPlayer[1].logAllCard();
	//cout << "起牌:========================================================" << endl;
	Card.m_Type = -1;
	Card.m_Value = -1;

	//设置第一次状态
	t_OtherPlayer[2].setState(1);

	cout << t_OtherPlayer[2].getState() << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << endl;
	schedule(schedule_selector(HelloWorld::schePlayerCallBack_2), 1 / 30);
	//开启倒计时
	
}


//创建监听
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (t_OtherPlayer[2].getState() != 1)
	{
		return false;
	}
	else
	{
		line = DrawNode::create();
		line->drawSegment(Point(0, visibleSize.height / 2 - 50), Point(visibleSize.width, visibleSize.height / 2 - 50), 2, Color4F(0, 1, 0, 1));
		addChild(line);

		vector <SpriteData>::iterator iter = m_CardWallSprite.begin();
		for (; iter != m_CardWallSprite.end(); ++iter)
		{
			Point locationInNode = (*iter).m_card->convertToNodeSpace(touch->getLocation()); //convertToNodeSpace转换空间为节点
			Size s = (*iter).m_card->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode))
			{
				moveCard = (*iter).m_card;
				oldCardPoint = (*iter).point; //标记原来坐标
				moveCard->setLocalZOrder(20);
				setIndext((*iter).index);
				return true;
			}
		}
		//log("onTouchBegan");
		//log("x:%f,y:%f", touch->getLocation().x, touch->getLocation().y);
	}
	return false;
}
void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
	moveCard->setPosition(touch->getLocation());

}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	line->clear();
	moveCard->setLocalZOrder(10);
	if (touch->getLocation().y > visibleSize.height / 2 - 50)
	{
		t_OtherPlayer[2].delACard(getIndext());
		t_OtherPlayer[2].logAllCard();
		PopPai[2] = t_OtherPlayer[2].popCard;  //显示我打出的牌
		Card = t_OtherPlayer[2].popCard;
		createACard();
		/*setPlayerId(0);*/
		removeMyCardWall();
		createMyCardWall();
		//设置2次状态
		t_OtherPlayer[2].setState(-1);
		t_OtherPlayer[0].setState(0);
		t_OtherPlayer[1].setState(0);
		chupai->setVisible(false);

		//cout << "2" << t_OtherPlayer[2].getState() << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << endl;
		schedule(schedule_selector(HelloWorld::schePlayerCallBack_0), 1/30);
		schedule(schedule_selector(HelloWorld::schePlayerCallBack_1), 1 / 30);

	}
	else
	{
		moveCard->setPosition(oldCardPoint);
	}
}

//创建定时器
void HelloWorld:: scheCallBack_1(float dt)
{
	//倒计
	time->setString(StringUtils::format("%d", getTimeNumber()));
	setTimeNumber(getTimeNumber() - 1);
	if (getTimeNumber() < 0)
	{
		//stop
		time->removeFromParent();
		unschedule(schedule_selector(HelloWorld::scheCallBack_1));
		//强制出一张牌
	}
	
}


//GET,SET timenumber
void HelloWorld::setTimeNumber(int num)
{
	TimeNumber = num;
}
int HelloWorld::getTimeNumber()
{
	return TimeNumber;
}


void HelloWorld:: scheCallBack_2(float dt)
{
	if (getPlayerId() == 0 || getPlayerId() == 1)
	{
		checkCardWall(getPlayerId());
	}

}

//创建用户012的监听
void HelloWorld::schePlayerCallBack_0(float dt)
{
	int t_Type = Card.m_Type;
	int t_Value = Card.m_Value;
	
	if (t_OtherPlayer[0].getState() == 0)
	{
		//不可以出牌，但是检测扫穿//可以碰
		//检测胡牌
		bool isChi = true;
		if (t_OtherPlayer[0].checkHuPai(t_Type, t_Value))
			{
				//cout << "胡牌了~！" << endl;
				//停止定时器检测
				unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
				unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
				unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
				auto layer = AccountsLayer::create();
				addChild(layer);
			
			}
			//碰
			if (t_OtherPlayer[0].checkPengACard(t_Type, t_Value))
			{
				//log("p1,peng");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				::_sleep(3000);
#else
				usleep(2000000);
#endif
					removeACard();		//移除桌面上的牌
					t_OtherPlayer[0].doPengACard(t_Type, t_Value);
					createPengSprite(0);	//显示碰牌

					t_OtherPlayer[0].setState(1);
					t_OtherPlayer[1].setState(-1);
					t_OtherPlayer[2].setState(-1);
					//cout << "3" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
					isChi = false;
			}
			if (isChi)
			{
				if (t_OtherPlayer[2].getState() == -1 && t_OtherPlayer[1].getState() == 0 || isQi)
				{
					t_OtherPlayer[0].setState(3);
					//cout << "4" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				}
			}

	}
	if (t_OtherPlayer[0].getState() == 1)
	{
		//可以操作，出牌并且显示
		//检测时间
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		::_sleep(3000);
#else
		usleep(2000000);
#endif
			t_OtherPlayer[0].delACard(0);
			Card = t_OtherPlayer[0].popCard;
			createACard();

			t_OtherPlayer[1].setState(0);
			t_OtherPlayer[2].setState(0);
			t_OtherPlayer[0].setState(-1);
			isQi = false;
			//cout << "16" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
			
	}
	if (t_OtherPlayer[0].getState() == 2)
	{
		//起一张牌，并且显示
		removeACard();
		if (isHzhuang)
		{
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
			//cout << "HUANGZHUANG" << endl;
			huangzhuang->setVisible(true);
		}
		else
		{
			CardEx t_pai = t_ZPManage.GetAPai();
			isHzhuang = t_pai.IsHz;
			//cout << "底牌" << t_pai.m_CardNum << endl;
			Card = t_pai.m_NewCard;
			createACard();

			t_OtherPlayer[0].setState(0);
			t_OtherPlayer[1].setState(0);
			t_OtherPlayer[2].setState(0);
			isQi = true;
			//cout << "8" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
		}

	}

	if (t_OtherPlayer[0].getState() == 3)
	{
		//检测吃
		bool isGet = true;
			if (t_OtherPlayer[0].checkChiACard2_7_10(t_Type, t_Value))
			{
				//log("00000,2,7,10");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				::_sleep(3000);
#else
				usleep(2000000);
#endif
				t_OtherPlayer[0].doChi2_7_10(t_Type, t_Value, 0);
				removeACard();
				createSpecialSprite(0); //显示2，7，10
				
				t_OtherPlayer[0].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "5" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				isGet = false;
			}
			if (t_OtherPlayer[0].checkChiA_B_C(t_Type, t_Value))
			{
				//log("00000,3,123");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				::_sleep(3000);
#else
				usleep(2000000);
#endif
				t_OtherPlayer[0].doChiA_B_C(t_Type, t_Value, 0);
				removeACard();
				createCardVec(0);//显示吃的容器

				t_OtherPlayer[0].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "6" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				isGet = false;
			}
			if (isGet)
			{
				t_OtherPlayer[0].setState(2);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "7" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
			}
			
		//}

	}
}

void HelloWorld::schePlayerCallBack_1(float dt)
{
	int t_Type = Card.m_Type;
	int t_Value = Card.m_Value;

	if (t_OtherPlayer[1].getState() == 0)
	{
		//不可以出牌，但是检测扫穿//可以碰
		//检测胡牌
		bool isChi = true;
		if (t_OtherPlayer[0].checkHuPai(t_Type, t_Value))
		{
			//cout << "胡牌了~！" << endl;
			//停止定时器检测
			//跳转到结算界面
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
			auto layer = AccountsLayer::create();
			addChild(layer);
		}
		//碰
		if (t_OtherPlayer[1].checkPengACard(t_Type, t_Value))
		{
			//log("p2,peng");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[1].doPengACard(t_Type, t_Value);
				removeACard();		//移除桌面上的牌
				createPengSprite(1);	//显示碰牌

				//set state
				t_OtherPlayer[1].setState(1);
				t_OtherPlayer[0].setState(-1);
				t_OtherPlayer[2].setState(-1);
				cout << "9" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				isChi = false;

		}
		if (isChi)
		{
			if (t_OtherPlayer[0].getState() == -1 && t_OtherPlayer[2].getState() == 0 || isQi)
			{
				//log("p2,ischi");
				t_OtherPlayer[1].setState(3);
				//cout << "10" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

			}
		}

	}
	if (t_OtherPlayer[1].getState() == 1)
	{
		//可以操作，出牌
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		::_sleep(3000);
#else
		usleep(2000000);
#endif
			t_OtherPlayer[1].delACard(0);
			Card = t_OtherPlayer[1].popCard;
			createACard(); //显示牌

			//修改状态
			t_OtherPlayer[0].setState(0);
			t_OtherPlayer[2].setState(0);
			t_OtherPlayer[1].setState(-1);
			isQi = false;
			//cout << "14" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;


	}if (t_OtherPlayer[1].getState() == 2)
	{
		removeACard();
		if (isHzhuang)
		{
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
			//cout << "HUANGZHUANG" << endl;
			huangzhuang->setVisible(true);
		}
		else
		{
			//起一张牌
			CardEx t_pai = t_ZPManage.GetAPai();
			isHzhuang = t_pai.IsHz;
			//cout << "底牌" << t_pai.m_CardNum << endl;
			Card = t_pai.m_NewCard;
			createACard(); //显示牌


			t_OtherPlayer[1].setState(0);
			t_OtherPlayer[0].setState(0);
			t_OtherPlayer[2].setState(0);
			isQi = true;
			//cout << "19" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
		}

	}
	if (t_OtherPlayer[1].getState() == 3)
	{
		//检测吃
		bool isGet = true;
		if (t_OtherPlayer[1].checkChiACard2_7_10(t_Type, t_Value))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[1].doChi2_7_10(t_Type, t_Value, 0);
				removeACard();
				createSpecialSprite(1); //显示2，7，10

				t_OtherPlayer[1].setState(1);
				t_OtherPlayer[0].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "11" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				isGet = false;

	
		}
		if (t_OtherPlayer[1].checkChiA_B_C(t_Type, t_Value))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[1].doChiA_B_C(t_Type, t_Value, 0);
				removeACard();
				createCardVec(1);


				t_OtherPlayer[1].setState(1);
				t_OtherPlayer[0].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "12" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
				isGet = false;

	
		}
		if (isGet)
		{

				t_OtherPlayer[1].setState(2);
				t_OtherPlayer[0].setState(-1);
				t_OtherPlayer[2].setState(-1);
				//cout << "13" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;


		}
	}
}



void HelloWorld::schePlayerCallBack_2(float dt)
{
	int t_Type = Card.m_Type;
	int t_Value = Card.m_Value;

	if (t_OtherPlayer[2].getState() == 0)
	{
		//不可以出牌，但是检测扫穿//可以碰
		bool isChi = true;
		//检测胡牌
		if (t_OtherPlayer[2].checkHuPai(t_Type, t_Value))
		{
			//cout << "胡牌了~！" << endl;
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
			
			//跳转到结算界面
			auto layer = AccountsLayer::create();
			addChild(layer);

		}
		//碰
		if (t_OtherPlayer[2].checkPengACard(t_Type, t_Value))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[2].doPengACard(t_Type, t_Value);
				removeACard();
				createPengSprite(2);

				//更新牌墙
				removeMyCardWall();
				createMyCardWall();

				t_OtherPlayer[2].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[0].setState(-1);
				isChi = false;
				//cout << "21" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

		}
		if (isChi)
		{
			if (t_OtherPlayer[1].getState() == -1 && t_OtherPlayer[0].getState() == 0 || isQi)
			{
				t_OtherPlayer[2].setState(3);
				//cout << "22" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
			}
			
		}

	}
	if (t_OtherPlayer[2].getState() == 1)
	{

		chupai->setVisible(true);
		unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
		unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
		isQi = false;
		//cout << "14" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

	}
	if (t_OtherPlayer[2].getState() == 2)
	{
		removeACard();
		if (isHzhuang)
		{
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_0));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_1));
			unschedule(schedule_selector(HelloWorld::schePlayerCallBack_2));
			schedule(schedule_selector(HelloWorld::scheCallBack_1), 1);
			//cout << "HUANGZHUANG" << endl;
			huangzhuang->setVisible(true);
		}
		else
		{
			//起一张牌
			CardEx t_pai = t_ZPManage.GetAPai();
			isHzhuang = t_pai.IsHz;
			//cout << "底牌" << t_pai.m_CardNum << endl;
			Card = t_pai.m_NewCard;
			createACard(); //显示牌


			t_OtherPlayer[2].setState(0);
			t_OtherPlayer[1].setState(0);
			t_OtherPlayer[0].setState(0);
			isQi = true;
			cout << "28" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
		}
	}
	if (t_OtherPlayer[2].getState() == 3)
	{
		//检测吃	
		bool isGet = true;
		if (t_OtherPlayer[2].checkChiACard2_7_10(t_Type, t_Value))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[2].doChi2_7_10(t_Type, t_Value, 0);
				removeACard();
				createSpecialSprite(2); //显示2，7，10

				//更新牌墙
				removeMyCardWall();
				createMyCardWall();

				t_OtherPlayer[2].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[0].setState(-1);
				isGet = false;
				//cout << "23" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

		}
		if (t_OtherPlayer[2].checkChiA_B_C(t_Type, t_Value))
		{
			//if (true)
			//{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[2].doChiA_B_C(t_Type, t_Value, 0);
				removeACard();
				createCardVec(2);

				//更新牌墙
				removeMyCardWall();
				createMyCardWall();

				t_OtherPlayer[2].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[0].setState(-1);
				isGet = false;
				//cout << "24" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

			//}

		}
		if (t_OtherPlayer[2].checkChiACardA_A_a(t_Type, t_Value))
		{
			//if (true)
			//{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[2].doChiA_A_a(t_Type, t_Value); //没改
				removeACard();
				createCardVec(2);

				//更新牌墙
				removeMyCardWall();
				createMyCardWall();

				t_OtherPlayer[2].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[0].setState(-1);
				isGet = false;
				//cout << "25" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
			//}

		}
		if (t_OtherPlayer[2].checkChiACardA_A_a_a(t_Type, t_Value))
		{
			//if (true)
			//{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			::_sleep(3000);
#else
			usleep(2000000);
#endif
				t_OtherPlayer[2].doChiA_A_a_a(t_Type, t_Value);
				removeACard();
				createCardVec(2);

				//更新牌墙
				removeMyCardWall();
				createMyCardWall();

				t_OtherPlayer[2].setState(1);
				t_OtherPlayer[1].setState(-1);
				t_OtherPlayer[0].setState(-1);
				isGet = false;
				//cout << "26" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;

			//}
		}
		if (isGet)
		{
			t_OtherPlayer[2].setState(2);
			t_OtherPlayer[0].setState(-1);
			t_OtherPlayer[1].setState(-1);
			//cout << "27" << t_OtherPlayer[0].getState() << t_OtherPlayer[1].getState() << t_OtherPlayer[2].getState() << endl;
		}
	}
}


//创建长的牌card
Sprite* HelloWorld:: createBigCardSprite(int p_Type, int p_Value)
{
	Sprite* card;
	if (p_Type == 0)
	{
		//小写 out_zipx0-10.png	
		card = Sprite::create(StringUtils::format("chang_x%d.png", p_Value));
		card->setScale(0.5);
		
	}
	if (p_Type == 1)
	{
		//小写 out_zipx0-10.png	
		card = Sprite::create(StringUtils::format("chang_d%d.png", p_Value));
		card->setScale(0.5);
	}
	return card;
}

//短牌创建
Sprite* HelloWorld::createSmallCardSprite(int p_Type, int p_Value)
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



//创建吃好的牌型容器
void HelloWorld::createCardVec(int player_id)
{
	ChiVec.clear();
	int count = 0;
	if (!t_OtherPlayer[player_id].m_ChiCardVec[0].empty())
	{
		//log("hhhhhhh");
		for (int i = 0; i < t_OtherPlayer[player_id].m_ChiCardVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_ChiCardVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			ChiVec.push_back(card_1);

		}
		
	}if (!t_OtherPlayer[player_id].m_ChiCardVec[1].empty())
	{
		//log("llllllll");
		for (int i = 0; i < t_OtherPlayer[player_id].m_ChiCardVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_ChiCardVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					//card_1->setPosition(Vec2(900 + (count % 3)*card_1->getContentSize().width, (count / 3)*card_1->getContentSize().height + 400));

					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					//card_1->setPosition(Vec2(100 + (count % 3)*card_1->getContentSize().width, (count / 3)*card_1->getContentSize().height + 400));

					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					//card_1->setPosition(Vec2(200 + (count % 3)*card_1->getContentSize().width, (count / 3)*card_1->getContentSize().height + 250));


					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			ChiVec.push_back(card_1);
		}
	}

	//SpriteVec[i]->setPosition(Vec2(visibleSize.width / 3 + (i % 10)*SpriteVec[i]->getContentSize().width, (i / 10)*SpriteVec[i]->getContentSize().height + 130));
}

//移除吃好容器创建的精灵
void HelloWorld::removeCardVect(ZiPai& player)
{
	for (int i = 0; i < ChiVec.size(); i++)
	{
		ChiVec[i]->removeFromParent();
	}
}


//我的牌墙创建
void HelloWorld::createMyCardWall()
{
	float x = 200;
	float y = 110;
	int count = 0;
	if (t_OtherPlayer[2].m_MyCard[0].size()>0)
	{
		int k = 1;
		SpriteData  spriteData;
		for (int i = 0; i < t_OtherPlayer[2].m_MyCard[0].size(); i++)
		{
			Sprite * card = createBigCardSprite(0, t_OtherPlayer[2].m_MyCard[0][i]);
			spriteData.m_card = card;
			if (count == 0)
			{
				card->setPosition(Point(x, y));
				spriteData.point = Point(x, y);
			}
			if (count != 0)
			{
				card->setPosition(Point(x + 35 * count, y));
				spriteData.point = Point(x + 35 * count, y);
			}
			addChild(card);
			spriteData.index = count;
			count++;
			m_CardWallSprite.push_back(spriteData);
		}
	}
	if (t_OtherPlayer[2].m_MyCard[1].size()>0)
	{
		int k = 1;
		SpriteData  spriteData;
		for (int i = 0; i < t_OtherPlayer[2].m_MyCard[1].size(); i++)
		{
			Sprite * card = createBigCardSprite(1, t_OtherPlayer[2].m_MyCard[1][i]);
			spriteData.m_card = card;
			if (count == 0)
			{
				card->setPosition(Point(x, y));
				spriteData.point = Point(x, y);
			}
			if (count != 0)
			{
				card->setPosition(Point(x + 35 * count, y));
				spriteData.point = Point(x + 35 * count, y);
			} 
			addChild(card);
			spriteData.index = count;
			count++;
			m_CardWallSprite.push_back(spriteData);

		}
	}
}
//全部移除牌墙精灵
void HelloWorld:: removeMyCardWall()
{
	vector<SpriteData> ::iterator it = m_CardWallSprite.begin();
	for (it; it != m_CardWallSprite.end() ; it++)
	{
		(*it).m_card->removeFromParent();
	}
	m_CardWallSprite.clear();
}

//创建一张牌
void HelloWorld::createACard()
{
	ACard = createBigCardSprite(Card.m_Type,Card.m_Value);
	ACard->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(ACard);
}

//移除一张牌
void HelloWorld::removeACard()
{
	if (ACard)
	{
		ACard->removeFromParent();
		//Card.m_Type = -1;
		//Card.m_Value = -1;
	}
}


//设置下标
void  HelloWorld::setIndext(int x)
{
	indext = x;
}
//获取下标
int  HelloWorld::getIndext()
{
	return indext;
}

//设置用户id
void HelloWorld:: setPlayerId(int id)
{
	player_id = id;
}

//获取用户id
int HelloWorld::getPlayerId()
{
	return player_id;
}






//通过id判断谁检测牌墙
bool HelloWorld:: checkCardWall( int player_id)
{
//	int number = -1;
//	if (isHzhuang)
//	{
//		//log("isHz");
//	}
//	if (player_id == 0) //我的下家
//	{
//		/*::_sleep(10000);*/
//		number = 2;
//		CheckCard(number, player_id);
//		setPlayerId(1);
//		return true;
//	}
//	if (player_id == 1) //我的上家
//	{
//		/*::_sleep(10000);*/
//		number = 0;
//		CheckCard(number, player_id);
//		setPlayerId(2);
//		return true;
//	}
//	if (player_id == 2)
//	{
//		/*::_sleep(1000);*/
//		number = 1;
//		CheckCard(number, player_id);
//		setPlayerId(0);
//		return true;
//	}
	return false;
}

//检测ai吃牌
//void HelloWorld:: CheckCard(int number,int player_id)
//{
//	if (GetPai[number].m_NewCard.m_Value != -1)
//	{
//		//判断碰，扫，开招
//
//		if (t_OtherPlayer[player_id].checkChiA_B_C(GetPai[number].m_NewCard.m_Type, GetPai[number].m_NewCard.m_Value))
//		{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(1000);
//#endif
//			//cout << "我的下家吃起牌" << endl;
//			t_OtherPlayer[player_id].logAllTempCard();
//			int num = 0;
//			t_OtherPlayer[player_id].doChiA_B_C(GetPai[number].m_NewCard.m_Type, GetPai[number].m_NewCard.m_Value, num);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(5000);
//#endif
//			//移除桌面上的牌
//			removeACard();
//			//显示吃了的容器
//			createCardVec(player_id);
//			t_OtherPlayer[player_id].delACard(num);
//			PopPai[player_id] = t_OtherPlayer[player_id].popCard;
//			Card = PopPai[player_id];
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(5000);
//#endif
//			createACard();
//			//cout << "我的下家[0]出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
//			GetPai[number].m_NewCard.m_Value = -1;
//			GetPai[number].m_NewCard.m_Type = -1;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(1000);
//#endif
//		}
//		else
//		{
//			GetACard(player_id);
//			removeACard();
//			if (t_OtherPlayer[player_id].checkChiA_B_C(GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value))
//			{
//				//cout << "我的下家吃自己起的起牌" << endl;
//				t_OtherPlayer[player_id].logAllTempCard();
//				int num = 0;
//				t_OtherPlayer[player_id].doChiA_B_C(GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value,num);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(5000);
//#endif
//				//移除桌面上的牌
//				removeACard();
//				//显示吃了的容器
//				createCardVec(player_id);
//				t_OtherPlayer[player_id].delACard(num);
//				PopPai[player_id] = t_OtherPlayer[player_id].popCard;
//				Card = PopPai[player_id];
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(5000);
//#endif
//				createACard();
//				//cout << "我的下家[0]出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
//				GetPai[player_id].m_NewCard.m_Value = -1;
//				GetPai[player_id].m_NewCard.m_Type = -1;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(1000);
//#endif
//			}
//		}
//	}
//	//检测是否能吃打的，起的
//	if (PopPai[number].m_Value != -1)
//	{
//		if (t_OtherPlayer[player_id].checkChiA_B_C(PopPai[number].m_Type, PopPai[number].m_Value))
//		{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(3000);
//#endif
//			//cout << "我的下家吃打牌" << endl;
//			t_OtherPlayer[player_id].logAllTempCard();
//			int num = 0;
//			//cin >> num;
//			t_OtherPlayer[player_id].doChiA_B_C(PopPai[number].m_Type, PopPai[number].m_Value, num);
//			//出一张牌，写一个出牌函数用于ai调用
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(3000);
//#endif
//			//移除桌面上的牌
//			removeACard();
//			//显示吃了的容器
//			createCardVec(player_id);
//			t_OtherPlayer[player_id].delACard(num);
//			PopPai[player_id] = t_OtherPlayer[player_id].popCard;
//			Card = PopPai[player_id];
//			createACard();
//			//cout << "我的下家[0]出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
//			PopPai[number].m_Value = -1;
//			PopPai[number].m_Type = -1;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(3000);
//#endif
//		}
//		else
//		{
//			//cout << "我的下家起一牌：";
//			removeACard();
//			GetACard(player_id);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			::_sleep(3000);
//#endif
//			if (t_OtherPlayer[player_id].checkChiA_B_C(GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value))
//			{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(3000);
//#endif
//				//cout << "我的下家吃自己起牌" << endl;
//				t_OtherPlayer[player_id].logAllTempCard();
//				int num = 0;
//				t_OtherPlayer[player_id].doChiA_B_C(GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value, num);
//				//出一张牌，写一个出牌函数用于ai调用
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(3000);
//#endif
//				//移除桌面上的牌
//				removeACard();
//				//显示吃了的容器
//				createCardVec(player_id);
//				t_OtherPlayer[player_id].delACard(num);
//				PopPai[player_id] = t_OtherPlayer[player_id].popCard;
//				Card = PopPai[player_id];
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(3000);
//#endif
//				createACard();
//				//cout << "我的下家[0]出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
//				GetPai[player_id].m_NewCard.m_Value = -1;
//				GetPai[player_id].m_NewCard.m_Type = -1;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//				::_sleep(3000);
//#endif
//			}
//		}
//
//	}
//}



//通过id决定谁起牌并
void HelloWorld:: GetACard(int player_id)
{
	if (isHzhuang)
	{
		//cout << "跳出循环，显示黄庄" << endl;
		return;
	}
	GetPai[player_id] = t_ZPManage.GetAPai();
	Card = GetPai[player_id].m_NewCard;
	createACard();
	isHzhuang = GetPai[player_id].IsHz;
	//cout << "起的牌：" << "T:" << GetPai[player_id].m_NewCard.m_Type << "V:" << GetPai[player_id].m_NewCard.m_Value;
	cout << endl;
}
/*
//我的检测
void HelloWorld::IsMe( int player_id)
{
	int number = 1;
	if (GetPai[number].m_NewCard.m_Value != -1)
	{
		 
		log("*******************WOWOWOWOW***********************************");
		if (t_MyPlayer.check(t_MyPlayer, GetPai[number].m_NewCard.m_Type, GetPai[number].m_NewCard.m_Value))
		{
			t_MyPlayer.logAllCard();
		CINNum1:
			int indext;
			cin >> indext;
			if (t_MyPlayer.delACard(indext) == false)
			{
				cout << "没有此牌" << endl;
				goto CINNum1;
			}
			PopPai[player_id] = t_MyPlayer.popCard;
			cout << "我出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
			GetPai[number].m_NewCard.m_Value = -1;
			GetPai[number].m_NewCard.m_Type = -1;
		}
		else
		{
			log("4444444444444444444444444444444444444444444444444");
			cout << "我起一牌：";
			GetACard(player_id);
			if (t_MyPlayer.check(t_MyPlayer, GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value))
			{
				cout << "我吃自己起的牌" << endl;
				t_MyPlayer.logAllCard();
			CINNum2:
				int indext;
				cin >> indext;
				if (t_MyPlayer.delACard(indext) == false)
				{
					cout << "没有此牌" << endl;
					goto CINNum2;
				}
				PopPai[player_id] = t_MyPlayer.popCard;
				cout << "我的上家[1]出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
				GetPai[player_id].m_NewCard.m_Value = -1;
				GetPai[player_id].m_NewCard.m_Type = -1;
			}
		}
	}
	log("*******************3************************************");
	if (PopPai[number].m_Value != -1)
	{
		//检测是否能吃
		log("*******************2************************************");
		if (t_MyPlayer.check(t_MyPlayer, PopPai[number].m_Type, PopPai[number].m_Value))
		{
			cout << "我吃我的shang家打出的牌" << endl;

			t_MyPlayer.logAllCard();
		CINNum3:
			int indext;
			cin >> indext;
			if (t_MyPlayer.delACard(indext) == false)
			{
				cout << "没有此牌" << endl;
				goto CINNum3;
			}
			PopPai[player_id] = t_MyPlayer.popCard;
			cout << "我出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
			PopPai[number].m_Value = -1;
			PopPai[number].m_Type = -1;
		}
		else
		{
			GetACard(player_id);
			if (t_MyPlayer.check(t_MyPlayer, GetPai[player_id].m_NewCard.m_Type, GetPai[player_id].m_NewCard.m_Value))
			{
				cout << "我吃自己起的牌" << endl;
				t_MyPlayer.logAllCard();
			CINNum4:
				int indext;
				cin >> indext;
				if (t_MyPlayer.delACard(indext) == false)
				{
					cout << "没有此牌" << endl;
					goto CINNum4;
				}
				PopPai[player_id] = t_MyPlayer.popCard;
				cout << "我出的牌：T：" << PopPai[player_id].m_Type << "V:" << PopPai[player_id].m_Value << endl;
				GetPai[player_id].m_NewCard.m_Value = -1;
				GetPai[player_id].m_NewCard.m_Type = -1;
			}
		}
	}
	setPlayerId(0);
}
*/


//********************************************************************************************//


//创建可吃的牌容器的牌面
void HelloWorld::AllTemCardSprite(ZiPai & player)
{

	//log("-----------------------------------");
	if (!player.m_TempChiCardVec.empty())
	{
		int i = 0;
		for (int i = 0; i < player.m_TempChiCardVec.size(); ++i)
		{
			//log("[%d],%d,%d,%d", i, player.m_TempChiCardVec[i].m_Value1, player.m_TempChiCardVec[i].m_Value2, player.m_TempChiCardVec[i].m_Value3);
			Sprite* card1 = createBigCardSprite(player.m_TempChiCardVec[i].m_Type, player.m_TempChiCardVec[i].m_Value1);
			Sprite* card2 = createBigCardSprite(player.m_TempChiCardVec[i].m_Type, player.m_TempChiCardVec[i].m_Value2);
			Sprite* card3 = createBigCardSprite(player.m_TempChiCardVec[i].m_Type, player.m_TempChiCardVec[i].m_Value3);
			card1->setPosition(ccp(50 + 50 * i, 500));
			card2->setPosition(ccp(50 + 50 * i, 530));
			card3->setPosition(ccp(50 + 50 * i, 560));
			card1->setScale(0.5);
			card2->setScale(0.5);
			card3->setScale(0.5);
			addChild(card1, 3);
			addChild(card2, 2);
			addChild(card3, 1);
			i++;
		}
	}
	else
	{
		//log("size <=0");
	}
	//log("-----------------------------------");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HelloWorld::createPengSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_PengCardVec[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_PengCardVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_PengCardVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}

			}
			//ChiVec.push_back(card_1);

		}

	}if (!t_OtherPlayer[player_id].m_PengCardVec[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_PengCardVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_PengCardVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}

void HelloWorld::createSaoSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_SaoCardVec[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_SaoCardVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_SaoCardVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);

		}

	}if (!t_OtherPlayer[player_id].m_SaoCardVec[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_SaoCardVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_SaoCardVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}

void HelloWorld::createGuosaoSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_GuoSaoCardBVec[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_GuoSaoCardBVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_GuoSaoCardBVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);

		}

	}if (!t_OtherPlayer[player_id].m_GuoSaoCardBVec[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_GuoSaoCardBVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_GuoSaoCardBVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}

void HelloWorld::createSaoChuanSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_SaoChuanCardVec[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_SaoChuanCardVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_SaoChuanCardVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);

		}

	}if (!t_OtherPlayer[player_id].m_SaoChuanCardVec[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_SaoChuanCardVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_SaoChuanCardVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}

void HelloWorld::createSpecialSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_ChiSpeclal[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_ChiSpeclal[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_ChiSpeclal[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}if (!t_OtherPlayer[player_id].m_ChiSpeclal[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_ChiSpeclal[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_ChiSpeclal[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}

void HelloWorld::createKaiDuoSprite(int player_id)
{
	//ChiVec.clear();

	int count = 0;
	if (!t_OtherPlayer[player_id].m_KaiDuoCardVec[0].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_KaiDuoCardVec[0].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(0, t_OtherPlayer[player_id].m_KaiDuoCardVec[0][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}if (!t_OtherPlayer[player_id].m_KaiDuoCardVec[1].empty())
	{
		for (int i = 0; i < t_OtherPlayer[player_id].m_KaiDuoCardVec[1].size(); i++)
		{
			Sprite* card_1 = createSmallCardSprite(1, t_OtherPlayer[player_id].m_KaiDuoCardVec[1][i]);
			if (card_1)
			{
				if (player_id == 0)
				{
					card_1->setPosition(Vec2(900, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 1)
				{
					card_1->setPosition(Vec2(100, 400 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
				if (player_id == 2)
				{
					card_1->setPosition(Vec2(200, 250 + (30 * count)));
					card_1->setScale(0.3);
					addChild(card_1, count);
					count++;
				}
			}
			//ChiVec.push_back(card_1);
		}
	}
}
#pragma once

#include "cocos2d.h"

#include "ZiPai.h"
#include "ZiPaiManage.h"
#include "AccountsLayer.h"

USING_NS_CC;

struct SpriteData
{
	Sprite* m_card;
	Point   point;
	int     index;
};

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

	bool startGame;			//是否开始游戏
	ZiPai t_OtherPlayer[3];			//其他两个玩家
	//ZiPai t_MyPlayer;				//我自己
	ZiPaiManage t_ZPManage;

	CardEx GetPai[3]; //玩家起的牌
	CardData PopPai[3];	//玩家出的牌

	//创建监听
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
public:
	void createMyCardWall();				//创建我的牌墙
	void removeMyCardWall();				//移除我的牌墙
	void AllTemCardSprite(ZiPai & player);		//创建可吃容器内的精灵
	
	void createCardVec(int player_id);			//创建吃好的牌型容器
	void removeCardVect(ZiPai& player);			//移除吃好容器创建的精灵
	void createACard();							//创建一张牌
	void removeACard();							//移除一张牌

	vector<Sprite*> ChiVec;						//吃好
	//vector<Sprite*> PengVec;

	Sprite* createBigCardSprite(int p_Type, int p_Value);		//创建长牌精灵
	Sprite* createSmallCardSprite(int p_Type, int p_Value);		//创建短牌精灵

	//获取，设置下标indext
	void setIndext(int x);
	int getIndext();
	//获取，设置用户id
	void setPlayerId(int id);
	int  getPlayerId();
	//通过id判断谁检测牌墙
	bool checkCardWall( int player_id);
	//通过id决定谁起牌并
	void GetACard(int player_id);
	//使用下标获取那个玩家的牌检测
	void CheckCard(int number,int player_id);
	//我
	//void IsMe(int player_id);
	//开始游戏按钮回调方法
	void startCallBack(Ref* ref);
	//游戏退出回调
	void overCallBack(Ref* ref);

	//创建定时器
	void scheCallBack_1(float dt);
	void scheCallBack_2(float dt);
	//创建用户012的监听
	void schePlayerCallBack_0(float dt);
	void schePlayerCallBack_1(float dt);
	void schePlayerCallBack_2(float dt);

	//修改状态
	void State(int player_id);

	void createPengSprite(int player_id);
	void createSaoSprite(int player_id);
	void createGuosaoSprite(int player_id);
	void createSaoChuanSprite(int player_id);
	void createSpecialSprite(int player_id);
	void createKaiDuoSprite(int player_id);

private:
	DrawNode* line;			//创建线
	Size visibleSize;		
	Vec2 origin;
	//LabelTTF* time;				//
	Label* time;
	int TimeNumber;
	void setTimeNumber(int num);
	int  getTimeNumber();

	vector<SpriteData> m_CardWallSprite; //容器装创建牌墙精灵，数据等
	Sprite* moveCard;					 //点击需要移动的牌
	Point oldCardPoint;					 //原来卡片的坐标
	int indext;							 //下标
	bool isHzhuang;				//是否黄庄
	int player_id;						//用户id
	CardData Card;						//桌牌
	Sprite* ACard;						//牌
	bool isQi;
	Sprite* chupai;
	Sprite* huangzhuang;

	void xiPai();						//洗牌函数
	CREATE_FUNC(HelloWorld);
};

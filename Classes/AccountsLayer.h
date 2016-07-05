#pragma once

#include "cocos2d.h"
#include "Win.h"
#include "layerUtils/Pop.h"
#include "layer/ShowCard.h"
#include <vector>

#include "layer/GameLayer.h"

using	namespace std;

using namespace cocos2d;
/*
	结算界面
*/

class AccountsLayer: public Layer
{
public:
	AccountsLayer();
	~AccountsLayer();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AccountsLayer);
	virtual void onEnter();
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
public:

	void addUI();

	//显示底牌
	void showDiPai(Node* node);
	//显示赢家胡牌牌型
	void showWinCard(int player);

	void addAAaaUI(vector<int> ver[2]);
	
	void showMyCardWall(vector<int> ver[2]);

	void showThreeVer( vector<int> ver[2]);
	void showFourVer( vector<int> ver[2]);

	//添加label
	void AddLabel();
	//添加winui
	void addWinUI();

	//添加按钮特效
	RepeatForever* MyPathFun(float controlX, float controlY, float w);
	ParticleSystem* particleInit();

	void addHZUI(Node* node);
	void showTowCardVer(vector<ShowCard*> verCard);
	void showOneCardVer(vector<ShowCard*> verCard);

	void showCardPVer();
	void setCardVerPoint();

public:

	void quiteCallback(Ref* sender);
	void restartCallback(Ref* sender);

private:
	std::vector<Sprite*> SpriteVec;

	static int count;

	vector<int> Card_4[2];
	vector<int> Card_3[2];
	vector<int> Card_2[2];
	vector<int> Card_1[2];

	vector<CardPoint> showCard; //sizhangyilie
};


#pragma once

#include "cocos2d.h"
#include "Win.h"
#include "layerUtils/Pop.h"
#include "layer/ShowCard.h"
#include <vector>

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

	void showThreeVer( vector<int> ver[2], vector<ShowCard*> verCard);
	void showFourVer( vector<int> ver[2], vector<ShowCard*> verCard);
	void showThreeCardVer(vector<ShowCard*> verCard);
	void showFourCardVer(vector<ShowCard*> verCard);

	//添加label
	void AddLabel();
	//添加winui
	void addWinUI();
	
public:

	void quiteCallback(Ref* sender);
	void restartCallback(Ref* sender);

private:
	std::vector<Sprite*> SpriteVec;

	static int count;
};


#pragma once

#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;

#define VISIBLESIZE  Director::getInstance()->getVisibleSize()
//消息名称

#define CREATE_CARD "createCard"
#define NEW_CARD	"getANewCard"

#define PLAYERBLINK_0	"blink_0"				//头像跳动
#define PLAYERBLINK_1	"blink_1"
#define PLAYERBLINK_2	"blink_2"

#define PLAYER_PENG			"pengACard"			//我碰
#define PLAYER_CHI			"chiACard"			//我吃
#define CLOSE_CHOOSELAYER	"closeChooseLayer"	//关闭选择层
#define CHOOSELAYER			"chooseLayer"

#define SHOW_PENGCARD		"showPengCard"		//显示碰的牌
#define SHOW_KAIDUOCARD		"showKaiduoCard"	//显示开舵的牌
#define SHOW_SAOCHUANCARD	"showSaoChuanCard"	//显示扫穿的牌
#define SHOW_SAOCARD		"showSaoCard"		//显示扫的牌
#define SHOW_CHICARD		"showChiCard"		//显示吃的牌

#define SHOW_CHICARDLAYER	"showChiCardLayer"	//显示吃层
#define SHOW_RATIOLAYER     "showRatioLayer"	//显示番醒
#define REPLACE_ACCOUNTS    "replaceAccounts"	//跳转到结算			

//层zorder

#define CARD_ZORDER_1 10
#define CARD_ZORDER_2 20

//userdefault 数据存储

#define ISFIRSTPLAY "isFirstPlay"			//是否第一次打牌
#define ISGETORPLAY	"isGetOrPlay"			//是摸牌还是打牌   true 摸牌，false 打牌
#define ISPLAYCAED	"isPlayCard"			//我能否出牌
#define ISHZ		"ishuangzhuang"			//是否黄庄
#define GAMESTATE	"gamestate"				//游戏状态	0（上家）， 1（下家）， 2（我）
#define CHIWHAT		"chiwhat"				//吃什么牌


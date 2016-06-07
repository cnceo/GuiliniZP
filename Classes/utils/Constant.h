#pragma once

#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;

#define VISIBLESIZE  Director::getInstance()->getVisibleSize()

//消息名称

#define CREATE_CARD "createCard"
#define NEW_CARD	"getANewCard"

#define PLAYERBLINK_0	"blink_0"	//头像跳动
#define PLAYERBLINK_1	"blink_1"
#define PLAYERBLINK_2	"blink_2"

#define PLAYER_PENG			"pengACard"			//我碰
#define CLOSE_CHOOSELAYER	"closeChooseLayer"	//关闭选择层

#define SHOW_PENGCARD		"showPengCard"		//显示碰的牌
#define SHOW_KAIDUOCARD		"showKaiduoCard"	//显示开舵的牌

//层zorder

#define CARD_ZORDER_1 10
#define CARD_ZORDER_2 20
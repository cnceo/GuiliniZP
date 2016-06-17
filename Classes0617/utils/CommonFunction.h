#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"  
#include "ui/CocosGUI.h"

using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC;

//安卓的打印
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

#define  LOG_TAG    "TBU_DEBUG"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

/*
常用函数集合
*/
#define RANDOM_RANGE(start, end) (float)CCRANDOM_0_1() * (end - start) + start
#define RANDOM_VALUE(end) (float)CCRANDOM_0_1() * end 

#define WM_TIME_NUMBER 0.04

typedef void (cocos2d::Ref::*callback_CallFun)();
#define OnClickCallFunc_selector(_SELECTOR) static_cast<callback_CallFun>(&_SELECTOR)  

typedef void (cocos2d::Ref::*callback_CallFun_B)(bool flag);
#define OnClickCallFunc_selector_B(_SELECTOR) static_cast<callback_CallFun_B>(&_SELECTOR)  

typedef void (cocos2d::Ref::*callback_CallFun_I)(int guideTalkID);
#define OnClickCallFunc_selector_I(_SELECTOR) static_cast<callback_CallFun_I>(&_SELECTOR)

typedef void (cocos2d::Ref::*callback_CallFun_S)(std::string codeStr);
#define OnClickCallFunc_selector_S(_SELECTOR) static_cast<callback_CallFun_S>(&_SELECTOR)

enum Anchor
{
	LeftTop,
	LeftMid,
	LeftButtom,

	RightTop,
	RightMid,
	RightButtom,

	MidTop,
	Center,
	MidButtom
};

enum ShakeMode
{
	Slight,
	Moderation,
	Intensity,
	SlightNormal,
};

enum EaseElasticOutType
{
	Out = 1,
	in
};

class CommonFunction
{
public:
	// 基于屏幕坐标系得到对应锚点的偏移位置
	static Vec2 getVisibleAchor(Anchor anchor, Vec2 deltaPos = Vec2::ZERO);
	static Vec2 getVisibleAchor(Anchor anchor, Node * node = NULL, Vec2 deltaPos = Vec2::ZERO);
	static Vec2 getVisibleAchor(float pointx, float pointy, Vec2 deltaPos = Vec2::ZERO);
	static Vec2 getVisibleAchor(float pointx, float pointy, Node * node, Vec2 deltaPos = Vec2::ZERO);
	//static Widget * createWidgetButton(Node* childNode, float touchSizeScale = 1);
	//static cocos2d::ui::RichText* getRichtext(std::string textStr, float richWight, float richHight, bool readColor = true);

	static int htoi(std::string  s);//十六进制转十进制

	static std::string WStrToUTF8(const std::wstring& str);//转换中文
	static std::string getString(int number);//获取字符串
	static std::string getString(float number);//获取字符串
	static std::string getLableText(std::string &str, Color3B &fontColor, int &fontSize);

	static CCActionInterval * GetShakeAction(ShakeMode mode);
	static void runShakeAction(Node* runNode, ShakeMode mode);

	static CCActionInterval * setScaleto(float time, float scalNum, EaseElasticOutType type);
	static Color3B getColor(std::string clorStr);
	static std::string decodeDataBasePSW();
	static std::string& replace_all(std::string& str, const std::string& old_value, const std::string& new_value);

	static void stopAllAction(Node *node);
	static void nodeFadeOut(Node * node, float time);
	static void nodeFadeIn(Node * node, float time);
	static void stopAction(Node* node, Vec2 vec);//暂停指定对象动作

	static void nodeVisible(Node* node, bool isVisibel);
	static void setNodeOpacity(Node * node, float opacity = 0);
	static void nodeVisit(Node * node);

	static Node* getNodeChildByTag(Node * node, int childTag);
	static Sprite* MakeSpiteGray(std::string imageName);
	static std::string getImageName(int iconID);//获取图片名

	static float getWinRate();

public:
	//骨骼动画
	static cocostudio::CCArmature * loadArmature(std::string imagePath, std::string plistPath, std::string configFilePath, std::string armatureName);
	static cocostudio::CCArmature * loadArmatures(std::string imagePath, std::string plistPath, std::string configFilePath, std::string armatureName);

	static Animate* getCCAnimate(std::string imageName, float &actionTime, float intervalTime = 0.1);
	static Animate* getCCAnimate(std::string imageName, float intervalTime = 0.1);
	static Animate* getCCAnimate(std::string imageName, Size &spriteSize, float intervalTime = 0.1);
	static Animate* getCCAnimate(std::string imageName, Size &spriteSize, float &actionTime, float intervalTime = 0.1);
	//帧动画
	static Animation* createWithSingleFrameName(const char* name, float dely, int iLoops);
	static Animation* createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops);

	//时间
	static int getCurDay();
	static int getCurDay(long long timeLong);

private:
	
	static void WStrToUTF8(std::string& dest, const std::wstring& src);
};
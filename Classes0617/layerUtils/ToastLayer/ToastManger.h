#pragma once

#include "cocos2d.h"
#include "ToastLayer.h"

USING_NS_CC;

#define TOAST_LAYER_TAG 100001
/*
提示层，小的提示框
*/

class ToastManger
{
public:
	static ToastManger* getInstance();
	void createToast(std::string str);

private:
	void createToast(std::string str, Node * sceneNode);
	ToastManger();
	~ToastManger();

private:
	void creatToastLayer();

private:
	Node        *  m_scene;//场景
	ToastLayer  *  m_ToastLayer;//Toast层
};
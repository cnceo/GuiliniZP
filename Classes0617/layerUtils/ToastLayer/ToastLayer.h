#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

#define MOVE_LENGTH 50 //移动距离

class ToastLayer :public Layer
{
public:
	static  ToastLayer* create();

	ToastLayer();
	~ToastLayer();
	void addLayer(std::string str);//添加层
	void  moveNode();//移动节点


	void OnInit();//初始化

	void deleteNode(Node * node);//删除节点

public:

	std::vector<Node *> m_node;//层节点
};

class  Toast :public Layer
{
public:
	static  Toast* create(std::string str, ToastLayer * toastLayer);
	void OnInit();
	void  nodeDeleteAction();
	void  removeThis();

	ToastLayer * m_toastLayer;
	std::string m_showString;
};
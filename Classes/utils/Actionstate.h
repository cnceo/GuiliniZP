#pragma once

#include <iostream>
#include <set>
#include "cocos2d.h"
USING_NS_CC;

class Actionstate:public Ref
{
public:
    //初始化一个状态机
    bool init();

    static Actionstate* create(std::string state, std::function<void()> onEnter = nullptr);

    Actionstate(std::string state, std::function<void()> onEnter = nullptr);

    Actionstate* addState(std::string state, std::function<void()> onEnter = nullptr);

    //添加动作事件转化机制from动作to动作
    Actionstate* addEvent(std::string eventName, std::string from, std::string to);

    //判断动作状态是否存在
	//bool isContainState(std::string stateName);

	bool isContain(std::string stateName);
    //打印状态列表
    //void printState();
	void logState();

    //执行动作动画
    void doEvent(std::string eventName);

    //判断是否可以执行动画
    bool canDoEvent(std::string eventName);

    //设置状态的回调
    void setOnEnter(std::string state, std::function<void()> onEnter);

    std::string getState(){return _currentState;}

    std::string _previousState;   //保存from状态

private:
    //改变状态运行callback
    void changeToState(std::string state);

private:
    std::set<std::string> _states;

    std::unordered_map<std::string,std::unordered_map<std::string,std::string>> _events;

    std::unordered_map<std::string,std::function<void()>> _onEnters;

    std::string _currentState;    //当前状态
    
};


#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
只能是.fnt类型的字
	使用：
	runNumber = RunNumLabel::create(CommonFunction::getString(00), "fonts/fnt/huangshe.fnt", 0.5f, 0, TextHAlignment::LEFT, Vec2::ZERO);
	runNumber->setAnchorPoint(Vec2(0, 0.5));
	runNumber->setPosition(CommonFunction::getVisibleAchor(0, 1, Vec2(390, -85)));
	addChild(runNumber);
	------
	static int index = 0;
	index += 10;
	runNumber->setString(Value(index).asString());
*/
class RunNumLabel : public Node
{
public:
	static RunNumLabel* create(const std::string& str, const std::string& fntFile, float runTime = 1, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT, const Vec2& imageOffset = Vec2::ZERO);

	bool initLabel(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT, const Vec2& imageOffset = Vec2::ZERO);

	void setString(const std::string& newString);
	std::string getString();

	void setAnchorPoint(Vec2 anchor);
	Size getContentSize();

private:
	void updateNum(float dt);

private:
	float m_runTime;
	Label* m_bmfort;
	std::string m_curText;
	std::string m_lastText;
	std::string m_origText;

	int m_lastNum;

	float m_deltaUpdate;
	float m_updateValue;
};
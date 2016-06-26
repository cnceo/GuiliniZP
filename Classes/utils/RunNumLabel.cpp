#include "RunNumLabel.h"

RunNumLabel* RunNumLabel::create(const std::string& str, const std::string& fntFile, float runTime, float width /* = 0 */, TextHAlignment alignment /* = TextHAlignment::LEFT */, const Vec2& imageOffset /* = Vec2::ZERO */)
{
	RunNumLabel* pReturn = new RunNumLabel();
	if (pReturn && pReturn->initLabel(str, fntFile, width, alignment, imageOffset))
	{
		pReturn->m_runTime = runTime;

		pReturn->autorelease();

		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return nullptr;
}

bool RunNumLabel::initLabel(const std::string& str, const std::string& fntFile, float width, TextHAlignment alignment, const Vec2& imageOffset)
{
	char _num[20];
	sprintf(_num, "%d", atoi(str.c_str())); 

	m_bmfort = Label::createWithBMFont(fntFile, _num, alignment, width, imageOffset);
	this->addChild(m_bmfort);

	m_lastText = str.c_str();
	m_lastNum = atoi(m_lastText.c_str());

	schedule(schedule_selector(RunNumLabel::updateNum));
	return true;
}

void RunNumLabel::setAnchorPoint(Vec2 anchor)
{
	m_bmfort->setAnchorPoint(anchor);
}

Size RunNumLabel::getContentSize()
{
	return m_bmfort->getContentSize();
}

std::string RunNumLabel::getString()
{
	//return m_lastText;
	return m_origText;
}

void RunNumLabel::setString(const std::string& newString)
{
	m_lastText = newString;
	m_lastNum = atoi(m_lastText.c_str());
	m_origText = m_bmfort->getString();
	//m_deltaUpdate = m_runTime / ;
	m_updateValue = 0;

}

void RunNumLabel::updateNum(float dt)
{
	m_curText = m_bmfort->getString();
	int curNum = atoi(m_curText.c_str());

	if (m_lastNum > curNum)
	{
		m_updateValue += dt / m_runTime * (float)(atoi(m_lastText.c_str()) - atoi(m_origText.c_str()));

		if (m_updateValue >= 1)
		{
			curNum += (int)m_updateValue;
			m_updateValue -= (int)m_updateValue;
		}

		char _num[20];
		sprintf(_num, "%d", curNum);
		m_bmfort->setString(std::string(_num));
	}
	else if (m_lastNum == curNum)
	{
		//this->unscheduleAllSelectors();
		return;
	}
	else
	{
		char _num[20];
		sprintf(_num, "%d", m_lastNum);
		m_bmfort->setString(std::string(_num));
	}
}


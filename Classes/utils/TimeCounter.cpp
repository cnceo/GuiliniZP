#include "TimeCounter.h"

TimeCounter::TimeCounter() :m_timeLabel(nullptr)
{

}

TimeCounter::~TimeCounter()
{

}

bool TimeCounter::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_isCounting = false;
	schedule(schedule_selector(TimeCounter::myupdate),1);

	auto clock_sp = Sprite::create("clock.png");
	if (clock_sp)
	{
		addChild(clock_sp);
	}
	m_timeLabel = Label::createWithBMFont("fonts/baishe.fnt", "10",TextHAlignment::LEFT, 0,Vec2::ZERO);
	if (m_timeLabel)
	{
		addChild(m_timeLabel);
	}
	return true;
}

void TimeCounter::myupdate(float dt)
{
	if (m_isCounting == false)
	{
		return;
	}

	m_fCBTime--;
	if (m_timeLabel)
	{
		m_timeLabel->setString(Value(m_fCBTime).asString());
	}
	if (m_fCBTime == 0)
	{
		m_func();
		m_isCounting = false;
	}
}

void TimeCounter::start(int fCBTime, std::function<void()>func)
{
	if (m_timeLabel)
	{
		m_timeLabel->setString(Value(fCBTime).asString());

	}
	m_fCBTime = fCBTime;
	m_func = func;
	m_isCounting = true;
}
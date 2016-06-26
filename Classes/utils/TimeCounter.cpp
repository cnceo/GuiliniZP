#include "TimeCounter.h"
#include "utils/Constant.h"

TimeCounter::TimeCounter() :m_timeLabel(nullptr), _clock_sp(nullptr)
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

	 _clock_sp = Sprite::create("clock.png");
	 if (_clock_sp)
	{
		 addChild(_clock_sp);
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
	if (_clock_sp)
	{
		if (m_fCBTime >5)
		{
			_clock_sp->stopAllActions();
			_clock_sp->setRotation(0);
		}
		else
		{
			auto rotate_1 = RotateTo::create(0.25f, -45);
			auto rotate_2 = RotateTo::create(0.25f, 45);
			auto seq = Sequence::create(rotate_1, rotate_2, nullptr);
			auto repeat = RepeatForever::create(seq);
			_clock_sp->runAction(repeat);
		}

		if (m_fCBTime == 3)
		{
		//	//在屏幕中间显示倒计时
			std::cout << "时间少于三秒" << std::endl;
			_eventDispatcher->dispatchCustomEvent(SHOW_TIMECOUNT);
		}
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

	if (_clock_sp)
	{
		if (m_fCBTime > 5)
		{
			_clock_sp->stopAllActions();
			_clock_sp->setRotation(0);
		}
	}
}
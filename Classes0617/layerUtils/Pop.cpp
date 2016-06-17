#include "Pop.h"

bool Pop::init()
{
	return Base::init();
}

void Pop::onEnter()
{
	Base::onEnter();

	m_popNode->setOpacity(250);

	auto scaleTo_1 = ScaleTo::create(0.1f, 1.2f);
	auto scaleTo_2 = ScaleTo::create(0.1f, 1.0f);
	auto fadeTo = FadeTo::create(0.05f, 255);

	auto spawn = Sequence::create(scaleTo_1, scaleTo_2, fadeTo, nullptr);

	m_popNode->runAction(spawn);
}

void Pop::close()
{
	auto scaleTo_1 = ScaleTo::create(0.1f, 1.2f);
	auto scaleTo_2 = ScaleTo::create(0.1f, 1.0f);

	auto fadeTo = FadeTo::create(0.1f, 0);
	auto callFunc = CallFunc::create(this, callfunc_selector(Pop::onExitAnimComplete));

	auto spawn = Spawn::create(scaleTo_2, fadeTo, callFunc, nullptr);
	auto seq = Sequence::create(scaleTo_1, spawn, nullptr);

	m_popNode->runAction(seq);
}

void Pop::onEnterAnimComplete()
{

}

void Pop::onExitAnimComplete()
{
	Base::close();
}
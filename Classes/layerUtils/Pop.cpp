#include "Pop.h"
#include "utils/CommonFunction.h"

bool Pop::init()
{
	return Base::init();
}

void Pop::onEnter()
{
	Base::onEnter();

	auto scaleTo_1 = ScaleTo::create(0.1f,1.2f);
	auto scaleTo_2 = ScaleTo::create(0.1f,1.0f);
	auto spawn = Sequence::create(scaleTo_1, scaleTo_2, nullptr);
	m_popNode->runAction(spawn);
}

void Pop::close()
{
	auto scaleTo_1 = ScaleTo::create(0.1f, 1.2f);
	auto scaleTo_2 = ScaleTo::create(0.1f, 1.0f);
	auto fadeOut = FadeOut::create(0.1f);
	auto callFunc = CallFunc::create(this, callfunc_selector(Pop::onExitAnimComplete));
	auto spawn = Spawn::create(scaleTo_2,fadeOut,nullptr);
	auto seq = Sequence::create(scaleTo_1, spawn, callFunc, nullptr);

	m_popNode->runAction(seq);
}

void Pop::onEnterAnimComplete()
{

}

void Pop::onExitAnimComplete()
{
	Base::close();
}

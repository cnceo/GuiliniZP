#include "TestPopLayer.h"

TestPopLayer::TestPopLayer()
{

}

TestPopLayer::~TestPopLayer()
{

}

bool TestPopLayer::init()
{
	if (!Pop::init()) return false;
		
	initUI();
	return true;
}


void TestPopLayer::initData()
{

}

void TestPopLayer::initUI()
{
	auto sp = Sprite::create("HelloWorld.png");
	sp->setTag(99);
	m_popNode->addChild(sp);
}
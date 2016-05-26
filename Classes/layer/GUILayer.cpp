#include "GUILayer.h"

GUILayer::GUILayer()
{

}

GUILayer::~GUILayer()
{

}

bool GUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();
	initUI();

	return true;
}

void GUILayer::initData()
{

}

void GUILayer::initUI()
{

}
#include "GetLayer.h"
#include "layer/GameLayer.h"

GetLayer* GetLayer::_instance = nullptr;

GetLayer::GetLayer():
_gameLayer(nullptr),
_oneLayer(nullptr),
_zeroLayer(nullptr)
{
}

GetLayer::~GetLayer()
{
	purgeInstance();
}

GetLayer* GetLayer::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) GetLayer();
	}
	return _instance;
}

bool GetLayer::purgeInstance()
{
	CCASSERT(_instance, "instance can not emptoy");
	if (_instance){
		delete _instance;
		_instance = nullptr;
	}
	return true;
}

void GetLayer::setgameLayer(GameLayer* _gLayer)
{
	if (!_gLayer)
	{
		return;
	}
	_gameLayer = _gLayer;
}

GameLayer* GetLayer::getgameLayer()
{
	if (_gameLayer)
	{
		return _gameLayer;
	}
	return nullptr;
}

void GetLayer::setOneLayer(ShowOneLayer* _sLayer)
{
	if (!_sLayer)
	{
		return;
	}
	_oneLayer = _sLayer;
}

ShowOneLayer* GetLayer::getOneLayer()
{
	if (_oneLayer)
	{
		return _oneLayer;
	}
	return nullptr;
}

void GetLayer::setZeroLayer(ShowZeroLayer* _sLayer)
{
	if (!_sLayer)
	{
		return;
	}
	_zeroLayer = _sLayer;
}

ShowZeroLayer* GetLayer::getZeroLayer()
{
	if (_zeroLayer)
	{
		return _zeroLayer;
	}
	return nullptr;
}
#include "GameScene.h"
#include "GameLayer.h"
#include "GUILayer.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addChild(GameLayer::create());
	addChild(GUILayer::create());
	return true;

}
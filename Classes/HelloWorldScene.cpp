#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SkiGame.h"
#include "EndGame.h"

#include <cstdlib>
#include <ctime>


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");
	
	addChild(rootNode);

	auto StartButton = rootNode->getChildByName<cocos2d::ui::Button*>("StartButton");
	auto ExitButton = rootNode->getChildByName<cocos2d::ui::Button*>("ExitButton");

	StartButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = SkiGame::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

	ExitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			CCDirector::getInstance()->end();
		}
	});

 

    return true;
}

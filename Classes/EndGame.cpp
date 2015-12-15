#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EndGame.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* EndGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	
    auto rootNode = CSLoader::createNode("EndGame.csb");

    addChild(rootNode);

	auto MenuButton = rootNode->getChildByName<cocos2d::ui::Button*>("MainButton");

	backButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::widget::TouchEventType Event))
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			autoscene = HelloWorld::createScene();
			director::getInstance()->replaceScene(scene)
		}
	}

    return true;
}


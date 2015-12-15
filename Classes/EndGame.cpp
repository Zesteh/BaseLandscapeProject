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
	auto LosingDisplay = rootNode->getChildByName<cocos2d::ui::Text*>("Losing Display");
	auto MenuButton = rootNode->getChildByName<cocos2d::ui::Button*>("MainButton");
	//LosingDisplay->setString(StringUtils::format("%s %d", "Score:", ShownScore, "Speed:", ShownSpeed));
	MenuButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

    return true;
}


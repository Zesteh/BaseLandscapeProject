#include "SkiGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EndGame.h"
// Includes required for Pseudo Random Numbers
#include <cstdlib>
#include <ctime>


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SkiGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SkiGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SkiGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// First, lets create our seed for the random number generator
	srand(time(NULL));
    //NEED THE SKIER BACKGROUND .CSB
    auto rootNode = CSLoader::createNode("SkiGame.csb");

    addChild(rootNode);
	//setting the values
	jumpButtonTouched = false;
	duckButtonTouched = false;
	pauseButtonTouched = false;
	int ShownLives = 3;
	int ShownScore = 0;
	int ShownSpeed = 1;
/*
	cocos2d::Sprite* BG1;
    cocos2d::Sprite* BG2;
	cocos2d::Sprite* Skier;
	cocos2d::ui::Text* lives;
	cocos2d::ui::Text* Score;
	cocos2d::ui::Text* Speed;
	cocos2d::ui::Text* LosingdisplayText;
	cocos2d::ui::button* PauseButton;
	cocos2d::ui::button* gameOverButton;
	gameOverButton = (ui::Button*)rootNode->getChildByName("GameOverButton");
	cocos2d::ui::Text* LosingDisplay;
	LosingDisplay = (ui::Text*)rootNode->getChildByName("Losing Display")
*/
	BG1 = (Sprite*)rootNode->getChildByName("BG1");
	BG2 = (Sprite*)rootNode->getChildByName("BG2");
	Skier = (Sprite*)rootNode->getChildByName("Skier");
	Lives = (ui::Text*)rootNode->getChildByName("Lives");
	Score = (ui::Text*)rootNode->getChildByName("Score");
	Speed = (ui::Text*)rootNode->getChildByName("Speed");
	
	PauseButton = (ui::Button*)rootNode->getChildByName("PauseButton");

	//allow jumping of objects
	auto JumpButton = rootNode->getChildByName<cocos2d::ui::Button*>("JumpButton");
		JumpButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{

		if (pressed == ui::Widget::TouchEventType::BEGAN)
		{
			jumpButtonTouched = true;
		}
		else if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			jumpButtonTouched = false;
		}
	});
	//allow ducking of objects
		auto DuckButton = rootNode->getChildByName<cocos2d::ui::Button*>("DuckButton");
		DuckButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{

		if (pressed == ui::Widget::TouchEventType::BEGAN)
		{
			duckButtonTouched = true;
		}
		else if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			duckButtonTouched = false;
		}
	});
	//allow player to pause and resume game
		auto PauseButton = rootNode->getChildByName<cocos2d::ui::Button*>("PauseButton");
		PauseButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{

		if (pressed == ui::Widget::TouchEventType::BEGAN)
		{
			pauseButtonTouched = true;
		}
		else if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			pauseButtonTouched = false;
		}
	});
	//take you back to main menu
	

	
	

    return true;
}

void SkiGame::update(float variable)
{
	if (ShownLives <= 0)
	{


		auto scene = EndGame::createScene();
		Director::getInstance()->replaceScene(scene);
			/*ShownLives = 0;
			Lives->setString(StringUtils::format("%s %d", "Lives:", ShownLives));

			LosingDisplay->setString(StringUtils::format("%s %d", "Score:", ShownScore, "Speed:", ShownSpeed));
			losingDisplay->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 4, Director::getInstance()->getVisibleSize().height / 4))
			gameOverButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2))*/
	}
	else
	{
		Lives->setString(StringUtils::format("%s %d", "Lives:", ShownLives));
		Score->setString(StringUtils::format("%s %d", "Score:", ShownScore));

		//Background Scrolling
		//setting positions
		BG1->setAnchorPoint(Vec2(0, 0));
		BG1->setPosition(Vec2(0, 0));
		BG2->setAnchorPoint(Vec2(0, 0));
		BG2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width, 0));

		//movement action
		auto Movement = MoveBy::create(3, Vec2(100, 100));
		BG1->runAction(Movement);
		BG2->runAction(Movement);

		if (BG1->getPositionX() == -960)
		{
			BG1->setPosition(Vec2(960, 0));
		}
		else if (BG2->getPositionX() == -960)
		{
			BG2->setPosition(Vec2(960, 0));
		}

		//boulders and birds movement
		//need random generation of birds and boulders and setting their positions
		//need a collision detection for skier and birds
		//auto ObsMove = MoveBy::create(3, Vec2(2,2)); //need to find out what movement is needed.

	}
}


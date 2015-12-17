#include "SkiGame.h"
#include "cocostudio/CocoStudio.h"
#include "EndGame.h"
#include "HelloWorldScene.h"


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
	if (!Layer::init())
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
	ShownLives = 3;
	ShownScore = 0;
	ShownSpeed = 1;

	
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
		Birdie = (Sprite*)rootNode->getChildByName("Birdie");
		Boulder = (Sprite*)rootNode->getChildByName("Boulder");
		BG1 = (Sprite*)rootNode->getChildByName("BG1");
		BG2 = (Sprite*)rootNode->getChildByName("BG2");
		Skier = (Sprite*)rootNode->getChildByName("Skier");
		Lives = (ui::Text*)rootNode->getChildByName("Lives");
		Score = (ui::Text*)rootNode->getChildByName("Score");
		Speed = (ui::Text*)rootNode->getChildByName("Speed");

		/*PauseButton = (ui::Button*)rootNode->getChildByName("PauseButton");*/

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
		/*	auto PauseButton = rootNode->getChildByName<cocos2d::ui::Button*>("PauseButton");
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
			});*/



		this->scheduleUpdate();


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
			Speed->setString(StringUtils::format("%s %d", "Speed:", ShownSpeed));
			//Background Scrolling
			//setting positions
		

			//BG movement action
			auto BG1Movement = MoveBy::create(1, Vec2(-5, 0));
			auto BG2Movement = MoveBy::create(1, Vec2(-5, 0));
			BG1->runAction(BG1Movement);
			BG2->runAction(BG2Movement);

			if (BG1->getPositionX() <= -960)
			{
				BG1->setPosition(Vec2(960, 0));
			}
			else if (BG2->getPositionX() <= -960)
			{
				BG2->setPosition(Vec2(960, 0));
			}
			//Obstacle movement
			if (Birdie->getPositionX() <= 0 || Birdie->getPositionX() >= 960)
			{
				auto boulderMovement = MoveBy::create(35, Vec2(-30, 2));
				Boulder->runAction(boulderMovement);

				if (Boulder->getPositionX() <= -500)
				{
					Boulder->setPosition(1044, 158);
				}

				if (collisions(Skier, Boulder))
				{
					ShownLives--;
					Boulder->setPosition(1044, 158);
				}
				else
				{
					ShownScore++;
				}
			}
			if (Boulder->getPositionX() <= 0 || Boulder->getPositionX() >= 960)
			{
			
			auto BirdieMovement = MoveBy::create(47, Vec2(-30, 3));
			Birdie->runAction(BirdieMovement);
			if (Birdie->getPositionX() <= -500)
			{
				Birdie->setPosition(1480, 245);
			}

			if (collisions(Skier, Birdie))
			{
				ShownLives--;
				Birdie->setPosition(1480, 245);
			}
			else
			{
				ShownScore++;
			}
			}
			//Skier Movement
			auto SkierUp = MoveBy::create(2, Vec2(0, 45));
			auto SkierDuck = MoveBy::create(2, Vec2(0, -45));

			if (jumpButtonTouched == true && Skier->getPositionY() <= 285)
			{
				Skier->runAction(SkierUp);
				if (Skier->runAction(SkierUp))
				{
					Skier->runAction(SkierDuck);
				}
			}
			if (duckButtonTouched == true && Skier->getPositionY() >= 225)
			{
				Skier->runAction(SkierDuck);
				if (Skier->runAction(SkierDuck))
				{
					Skier->runAction(SkierUp);
				}
			}		
		}
	}

	bool SkiGame::collisions(cocos2d::Sprite* Sprite1, cocos2d::Sprite* Sprite2)
	{
		cocos2d::Rect Skiers = Sprite1->getBoundingBox();
		cocos2d::Rect Obstacles = Sprite2->getBoundingBox();
		if (Skiers.intersectsRect(Obstacles))
		{
			return true;
		}
		return false;
	}



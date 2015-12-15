#ifndef __SKI_GAME_H__
#define __SKI_GAME_H__


#include "cocos2d.h"
#include "Obstacles.h"
#include "ui/CocosGUI.h"

class SkiGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SkiGame);

	void update(float) override;
	int ShownScore;
	int ShownLives;
	int ShownSpeed;

private:
	cocos2d::Sprite* BG1;
	cocos2d::Sprite* BG2;
	cocos2d::Sprite* Skier;
	cocos2d::ui::Text* Lives;
	cocos2d::ui::Text* Score;
	cocos2d::ui::Text* Speed;
	
	cocos2d::ui::Button* PauseButton;
	bool jumpButtonTouched;
	bool duckButtonTouched;
	bool pauseButtonTouched;

};

#endif 

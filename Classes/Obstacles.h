#pragma once
#include "cocos2d.h"
using  namespace cocos2d;

class Obstacles
{
public:
	Obstacles();
	~Obstacles();
	Sprite* init(int);
	void spawn();
	bool move(float);
	void despawn();
	void setspeed(float);
	bool isspawned();
	Vec2 getPos();

private:
	float speed;
	bool spawned;

public:
	cocos2d::Sprite* image;
};


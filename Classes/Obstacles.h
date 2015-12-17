#pragma once
#include "cocos2d.h"
using  namespace cocos2d;

struct
{
	float x;
	float y;
};
class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	Sprite* init(int);
	void spawn();
	bool move(float);
	void despawn();
	Vec2 position();

private:
	float speed;
	bool spawned;

public:
	cocos2d::Sprite* image;
};


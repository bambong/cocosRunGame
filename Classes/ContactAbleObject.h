#pragma once
//#include "HelloWorldScene.h"
#include "cocos2d.h"
#define ITEM 4
#define OBSTACLE 5
#define PLATFORM_BITMASK 2

USING_NS_CC;

class ContactAbleObject : public cocos2d::Sprite
{
public:
	ContactAbleObject() {}
	float speed;
	virtual void Active();
	void SetSpriteScale(float x);
	void SetSpriteScale(float x, float y);
	Size GetContentSize();
	void MoveUpdate(float t);
	virtual void OnOutOfCamera();
};

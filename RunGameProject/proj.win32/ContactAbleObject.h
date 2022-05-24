#pragma once

#include "cocos2d.h"

USING_NS_CC;

class ContactAbleObject
{
public:
	Sprite* sprite;
	float speed;
	virtual void Active();
	void SetSpriteScale(float x);
	void SetSpriteScale(float x, float y);
	Size GetContentSize();
};

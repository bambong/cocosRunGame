#pragma once
#include "ContactAbleObject.h"

//#include "cocos2d.h"
//
//USING_NS_CC;
class Item : public ContactAbleObject
{
public :
	virtual void OnOutOfCamera();
	void Init(Vec2 pos, float speed);
	virtual void Active();
	static Item* Item::Create(const std::string& filename);
};


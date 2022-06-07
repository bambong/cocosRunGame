#pragma once
#include "ContactAbleObject.h"
#include "cocos2d.h"
USING_NS_CC;
class Platform : public ContactAbleObject
{
public:
	void Init(Vec2 pos, float speed);
	static Platform* Create(const std::string& filename);
	virtual void OnOutOfCamera();
};


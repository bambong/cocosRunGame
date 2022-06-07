#pragma once
#include "ContactAbleObject.h"

class Obstacle : public ContactAbleObject
{
public:
	void Init(Vec2 pos, float speed);
	virtual void Active();
	virtual void OnOutOfCamera();
	static Obstacle* Create(const std::string& filename);
};


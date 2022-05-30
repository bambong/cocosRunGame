#pragma once
#include "Item.h"
#include "Obstacle.h"

#include "cocos2d.h"

USING_NS_CC;


enum E_OBSTACLE_TYPE
{
	OBSTACLE_TYPE_1 = 0,
	OBSTACLE_TYPE_2 = 1,
	OBSTACLE_TYPE_3 = 2
};
class ObjectManager
{
public:
	static ObjectManager* instance;
	static ObjectManager* GetInstance() {
		if (!instance)
		{
			instance = new ObjectManager();

		}
		return instance;
	}
	Vector<ContactAbleObject*> moveUpdateList;
	void MoveUpdate(float t);
	void RemoveItem(ContactAbleObject* item);
	void MakeItem(Vec2 pos, float speed , Scene* scene);
	void MakeObstacle(Vec2 pos, float speed, Scene* scene , E_OBSTACLE_TYPE obstacleType);
	void MakePlatform(Vec2 pos, float speed, float width, float height, Scene* scene);
};


#include "ObjectManager.h"
#include "Platform.h"

ObjectManager* ObjectManager::instance = NULL;

void ObjectManager::MoveUpdate(float t)
{
	//Vector<Item*>::iterator itor;
	auto update = new Vector<ContactAbleObject*>(moveUpdateList);
	for(auto itor = update->begin();itor != update->end();++itor)
	{
		(*itor)->MoveUpdate(t);
	}
}


void ObjectManager::RemoveItem(ContactAbleObject* item)
{
	moveUpdateList.eraseObject(item);
}

void ObjectManager::MakeItem(Vec2 pos, float speed ,Scene* scene)
{
	auto testItem = Item::Create("Progress-Bar.png");
	testItem->Init(pos, speed);
	moveUpdateList.pushBack(testItem);
	scene->addChild(testItem);
}

void ObjectManager::MakeObstacle(Vec2 pos, float speed, Scene* scene, E_OBSTACLE_TYPE obstacleType)
{
	Obstacle* obstacle;
	switch (obstacleType)
	{
	case E_OBSTACLE_TYPE::OBSTACLE_TYPE_1:
		obstacle = Obstacle::Create("Progress-Bar.png");
		obstacle->SetSpriteScale(100,100);
		break;
	case E_OBSTACLE_TYPE::OBSTACLE_TYPE_2:
		obstacle = Obstacle::Create("Progress-Bar.png");
		break;
	case E_OBSTACLE_TYPE::OBSTACLE_TYPE_3:
		obstacle = Obstacle::Create("Progress-Bar.png");
		break;
	default:
		break;
	}
	obstacle->Init(pos, speed);
	moveUpdateList.pushBack(obstacle);
	scene->addChild(obstacle);
}
void ObjectManager::MakePlatform(Vec2 pos, float speed,float width, float height, Scene* scene)
{
	Platform* platform;
	platform = Platform::Create("platform.png");
	platform->SetSpriteScale(width, height);
	platform->Init(pos, speed);
	moveUpdateList.pushBack(platform);
	scene->addChild(platform);
}
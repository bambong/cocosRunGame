#pragma once
#include "Item.h"
#include "Obstacle.h"

#include <string>
#include <sstream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;


enum E_ObjectType
{
	TypeObstacle = 0,
	TypePlatform,
	TypeItem
};
class ObjectData 
{
public :
	ObjectData(E_ObjectType a,int num ,float X,float Y):objectType(a),typeNum(num),x(X),y(Y){}
	E_ObjectType objectType;
	int typeNum;
	float x;
	float y;
};

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
	float clearPosX = 0;
	Vector<ContactAbleObject*> moveUpdateList;
	int MyStoi(string str);
	float MyStof(string str);
	void LoadMapData();
	vector<string> objectSplitData;
	vector<ObjectData*> objectDatas;
	void SpawnMap(Scene* scene , float speed);
	void MoveUpdate(float t, float speed);
	void RemoveItem(ContactAbleObject* item);
	void MakeItem(Vec2 pos, float speed , Scene* scene);
	void MakeObstacle(Vec2 pos, float speed, Scene* scene , int typeNum);
	void MakePlatform(Vec2 pos, float speed, Scene* scene , int typeNum);
	vector<string> split(string str, char Delimiter);
};


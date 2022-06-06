#include "ObjectManager.h"
#include "Platform.h"
#include "HelloWorldScene.h"
#include<algorithm>

ObjectManager* ObjectManager::instance = NULL;

void ObjectManager::LoadMapData()
{
	auto mFiledata = FileUtils::getInstance()->getDataFromFile("MapData.dat");
	//FILE* fp = fopen(filePath.c_str(), "rt");
	char* pBytes = (char*)mFiledata.getBytes();
	// 받아온 값을 int값에 저장
	// string으로 변환하여 출력
	std::string re(pBytes);
	re.erase(remove(re.begin(), re.end(), '\r'),re.end());
	vector<string> objectSplitData = split(re, '\n');
	objectSplitData.pop_back();
	try {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		for (auto iter = objectSplitData.begin(); iter != objectSplitData.end(); ++iter)
		{
			auto objectDataStr = split((*iter), ' ');

			E_ObjectType type;
			auto dataIter = objectDataStr.begin();
			auto typeStr = (*dataIter);
			if (typeStr._Equal("obstacle"))
			{
				type = E_ObjectType::TypeObstacle;
			}
			else if (typeStr._Equal("platform"))
			{
				type = E_ObjectType::TypePlatform;
			}
			else if (typeStr._Equal("item"))
			{
				type = E_ObjectType::TypeItem;
			}
			dataIter++;
			auto num = stoi((*dataIter));
			dataIter++;
			auto posData = split((*dataIter), ',');
			auto posIter = posData.begin();
			auto x = stof(*posIter);
			posIter++;
			auto y = visibleSize.height - stof(*posIter);

			auto temp = new ObjectData(type, num, x, y);
			objectDatas.push_back(temp);
		}
	}catch(exception ex)
	{
		
	}
}

void ObjectManager::SpawnMap(Scene* scene,float speed)
{

	while(!objectDatas.empty())
	{
		auto data = (objectDatas.back());
		if (clearPosX < data->x) 
		{
			clearPosX = data->x;
		}
		switch (data->objectType)
		{

		case E_ObjectType::TypeObstacle:
			MakeObstacle(Vec2(data->x + 3000, data->y), speed, scene, data->typeNum);
			break;

		case E_ObjectType::TypePlatform:
			MakePlatform(Vec2(data->x + 3000, data->y), speed, scene, data->typeNum);
			break;
		case E_ObjectType::TypeItem:
			MakeItem(Vec2(data->x + 3000, data->y), speed, scene);
			break;
		}
		objectDatas.pop_back();
		delete data;
	}
	clearPosX += 3000;

	/*for(auto iter = objectDatas.begin(); iter != objectDatas.end();iter++)
	{
		auto data = (*iter);
		switch (data->objectType)
		{
		
		case E_ObjectType::TypeObstacle:
			MakeObstacle(Vec2(data->x, data->y), speed, scene, data->typeNum);
			break;
		
		case E_ObjectType::TypePlatform:
			MakePlatform(Vec2(data->x, data->y), speed, scene, data->typeNum);
			break;
		case E_ObjectType::TypeItem:
			MakeItem(Vec2(data->x, data->y), speed, scene);
			break;
		}
	}*/
}

void ObjectManager::MoveUpdate(float t ,float speed)
{
	//Vector<Item*>::iterator itor;
	auto update = new Vector<ContactAbleObject*>(moveUpdateList);
	for(auto itor = update->begin();itor != update->end();++itor)
	{
		(*itor)->MoveUpdate(t);
	}
	clearPosX -= speed * t;
	if(clearPosX <= -100)
	{
		HelloWorld::GetInstance()->OnClear();
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

void ObjectManager::MakeObstacle(Vec2 pos, float speed, Scene* scene, int typeNum)
{
	Obstacle* obstacle;
	switch (typeNum)
	{
	case 1:
		obstacle = Obstacle::Create("Bed.png");
		break;
	case 2:
		obstacle = Obstacle::Create("consol.png");
		break;
	case 3:
		obstacle = Obstacle::Create("Phone.png");
		break;
	case 4:
		obstacle = Obstacle::Create("Game-Machine.png");
		break;
	case 5:
		obstacle = Obstacle::Create("Computer.png");
		break;
	case 6:
		obstacle = Obstacle::Create("TV.png");
		break;
	case 7:
		obstacle = Obstacle::Create("TV2.png");
		break;
	case 8:
		obstacle = Obstacle::Create("chicken.png");
		break;
	case 9:
		obstacle = Obstacle::Create("Pizza.png");
		break;
	case 10:
		obstacle = Obstacle::Create("hamburger.png");
		break;
	case 11:
		obstacle = Obstacle::Create("Snacks.png");
		break;
	case 12:
		obstacle = Obstacle::Create("muffin.png");
		break;
	default:
		break;
	}
	obstacle->Init(pos, speed);
	moveUpdateList.pushBack(obstacle);
	scene->addChild(obstacle);
}



void ObjectManager::MakePlatform(Vec2 pos, float speed, Scene* scene, int typeNum)
{
	Platform* platform;


	platform = Platform::Create(StringUtils::format("platform_%d.png",typeNum));
	platform->Init(pos, speed);
	moveUpdateList.pushBack(platform);
	scene->addChild(platform);
}

vector<string> ObjectManager::split(string str, char Delimiter) {
	istringstream iss(str);             // istringstream에 str을 담는다.
	string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼

	vector<string> result;

	// istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
	}

	return result;
}
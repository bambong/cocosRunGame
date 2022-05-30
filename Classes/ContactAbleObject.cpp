#include "ContactAbleObject.h"
#include "ObjectManager.h"

void ContactAbleObject::Active()
{
	log("it is base Active");
}

void ContactAbleObject::SetSpriteScale(float x)
{
	auto size = getContentSize();
	auto sizeRatio = x / size.width;
	setScale(sizeRatio);
}
void ContactAbleObject::SetSpriteScale(float x, float y)
{
	auto size = getContentSize();
	//auto sizeRatio = Size( x / size.width , y/ size.height);
	setScale(x / size.width, y / size.height);
	
}

Size ContactAbleObject::GetContentSize()
{
	auto contentSize = getContentSize();
	return Size(contentSize.width* getScaleX(), contentSize.height * getScaleY());
}

void ContactAbleObject::MoveUpdate(float t)
{
	auto moveValue = t * speed;
	auto movepos = getPosition().x - moveValue;
	setPosition(movepos, getPosition().y);

	if (movepos< -GetContentSize().width-10)
	{
		OnOutOfCamera();
	}
}

void ContactAbleObject::OnOutOfCamera()
{
	ObjectManager::GetInstance()->RemoveItem(this);
}

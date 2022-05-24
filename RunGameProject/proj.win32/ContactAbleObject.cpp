#include "ContactAbleObject.h"


void ContactAbleObject::Active()
{
	log("it is base Active");
}

void ContactAbleObject::SetSpriteScale(float x)
{
	auto size = sprite->getContentSize();
	auto sizeRatio = x / size.width;
	sprite->setScale(sizeRatio);
}
void ContactAbleObject::SetSpriteScale(float x, float y)
{
	auto size = sprite->getContentSize();
	auto sizeRatio = Size( x / size.width , y/ size.height);
	sprite->setScale(sizeRatio.width,size.height);
}

Size ContactAbleObject::GetContentSize()
{
	auto contentSize = sprite->getContentSize();
	return Size(contentSize.width* sprite->getScaleX(), contentSize.height * sprite->getScaleY());
}

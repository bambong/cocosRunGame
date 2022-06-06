#include "Item.h"
#include "Item.h"
#include "ObjectManager.h"

void Item::OnOutOfCamera()
{
	ObjectManager::GetInstance()->RemoveItem(this);
}
void Item::Init(Vec2 pos ,float speed)
{
	setAnchorPoint(Vec2::ZERO);
	this->speed = speed;
	//this->scene = scene;
	//this->create("Progress-Bar.png");
	setPosition(pos);
	SetSpriteScale(180);
	auto body = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(1, 0, 0));
	body->setDynamic(false);
	body->setCollisionBitmask(ITEM);
	body->setContactTestBitmask(true);
	setPhysicsBody(body);
	//this->scene->addChild(sprite);
}

void Item::Active()
{
	removeFromParentAndCleanup(true);
}

Item* Item::Create(const std::string& filename)
{
	Item* sprite = new (std::nothrow) Item();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
			return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

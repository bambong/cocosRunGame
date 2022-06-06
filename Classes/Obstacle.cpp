#include "Obstacle.h"
#include "ObjectManager.h"

void Obstacle::Init(Vec2 pos, float speed)
{
	setAnchorPoint(Vec2::ZERO);
	this->speed = speed;
	setPosition(pos);
	auto body = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(1, 0, 0));
	body->setDynamic(false);
	body->setCollisionBitmask(OBSTACLE);
	body->setContactTestBitmask(true);
	setPhysicsBody(body);
}

void Obstacle::Active()
{
	removeFromParentAndCleanup(true);
}

void Obstacle::OnOutOfCamera()
{
	ObjectManager::GetInstance()->RemoveItem(this);
}

Obstacle* Obstacle::Create(const std::string& filename)
{
	Obstacle* sprite = new (std::nothrow) Obstacle();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

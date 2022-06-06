#include "Platform.h"
#include "ObjectManager.h"

void Platform::Init(Vec2 pos, float speed)
{
	setAnchorPoint(Vec2::ZERO);
	this->speed = speed;
	setPosition(pos);
	auto body = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(1, 0, 0));
	body->setDynamic(false);
	body->setCollisionBitmask(PLATFORM_BITMASK);
	body->setContactTestBitmask(true);
	setPhysicsBody(body);
}

Platform* Platform::Create(const std::string& filename)
{
	Platform* sprite = new (std::nothrow) Platform();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Platform::OnOutOfCamera()
{
	ObjectManager::GetInstance()->RemoveItem(this);
}



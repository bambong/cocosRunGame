#include "Player.h"

Player::Player()
{
}

void Player::Init(Scene* scene)
{
	playerRunAnim = Animation::create();
	
	auto cache = SpriteFrameCache::getInstance(); 
	cache->addSpriteFramesWithFile("player-sheet.plist");
	instance = Sprite::createWithSpriteFrameName("grossini.png"); 
	phyBody = PhysicsBody::createBox(instance->getContentSize(),PhysicsMaterial(1,0,1));
	//phy->setDynamic(false);
	phyBody->setCollisionBitmask(PLAYER_BITMASK);
	phyBody->setContactTestBitmask(true);
	phyBody->setRotationEnable(false);
	
	
	//phy->setPositionOffset()
	instance->setPhysicsBody(phyBody);
	phyBody->setMass(1);
	playerRunAnim->setDelayPerUnit(0.2f);

	playerRunAnim->addSpriteFrame(cache->spriteFrameByName("grossini.png"));
	for (int i = 1; i < 15; i++)
	{
		auto frame = cache->spriteFrameByName(StringUtils::format("grossini_dance_%02d.png", i));
		playerRunAnim->addSpriteFrame(frame);
	}
	scene->addChild(instance);
}

void Player::PlayerRun(CallFunc* call)
{

	auto animate = Animate::create(playerRunAnim);
	auto rep = RepeatForever::create(animate);
	auto moveAction = MoveTo::create(4,Vec2(400, 200));
	//auto spawn = Spawn::createWithTwoActions(moveAction, animate);
	auto seq = Sequence::create(moveAction, call, NULL);
	
	instance->runAction(seq);
	instance->runAction(rep);
}

#include "Player.h"

Player::Player()
{
}

void Player::Init(Scene* scene)
{
	
	playerRunAnim = Animation::create();
	playerHitAnim = Animation::create();
	playerJumpAnim = Animation::create();

	auto cache = SpriteFrameCache::getInstance(); 
	cache->addSpriteFramesWithFile("player-run.plist");
	cache->addSpriteFramesWithFile("player-hit.plist");
	
	instance = Sprite::createWithSpriteFrameName("run_3.png"); 
	instance->setZOrder(3);
	//instance->setAnchorPoint(Vec2::ZERO);

	phyBody = PhysicsBody::createBox(instance->getContentSize(),PhysicsMaterial(1,0,1));
	phyBody->setCollisionBitmask(PLAYER_BITMASK);
	phyBody->setContactTestBitmask(true);
	phyBody->setRotationEnable(false);

	instance->setPhysicsBody(phyBody);
	phyBody->setMass(1);
	playerRunAnim->setDelayPerUnit(0.2f);
	playerHitAnim->setDelayPerUnit(0.2f);
	playerJumpAnim->setDelayPerUnit(0.2f);
	//playerRunAnim->addSpriteFrame(cache->spriteFrameByName("grossini.png"));
	for (int i = 1; i <= 5; i++)
	{
		auto runFrame = cache->spriteFrameByName(StringUtils::format("run_%d.png", i));
		auto hitFrame = cache->spriteFrameByName(StringUtils::format("damage_%d.png", i));
		playerRunAnim->addSpriteFrame(runFrame);
		playerHitAnim->addSpriteFrame(hitFrame);
	}
	playerJumpAnim->addSpriteFrameWithFile("Jump.png");
	scene->addChild(instance);
}



void Player::PlayerRun(CallFunc* call)
{
	
	PlayerRunAnimPlay();
	//PlayerJumpAnimPlay();
	//PlayerHitAnimPlay();
	auto moveAction = MoveBy::create(6,Vec2(372 + instance->getContentSize().width/2,0));
	auto seq = Sequence::create(moveAction, call, NULL);
	instance->runAction(seq);

}

void Player::PlayerRunAnimPlay()
{
	instance->stopActionByTag(2);
	auto cache = SpriteFrameCache::getInstance();
	playerRunAnim = Animation::create();
	playerRunAnim->setDelayPerUnit(0.2f);
	for (int i = 1; i <= 5; i++)
	{
		auto runFrame = cache->spriteFrameByName(StringUtils::format("run_%d.png", i));
		playerRunAnim->addSpriteFrame(runFrame);
	}

	auto animate = Animate::create(playerRunAnim);

	playerRunAction = RepeatForever::create(animate);
	playerRunAction->setTag(2);
	instance->runAction(playerRunAction);
}

void Player::PlayerHitAnimPlay()
{
	//playerRunAction->stop();
	auto cache = SpriteFrameCache::getInstance();
	playerHitAnim = Animation::create();
	playerHitAnim->setDelayPerUnit(0.2f);
	for (int i = 1; i <= 5; i++)
	{
		auto runFrame = cache->spriteFrameByName(StringUtils::format("damage_%d.png", i));
		playerHitAnim->addSpriteFrame(runFrame);
	}
	instance->stopActionByTag(2);
	auto animate = Animate::create(playerHitAnim);
	playerRunAction = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(Player::PlayerRunAnimPlay,this)),NULL);
	playerRunAction->setTag(2);
	instance->runAction(playerRunAction);
}

void Player::PlayerJumpAnimPlay()
{
	//playerRunAction->stop();
	instance->stopActionByTag(2);
	playerJumpAnim = Animation::create();
	playerJumpAnim->addSpriteFrameWithFile("Jump.png");
	playerJumpAnim->setDelayPerUnit(0.2f);
	playerRunAction = Animate::create(playerJumpAnim);
	playerRunAction->setTag(2);
	instance->runAction(playerRunAction);
}

void Player::TouchedGround()
{
	isJumping = false;
	PlayerRunAnimPlay();
}

void Player::Jump()
{
	if (isJumping)
	{
		return;
	}
	isJumping = true;
	PlayerJumpAnimPlay();

	instance->getPhysicsBody()->applyImpulse(Vec2(0, JumpPow));
}

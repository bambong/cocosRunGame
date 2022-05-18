#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define PLAYER_BITMASK 1
#define PLATFORM_BITMASK 2
#define GROUND 3

class Player
{
	public: 	
		Sprite* instance;
		Animate playerAnimate;
		Animation* playerRunAnim;
		PhysicsBody* phyBody;
		Player();
		void Init(Scene* scene);
		void PlayerRun(CallFunc* call);
		void PlayerDead();
		bool CheckPlayerTouched();

};


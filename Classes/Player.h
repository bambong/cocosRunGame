#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define PLAYER_BITMASK 1

#define GROUND 3


class Player
{
private :
	float const JumpPow = 200;
public : 	
		Sprite* instance;
		Animate playerAnimate;
		Action* playerRunAction;
		Animation* playerRunAnim;
		Animation* playerHitAnim;
		Animation* playerJumpAnim;
		PhysicsBody* phyBody;
		Player();
		void Init(Scene* scene);
		void PlayerRun(CallFunc* call);
		void PlayerRunAnimPlay();
		void PlayerHitAnimPlay();
		void PlayerJumpAnimPlay();
		bool isJumping;
		void PlayerDead();
		bool CheckPlayerTouched();
		void TouchedGround();
		void Jump();

};


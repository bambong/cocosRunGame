#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BackGroundController
{
	public :
		Sprite* backGround1;
		Sprite* backGround2;
		float speed;
		float widthSize;
		void Init(char* bg1,char* bg2 ,float widthSize ,float speed,Scene* scene);
		void MoveUpdate(float t);
		void SetSpriteScaleByFixelWidth(float x);


};


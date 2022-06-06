#include "BackGroundController.h"

void BackGroundController::Init(char* bg1, char* bg2, float speed, Scene* scene)
{

	/*auto node = ParallaxNode::create(); 
	scene->addChild(node);
	auto action_0 = MoveBy::create(20.0, Point(-2000, 0)); 
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL); 
	auto action_3 = RepeatForever::create(action_2); 
	node->runAction(action_3);*/


	backGround1 = Sprite::create(bg1);
	backGround2 = Sprite::create(bg2);

	backGround1->getTexture()->setAliasTexParameters();
	backGround2->getTexture()->setAliasTexParameters();

	widthSize = backGround1->getContentSize().width;
	//SetSpriteScaleByFixelWidth(widthSize);
	backGround1->setAnchorPoint(Vec2::ZERO);
	backGround2->setAnchorPoint(Vec2::ZERO);	
	backGround2->setPosition(widthSize-0.5f, 0);
	this->speed = speed;
	scene->addChild(backGround1);
	scene->addChild(backGround2); 
}

void BackGroundController::SetSpriteScaleByFixelWidth(float x)
{
	auto size = backGround1->getContentSize();
	auto sizeRatio = x / size.width;
	backGround1->setScale(sizeRatio);
	backGround2->setScale(sizeRatio);
	widthSize = x;
}
void BackGroundController::MoveUpdate(float t)
{
	auto moveValue = t * speed;
	auto movepos1 = backGround1->getPosition().x - moveValue;
	auto movepos2 = backGround2->getPosition().x - moveValue;
	backGround1->setPosition(movepos1, 0);
	backGround2->setPosition(movepos2, 0);
	
	if (movepos1 < -widthSize)
	{
		backGround1->setPosition(backGround2->getPosition().x+widthSize - 0.5f,0);
	}
	else if(movepos2 < -widthSize)
	{
		backGround2->setPosition(backGround1->getPosition().x+widthSize - 0.5f,0);
	}
}
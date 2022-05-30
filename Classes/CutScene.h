
#ifndef __CUTSCENE_SCENE_H__
#define __CUTSCENE_SCENE_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif
USING_NS_CC;

class CutScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool isTouched;
	Layer* touchlayer;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	void SetSpriteScaleByFixel(Sprite* sprite, float x, float y);
	void SetSpriteScaleByFixelWidth(Sprite* sprite, float x);

	CREATE_FUNC(CutScene);
};

#endif
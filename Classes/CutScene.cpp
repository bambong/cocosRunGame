#include "CutScene.h"
#include "MainMenuScene.h"

cocos2d::Scene* CutScene::createScene()
{
	return CutScene::create();
}

bool CutScene::init()
{
	auto visbleSize = Director::getInstance()->getVisibleSize();
	auto cutScene = Sprite::create("country-platform-back.png");
	SetSpriteScaleByFixel(cutScene, visbleSize.width, visbleSize.height);
	cutScene->setAnchorPoint(Vec2(0, 0));
	this->addChild(cutScene);


	touchlayer = Layer::create();

	auto touchevent = EventListenerTouchOneByOne::create();
	touchevent->onTouchBegan = CC_CALLBACK_2(CutScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchevent, touchlayer);
	this->addChild(touchlayer);
	return true;
}
bool CutScene::onTouchBegan(Touch* touch, Event* event)
{
	if (isTouched)
	{
		return true;
	}
	isTouched = true;
	auto scene = TransitionFade::create(2.0f, MainMenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
	return true;
}
void CutScene::SetSpriteScaleByFixel(Sprite* sprite, float x, float y)
{
	auto size = sprite->getContentSize();
	sprite->setScale(x / size.width, y / size.height);
}

void CutScene::SetSpriteScaleByFixelWidth(Sprite* sprite, float x)
{
	auto size = sprite->getContentSize();
	sprite->setScale(x / size.width);
}
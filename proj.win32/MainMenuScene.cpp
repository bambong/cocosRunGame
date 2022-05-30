#include "MainMenuScene.h"
#include "HelloWorldScene.h"
cocos2d::Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	auto background_back = Sprite::create("country-platform-back.png");
	auto background_front = Sprite::create("country-platform-tiles-example.png");
	SetSpriteScaleByFixelWidth(background_back, 1600);
	SetSpriteScaleByFixelWidth(background_front, 1600);
	background_back->setAnchorPoint(Vec2(0, 0));
	background_front->setAnchorPoint(Vec2(0, 0));
	this->addChild(background_back);
	this->addChild(background_front);

	auto playerReady = Sprite::create("player-ready.png");
	SetSpriteScaleByFixel(playerReady,505,760);
	playerReady->setAnchorPoint(Vec2(0, 0));
	playerReady->setPosition(Vec2(100, -60));
	this->addChild(playerReady);

	auto title = Label::createWithSystemFont("", "학점을향하여", 100);
	title->setPosition(Vec2(1000, 300));
	this->addChild(title);
	touchlayer = Layer::create();
	
	auto touchevent = EventListenerTouchOneByOne::create();
	touchevent->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchevent, touchlayer);
	this->addChild(touchlayer);
	return true;
}
bool MainMenuScene::onTouchBegan(Touch* touch, Event* event)
{
	if(isTouched)
	{
		return true;
	}
	isTouched = true;
	auto scene	= TransitionFade::create(2.0f, HelloWorld::createScene());
	Director::getInstance()->replaceScene(scene);
	return true;
}
void MainMenuScene::SetSpriteScaleByFixel(Sprite* sprite, float x, float y)
{
	auto size = sprite->getContentSize();
	sprite->setScale(x / size.width, y / size.height);
}

void MainMenuScene::SetSpriteScaleByFixelWidth(Sprite* sprite, float x)
{
	auto size = sprite->getContentSize();
	sprite->setScale(x / size.width);
}
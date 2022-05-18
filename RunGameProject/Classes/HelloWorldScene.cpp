#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
//#include "Platform.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setSpeed(8);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -35));
   
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

 
    curHp = initHp;
    auto hpBarBack = Sprite::create("Progress_Bar_Outside.png");
    hpBarBack->setLocalZOrder(0);
    hpBarBack->setAnchorPoint(Vec2(0,1));
    
    auto hpbarinner = Sprite::create("Progress_Bar_inside.png");
    //hpbarinner->setAnchorPoint(Vec2(0, 1));
   
    hpBar = ProgressTimer::create(hpbarinner);
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setLocalZOrder(1);
    hpBar->setMidpoint(Vec2(0,0.5));
    hpBar->setBarChangeRate(Vec2(1, 0));
    //auto a =  ProgressTo::create(1, 100);
    hpBar->setAnchorPoint(Vec2(0, 1));
    //hpBar->runAction(a);

   
    auto hpBarMenu = Layer::create();
    hpBarMenu->addChild(hpBar);
    hpBarMenu->addChild(hpBarBack);
    hpBarMenu->setPosition(Vec2(-10, visibleSize.height));
    this->addChild(hpBarMenu);
    hpBarMenu->setZOrder(10);


    ////////////jump Button//////////////////


    auto jumpButton = MenuItemImage::create(
        "Jump-button.png",
        "Jump-button.png",
        CC_CALLBACK_1(HelloWorld::JumpCallback, this));
    jumpButton->setAnchorPoint(Vec2(1, 0));
    jumpButton->setPosition(Vec2(visibleSize.width - 50, 10));

    auto menu = Menu::create(jumpButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    menu->setVisible(false);
    isJumping = true;


  //////////////////BackGround//////////////
    
    background1 = new BackGroundController();
    background2 = new BackGroundController();
 
    background2->Init("country-platform-back.png", "country-platform-back.png", 1600, 50, this);
    background1->Init("country-platform-tiles-example.png", "country-platform-tiles-example.png", 1600, 500, this);
    this->scheduleUpdate();

    
    /////////////platformtest/////////


    platform = Sprite::create("platform.png");
    SetSpriteScaleByFixel(platform, 300, 100);
    platform->setPosition(300,  500);
    auto platformBody = PhysicsBody::createBox(platform->getContentSize(), PhysicsMaterial(1, 0, 0));
    platformBody->setDynamic(false);
    platformBody->setCollisionBitmask(PLATFORM_BITMASK);
    platformBody->setContactTestBitmask(true);
    platform->setPhysicsBody(platformBody);
    this->addChild(platform);


    ////////////////////////////////////

    player = new Player();
    player->Init(this);
    player->instance->setPosition(-200,200);
    player->PlayerRun(CallFunc::create([=]() { 
        menu->setVisible(true);
        isJumping = false; }));

   
   
    
    ////////////GROUND////////////////

    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width+700,100), PHYSICSBODY_MATERIAL_DEFAULT);
    auto node = Node::create();
    node->setPosition(Vec2(visibleSize.width/2,50));
    body->setCollisionBitmask(GROUND);
    body->setContactTestBitmask(true);
    node->setPhysicsBody(body);
    this->addChild(node);
    
    /////////////////////////////////
 

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::OnContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,player->instance);
    return true;
}


void HelloWorld::OnGameOver()
{


}

void HelloWorld::HpBarUpdate()
{
    auto ratio = 100 * (curHp / initHp);
    hpBar->setPercentage(ratio);
}

void HelloWorld::UpdateHp(float f)
{                                 
    curHp -= f * DecreaseHpAmount;

    if (curHp <= 0)
    {
        OnGameOver();
        hpBar->setPercentage(0);
        return; 
    }
    HpBarUpdate();
    //hpBar->runAction(ProgressTo::create(f,ratio));
}

void HelloWorld::AddHp(float amount)
{
    curHp += amount;
    if (curHp > initHp) 
    {
        curHp = initHp;
    }
    HpBarUpdate();

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::JumpCallback(cocos2d::Ref* pSender)
{
    if(isJumping)
    {
        return;
    }
    isJumping = true;
    AddHp(10);
    player->instance->getPhysicsBody()->applyImpulse(Vec2(0,200));
}

void HelloWorld::SetSpriteScaleByFixel(Sprite* sprite, float x, float y)
{
    auto size = sprite->getContentSize();
    sprite->setScale(x / size.width, y / size.height);
}

void HelloWorld::SetSpriteScaleByFixelWidth(Sprite* sprite, float x)
{
    auto size = sprite->getContentSize();
    sprite->setScale(x / size.width);
}

void HelloWorld::update(float delta)
{
    UpdateHp(delta);
    auto curPos = platform->getPosition();
    curPos.x -= 200 * delta;
    platform->setPosition(curPos);
    if(curPos.x < -200)
    {
        platform->setPosition(Vec2(1000, curPos.y));
    }
    
    background1->MoveUpdate(delta);
    background2->MoveUpdate(delta);
}

bool HelloWorld::OnContactBegin(cocos2d::PhysicsContact& contacter)
{
    auto player = contacter.getCurrentTarget();
    PhysicsBody* a = contacter.getShapeA()->getBody();
    PhysicsBody* b = contacter.getShapeB()->getBody();
    PhysicsBody* notPlayerContecter;
    
    notPlayerContecter = b->getCollisionBitmask() == PLAYER_BITMASK ? a : b;
    auto notPlayerContecterBitmask = notPlayerContecter->getCollisionBitmask();

    if(notPlayerContecterBitmask == GROUND)
    {
        isJumping = false;
        return true;
    }

    if(notPlayerContecterBitmask == PLATFORM_BITMASK)
    {
        
        log("normal x: %f y: %f", contacter.getContactData()->normal.x, contacter.getContactData()->normal.y);

        auto e = player->getPosition().x + player->getContentSize().width / 2 * player->getScaleX();
        auto g = notPlayerContecter->getPosition().x - 150;
        auto platformSizeDump = notPlayerContecter->getNode()->getContentSize().height / 2 * notPlayerContecter->getNode()->getScaleY();
        auto isBottom = notPlayerContecter->getPosition().y + platformSizeDump <= player->getPosition().y - player->getContentSize().height / 2 * player->getScaleY();
        if (isBottom)
        {
            isJumping = false;
        }
          
         return isBottom;
    }
    
    return true;
}



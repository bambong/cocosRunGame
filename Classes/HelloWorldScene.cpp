#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "ObjectManager.h"
#include "CutScene.h"
//#include "Platform.h"

USING_NS_CC;

HelloWorld* HelloWorld::instance = NULL;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
   //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setSpeed(8);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -35));
   
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    instance = layer;
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
    auto hpBarBack = Sprite::create("Progress-Bar_Outside.png");
    hpBarBack->setLocalZOrder(0);
    hpBarBack->setAnchorPoint(Vec2(0,0.5));
    
    auto hpbarinner = Sprite::create("Progress-Bar_inside.png");
   
    //hpbarinner->setAnchojrPoint(Vec2(0, 1));
   
    auto star = Sprite::create("Progress-Bar.png");
    star->setAnchorPoint(Vec2(0, 1));

    hpBar = ProgressTimer::create(hpbarinner);
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setLocalZOrder(1);
    hpBar->setMidpoint(Vec2(0,0.5));
    hpBar->setBarChangeRate(Vec2(1, 0));
    //auto a =  ProgressTo::create(1, 100);
    hpBar->setAnchorPoint(Vec2(0, 0.5));
    //hpBar->runAction(a);
    auto sizeDiff = (hpBarBack->getContentSize() - hpbarinner->getContentSize())/2;
    auto hpBarPos = Vec2(star->getContentSize().width + 10,star->getContentSize().height/2 * -1);
    hpBar->setPosition(sizeDiff.width + hpBarPos.x, hpBarPos.y);
    hpBarBack->setPosition(hpBarPos.x, hpBarPos.y);
    auto hpBarMenu = Layer::create();
    hpBarMenu->addChild(star);
    hpBarMenu->addChild(hpBar);
    hpBarMenu->addChild(hpBarBack);
    hpBarMenu->setPosition(Vec2(10, visibleSize.height));
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
    menu->setZOrder(10);
    isJumping = true;


  //////////////////BackGround//////////////
   
    testBack_back = Sprite::create("background.png");
    testBack_back->setAnchorPoint(Vec2(0, 0));
    this->addChild(testBack_back);

    background1 = new BackGroundController();
    background2 = new BackGroundController();
    
   

    background2->Init("background_cloud.png", "background_cloud.png", ForgroundMoveSpeed-60, this);
    background1->Init("platform0.png", "platform0.png", ForgroundMoveSpeed, this);
    this->scheduleUpdate();
  

    
    /////////////platformtest/////////

     ////////////GROUND////////////////

    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width + 700, 59), PHYSICSBODY_MATERIAL_DEFAULT);
    auto node = Node::create();
    node->setPosition(Vec2(visibleSize.width / 2, 29.5f));
    body->setCollisionBitmask(GROUND);
    body->setContactTestBitmask(true);
    node->setPhysicsBody(body);
    this->addChild(node);

    /////////////////////////////////

    ////////////////////////////////////

    player = new Player();
    player->Init(this);
    player->instance->setPosition(-400,300);
    player->PlayerRun(CallFunc::create([=]() { 
        menu->setVisible(true);
        isJumping = false; }));

    SetSpriteScaleByFixel(player->instance, 176, 285);
    //SetSpriteScaleByFixelWidth(player->instance, 285);
    player->instance->setScaleX(-player->instance->getScaleX());
   
    
   
    
    
    
    
    
    
    
    //////////item///////////////////

    objectManager = ObjectManager::GetInstance();
    
    objectManager->instance->SpawnMap(this, ForgroundMoveSpeed);
   
   // auto testItem = Item::Create("Progress-Bar.png");
   // testItem->Init(Vec2(visibleSize.width, 200), ForgroundMoveSpeed);
   //// testItem->GetSprite()->setPosition(visibleSize.width,100);
   // this->addChild(testItem);


    /// ////////////////////////////

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::OnContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,player->instance);
    return true;
}


void HelloWorld::OnClear()
{
    if (isClear)
    {
        return;
    }
    isClear = true;

    auto moveBy = MoveBy::create(3,Vec2(Director::getInstance()->getVisibleSize().width, 0));
    auto call = CallFunc::create(CC_CALLBACK_0(HelloWorld::OnGameOver, this));
    auto seq = Sequence::create(moveBy, call, NULL);
    player->instance->runAction(seq);
}

void HelloWorld::OnGameOver()
{
    auto scene = TransitionFade::create(2.0f, CutScene::createScene());
    Director::getInstance()->replaceScene(scene);
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
        isDead = true;
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

void HelloWorld::HitDamage(float amount)
{
    curHp -= amount;
    if (curHp <= 0 )
    {
        OnGameOver();
        hpBar->setPercentage(0);
        return;
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
    if (isDead)
    {
        return;
    }
    player->Jump();
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
    if (isDead)
    {
        return;
    }
    
    objectManager->MoveUpdate(delta,ForgroundMoveSpeed);
    
    if (isClear)
    {
        return;
    }

    UpdateHp(delta);
    
    auto forSpeed = delta * ForgroundMoveSpeed;
    auto cloudSpeed = delta * (ForgroundMoveSpeed-20);
   // auto backSpeed = delta * (ForgroundMoveSpeed-30);
   // testBack_back->setPositionX(testBack_back->getPosition().x - forSpeed);
    //testBack_cloud->setPositionX(testBack_cloud->getPosition().x - cloudSpeed);
    //testBack_ground->setPositionX(testBack_ground->getPosition().x - forSpeed);
    background1->MoveUpdate(delta);
    background2->MoveUpdate(delta);
}

bool HelloWorld::OnContactBegin(cocos2d::PhysicsContact& contacter)
{

    PhysicsBody* a = contacter.getShapeA()->getBody();
    PhysicsBody* b = contacter.getShapeB()->getBody();
    PhysicsBody* notPlayerContecter;
    
    if (b->getCollisionBitmask() != PLAYER_BITMASK && a->getCollisionBitmask() != PLAYER_BITMASK)
    {
        return false;
    }

    notPlayerContecter = b->getCollisionBitmask() == PLAYER_BITMASK ? a : b;
  
    auto notPlayerContecterBitmask = notPlayerContecter->getCollisionBitmask();

    if(notPlayerContecterBitmask == GROUND)
    {
        player->TouchedGround();
        return true;
    }
    if(notPlayerContecterBitmask == PLATFORM_BITMASK)
    {
        
        log("normal x: %f y: %f", contacter.getContactData()->normal.x, contacter.getContactData()->normal.y);

        auto e = player->instance->getPosition().x + player->instance->getContentSize().width / 2 * player->instance->getScaleX();
        auto g = notPlayerContecter->getPosition().x - 150;
        auto platformSizeDump = notPlayerContecter->getNode()->getContentSize().height / 2 * notPlayerContecter->getNode()->getScaleY();
        auto isBottom = notPlayerContecter->getPosition().y + platformSizeDump <= player->instance->getPosition().y - player->instance->getContentSize().height / 2 * player->instance->getScaleY();
        if (isBottom)
        {
            player->TouchedGround();
        }
          
         return isBottom;
    }
    if(notPlayerContecterBitmask == ITEM )
    {
      
        //this->removeChild(notPlayerContecter->getNode());
        //notPlayerContecter->getNode();
        auto node = (Item*)notPlayerContecter->getNode();
        AddHp(100);
        objectManager->RemoveItem(node);
        node->Active();
        //notPlayerContecter->getNode()->removeFromParentAndCleanup(true);       
        return false;
    }

    if (notPlayerContecterBitmask == OBSTACLE)
    {
        auto node = (Obstacle*)notPlayerContecter->getNode();
        HitDamage(50);
        objectManager->RemoveItem(node);
        player->PlayerHitAnimPlay();
        node->Active();
        //notPlayerContecter->getNode()->removeFromParentAndCleanup(true);       
        return false;
    }

    return true;
}



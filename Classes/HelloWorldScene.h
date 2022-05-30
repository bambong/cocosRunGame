#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "BackGroundController.h"
#include "Player.h"
#include "ContactAbleObject.h"
#include "ObjectManager.h"


USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    const float DecreaseHpAmount = 1;
    const float initHp = 100;
    const float ForgroundMoveSpeed = 200;
    
    bool isJumping;
    bool isDead;
    float curHp;
   
    ObjectManager* objectManager;
    
    Player* player;
    
    ProgressTimer* hpBar;
    
    BackGroundController* background1;
    BackGroundController* background2;
    
    Sequence* jumpActionSeq;
    Sprite* platform;
  
    void OnGameOver();
    void HpBarUpdate();
    void UpdateHp(float f);
    void AddHp(float amount);
    void HitDamage(float amount);
   
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void JumpCallback(cocos2d::Ref* pSender);

    void SetSpriteScaleByFixel(Sprite* sprite, float x, float y);
    void SetSpriteScaleByFixelWidth(Sprite* sprite, float x);
    void update(float delta);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::PhysicsWorld* sceneworld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneworld = world; };
    bool OnContactBegin(cocos2d::PhysicsContact &contacter);
};

#endif // __HELLOWORLD_SCENE_H__

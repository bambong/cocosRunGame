#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "BackGroundController.h"
#include "Player.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    const float DecreaseHpAmount = 1;
    const float initHp = 100;
    virtual bool init();
    ProgressTimer* hpBar;
    Player* player;
    Sequence* jumpActionSeq;
    Sprite* platform;
    bool isJumping;
    BackGroundController* background1;
    BackGroundController* background2;
    float curHp;
    void OnGameOver();
    void HpBarUpdate();
    void UpdateHp(float f);
    void AddHp(float amount);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void JumpCallback(cocos2d::Ref* pSender);

    void SetSpriteScaleByFixel(Sprite* sprite, float x, float y);
    void SetSpriteScaleByFixelWidth(Sprite* sprite, float x);
    void update(float delta);




    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::PhysicsWorld* sceneworld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneworld = world; };
    bool OnContactBegin(cocos2d::PhysicsContact &contacter);
};

#endif // __HELLOWORLD_SCENE_H__

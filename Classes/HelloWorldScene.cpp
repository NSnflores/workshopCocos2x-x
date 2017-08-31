#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Escena2.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    Sprite* sprite = Sprite::create("HelloWorld.png");
    this->addChild(sprite);
    
    sprite->setPosition(screenSize/2);
    
    MoveBy* mover = MoveBy::create(3, Vec2(300,0));
    JumpBy* saltar = JumpBy::create(3, Vec2(-300,0), 100, 3);
    
    
    FadeOut* fadeOut = FadeOut::create(3);
    FadeIn* fadeIn = FadeIn::create(3);
    
    Spawn* spawn = Spawn::create(saltar,fadeOut, NULL);
    Spawn* spawn2 = Spawn::create(mover,fadeIn, NULL);
    
    Sequence* secuencia = Sequence::create(spawn, spawn2, NULL);
    
    sprite->runAction(secuencia);
    
    getPhysicsWorld()->setGravity(Vec2(0,-98.1));
    
    Node* centerNode =  Node::create();
    centerNode->setPosition(screenSize/2);
    PhysicsBody* boundingBox = PhysicsBody::createEdgeBox(screenSize);
    centerNode->addComponent(boundingBox);
    
    this->addChild(centerNode);
    
    for(int i = 0; i < 300; i++)
    {
        Node* node = Node::create();
        float xPos = random(0.f, screenSize.width);
        float yPos = random(0.f, screenSize.height);
        this->addChild(node);
        node->setPosition(Vec2(xPos, yPos));
        
        PhysicsBody* bolitafisica = PhysicsBody::createCircle(3);
        node->addComponent(bolitafisica);
    }
    
    Node* node = Node::create();
    float xPos = random(0.f, screenSize.width);
    float yPos = random(0.f, screenSize.height);
    this->addChild(node);
    node->setPosition(Vec2(xPos, yPos));
    
    PhysicsBody* bolitafisica = PhysicsBody::createCircle(15);
    node->addComponent(bolitafisica);
    
    bolitafisica->setGravityEnable(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [](Touch* touch, Event* event)
    {
        Scene* escena = Escena2::createScene();
        TransitionFade* trans = TransitionFade::create(1, escena);
        Director::getInstance()->pushScene(trans);
        
        return true;
    };
    listener->onTouchEnded = [](Touch* touch, Event* event)
    {
        return true;
    };
    listener->onTouchMoved = [=](Touch* touch, Event* event)
    {
        bolitafisica->setVelocity((touch->getLocation() - node->getPosition()) * 10);
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
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

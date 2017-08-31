
#include "Escena2.h"

Scene* Escena2::createScene()
{
    return Escena2::create();
}

bool Escena2::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    auto sprite = Sprite::create("circle.png");
    addChild(sprite);
    
    
    return true;
}

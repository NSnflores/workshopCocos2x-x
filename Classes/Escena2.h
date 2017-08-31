#ifndef Escena2_hpp
#define Escena2_hpp

#include "cocos2d.h"

using namespace cocos2d;
class Escena2 : Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(Escena2);
};


#endif /* Escena2_hpp */

//
//  MSprite.hpp
//  GameVina
//
//  Created by Black3rry on 3/23/16.
//
//

#ifndef MSprite_hpp
#define MSprite_hpp

#include "cocos2d.h"

class MSprite : public cocos2d::Sprite {
    
public:
    
    static MSprite* create(std::string text,cocos2d::Size size);
    static MSprite* createX(std::string text);
    static MSprite* create(std::string text);
    static MSprite* createwithFrameName(std::string textureName);
    
    static MSprite* createExtends(std::string fileName,std::string text,cocos2d::Size size);
    static MSprite* createExtendsUp(std::string fileName,cocos2d::Size size);
    static MSprite* createExtendsDown(std::string fileName,float width);
    float  getTopPosition();
    float  getRightPosition();

    static MSprite* createWithUrl();
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MSprite);
    
public:
    
    float getWidth();
    float getHeight();
    cocos2d::Size getSize();
    void setSize(cocos2d::Size size);
    
};

#endif /* MSprite_hpp */

//
//  MiniGamePopUp.hpp
//  KingGameTest
//
//  Created by hungle on 8/15/16.
//
//

#ifndef MiniGamePopUp_hpp
#define MiniGamePopUp_hpp

#include "cocos2d.h"

class MiniGamePopUp : public cocos2d::Node {
public:
    
    MiniGamePopUp();
    ~MiniGamePopUp();
    static MiniGamePopUp* create(int index);
    static MiniGamePopUp* getInstance();
    static MiniGamePopUp* _instance;
    
    virtual bool init() override;
    void onEnter() override;
    void update(float dt) override;
    void addEvent();
    
    void update();
    
    CREATE_FUNC(MiniGamePopUp);
    
    void showObjectThrow();
    void hiddenInfoExtend();
    void show();
    
    cocos2d::Point touchOffset;
    CC_SYNTHESIZE(cocos2d::Vec2,_originPos,OriginPos);
    
private:
    
    float getWidth();
    float getHeight();
    cocos2d::Size getSize();
};

#endif /* MiniGamePopUp_hpp */

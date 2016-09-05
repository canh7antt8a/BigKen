//
//  CircleBar.hpp
//  MyCards
//
//  Created by hungle on 4/20/16.
//
//

#ifndef CircleBar_hpp
#define CircleBar_hpp

#include "string"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "UI/MSprite.hpp"

using namespace cocos2d::ui;

USING_NS_CC;

class CircleBar : public Node {
public:
    CREATE_FUNC(CircleBar);
    
    virtual bool init();
    virtual void onExit();
    
    virtual void disappear();
    virtual void appear(float time);
    
protected:
    Layer                       *m_popupLayer;
    MSprite                     *background;
    Sprite                     *progress;
    
    ActionInterval              *m_appearAction;
    ActionInterval              *m_disappearAction;
    RepeatForever* rotateAppear;
};


#endif /* CircleBar_hpp */

//
//  ItemShowGame.hpp
//  MyCards
//
//  Created by hungle on 8/5/16.
//
//

#ifndef ItemShowGame_hpp
#define ItemShowGame_hpp

#include "cocos2d.h"
#include "CardSpriteEventDelegate.hpp"

class ItemShowGame : public cocos2d::Sprite {
public:

    static ItemShowGame* create(std::string texture,int index,cocos2d::Size size,CardSpriteEventDelegate *cardEvent);
    virtual bool init() override;
    void onEnter() override;
    void addEvents();
    void setEvent(CardSpriteEventDelegate *cardEvent);
    void touchEvent(cocos2d::Touch* touch);
    CardSpriteEventDelegate *cardEvent;
    
    CREATE_FUNC(ItemShowGame);
};

#endif /* ItemShowGame_hpp */

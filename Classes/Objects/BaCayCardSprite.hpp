//
//  BaCayCardSprite.hpp
//  MyCards
//
//  Created by hungle on 8/3/16.
//
//

#ifndef BaCayCardSprite_hpp
#define BaCayCardSprite_hpp

#include "Card.hpp"
#include "cocos2d.h"

class BaCayCardSprite : public cocos2d::Sprite {
public:
    
    static BaCayCardSprite* createCard(Card card, float width);
    virtual bool init() override;
    void onEnter() override;
    void addEvents();
	void removeEvents();
    void update();
    
    CREATE_FUNC(BaCayCardSprite);
    
    CC_SYNTHESIZE(Card, _card, Card);
    
private:
    
    float getWidth();
    float getHeight();
    
    cocos2d::Point touchOffset;
    
public:
    
    
};

#endif /* BaCayCardSprite_hpp */

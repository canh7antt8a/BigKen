//
//  MauBinhCardSprite.hpp
//  MyCards
//
//  Created by hungle on 8/1/16.
//
//

#ifndef MauBinhCardSprite_hpp
#define MauBinhCardSprite_hpp

#include "cocos2d.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "CardSpriteMoveDelegate.h"
#include "Card.hpp"

using namespace std;
using namespace cocos2d;

struct PosIndex {
    int x;
    int y;
};

class MauBinhCardSprite : public cocos2d::Sprite {
public:

    static MauBinhCardSprite* createCard(Card card, PosIndex posIndex, float width,CardSpriteMoveDelegate* cardEvent);
    virtual bool init() override;
    void onEnter() override;
    void addEvents();
    void setEvent(CardSpriteMoveDelegate *cardEvent);
    void touchEvent(cocos2d::Touch* touch);
    
    CardState cardState;
    float posY;
    cocos2d::Sprite* hidden;
    
    void update();
    
    CREATE_FUNC(MauBinhCardSprite);
    
    CC_SYNTHESIZE(Vec2, _currentPos, CurrentPos);
    CC_SYNTHESIZE(Card, _card, Card);
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex);
    
public:
    
    void addHidden();
    //MOVE
    void setMoveToCenter(int sizeIndex,int index,Vec2 origin,
                         Size visibleSize,float cardWidth);
    
    void setState(CardState state);
    enum CardState getState();
    
    void setNumberValue(int numberValue);
    int getNumberValue();
    
    void setCardType(CardType type);
    CardType getCardType();
    
    void setReady(bool isReady);
    bool getReady();
    
    void showHidden(bool show);
    void setPosY(float posY);
    void setSuggest(bool suggest);
    bool getSuggest();
    
    void setMoveUp(int index);
    void setMoveDown();
    
private:
    cocos2d::Vec2 originPostion;
    std::string value;
    int cardValue;
    int numberValue;
    
    int index;
    
    bool isReady = false;
    bool suggest = false;
    
    bool isSavedPosition;
    CardSpriteMoveDelegate *cardEvent;
    cocos2d::Point touchOffset  ;
    
public:
    
    float getWidth();
    float getHeight();
    cocos2d::Size getSize();
};

#endif /* MauBinhCardSprite_hpp */

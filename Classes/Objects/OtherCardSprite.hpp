#ifndef OtherCardSprite_hpp
#define OtherCardSprite_hpp

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class OtherCardSprite : public cocos2d::Sprite {
public:
    static OtherCardSprite* create(int value,float width);
    static OtherCardSprite* createSelf(int value,float width);
    static OtherCardSprite* createCardCover(float width);
    virtual bool init() override; // Initializing process
    
    CC_SYNTHESIZE(bool, _isHighLight, HighLight);
    void onEnter() override; // Display pre-treatment
    
    CREATE_FUNC(OtherCardSprite);
    
public:
    void setMoveFromToPhom(Vec2 pos1,Vec2 ps2);
    void setMoveToCenterPhom(int indexUser,int indexCard,Vec2 origin,Size visibleSize,float cardWidth);
    void setMoveHaBaiPhom(Vec2 pos,int indexUser,int indexCard,int sizePhom,int indexPhom,Vec2 origin,Size visibleSize,float cardWidth,bool animate);
    void setMoveGuiBaiPhom(Vec2 pos,float posY,int indexUser,int indexCard,int sizePhom,int indexPhom,Vec2 origin,Size visibleSize,float cardWidth);
    
    void setMoveToCenter(int sizeIndex,int index,Vec2 origin,Size visibleSize,float cardWidth,int randomX);
    void setMoveToCenterSelf(int sizeIndex,int index,Vec2 origin,Size visibleSize,float cardWidth,int randomX);
    void setValue(int value);
    int getValue();
    float getWidth();
    float getHeight();
    
    void addEvent(int posIndex);
    
    Vec2 getCardPostionPhom(int indexUser,int indexCard,float cardWidth);
    Vec2 getCardCoverPostionPhom(int index,float cardWidth,Size visibleSize);
    
    void addHidden();
    void showHidden(bool hidden);
    
    string getSpriteName(int value);
    
private:
    int value;
};
#endif /* OtherCardSprite_hpp */

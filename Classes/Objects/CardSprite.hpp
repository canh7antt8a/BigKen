#ifndef CardSprite_hpp
#define CardSprite_hpp

#include "cocos2d.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "CardSpriteEventDelegate.hpp"
#include "Card.hpp"

using namespace std;
using namespace cocos2d;

struct PositionIndex {
    int x;
    int y;
};

class CardSprite : public cocos2d::Sprite {
public:
	static CardSprite* create(Card card, PositionIndex PositionIndex, float scale,CardSpriteEventDelegate *cardEvent);
    static CardSprite* createCard(Card card, PositionIndex PositionIndex, float width, CardSpriteEventDelegate* cardEvent);
    virtual bool init() override;
    void onEnter() override;
    void addEvents();
    void setEvent(CardSpriteEventDelegate *cardEvent);
    void touchEvent(cocos2d::Touch* touch);
    
    CardState cardState;
    float posY;
    cocos2d::Sprite* hidden;
    
    void update();
    
    CREATE_FUNC(CardSprite);
    
    CC_SYNTHESIZE(Card, _card, Card);
    CC_SYNTHESIZE(PositionIndex, _positionIndex, PositionIndex);
    
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
    float getPosY();
    void setSuggest(bool suggest);
    bool getSuggest();
    
    void setMoveUp(int index);
    void setMoveDown();
    bool isFlip() const; 
    void setFlip(bool _isFlip);
    void flipCard();
    
private:
	cocos2d::Vec2 originPostion;
    std::string value;
    int cardValue;
    int numberValue;
    
    int index;
    
    bool isReady = false;
    bool suggest = false;
    bool _flip;
    
    bool isSavedPosition;
    CardSpriteEventDelegate *cardEvent;
    
public:
    
    float getWidth();
    float getHeight();
    cocos2d::Size getSize();
};

#endif /* CardSprite_hpp */

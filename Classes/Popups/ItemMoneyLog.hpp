#ifndef ItemMoneyLog_hpp
#define ItemMoneyLog_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI/MSprite.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MLabel.hpp"
#include "protobufObject/lookup_money_history.pb.h"

using namespace cocos2d;
USING_NS_CC;
using namespace cocos2d::ui;

class ItemMoneyLog : public Node {
public:
    
    ItemMoneyLog();
    virtual ~ItemMoneyLog();
    
    bool init();
    
	static ItemMoneyLog* createMoneyLog(BINMoneyLog moneyLog, int pos);
    
    virtual void onExit();
    
    float getWidth();
    float getHeight();
};



#endif /* ItemCell_hpp */

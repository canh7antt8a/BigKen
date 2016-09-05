//
//  MLabel.hpp
//  GameVina
//
//  Created by Black3rry on 3/25/16.
//
//

#ifndef MLabel_hpp
#define MLabel_hpp

#include "cocos2d.h"
#include "Utils/TLMNConfig.hpp"

class MLabel : public cocos2d::Label{
  
public:
    static MLabel* create(std::string text,float size);
    static MLabel* create(std::string text,float size,cocos2d::Color3B color);
    static MLabel* create(std::string text,float size,cocos2d::Color3B color,int tag);
    static MLabel* createCountDown(int timeCountDown);
    static MLabel* createClockCountDown(int timeCountDown);
    static MLabel* createWithBitmapFont(std::string text,std::string fontName);
    
    static MLabel* createUpdateMoney(long long money);
	static MLabel* createUpdateMoney(long long money, int time_delay, float height, std::string text);
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MLabel);
    
public:
    
    float getWidth();
    float getHeight();
    
};

#endif /* MLabel_hpp */

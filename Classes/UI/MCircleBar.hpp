//
//  MCircleBar.hpp
//  MyCards
//
//  Created by hungle on 5/4/16.
//
//

#ifndef MCircleBar_hpp
#define MCircleBar_hpp

#include "cocos2d.h"

class MCircleBar :public cocos2d::Sprite{
public:
    MCircleBar() {
        dis = 0;
        _divisorValue = 0;
        _dividendValue = 0;
    }
    static MCircleBar *createWithPer(float percent,float time);
    bool initWithPer(float percent,float time);
    void upDatePer(float percent,float time);
    void makeProgressBar(float percent,float time);
    void setBarValue(int divisorValue, int dividendValue);
private:
    float dis;
    int _divisorValue;
    int _dividendValue;
};

#endif /* MCircleBar_hpp */

//
//  MToast.hpp
//  MyCards
//
//  Created by hungle on 6/7/16.
//
//

#ifndef MToast_hpp
#define MToast_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "UI/MLabel.hpp"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define TOAST_TEXT_COLOR Color3B(255,255,255)  // màu text của Toast
class MToast : public LayerColor {
private:
    ui::Scale9Sprite *spriteBackground;
    MLabel *labelMessasge;
    
    void initUI();
    void onHideToast();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    CREATE_FUNC(MToast);
    ~MToast();
    void show(const char *message, float duration);
	void showWithWrap(const char *message, float duration);
	void initParams();
	ui::Scale9Sprite* getBackground();
	MLabel* getLabelMessage();
};

#endif /* MToast_hpp */

#ifndef FriendCell_h
#define FriendCell_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI/MSprite.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MLabel.hpp"
#include <protobufObject/user_info.pb.h>

using namespace cocos2d;
USING_NS_CC;
using namespace cocos2d::ui;

class FriendCell : public Node {
public:
    
    FriendCell();
    virtual ~FriendCell();
    
    bool init();
    
    static FriendCell* createFriendCell(BINUserInfo friendCell, int pos, int add_size);
    
    virtual void onExit();
    
    float getWidth();
    float getHeight();
protected:
  MButton *tab_friend_active;
  MButton *btn_avatar;
  float text_size;
};


#endif /* ItemCell_hpp */

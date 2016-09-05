//
//  PopupReconnect.hpp
//  MyCards
//
//  Created by hungle on 6/20/16.
//
//

#ifndef PopupReconnect_hpp
#define PopupReconnect_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC; 

class PopupReconnect : public Node {
    
public:
    PopupReconnect();
    ~PopupReconnect();
    static PopupReconnect* getInstance();
    void setRoomIndex(int roomIndex);
    int getRoomIndex();
    bool init();
    void showPopup();
    void hidePopup();
    
private:
    int roomIndex;
    static PopupReconnect* _instance;
    void menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
};

#endif /* PopupReconnect_hpp */

//
//  PopUpVongQuayMayMan.hpp
//  MyCards
//
//  Created by hungle on 8/10/16.
//
//

#ifndef PopUpVongQuayMayMan_hpp
#define PopUpVongQuayMayMan_hpp

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "protobufObject/enter_zone.pb.h"
#include <vector>
#include "UI/MEditBox.hpp"
#include "Utils/Common.h"


using namespace std;

class PopUpVongQuayMayMan : public Popup {
    
public:
    
    CREATE_FUNC(PopUpVongQuayMayMan);
    
    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
};

#endif /* PopUpVongQuayMayMan_hpp */

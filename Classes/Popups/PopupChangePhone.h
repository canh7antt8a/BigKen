//
//  PopupChangePhone.hpp
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupChangePhone.h
#ifndef __POPUP_CHANGEPHONE_H__
#define __POPUP_CHANGEPHONE_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "UI/MEditBox.hpp"
#include <Utils/Common.h>
class PopupChangePhone : public Popup {

public:

    CREATE_FUNC(PopupChangePhone);
    
    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void setPhone(string phone);
    string getPhone();
protected:
    MEditBox *input_phone;
private:
    string phone;
};

#endif /* defined (__POPUP_CHANGEPHONE_H__) */
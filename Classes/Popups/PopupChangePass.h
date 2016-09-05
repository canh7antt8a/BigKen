//
//  PopupChangePass.hpp
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupChangePass.h
#ifndef __POPUP_CHANGEPASS_H__
#define __POPUP_CHANGEPASS_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "UI/MEditBox.hpp"
#include <Utils/Common.h>
class PopupChangePass : public Popup {

public:

    CREATE_FUNC(PopupChangePass);

    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
protected:
    MEditBox *input_old_pass;
    MEditBox *input_new_pass;
    MEditBox *input_confirm_pass;
private:
  string phone;
};

#endif /* defined (__POPUP_CHANGEPASS_H__) */
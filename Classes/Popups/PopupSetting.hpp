//
//  PopupSetting.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.h
#ifndef __POPUP_SETTING_H__
#define __POPUP_SETTING_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "protobufObject/update_user_setting.pb.h"
#include "Utils/Common.h"

class PopupSetting : public Popup {
    
public:
    
    CREATE_FUNC(PopupSetting);
    
    bool init();
    virtual void onExit();
	void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
	void changeOnOffSetting(MButton * button, const char* pkey);

	void updateUserSettingResponse();

	void update(float);

private:
	int TAG_BTN_CLICKED;
	MSprite *contentBackground;
};

#endif /* defined (__POPUP_SETTING_H__) */
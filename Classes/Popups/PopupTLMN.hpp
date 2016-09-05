//
//  PopupSetting.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.h
#ifndef __POPUP_TLMN_H__
#define __POPUP_TLMN_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "Scenes/BaseScene.hpp"

class PopupTLMN : public Popup {
    
public:

    void createPopUp(int roomIndex);
    
    CREATE_FUNC(PopupTLMN);
    
    bool init();
    virtual void onExit();
	void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    static PopupTLMN* createPopup(int roomIndex);
    void setRoomIndex(int roomIndex);
    int getRoomIndex();
private:
    int roomIndex;
    bool check_exit_room;
};

#endif /* defined (__POPUP_TLMN_H__) */

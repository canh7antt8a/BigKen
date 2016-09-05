//
//  PopupSetting.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.h
#ifndef __POPUP_CREATEROOM_H__
#define __POPUP_CREATEROOM_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "protobufObject/enter_zone.pb.h"
#include <vector>
#include "UI/MEditBox.hpp"
#include "Utils/Common.h"


using namespace std;

class PopupCreateRoom : public Popup {
    
public:
    
    CREATE_FUNC(PopupCreateRoom);
    
    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void moneyPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void changeOnOffSetting(MButton * button, const char* pkey);

    void showGoldBet(vector<BINRoomConfig> goldRoomList, MSprite* itemRow, float top, float height);
    void showCashBet(vector<BINRoomConfig> cashRoomList, MSprite* itemRow, float top, float height);
    
    //static PopupCreateRoom* createPopupCreateRoom(vector<BINRoomConfig> cashRoomList, vector<BINRoomConfig> goldRoomList);
    //void setCashRoomList(vector<BINRoomConfig> cashRoomList);
    //void setGoldRoomList(vector<BINRoomConfig> goldRoomList);
    //vector<BINRoomConfig> getCashRoomList();
    //vector<BINRoomConfig> getGoldRoomList();
protected:
  //MButton * room_active;
  MButton * gold_button;
  MButton * cash_button;
  MButton * button_active;
  int active_bet;
  MEditBox *input_password;
  bool is_vip_room;
  float top;
  float height;
private: 
  bool canCreateRoom = true;
  //vector<BINRoomConfig> cashRoomList;
  //vector<BINRoomConfig> goldRoomList;
};

#endif /* defined (__POPUP_SETTING_H__) */
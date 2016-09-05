//
//  Utility.h
//  MyCards
//
//  Created by hungle on 4/26/16.
//
//

#ifndef Utility_h
#define Utility_h

#define MUSIC "music"
#define SOUND "sound"
#define VIBARTE "vibarte"
#define AUTOREADY "autoready"
#define DENY_INVITES "denyinvites"
#define USER_INFOR "user_infor"
#define AUTO_SIT "auto_sit"
#define NOTIFY_TABLE "notify_table"

#define MUSIC_TEXT "Nhạc nền"
#define SOUND_TEXT "Âm thanh"
#define VIBARTE_TEXT "Rung"
#define AUTO_READY_TEXT "Tự động sẵn sàng"
#define DENY_INVITES_TEXT "Từ chối lời mời"
#define AUTO_SIT_TEXT "Tự động ngồi xuống"
#define NOTIFY_TANLE_TEXT "Thông báo trong bàn chơi"
#define SETTING_TEXT "Cài đặt"
#define INFO_INPUT "Nhập thông tin"
#define CHANGE_PASS "Đổi mật khẩu"
#define FRIEND_TEXT "Bạn bè"
#define NUMBER_PLAY_TEXT "Số ván chơi"
#define NUMBER_PLAY_LOST_TEXT "Số ván thua"
#define NUMBER_PLAY_WIN_TEXT "Sô ván thắng"
#define UNFRIEND_TEXT "Hủy kết bạn"
#define ADD_FRIEND_TEXT "Kết bạn"
#define SEND_SMS_TEXT "Gửi tin nhắn"
#define REMOVE_REQUEST_TEXT "Xóa yêu cầu"
#define ACCEPT_FRIEND_TEXT "Chấp nhận"
#define SEND_SMS_TEXT "Gửi tin nhắn"
#define UNFRIEND_SUCCESS_TEXT "Hủy kết bạn thành công"
#define SUCCESS_TEXT "Thực hiện thành công"
#define OLD_PASS_TEXT "Mật khẩu cũ"
#define NEW_PASS_TEXT "Mật khẩu mới"
#define CONFIRM_PASS_TEXT "Nhập lại mật khẩu mới"

#define GAME_FONTS "fonts/gamevina.otf"
#define CREATE_ROOM_TEXT "Tạo Bàn Mới"
#define GOLD_TABLE_TEXT "Bàn Thường"
#define CASH_TABLE_TEXT "Bàn Vip"
#include "Image.h"
#define REPLACESCENE(X,Y) \
auto MACRO_tmp_1 = (X); \
auto MACRO_tmp_2 = (Y); \
    Director::getInstance()->replaceScene(TransitionCrossFade::create(MACRO_tmp_1, MACRO_tmp_2)); \

#define ADD_CHILD(X, Y) \
auto MACRO_tmp_1 = (X); \
auto MACRO_tmp_2 = (Y); \
if (MACRO_tmp_2->getParent() == nullptr) {\
MACRO_tmp_1->addChild(MACRO_tmp_2); \
} \


#include "cocos2d.h"

#define USER_NAME "user_name"
#define USER_PASSWORD "user_password"

using namespace cocos2d;
using namespace std;

inline void setPrefString(const char *tag,string set){
    UserDefault::getInstance()->setStringForKey(tag, set);
}

inline string getPrefString(const char *tag){
    return UserDefault::getInstance()->getStringForKey(tag);
}

inline void setPrefs(const char *tag,bool set){
    UserDefault::getInstance()->setBoolForKey(tag,set);
}

inline bool getPrefs(const char *tag){
    return UserDefault::getInstance()->getBoolForKey(tag,true);
}

inline string getImagePrefs(const char *tag){
  return getPrefs(tag) ? IMAGE_ON : IMAGE_OFF;
}


#endif /* Utility_h */

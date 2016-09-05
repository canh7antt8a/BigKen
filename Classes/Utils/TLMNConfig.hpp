//
//  TLMNConfig.hpp
//  MyCards
//
//  Created by Black3rry on 4/9/16.
//
//

#ifndef __TLMNCONFIG_H__
#define __TLMNCONFIG_H__

#include "vector"

using namespace std;

extern const int        SCREEN_WIDTH;
extern const int        SCREEN_HEIGHT;

extern const char* SERVER_NAME;
extern const int SERVER_PORT;
extern const char* TurnResponseKey[];
extern vector<const char*> soundTLMN;
extern vector<const char*> soundPhom;
extern vector<int> moneyType; 

enum AssetConfig {
	THE_CAO = 1,
	HIEN_VAT = 2
};

enum ThreeCard_BetType {
	BET_TABLE = 1,
	GOP_GA = 2,
	DANH_BIEN = 3,
	DONG_Y_DANH_BIEN = 4
};

enum ThreeCard_RequestChangeHostType {
	CHECK_CHANGE_CHUONG = 1,
	CONFIRM_SELL_CHUONG = 2,
	CONFIRM_BUY_CHUONG = 3
};

enum {
    kCardLayer1 = 1,
    kCardLayer2 = 1,
    kCardLayer3 = 3,
    kCardLayer4 = 4,
    kCardLayer5 = 5,
    kCardlayer6 = 6
};

enum CardState {
    Idle,
    OnHand,
    OnTable
};

enum ScopeChat {
    CHAT_ROOM = 2,
    CHAT_PRIVATE = 3
};

enum PlayerState{
    NOT_IN_ROOM,
    PLAYING,
    WAITING,
};

enum CardType {
    Hearts = 0,
    Diamonds,
    Clubs,
    Spade,
    OTHER
};

enum CardValue {
    TWO = 12
};

//loai bai la 1 cay, bo doi, bo ba... day lien tiep
enum CheckType {
    NO_CARD = 0,
    CARD_SINGLE = 1,
    CARD_SERIAL = 2,
    CARD_SERIAL_COUPLE = 3,
    CARD_COUPLE = 4,
    CARD_FAIL = 5
};

enum TABLE_ORDERBY {
	MIN_BET = 1,
	NUM_PLAYER = 2,
	INDEX = 3,
};

enum ORDERBY_FIELD_TOP_USER {
	TOP_GOLD = 1,
	TOP_CASH = 2,
	TOP_CAOTHU = 3,
	TOP_LEVEL = 4
};

#define CARD_DOWN 1
#define CARD_UP 2

#define PI 3.14159265
#define CARD_RATIO 1.490909
#define BUTTON_PADDING 15

#define INDEX_BACKGROUND 1
#define INDEX_AVATAR 2
#define INDEX_CARD 3
#define INDEX_ANIMATION 21
#define INDEX_UPDATE_MONEY 22
#define INDEX_POPUP 31
#define INDEX_TOAST 32

// === Login screen

#define LOGIN_BTN_CHOINGAY "btn_choingay_login.png"
#define LOGIN_BTN_DANGKY "btn_dang_ky.png"
#define LOGIN_BTN_DANGNHAP "btn_dangnhap.png"
#define LOGIN_BTN_FACEBOOK "btn_facebook.png"
#define LOGIN_BTN_HOTLINE "btn_hotline.png"
#define LOGIN_BTN_PHONE "btn_phone.png"
#define LOGIN_CHECK_BOX "check_box.png"
#define LOGIN_CHECKEDIT_PASSWORD "checkedit_password.png"
#define LOGIN_SPRITE_GIRL "sprite_cogai.png"
#define LOGIN_EDIT_PASSWORD "edit_password.png"
#define LOGIN_SPRITE_BIGKEN "sprite_bigken.png"
#define LOGIN_BTN_BUTTON "btn_button.png"
#define LOGIN_SPRITE_CARD "sprite_card.png"

//===== message
#define MSG_MAINTAIN "Hệ thống đang bảo trì, vui lòng thử lại"

// ===== Table scene

//table
#define TABLE_BTN_BACK "btn_back_tlmn.png"
#define TABLE_BTN_CAIDAT "btn_caidat.png"
#define TABLE_BTN_CHOINGAY "btn_choingay_table.png"
#define TABLE_BTN_TABBUTTON "btn_tabbutton.png"
#define TABLE_BTN_TAOBAN "btn_taoban.png"
#define TABLE_BTN_TIEN "btn_tien.png"
#define TABLE_BTN_PHONE "btn_call.png"
#define TABLE_BTN_HOPTHU "btn_email.png"
#define TABLE_INSIDE_PROGRESSBAR "inside_progressbar.png"
#define TABLE_SPRITE_SCROLL "sprite_scroll.png"
#define TABLE_SPRITE_TABBUTTION "sprite_tabbutton.png"
#define TABLE_SPRITE_XU "sprite_xu.png"
#define TABLE_SPRITE_XUX "sprite_xux.png"
#define TABLE_SPRITE_KEN "sprite_ken.png"
#define TABLE_SPRITE_KENX "sprite_kenx.png"
#define TABLE_UNDER_PROGRESSBAR "under_progressbar.png"
#define TABLE_UNDER_XUKEN "under_xuken.png"
#define TABLE_BK_AVATAR "bk_avatar.png"
#define TABLE_BG_PHONGCHO "bk_phongcho.png"
#define TABLE_BG_PHONGFREE "bk_phongfree.png"
#define TABLE_BG_PHONGVIP "bk_phongvip.png"
#define TABLE_BTN_MENU_KEN "bg_kenmenu.png"
#define TABLE_BTN_MENU_XU "bg_xumenu.png"
#define TABLE_BTN_MENU_CUOCBAN "ic_cuocban.png"
#define TABLE_BTN_MENU_TAOBAN "bg_menu_taoban.png"
#define TABLE_BTN_MENU_REFRESH "bg_menu_refresh.png"
#define TABLE_BG_LST_TABLE "bg_lst_table.png"
#define TABLE_BG_CONTENT_CELL "sprite_cell_content_table.png"
#define TABLE_IC_SAO "bk_iconsao.png"
#define TABLE_IC_SORT "ic_sort_muiten.png"
#define TABLE_CONTENT_CELL_STATUS_PLAYING "Đang chiến"
#define TABLE_CONTENT_CELL_STATUS_MIS_SLOT "Thiếu chân"
#define TABLE_TXT_SOBAN "Số bàn"
#define TABLE_TXT_MUCCUOC "Mức cược"
#define TABLE_TXT_SONGUOICHOI "Số người chơi"
#define TABLE_TXT_TOITHIEU "Tối thiểu"
#define TABLE_TXT_TRANGTHAI "Trạng thái"

#define TEXT_SHOWGAME_HELLO "Chào mừng bạn đã đến với Game Bài Đổi Thưởng BigKen Online !"

//== Register screen

#define BTN_REGISTER_REGISTER "btn_register_register.png"
#define BKG_INPUT_SDT "bkg_input_sdt.png"
#define BKG_INPUT_PASSWORD "bkg_input_password.png"
#define BKG_INPUT_REPASSWORD "bkg_input_repassword.png"
#define SPRITE_BIGKEN_ONLINE "txt_bigken_online.png"
#define SPRITE_GIRL_REGISTER "girl_register.png"
#define BKG_REGISTER "bkg_register.png"

//== List Game Screen
#define BTN_ITEM_GAME "btn_item_game.png"
#define BTN_BACK "btn_back_tlmn.png"
#define BTN_MENU "btn_menu.png"
#define BTN_SETTING "btn_setting"
#define BTN_HELPER "btn_helper.png"
#define BTN_CENTS "btn_load_cents.png"
#define BTN_DOI_THUONG "btn_doi_thuong.png"
#define BTN_CLOSE "close.png"
#define BKG_AVATAR "bkg_avatar.png"
#define SPRITE_COINS "image_coins.png"
#define SPRITE_KENS "image_kens.png"
#define SPRITE_LIST_GAME "girl_list_game.png"
#define BKF_LIST_GAME "bkg_list_game.jpg"

// TLMN
#define BTN_START_MATCH "btn_batdau.png"
#define BTN_MESSAGE "btn_chat.png"
#define BTN_SOUND_ON "btn_sound_on.png"
#define BTN_FACEBOOK "facebook.png"
#define BTN_SOUND_OFF "btn_sound_off.png"
#define BTN_PURCHASE "btn_purcharse.png"
#define BTN_BUTTON "ic_button_primary.png"
#define BKG_CHAT_BOX "bkg_charbox.9.png"
#define BKG_TABLE "bkg_table.jpg"
#define IMAGE_CLOSE "ic_button_close.png"

//3 cay
#define BG_CUOC_BAN "ba_cay/bg_bet_table.png"
#define SPRITE_CUOC_BAN "ba_cay/sprite_sliderbar.png"
#define SPRITE_SLID_BALL "ba_cay/sprite_keo.png"
#define BTN_CUOC_XACNHAN "ba_cay/btn_xacnhan.png"
#define TXT_CUOC_XACNHAN "Xác nhận"
#define BTN_BET_BARIER "ba_cay/sprite_danhbien.png"
#define BTN_GOPGA "ba_cay/sprite_gopga.png"
#define ICON_GA "ba_cay/ga.png"
#define SPRITE_CHUONG "ba_cay/icon_chuong.png"
#define SPRITE_GA "ba_cay/icon_ga.png"
#define SPRITE_BARIER "ba_cay/sprite_bien.png"
#define SPRITE_MUCCUOC "ba_cay/sprite_muccuoc.png"

#define TXT_GOPGA "Góp Gà"
#define MSG_CONFIRM_BET_BARIER "Người chơi %s muốn đánh biên số tiền %lld %s, bạn có muốn thử sức không?"
#define TITLE_POPUP_CONFIRM "Xác nhận"
#define MSG_SELL_CHUONG "Bạn là chương mới, bạn có muốn bán chương không?"
#define MSG_BUY_CHUONG "Người cầm chương muốn bán chương cho bạn, bạn có muốn nhận chương không?"
#define TXT_BTN_START_MATCH "Bắt đầu"
#define TXT_BTN_FINISH "Xếp bài"
#define TXT_ENOUGH_PLAYER "Không đủ người chơi trong phòng"

//title game
#define TXT_TITLE_GAME_TLMN "TIẾN LÊN MIỀN NAM"
#define TXT_TITLE_GAME_BACAY "BA CÂY"
#define TXT_TITLE_GAME_PHOM "PHỎM"
#define TXT_TITLE_GAME_XOCDIA "XÓC ĐĨA"
#define TXT_TITLE_GAME_MAUBINH "MẬU BINH"

//COMMON
extern char* screenshot_path_ios;
extern char* screenshot_path_android;
#define TXT_BTN_DELETE "Xóa"
#define BG_SONGUOIXEM "bg_songuoixem.png"
#define IC_SONGUOIXEM "xocdia/icon_nguoichoingoai.png"
#define TEXT_NOTIFY_FUNCTION_FUTURE "Chức năng hiện đang trong quá trình phát triển"

//xoc dia
#define XOCDIA_BTN_KHUNGCUOC "xocdia/khung_cuoc.png"
#define XOCDIA_BTN_KHUNGCUOC_WIN "xocdia/khung_cuoc_win.png"
#define XOCDIA_BTN_CUOC "xocdia/bg_cuoc.png"
#define XOCDIA_BTN_CUOC_WIN "xocdia/bg_cuoc_win.png"
#define XOCDIA_BTN_XINCAI "xocdia/bg_xinlamnhacai.png"
#define XOCDIA_BTN_HANDLER "xocdia/btn_handler.png"

#define XOCDIA_CHIP1 "xocdia/btn_chipx1.png"
#define XOCDIA_CHIP5 "xocdia/btn_chipx5.png"
#define XOCDIA_CHIP25 "xocdia/btn_chipx25.png"
#define XOCDIA_CHIP50 "xocdia/btn_chipx50.png"
#define XOCDIA_DATCHIP "xocdia/bg_chip.png"
#define XOCDIA_CHIP1_ONBOARD "xocdia/chip1.png"
#define XOCDIA_CHIP5_ONBOARD "xocdia/chip5.png"
#define XOCDIA_CHIP25_ONBOARD "xocdia/chip25.png"
#define XOCDIA_CHIP50_ONBOARD "xocdia/chip50.png"
#define XOCDIA_BAT "xocdia/bk_bat.png"
#define XOCDIA_DIA "xocdia/bk_dia.png"
#define XOCDIA_NUT_DO "xocdia/nut_do.png"
#define XOCDIA_NUT_TRANG "xocdia/nut_trang.png"
#define XOCDIA_SPRITE_DO "xocdia/sprite_le.png"
#define XOCDIA_SPRITE_TRANG "xocdia/sprite_chan.png"

#define XOCDIA_CHIP1_CLICK "xocdia/btn_chipx1_clicked.png"
#define XOCDIA_CHIP1_ROTATE "xocdia/chipx1_rotated.png"
#define XOCDIA_CHIP5_CLICK "xocdia/btn_chipx5_clicked.png"
#define XOCDIA_CHIP5_ROTATE "xocdia/chipx5_roated.png"
#define XOCDIA_CHIP25_CLICK "xocdia/btn_chipx25_clicked.png"
#define XOCDIA_CHIP25_ROTATE "xocdia/chipx25_rotated.png"
#define XOCDIA_CHIP50_CLICK "xocdia/btn_chipx50_clicked.png"
#define XOCDIA_CHIP50_ROTATE "xocdia/btn_chipx50_rotated.png"

#define XOCDIA_TOTAL_CHANLE "xocdia/bg_left_total_chanle.png"
#define XOCDIA_THONGKE_CHANLE "xocdia/bg_thongke_chanle.png"

#define XOCDIA_BG_4TRANG "xocdia/bg_4trang.png"
#define XOCDIA_BG_3TRANG "xocdia/bg_3trang.png"
#define XOCDIA_BG_1TRANG "xocdia/bg_1trang.png"
#define XOCDIA_BG_0TRANG "xocdia/bg_0trang.png"

#define XOCDIA_TEXT_CHAN "CHẴN "
#define XOCDIA_TEXT_LE "LẺ "

//TAG LIST

//Login
#define TAG_LOGIN_SCENE 0
#define TAG_LOGIN_BTN_FACEBOOK 1
#define TAG_LOGIN_BTN_LOGIN 2
#define TAG_LOGIN_BTN_REGISTER 3
#define TAG_LOGIN_BTN_PLAYNOW 4
#define TAG_LOGIN_BTN_FOGOTPASSWORD 5
#define TAG_LOGIN_EDITBOX_MATKHAU 6
#define TAG_LOGIN_EDITBOX_TAIKHOAN 7

#define TXT_LOGIN_BTN_LOGIN "Đăng nhập"
#define TXT_LOGIN_BTN_REGISTER "Đăng kí"
#define TXT_LOGIN_BTN_PLAYNOW "Chơi ngay"
#define TXT_LOGIN_BTN_FACEBOOK "Đăng nhập bằng facebook"
#define TXT_REGISTER_LABEL_NOTIFY "Nhập số điện thoại để nhận đổi thưởng"
#define TXT_CONNECT "Kết nối"
#define TXT_RECONNECT_MESSAGE "Lỗi kết nối máy chủ, vui lòng thử lại."
#define TXT_OK "OK"

//Popup
#define TAG_POPUP_SETTING_SCENE 21
#define TAG_POPUP_BTN_BACK 22
#define TAG_POPUP_BTN_MUSIC 23
#define TAG_POPUP_BTN_SOUND 24
#define TAG_POPUP_BTN_VIBARTE 25 // rung
#define TAG_POPUP_BTN_AUTO_READY 26
#define TAG_POPUP_BTN_DENNY_INVITE 27
#define TAG_POPUP_BTN_AUTO_SIT 28
#define TAG_POPUP_BTN_NOTIFY_TABLE 29
#define TAG_POPUP_RECONNECT 30
//REG
#define TAG_REG_SCENE 40
#define TAG_REG_BTN_REGISTER 41
#define TAG_REG_BTN_BACK 42
#define TAG_REG_EDITBOX_NHAP_MATKHAU 43
#define TAG_REG_EDITBOX_NHAPLAI_MATKHAU 44
#define TAG_REG_EDITBOX_NHAP_SDT 45
#define TAG_REG_EDITBOX_NHAP_TEN 46

//Show
#define TAG_SHOW_SCENE 60
#define TAG_SHOW_BTN_BACK 61
#define TAG_SHOW_BTN_MENU 62
#define TAG_SHOW_BTN_NAPXU 63
#define TAG_SHOW_BTN_TROGIUP 64
#define TAG_SHOW_BTN_CAIDAT 65
#define TAG_SHOW_GAME_XITO 66
#define TAG_SHOW_GAME_PHOM 67
#define TAG_SHOW_GAME_TLMB 68
#define TAG_SHOW_GAME_TLMN 89
#define TAG_SHOW_GAME_BACAY 70
#define TAG_SHOW_GAME_POCKER 71
#define TAG_SHOW_GAME_XOCDIA 72
#define TAG_SHOW_GAME_MAUBINH 59
#define TAG_SHOW_BTN_FRIEND 73
#define TAG_SHOW_BTN_DOI_THUONG 74
#define TAG_SHOW_BTN_AVATAR 75
#define TAG_SHOW_GAME_SAM 76
#define TAG_SHOW_GAME_SAM_2 77
#define TAG_SHOW_BTN_MESSAGE 78
#define TAG_SHOW_BTN_PHONE 79
#define TAG_SHOW_ARROW_BACK 80
#define TAG_SHOW_ARROW_NEXT 81
#define TAG_SHOW_GAME_TALA 82
#define TAG_SHOW_GAME_HOPTHU 83
#define TAG_SHOW_GAME_THONGBAO 84
#define TAG_SHOW_BTN_GIFTCODE 85
#define TAG_SHOW_BTN_XEPHANG 96
#define TAG_SHOW_BTN_REFRESH 86
#define TAG_SHOW_SORT_NUMPLAYER 87
#define TAG_SHOW_SORT_MUCCUOC 88
#define TAG_SHOW_SORT_TOITHIEU 89


//TLMN
#define TAG_BET_1 90
#define TAG_BET_2 91
#define TAG_BET_3 92
#define TAG_BET_4 93
#define TAG_BET_50K 94
#define TAG_BET_100K 95
#define TAG_BET_100K 95

#define TAG_TLMN_SCENE 100
#define TAG_TLMN_BTN_MENU 101
#define TAG_TLMN_BTN_MESSAGE 102
#define TAG_TLMN_BTN_PURCHASE 103
#define TAG_TLMN_BTN_SOUND 104
#define TAG_TLMN_BTN_FACEBOOK 105
#define TAG_TLMN_BTN_CHONLAI 106
#define TAG_TLMN_BTN_XEPBAI 107
#define TAG_TLMN_BTN_DANHBAI 108
#define TAG_TLMN_BTN_BOLUOT 109
#define TAG_TLMN_BTN_EXIT 110
#define TAG_TLMN_START_MATCH 111
#define TAG_TLMN_CREATE_ROOM 112
#define TAG_TLMN_BTN_BACK 113
#define TAG_TLMN_BTN_KHOA 114
#define TAG_TLMN_BTN_PHONGCHO 115
#define TAG_TLMN_BTN_CAIDAT 116
#define TAG_TLMN_BTN_SANSANG 117
#define TAG_TLMN_CREATE_ROOM_GOLD 118
#define TAG_TLMN_CREATE_ROOM_CASH 119
#define TAG_BTN_INVITE_TO_PLAY 120

// 200 - 210 khoang tag danh cho BET
#define TAG_TLMN_CREATE_ROOM_BET 200
//400-450 khoang cho FRIEND LIST
#define TAG_POPUP_SEND_SMS 150
#define TAG_POPUP_UNFRIEND 151
#define TAG_POPUP_FRIEND_LIST 400

//10xx - 11xx
#define TAG_BACAY_BTN_SANSANG 1001
#define TAG_BACAY_BTN_LATBAI 1002
#define TAG_NODE_BACAY_BETTABLE 1003
#define TAG_BTN_CUOC_XACNHAN 1004
#define TAG_BTN_LABEL_MUCCUOC 1005
#define TAG_BTN_BET_BARIER1 1006
#define TAG_BTN_BET_BARIER2 1007
#define TAG_BTN_GOP_GA 1008
#define TAG_BACAY_BTN_SOBAI 1009

#define TAG_BTN_SANSANG 1010

//20xx - 21xx
#define TAG_MAUBINH_BTN_START_MATCH 2001
#define TAG_MAUBINH_BTN_SANSANG 2002
#define TAG_MAUBINH_BTN_XONG 2003
#define TAG_MAUBINH_EFFECT_TEXT 2004

//Table
#define TAG_TABLE_SCENE 120
#define TAG_TABLE_BTN_BACK 121
#define TAG_TABLE_BTN_PLAYNOW 122
#define TAG_TABLE_BTN_CREATE 123
#define TAG_TABLE_BTN_GOTO 124
#define TAG_TABLE_BTN_REFRESH 125
#define TAG_TABLE_BTN_PHONGVIP 126
#define TAG_TABLE_BTN_PHONGFREE 127
#define TAG_TABLE_BTN_HOPTHU 128
#define TAG_TABLE_BTN_TIEN 129
#define TAG_TABLE_BTN_PHONE 130
#define TAG_TABLE_BTN_CAIDAT 131

#define TAG_TABLE_BTN_PHONGCHO 132
#define TAG_TABLE_BTN_VIPXU 133
#define TAG_TABLE_BTN_KEN 134
#define TAG_TABLE_BTN_MUCCUOC 135
#define TAG_TABLE_BTN_SONGUOI 136
#define TAG_TABLE_BTN_KHOA 137

//Intro
#define TAG_INTRO_SCENE 140

//Xoc dia scene
#define TAG_XOCDIA_BTN_X1 141
#define TAG_XOCDIA_BTN_X5 142
#define TAG_XOCDIA_BTN_X25 143
#define TAG_XOCDIA_BTN_X50 144
#define TAG_XOCDIA_CUA_CHAN 145
#define TAG_XOCDIA_CUA_LE 146
#define TAG_XOCDIA_CUA_0_TRANG 147
#define TAG_XOCDIA_CUA_1_TRANG 148
#define TAG_XOCDIA_CUA_3_TRANG 149
#define TAG_XOCDIA_CUA_4_TRANG 152
#define TAG_XOCDIA_BTN_DATLAI 153
#define TAG_XOCDIA_BTN_HUYCUOC 154
#define TAG_XOCDIA_BTN_GAPDOI 155
#define TAG_XOCDIA_BTN_XINCAI 157
#define TAG_XOCDIA_BTN_HUYCAI 158
#define TAG_XOCDIA_NUT_TRANG_DO 156
#define TAG_XOCDIA_OUTSITE_PLAYER 159

// update password
#define TAG_UPDATEPASSWORD_SCENE 160
#define TAG_UPDATEPASSWORD_OLD_PASSWORD 161
#define TAG_UPDATEPASSWORD_NEW_PASSWORD 162
#define TAG_UPDATEPASSWORD_RENEW_PASSWORD 163
#define TAG_UPDATEPASSWORD_BTN_SAVE 164

//popup chat
#define TAG_SEND_MESSAGE 165
#define TAG_EDITBOX_MESSAGE 166
#define TAG_MSG_CHAT_TEMP1 167
#define TAG_MSG_CHAT_TEMP2 168
#define TAG_MSG_CHAT_TEMP3 169
#define TAG_MSG_CHAT_TEMP4 170
#define TAG_MSG_CHAT_TEMP5 171
#define TAG_MSG_CHAT_TEMP6 172
#define TAG_CLOSE 173
#define CONTENT_MESSAGE_CHAT "Nhập nội dung chat"
#define SEND_CHAT "Gửi"
#define MSG_CHAT_TEMP1 "Chào nhé ! mình out"
#define MSG_CHAT_TEMP2 "Đánh nhanh lên"
#define MSG_CHAT_TEMP3 "Bài đẹp quá"
#define MSG_CHAT_TEMP4 "Bài xấu VL"
#define MSG_CHAT_TEMP5 "Bài xấu quá"
#define MSG_CHAT_TEMP6 "chào cả nhà AHI"

//popup create room
#define CR_ROOM_BTN_OK "OK"
#define CR_ROOM_SELECT "Chọn"
#define CR_ROOM_INPUT_PASSWORD "   Nhập mật khẩu"
#define CR_ROOM_INPUT_ROOMNAME "   Nhập tên phòng"
#define CR_ROOM_ROOMNAME "Tên phòng"
#define CR_ROOM_PASSWORD "Mật khẩu"

#define TAG_POPUP_DOITHE_SERIA 300
#define TAG_POPUP_DOITHE_MATHE 301
#define TAG_POPUP_DOITHE_BTN_NAPTHE 302
#define TAG_POPUP_DOITHE_CAPTCHA 303
#define TAG_POPUP_DOITHE_VINAPHONE 304
#define TAG_POPUP_DOITHE_VIETTEL 305
#define TAG_POPUP_DOITHE_MOBIFONE 306
#define TAG_POPUP_DOITHE_RELOAD_CAPTCHA 307

#define TAG_POPUP_BUY_CARD_VIETTEL 320

#define TAG_POPUP_LOCKTABLE_PASSWORD 220
#define TAG_POPUP_LOCKTABLE_EXIT 221
#define TAG_POPUP_LOCKTABLE_OK 222

#define TAG_TABLE_BTN_HOSO 203
#define TAG_TABLE_BTN_HOMTHU 204
#define TAG_TABLE_BTN_LICHSUDOITHUONG 205

#define TAG_TIME_COUNTDOWN 223

//popup confirm
#define TAG_POPUP_CONFIRM_OK 224
#define TAG_POPUP_CONFIRM_NOK 225

// phom scene
#define TAG_PHOM_BTN_DANHBAI 240
#define TAG_PHOM_BTN_XEPBAI 241
#define TAG_PHOM_BTN_BOCBAI 242
#define TAG_PHOM_BTN_ANBAI 243
#define TAG_PHOM_BTN_BATDAU 244
#define TAG_PHOM_BTN_HAPHOM 245
#define TAG_PHOM_BTN_GUIBAI 246
#define TAG_PHOM_BTN_U 247

//popup user infor
#define TAG_POPUP_USERINFO 260
// ho so
#define TAG_POPUP_USERINFO_BTN_EDIT_NAME 261
#define TAG_POPUP_USERINFO_BTN_EDIT_SDT 262
#define TAG_POPUP_USERINFO_BTN_DOI_MATKHAU 263
#define TAG_POPUP_USERINFO_LBL_NAME 264
#define TAG_POPUP_USERINFO_LBL_LEVEL 265
#define TAG_POPUP_USERINFO_LBL_ID 266
#define TAG_POPUP_USERINFO_LBL_VIP 267
#define TAG_POPUP_USERINFO_LBL_SDT 268
#define TAG_POPUP_USERINFO_LBL_KEN 270
#define TAG_POPUP_USERINFO_LBL_SOVANCHOI 271
#define TAG_POPUP_USERINFO_LBL_SOVANTHANG 272
#define TAG_POPUP_USERINFO_LBL_SOVANTHUA 273
#define TAG_POPUP_USERINFO_LBL_CHISOTINNHIEM 274
#define TAG_POPUP_USERINFO_LBL_XU 275
#define TAG_POPUP_UNSERINFO_SAVE 276
#define TAG_POPUP_UNSERINFO_EXIT 278
#define TAG_POPUP_CHANGE_PASS_EXIT 279
#define TAG_POPUP_CHANGE_PASS_SAVE 280

//register
#define MAX_LENGTH_USERNAME 32
#define MIN_LENGTH_USERNAME 6
#define MAX_LENGTH_PASSWORD 32
#define MIN_LENGTH_PASSWORD 8
#define MIN_LENGTH_SERIA 10
#define MAX_LENGTH_SERIA 20
#define MAX_LENGTH_SDT 11
#define INVALID_USERNAME "Tên đăng nhập từ 6 đến 32 ký tự"
#define BLANK_USERNAME "Vui lòng nhập vào ô trống"
#define INVALID_PASSWORD "Mật khẩu từ 8 đến 32 ký tự"
#define INVALID_SERIA "Seria hoặc Mã thẻ không đúng"
#define PASSWORD_NOT_MATCH "Mật khẩu xác nhận không chính xác!"
#define PASSWORD_NOT_CHANGE "Mật khẩu mới không được trùng với mật khẩu cũ"
// nap the
#define BLANK_FILES "Vui lòng nhập đầy đủ dữ liệu"
//mail
#define MAIL_CELL_BACKGROUND "mail/sprite_background.png"
#define MAIL_ICON_MAIL "mail/sprite_email.png"
#define MAIL_SPRITE_CONTENT "mail/sprite_noidung.png"
#define MAIL_THUNG_RAC "mail/btn_thungrac.png"
#define MAIL_DOC_NHAN "mail/btn_doc.png"

#define MAIL_RD_ICON_MAIL "mail/sprite_da_doc_email.png"
#define MAIL_RD_SPRITE_CONTENT "mail/sprite_da_doc_noidung.png"
#define MAIL_RD_THUNG_RAC "mail/btn_da_doc_thungrac.png"
#define MAIL_RD_DOC_NHAN "mail/btn_da_doc.png"

#define MAIL_BG_DOC_MAIL "mail/sprite_docemail.png"
#define MAIL_LINE_TITLE "mail/sprite_line_title.png"
#define MAIL_LINE_CONTENT "mail/sprite_line_content.png"

#define MAIL_FOMAT "- Thời gian gửi: "
#define MAIL_TXT_READ "Đọc"
#define MAIL_TXT_RECV "Nhận"
#define MAIL_TXT_HOME "Hòm thư"
#define TEXT_CONFIRM "Bạn có chắc chắn muốn thực hiện không?"

#define TAG_MAIL_CONTENT 280
#define TAG_MAIL_DEL 281
#define TAG_MAIL_READ 282
#define TAG_MAIL_RECV 283
#define TAG_MAIL_VIEW_READ 284
#define TAG_MAIL_HOME 285
//end mail

//lich su doi thuong
#define LS_DOITHUONG_ODD "ls_doi_thuong/sprite_odd.png"
#define LS_DOITHUONG_TXT_SENDER "Người gửi"
#define LS_DOITHUONG_TXT_CONTENT "Nội dung"
#define LS_DOITHUONG_TXT_TIME "Thời gian"

#define NUM_LOAD_MORE_ITEM 10
#define NUM_LOAD_MORE_FRIEND 10
//end

#define CHANGE_PASSWORD "Đổi mật khẩu"
#define TXT_ADD_FRIEND "Thêm bạn bè"
#define TXT_REMOVE_FRIEND "Hủy kết bạn"
#define TXT_ACCEPT_FRIEND "Chấp nhận kết bạn"
#define TXT_DENY_FRIEND "Từ chối lời mời"
#define TAG_CHANGE_PASSWORD 290

#define TAG_CHANGE_AVATAR 291
#define TAG_CLICK_PLAY_AVATAR 292

//nem gach da
#define TAG_CLICK_PHAO 293
#define TAG_CLICK_DEP 294
#define TAG_CLICK_BEER 295
#define TAG_CLICK_CACHUA 296
#define TAG_CLICK_TRUNG 297
#define TAG_CLICK_ROSE 298

#define TAG_NODE_EMOTICON 299
#define TAG_CLICK_USER_INFO 300
#define TAG_CLICK_USER_OUT 301
//end

#define TAG_ADD_FRIEND 302
#define TAG_REMOVE_FRIEND 303
#define TAG_ACCEPT_FRIEND 304
#define TAG_DENY_FRIEND 305

#define TXT_XOCDIA_XINCAI "Xin làm cái"
#define TXT_XOCDIA_HUYCAI "huỷ làm cái"

#define TAG_NODE_CONTACT_USER 311

//common popup
#define RS_TITLE_POPUP "sprite_title_popup.png"

//popup view player outsite
#define RS_CONTENT_POPUP_VIEW_PLAYER_OUTSITE "popup_view_player_outsite/content_view_player_outsite.png"
#define TAG_POPUP_VIEW_PLAYER_OUTSITE_EXIT 312

//popup top user
#define TAG_POPUP_TOP_PLAYER_EXIT 313
#define TAG_POPUP_TOP_PLAYER_TOP_DOI_THUONG 314
#define TAG_POPUP_TOP_PLAYER_TOP_DAI_GIA 315
#define TAG_POPUP_TOP_PLAYER_TOP_CAO_THU 316

//popup invite to play
#define TAG_POPUP_INVITE_TO_PLAY_EXIT 317
#define TAG_POPUP_INVITE_ALL 318
#define TAG_POPUP_INVITE_SELECT 319
#define TAG_ITEM_INVITE_CHECKED 320

//popup confirm
#define TAG_POPUP_NODE_CONFIRM_EXIT 321

//popup gift code
#define TAG_POPUP_GIFTCODE_EXIT 322
#define TAG_BTN_XACNHAN_GIFTCODE 323

//popup hotline
#define TAG_POPUP_HOTLINE_EXIT 324
#define TAG_POPUP_HOTLINE_CALL_SUPPORT1 325
#define TAG_POPUP_HOTLINE_CALL_SUPPORT2 326

#define POPUP_TAG_FRIEND 331
#define POPUP_TAG_USERINFOR 332
#define POPUP_TAG_DOITHE 333
#define POPUP_TAG_SETTING 334
#define POPUP_TAG_TOPUSER 335
#define POPUP_TAG_PASSWORD 336
#define POPUP_TAG_CREATEROOM 337
#define POPUP_TAG_CHAT 338
#define POPUP_TAG_INVITE 339
#define POPUP_TAG_LOCKTABLE 340
#define POPUP_TAG_OUTSITE_PLAYER 341
#define POPUP_TAG_HOTLINE 342
#define POPUP_TAG_MUATHE 343
#define POPUP_TAG_GIFTCODE 344

#define POPUP_TAG_CHANGE_PASS 346
#define POPUP_TAG_CHANGE_PHONE 347

//popup doi thuong
#define TAG_POPUP_DOITHUONG_EXIT 345

#endif

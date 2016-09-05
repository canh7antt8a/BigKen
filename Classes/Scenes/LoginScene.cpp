#include "LoginScene.h"
#include "RegisterScene.h"
#include "ShowGame.h"
#include "TLMienNam.h"
#include "MauBinhScene.hpp"
#include "PhomScene.hpp"
#include "ThreeCardsScene.hpp"
#include "Popups/PopUpVongQuayMayMan.hpp"

#include "UI/MButton.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MText.hpp"

#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "Utils/Utility.h"

#include "protobufObject/login.pb.h"
#include "protobufObject/quick_play.pb.h"
#include "protobufObject/user_info.pb.h"
#include "protobufObject/enter_room.pb.h"
#include "protobufObject/user_info.pb.h"
#include "protobufObject/update_user_setting.pb.h"
#include <thread>
#include <iostream>

#if WIN32
#pragma comment(lib, "libprotobuf.lib")
#endif

#include <string>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include "zlib.h"

#include "platform/android/jni/JniLink.h"

#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096
#define MAX_SIZE 1024 * 1024

using namespace cocos2d::ui;

#include <stdio.h>
#include <string.h>

Scene* LoginScene::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = LoginScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool LoginScene::init() {
    
    if ( !BaseScene::init() ) {
        return false;
    }
    auto bkg = MSprite::create("sprite_background_login.png",visibleSize);
    bkg->setPosition(MVec2(0, 0));
    
    //loginfacebook Button
	auto btn_login_facebook = MButton::create(LOGIN_BTN_FACEBOOK, TXT_LOGIN_BTN_FACEBOOK, 20, TAG_LOGIN_BTN_FACEBOOK);
    btn_login_facebook->setPosition(MVec2(width-btn_login_facebook->getWidth()*5/4,
                                          height/2-btn_login_facebook->getHeight()*3-20*3));
    btn_login_facebook->setZoomScale(0.01f);
    btn_login_facebook->addTouchEventListener(CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    //choi ngay
	auto btn_playnow = MButton::create(LOGIN_BTN_CHOINGAY, TXT_LOGIN_BTN_PLAYNOW, 20, TAG_LOGIN_BTN_PLAYNOW);
    btn_playnow->setPosition(Vec2(btn_login_facebook->getPosition().x,
                                  btn_login_facebook->getPosition().y
                                  +btn_login_facebook->getHeight()+15));
    //btn_playnow->setBright(false);
    btn_playnow->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    //đăng nhập
	auto btn_login = MButton::create(LOGIN_BTN_DANGNHAP, TXT_LOGIN_BTN_LOGIN, 20,TAG_LOGIN_BTN_LOGIN);
    btn_login->setPosition(Vec2(btn_playnow->getPosition().x,
                                btn_playnow->getPosition().y+btn_playnow->getHeight()+15));
    btn_login->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    //đăng ký
	auto btn_register = MButton::create(LOGIN_BTN_DANGKY, TXT_LOGIN_BTN_REGISTER, 20, TAG_LOGIN_BTN_REGISTER);
    btn_register->setPosition(Vec2(btn_playnow->getPosition().x+btn_playnow->getWidth()
                                   -btn_register->getWidth(),
                                   btn_login->getPosition().y));
    btn_register->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    //quen mk
    auto fogotPassword = MButton::create("Quên mật khẩu?",btn_playnow->getHeight()/3.2f,TAG_LOGIN_BTN_FOGOTPASSWORD);
    fogotPassword->setPosition(Vec2(btn_playnow->getPosition().x+btn_playnow->getWidth()
                                    -fogotPassword->getWidth()-5,
                                    btn_register->getPosition().y+btn_register->getHeight()+15));
    fogotPassword->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    //underline
    auto under_line = MText::create("_________________",btn_playnow->getHeight()/3.2f);
    under_line->setPosition(Vec2(fogotPassword->getPosition().x,fogotPassword->getPosition().y));
    
    //========================= Text Field
    
    // Textfield mat khau
    auto background_matkhau = MSprite::create(LOGIN_EDIT_PASSWORD);
	background_matkhau->setPosition(Vec2(btn_playnow->getPosition().x,
		fogotPassword->getPosition().y + fogotPassword->getHeight() + 10));

	auto bg_edit_text = MSprite::create("edit_login_null.png");
    edit_matkhau = MEditBox::create(background_matkhau->getContentSize(), "edit_login_null.png",
                                         background_matkhau->getHeight()/3);
	edit_matkhau->setPosition(Vec2(background_matkhau->getPosition().x + background_matkhau->getWidth() - bg_edit_text->getWidth(),
                                   fogotPassword->getPosition().y+fogotPassword->getHeight()+10));
    edit_matkhau->setPlaceHolder("Nhập mật khẩu");
	edit_matkhau->setPlaceholderFontColor(Color3B::BLACK);
	edit_matkhau->setFont("fonts/font_title.otf", background_matkhau->getHeight() / 3);
	edit_matkhau->setPlaceholderFont("fonts/font_title.otf", background_matkhau->getHeight() / 3);
	edit_matkhau->setFontColor(Color3B::BLACK);
    edit_matkhau->setMaxLength(12);
    edit_matkhau->setTag(TAG_LOGIN_EDITBOX_MATKHAU);
    edit_matkhau->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    edit_matkhau->setDelegate(this);
    edit_matkhau->setText(getPrefString(USER_PASSWORD).c_str());

    // Textfield tai khoan
	auto background_user = MSprite::create(LOGIN_EDIT_PASSWORD);
	background_user->setPosition(Vec2(btn_playnow->getPosition().x,
		edit_matkhau->getPosition().y + background_matkhau->getHeight() + 10));

	auto icon_user = MSprite::create("icon_user.png");
	icon_user->setPosition(Vec2(background_user->getPosition().x + 10, background_user->getPosition().y
		+ background_user->getHeight() / 2 - icon_user->getHeight() / 2));

	auto icon_matkhau = MSprite::create("icon_pass.png");
	icon_matkhau->setPosition(Vec2(background_matkhau->getPosition().x + icon_user->getWidth() / 2 - icon_matkhau->getWidth() / 2 + 10
		, background_matkhau->getPosition().y + background_matkhau->getHeight() / 2 - icon_matkhau->getHeight() / 2));

	edit_user = MEditBox::create(background_matkhau->getContentSize(), "edit_login_null.png", background_matkhau->getHeight() / 3);
	edit_user->setPosition(Vec2(background_user->getPosition().x + background_user->getWidth() - bg_edit_text->getWidth(),
                                edit_matkhau->getPosition().y+background_matkhau->getHeight()+10));
    edit_user->setPlaceHolder("Nhập tên");
	edit_user->setPlaceholderFontColor(Color3B::BLACK);
	edit_user->setPlaceholderFont("fonts/font_title.otf", background_matkhau->getHeight() / 3);
	edit_user->setFontColor(Color3B::BLACK);
	edit_user->setFont("fonts/font_title.otf", background_matkhau->getHeight() / 3);
    edit_user->setTag(TAG_LOGIN_EDITBOX_TAIKHOAN);
    edit_user->setMaxLength(12);
    edit_user->setDelegate(this);
    edit_user->setText(getPrefString(USER_NAME).c_str());
    
    auto bigken = MSprite::create(LOGIN_SPRITE_BIGKEN);
    bigken->setPosition(btn_playnow->getPosition().x+btn_playnow->getWidth()/2-bigken->getWidth()/2,
                        edit_user->getPosition().y+edit_user->getContentSize().height+25);
    
    //hotline
    auto hotline_txt = MLabel::create("Hotline : 19001755",background_matkhau->getHeight()/3);
    hotline_txt->setPosition(MVec2(15,height-15-hotline_txt->getHeight()));
    
    //version
    auto version_txt = MLabel::create("Ver 1.0",background_matkhau->getHeight()/3);
    version_txt->setPosition(MVec2(width-version_txt->getWidth()-15,
                                   height-15-version_txt->getHeight()));
	
	auto sprite_card = MSprite::create(LOGIN_SPRITE_CARD);
	float scale = 0.9*height / sprite_card->getHeight();
	sprite_card->setScale(scale);
	sprite_card->setPosition(Vec2(originX, originY));

	//girl
	auto girl = MSprite::create(LOGIN_SPRITE_GIRL);
	girl->setScale(0.9*height / girl->getHeight());
	girl->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	girl->setPosition(Vec2(originX + sprite_card->getWidth() * scale / 2, originY));
    
    this->addChild(bkg);
    this->addChild(hotline_txt);
    this->addChild(version_txt);
	this->addChild(sprite_card);
    this->addChild(girl);
    
    this->addChild(btn_login_facebook);
    this->addChild(btn_login);
    this->addChild(btn_register);
    this->addChild(btn_playnow);
    this->addChild(fogotPassword);
    this->addChild(under_line);
    
	this->addChild(background_matkhau);
	this->addChild(icon_matkhau);
	this->addChild(background_user);
	this->addChild(icon_user);
    this->addChild(edit_matkhau);
    this->addChild(edit_user);
    this->addChild(bigken);
    
    this->scheduleUpdate();

    return true;
}

bool LoginScene::isHasPlayingMatch() const {
    return hasPlayingMatch; 
}

void LoginScene::setHasPlayingMatch(bool _hasPlayingMatch) {
    this->hasPlayingMatch = _hasPlayingMatch; 
}

std::string user_id_str;
std::string password_str;

void LoginScene::update(float delta){
    BaseScene::update(delta);
    //handle login
    BINLoginResponse* loginresponse = (BINLoginResponse *) Common::getInstance()->checkEvent(NetworkManager::LOGIN);
    if (loginresponse != 0) {
        CCLOG("login response: %s", loginresponse->DebugString().c_str());
        if (loginresponse->responsecode()) {
            std::string session_id = loginresponse->sessionid();
            cocos2d::UserDefault::getInstance()->setStringForKey(Common::KEY_SESSION_ID,
                                                                 loginresponse->sessionid());
            
            cocos2d::UserDefault::getInstance()->setIntegerForKey(Common::KEY_USER_ID,
                                                                  (int)loginresponse->userinfo().userid());

            setHasPlayingMatch(loginresponse->hasplayingmatch());
            if (loginresponse->has_userinfo()) {
                LoginScene::saveUserInfo(loginresponse->userinfo());
            }
            if (loginresponse->has_usersetting()) {
                LoginScene::saveUserSetting(loginresponse->usersetting());
            }
            
            if (!isHasPlayingMatch()) {
                setPrefString(USER_NAME,edit_user->getText());
                setPrefString(USER_PASSWORD,edit_matkhau->getText());
                auto showgame = ShowGame::createScene();
                REPLACESCENE(0.1f, showgame);
            }
        }else {
            showToast(loginresponse->message().c_str(), 2);
        }
        // Code kill room index
        if (Common::getInstance()->getUserName() == "sanglx") {
            //NetworkManager::getInstance()->getKillRoomMessageFromServer(4, 10);
            NetworkManager::getInstance()->getKillRoomMessageFromServer(4,10);
        }
    }
    this->enterRoomResponseHandler();
}

Vector<SpriteFrame*> LoginScene::getAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void LoginScene::menuCallBack(Ref *pSender, Widget::TouchEventType eventType) {
    if(eventType == Widget::TouchEventType::ENDED){
        
        MButton *button = (MButton*) pSender;
        int tag = button->getTag();
        string user_fb_id;
        string user_fb_name;
        switch (tag) {
            case TAG_LOGIN_BTN_FACEBOOK:
                CCLOG("%s","Login with facebook!");
                
                user_fb_id = Common::getInstance()->getUserIdFacebook();

                CCLOG("xxxxis %s",user_fb_id.c_str());
                
                if(!user_fb_id.empty()){
					user_fb_name = Common::getInstance()->getUserNameFacebook();
                    CCLOG("xxxxname %s",user_fb_name.c_str());
                    NetworkManager::getInstance()->getOpenIdLoginMessageFromServer(Common::FACEBOOK_CHANNEL,user_fb_id, user_fb_name);
                }
                break;
			case TAG_LOGIN_BTN_LOGIN:
				CCLOG("%s", "Login with esxit!");
				NetworkManager::getInstance()->getLoginMessageFromServer(edit_user->getText(), edit_matkhau->getText());
                break;
            case TAG_LOGIN_BTN_REGISTER:
            {
                CCLOG("%s","register with esxit!");
                auto registerscene = RegisterScene::createScene();
                REPLACESCENE(0.25f, registerscene);
            }
                break;
            case TAG_LOGIN_BTN_PLAYNOW:
            {
                string device_id = Common::getInstance()->getDeviceId();
                string device_info = Common::getInstance()->getDeviceInfo();
                NetworkManager::getInstance()->getQuickPlayMessageFromServer(device_id,
                    device_info);
            }
                break;
            case TAG_LOGIN_BTN_FOGOTPASSWORD:
                CCLOG("%s","Forgot_Password!");
                break;
            default:
                break;
        }
    }
}

#pragma mark - EditBoxDelegate

void LoginScene::editBoxEditingDidBegin(ui::EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void LoginScene::editBoxEditingDidEnd(ui::EditBox *editBox) {
    
    switch (editBox->getTag()) {
        case TAG_LOGIN_EDITBOX_MATKHAU:
            password_str = editBox->getText();
            NetworkManager::getInstance()->getLoginMessageFromServer(edit_user->getText(),edit_matkhau->getText());
            CCLOG("%s",password_str.c_str());
            break;
        case TAG_LOGIN_EDITBOX_TAIKHOAN:
            user_id_str = editBox->getText();
            CCLOG("%s",user_id_str.c_str());
            break;
        default:
            break;
    }
}

void LoginScene::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
    CCLOG("%s","edit changed!");
}

void LoginScene::editBoxReturn(ui::EditBox *editBox) {
    
}

void LoginScene::onExit() {
    BaseScene::onExit();
}

void LoginScene::handler(std::vector<std::pair<google::protobuf::Message*, int>> listMessages){
    // CCLOG("OK");
}

void LoginScene::saveUserInfo(BINUserInfo userInfo) {
    Common::getInstance()->setUserName(userInfo.username());
    if (userInfo.has_displayname()) {
        Common::getInstance()->setDisplayName(userInfo.displayname());
    }
    
    if (userInfo.has_level()) {
        Common::getInstance()->setLevel(userInfo.level().level());
    }
    
    if (userInfo.has_cash()) {
        Common::getInstance()->setCash(userInfo.cash());
    }
    
    if (userInfo.has_gold()) {
        Common::getInstance()->setGold(userInfo.gold());
    }
    
    if (userInfo.has_avatarid()) {
        Common::getInstance()->setAvatarId((int)userInfo.avatarid());
    }

	if (userInfo.has_mobile()){
		Common::getInstance()->setPhoneNunber(userInfo.mobile());
	}
}

void LoginScene::saveUserSetting(BINUserSetting userSetting) {
    if (userSetting.has_autoready()) {
        Common::getInstance()->setAutoReady(userSetting.autoready());
		setPrefs(AUTOREADY, userSetting.autoready());
    }
    
    if (userSetting.has_autodenyinvitation()) {
        Common::getInstance()->setAutoDenyInvitation(userSetting.autodenyinvitation());
		setPrefs(DENY_INVITES, userSetting.autodenyinvitation());
    }
}

void LoginScene::enterRoomResponseHandler() {
    BINEnterRoomResponse* enterroomresponse = (BINEnterRoomResponse *)Common::getInstance()
    ->checkEvent(NetworkManager::ENTER_ROOM);
    
    if (enterroomresponse != 0) {
        CCLOG("enter room response: %s", enterroomresponse->DebugString().c_str());
        if (enterroomresponse->responsecode()) {
            vector<BINPlayer> lst_player;
            vector<BINPlayer> waitingPlayerList;
            
            for (int i = 0; i < enterroomresponse->playingplayers_size(); i++) {
                lst_player.push_back(enterroomresponse->playingplayers(i));
            }
            
            for (int i = 0; i < enterroomresponse->waitingplayers_size(); i++){
                waitingPlayerList.push_back(enterroomresponse->waitingplayers(i));
            }
            bool is_create_room =
            Common::getInstance()->getUserId() == (int)enterroomresponse->owneruserid();
			if (enterroomresponse->has_zoneid() && enterroomresponse->has_roomplay()) {
				Common::getInstance()->setZoneId(enterroomresponse->zoneid());

				BINRoomPlay roomPlay = enterroomresponse->roomplay();
                if (enterroomresponse->zoneid() == 5) {
                    auto scene =
						TLMienNam::createScene(roomPlay.roomindex(),
                                           lst_player, waitingPlayerList,
										   is_create_room, TAG_SHOW_GAME_TLMN, true, roomPlay.passwordrequired(),
										   roomPlay.viproom(), roomPlay.minbet(), "", enterroomresponse);
                    REPLACESCENE(0.1f, scene);
                } else if (enterroomresponse->zoneid() == 4) {
                    auto scene =
						PhomScene::createScene(roomPlay.roomindex(),
                                           lst_player, waitingPlayerList,
										   is_create_room, TAG_SHOW_GAME_PHOM, true, roomPlay.passwordrequired(),
										   roomPlay.viproom(), roomPlay.minbet(), enterroomresponse);
                    REPLACESCENE(0.1f, scene);
                }
                else if (enterroomresponse->zoneid() == Common::BACAY_ZONE) {
                    auto scene = ThreeCardsScene::createScene(roomPlay,
                        lst_player, waitingPlayerList, is_create_room, true, enterroomresponse);
                    REPLACESCENE(0.1f, scene);
                }
                else if (enterroomresponse->zoneid() == Common::MAUBINH_ZONE) {
                    auto scene = MauBinhScene::createScene(roomPlay.roomindex(),
                        lst_player, waitingPlayerList, is_create_room, 
                        TAG_SHOW_GAME_MAUBINH, true, roomPlay.passwordrequired(), 
                        roomPlay.viproom(), roomPlay.minbet(), enterroomresponse);
                    REPLACESCENE(0.1f, scene);
                }
            }
        }
    }
}

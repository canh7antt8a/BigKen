#include "RegisterScene.h"
#include "LoginScene.h"
#include "ShowGame.h"

#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "UI/MEditBox.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Utility.h"
#include "Utils/Common.h"

#include "protobufObject/register.pb.h"
#include "protobufObject/login.pb.h"
#include <thread>

#include <iostream>

using namespace cocos2d::ui;

Scene* RegisterScene::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = RegisterScene::create();

    scene->addChild(layer);

    return scene;
}

bool RegisterScene::init() {
    
    if (!BaseScene::init()) {
        return false;
    }
    
    auto bkg = MSprite::create("sprite_background_login.png",visibleSize);
    bkg->setPosition(MVec2(0,0));
    this->addChild(bkg);
    
    this->initMenu();
    
    this->scheduleUpdate();

    return true;
}

void RegisterScene::initMenu(){
    
	auto sprite_card = MSprite::create(LOGIN_SPRITE_CARD);
	float scale = 0.9*height / sprite_card->getHeight();
	sprite_card->setScale(scale);
	sprite_card->setPosition(Vec2(originX, originY));
	this->addChild(sprite_card);

	//girl
	auto girl = MSprite::create(LOGIN_SPRITE_GIRL);
	girl->setScale(0.9*height / girl->getHeight());
	girl->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	girl->setPosition(Vec2(originX + sprite_card->getWidth() * scale / 2, originY));
	this->addChild(girl);
    //==================================== Buttons
    
	auto sprite_edit_password = MSprite::create(LOGIN_EDIT_PASSWORD);
	float positionX = width / 2 + 70;

    //register Button
	auto btn_register = MButton::create("btn_dang_ky.png", TXT_LOGIN_BTN_REGISTER, 20, TAG_REG_BTN_REGISTER);
	btn_register->setPosition(MVec2(positionX //+ sprite_edit_password->getWidth() / 2 - btn_register->getWidth() / 2
		, height / 2 - btn_register->getHeight() * 4 - 15));
    btn_register->setZoomScale(0.01f);
    btn_register->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_register);
    
    auto background_nhap_register = MSprite::create(LOGIN_EDIT_PASSWORD);

    // btn back
    auto btn_back = MButton::create(BTN_BACK, TAG_REG_BTN_BACK);
	btn_back->setPosition(MVec2(10, height - btn_back->getHeight() - 10));
    btn_back->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_back);
    
	auto text_notify = MLabel::create(TXT_REGISTER_LABEL_NOTIFY, btn_register->getHeight() / 4);
	text_notify->setPosition(Vec2(originX + positionX + sprite_edit_password->getWidth() / 2 - text_notify->getWidth() / 2,
		btn_register->getPosition().y + btn_register->getHeight() + 20));
	this->addChild(text_notify);

    //==================================== Text Field
    
	auto nhap_sdt = MEditBox::create(background_nhap_register->getContentSize(),
		LOGIN_EDIT_PASSWORD, background_nhap_register->getHeight() / 3);
	nhap_sdt->setPosition(Vec2(originX + positionX,
		text_notify->getPosition().y + text_notify->getHeight() + 20));
	nhap_sdt->setPlaceHolder("Nhập số điện thoại");
	nhap_sdt->setMaxLength(MAX_LENGTH_SDT);
	nhap_sdt->setTag(TAG_REG_EDITBOX_NHAP_SDT);
	nhap_sdt->setDelegate(this);
	nhap_sdt->setPlaceholderFontColor(Color3B::BLACK);
	nhap_sdt->setFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_sdt->setPlaceholderFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_sdt->setFontColor(Color3B::BLACK);
	this->addChild(nhap_sdt);

    auto nhaplai_matkhau = MEditBox::create(background_nhap_register->getContentSize(),
                                            LOGIN_EDIT_PASSWORD,background_nhap_register->getHeight()/3);
	nhaplai_matkhau->setPosition(Vec2(nhap_sdt->getPosition().x,
		nhap_sdt->getPosition().y + nhap_sdt->getHeight() + 20));
    nhaplai_matkhau->setPlaceHolder("Nhập lại mật khẩu");
    nhaplai_matkhau->setMaxLength(12);
    nhaplai_matkhau->setTag(TAG_REG_EDITBOX_NHAPLAI_MATKHAU);
    nhaplai_matkhau->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    nhaplai_matkhau->setDelegate(this);
	nhaplai_matkhau->setPlaceholderFontColor(Color3B::BLACK);
	nhaplai_matkhau->setFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhaplai_matkhau->setPlaceholderFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhaplai_matkhau->setFontColor(Color3B::BLACK);
    this->addChild(nhaplai_matkhau);
    
    // editbox nhap mat khau

    auto nhap_matkhau = MEditBox::create(background_nhap_register->getContentSize(),
                                         LOGIN_EDIT_PASSWORD,background_nhap_register->getHeight()/3);
	nhap_matkhau->setPosition(Vec2(nhap_sdt->getPosition().x,
                                   nhaplai_matkhau->getPosition().y+nhaplai_matkhau->getHeight()+20));
    nhap_matkhau->setPlaceHolder("Nhập mật khẩu");
    nhap_matkhau->setMaxLength(12);
    nhap_matkhau->setTag(TAG_REG_EDITBOX_NHAP_MATKHAU);
    nhap_matkhau->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    nhap_matkhau->setDelegate(this);
	nhap_matkhau->setPlaceholderFontColor(Color3B::BLACK);
	nhap_matkhau->setFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_matkhau->setPlaceholderFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_matkhau->setFontColor(Color3B::BLACK);
    this->addChild(nhap_matkhau);
    
    // editbox ten dang nhap
    
    auto nhap_ten = MEditBox::create(background_nhap_register->getContentSize(),
                                     LOGIN_EDIT_PASSWORD,background_nhap_register->getHeight()/3);
	nhap_ten->setPosition(Vec2(nhap_sdt->getPosition().x,
                               nhap_matkhau->getPosition().y+nhap_matkhau->getHeight()+20));
	nhap_ten->setPlaceHolder("Tên đăng nhập");
	nhap_ten->setMaxLength(MAX_LENGTH_USERNAME);
	nhap_ten->setTag(TAG_REG_EDITBOX_NHAP_TEN);
	nhap_ten->setDelegate(this);
	nhap_ten->setPlaceholderFontColor(Color3B::BLACK);
	nhap_ten->setFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_ten->setPlaceholderFont("fonts/font_title.otf", background_nhap_register->getHeight() / 3);
	nhap_ten->setFontColor(Color3B::BLACK);
	this->addChild(nhap_ten);
    
	auto bigken = MSprite::create(LOGIN_SPRITE_BIGKEN);
	bigken->setPosition(MVec2(nhap_sdt->getPosition().x + nhap_ten->getWidth() / 2 - bigken->getWidth() / 2,
		nhap_ten->getPosition().y + nhap_ten->getHeight() + 20));
	this->addChild(bigken);
}

bool registerSuccess = false;

std::mutex mtx_register;
std::string user_id_str_register;
std::string password_str_register;
std::string re_password_str_register;
std::string sdt_str_register;

void RegisterScene::update(float delta){
   
    BaseScene::update(delta);

    BINLoginResponse *loginresponse = (BINLoginResponse*)
        Common::getInstance()->checkEvent(NetworkManager::LOGIN);

    if (loginresponse != 0) {
        CCLOG("login response: %s", loginresponse->DebugString().c_str());
        if (loginresponse->responsecode()) {
            std::string session_id = loginresponse->sessionid();
            cocos2d::UserDefault::getInstance()->setStringForKey(
                Common::KEY_SESSION_ID, loginresponse->sessionid());

            cocos2d::UserDefault::getInstance()->setIntegerForKey(
                Common::KEY_USER_ID, (int)loginresponse->userinfo().userid());
            
			if (loginresponse->has_userinfo()) {
				RegisterScene::saveUserInfo(loginresponse->userinfo());
			}
			if (loginresponse->has_usersetting()) {
				RegisterScene::saveUserSetting(loginresponse->usersetting());
			}
			if (!loginresponse->hasplayingmatch()) {
				setPrefString(USER_NAME, user_id_str_register);
				setPrefString(USER_PASSWORD, password_str_register);
				auto showgame = ShowGame::createScene();
				REPLACESCENE(0.1f, showgame);
			}
        }
        else {
            cocos2d::MessageBox(loginresponse->message().c_str(), "xxx");
        }
    }
    BINRegisterResponse *registerresponse = (BINRegisterResponse*)
        Common::getInstance()->checkEvent(NetworkManager::REGISTER);
    if (registerresponse != 0) {
        CCLOG("register response: %s", registerresponse->DebugString().c_str());
        if (registerresponse->responsecode()) {
            NetworkManager::getInstance()->getLoginMessageFromServer(
                user_id_str_register, password_str_register);
        }
        else {
            cocos2d::MessageBox(registerresponse->message().c_str(), "xxx");
        }
    }
}

void RegisterScene::menuCallBack(Ref *sender,Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        MButton * button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_REG_BTN_REGISTER:
            {
                if(user_id_str_register.empty() || password_str_register.empty()
                  || re_password_str_register.empty()){
                  cocos2d::MessageBox(BLANK_USERNAME, "Đăng ký");
                    return;
                }
                if (user_id_str_register.length() < MIN_LENGTH_USERNAME 
                  || user_id_str_register.length() > MAX_LENGTH_USERNAME){
                  cocos2d::MessageBox(INVALID_USERNAME, "Đăng ký");
                  return;
                }
                if (password_str_register.length() < MIN_LENGTH_PASSWORD 
                  || password_str_register.length() > MAX_LENGTH_PASSWORD){
                  cocos2d::MessageBox(INVALID_PASSWORD, "Đăng ký");
                  return;
                }
                if(password_str_register == re_password_str_register){
                    NetworkManager::getInstance()->getRegisterMessageFromServer(
						user_id_str_register, password_str_register, re_password_str_register, "", sdt_str_register);
                } else {
                    showToast(PASSWORD_NOT_MATCH, 2);
                }
            }
                break;
            case TAG_REG_BTN_BACK:
                {
                    auto loginscene = LoginScene::createScene();
					REPLACESCENE(0.25f, loginscene);
                    //Director::getInstance()->popScene();
                }
                break;
            default:
                break;
        }
    }
}

void RegisterScene::editBoxEditingDidBegin(ui::EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void RegisterScene::editBoxEditingDidEnd(ui::EditBox *editBox) {
    switch (editBox->getTag()) {
        case TAG_REG_EDITBOX_NHAP_MATKHAU:
            password_str_register = editBox->getText();
            CCLOG("%s",this->nhap_matkhau_str.c_str());
            break;
        case TAG_REG_EDITBOX_NHAPLAI_MATKHAU:
            re_password_str_register = editBox->getText();
            CCLOG("%s",this->nhaplai_matkhau_str.c_str());
            break;
		case TAG_REG_EDITBOX_NHAP_TEN:
			user_id_str_register = editBox->getText();
			CCLOG("%s", this->nhap_sdt_str.c_str());
			break;
        case TAG_REG_EDITBOX_NHAP_SDT:
			sdt_str_register = editBox->getText();
            break;
        default:
            break;
    }
    CCLOG("%s","edit end!");
}

void RegisterScene::editBoxTextChanged(ui::EditBox *editBox, std::string &text) {
    CCLOG("%s","edit changed!");
}

void RegisterScene::editBoxReturn(ui::EditBox *editBox) {
   
}

void RegisterScene::onExit() {
    BaseScene::onExit();
}


void RegisterScene::saveUserInfo(BINUserInfo userInfo) {
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

void RegisterScene::saveUserSetting(BINUserSetting userSetting) {
	if (userSetting.has_autoready()) {
		Common::getInstance()->setAutoReady(userSetting.autoready());
	}

	if (userSetting.has_autodenyinvitation()) {
		Common::getInstance()->setAutoDenyInvitation(userSetting.autodenyinvitation());
	}
}
#include "ShowGame.h"
#include "LoginScene.h"
#include "TLMienNam.h"
#include "SceneTable.hpp"
#include "IntroScene.h"

#include "UI/MButton.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "Utils/Utility.h"
#include "Utils/Image.h"
#include "protobufObject/enter_zone.pb.h"

#include "Handler/CardHandler.h"
#include "Handler/TLMNCardHandler.h"
#include <iostream>

#include "Utils/AnimationManager.hpp"
#include "Popups/PopupReconnect.hpp"
#include "Popups/MiniGamePopUp.hpp"

using namespace cocos2d::ui;
using namespace std;

#define padding 12

Scene* ShowGame::createScene() {
    auto scene = Scene::create();
    
    auto layer = ShowGame::create();
    
    scene->addChild(layer);

	NetworkManager::getInstance()->getFilterMailFromServer(0, 10, -1);

    return scene;
}

bool ShowGame::init() {
    if ( !BaseScene::init() ) {
        return false;
    }

    auto bkg = MSprite::create(BGR_LISTGAMES,visibleSize);
    bkg->setPosition(MVec2(0,0));
    this->addChild(bkg);
  
    auto btn_back = MButton::createExtends(ICON_BACK_TLMN, "", 30, TAG_SHOW_BTN_BACK);
    btn_back->setPosition(MVec2(padding, height - btn_back->getHeight() - padding));
    btn_back->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
    this->addChild(btn_back);

    //phone
    auto btn_phone = MButton::createExtends(TABLE_BTN_PHONE, "", 30, TAG_SHOW_BTN_PHONE);
    btn_phone->setPosition(Vec2(btn_back->getPosition().x + btn_back->getWidth() + padding, btn_back->getPosition().y));
    btn_phone->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
    this->addChild(btn_phone);

	//btn cai dat
	auto btn_caidat = MButton::create(TABLE_BTN_CAIDAT, TAG_SHOW_BTN_CAIDAT);
	btn_caidat->setPosition(MVec2(width - padding - btn_caidat->getWidth(),
		height - padding - btn_caidat->getHeight()));
	btn_caidat->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
	this->addChild(btn_caidat);

	//btn hop thu
	auto btn_hopthu = MButton::create(TABLE_BTN_HOPTHU, TAG_SHOW_GAME_HOPTHU);
	btn_hopthu->setPosition(Vec2(btn_caidat->getPosition().x - padding - btn_hopthu->getWidth(),
		originY + height - padding - btn_hopthu->getHeight()));
	btn_hopthu->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
	this->addChild(btn_hopthu);

	sprite_new_mail = MSprite::create("bg_songuoixem.png");
	sprite_new_mail->setPosition(Vec2(btn_hopthu->getWidth() - sprite_new_mail->getWidth(), btn_hopthu->getHeight() - sprite_new_mail->getHeight()));
	btn_hopthu->addChild(sprite_new_mail);

	label_number_new_mail = MLabel::create(Common::getInstance()->convertIntToString(totalNewMail), 25);
	label_number_new_mail->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label_number_new_mail->enableOutline(Color4B(201, 227, 29, 255), 2);
	label_number_new_mail->setPosition(Vec2(sprite_new_mail->getWidth()/2
		, sprite_new_mail->getHeight() / 2));
	
	sprite_new_mail->addChild(label_number_new_mail);
	sprite_new_mail->setVisible(false);

	//btn purcharse
	auto btn_purcharse = MButton::create(BTN_PURCHASE, TAG_SHOW_BTN_NAPXU);
	btn_purcharse->setPosition(Vec2(btn_hopthu->getPosition().x - padding - btn_purcharse->getWidth(),
		originY + height - padding - btn_hopthu->getHeight()));
	btn_purcharse->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
	this->addChild(btn_purcharse);

	//bg avatar
	auto bk_avatar = MSprite::create(TABLE_BK_AVATAR);
	bk_avatar->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	bk_avatar->setPosition(Vec2(btn_phone->getPosition().x + btn_phone->getWidth() + padding,
		btn_phone->getPosition().y + btn_phone->getHeight()));
	this->addChild(bk_avatar);

	// avartar
	int avatar_id = Common::getInstance()->getAvatarId();
	auto btn_avatar = MButton::create(StringUtils::format("avatar%d.png", avatar_id), TAG_SHOW_BTN_AVATAR);
	btn_avatar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	btn_avatar->setPosition(Vec2(bk_avatar->getPosition().x + bk_avatar->getWidth()/2,
		bk_avatar->getPosition().y - bk_avatar->getHeight() / 2));
	btn_avatar->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
	this->addChild(btn_avatar);

	//info
	auto label_id = MLabel::create(StringUtils::format("ID: %d", Common::getInstance()->getUserId()), bk_avatar->getHeight()/5);
	label_id->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	label_id->setPosition(Vec2(btn_avatar->getPosition().x + btn_avatar->getWidth() / 2 + padding, btn_avatar->getPosition().y));
	this->addChild(label_id);
	
	//ten hien thi
	auto label_name = MLabel::create(Common::getInstance()->getUserName(), 1.2 * bk_avatar->getHeight() / 5);
	label_name->setPosition(Vec2(btn_avatar->getPosition().x + btn_avatar->getWidth() / 2 + padding, 
		btn_phone->getPosition().y + btn_phone->getHeight()/2));
	this->addChild(label_name);

	float widthName = label_name->getWidth() > label_id->getWidth() ? label_name->getWidth() : label_id->getWidth();

	float widthXuKen = btn_purcharse->getPosition().x - (label_name->getPosition().x + 
		widthName + 3 * padding); //+ btn_purcharse->getWidth()

	auto common = Common::getInstance();

	//ken
	auto _bgr_ken = MSprite::create(SPRITE_BK_XUKEN); //TABLE_SPRITE_KEN
	_bgr_ken->setScaleX((widthXuKen / 2) / (_bgr_ken->getWidth()));
	_bgr_ken->setContentSize(Size(widthXuKen / 2, _bgr_ken->getHeight()));
	_bgr_ken->setPosition(Vec2(btn_purcharse->getPosition().x - _bgr_ken->getWidth() - padding,
		btn_purcharse->getPosition().y + btn_purcharse->getHeight() / 2 - _bgr_ken->getHeight() / 2));
	this->addChild(_bgr_ken);

	auto sprite_ken = MSprite::create(TABLE_SPRITE_KEN);
	sprite_ken->setPosition(Vec2(_bgr_ken->getPosition().x + 5, 
		_bgr_ken->getPosition().y + _bgr_ken->getHeight() / 2 - sprite_ken->getHeight()/2));
	this->addChild(sprite_ken);

	label_ken = MLabel::create(common->numberFormatWithCommas(common->getGold()), _bgr_ken->getHeight()*0.4f);
	label_ken->setPosition(_bgr_ken->getPosition().x + _bgr_ken->getWidth() - label_ken->getWidth() - 5,
		_bgr_ken->getPosition().y + _bgr_ken->getHeight() / 2 - label_ken->getHeight() / 2);
	label_ken->setColor(Color3B(255, 255, 0));
	this->addChild(label_ken);

	//xu
	auto _bgr_xu = MSprite::create(SPRITE_BK_XUKEN); //SPRITE_XU
	_bgr_xu->setScaleX((widthXuKen / 2) / (_bgr_xu->getWidth()));
	_bgr_xu->setContentSize(Size(widthXuKen / 2, _bgr_xu->getHeight()));
	_bgr_xu->setPosition(Vec2(_bgr_ken->getPosition().x - padding - _bgr_xu->getWidth(),
		btn_purcharse->getPosition().y + btn_purcharse->getHeight() / 2 - _bgr_ken->getHeight() / 2));
	this->addChild(_bgr_xu);

	auto sprite_xu = MSprite::create(SPRITE_XU);
	sprite_xu->setPosition(Vec2(_bgr_xu->getPosition().x + 5,
		_bgr_xu->getPosition().y + _bgr_xu->getHeight() / 2 - sprite_xu->getHeight() / 2));
	this->addChild(sprite_xu);
    
	label_xu = MLabel::create(common->numberFormatWithCommas(common->getCash()), _bgr_xu->getHeight()*0.4f);
	label_xu->setPosition(_bgr_xu->getPosition().x + _bgr_xu->getWidth() - label_xu->getWidth() - 5,
		_bgr_xu->getPosition().y + _bgr_xu->getHeight() / 2 - label_xu->getHeight() / 2);
	label_xu->setColor(Color3B(255, 255, 0));
	this->addChild(label_xu);

	sprite_thongtin = MSprite::create(SPRITE_THONGTIN);
	sprite_thongtin->setPosition(Vec2(origin.x + width / 2 - sprite_thongtin->getWidth() / 2,
		btn_avatar->getPosition().y - btn_avatar->getHeight() - padding));
	this->addChild(sprite_thongtin);

	label_hello = MLabel::create(TEXT_SHOWGAME_HELLO, _bgr_xu->getHeight()*0.4f);
	
	label_hello->setColor(Color3B::WHITE);
	label_hello->setPosition(sprite_thongtin->getWidth() / 2 - label_hello->getWidth() / 2,
		sprite_thongtin->getHeight() / 2 - label_hello->getHeight() / 2);
    
	auto bg_thongtin = MSprite::create(SPRITE_THONGTIN);
	ClippingNode* clipText = ClippingNode::create(bg_thongtin);
	clipText->setPosition(Vec2(origin.x + width / 2 - bg_thongtin->getWidth() / 2,
		btn_avatar->getPosition().y - btn_avatar->getHeight() - padding));
	clipText->addChild(label_hello);
	this->addChild(clipText);
    
    auto sprite_thongtin_hidden = MSprite::create("sprite_thongtin_hidden.png");
    sprite_thongtin_hidden->setPosition(Vec2(sprite_thongtin->getPosition().x,
                                             sprite_thongtin->getPosition().y));
    this->addChild(sprite_thongtin_hidden);

    //====================================  navigation bar
    {
        auto bkg_navigationbar = MSprite::create(BGR_UNDERLINE);
        bkg_navigationbar->setScale(width / bkg_navigationbar->getWidth(), 1);
        bkg_navigationbar->setPosition(MVec2(0, 0));
        this->addChild(bkg_navigationbar);      //left

        // doi thuong
        auto btn_doithuong = MButton::createExtends(ICON_DOI_THUONG, "", 30, TAG_SHOW_BTN_DOI_THUONG);
        btn_doithuong->setPosition(MVec2(width / 2 - btn_doithuong->getWidth() / 2, 0));
        btn_doithuong->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
        this->addChild(btn_doithuong);

        // thong bao
		auto btn_thongbao = MButton::createExtendsBottom(ICON_BTN_THONGBAO, "Thông báo", 30, TAG_SHOW_GAME_THONGBAO);

		auto labelTmp = Label::createWithTTF("Tmp", "fonts/gamevina.otf", btn_thongbao->getHeight() / 2.0f);
		float height = labelTmp->getContentSize().height + 5 + btn_thongbao->getHeight();
		btn_thongbao->setPosition(MVec2(width * 5 / 8, bkg_navigationbar->getHeight() / 2 - height / 2
			+ (labelTmp->getContentSize().height + 5)));
		btn_thongbao->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_thongbao);
        
        // chat
		auto btn_chat = MButton::createExtendsBottom(ICON_CHAT, "Chat", 30, TAG_SHOW_BTN_MESSAGE);
		btn_chat->setPosition(Vec2(originX + width * 6 / 8, btn_thongbao->getPosition().y));
		btn_chat->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_chat);

        // giftcode
		auto btn_giftcode = MButton::createExtendsBottom(ICON_GIFTCODE, "Gift code", 30, TAG_SHOW_BTN_GIFTCODE);
		btn_giftcode->setPosition(Vec2(originX + width * 7 / 8 + 10, btn_thongbao->getPosition().y));
		btn_giftcode->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_giftcode);

		//huong dan
		auto btn_help = MButton::createExtendsBottom(ICON_HELP, "Hướng dẫn", 30, TAG_SHOW_BTN_TROGIUP);
		btn_help->setZoomScale(0.2f);
		btn_help->setPosition(Vec2(originX + width * 1 / 8 - btn_help->getWidth(), btn_thongbao->getPosition().y));
		btn_help->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_help);

		//xep hang
		auto btn_xephang = MButton::createExtendsBottom(ICON_TOP, "Xếp hạng", 30, TAG_SHOW_BTN_XEPHANG);
		btn_xephang->setPosition(Vec2(originX + width * 2 / 8 - btn_xephang->getWidth(), btn_thongbao->getPosition().y));
		btn_xephang->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_xephang);

		// banbe
		auto btn_friend = MButton::createExtendsBottom(ICON_FRINED, "Bạn bè", 30, TAG_SHOW_BTN_FRIEND);
		btn_friend->setPosition(Vec2(originX + width * 3 / 8 - btn_friend->getWidth(), btn_thongbao->getPosition().y));
		btn_friend->addTouchEventListener(CC_CALLBACK_2(ShowGame::menuCallBack, this));
		this->addChild(btn_friend);
    }

    //==================================== scroll view - game button
    
    auto bkg_doithuong = MSprite::create(ICON_DOI_THUONG);
    Size scollFrameSize = Size(width,
		sprite_thongtin->getPosition().y - bkg_doithuong->getHeight());
    scrollView = ui::ScrollView::create();
    scrollView->setContentSize(scollFrameSize);
	scrollView->setPosition(Vec2(origin.x, origin.y + bkg_doithuong->getHeight() - 10));
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    scrollView->setScrollBarEnabled(false);
    scrollView->setBounceEnabled(false);
    scrollView->setInertiaScrollEnabled(true);
    scrollView->setTouchEnabled(true);
    
    auto containerSize = Size(scollFrameSize.width * 1.5f, scollFrameSize.height);
    scrollView->setInnerContainerSize(containerSize);
    this->addChild(scrollView);
    scrollPage = 0;
    
    //====
    vector<std::string> nameTabButton = { ICON_PHOM, ICON_XOC_DIA, ICON_TLMN, ICON_BACAY, ICON_MAUBINH };
    vector<int> tagTabButton = { TAG_SHOW_GAME_PHOM, TAG_SHOW_GAME_XOCDIA, TAG_SHOW_GAME_TLMN, TAG_SHOW_GAME_BACAY, TAG_SHOW_GAME_MAUBINH };
    
	auto button_size = Size(visibleSize.width * 0.24f, visibleSize.width * 0.24f * 361 / 310.0f);  //405 / 302.0f
    auto distance_button = (scollFrameSize.width - 5*button_size.width) / 10;

    for (int i = 0; i<nameTabButton.size(); i++){
        auto game_button = MButton::createWidthSize(nameTabButton[i], button_size, tagTabButton[i]);
        game_button->setPosition(Vec2((i+1) * (button_size.width + distance_button) - button_size.width/2,
			containerSize.height / 2));
		game_button->setZoomScale(0.2f);
        game_button->addTouchEventListener(CC_CALLBACK_2(ShowGame::gameItemCallBack, this));
        scrollView->addChild(game_button);
    }

    this->scheduleUpdate();

    return true;
}

//mail
void ShowGame::loadEmail(vector<Mail> lstEmail){
	if (totalNewMail == 0){
		for (int i = 0; i < lstEmail.size(); i++){
			if (!lstEmail[i].getReaded()){
				totalNewMail++;
			}
		}

		if (totalNewMail > 0){
			label_number_new_mail->setString(Common::getInstance()->convertIntToString(totalNewMail));
			sprite_new_mail->setVisible(true);
		}
	}
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeHopThu()->loadMail(lstEmail);
    }
}

void ShowGame::showNumberNewMail(){
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo == nullptr){
        return;
    }
	if (m_popupUserInfo->getNodeHopThu()->getTotalMailLoaded() <= NUM_LOAD_MORE_ITEM){
		if (totalNewMail > 0 && !m_popupUserInfo->getNodeHopThu()->isMailReaded()){
			totalNewMail--;

			if (totalNewMail == 0){
				sprite_new_mail->setVisible(false);
			}
			else {
				sprite_new_mail->setVisible(true);
				label_number_new_mail->setString(Common::getInstance()->convertIntToString(totalNewMail));
			}
		}
	}
}

void ShowGame::readMail(Mail mail){
	showNumberNewMail();
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
    if(m_popupUserInfo != 0){
        m_popupUserInfo->getNodeHopThu()->readMail(mail);
    }
}

void ShowGame::deleteMail(vector<long> lstMailId){
	showNumberNewMail();
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
    if(m_popupUserInfo != 0){
        m_popupUserInfo->getNodeHopThu()->deleteMail(lstMailId);
    }
}
//end mail

//user info
void ShowGame::viewUserInfo(BINViewUserInfoResponse *viewUserInfo){
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
    if(m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeHoSo()->viewUserInfo(viewUserInfo->userinfo());
    }
}
//end

//lich su doi thuong
void ShowGame::loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs){
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeLsDoiThuong()->loadMoneyLogsHistory(lstMoneyLogs);
    }
}

void ShowGame::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_SHOW_BTN_FRIEND:
              CCLOG("%s", "TAG_SHOW_BTN_FRIEND");
              {
                enableTouch = false;
                NetworkManager::getInstance()->getFilterAddFriendFromServer(-1,-1);
                NetworkManager::getInstance()->getFilterFriendFromServer(0, NUM_LOAD_MORE_FRIEND);
              }
              break;
            case TAG_SHOW_BTN_BACK:
              CCLOG("%s", "logout request");
              NetworkManager::getInstance()->getLogoutMessageFromServer(true);
              break;
            case TAG_SHOW_BTN_DOI_THUONG:
                {
                    if (Common::getInstance()->isEnabledTopup()) {
                        if (this->getChildByTag(POPUP_TAG_MUATHE) == nullptr){
							auto m_popupDoiThuong = PopupDoiThuong::create();
							m_popupDoiThuong->setTag(POPUP_TAG_MUATHE);
							m_popupDoiThuong->setContext(this);
							addChild(m_popupDoiThuong, INDEX_POPUP);
							m_popupDoiThuong->appear();
                        }
                    }
                    else {
						this->showToast(MSG_MAINTAIN, 2);
                    }
                }
                break;
            case TAG_SHOW_BTN_AVATAR:
                if(this->getChildByTag(POPUP_TAG_USERINFOR) == nullptr){
                    auto m_popupUserInfo = PopupUserInfo::create();
                    m_popupUserInfo->setTag(POPUP_TAG_USERINFOR);
                    addChild(m_popupUserInfo,INDEX_POPUP);
                    m_popupUserInfo->showPositionTab(1);
                    m_popupUserInfo->appear();
                }
                break;
            case TAG_SHOW_BTN_CAIDAT:
                CCLOG("%s","btn_catdat");
                {
                    enableTouch = false;
                    // POPUP SETTING
                    if(this->getChildByTag(POPUP_TAG_SETTING) == nullptr){
                        auto m_popupSetting = PopupSetting::create();
                        m_popupSetting->setTag(POPUP_TAG_SETTING);
                        addChild(m_popupSetting,INDEX_POPUP);
                        m_popupSetting->appear();
                    }
                    
                }
                break;
			case TAG_SHOW_GAME_HOPTHU:
            {
                if(this->getChildByTag(POPUP_TAG_USERINFOR) == nullptr){
                    auto m_popupUserInfo = PopupUserInfo::create();
                    m_popupUserInfo->setTag(POPUP_TAG_USERINFOR);
					m_popupUserInfo->showPositionTab(2);
                    addChild(m_popupUserInfo,INDEX_POPUP);
                    m_popupUserInfo->appear();
                }
                
                break;
            }
            case TAG_SHOW_BTN_NAPXU:
                CCLOG("%s", "btn_napxu");
                {
                    if (Common::getInstance()->isEnabledPurchaseCash()) {
                        NetworkManager::getInstance()->getCaptchaMessageFromServer(true);
                    }
                    else {
                        this->showToast(MSG_MAINTAIN, 2);
                    }
                }
                break;
                
            case TAG_SHOW_BTN_TROGIUP:
                CCLOG("%s","btn_trogiup");
                NetworkManager::getInstance()->getFilterTopUserMessageFromServer(-1, -1);
                break;
			case TAG_SHOW_BTN_XEPHANG:
                if(this->getChildByTag(POPUP_TAG_TOPUSER) == nullptr){
                    auto m_popup = PopupTopUser::create();
                    m_popup->setTag(POPUP_TAG_TOPUSER);
                    addChild(m_popup,INDEX_POPUP);
                    m_popup->requestTopUser();
                    m_popup->appear();
                }
              break;
			case TAG_SHOW_BTN_GIFTCODE:
                if(this->getChildByTag(POPUP_TAG_GIFTCODE) == nullptr){
                    auto m_popupGiftCode = PopupGiftCode::create();
                    m_popupGiftCode->setContext(this);
                    addChild(m_popupGiftCode,INDEX_POPUP);
                    m_popupGiftCode->appear();
                }
                
				break;
			case TAG_SHOW_BTN_PHONE:
                if(this->getChildByTag(POPUP_TAG_HOTLINE) == nullptr){
                    auto m_popupHotLine = PopupHotLine::create();
                    m_popupHotLine->setTag(POPUP_TAG_HOTLINE);
                    addChild(m_popupHotLine,INDEX_POPUP);
                    m_popupHotLine->appear();
                }
				break;
            default:
                break;
        }
    }
}

void ShowGame::gameItemCallBack(cocos2d::Ref *sender, Widget::TouchEventType type) {
    if(type == Widget::TouchEventType::ENDED){
        gameTag = ((MButton*) sender)->getTag();
        Common::getInstance()->setGameTag(gameTag);
        CCLOG("%d", Common::getInstance()->getZoneId());
		/*int zone = Common::getInstance()->getZoneId();
		showToast(StringUtils::format("%d", zone).c_str(), 2);*/
        NetworkManager::getInstance()->
        getEnterZoneMessageFromServer(Common::getInstance()->getZoneId());
    }
}

void ShowGame::update(float dt) {
	BaseScene::update(dt);

	//=====
	auto position = label_hello->getPosition();
	position.x -= 100 * dt;
	if (position.x  < - label_hello->getWidth())
		position.x = sprite_thongtin->getWidth();
	label_hello->setPosition(position);

    //handle login
    BINEnterZoneResponse* enter_zone_response = (BINEnterZoneResponse*) Common
        ::getInstance()->checkEvent(NetworkManager::ENTER_ZONE);
    
    if (enter_zone_response != 0) { //found
        CCLOG("enter zone: %s", enter_zone_response->DebugString().c_str());
        if (enter_zone_response->responsecode()) {
			//Common::getInstance()->setZoneId(enter_zone_response->);

            if (enter_zone_response->has_enabledisplayroomlist() &&
                enter_zone_response->enabledisplayroomlist()) {
                /*
                 Sau này xử lý phần người chơi click vào một mức cược cụ thể không cần hiển thị danh sách phòng chơi
                 */
                vector<BINRoomConfig> cashRoomList;
                vector<BINRoomConfig> goldRoomList;
                if (enter_zone_response->cashroomconfigs_size() > 0) {
                    for (int i = 0; i < enter_zone_response->cashroomconfigs_size(); i++) {
                        cashRoomList.push_back(enter_zone_response->cashroomconfigs(i));
                    }
                }
                if (enter_zone_response->goldroomconfigs_size() > 0) {
                    for (int i = 0; i < enter_zone_response->goldroomconfigs_size(); i++) {
                        goldRoomList.push_back(enter_zone_response->goldroomconfigs(i));
                    }
                }
                Common::getInstance()->setGoldRoomList(goldRoomList);
                Common::getInstance()->setCashRoomList(cashRoomList);
            }
			
			this->unscheduleUpdate();
            auto scene = SceneTable::createScene(enter_zone_response->enabledisplayroomlist());
            REPLACESCENE(0.25f, scene);
            
        //    return;
        } else {
			Common::getInstance()->setZoneId(-1);  //reset zone id
            showToast(enter_zone_response->message().c_str(), 2);
        }
    }
//logout
    BINLogoutResponse* logout_response = (BINLogoutResponse *)Common::getInstance()->checkEvent(NetworkManager::LOGOUT);
    if (logout_response != 0) {
      CCLOG("exit room response: %s", logout_response->DebugString().c_str());
      if (logout_response->responsecode()) {
          cocos2d::UserDefault::getInstance()->deleteValueForKey(Common::getInstance()
              ->KEY_SESSION_ID);
        Common::getInstance()->setSessionId("-1");

		//gui lai ban tin init
		NetworkManager::getInstance()->getInitializeMessageFromServer(
			Common::getInstance()->getCp(),
			Common::getInstance()->getAppVersion(),
			Common::getInstance()->getCountry(),
			Common::getInstance()->getLanguage(),
			Common::getInstance()->getDeviceId(),
			Common::getInstance()->getDeviceInfo(),
			Common::getInstance()->getIpaddress(), 
            Common::getInstance()->getPackageName()
			);
        /*auto introScene = IntroScene::createScene();
		REPLACESCENE(0.25f, introScene);*/
      } else {
		  showToast(logout_response->message().c_str(), 2);
      }
    }

	//init 
	BINInitializeResponse *init_response = (BINInitializeResponse*)
		Common::getInstance()->checkEvent(NetworkManager::INITIALIZE);
	if (init_response != 0) {
		CCLOG("init response: %s", init_response->DebugString().c_str());
		NetworkManager::setInitialize(init_response->responsecode());
		auto scene = LoginScene::createScene();
		REPLACESCENE(0.25f, scene);
	}

    //bật popup
    BINCaptchaResponse* captcha_response = (BINCaptchaResponse *)Common::getInstance()->checkEvent(NetworkManager::CAPTCHA);
    if (captcha_response != 0) {
        CCLOG("captcha_response: %s", captcha_response->DebugString().c_str());
        if (captcha_response->responsecode()) {
            CCLOG("securitykey: %s", captcha_response->captcha().securitykey().c_str());
            auto m_popupDoiThe = (PopupDoiThe*) this->getChildByTag(POPUP_TAG_DOITHE);
            if(m_popupDoiThe == nullptr){
				m_popupDoiThe = PopupDoiThe::create();
				addChild(m_popupDoiThe, POPUP_TAG_DOITHE);
                m_popupDoiThe->setCaptchaText(captcha_response->captcha().captchachallenge());
                m_popupDoiThe->setSecurityKey(captcha_response->captcha().securitykey());
                m_popupDoiThe->appear();
            }
        }
        else {
			showToast(captcha_response->message().c_str(), 2);
        }
    }
    /*BINFilterTopUserResponse *filter_top_response = (BINFilterTopUserResponse *)
        Common::getInstance()->checkEvent(NetworkManager::FILTER_TOP_USER);
    if (filter_top_response != 0) {
        CCLOG("filter top response: %s", filter_top_response->DebugString().c_str());
        CCLOG("filter top response top player size: %d", filter_top_response->topusers_size());
    }*/

    /*BINLookUpMoneyHistoryResponse *lookupmoneyhistoryresponse = (BINLookUpMoneyHistoryResponse *)
        Common::getInstance()->checkEvent(NetworkManager::LOOKUP_MONEY_HISTORY);

    if (lookupmoneyhistoryresponse != 0) {
        CCLOG("look up money history response: %s", lookupmoneyhistoryresponse->DebugString().c_str());
        CCLOG("look up money history size: %d", lookupmoneyhistoryresponse->moneylogs_size());
    }*/

    //response email
    filterEmailResponse();
    sendMailResponse();
    readMailResponse();
    deleteMailResponse();
    claimMailResponse();
    //end

	//user_info
	viewUserInfoFromServer();

	//update money
	updateMoneyResponseHandler();

	//ls doi thuong
	lookupMoneyHistoryResponse();
    // friend pop up
    turnOnPopupFriendResponseHandler();
}

void ShowGame::gotoMenuDialog(){
}

void ShowGame::turnOnPopupFriendResponseHandler(){
  auto common = Common::getInstance();
  BINFilterFriendResponse *filterFriendResponse =
    (BINFilterFriendResponse*)common->checkEvent(NetworkManager::FILTER_FRIEND);
  if (filterFriendResponse != 0){
      CCLOG("BINFilterFriendResponse: %s", filterFriendResponse->DebugString().c_str());
      int add_size = (int)listFriends.size();
      if (filterFriendResponse->currentfriends_size() > 0) {
        for (int i = 0; i < filterFriendResponse->currentfriends_size(); i++) {
          listFriends.push_back(filterFriendResponse->currentfriends(i));
        }
      }
      auto m_popupFriend = (PopupFriend*)this->getChildByTag(POPUP_TAG_FRIEND);
      if(m_popupFriend == nullptr){
		  m_popupFriend = PopupFriend::create();
		  addChild(m_popupFriend, POPUP_TAG_FRIEND);
          m_popupFriend->resetFriendList();
          m_popupFriend->appear();
          m_popupFriend->setFriendList(listFriends, add_size);
      }
  }

  BINFilterAddFriendResponse *filterAddFriendResponse =
    (BINFilterAddFriendResponse*) Common::getInstance()->checkEvent(NetworkManager::FILTER_ADD_FRIEND);
  if (filterAddFriendResponse != 0){
    CCLOG("BINFilterAddFriendResponse: %s", filterAddFriendResponse->DebugString().c_str());
    CCLOG("BINFilterAddFriendResponse2: %d", filterAddFriendResponse->requestfriends_size());
    listFriends.clear();
    if (filterAddFriendResponse->requestfriends_size() > 0) {
      for (int i = 0; i < filterAddFriendResponse->requestfriends_size(); i++) {
        if (filterAddFriendResponse->requestfriends(i).has_senderuser()) {
            listFriends.push_back(filterAddFriendResponse->requestfriends(i).senderuser());
        }
      }
    }
  }
}

void ShowGame::updateMoneyResponseHandler(){
	auto common = Common::getInstance();

	BINUpdateMoneyResponse *updatemoneyresponse =
		(BINUpdateMoneyResponse*) common->checkEvent(NetworkManager::UPDATE_MONEY);

	if (updatemoneyresponse != 0) {
		CCLOG("update money response: %s", updatemoneyresponse->DebugString().c_str());
		if (updatemoneyresponse->responsecode() && updatemoneyresponse->moneyboxes_size() > 0){

			BINMoneyBox moneyBox;
			long long origin_money;

			for (int i = 0; i < updatemoneyresponse->moneyboxes_size(); i++) {
				moneyBox = updatemoneyresponse->moneyboxes(i);
                bool isCash = moneyBox.iscash();
				if (moneyBox.userid() == Common::getInstance()->getUserId()){
                    origin_money = moneyBox.currentmoney();

					//set lai tien cho nguoi choi
					if (isCash){
						common->setCash(origin_money);
						label_xu->setString(common->numberFormatWithCommas(common->getCash()));
					}
					else {
						common->setGold(origin_money);
						label_ken->setString(common->numberFormatWithCommas(common->getGold()));
					}
					break;
				}
			}
		}
		if (updatemoneyresponse->has_message()){
			showToast(updatemoneyresponse->message().c_str(), 2);
		}
	}
}

void ShowGame::onExit() {
    BaseScene::onExit();
}


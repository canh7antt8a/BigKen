#include "SceneTable.hpp"
#include "TLMienNam.h"
#include "ShowGame.h"
#include "ThreeCardsScene.hpp"
#include "PhomScene.hpp"
#include "ItemCell.hpp"
#include "SocdiaScene.hpp"

#include "UI/MButton.hpp"
#include "UI/MText.hpp"
#include "UI/M9Path.hpp"
#include "UI/MLabel.hpp"

#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "Utils/Utility.h"
#include "Utils/Image.h"
#include "MauBinhScene.hpp"
#include "Popups/MiniGamePopUp.hpp"
#include "Popups/NodeConfirm.hpp"

using namespace cocos2d::ui;
using namespace rapidjson;

#define SCROLL_Y 85
#define SCROLL_HEIGHT 435
#define padding 12

cocos2d::Scene* SceneTable::createScene(bool tempEnableDisplayRoomList) {
    auto scene = Scene::create();
    
    auto layer = SceneTable::create();
    layer->setEnableDisplayRoomList(tempEnableDisplayRoomList);
    
    scene->addChild(layer);
    
    return scene;
}

bool SceneTable::init() {
    if (!BaseScene::init()) {
        return false;
    }
    this->canCreateRoom = true;

	auto background_screen = MSprite::create(BGR_LISTGAMES, visibleSize);
    background_screen->setPosition(Vec2(originX, originY));
    this->addChild(background_screen);
    
    if(enableDisplayRoomList){
        CCLOG("XXXX: true");
    }else{
        CCLOG("XXXX: false");
    }
    
    this->initMenu();
    
    //cap nhat room play sau 5s
    //Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(SceneTable::reloadRoom), this, 5.0f, true, 0, 0);
    //schedule(SEL_SCHEDULE(&SceneTable::reloadRoom), 10.0f);

    this->scheduleUpdate();
    NetworkManager::getInstance()->
    getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
		false, -1, -1, orderByField, true);

	NetworkManager::getInstance()->getFilterMailFromServer(0, 10, -1);

    return true;
}

bool isChangedStatus = false;

void SceneTable::reloadRoom(float dt){
    listRoomPlay.clear();
    NetworkManager::getInstance()->getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
		false, -1, -1, orderByField, true);
}

void SceneTable::update(float delta) {
    BaseScene::update(delta);
    //handle filter room response
    BINFilterRoomResponse* response = (BINFilterRoomResponse*)Common::getInstance()->checkEvent(NetworkManager::FILTER_ROOM);
    if (response != 0){
        CCLOG("filter room response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            for (int i = 0; i < response->roomplays_size(); i++) {
                listRoomPlay.push_back(response->roomplays(i));
            }
            tableView->reloadData();
        }
        else {
            //
        }
    }

    //handle enter room response

    vector<BINPlayer> playerList;
    BINEnterRoomResponse *enterroomresponse = (BINEnterRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::ENTER_ROOM);
    if (enterroomresponse != 0) {
        CCLOG("enter room response: %s", enterroomresponse->DebugString().c_str());
        if (enterroomresponse->responsecode()) {
            vector<BINPlayer> waitingPlayerList;
            Common::getInstance()->setOwnerUserId((int) enterroomresponse->owneruserid());
            
            for (int i = 0; i < enterroomresponse->playingplayers_size(); i++) {
                playerList.push_back(enterroomresponse->playingplayers(i));
            }
            for (int i = 0; i < enterroomresponse->waitingplayers_size();i++){
                waitingPlayerList.push_back(enterroomresponse->waitingplayers(i));
            }

            if (enterroomresponse->has_roomplay()){
                BINRoomPlay roomPlay = enterroomresponse->roomplay();
                CCLOG("room index: %d", roomPlay.roomindex());

                bool is_create_room = (Common::getInstance()->getUserId() == enterroomresponse->owneruserid()) ? true : false;
				if (Common::getInstance()->getZoneId() == Common::TIENLENMIENNAM_ZONE) {
					std::string cardRemainingCount = "";
					for (int i = 0; i < enterroomresponse->args_size(); i++){
						if (enterroomresponse->args(i).key() == "cardRemainingCount"){
							std::string json = enterroomresponse->args(i).value();
							cardRemainingCount = json;
							break;
						}
					}

                    auto tlmiennam = TLMienNam::createScene(roomPlay.roomindex(),
                        playerList, waitingPlayerList, is_create_room, TAG_SHOW_GAME_TLMN,
						this->getEnableDisplayRoomList(), roomPlay.passwordrequired(),
						roomPlay.viproom(), roomPlay.minbet(), cardRemainingCount, NULL);
					
                    REPLACESCENE(0.25f, tlmiennam);
                }
				else if (Common::getInstance()->getZoneId() == Common::PHOM_ZONE) {
                    auto phom = PhomScene::createScene(roomPlay.roomindex(),
                        playerList, waitingPlayerList, is_create_room, TAG_SHOW_GAME_PHOM,
						this->getEnableDisplayRoomList(), roomPlay.passwordrequired(), 
						roomPlay.viproom(), roomPlay.minbet(), NULL);
                    REPLACESCENE(0.25f, phom);
                }
				else if (Common::getInstance()->getZoneId() == Common::BACAY_ZONE) {
					/*std::string startMatchTime = "";
					for (int i = 0; i < enterroomresponse->args_size(); i++){
						if (enterroomresponse->args(i).key() == "startMatchCdRemaining"){
							std::string json = enterroomresponse->args(i).value();
							startMatchTime = json;
							break;
						}
					}*/

                    auto bacay = ThreeCardsScene::createScene(roomPlay, playerList, waitingPlayerList, is_create_room,
						this->getEnableDisplayRoomList(), enterroomresponse);
                    REPLACESCENE(0.25f, bacay);
                }
				else if (Common::getInstance()->getZoneId() == Common::MAUBINH_ZONE) {
                    auto maubinh = MauBinhScene::createScene(roomPlay.roomindex(),
                        playerList, waitingPlayerList, is_create_room, TAG_SHOW_GAME_MAUBINH,
                        this->getEnableDisplayRoomList(), roomPlay.passwordrequired(),
                        roomPlay.viproom(), roomPlay.minbet(), NULL);
                    REPLACESCENE(0.25f, maubinh);
                }
				else if (Common::getInstance()->getZoneId() == Common::XOCDIA_ZONE) {
					auto xocdia = SocdiaScene::createScene(roomPlay.roomindex(), playerList, waitingPlayerList,
						is_create_room, TAG_SHOW_GAME_XOCDIA, this->getEnableDisplayRoomList(),
						roomPlay.passwordrequired(), roomPlay.viproom(),
						roomPlay.minbet(), NULL, roomPlay.roomconfig());
					REPLACESCENE(0.25f, xocdia);
				}
            }
        }
        else {
            this->showToast(enterroomresponse->message().c_str(), 2);
        }
    }
    
    BINCreateRoomResponse *createroomresponse = (BINCreateRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::CREATE_ROOM);
    if (createroomresponse != 0) {
        CCLOG("create room response: %s", createroomresponse->DebugString().c_str());
        this->showToast(createroomresponse->message().c_str(), 2);
        if (createroomresponse->responsecode()) {
			Common::getInstance()->setOwnerUserId((int)createroomresponse->myplayer().userid());

            vector<BINPlayer> waitingPlayerList;
            playerList.push_back(createroomresponse->myplayer());

            BINRoomPlay roomPlay = createroomresponse->roomplay();
            CCLOG("room index: %d", roomPlay.roomindex());
			if (Common::getInstance()->getZoneId() == Common::TIENLENMIENNAM_ZONE) {
                auto tlmiennam = TLMienNam::createScene(roomPlay.roomindex(),playerList, waitingPlayerList,
                                                        true, TAG_SHOW_GAME_TLMN, true,
                                                        roomPlay.passwordrequired(), roomPlay.viproom(),
                                                        roomPlay.minbet(), "", NULL);
                REPLACESCENE(0.25f, tlmiennam);
			}
			else if (Common::getInstance()->getZoneId() == Common::PHOM_ZONE) {
                auto phom = PhomScene::createScene(roomPlay.roomindex(), playerList, waitingPlayerList,
                                                   true, TAG_SHOW_GAME_PHOM, true,
                                                   roomPlay.passwordrequired(), roomPlay.viproom(),
                                                   roomPlay.minbet(), NULL);
                REPLACESCENE(0.25f, phom);
			}
			else if (Common::getInstance()->getZoneId() == Common::BACAY_ZONE) {
				auto bacay = ThreeCardsScene::createScene(roomPlay, playerList, waitingPlayerList, true, true, NULL);
                REPLACESCENE(0.25f, bacay);
			}
			else if (Common::getInstance()->getZoneId() == Common::XOCDIA_ZONE) {
                auto xocdia = SocdiaScene::createScene(roomPlay.roomindex(), playerList, waitingPlayerList,
                                                       true, TAG_SHOW_GAME_XOCDIA, true,
                                                       roomPlay.passwordrequired(), roomPlay.viproom(),
                                                       roomPlay.minbet(), NULL, roomPlay.roomconfig());
                REPLACESCENE(0.25f, xocdia);
            }
			else if (Common::getInstance()->getZoneId() == Common::MAUBINH_ZONE) {
                auto maubinh = MauBinhScene::createScene(roomPlay.roomindex(), playerList, waitingPlayerList, true, 
                    TAG_SHOW_GAME_MAUBINH, true, roomPlay.passwordrequired(), roomPlay.viproom(), roomPlay.minbet(), NULL);
                REPLACESCENE(0.25f, maubinh);
            }
        }
        else {
            this->canCreateRoom = true;
            this->showToast(createroomresponse->message().c_str(), 2);
        }
    }
    
	inviteToRoomResponseHandler();
	replyToInviteResponse();

    /*
     chat response handler
     */
    SceneTable::instantMessageResponseHandle();

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
    exitZoneResponseHandler();

	lookupMoneyHistoryResponse();

	getCapchaMessageResponse();
}

void SceneTable::getCapchaMessageResponse(){
	//bật popup
	BINCaptchaResponse* captcha_response = (BINCaptchaResponse *)Common::getInstance()->checkEvent(NetworkManager::CAPTCHA);
	if (captcha_response != 0) {
		CCLOG("captcha_response: %s", captcha_response->DebugString().c_str());
		if (captcha_response->responsecode()) {
			CCLOG("securitykey: %s", captcha_response->captcha().securitykey().c_str());
			auto m_popupDoiThe = (PopupDoiThe*) this->getChildByTag(POPUP_TAG_DOITHE);
			if (m_popupDoiThe == nullptr){
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
}

void SceneTable::replyToInviteResponse(){
	BINRelyInvitationResponse *response = (BINRelyInvitationResponse*) Common::getInstance()->checkEvent(NetworkManager::RELY_INVITE);
	if (response != 0){
		CCLOG("reply to invite response: %s", response->DebugString().c_str());
		if (response->responsecode()){ // neu chap nhan loi moi thi request enter room
			if (response->accept() && roomIndexInvite != 0){
				/*NetworkManager::getInstance()->getEnterRoomMessageFromServer(roomIndexInvite, "");*/
				roomIndexInvite = 0;
			}
		}
		else {
			if (response->has_message()){
				showToast(response->message().c_str(), 2);
			}
		}
	}
}

void SceneTable::onEvent(int enventType, BINRoomPlay sender){
	if (enventType == OnEvenListener::EVENT_CONFIRM_OK){ //khi click xac nhan xoa email
		//goi network xac nhan
		roomIndexInvite = sender.roomindex();
		NetworkManager::getInstance()->getRelyInviteFromServer(Common::getInstance()->getZoneId(), sender.roomindex(), true);
	}
	else if (enventType == OnEvenListener::EVENT_CANCEL_CONFIRM){
		//huy xac nhan
		roomIndexInvite = 0;
		NetworkManager::getInstance()->getRelyInviteFromServer(Common::getInstance()->getZoneId(), sender.roomindex(), false);
	}
}

//nhan loi moi vao room
void SceneTable::inviteToRoomResponseHandler(){
	BINInviteToRoomResponse *response = (BINInviteToRoomResponse*) Common::getInstance()->checkEvent(NetworkManager::INVITE_TO_ROOM);
	if (response != 0){
		CCLOG("invite to room response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			BINRoomPlay roomPlay = response->roomplay();
			string typeMoney = (roomPlay.viproom() ? " XU" : " KEN");
			string textConfirm = "Người chơi " + response->inviterusername() + " mời bạn chơi game "
				+ Common::getInstance()->getTitleGame() + " tại phòng" + typeMoney + " bàn " + StringUtils::format("%d", roomPlay.roomindex())
				+ " với mức cược " + StringUtils::format("%d", roomPlay.minbet()) + typeMoney;
			//show popup xac nhan loi moi
			NodeConfirm<BINRoomPlay> * nodeConfirm = NodeConfirm<BINRoomPlay>::create(this, "Mời chơi", textConfirm);
			nodeConfirm->setSender(response->roomplay());
			nodeConfirm->showDlg();
		}
		else {
			showToast(response->message().c_str(), 2);
		}
	}
}

//lich su doi thuong
void SceneTable::loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs){
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo == nullptr){
        return;
    }
	m_popupUserInfo->getNodeLsDoiThuong()->loadMoneyLogsHistory(lstMoneyLogs);
}

void SceneTable::updateMoneyResponseHandler(){
	auto common = Common::getInstance();

	BINUpdateMoneyResponse *updatemoneyresponse =
		(BINUpdateMoneyResponse*)common->checkEvent(NetworkManager::UPDATE_MONEY);

	if (updatemoneyresponse != 0) {
		CCLOG("update money response: %s", updatemoneyresponse->DebugString().c_str());
		if (updatemoneyresponse->responsecode() && updatemoneyresponse->moneyboxes_size() > 0){

			BINMoneyBox moneyBox;
			
			long long origin_money;

			for (int i = 0; i < updatemoneyresponse->moneyboxes_size(); i++) {
				moneyBox = updatemoneyresponse->moneyboxes(i);

				if (moneyBox.userid() == Common::getInstance()->getUserId()){
                    bool isCash = moneyBox.iscash();
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

void SceneTable::initTitleTable(float posX, float posY){
    /*for(int i=0;i<6;i++){
        auto tabSprite = MSprite::create("btn_tabbutton.png");
        tabSprite->setScaleX((width-6*2)/(6*tabSprite->getWidth()));
        tabSprite->setContentSize(Size((width-6*2)/6,tabSprite->getHeight()));
        tabSprite->setPosition(Vec2(originX+2*(i+1)+i*(width-6*2)/6,originY +SCROLL_Y+SCROLL_HEIGHT-10));
        this->addChild(tabSprite);
    }*/
    
	
    
    /*tab = MSprite::createExtendsDown(TABLE_SPRITE_TABBUTTION,(width-6*2)/6);
    tab->setPosition(Vec2(originX+2,originY+SCROLL_Y+SCROLL_HEIGHT-10));
    this->addChild(tab);
    
    vector<std::string> nameTabButton = {"Phòng chờ","VIP XU","ken","Mức cược","Số người","Khóa"};
    vector<int> tagTabButton = {TAG_TABLE_BTN_PHONGCHO,TAG_TABLE_BTN_VIPXU,TAG_TABLE_BTN_KEN,TAG_TABLE_BTN_MUCCUOC,
        TAG_TABLE_BTN_SONGUOI,TAG_TABLE_BTN_KHOA};
    
    for(int i=0;i<6;i++){
        auto tabButton = MButton::create("btn_tabbutton_null.png",nameTabButton[i],30,tagTabButton[i]);
        tabButton->setScaleX((width-6*2)/(6*tabButton->getWidth()));
        tabButton->setContentSize(Size((width-6*2)/6,tabButton->getHeight()));
        tabButton->setPosition(Vec2(originX+2*(i+1)+i*(width-6*2)/6,originY+ SCROLL_Y+SCROLL_HEIGHT-10));
        tabButton->addTouchEventListener(CC_CALLBACK_2(SceneTable::phongCallBack, this));
        this->addChild(tabButton);
    }*/
	float width = bg_lst_table->getWidth();
	float height = hightTable / 6;
	float sizeText = height / 3;

	//so ban
	auto lb_soban = MLabel::create(TABLE_TXT_SOBAN, sizeText);
	lb_soban->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_soban->setPosition(Vec2(posX + width / 12, posY));
	this->addChild(lb_soban);

	//muc cuoc
	auto lb_muccuoc = MLabel::create(TABLE_TXT_MUCCUOC, sizeText);
	lb_muccuoc->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_muccuoc->setPosition(Vec2(posX + width / 6 + 3 * width / (8 * 6), posY));
	this->addChild(lb_muccuoc);

	btn_sort_muccuoc = MButton::create(TABLE_IC_SORT);
	btn_sort_muccuoc->setAnchorPoint(Point::ANCHOR_MIDDLE);
	btn_sort_muccuoc->setPosition(Vec2(posX + width / 6 + 3 * width / (4 * 6) + btn_sort_muccuoc->getWidth()/2, posY));
	btn_sort_muccuoc->setTag(TAG_SHOW_SORT_MUCCUOC);
	btn_sort_muccuoc->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
	this->addChild(btn_sort_muccuoc);

	//so nguoi choi
	auto lb_songuoichoi = MLabel::create(TABLE_TXT_SONGUOICHOI, sizeText);
	lb_songuoichoi->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_songuoichoi->setPosition(Vec2(posX + 3 * width / 6, posY));
	this->addChild(lb_songuoichoi);

	//sort songuoichoi
	btn_sort_songuoichoi = MButton::create(TABLE_IC_SORT);
	btn_sort_songuoichoi->setAnchorPoint(Point::ANCHOR_MIDDLE);
	btn_sort_songuoichoi->setPosition(Vec2(lb_songuoichoi->getPosition().x + lb_songuoichoi->getWidth()/2 
		+ btn_sort_songuoichoi->getWidth()/2 + 10, posY));
	btn_sort_songuoichoi->setTag(TAG_SHOW_SORT_NUMPLAYER);
	btn_sort_songuoichoi->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
	this->addChild(btn_sort_songuoichoi);

	//toi thieu
	auto lb_toithieu = MLabel::create(TABLE_TXT_TOITHIEU, sizeText);
	lb_toithieu->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_toithieu->setPosition(Vec2(posX + 4 * width / 6 + 3 * width / (8 * 6), posY));
	this->addChild(lb_toithieu);

	//sort toi thieu
	btn_sort_toithieu = MButton::create(TABLE_IC_SORT);
	btn_sort_toithieu->setAnchorPoint(Point::ANCHOR_MIDDLE);
	btn_sort_toithieu->setPosition(Vec2(posX + 4 * width / 6 + 3 * width / (4 * 6) + btn_sort_toithieu->getWidth() / 2, posY));
	btn_sort_toithieu->setTag(TAG_SHOW_SORT_TOITHIEU);
	btn_sort_toithieu->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
	this->addChild(btn_sort_toithieu);

	//trang thai
	auto lb_trangthai = MLabel::create(TABLE_TXT_TRANGTHAI, sizeText);
	lb_trangthai->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_trangthai->setPosition(Vec2(posX + 5 * width / 6 + width / (2 * 6), posY));
	this->addChild(lb_trangthai);

	//sort trangthai
	/*auto btn_sort_trangthai = MButton::create(TABLE_IC_SORT);
	btn_sort_trangthai->setAnchorPoint(Point::ANCHOR_MIDDLE);
	btn_sort_trangthai->setPosition(Vec2(posX + 5 * width / 6 + 3 * width / (4 * 6) + btn_sort_toithieu->getWidth() / 2, posY));
	this->addChild(btn_sort_trangthai);*/
}

void SceneTable::showPopupPassWord(int roomIndex){
    auto passWordPopup = (PasswordPopup*)this->getChildByTag(POPUP_TAG_PASSWORD);
	if (passWordPopup == nullptr){
        return;
    }
    passWordPopup->setRoomIndex(roomIndex);
    passWordPopup->appear();
}

void SceneTable::initMenu() {
    auto btnBack = MButton::create(TABLE_BTN_BACK,TAG_TABLE_BTN_BACK);
	btnBack->setPosition(MVec2(padding, visibleSize.height - btnBack->getHeight() - padding));
    btnBack->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btnPhone = MButton::create(TABLE_BTN_PHONE,TAG_TABLE_BTN_PHONE);
    btnPhone->setPosition(Vec2(btnBack->getPosition().x+btnBack->getWidth()+padding,
                                btnBack->getPosition().y));
    btnPhone->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btnCaiDat = MButton::create(TABLE_BTN_CAIDAT,TAG_TABLE_BTN_CAIDAT);
    btnCaiDat->setPosition(MVec2(visibleSize.width-btnCaiDat->getWidth()-padding,
                                   visibleSize.height-btnCaiDat->getHeight()-padding));
    btnCaiDat->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btnHopThu = MButton::create(TABLE_BTN_HOPTHU,TAG_TABLE_BTN_HOPTHU);
	btnHopThu->setPosition(Vec2(btnCaiDat->getPosition().x - btnHopThu->getWidth() - padding,
                                       btnCaiDat->getPosition().y));
    btnHopThu->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));

	sprite_new_mail = MSprite::create("bg_songuoixem.png");
	sprite_new_mail->setPosition(Vec2(btnHopThu->getWidth() - sprite_new_mail->getWidth(), btnHopThu->getHeight() - sprite_new_mail->getHeight()));
	btnHopThu->addChild(sprite_new_mail);

	label_number_new_mail = MLabel::create(Common::getInstance()->convertIntToString(totalNewMail), 25);
	label_number_new_mail->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label_number_new_mail->enableOutline(Color4B(201, 227, 29, 255), 2);
	label_number_new_mail->setPosition(Vec2(sprite_new_mail->getWidth() / 2
		, sprite_new_mail->getHeight() / 2));
	
	sprite_new_mail->addChild(label_number_new_mail);
	sprite_new_mail->setVisible(false);
    
    auto btnTien = MButton::create(TABLE_BTN_TIEN,TAG_TABLE_BTN_TIEN);
	btnTien->setPosition(Vec2(btnHopThu->getPosition().x - btnTien->getWidth() - padding,
                                btnHopThu->getPosition().y));
	btnTien->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    //==bottom bar under
	auto bar = MSprite::create(BGR_UNDERLINE);
	bar->setScale(width / bar->getWidth(), 1);
    bar->setPosition(MVec2(0,0));
    
    this->addChild(btnBack);
    this->addChild(btnCaiDat);
    this->addChild(btnHopThu);
    this->addChild(btnTien);
    this->addChild(btnPhone);
    
    {
		//bg avatar
		auto bk_avatar = MSprite::create(TABLE_BK_AVATAR);
		bk_avatar->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		bk_avatar->setPosition(Vec2(btnPhone->getPosition().x + btnPhone->getWidth() + padding,
		btnPhone->getPosition().y + btnPhone->getHeight()));
		this->addChild(bk_avatar);

		// avartar
		int avatar_id = Common::getInstance()->getAvatarId();
		auto btn_avatar = MButton::create(StringUtils::format("avatar%d.png", avatar_id), TAG_SHOW_BTN_AVATAR);
		btn_avatar->setAnchorPoint(Point::ANCHOR_MIDDLE);
		btn_avatar->setPosition(Vec2(bk_avatar->getPosition().x + bk_avatar->getWidth() / 2,
			bk_avatar->getPosition().y - bk_avatar->getHeight() / 2));
		btn_avatar->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btn_avatar);

		////info
		auto label_id = MLabel::create(StringUtils::format("ID: %d", Common::getInstance()->getUserId()), bk_avatar->getHeight() / 5);
		label_id->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		label_id->setPosition(Vec2(btn_avatar->getPosition().x + btn_avatar->getWidth() / 2 + padding, btn_avatar->getPosition().y));
		this->addChild(label_id);

		////ten hien thi
		auto label_name = MLabel::create(Common::getInstance()->getUserName(), 1.2 * bk_avatar->getHeight() / 5);
		label_name->setPosition(Vec2(btn_avatar->getPosition().x + btn_avatar->getWidth() / 2 + padding,
			btnPhone->getPosition().y + btnPhone->getHeight() / 2));
		this->addChild(label_name);

		float widthName = label_name->getWidth() > label_id->getWidth() ? label_name->getWidth() : label_id->getWidth();

		float widthXuKen = btnTien->getPosition().x - (label_name->getPosition().x +
			widthName + 3 * padding);

		auto common = Common::getInstance();
		////ken
		auto _bgr_ken = MSprite::create(SPRITE_BK_XUKEN); //TABLE_SPRITE_KEN
		_bgr_ken->setScaleX((widthXuKen / 2) / (_bgr_ken->getWidth()));
		_bgr_ken->setContentSize(Size(widthXuKen / 2, _bgr_ken->getHeight()));
		_bgr_ken->setPosition(Vec2(btnTien->getPosition().x - _bgr_ken->getWidth() - padding,
			btnTien->getPosition().y + btnTien->getHeight() / 2 - _bgr_ken->getHeight() / 2));
		this->addChild(_bgr_ken);

		auto sprite_ken = MSprite::create(TABLE_SPRITE_KEN);
		sprite_ken->setPosition(Vec2(_bgr_ken->getPosition().x + 5,
			_bgr_ken->getPosition().y + _bgr_ken->getHeight() / 2 - sprite_ken->getHeight() / 2));
		this->addChild(sprite_ken);

		label_ken = MLabel::create(common->numberFormatWithCommas(common->getGold()), _bgr_ken->getHeight()*0.4f);
		label_ken->setPosition(_bgr_ken->getPosition().x + _bgr_ken->getWidth() - label_ken->getWidth() - 5,
			_bgr_ken->getPosition().y + _bgr_ken->getHeight() / 2 - label_ken->getHeight() / 2);
		label_ken->setColor(Color3B(255, 255, 0));
		this->addChild(label_ken);

		////xu
		auto _bgr_xu = MSprite::create(SPRITE_BK_XUKEN); //SPRITE_XU
		_bgr_xu->setScaleX((widthXuKen / 2) / (_bgr_xu->getWidth()));
		_bgr_xu->setContentSize(Size(widthXuKen / 2, _bgr_xu->getHeight()));
		_bgr_xu->setPosition(Vec2(_bgr_ken->getPosition().x - padding - _bgr_xu->getWidth(),
			btnTien->getPosition().y + btnTien->getHeight() / 2 - _bgr_ken->getHeight() / 2));
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

		std::string img_title_room_play = ICON_TITLE_ROOM_PLAY_TLMN;

		int zoneId = common->getZoneId();

		if (zoneId == Common::TIENLENMIENNAM_ZONE){
			img_title_room_play = ICON_TITLE_ROOM_PLAY_TLMN;
		}
		else if (zoneId == Common::PHOM_ZONE){
			img_title_room_play = ICON_TITLE_ROOM_PLAY_PHOM;
		}
		else if (zoneId == Common::BACAY_ZONE){
			img_title_room_play = ICON_TITLE_ROOM_PLAY_BACAY;
        }
		else if (zoneId == Common::MAUBINH_ZONE) {
            img_title_room_play = ICON_TITLE_ROOM_PLAY_MAUBINH;
        }
		else if (zoneId == Common::XOCDIA_ZONE) {
            img_title_room_play = ICON_TITLE_ROOM_PLAY_XOCDIA;
        }

		auto txt_game_name = MSprite::create(img_title_room_play);
		txt_game_name->setPosition(Vec2(origin.x + width / 2 - txt_game_name->getWidth() / 2,
			_bgr_xu->getPosition().y - txt_game_name->getHeight() - 12));
		this->addChild(txt_game_name);

		auto sprite_sao_trai = MSprite::create(TABLE_IC_SAO);
		sprite_sao_trai->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		sprite_sao_trai->setPosition(Vec2(origin.x + width / 2 - txt_game_name->getWidth() / 2 - padding,
			_bgr_xu->getPosition().y - txt_game_name->getHeight() / 2 - 12));
		this->addChild(sprite_sao_trai);

		auto sprite_sao_phai = MSprite::create(TABLE_IC_SAO);
        sprite_sao_phai->setFlippedX(true);
		sprite_sao_phai->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		sprite_sao_phai->setPosition(Vec2(origin.x + width / 2 + txt_game_name->getWidth() / 2 + padding + sprite_sao_phai->getWidth(),
			_bgr_xu->getPosition().y - txt_game_name->getHeight() / 2 - padding));

		this->addChild(sprite_sao_phai);

		//ban choi
		int scrollHeight = txt_game_name->getPosition().y - originY - bar->getHeight() - 12;
		float scrollY = bar->getHeight() - 5;
		scrollBkg = MSprite::create(TABLE_BG_PHONGCHO);
		scrollBkg->setScaleX((width - 30) / scrollBkg->getWidth());
		scrollBkg->setScaleY(scrollHeight / scrollBkg->getHeight());
		scrollBkg->setContentSize(Size(width - 30, scrollHeight));
		scrollBkg->setPosition(MVec2(15, scrollY));
		this->addChild(scrollBkg);

		bg_lst_table = MSprite::create(TABLE_BG_LST_TABLE);
		bg_lst_table->setScaleX((width - 40) / bg_lst_table->getWidth());
		bg_lst_table->setScaleY((scrollHeight - 8) / bg_lst_table->getHeight());
		bg_lst_table->setContentSize(Size(width - 40, scrollHeight - 8));
		bg_lst_table->setPosition(MVec2(15 + (scrollBkg->getWidth() - bg_lst_table->getWidth()) / 2, scrollY));
		this->addChild(bg_lst_table);

		hightTable = bg_lst_table->getHeight() - 0.76 * bg_lst_table->getHeight() / 6;

		tableView = TableView::create(this, Size(bg_lst_table->getWidth(), hightTable));
		tableView->setDirection(TableView::Direction::VERTICAL);
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDelegate(this);
		tableView->setBounceable(true);
		tableView->setPosition(MVec2(15 + (scrollBkg->getWidth() - bg_lst_table->getWidth()) / 2, scrollY));
		this->addChild(tableView);
        
        /*auto selected = MSprite::create("cell", Size(bg_lst_table->getWidth(), hightTable / 6));
        selected->setPosition(Vec2(0,tableView->getContentSize().height - hightTable / 6));
        tableView->addChild(selected);*/
		//tableView->reloadData();

		initTitleTable(originX + 15 + (scrollBkg->getWidth() - bg_lst_table->getWidth()) / 2, 
			bg_lst_table->getPosition().y + bg_lst_table->getHeight() - 0.76 * bg_lst_table->getHeight() / 12);

		//bar
		this->addChild(bar);

		// choi ngay
		auto btnChoiNgay = MButton::createExtends(ICON_CHOINGAY, "", 30, TAG_TABLE_BTN_PLAYNOW);
		btnChoiNgay->setPosition(MVec2(width / 2 - btnChoiNgay->getWidth() / 2, 0));
		btnChoiNgay->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btnChoiNgay);

		// ken
		auto btn_ken = MButton::createExtendsBottom(TABLE_BTN_MENU_KEN, "KEN", 30, TAG_TABLE_BTN_KEN);

		auto labelTmp = Label::createWithTTF("Tmp", "fonts/gamevina.otf", btn_ken->getHeight() / 2.0f);
		float height = labelTmp->getContentSize().height + 5 + btn_ken->getHeight();

		btn_ken->setPosition(MVec2(width * 5 / 8, bar->getHeight() / 2 - height / 2 + (labelTmp->getContentSize().height + 5)));
		btn_ken->addTouchEventListener(CC_CALLBACK_2(SceneTable::phongCallBack, this));
		this->addChild(btn_ken);

		// cuoc ban
		auto btn_cuocban = MButton::createExtendsBottom(TABLE_BTN_MENU_CUOCBAN, "Cược bàn", 30, TAG_TABLE_BTN_MUCCUOC);
		btn_cuocban->setPosition(Vec2(originX + width * 6 / 8, btn_ken->getPosition().y));
		btn_cuocban->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btn_cuocban);

		// tao ban
		auto btn_taoban = MButton::createExtendsBottom(TABLE_BTN_MENU_TAOBAN, "Tạo bàn", 30, TAG_TABLE_BTN_CREATE);
		btn_taoban->setPosition(Vec2(originX + width * 7 / 8, btn_ken->getPosition().y));
		btn_taoban->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btn_taoban);

		//xu
		auto btn_xu = MButton::createExtendsBottom(TABLE_BTN_MENU_XU, "XU", 30, TAG_TABLE_BTN_VIPXU);
		btn_xu->setPosition(Vec2(originX + width * 3 / 8 - btn_xu->getWidth(), btn_ken->getPosition().y));
		btn_xu->addTouchEventListener(CC_CALLBACK_2(SceneTable::phongCallBack, this));
		this->addChild(btn_xu);

		//lam moi
		auto btn_refresh = MButton::createExtendsBottom(TABLE_BTN_MENU_REFRESH, "Làm mới", 30, TAG_SHOW_BTN_REFRESH);
		btn_refresh->setPosition(Vec2(originX + width * 2 / 8 - btn_refresh->getWidth(), btn_ken->getPosition().y));
		btn_refresh->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btn_refresh);

		// luat choi
		auto btn_luatchoi = MButton::createExtendsBottom(ICON_HELP, "Luật chơi", 30, TAG_SHOW_BTN_TROGIUP);
		btn_luatchoi->setPosition(Vec2(originX + width * 1 / 8 - btn_luatchoi->getWidth(), btn_ken->getPosition().y));
		btn_luatchoi->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
		this->addChild(btn_luatchoi);
    }
}


void SceneTable::tableCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        //xxxxx
    }
}

//mail
void SceneTable::loadEmail(vector<Mail> lstEmail){
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

void SceneTable::showNumberNewMail(){
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

void SceneTable::readMail(Mail mail){
	showNumberNewMail();
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeHopThu()->readMail(mail);
    }
}

void SceneTable::deleteMail(vector<long> lstMailId){
	showNumberNewMail();
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeHopThu()->deleteMail(lstMailId);
    }
}
//end mail

//user info
void SceneTable::viewUserInfo(BINViewUserInfoResponse *viewUserInfo){
    auto m_popupUserInfo = (PopupUserInfo*)this->getChildByTag(POPUP_TAG_USERINFOR);
	if (m_popupUserInfo != nullptr){
        m_popupUserInfo->getNodeHoSo()->viewUserInfo(viewUserInfo->userinfo());
    }
}
//end

void SceneTable::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();

        switch (tag) {
            case TAG_TABLE_BTN_BACK:
                CCLOG("%s","Button Back");
                {
                    NetworkManager::getInstance()->getExitZoneMessageFromServer(
                        Common::getInstance()->getZoneId());
                }
                break;
            case TAG_TABLE_BTN_CREATE:
                CCLOG("%s","Button create");
                
                if(this->getChildByTag(POPUP_TAG_CREATEROOM) == nullptr){
                    auto m_popupCreateRoom = PopupCreateRoom::create();
                    m_popupCreateRoom->setTag(POPUP_TAG_CREATEROOM);
                    addChild(m_popupCreateRoom, INDEX_POPUP);
                    m_popupCreateRoom->appear();
                }
                
                break;
			case TAG_SHOW_BTN_AVATAR:
                
                if(this->getChildByTag(POPUP_TAG_USERINFOR) == nullptr){
                    auto m_popupUserInfo = PopupUserInfo::create();
                    m_popupUserInfo->setTag(POPUP_TAG_USERINFOR);
                    m_popupUserInfo->showPositionTab(1);
					addChild(m_popupUserInfo, INDEX_POPUP);
                    m_popupUserInfo->appear();
                }
				break;
            case TAG_TABLE_BTN_GOTO:
                CCLOG("%s","Button GoTo");
                break;
			case TAG_TABLE_BTN_HOPTHU:
                if(this->getChildByTag(POPUP_TAG_USERINFOR) == nullptr){
                    auto m_popupUserInfo = PopupUserInfo::create();
                    m_popupUserInfo->setTag(POPUP_TAG_USERINFOR);
                    m_popupUserInfo->showPositionTab(2);
					addChild(m_popupUserInfo, INDEX_POPUP);
                    m_popupUserInfo->appear();
                }
				
				break;
			case TAG_TABLE_BTN_PLAYNOW:
			{
				CCLOG("%s", "Button Play Now");
				NetworkManager::getInstance()->getEnterRoomGroupFromServer(-1, is_vip_room);
			}
                break;
			case TAG_SHOW_BTN_REFRESH:
				{
					CCLOG("%s", "Button Refresh");
					listRoomPlay.clear();
					NetworkManager::getInstance()->
						getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
						is_vip_room, -1, -1, orderByField, true);
				}
                break;
			case TAG_TABLE_BTN_CAIDAT:
				// POPUP SETTING
				if (this->getChildByTag(POPUP_TAG_SETTING) == nullptr){
					auto m_popupSetting = PopupSetting::create();
					m_popupSetting->setTag(POPUP_TAG_SETTING);
					addChild(m_popupSetting, INDEX_POPUP);
					m_popupSetting->appear();
				}
				break;
			case TAG_TABLE_BTN_TIEN:
				if (Common::getInstance()->isEnabledPurchaseCash()) {
					NetworkManager::getInstance()->getCaptchaMessageFromServer(true);
				}
				else {
					this->showToast(MSG_MAINTAIN, 2);
				}
				break;
			case TAG_SHOW_SORT_NUMPLAYER:
				listRoomPlay.clear();
				orderByField = TABLE_ORDERBY::NUM_PLAYER;
				btn_sort_songuoichoi->setRotation(-180);
				btn_sort_toithieu->setRotation(0);
				btn_sort_muccuoc->setRotation(0);
				NetworkManager::getInstance()->
					getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
					is_vip_room, -1, -1, orderByField, true);
				break;
			case TAG_SHOW_SORT_MUCCUOC:
				listRoomPlay.clear();
				orderByField = TABLE_ORDERBY::MIN_BET;
				btn_sort_songuoichoi->setRotation(0);
				btn_sort_toithieu->setRotation(0);
				btn_sort_muccuoc->setRotation(-180);
				NetworkManager::getInstance()->
					getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
					is_vip_room, -1, -1, orderByField, true);
				break;
			case TAG_SHOW_SORT_TOITHIEU:
				/*listRoomPlay.clear();
				orderByField = TABLE_ORDERBY::;
				NetworkManager::getInstance()->
					getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
					is_vip_room, -1, -1, orderByField, true);*/
				break;
			case TAG_TABLE_BTN_PHONE:
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

void SceneTable::loadTabButton(float x,bool zone){
    tab->setPosition(Vec2(originX + x,tab->getPosition().y));
    listRoomPlay.clear();
    CCLOG("is vip room: %s", zone ? "true" : "false");
    NetworkManager::getInstance()->
    getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
		zone, -1, -1, orderByField, true);
}

void SceneTable::phongCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_TABLE_BTN_PHONGCHO:
                is_vip_room = false;
                loadTabButton(2+0*(width-6*2)/6,false);
                break;
            case TAG_TABLE_BTN_VIPXU:
				listRoomPlay.clear();
                is_vip_room = true;
				scrollBkg->setTexture(TABLE_BG_PHONGVIP);
				NetworkManager::getInstance()->
					getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
					true, -1, -1, orderByField, true);
                break;
            case TAG_TABLE_BTN_KEN:
				listRoomPlay.clear();
                is_vip_room = false;
				scrollBkg->setTexture(TABLE_BG_PHONGFREE);
				NetworkManager::getInstance()->
					getFilterRoomMessageFromServer(Common::getInstance()->getZoneId(),
					false, -1, -1, orderByField, true);
                break;
            case TAG_TABLE_BTN_MUCCUOC:
                is_vip_room = false;
                loadTabButton(2*4+3*(width-6*2)/6,false);
                break;
            case TAG_TABLE_BTN_SONGUOI:
                is_vip_room = false;
                loadTabButton(2*5+4*(width-6*2)/6,false);
                break;
            case TAG_TABLE_BTN_KHOA:
                is_vip_room = false;
                loadTabButton(2*6+5*(width-6*2)/6,false);
                break;
            default:
                break;
        }
    }
}

//========================= TableView

void SceneTable :: tableCellHighlight (TableView * table, TableViewCell * cell){
    MSprite * pSprite = (MSprite *) cell-> getChildByTag (789);
    pSprite->setTexture("sprite_cell_content_table_selected.png");
    pSprite->setScale(bg_lst_table->getWidth()/pSprite->getWidth(),hightTable/(6*pSprite->getHeight()));
}

//when we move away from the cell and unhighlight it.This also I haven't used because I just want some buttons to be added and scrolled up and down.
void SceneTable :: tableCellUnhighlight (TableView * table,TableViewCell * cell){
    MSprite * pSprite = (MSprite *) cell-> getChildByTag (789);
    pSprite->setTexture(TABLE_BG_CONTENT_CELL);
    pSprite->setScale(bg_lst_table->getWidth()/pSprite->getWidth(),hightTable/(6*pSprite->getHeight()));
}

void SceneTable::tableItemCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        CCLOG("tag: %d",tag-1000);
        //NetworkManager::getInstance()->getEnterRoomMessageFromServer(listRoomPlay[tag-1000].roomindex(), "");
        //roomIndex1 = listRoomPlay[tag].roomindex();
    }
}

Size SceneTable::cellSizeForTable(TableView *table) {
	return Size(bg_lst_table->getWidth(), hightTable / 6);
}

ssize_t SceneTable::numberOfCellsInTableView(TableView *table) {
    //return listRoomPlay.size() < 6 ? 6 : listRoomPlay.size();
	return listRoomPlay.size();
}

void SceneTable::tableCellTouched(TableView *table, TableViewCell *cell) {
	int index = (int)cell->getIdx();
	int roomIndex = (int)listRoomPlay[index].roomindex();
	if (listRoomPlay[index].passwordrequired()){
		this->showPopupPassWord(roomIndex);
	} else {
		NetworkManager::getInstance()->getEnterRoomMessageFromServer(roomIndex, "");
	}
}

TableViewCell* SceneTable::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    
    // new cell created
	auto bg = MSprite::create(TABLE_BG_CONTENT_CELL, Size(bg_lst_table->getWidth(), hightTable / 6));
    bg->setTag(789);
    cell->addChild(bg);
    
	auto itemCell = ItemCell::create(listRoomPlay[idx].roomindex(), listRoomPlay[idx].passwordrequired(), 
		bg_lst_table->getWidth(), hightTable / 6, listRoomPlay[idx].minbet(), 
		listRoomPlay[idx].enteringplayer(), listRoomPlay[idx].viproom(), listRoomPlay[idx].playersize(), listRoomPlay[idx].minentermoney());

	itemCell->setAnchorPoint(Vec2(0, 0));
	/*itemCell->setPosition(Vec2((2 * i + 1)*width / 8 - scrollBkg->getHeight() / 6,
		scrollBkg->getHeight() / 12 - itemCell->getContentSize().height / 2));*/
	itemCell->setContentSize(Size(bg_lst_table->getWidth(), bg->getHeight()));
	cell->addChild(itemCell);

    /*int sizeItem = (listRoomPlay.size() - idx*4 < 4) ? (int)listRoomPlay.size() - (int)idx*4 : 4;

    for(int i=0;i< sizeItem ;i++){
        char buffer[50];
        sprintf(buffer, "%d xu", listRoomPlay[4*idx+i].minbet());
        int roomIndex = listRoomPlay[4*idx+i].roomindex();
        auto itemCell = ItemCell::create(roomIndex, listRoomPlay[4 * idx + i].passwordrequired(), scrollBkg->getHeight() / 3, buffer,
                                         listRoomPlay[4 * idx + i].enteringplayer(), this);
        
        itemCell->setAnchorPoint(Vec2(0,0));
        itemCell->setPosition(Vec2((2*i+1)*width/8 - scrollBkg->getHeight()/6,
                                   scrollBkg->getHeight() / 12-itemCell->getContentSize().height/2));
        itemCell->setContentSize(Size(scrollBkg->getHeight()/3,scrollBkg->getHeight()/6));
        cell->addChild(itemCell);
    }*/
    return cell;
}

void SceneTable::onExit() {
    BaseScene::onExit();
};

void SceneTable::instantMessageResponseHandle() {
    BINInstantMessageResponse* response =
    (BINInstantMessageResponse*)Common::getInstance()->checkEvent(NetworkManager::INSTANT_MESSAGE);
    if (response != 0){
        CCLOG("filter room response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            if (response->has_scope() && response->scope() == 1) {
                if (response->has_zoneid() &&
                    response->zoneid() == Common::getInstance()->getZoneId()) {
                    /*
                     xu ly hien thi message trong khung chat
                     */
                    std::string username =
                    response->has_senderusername() ? response->senderusername() : "eo biet thang nao gui";
                    std::string message = response->has_instantmessage() ? response->instantmessage() : "eo biet no gui cai gi";
                    long long int time = response->has_senttime() ? response->senttime() : 0;
                    CCLOG("luc %lld thang %s gui tin nhan: %s", time, username.c_str(), message.c_str());
                }
            }
        }
    }
}

void SceneTable::setEnableDisplayRoomList(bool enable) {
    enableDisplayRoomList = enable;
}

bool SceneTable::getEnableDisplayRoomList() {
    return enableDisplayRoomList;
}

void SceneTable::exitZoneResponseHandler() {
    BINExitZoneResponse* response = (BINExitZoneResponse *)Common::getInstance()
        ->checkEvent(NetworkManager::EXIT_ZONE);
    if (response != 0) {
        CCLOG("exit zone response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
			Common::getInstance()->setZoneId(-1);
			this->unscheduleUpdate();
            auto scene = ShowGame::createScene();
            REPLACESCENE(0.15f, scene);
        }
    }
}

#include "PlayScene.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "LoginScene.h"
#include "Utils/Common.h"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/SoundManager.h"
#include "Utils/AnimationManager.hpp"
#include "SceneTable.hpp"
#include "Popups/PopupSetting.hpp"
#include "Popups/PopupDoiThe.hpp"
#include <cmath>

#define padding 10

using namespace cocos2d;
using namespace std;

//implement
bool PlayScene::init() {
    if (!BaseScene::init()) {
        return false;
    }
    
    //initMenu();

    this->scheduleUpdate();

    return true;
}

void PlayScene::onExit() {
    BaseScene::onExit();
}

void PlayScene::levelResponseHandler() {
    BINLevelUpResponse *response = (BINLevelUpResponse *)Common::getInstance()
        ->checkEvent(NetworkManager::LEVEL_UP); 
    if (response != 0) {
        CCLOG("level up response: %s", response->DebugString().c_str()); 
        if (response->responsecode()) {
            
        } else {
            this->showToast(response->message().c_str(), 2.0f);
        }
    }
}

void PlayScene::medalResonseHandler() {
    BINMedalUpResponse *response = (BINMedalUpResponse *)Common::getInstance()
        ->checkEvent(NetworkManager::MEDAL_UP);
    if (response != 0) {
        CCLOG("medal up response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
        }
        else {
            this->showToast(response->message().c_str(), 2.0f);
        }
    }
}

void PlayScene::update(float delta) {
    BaseScene::update(delta);
    /*
    chat
    */
    chatResponseHandler();

    levelResponseHandler();

    medalResonseHandler();
    //lock phong
    lockRoomResponseHandler();

    exitRoomResponseHandler(); 

	//user info
	viewUserInfoFromServer();
    
    textEmoticonResponseHandler();

	//message chap nhan loi moi vao phong
	replyToInviteResponse();

	//message nap the
	getCapchaMessageResponse();
}

void PlayScene::getCapchaMessageResponse(){
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

void PlayScene::replyToInviteResponse(){
	BINRelyInvitationResponse *response = (BINRelyInvitationResponse*)Common::getInstance()->checkEvent(NetworkManager::RELY_INVITE);
	if (response != 0){
		CCLOG("reply to invite response: %s", response->DebugString().c_str());
		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
	}
}

void PlayScene::viewUserInfo(BINViewUserInfoResponse *viewUserInfo){
	if (this->getChildByTag(TAG_NODE_CONTACT_USER) == nullptr){
		_eventDispatcher->pauseEventListenersForTarget(this, true);

		NodeContactUser* contactUser = NodeContactUser::create();
		contactUser->viewUserInfo(viewUserInfo);
		contactUser->setTag(TAG_NODE_CONTACT_USER);
		contactUser->setPosition(MVec2(0, 0));
		this->addChild(contactUser,INDEX_POPUP);
	}
}

void PlayScene::setDisplayRoomList(bool _isDisplayRoomList) {
    this->_displayRoomList = _isDisplayRoomList;
}

bool PlayScene::isDisplayRoomList() const {
    return this->_displayRoomList;
}

//hien thi lai lock room cho ownerUserId moi
void PlayScene::displayLockRoomForOwner(int ownerUserId){
	auto common = Common::getInstance();
	if (common->getUserId() == ownerUserId){
		if (!this->btnKhoa->isVisible()) {
			this->btnKhoa->setVisible(true);
			if (!this->passwordRequired){
				this->btnKhoa->loadTextureNormal("btn_khoa.png");
			}
			else {
				this->btnKhoa->loadTextureNormal("btn_mokhoa.png");
			}
			lb_title_game->runAction(MoveTo::create(0.2f, Vec2(lb_title_game->getPositionX() + padding + btnKhoa->getWidth()
				, lb_title_game->getPositionY())));
			lb_title_minbet->runAction(MoveTo::create(0.2f, Vec2(lb_title_minbet->getPositionX() + padding + btnKhoa->getWidth()
				, lb_title_minbet->getPositionY())));
			lb_value_minbet->runAction(MoveTo::create(0.2f, Vec2(lb_value_minbet->getPositionX() + padding + btnKhoa->getWidth()
				, lb_value_minbet->getPositionY())));
		}
	}
	else {
		if (this->btnKhoa->isVisible()){
			this->btnKhoa->setVisible(false);
			lb_title_game->runAction(MoveTo::create(0.2f, Vec2(lb_title_game->getPositionX() - padding - btnKhoa->getWidth()
				, lb_title_game->getPositionY())));
			lb_title_minbet->runAction(MoveTo::create(0.2f, Vec2(lb_title_minbet->getPositionX() - padding - btnKhoa->getWidth()
				, lb_title_minbet->getPositionY())));
			lb_value_minbet->runAction(MoveTo::create(0.2f, Vec2(lb_value_minbet->getPositionX() - padding - btnKhoa->getWidth()
				, lb_value_minbet->getPositionY())));
		}
	}
}

void PlayScene::exitRoomResponseHandler() {
    BINExitRoomResponse* exit_room_response =
        (BINExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::EXIT_ROOM);
    if (exit_room_response != 0) {
        CCLOG("exit room response: %s", exit_room_response->DebugString().c_str());
        if (exit_room_response->responsecode() && exit_room_response->has_exitaftermatchend()) {
            if (!exit_room_response->exitaftermatchend()) {
                enter_room_response = 0; //xoa bien luu trang thai dang choi khi nguoi choi join lai ban choi
                auto showtable = SceneTable::createScene(isDisplayRoomList());
                REPLACESCENE(0.1f, showtable);
            }
        }
        else {
            this->showToast(exit_room_response->message().c_str(), 2);
        }
    }
}

//hien thi nut moi choi (neu so luong nguoi choi numPlaying >= capacity_size thi an nut moi choi di)
void PlayScene::showInvitePlayer(int numPlaying){
	btnInvitePlay->setVisible(numPlaying < capacity_size);
}

void PlayScene::setRoomIndex(int roomIndex){
    this->roomIndex = roomIndex;
}

int PlayScene::getRoomIndex() const {
    return this->roomIndex;
}

void PlayScene::setPassWordRequired(bool passwordRequired){
    this->passwordRequired = passwordRequired;
}

bool PlayScene::getPassWordRequired() const {
    return this->passwordRequired;
}

void PlayScene::setPlayerList(vector<BINPlayer> player_list){
    this->player_list = player_list;
}

vector<BINPlayer> PlayScene::getPlayerList(){
    return this->player_list;
}

void PlayScene::setWaitingPlayerList(vector<BINPlayer> waiting_player_list){
    this->waiting_player_list = waiting_player_list;
}

vector<BINPlayer> PlayScene::getWaitingPlayerList(){
    return this->waiting_player_list;
}

void PlayScene::setEnterRoomResponse(BINEnterRoomResponse* reEnterRoomResponse){
    this->enter_room_response = reEnterRoomResponse;
}

BINEnterRoomResponse* PlayScene::getEnterRoomResponse(){
    return this->enter_room_response;
}

void PlayScene::setCreateRoom(bool is_create_room){
    this->is_create_room = is_create_room;
}

bool PlayScene::isCreateRoom(){
    return this->is_create_room;
}

void PlayScene::setVipRoom(bool is_vip_room){
	this->is_vip_room = is_vip_room;
}

bool PlayScene::isVipRoom(){
	return this->is_vip_room;
}

void PlayScene::runAnimation(const char *format, int count,Vec2 posTarget,int times) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> frames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        frames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/10);
    //auto repeat =  RepeatForever::create(Animate::create(animation));
    auto repeat = Repeat::create(Animate::create(animation), 2);
    
    auto spriteAnim = Sprite::createWithSpriteFrame(frames.front());
    spriteAnim->setPosition(posTarget);
    spriteAnim->runAction(Sequence::create(repeat,RemoveSelf::create(), NULL));
    if(spriteAnim->getParent() == NULL){
        this->addChild(spriteAnim,INDEX_ANIMATION);
    }
}

Vector<SpriteFrame*> PlayScene::getFrameAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void PlayScene::initMenu(){

    auto bkg = MSprite::create("item_background.png");

    int rows = width / bkg->getWidth() + 1;
    int cols = height / bkg->getHeight() + 1;
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            auto itemBackground = MSprite::create("item_background.png");
            itemBackground->setPosition(MVec2(i*itemBackground->getWidth(),
                j*itemBackground->getHeight()));
            this->addChild(itemBackground);
        }
    }

    auto btnBack = MButton::create("btn_back_tlmn.png", TAG_TLMN_BTN_BACK);
    btnBack->setPosition(MVec2(padding, height - padding - btnBack->getHeight()));
    btnBack->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));
    
	btnInvitePlay = MButton::create("popup_moichoi/btn_moichoi.png", TAG_BTN_INVITE_TO_PLAY);
	btnInvitePlay->setPosition(Vec2(btnBack->getPosition().x, btnBack->getPosition().y - padding - btnInvitePlay->getHeight()));
	btnInvitePlay->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    string icon_lock = passwordRequired ? "btn_mokhoa.png" : "btn_khoa.png";

    btnKhoa = MButton::create(icon_lock, TAG_TLMN_BTN_KHOA);
    btnKhoa->setPosition(Vec2(btnBack->getPosition().x + btnBack->getWidth() + padding, btnBack->getPosition().y));
    btnKhoa->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));
    btnKhoa->setVisible(is_create_room);

	std::string title_game = Common::getInstance()->getTitleGame();
	
	lb_title_game = MLabel::create(title_game, btnKhoa->getHeight() * 0.35f, Color3B(5, 111, 156));
	lb_title_game->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	float posx_titlegame = is_create_room ? (btnKhoa->getPosition().x + btnKhoa->getWidth() + padding) : 
		(btnBack->getPosition().x + btnBack->getWidth() + padding);
	lb_title_game->setPosition(Vec2(posx_titlegame, originY + height - padding));
	this->addChild(lb_title_game);

	lb_title_minbet = MLabel::create(TABLE_TXT_MUCCUOC, btnKhoa->getHeight() * 0.25f, Color3B(5, 111, 156));
	lb_title_minbet->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	lb_title_minbet->setPosition(Vec2(lb_title_game->getPosition().x, lb_title_game->getPosition().y - lb_title_game->getHeight() - 2));
	this->addChild(lb_title_minbet);

	std::string value_minbet = Common::getInstance()->numberFormatWithCommas(minBet);
	std::string minbet_type = is_vip_room ? "XU" : "KEN";
	
	lb_value_minbet = MLabel::create(value_minbet + " " + minbet_type, btnKhoa->getHeight() * 0.25f, Color3B::WHITE);
	lb_value_minbet->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	lb_value_minbet->setPosition(Vec2(lb_title_minbet->getPosition().x + lb_title_minbet->getWidth() + 2, lb_title_minbet->getPosition().y));
	this->addChild(lb_value_minbet);

    btn_caidat = MButton::create("btn_caidat.png", TAG_TLMN_BTN_CAIDAT);
    btn_caidat->setPosition(MVec2(width - padding - btn_caidat->getContentSize().width,
        height - btn_caidat->getContentSize().height - padding));
    btn_caidat->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    auto btn_menu = MButton::create(BTN_MENU, TAG_TLMN_BTN_MENU);
    btn_menu->setPosition(Vec2(origin.x + padding, origin.y + visibleSize.height - btn_menu->getHeight() - padding));
    btn_menu->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    btn_message = MButton::create(BTN_MESSAGE, TAG_TLMN_BTN_MESSAGE);
    btn_message->setPosition(MVec2(width - btn_message->getWidth() - padding, padding));
    btn_message->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    auto btn_purcharse = MButton::create(BTN_PURCHASE, TAG_TLMN_BTN_PURCHASE);
    btn_purcharse->setPosition(Vec2(btn_caidat->getPosition().x - padding - btn_purcharse->getContentSize().width,
        btn_caidat->getPosition().y));
    btn_purcharse->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    //icon facebook
    auto btn_facebook = MButton::create(BTN_FACEBOOK, TAG_TLMN_BTN_FACEBOOK);
    btn_facebook->setPosition(Vec2(btn_purcharse->getPosition().x - padding - btn_facebook->getWidth(),
        btn_purcharse->getPosition().y));
    btn_facebook->addTouchEventListener(CC_CALLBACK_2(PlayScene::menuCallBack, this));

    this->addChild(btnBack);
    this->addChild(btnKhoa);
	this->addChild(btnInvitePlay);
    this->addChild(btn_message);
    this->addChild(btn_purcharse);
    this->addChild(btn_caidat);
    //this->addChild(btn_facebook);
}

void PlayScene::setMinBet(int minBet){
	this->minBet = minBet;
}

int PlayScene::getMinBet(){
	return this->minBet;
}

//an cac nut moi choi va chat doi voi nguoi cho
void PlayScene::showBtnWithWatingPlayer(bool isShow){
	btnInvitePlay->setVisible(isShow);
	btn_message->setVisible(isShow);
}

void PlayScene::menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType){
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*)pSender)->getTag();
        switch (tag) {
        case TAG_TLMN_BTN_BACK:
            CCLOG("%s", "m_popupTLMN");
            {
                //m_popupTLMN->appear();
				if (!check_exit_room) {
					NetworkManager::getInstance()->getExitRoomMessageFromServer(roomIndex);
				}
				else {
					NetworkManager::getInstance()->getCancelExitRoomMessageFromServer(roomIndex);
				}
				check_exit_room = !check_exit_room;
            }
            break;
        case TAG_TLMN_BTN_MESSAGE:
                
            if(this->getChildByTag(POPUP_TAG_CHAT) == nullptr){
                auto m_popupChat = PopupChat::createPopup(ScopeChat::CHAT_ROOM);
                m_popupChat->setTag(POPUP_TAG_CHAT);
                addChild(m_popupChat,INDEX_POPUP);
                m_popupChat->appear();
            }
            break;
		case TAG_BTN_INVITE_TO_PLAY:
                if(this->getChildByTag(POPUP_TAG_INVITE) == nullptr){
                    auto m_popupInviteToPlay = PopupInviteToPlay::create();
                    m_popupInviteToPlay->setTag(POPUP_TAG_INVITE);
                    m_popupInviteToPlay->setVipRoom(is_vip_room);
                    m_popupInviteToPlay->setRoomIndex(roomIndex);
                    addChild(m_popupInviteToPlay, INDEX_POPUP);
                    
                    m_popupInviteToPlay->getLookupUserToInviteFromServer();
                    m_popupInviteToPlay->appear();
                }
			
			break;
        case TAG_TLMN_BTN_KHOA:
        {
            if (passwordRequired){
                //popup_lock->setLock(false);
                NetworkManager::getInstance()->getLockRoom(roomIndex, false);
            }
            else{
                if(this->getChildByTag(POPUP_TAG_LOCKTABLE) == nullptr){
                    auto popup_lock = PopupLockTable::create();
                    popup_lock->setTag(POPUP_TAG_LOCKTABLE);
                    this->addChild(popup_lock, INDEX_POPUP);
                    popup_lock->appear();
                }
                
            }
        }
            break;
        case TAG_TLMN_BTN_PURCHASE:
            CCLOG("%s", "purchase");
			if (Common::getInstance()->isEnabledPurchaseCash()) {
				NetworkManager::getInstance()->getCaptchaMessageFromServer(true);
			}
			else {
				this->showToast(MSG_MAINTAIN, 2);
			}
            break;
        case TAG_TLMN_BTN_CAIDAT:
            CCLOG("%s", "sound");
			if (this->getChildByTag(POPUP_TAG_SETTING) == nullptr){
				auto m_popupSetting = PopupSetting::create();
				m_popupSetting->setTag(POPUP_TAG_SETTING);
				addChild(m_popupSetting, INDEX_POPUP);
				m_popupSetting->appear();
			}
            break;
        case TAG_TLMN_BTN_FACEBOOK:
            captureScreenShareFace();
            break;
        default:
            break;
        }
    }
}
//capacity_size -> so nguoi choi toi da trong room
void PlayScene::setPositionPlayer(Player& player){
    auto btn_danh_bai = MButton::create("btn_danhbai.png");

    int position_index;  //vi tri that cua nguoi choi
    //tinh toan vi tri that cua nguoi choi
    if (player.getTableIndex() >= currentTableIndex){
        position_index = player.getTableIndex() - currentTableIndex;
    }
    else {
        position_index = player.getTableIndex() - currentTableIndex + capacity_size;
    }

    if (position_index >= capacity_size){
        position_index = 0;
    }

    auto avatar = Avatar::create();

    // int _numberCard = player.getNumberCard();
    string user_name = player.getName();
    string user_id = player.getID();
    long long gold = player.getGold();
	long long cash = player.getCash();

    //char buffer[20];
	//sprintf(buffer, "%lld $", is_vip_room ? cash : gold);

	std::string buffer = StringUtils::format("%lld $", is_vip_room ? cash : gold);
    int image_index = player.getAvatarId();

    avatar->loadAvatar(image_index, user_id, user_name, buffer, roomIndex);
    auto pos = avatar->getAvatarPostion(position_index, origin, visibleSize, btn_danh_bai->getHeight());
    if(position_index == 0){
        pos = MVec2(width/2 - avatar->getContentSize().width/2,avatar->getPosition().y);
    }
    avatar->setPosition(pos);

    double cardCoverWidth = cardWidth() * 0.8f;
    avatar->loadCardCover(cardCoverWidth, position_index, 0);
    if (position_index == 0) {
        //if (indexPos == currentIndex) {
        avatar->hideCardCover();
    }

    avatar->setNumberCard(0);

    avatars.push_back(avatar);

    if (avatar->getParent() == nullptr)
        this->addChild(avatar);
}

//xoa bo nguoi cho khoi ban choi
void PlayScene::resetListWaiting(){
    for (size_t i = 0; i < lstDisplayWaitingPlayer.size(); i++)
    {
        if (lstDisplayWaitingPlayer[i]->getParent() != nullptr){
            lstDisplayWaitingPlayer[i]->removeFromParentAndCleanup(true);
        }
    }
    lstDisplayWaitingPlayer.clear();
}

void PlayScene::addCountDown(int countDown){
    auto background_countDown = MSprite::create("background_text_countdown.png");
    background_countDown->setPosition(MVec2(width/2+background_countDown->getWidth()*0.2f,
                                            height/2 - background_countDown->getHeight()/2));
    background_countDown->setTag(TAG_TIME_COUNTDOWN);
    this->addChild(background_countDown);
    
    auto background_countDownLeft = MSprite::create("text_vanchoisebatdausau.png");
    background_countDownLeft->setPosition(Vec2(- background_countDownLeft->getWidth(),
                                            background_countDown->getHeight()/2 - background_countDownLeft->getHeight()/2));
    background_countDown->addChild(background_countDownLeft);
    
    //TODO: Hùng xem lại chỗ này, add lại cái count down cho hợp lý nhé
    auto timerCountDown = MLabel::createCountDown(countDown);
    timerCountDown->setPosition(Vec2(background_countDown->getWidth()/2,background_countDown->getHeight()/2));
    background_countDown->addChild(timerCountDown);
    
    background_countDown->runAction(Sequence::create(DelayTime::create(countDown),RemoveSelf::create(), NULL));
}

//hidden card remaining count
void PlayScene::hiddenCardRemainingCount(vector<Avatar*> &avatars){
    for (int i = 0; i < avatars.size(); i++){
        avatars[i]->hideNumberCard(true);
    }
}

//lay ra avatar cua nguoi choi
Avatar* PlayScene::findAvatarOfPlayer(long long player_id) {
    for (int i = 0; i < avatars.size(); i++){
        if (avatars[i]->getPlayerId() == player_id){
            return avatars[i];
        }
    }
    return NULL;
}

void PlayScene::chatResponseHandler() {
    BINInstantMessageResponse* response =
        (BINInstantMessageResponse*)Common::getInstance()->checkEvent(NetworkManager::INSTANT_MESSAGE);
    if (response != 0){
        CCLOG("chat room response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            if (response->has_scope() && response->scope() == 2) {
                if (response->has_zoneid() &&
                    response->zoneid() == Common::getInstance()->getZoneId()) {
                    if (response->has_roomindex() &&
                        response->roomindex() == roomIndex) {
                        /*
                        xu ly hien thi message cho thang noi
                        */
                        long long int userId = response->has_senderuserid() ? response->senderuserid() : 0;
                        std::string message = response->has_instantmessage() ? response->instantmessage() : "";
                        Avatar* avatar = findAvatarOfPlayer(userId);
                        if (avatar != 0){
                            showMessageChat(message.c_str(), avatar, 3);
                        }
                        CCLOG("thang %lld gui tin nhan %s", userId, message.c_str());
                    }
                }
            }
        } else {
            this->showToast(response->message().c_str(), 2);
        }
    }
}

void PlayScene::textEmoticonResponseHandler(){
	BINSendTextEmoticonResponse* text_emoticon_response = (BINSendTextEmoticonResponse *)
		Common::getInstance()->checkEvent(NetworkManager::SEND_TEXT_EMOTICON);

	if (text_emoticon_response != 0){
		CCLOG("text emoticon response: %s", text_emoticon_response->DebugString().c_str());

		if (text_emoticon_response->responsecode()){
			int textEmoticonId = text_emoticon_response->textemoticonid(); //vat nem
			Avatar* senderAvatar = findAvatarOfPlayer(text_emoticon_response->senderuserid());//avatar nguoi nem
			Avatar* targerAvatar = findAvatarOfPlayer(text_emoticon_response->targetuserid());  //avatar nguoi bi nem

			if (senderAvatar != 0 && targerAvatar != 0){
                //hieu ung nem
                this->addNemAnimation(senderAvatar, targerAvatar,textEmoticonId);
			}
		}
        
		if (text_emoticon_response->has_message()){
			showToast(text_emoticon_response->message().c_str(), 2);
		}
	}
}

float PlayScene::cardWidth(){
    return width/18;
}

float PlayScene::posYCard(){
    return 5+btn_message->getHeight()*1.5f + cardWidth() * CARD_RATIO * 0.5f;
}

void PlayScene::addNemAnimation(Avatar * senderAvatar, Avatar* targerAvatar,int textEmoticonId) {
    Size sizeSender = senderAvatar->background->getSize();
    Vec2 posSender = senderAvatar->getPosition() + senderAvatar->background->getPosition()
                    + Vec2(sizeSender.width/2,sizeSender.height/2);
    
    Size sizeTarget = targerAvatar->background->getSize();
    Vec2 posTarget = targerAvatar->getPosition() + targerAvatar->background->getPosition()
                    + Vec2(sizeTarget.width/2,sizeTarget.height/2);
    
    Vec2 vecAngel = posTarget - posSender;
    float angle = atan(vecAngel.x / vecAngel.y) *180.0 / PI;
    CCLOG("Angle : %f",angle);
    CCLOG("X,y : %f,%f",vecAngel.x,vecAngel.y);
    
    Sprite * sprite;
    if(textEmoticonId == TAG_CLICK_PHAO){
        
        sprite = Sprite::createWithSpriteFrameName("nem_1_dan.png");
        sprite->setPosition(posSender);
        this->addChild(sprite,INDEX_ANIMATION);
        
        auto phao = Sprite::createWithSpriteFrameName("nem_1_phao.png");
        phao->setPosition(Vec2(posSender.x,posSender.y));
        phao->setRotation(angle);
        this->addChild(phao,INDEX_ANIMATION);
        phao->runAction(Sequence::create(MoveBy::create(0.1f,Vec2(-5,-5/tan(90-angle))),RemoveSelf::create(), NULL));
        auto khoi = Sprite::createWithSpriteFrameName("nem_1_khoi.png");
        khoi->setPosition(phao->getPosition() +
                          Vec2(phao->getContentSize().width,phao->getContentSize().height / tan(angle)));
        khoi->setRotation(angle);
        this->addChild(khoi,INDEX_ANIMATION);
        khoi->runAction(Sequence::create(FadeOut::create(0.3f),RemoveSelf::create(),NULL));
        
        sprite->setRotation(angle);
        auto call = CallFunc::create([=](){
            this->runAnimation("nem_1_%d.png",5, posTarget,1);
            this->removeChild(sprite);
        });
        sprite->runAction(Sequence::create(DelayTime::create(0.3f),MoveTo::create(0.5f, posTarget),call,NULL));
        
    }else if(textEmoticonId == TAG_CLICK_BEER){
        this->runAnimation("nem_3_%d.png",3, posTarget,2);
    }else if(textEmoticonId == TAG_CLICK_ROSE){
        this->runAnimation("nem_6_%d.png",10, posTarget,2);
    }else{
        
        CallFunc *call;
        
        switch (textEmoticonId) {
            case TAG_CLICK_CACHUA:
                sprite = Sprite::createWithSpriteFrameName("nem_4_cachua.png");
                call = CallFunc::create([=](){
                    this->runAnimation("nem_4_%d.png",2, posTarget,2);
                    this->removeChild(sprite);
                });
                
                break;
            case TAG_CLICK_DEP:
                sprite = Sprite::createWithSpriteFrameName("nem_2_dep.png");
                call = CallFunc::create([=](){
                    this->runAnimation("nem_2_%d.png",2, posTarget,2);
                    this->removeChild(sprite);
                });
                break;
            case TAG_CLICK_TRUNG:
                sprite = Sprite::createWithSpriteFrameName("nem_5_egg.png");
                call = CallFunc::create([=](){
                    this->runAnimation("nem_5_%d.png",5, posTarget,2);
                    this->removeChild(sprite);
                });
                break;
            default:
                break;
        }
        
        sprite->setPosition(posSender);
        sprite->setRotation(angle);
        sprite->runAction(Sequence::create(MoveTo::create(0.5f, posTarget),call,NULL));
        this->addChild(sprite,INDEX_ANIMATION);
    }

}

void PlayScene::lockRoomResponseHandler() {
    BINLockRoomResponse* lock_room_response =
        (BINLockRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::LOCK_ROOM);
    if (lock_room_response != 0) {
        CCLOG("lock room response: %s", lock_room_response->DebugString().c_str());
        if (lock_room_response->responsecode()) {
            this->passwordRequired = lock_room_response->lock();
            
            if (!this->passwordRequired){
                this->btnKhoa->loadTextureNormal("btn_khoa.png");
            }
            else {
                this->btnKhoa->loadTextureNormal("btn_mokhoa.png");
            }

            if (lock_room_response->has_message()){
                this->showToast(lock_room_response->message().c_str(), 2);
            }
        }
        else {
            this->showToast(lock_room_response->message().c_str(), 2);
        }
    }
}
//end implement

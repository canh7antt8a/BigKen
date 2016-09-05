//
//  PhomScene.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/17/16.
//
//

#include <algorithm>
#include <chrono>
#include <thread>

#include "PhomScene.hpp"
#include "SceneTable.hpp"

#include "UI/MButton.hpp"
#include "UI/MSprite.hpp"

#include "Utils/TLMNConfig.hpp"
#include "Utils/Common.h"
#include "Utils/Utility.h"

#include "external/json/writer.h"
#include "external/json/stringbuffer.h"

#include "Objects/CardSprite.hpp"
#include "Objects/PositionPlayer.h"

#include "Handler/TLMNCardHandler.h"

#include "protobufObject/exit_room.pb.h"

#define padding 20

#define TKAction "action"
#define TKNextAction "nextAction"
#define TKSuggestionCards "suggestionCards"
#define TKNewFirstRealeaseId "newFirstRealeaseId"
#define TKMainCount "mainCount"
#define TKIsPivot "isPivot"
#define TKData "data"
#define TKCurrentCards "currentCards"
#define TKKitSameKindAvaiables "kitSameKindAvaiables"
#define TKKitStraightAvaiables "kitStraightAvaiables"
#define TKBestKitCombinations "bestKitCombinations"
#define TKPairAvaiables "pairAvaiables"
#define TKSingleCards "singleCards"
#define TKMainCardCount "mainCardCount"
#define TKAllCurrentCardCount "allCurrentCardCount"
#define TKFirstReleaseUserId "firstReleaseUserId"

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

Scene* PhomScene::createScene(int _roomIndex, vector<BINPlayer> _playerList, vector<BINPlayer> _waitingPlayerList,
                              bool _createRoom, int _gameTag, bool _isDisplayRoomList, bool passwordRequired,
							  bool isVipRoom, int minBet, BINEnterRoomResponse* reEnterRoomResponse) {
    
    // 'layer' is an autorelease object
    auto scene = Scene::create();
    auto layer = PhomScene::create();
    layer->setRoomIndex(_roomIndex);
    layer->setVipRoom(isVipRoom);
    layer->setPassWordRequired(passwordRequired);
    layer->setPlayerList(_playerList);
    layer->setDisplayRoomList(_isDisplayRoomList);
    layer->setWaitingPlayerList(_waitingPlayerList);
    layer->setEnterRoomResponse(reEnterRoomResponse);
    layer->setCreateRoom(_createRoom);
	layer->setMinBet(minBet);
    layer->layoutInit();
    layer->initGame();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool PhomScene::init() {
    if (!PlayScene::init() ) {
        return false;
    }
    
    capacity_size = 4;
    _turnType = OTHER_CARD;
    this->initListThrowAndEatenCard();
    
    return true;
}

void PhomScene::initGame(){
    setListPlayerFromParams(player_list, waiting_player_list);
    if (enter_room_response != 0) {
        enterRoomResponseHandler(enter_room_response);
    }
}

void PhomScene::setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list) {
    if (_lstPlayer.size() > 0) _lstPlayer.clear();
    for (int i = 0; i < player_list.size(); i++) {
        PhomPlayer player = convertFromBINPlayer(player_list[i]);
        _lstPlayer.push_back(player);
    }
    
    for (int i = 0; i < waiting_player_list.size(); i++) {
        PhomPlayer player = convertFromBINPlayer(waiting_player_list[i]);
        _lstWaiting.push_back(player);
    }
    
	if (isUserPlaying()){
		showInvitePlayer((int)_lstPlayer.size());
		btn_san_sang->setVisible(false);
	}
	else {
		showBtnWithWatingPlayer(false);
	}

    showWaitingPlayerOnScene(_lstWaiting);
    //sap xep lai lst_player theo table_index
    sortListPlayer();
    //hien thi avatar cua nhung nguoi join vao phong
    displayInfoPlayer(_lstPlayer);
}

bool PhomScene::isUserPlaying(){
	int user_id = Common::getInstance()->getUserId();
	Player* player = findPlayer(user_id);
	if (player != 0){
		return true;
	}
	return false;
}

//show danh sach nguoi cho
void PhomScene::showWaitingPlayerOnScene(vector<PhomPlayer> lstWaiting){
    if (!lstWaiting.empty()){
        lstDisplayWaitingPlayer.clear();
        
        int size = (int)lstWaiting.size();
        int init_distance = 10;
        int distance = init_distance;
        for (int i = 0; i < 3; i++){
            if ((i + 1) > size){
                break;
            }
            WaitingPlayer* waitingPlayer = WaitingPlayer::create();
            waitingPlayer->setAvatar(lstWaiting[i].getName(), i);
            waitingPlayer->setPositionAvatar(origin, distance);
            distance += waitingPlayer->getAvatar()->getWidth()*0.5 + init_distance;
            lstDisplayWaitingPlayer.push_back(waitingPlayer);
            this->addChild(waitingPlayer);
        }
    }
}

void PhomScene::displayInfoPlayer(std::vector<PhomPlayer>& lst_info_players) {
    //find current index
    currentIndex = -1;
    currentTableIndex = -1;
    
    for (int i = 0; i < lst_info_players.size(); i++)  {
        int val;
        std::stringstream ss(lst_info_players[i].getID());
        ss >> val;
        if (Common::getInstance()->getUserId() == val) {
            currentIndex = i;
            currentTableIndex = lst_info_players[i].getTableIndex();
            break;
        }
    }
    //end find current index
    
    CCLOG("list player size: %lu", lst_info_players.size());
    int len = (int)lst_info_players.size();
    
    for (int i = 0; i < len; i++) {
        setPositionPlayer(lst_info_players[i]);
    }
    
}

void PhomScene::layoutInit() {
    PlayScene::initMenu();
    
    auto bkgTable = MSprite::create("sprite_table.png");
    bkgTable->setScale(width*0.8f/bkgTable->getWidth());
    bkgTable->setContentSize(Size(width*0.8f, bkgTable->getHeight()*bkgTable->getScale()));
    bkgTable->setPosition(Point(origin.x+visibleSize.width/2-bkgTable->getWidth()/2,
                                origin.y+visibleSize.height/2-bkgTable->getHeight()/2));
    this->addChild(bkgTable);
    
    btnStartMatch = MButton::create(BTN_START_MATCH, "Bắt đầu", 25, TAG_PHOM_BTN_BATDAU);
    btnStartMatch->setPosition(MVec2(0,10));
    btnStartMatch->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    btnStartMatch->setVisible(false);
    
    btnXepBai = MButton::create("btn_danhbai.png", "Xếp bài", 25, TAG_PHOM_BTN_XEPBAI);
    btnXepBai->setPosition(MVec2(width*0.3f - btnXepBai->getWidth()/2,10));
    btnXepBai->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    btnXepBai->setVisible(false);
    
    btnDanhBai = MButton::create("btn_danhbai.png", "Đánh bài", 25, TAG_PHOM_BTN_DANHBAI);
    btnDanhBai->setPosition(MVec2(width*0.6f - btnDanhBai->getWidth()/2,10));
    btnDanhBai->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
    btnBocBai = MButton::create("btn_danhbai.png", "Bốc bài", 25, TAG_PHOM_BTN_BOCBAI);
    btnBocBai->setPosition(MVec2(width*0.6f - btnBocBai->getWidth()/2,10));
    btnBocBai->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
    btnAnBai = MButton::create("btn_danhbai.png", "Ăn bài", 25, TAG_PHOM_BTN_ANBAI);
    btnAnBai->setPosition(MVec2(width*0.9f - btnAnBai->getWidth()/2,10));
    btnAnBai->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
    btnHaPhom = MButton::create("btn_danhbai.png", "Hạ Phỏm", 25, TAG_PHOM_BTN_HAPHOM);
    btnHaPhom->setPosition(MVec2(width*0.9f - btnHaPhom->getWidth()/2,10));
    btnHaPhom->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
    btnGuiBai = MButton::create("btn_danhbai.png", "Gửi Bài", 25, TAG_PHOM_BTN_GUIBAI);
    btnGuiBai->setPosition(MVec2(width * 0.9f - btnGuiBai->getWidth() / 2, 10));
    btnGuiBai->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
    btnU = MButton::create("btn_danhbai.png", "Ù", 25, TAG_PHOM_BTN_U);
    btnU->setPosition(MVec2(width * 0.9f - btnU->getWidth() / 2, 10));
    btnU->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    
	btn_san_sang = MButton::create(BTN_BUTTON, "Sẵn sàng", 25, TAG_TLMN_BTN_SANSANG);
	btn_san_sang->setPosition(Vec2(btn_message->getPosition().x - btn_san_sang->getWidth() - padding,
                                   btn_message->getPosition().y));
	btn_san_sang->addTouchEventListener(CC_CALLBACK_2(PhomScene::menuCallBack, this));
    btn_san_sang->setVisible(false);

    this->addChild(btnStartMatch);
    this->addChild(btnXepBai);
    this->addChild(btnDanhBai);
    this->addChild(btnBocBai);
    this->addChild(btnAnBai);
    this->addChild(btnHaPhom);
    this->addChild(btnGuiBai);
    this->addChild(btnU);
    this->addChild(btn_san_sang);
    this->disableAllCardButton();
    

    centerCard = MSprite::createwithFrameName("card_cover.png");
    centerCard->setScale(cardWidth()*0.8f/centerCard->getWidth());
    centerCard->setPosition(MVec2(width/2 -cardWidth()*0.4f,height/2 - cardWidth()*CARD_RATIO*0.4f));
    this->addChild(centerCard,1);
    centerCard->setVisible(false);
    
    remainCard = MLabel::create("0", cardWidth()/2);
    remainCard->setPosition(MVec2(width/2-remainCard->getWidth()/2,height/2-remainCard->getHeight()/2));
    this->addChild(remainCard,1);
    remainCard->setVisible(false);
    
    spriteFirstTurn = MSprite::create("firstTurn.png");
    this->addChild(spriteFirstTurn, 100);
    spriteFirstTurn->setVisible(false);
}

void PhomScene::onEvent(int value) {
    if (btnHaPhom->isVisible() == false) {
        for(CardSprite* card : card_tag) {
            if(card->getState() == OnHand && card->getNumberValue() != value) {
                card->setMoveDown();
            }
        }
    }
}

void PhomScene::sortCard(vector<int> card_values) {
    if (!_cards.empty()) _cards.clear();
    for(int i=0;i<card_values.size();i++) {
        Card card;
        card.setValue(card_values[i]); // Số thẻ là 1-52
        _cards.push_back(card);
        
    }
    this->showInitCard();
}

void PhomScene::createCard(PositionIndex positionIndex, int tag) {
    
    auto cardx = _cards[positionIndex.x];
    auto cardSprite = CardSprite::create(cardx,positionIndex,this->cardWidth(),this);
    
    cardSprite->setPosition(MVec2(visibleSize.width/2,visibleSize.height/2));
    cardSprite->setTag(cardx.getValue());
    
    this->card_tag.push_back(cardSprite);
    
}

void PhomScene::showInitCard() {
    _currentTurnUserId = -1;
    
    centerCard->setVisible(true);
    remainCard->setVisible(true);
    
    for (int i = 0; i < _cards.size();i++){
        PositionIndex positionIndex;
        positionIndex.x = i;
        positionIndex.y = 0;
        this->createCard(positionIndex, i);
        if (card_tag[i]->getParent() == nullptr)
            this->addChild(card_tag[i],INDEX_CARD);
    }
    
    for(int i = 0; i < card_tag.size();i++) {
        auto delay = DelayTime::create(1.0f);
        auto moveTo = MoveTo::create(0.2f+0.05f*i,MVec2(width/2 + (i-4)*cardWidth(),posYCard()));
        auto sequence = Sequence::create(ScaleBy::create(0,0.8f),delay,
                                         Spawn::create(ScaleBy::create(0.2f + 0.05f*i,10/8.0),moveTo, NULL), NULL);
        card_tag[i]->runAction(sequence);
        card_tag[i]->setPosY(posYCard());
    }
}

void PhomScene::sortCard() {
    refreshCard();
    for (int i = 0; i < _cards.size(); i++) {
        if (checkContainsCardTag(_cards[i].getValue())) {
            PositionIndex pos;
            pos.x = i;
            pos.y = 0;
            for(CardSprite* card : card_tag) {
                if(card->getNumberValue() == _cards[i].getValue()) {
                    card->setPositionIndex(pos);
                    card->setState(Idle);
                    auto moveTo = MoveTo::create(0.2f,MVec2(width/2 + (i -4) * cardWidth(),posYCard()));
                    card->runAction(moveTo);
                }
            }
        } else {
            _cards.erase(_cards.begin() + i);
        }
    }
}

void PhomScene::sortCardAfterMoveCardToCenter() {
    for (int i = 0;i<card_tag.size();i++) {
        card_tag[i]->setState(Idle);
        auto moveTo = MoveTo::create(0.2f, MVec2(width / 2 + (i - 4) * cardWidth(),posYCard()));
        card_tag[i]->runAction(moveTo);
    }
}

void PhomScene::removeCardAfterThrow(int cardValue) {
    for (int i = (int)card_tag.size() - 1; i >= 0; i--) {
        if (card_tag[i]->getNumberValue() == cardValue) {
            card_tag[i]->removeFromParentAndCleanup(true);
            card_tag.erase(card_tag.begin() + i);
        }
    }
}

void PhomScene::menuCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*) pSender)->getTag();
        vector<int> card_values;
        switch (tag) {
            case TAG_TLMN_BTN_BACK:
                m_popupTLMN->appear();
                break;
                
            case TAG_PHOM_BTN_BATDAU:
                CCLOG("Start match phong %d", getRoomIndex());
                btnStartMatch->setVisible(false);
                NetworkManager::getInstance()->getStartMatchMessageFromServer(getRoomIndex());
                break;
                
            case TAG_PHOM_BTN_DANHBAI:
                throwCard();
                break;
                
            case TAG_PHOM_BTN_BOCBAI:
                CCLOG("btn boc bai");
                pickCard();
                break;
                
            case TAG_PHOM_BTN_ANBAI:
                CCLOG("btn an bai");
                this->eatCard("true");
                break;
                
            case TAG_PHOM_BTN_HAPHOM:
                CCLOG("btn ha phom mac dinh tu dong ha");
                card_values.clear();
                for (int i = 0; i<card_tag.size(); i++) {
                    if (card_tag[i]->getState() == OnHand) {
                        card_values.push_back(card_tag[i]->getCard().value);
                    }
                }
                if (card_values.size() >= 3) {
                    this->releaseCard(Common::getInstance()->convertListCardToString(card_values));
                } else {
                    this->autoReleaseCard();
                }
                break;
                
            case TAG_PHOM_BTN_GUIBAI:
                CCLOG("btn gui bai");
                this->consignedCards();
                break;
                
            case TAG_PHOM_BTN_U:
                CCLOG("Bao U");
                this->u();
                break;
                
            case TAG_PHOM_BTN_XEPBAI:
                CCLOG("Sep bai");
                this->sortCard();
                break;

			case TAG_TLMN_BTN_SANSANG:
				NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, -1);
				break;
            default:
                break;
        }
    }
}

Vec2 PhomScene::getCardCoverPostion(Avatar* avatar){
    return avatar->getPosition() + avatar->spriteCard->getPosition();
}

void PhomScene::playCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {}

void PhomScene::cardCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {}

void PhomScene::onExit() {
    PlayScene::onExit();
}

void PhomScene::update(float delta) {
    PlayScene::update(delta);
    
    startMatchResponseHandler();
    
    playerEnterRoomResponseHandler();
    
    turnResponse();
    
    matchEndResponseHandler();
    
    roomOwnerChangedResponseHandler();
    
    updateMoneyResponseHandler();
    
    prepareNewMatchResponseHandler();
    
    playerExitRoomResponse();
    
    playerExitAfterMatchEndResponse();
    
    readyToPlayResponseHandler();
    
    matchBeginResponseHandler();
    
    roomOwnerChangedResponseHandler();
    
    changeRuleResponseHandler();

	cancelExitAfterMatchEndResponseHandler();
}

void PhomScene::matchEndResponseHandler() {
    BINMatchEndResponse *endmatchresponse = (BINMatchEndResponse*)
    Common::getInstance()->checkEvent(NetworkManager::MATCH_END);
    
    if (endmatchresponse != 0) {
        CCLOG("end match response: %s", endmatchresponse->DebugString().c_str());
        if (endmatchresponse->responsecode()) {
            
            for(int i = 0; i < avatars.size();i++){
                if(avatars[i]->getPositionIndex()!=0){
                    avatars[i]->hideCardCover(true);
                }
            }
            
            disableAllCardButton();
            btnXepBai->setVisible(false);
            if (endmatchresponse->textemoticons_size() > 0) {
                //TODO: Hùng xử lý lại cho anh phần animation có ù
                //các quân bài của thằng trong phỏm ù của thằng ù thì được lưu trong biến _phomsU
                long long userID = endmatchresponse->textemoticons(0).userid();
                long emoIconId = endmatchresponse->textemoticons(0).emoticonid();
                string message = endmatchresponse->textemoticons(0).message();
                string messageShow = StringUtils::format("thang %lld %s", userID, message.c_str());
                this->showToast(messageShow.c_str(), 2);
                
                //======
                
                // hide CENTER CARD,,remain card.
                centerCard->setVisible(false);
                remainCard->setVisible(false);
                
                for(int i = 0; i < avatars.size();i++){
                    if(avatars[i]->getPositionIndex()!=0){
                        avatars[i]->hideCardCover(true);
                    }
                }
                
                for(int i = 0;i < 4; i++){
                    for(int j = 0;j< groupEatCards[i].size() ; j++){
                        groupEatCards[i][j]->removeFromParentAndCleanup(true);
                    }
                    groupEatCards[i].clear();
                }
                
                auto background = LayerColor::create(Color4B(0,0,0,220));
                background->setContentSize(visibleSize);
                background->setPosition(MVec2(0, 0));
                this->addChild(background);
                background->runAction(Sequence::create(DelayTime::create(endmatchresponse->countdowntimer()/1000),
                                                       RemoveSelf::create(),NULL));
                auto avatarU = findAvatarOfPlayer(userID);
                if(avatarU != 0){
                    
                    if(userID == Common::getInstance()->getUserId()){
                        for(int i = 0 ; i< card_tag.size(); i++){
                            card_tag[i]->setVisible(false);
                        }
                        auto pos = avatarU->getAvatarPostion(0, origin, visibleSize, btn_message->getHeight());
                        avatarU->runAction(MoveTo::create(0.25f,Vec2(originX + width/2 - avatarU->getContentSize().width,pos.y)));
                    }
                    
                    avatarU->setU((int)emoIconId,endmatchresponse->countdowntimer()/1000);
                    int index = 0;
                    CCLOG("CARD SIZE : %d",(int)_phomsU.size());
                    for(int i = 0; i < _phomsU.size(); i++){
                        for(int j = 0; j < _phomsU[i].size(); j++){
                            index ++;
                            auto cardU = OtherCardSprite::createSelf(_phomsU[i][j], cardWidth());
                            //int sizeOfPhom = i == 0 ? 0 : (int)_phomsU[i-1].size();
                            cardU->setPosition(MVec2(width/2 - cardWidth()*6,height/2)
                                               + Vec2(index*cardWidth() + i*0.25f*cardWidth(),0));
                            cardU->runAction(Sequence::create(DelayTime::create(endmatchresponse->countdowntimer()/1000),
                                                              RemoveSelf::create(),NULL));
                            this->addChild(cardU);
                        }
                    }
                }
            }
            if (endmatchresponse->args_size() > 0) {
                for (int i = 0; i < endmatchresponse->args_size(); i++) {
                    string key = endmatchresponse->args(i).key();
                    string value = endmatchresponse->args(i).value();
                    if (key == "orderEnding") {
                        for (string::iterator it = value.begin(); it != value.end(); it++) {
                            if (*it == '\\') {
                                value.erase(it);
                            }
                        }
                        vector<JSONObject> ranks = parseJSONString(value);
                        for (vector<JSONObject>::iterator it = ranks.begin(); it != ranks.end(); it ++) {
                            int userID = Common::getInstance()->convertStringToInt(it->getKey());
                            int rank = Common::getInstance()->convertStringToInt(it->getValue());
                            Avatar* curAvatar = findAvatarOfPlayer(userID);
                            if(curAvatar!=0){
                                if (rank == 1) {
                                    if(_phomsU.size() == 0){
                                        curAvatar->setWin(endmatchresponse->countdowntimer()/1000);
                                    }
                                } else {
                                    string rank_text;
                                    if (rank == _lstPlayer.size()){
                                        rank_text = "bet.png";
                                    } else if (rank == 2) {
                                        rank_text = "nhi.png";
                                    } else if (rank == 3) {
                                        rank_text = "ba.png";
                                    } else if (rank == -1) {
                                        rank_text = "mom.png";
                                    }
                                    auto rank_sprite = Sprite::create(rank_text);
                                    rank_sprite->setPosition(curAvatar->getPosition() + Vec2(curAvatar->getContentSize().width/2,
                                                                                             curAvatar->getContentSize().height/2));
                                    rank_sprite->runAction(Sequence::create(DelayTime::create(3),RemoveSelf::create(),NULL));
                                    this->addChild(rank_sprite,INDEX_ANIMATION);
                                }
                            }
                        }
                    } else if (key == "cardRemaining"){
                        for (string::iterator it = value.begin(); it != value.end(); it++) {
                            if (*it == '\\' && *(it + 1)) {
                                value.erase(it);
                            }
                        }
                        
                        if(btnHaPhom->isVisible()){
                            return;
                        }
                        
                        if(_phomsU.size() != 0){
                            return;
                        }
                            
                        vector<JSONObject> result = parseJSONString(value);
                        
                        for (vector<JSONObject>::iterator it = result.begin(); it != result.end(); it++) {
                            //TODO: xử lý phần show các quân bài hạ
                            //userID tương ứng với người chơi có các quân bài còn lại trong cardRemainValue
                            
                            int userID = Common::getInstance()->convertStringToInt(it->getKey());
                            vector<string> cardRemain = Common::getInstance()->split(it->getValue(), ',');
                            vector<int> cardRemainValue = Common::getInstance()->convertStringsToInt(cardRemain);
                            Avatar* curAvatar = findAvatarOfPlayer(userID);
                            if(curAvatar!=0){
                                if (Common::getInstance()->getUserId() == userID) {
                                    //xử lý phần đưa những quân bài của thằng người chơi show ra màn hình
                                    //....
                                } else {
                                    //show toàn bộ những quân bài của thằng khác chưa hạ ra
                                    for(int i = 0;i < cardRemainValue.size(); i++){
                                        auto card = OtherCardSprite::createSelf(cardRemainValue[i],cardWidth());
                                        card->setPosition(getCardCoverPostion(curAvatar));
                                        Vec2 pos = Vec2(i*cardWidth()*0.8f*0.25f,0) + Vec2(cardWidth()*2,0);
                                        if(curAvatar->getPositionIndex() == 1){
                                            pos = Vec2((-cardRemainValue.size() + i ) * cardWidth()*0.8f*0.25f*0.3f,0) - Vec2(cardWidth(),0);
                                        }
                                        auto move = MoveTo::create(0.1f, getCardCoverPostion(curAvatar) + pos);
                                        card->runAction(Sequence::create(move,DelayTime::create(2),RemoveSelf::create(),NULL));
                                        this->addChild(card);
                                    }
                                }
                            }
                        }
                        
                    } else if (key == "compensationPlayerUserId") {
                        //TODO: animation thằng bị phạt vì đánh ù đền
                        int userId = Common::getInstance()->convertStringToInt(value);
                    }
                }
            }
        }
    }
}

void PhomScene::playerExitRoomResponse() {
    BINPlayerExitRoomResponse* rs =
    (BINPlayerExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_ROOM);
    if (rs != 0) {
        CCLOG("exit room player response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
            int leng = (int)_lstPlayer.size();
            for (int i = 0; i < leng; i++) {
                string userId = _lstPlayer[i].getID();
                if (userId == Common::getInstance()->convertIntToString((int) rs->exituserid())) {
                    _lstPlayer.erase(_lstPlayer.begin() + i);

					showInvitePlayer((int)_lstPlayer.size());  //show moi choi

					//neu chi con 1 nguoi choi thi an countdown dem nguoc chu phong
					if (_lstPlayer.size() == 1 && this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
						this->removeChildByTag(TAG_TIME_COUNTDOWN);
					}

                    auto avatar = findAvatarOfPlayer(rs->exituserid());
                    if(avatar!=0){
                        removeOutTablePlay(avatar);
                        avatars.erase(std::remove(avatars.begin(), avatars.end(), avatar), avatars.end());
                    }
                    
                    if (_lstPlayer.size() < 2) {
                        btnStartMatch->setVisible(false);
                    }
                    
                    if (rs ->changeownerroomcd() > 0) {
                        if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr) {
                            this->removeChildByTag(TAG_TIME_COUNTDOWN);
                        }
                        //int time = rs->changeownerroomcd() / 1000;
                        //auto timeCountDown = MLabel::createCountDown(time);
                        //timeCountDown->setPosition(width / 2, height / 2);
                        //this->addChild(timeCountDown);
                        //centerCard->setVisible(false);
                        //remainCard->setVisible(false);
                    }
                    break;
                }
            }
            
            Player* playerWaiting = findWaiting(rs->exituserid());
            if (playerWaiting != 0) {
                deleteWaitingPlayer(playerWaiting->getID());
                resetListWaiting();
                showWaitingPlayerOnScene(_lstWaiting);
            }
        }
    }
    
}

void PhomScene::playerExitAfterMatchEndResponse() {
    BINPlayerExitAfterMatchEndResponse* rs =
    (BINPlayerExitAfterMatchEndResponse*) Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_AFTER_MATCH_END);
    if (rs != 0) {
        CCLOG("player exit room after matchend response: \n%s", rs->DebugString().c_str());
        if (rs->responsecode()) {
            int leng = (int)_lstPlayer.size();
            for (int i = 0; i < leng; i++) {
                string userID = _lstPlayer[i].getID();
                if (userID == Common::getInstance()->convertIntToString((int) rs->exituserid())) {
                    /*char message[60];
					sprintf(message, "Người chơi %s đăng ký rời bàn chơi", _lstPlayer[i].getName().c_str());
					this->showToast(message, 2);*/

					Avatar* avatar = findAvatarOfPlayer(rs->exituserid());
					if (avatar != 0){
						avatar->showRegisterExitRoom(true);
					}
                    
                    break;
                }
            }
        }
    }
}

void PhomScene::turnResponse() {
    BINTurnResponse *turnresponse =
    (BINTurnResponse*)Common::getInstance()->checkEvent(NetworkManager::TURN);
    if (turnresponse != 0) {
        CCLOG("turn response: %s", turnresponse->DebugString().c_str());
        if (turnresponse->responsecode()) {
            long long player_id = turnresponse->currentturnuserid();
            long long next_player_id = turnresponse->nextturnuserid();
            if (turnresponse->has_countdowntimer()) {
                int coutDown = (int)turnresponse->countdowntimer();
                auto avatar = findAvatarOfPlayer(player_id);
                if (avatar != 0){
                    avatar->resetProcessCircleBar();
                }
                if (!turnresponse->matchend()){
                    avatar = findAvatarOfPlayer(next_player_id);
                    if (avatar != 0){
                        avatar->updateProgressCircleBar(100, coutDown);
                    }
                }
            }
            
            if (turnresponse->has_currentturnuserid()) {
                setPreviousTurnUserId(getCurrentTurnUserId());
                setCurrentTurnUserId((int)turnresponse->currentturnuserid());
                player_id = turnresponse->currentturnuserid();
            }
            
            if (turnresponse->has_nextturnuserid()) {
                next_player_id = turnresponse->nextturnuserid();
                setNextTurnUserId((int)next_player_id);
            }
            
            if (turnresponse->args_size() > 0) {
                bool canEat = false;
                string data = "";
                this->disableAllCardButton();
                for (int i = 0; i < turnresponse->args_size(); i++) {
                    string key = turnresponse->args(i).key();
                    string value = turnresponse->args(i).value();
                    if (key == TKAction) {
                        _turnType = (PhomTurnType)Common::getInstance()->convertStringToInt(value);
                    } else if (key == TKData) {
                        data = value;
                    }  else if (getNextTurnUserId() == Common::getInstance()->getUserId() && key == TKNextAction) {
                        vector<string> nextActionStrings = Common::getInstance()->split(value, ',');
                        vector<int> nextActions = Common::getInstance()->convertStringsToInt(nextActionStrings);
                        CCLOG("cac action %lu", nextActions.size());
                        for (vector<int>::iterator it = nextActions.begin(); it != nextActions.end(); it++) {
                            switch (*it) {
                                case DANHBAI:
                                    btnDanhBai->setVisible(true);
                                    break;
                                case BOCBAI:
                                    btnBocBai->setVisible(true);
                                    break;
                                case HABAI:
                                    btnHaPhom->setVisible(true);
                                    break;
                                case ANBAI:
                                    btnAnBai->setVisible(true);
                                    break;
                                case GUIBAI:
                                    btnGuiBai->setVisible(true);
                                    break;
                                case U:
                                    btnU->setVisible(true);
                                    break;
                                case TUDONGHA:
                                    break;
                                default:
                                    break;
                            }
                        }
                    } else if (key == TKSuggestionCards) {
                        if (getNextTurnUserId() == Common::getInstance()->getUserId()) {
                            if (_turnType == DANHBAI) {
                                vector<vector<int>> suggestPair = parseJSONToPair(value);
                                if (suggestPair.size() > 0) {
                                    canEat = true;
                                }
                            } else if (_turnType == U || _turnType == TUDONGHA || _turnType == BOCBAI || _turnType == GUIBAI) {
                                //TODO: gợi ý quân bài có thể gửi được
                                vector<string> sugestCardString = Common::getInstance()->split(value, ',');
                                vector<int> sugesstCards = Common::getInstance()->convertStringsToInt(sugestCardString);
                                
                                for (int suggestCard: sugesstCards){
                                    for(CardSprite* card : card_tag){
                                        if(card->getNumberValue() == suggestCard){
                                            auto sprite = Sprite::createWithSpriteFrameName("guibai_efect.png");
                                            sprite->setAnchorPoint(Vec2(0,0));
                                            sprite->setTag(1);
                                            card->addChild(sprite);
                                        }
                                    }
                                }
                            }
                        }
                    } else if (key == TKIsPivot) {
                        if (Common::getInstance()->to_bool(value)) {
                            this->showToast("Bắt chốt đấy đánh cẩn thận", 2);
                        }
                    } else if (_turnType == ANBAI && key == TKNewFirstRealeaseId) {
                        auto preAvatar = findAvatarOfPlayer(getFirstTurnUserId());
                        if (preAvatar!=0 && getMainCardCount() < _lstPlayer.size()) {
                            preAvatar->setStatus("Tái lượt", 2);
                        }
                        setFirstTurnUserId(Common::getInstance()->convertStringToInt(value));
                        //TODO: Chuyển người hạ phỏm
                        auto currAvatar = findAvatarOfPlayer(getFirstTurnUserId());
                        if(preAvatar != 0 && currAvatar != 0){
                            spriteFirstTurn->setPosition(preAvatar->getPosition());
                            spriteFirstTurn->runAction(MoveTo::create(0.5f, currAvatar->getPosition()));
                        }
                        
                    } else if (_turnType == BOCBAI && key == TKMainCount) {
                        setMainCardCount(Common::getInstance()->convertStringToInt(value));
                    } else if (key == TKKitSameKindAvaiables) {
                        
                        _kitSameKind = parseJSONToPair(value);
                        
                    } else if (key == TKKitStraightAvaiables) {
                        
                        _kitStraight = parseJSONToPair(value);
                        
                    } else if (key == TKBestKitCombinations) {
                        
                        _phoms = parseJSONToPair(value);
                        
                    } else if (key == TKPairAvaiables) {
                        
                        _pairs = parseJSONToPair(value);
                        
                    } else if (key == TKSingleCards) {
                        if (value != "") {
                            vector<string> cardString = Common::getInstance()->split(value, ',');
                            _singleCards = Common::getInstance()->convertStringsToInt(cardString);
                        }
                    }
                }
                turnTypeResponse(turnresponse->countdowntimer(),data,canEat);
            }
        } else {
            this->showToast(turnresponse->message().c_str(), 2);
        }
    }
}

void PhomScene::roomOwnerChangedResponseHandler() {
    BINRoomOwnerChangedResponse* response =
    (BINRoomOwnerChangedResponse*) Common::getInstance()->checkEvent(NetworkManager::ROOM_OWNER_CHANGED);
    if (response != 0) {
        CCLOG("room owner changed response:\n %s\n", response->DebugString().c_str());
        if (response->responsecode()) {
            int neOwnerUserId = (int)response->newowneruserid();
            auto common = Common::getInstance();
            common->setOwnerUserId(neOwnerUserId);
            setCreateRoom(common->getUserId() == neOwnerUserId);

			displayLockRoomForOwner(neOwnerUserId);

            btnStartMatch->setVisible(isCreateRoom() && _lstPlayer.size() >= 2);
            if (response->changeownerroomcd() > 0) {
                CCLOG("room owner change time countdown %d", response->changeownerroomcd());
                //int time = response->changeownerroomcd() / 1000;
                //auto timeCountDown = MLabel::createCountDown(time);
                //timeCountDown->setPosition(width / 2, height / 2);
                //this->addChild(timeCountDown);
                //centerCard->setVisible(false);
                //remainCard->setVisible(false);
            }
        } else {
            this->showToast(response->message().c_str(), 2);
        }
    }
}

void PhomScene::updateMoneyResponseHandler() {
    BINUpdateMoneyResponse *updatemoneyresponse =
    (BINUpdateMoneyResponse*)Common::getInstance()->checkEvent(NetworkManager::UPDATE_MONEY);
    
    if (updatemoneyresponse != 0) {
        CCLOG("update money response: %s", updatemoneyresponse->DebugString().c_str());
        if (updatemoneyresponse->responsecode()) {
            if (updatemoneyresponse->moneyboxes_size() > 0) {
                BINMoneyBox monneyBox;
                long long originMoney;
                Player* player;
                Avatar * avatar;
                for (int i = 0; i < updatemoneyresponse->moneyboxes_size(); i++) {
                    bool isCash = monneyBox.iscash();
                    monneyBox = updatemoneyresponse->moneyboxes(i);
                    player = findPlayer(monneyBox.userid());
                    if (player != 0) {
                        originMoney = monneyBox.currentmoney();
                        if (Common::getInstance()->getUserId() == monneyBox.userid()) {
                            if (isCash) {
                                Common::getInstance()->setCash(originMoney);
                            } else {
                                Common::getInstance()->setGold(originMoney);
                            }
                        }
                        avatar = findAvatarOfPlayer(monneyBox.userid());
                        if (avatar != 0) {
                            avatar->setMoney(originMoney);

							if (monneyBox.displaychangemoney() != 0){
								auto moneyText = MLabel::createUpdateMoney(monneyBox.displaychangemoney());
								moneyText->setPosition(Vec2(avatar->getPosition().x + avatar->avatar->getWidth() / 2,
									avatar->getPosition().y + avatar->avatar->getHeight() / 2));
								this->addChild(moneyText,INDEX_UPDATE_MONEY);
							}
                        }
                    }
                }
            }
        }
    }
}

void PhomScene::startMatchResponseHandler() {
    BINStartMatchResponse *rs =
    (BINStartMatchResponse*)Common::getInstance()->checkEvent(NetworkManager::START_MATCH);
    if (rs != 0) {
        CCLOG("start match response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
			if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
				this->removeChildByTag(TAG_TIME_COUNTDOWN);
			}

            this->showToast(rs->message().c_str(), 2);
            if (rs ->has_countdowntimer())
                setMatchCountDownTime(rs->countdowntimer());
            if (rs->has_firstturnuserid())
                setFirstTurnUserId((int)rs->firstturnuserid());

            if (rs->args_size() > 1) {
                for (int i = 0; i < rs->args_size(); i++) {
                    string key = rs->args(i).key();
                    string value = rs->args(i).value();
                    if (key == TKCurrentCards) {
                        std::vector<int> currentCards =
                        Common::getInstance()->convertStringsToInt(Common::getInstance()->
                                                                   split(value, ','));
                    } else if (key == TKMainCardCount) {
                        int mainCardCount = Common::getInstance()->convertStringToInt(value);
                        this->setMainCardCount(mainCardCount);
                        remainCard->setString(StringUtils::format("%d",getMainCardCount()));
                        remainCard->setPosition(MVec2(width/2-remainCard->getWidth()/2,height/2-remainCard->getHeight()/2));
                        
                    } else if (key == TKAllCurrentCardCount) {
                        
                    } else if (key == TKFirstReleaseUserId) {
                        int firstReleaseUserId = Common::getInstance()->convertStringToInt(value);
                        setFirstReleaseUserId(firstReleaseUserId);
                        
                    } else if (key == TKKitSameKindAvaiables) {
                        
                        _kitSameKind = parseJSONToPair(value);
                        
                    } else if (key == TKKitStraightAvaiables) {
                        
                        _kitSameKind = parseJSONToPair(value);
                        
                    } else if (key == TKBestKitCombinations) {
                        
                        _phoms = parseJSONToPair(value);
                        
                    } else if (key == TKPairAvaiables) {
                        
                        _pairs = parseJSONToPair(value);
                        
                    } else if (key == TKSingleCards) {
                        if (value != "") {
                            vector<string> cardString = Common::getInstance()->split(value, ',');
                            _singleCards = Common::getInstance()->convertStringsToInt(cardString);
                        }
                    }
                }
                swapCard();
                if (findPlayer(Common::getInstance()->getUserId()) != NULL) {
                    Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
                    if(avatar!=0){
                        if(avatar->getAvatarPostion(0, origin, visibleSize, btn_message->getHeight()) != avatar->getPosition()) {
                            auto move = MoveTo::create(0.5f,avatar->getAvatarPostion(0, origin, visibleSize, btnAnBai->getHeight()));
                            avatar->runAction(move);
                        }
                    }
                } else {
                    Avatar* avatar;
                    for (int i = 0; i < avatars.size(); i++){
                        if (avatars[i]->getPositionIndex() == 0){
                             avatar = avatars[i];
                            break;
                        }
                    }
                    if(avatar->getAvatarPostion(0, origin, visibleSize, btn_message->getHeight()) != avatar->getPosition()) {
                        auto move = MoveTo::create(0.5f,avatar->getAvatarPostion(0, origin, visibleSize, btnAnBai->getHeight()));
                        avatar->runAction(move);
                    }
                }
            }
        } else {
            btnStartMatch->setVisible(this->isCreateRoom());
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void PhomScene::playerEnterRoomResponseHandler() {
    BINPlayerEnterRoomResponse *newplayerresponse = (BINPlayerEnterRoomResponse*)
    Common::getInstance()->checkEvent(NetworkManager::PLAYER_ENTER_ROOM);
    if (newplayerresponse != 0) {
        CCLOG("player enter room response: %s", newplayerresponse->DebugString().c_str());
        if (newplayerresponse->responsecode()) {
            if (newplayerresponse->has_enterroomstatus()) {
                PhomPlayer player = convertFromBINPlayer(newplayerresponse->player());
                switch (newplayerresponse->enterroomstatus()) {
                    case PlayerState::PLAYING:
                        //ad vao list nguoi choi
                    {
                        _lstPlayer.push_back(player);

						showInvitePlayer((int)_lstPlayer.size());  //show moi choi

                        sortListPlayer();
                        int index_pos_newplayer = findIndexPlayer(_lstPlayer, player);
                        if (index_pos_newplayer != -1){
                            setPositionPlayer(_lstPlayer[index_pos_newplayer]);
                        }
                        btnStartMatch->setVisible(isCreateRoom() && _lstPlayer.size() >= 2);

						// thoi gian doi khi thay doi chu phong
                        if (newplayerresponse->changeownerroomcd() > 0) {
                            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr) {
                                this->removeChildByTag(TAG_TIME_COUNTDOWN);
                            }
                            
                            int time_wait = newplayerresponse->changeownerroomcd() / 1000;
                            addCountDown(time_wait);
                            centerCard->setVisible(false);
                            remainCard->setVisible(false);
                        }
                    }
                        break;
                        
                    case PlayerState::WAITING:
                        _lstWaiting.push_back(player);
                        resetListWaiting();
                        showWaitingPlayerOnScene(_lstWaiting);
                        break;
                        
                    case 3:
                        // thang nay dang choi roi add no lai vao list cu
                        break;
                        
                    default:
                        break;
                }
            }
        }
        else {
            this->showToast(newplayerresponse->message().c_str(), 2);
        }
    }
}

void PhomScene::matchBeginResponseHandler() {
    BINMatchBeginResponse* response =
    (BINMatchBeginResponse*)Common::getInstance()->checkEvent(NetworkManager::MATCH_BEGIN);
    if (response != 0) {
        CCLOG("match begin response:\n %s\n", response->DebugString().c_str());
        if (response->responsecode()) {

            if (findPlayer(Common::getInstance()->getUserId()) != NULL) {
                btnXepBai->setVisible(true);
                btnDanhBai->setVisible(getFirstTurnUserId() == Common::getInstance()->getUserId());
            }

            int timer = (response->has_countdowntimer()) ? response->countdowntimer() : 0;
            auto avatar = findAvatarOfPlayer(getFirstTurnUserId());
            if (avatar != 0){
                spriteFirstTurn->setPosition(avatar->getPosition());
                spriteFirstTurn->setVisible(true);
                avatar->updateProgressCircleBar(100, timer);
            }
        } else {
            //this->showToast(response->message().c_str(), 2);
        }
    }
}

void PhomScene::prepareNewMatchResponseHandler() {
    BINPrepareNewMatchResponse *prepareNewMatch = (BINPrepareNewMatchResponse*)
    Common::getInstance()->checkEvent(NetworkManager::PREPARE_NEW_MATCH);
    if (prepareNewMatch != 0) {
        CCLOG("prepare new match response: %s", prepareNewMatch->DebugString().c_str());
        if (prepareNewMatch->responsecode()) {
            
            if(this->getChildByTag(TAG_TIME_COUNTDOWN) == nullptr){
                addCountDown((int)prepareNewMatch->countdowntimer()/1000);
            }
            
            for(vector<vector<OtherCardSprite*>> groupCards : groupHaBaiCards){
                for(vector<OtherCardSprite*> cards : groupCards){
                    for(OtherCardSprite* card : cards){
                        card->removeFromParentAndCleanup(true);
                    }
                }
            }
            auto avatarUser = findAvatarOfPlayer(Common::getInstance()->getUserId());
            if(avatarUser!=0){
                auto pos = avatarUser->getAvatarPostion(0, origin, visibleSize, btn_message->getHeight());
                avatarUser->runAction(MoveTo::create(0.25f,Vec2(originX + width/2 - avatarUser->getContentSize().width,pos.y)));
            }
            
            for(int i = 0; i < avatars.size();i++){
                if(avatars[i]->getPositionIndex()!=0){
                    avatars[i]->hideCardCover(false);
                }
            }
            
            centerCard->setVisible(false);
            remainCard->setVisible(false);
            
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < groupThrowCards[i].size(); j++) {
                    if(groupThrowCards[i][j]->getParent() != nullptr){
                        groupThrowCards[i][j]->removeFromParentAndCleanup(true);
                    }
                }
                groupThrowCards[i].clear();
                
                if(_phomsU.size() == 0){
                    for (int j = 0; j < groupEatCards[i].size(); j++) {
                        groupEatCards[i][j]->removeFromParentAndCleanup(true);
                    }
                }
                groupEatCards[i].clear();
                
                groupHaBaiCards[i].clear();
            }
            
            for (int i = 0; i < card_tag.size(); i ++) {
                card_tag[i]->removeFromParentAndCleanup(true);
            }
            
            card_tag.clear();
            
            Vector<Node*> children = this->getChildren();
            for(int i = 0; i < children.size(); i ++) {
                OtherCardSprite* card = dynamic_cast<OtherCardSprite*>(children.at(i));
                if (card != nullptr) {
                    card->removeFromParentAndCleanup(true);
                }
            }
            children.clear();
            _phomsU.clear();
            _eatCard.clear();
            _cards.clear();
            _pairs.clear();
            _phoms.clear();
            _kitSameKind.clear();
            _kitStraight.clear();
            _singleCards.clear();
            setMainCardCount(0);
            remainCard->setString(StringUtils::format("%d",getMainCardCount()));
            remainCard->setPosition(MVec2(width/2-remainCard->getWidth()/2,height/2-remainCard->getHeight()/2));
            
            btnStartMatch->setVisible(this->isCreateRoom() && _lstPlayer.size() > 1);
            spriteFirstTurn->setVisible(false);
        } else {
            this->showToast(prepareNewMatch->message().c_str(), 2);
        }
    }
}

void PhomScene::cancelExitAfterMatchEndResponseHandler() {
	BINCancelExitAfterMatchEndResponse* cancel_exit_room_response =
		(BINCancelExitAfterMatchEndResponse *)Common::getInstance()->checkEvent(NetworkManager::CANCEL_EXIT_ROOM);
	if (cancel_exit_room_response != 0 && cancel_exit_room_response->cancelexituserid()) {
		CCLOG("cancel exit room response: %s", cancel_exit_room_response->DebugString().c_str());
		if (cancel_exit_room_response->responsecode()) {

			long cancelExitUserId = cancel_exit_room_response->cancelexituserid();
			Player* playCancelExitRoom = findPlayer(cancelExitUserId);

			if (playCancelExitRoom != 0){
				/*char message[60];
				sprintf(message, "Người chơi %s hủy đăng kí rời bàn chơi", playCancelExitRoom->getName().c_str());
				this->showToast(message, 2);*/

				Avatar* avatar = findAvatarOfPlayer(cancel_exit_room_response->cancelexituserid());
				if (avatar != 0){
					avatar->showRegisterExitRoom(false);
				}
			}

			// Hung code them phan hien thi hieu ung nguoi choi dang ky roi ban
			// Avatar* avatar = findAvatarOfPlayer(cancel_exit_room_response->cancelexituserid());
			//avatar->hideExitRoom();
		}
		else {
			this->showToast(cancel_exit_room_response->message().c_str(), 2);
		}
	}
}

void PhomScene::kickUserResponseHandler() {
    
}

void PhomScene::readyToPlayResponseHandler() {
    BINReadyToPlayResponse* response =
    (BINReadyToPlayResponse *)Common::getInstance()->checkEvent(NetworkManager::READY_TO_PLAY);
    
    if (response != 0){
        CCLOG("ready to play response: %s", response->DebugString().c_str());
        if (response->responsecode()){
			if (Common::getInstance()->getUserId() == response->readyuserid()){
				btn_san_sang->setVisible(false);
				showBtnWithWatingPlayer(true);
			}
            
            long long ready_player_id = response->readyuserid();
            int table_index = response->tableindex();
            PhomPlayer* player = (PhomPlayer*) findWaiting(ready_player_id);
            
            if (player != 0){
                //day vao lst playing
                PhomPlayer waiting_player = *player;
                waiting_player.setTableIndex(table_index);
                _lstPlayer.push_back(waiting_player);
                
				showInvitePlayer((int)_lstPlayer.size());  //show moi choi

                //remove avatar tren ban choi
                resetDisplayAvatar();
                //dat waiting player len ban choi
                sortListPlayer();
                displayInfoRemainCard(_lstPlayer);
                
                //xoa khoi lst_waiting
                deleteWaitingPlayer(waiting_player.getID());
                
                //hien thi lai danh sach cho len giao dien
                resetListWaiting();
                showWaitingPlayerOnScene(_lstWaiting);
            }
        } else {
            this->showToast(response->message().c_str(), 2);
        }
    }
    
}

void PhomScene::changeRuleResponseHandler() {
    
}

void PhomScene::sortListPlayer() {
    sort(_lstPlayer.begin(), _lstPlayer.end());
}

int PhomScene::findIndexPlayer(vector<PhomPlayer> lstPlayer, Player& player){
    for (int i = 0; i < lstPlayer.size(); i++){
        if (lstPlayer[i].getID() == player.getID()){
            return i;
        }
    }
    return -1;
}

PhomPlayer PhomScene::convertFromBINPlayer(BINPlayer binplayer) {
    char buffer[20];
    sprintf(buffer, "%lld", binplayer.userid());
    std::string uid = std::string(buffer);
    
    int numberCard = 0;
    
    BINMapFieldEntry fieldEntry;
    for (int i = 0; i < binplayer.args_size(); i++){
        fieldEntry = binplayer.args(i);
        if (fieldEntry.key() == TKCurrentCards){
            std::string jsonFieldEntry = fieldEntry.value();
            vector<std::string> lstEntry = Common::getInstance()->split(jsonFieldEntry, ',');
            numberCard = (int)lstEntry.size();
            break;
        }
    }
    
    PhomPlayer player = PhomPlayer(binplayer.username(), uid, numberCard, binplayer.cash(),
                                   binplayer.gold(), 0, binplayer.tableindex(), binplayer.avatarid());
    return player;
}

int PhomScene::getMatchCountDownTime() const {
    return this->_matchCountDownTime;
}

void PhomScene::setMatchCountDownTime(int countDownTime) {
    this->_matchCountDownTime = countDownTime;
}

int PhomScene::getFirstTurnUserId() const {
    return this->_firstTurnUserId;
}

void PhomScene::setFirstTurnUserId(int firstTurnUserId) {
    this->_firstTurnUserId = firstTurnUserId;
}

int PhomScene::getMainCardCount() const {
    return this->_mainCardCount;
}

int PhomScene::getFirstReleaseUserId() const {
    return this->_firstReleaseUserId;
}

void PhomScene::setFirstReleaseUserId(int id) {
    this->_firstReleaseUserId = id;
}

void PhomScene::setMainCardCount(int count) {
    this->_mainCardCount = count;
}

void PhomScene::enterRoomResponseHandler(BINEnterRoomResponse* response) {
    try {
        if (response != 0) {
            
            Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
            if(avatar!=0){
                auto move = MoveTo::create(0.5f,avatar->getAvatarPostion(0, origin, visibleSize, btn_message->getHeight()));
                avatar->runAction(move);
            }
            
            btnStartMatch->setVisible(false);
            
            if (response->has_currentturnuserid()) {
                setCurrentTurnUserId((int)response->currentturnuserid());
            }
            if (response->has_owneruserid()) {
                setOwnerUserId((int) response->owneruserid());
            }
            if (response->has_enterroomstatus() && response->enterroomstatus() == 3) {
                for (int i = 0; i < response->args_size(); i++) {
                    string key = response->args(i).key();
                    string value = response->args(i).value();
                    CCLOG("KEY : %s",key.c_str());
                    if (key == TKCurrentCards) {
                        vector<int> current_card_values =
                        Common::getInstance()->convertStringsToInt(Common::getInstance()->split(value, ','));
                        this->sortCard(current_card_values);
                        
                        // set firstTurn
                        auto ava = findAvatarOfPlayer(getFirstTurnUserId());
                        if(ava != 0){
                            spriteFirstTurn->setPosition(ava->getPosition());
                            spriteFirstTurn->setVisible(true);
                        }
                        btnXepBai->setVisible(true);
                    } else if (key == TKNextAction) {
                        vector<int> nextActions = Common::getInstance()->convertStringsToInt(Common::getInstance()->split(value, ','));
                        for (vector<int>::iterator it = nextActions.begin(); it != nextActions.end(); it++) {
                            switch (*it) {
                                case DANHBAI:
                                    btnDanhBai->setVisible(true);
                                    break;
                                case BOCBAI:
                                    btnBocBai->setVisible(true);
                                    break;
                                case HABAI:
                                    btnHaPhom->setVisible(true);
                                    break;
                                case ANBAI:
                                    btnAnBai->setVisible(true);
                                    break;
                                case GUIBAI:
                                    btnGuiBai->setVisible(true);
                                    break;
                                case U:
                                    btnU->setVisible(true);
                                    break;
                                case TUDONGHA:
                                    break;
                                default:
                                    break;
                            }
                        }
                    } else if (key == "allEatedCards") {
                        CCLOG("ALL EAT CARD");
                        for (string::iterator it = value.begin(); it != value.end(); it++) {
                            if (*it == '\\') {
                                value.erase(it);
                            }
                        }
                        vector<JSONObject> eatedCards = parseJSONString(value);
                        //TODO: thêm các quân bài ăn được vào group tương ứng với các id
                        for (vector<JSONObject>::iterator it = eatedCards.begin(); it != eatedCards.end(); it++) {
                            int userID = Common::getInstance()->convertStringToInt(it->getKey());
                            vector<string> cardsString = Common::getInstance()->split(it->getValue(), ',');
                            vector<int> cards = Common::getInstance()->convertStringsToInt(cardsString);
                            
                            Avatar* avatarEat = findAvatarOfPlayer(userID);
                            if(avatarEat!=0){
                                auto posIndex = avatarEat->getPositionIndex();
                                for(int i = 0 ;i< cards.size();i++){
                                    if (userID == Common::getInstance()->getUserId()) {
                                        CCLOG("CARD-->>> %d",(int)card_tag.size());
                                        for(int j = 0 ; j< card_tag.size();j++){
                                            if(cards[i] == card_tag[j]->getNumberValue()){
                                                auto sprite = getSpriteEatAnimation();
                                                sprite->setTag(1001);
                                                Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(card_tag[j]);
                                                card_tag[j]->addChild(sprite);
                                            }
                                        }
                                    } else {
                                        auto throwCard = OtherCardSprite::createSelf(cards[i],cardWidth()*0.8f);
                                        throwCard->setPosition(getCardCoverPostion(avatarEat));
                                        groupEatCards[posIndex].push_back(throwCard);
                                        int indexCard = (int)groupEatCards[posIndex].size() - 1;
                                        if(groupEatCards[posIndex][indexCard]->getParent() == nullptr)
                                            this->addChild(groupEatCards[posIndex][indexCard],INDEX_AVATAR);
                                    }
                                }
                                for(int i=0;i<groupEatCards[posIndex].size();i++) {
                                    auto postionEatCard = getCardCoverPostion(avatarEat)
                                    + Vec2( (i - (float)(groupEatCards[posIndex].size()-1)/2)*cardWidth()*0.8f*0.3f,
                                           cardWidth()*0.8f*CARD_RATIO*0.5f);
                                    groupEatCards[posIndex][i]->runAction(MoveTo::create(0.2f,postionEatCard));
                                }
                            }
                        }
                    } else if (key == "allTrashCards") {
                        CCLOG("ALL TRASH CARD");
                        vector<JSONObject> throwsCards = parseJSONString(value);
                        //TODO: thêm các quân đánh ra vào group tương ứng với các id
                        for (vector<JSONObject>::iterator it = throwsCards.begin(); it != throwsCards.end(); it++) {
                            int userID = Common::getInstance()->convertStringToInt(it->getKey());
                            vector<string> cardsString = Common::getInstance()->split(it->getValue(), ',');
                            vector<int> cards = Common::getInstance()->convertStringsToInt(cardsString);
                            
                            Avatar* avatarTrash = findAvatarOfPlayer(userID);
                            if(avatarTrash!=0){
                                int posIndex = avatarTrash->getPositionIndex();
                                //getCardCoverPostion(curAvatar)
                                for(int cardValue : cards){
                                    auto throwCard = OtherCardSprite::createSelf(cardValue, cardWidth());
                                    if(userID == Common::getInstance()->getUserId()){
                                        throwCard->setPosition(width/2,btn_message->getPosition().y + btn_message->getHeight());
                                    }else{
                                        throwCard->setPosition(getCardCoverPostion(avatarTrash));
                                    }
                                    int indexCard = (int)groupThrowCards[posIndex].size();
                                    throwCard->setMoveToCenterPhom(posIndex, indexCard, origin, visibleSize, cardWidth());
                                    groupThrowCards[posIndex].push_back(throwCard);
                                    if(groupThrowCards[posIndex][indexCard]->getParent() == nullptr)
                                        this->addChild(groupThrowCards[posIndex][indexCard]);
                                }
                            }
                        }
                    } else if (key == TKMainCardCount) {
                        setMainCardCount(Common::getInstance()->convertStringToInt(value));
                        remainCard->setString(StringUtils::format("%d",getMainCardCount()));
                        remainCard->setPosition(MVec2(width/2-remainCard->getWidth()/2,height/2-remainCard->getHeight()/2));
                    } else if (key == "gameMode") {
                        int gameMode = Common::getInstance()->convertStringToInt(value);
                        CCLOG("GAME MODE ??? : %d",gameMode);
                    }
                }
            }
        }
    } catch (std::exception &e) {
        CCLOG("error message: %s", e.what());
    }
}

int PhomScene::getNextTurnUserId() const {
    return this->_nextTurnUserId;
}

void PhomScene::setNextTurnUserId(int id) {
    this->_nextTurnUserId = id;
}

int PhomScene::getCurrentTurnUserId() const {
    return this->_currentTurnUserId;
}

void PhomScene::setCurrentTurnUserId(int id) {
    this->_currentTurnUserId = id;
}

int PhomScene::getOwnerUserId() const {
    return this->_ownerUserId;
}

void PhomScene::setOwnerUserId(int id) {
    this->_ownerUserId = id;
}

bool PhomScene::sortByValue(const Card &a, const Card &b) {
    return a.getValue() < b.getValue();
}

void PhomScene::throwCard() {
    int throwCardValude = 0;
    for (int i = 0; i < _cards.size(); i++) {
        if (card_tag[i]->getState() == OnHand) {
            throwCardValude = card_tag[i]->getNumberValue();
            break;
        }
    }
    if (throwCardValude > 0 && throwCardValude < 53) {
        std::string cardValue = Common::getInstance()->convertIntToString(throwCardValude);
        turnRequest(DANHBAI, cardValue);
    }
}

void PhomScene::pickCard() {
    turnRequest(BOCBAI);
}

void PhomScene::eatCard(std::string cardValue) {
    turnRequest(ANBAI);
}

void PhomScene::u() {
    turnRequest(U);
}

void PhomScene::consignedCards() {
    int throwCardValude;
    for (int i = 0; i < _cards.size(); i++) {
        if (card_tag[i]->getState() == OnHand) {
            throwCardValude = card_tag[i]->getNumberValue();
            break;
        }
    }
    if (throwCardValude < 0 || throwCardValude > 53) {
        this->showToast("mày không chọn bài đánh thằng thầy mày ah", 2);
    } else {
        std::string cardValue = Common::getInstance()->convertIntToString(throwCardValude);
        turnRequest(GUIBAI, cardValue);
    }
}

void PhomScene::releaseCard(std::string cardsValue) {
    turnRequest(HABAI, cardsValue);
}

void PhomScene::autoReleaseCard() {
    turnRequest(TUDONGHA);
}

void PhomScene::turnRequest(PhomTurnType type) {
    BINMapFieldEntry *entry = new BINMapFieldEntry();
    entry->set_key("action");
    entry->set_value(Common::getInstance()->convertIntToString(type));
    vector<BINMapFieldEntry> entries;
    entries.push_back(*entry);
    NetworkManager::getInstance()->getTurnMessageFromServer(getRoomIndex(), entries);
}

void PhomScene::turnRequest(PhomTurnType type, string data) {
    CCLOG("%d with data %s", type, data.c_str());
    vector<BINMapFieldEntry> entries;
    BINMapFieldEntry *actionEntry = new BINMapFieldEntry();
    actionEntry->set_key("action");
    actionEntry->set_value(Common::getInstance()->convertIntToString(type));
    
    BINMapFieldEntry *dataEntry = new BINMapFieldEntry();
    dataEntry->set_key("data");
    dataEntry->set_value(data);
    entries.push_back(*actionEntry);
    entries.push_back(*dataEntry);
    NetworkManager::getInstance()->getTurnMessageFromServer(getRoomIndex(), entries);
}

void PhomScene::disableAllCardButton() {
    btnAnBai->setVisible(false);
    btnBocBai->setVisible(false);
    btnDanhBai->setVisible(false);
    btnHaPhom->setVisible(false);
    btnGuiBai->setVisible(false);
    btnU->setVisible(false);
}

void PhomScene::initListThrowAndEatenCard() {
    vector<OtherCardSprite*> groupThrowCard;
    vector<OtherCardSprite*> groupEatCard;
    for(int i=0;i<4;i++){
        groupThrowCards[i] = groupThrowCard;
        groupEatCards[i] = groupEatCard;
    }
}

int PhomScene::getTableIndexByUserId(int userId) {
    for(vector<PhomPlayer>::iterator it = _lstPlayer.begin(); it != _lstPlayer.end(); it++) {
        if (Common::getInstance()->convertStringToInt(it->getID()) == userId) {
            return it->getTableIndex();
        }
    }
    return -1;
}

void PhomScene::changeFirstTurnUserIdAfterEatCard() {
    int beforeIndex = getTableIndexByUserId(getFirstTurnUserId());
    int afterIndex = (beforeIndex + 1) > _lstPlayer.size() ? 0 : beforeIndex + 1;
    for (vector<PhomPlayer>::iterator it = _lstPlayer.begin(); it != _lstPlayer.end(); it++) {
        if (it->getTableIndex() == afterIndex) {
            setFirstTurnUserId(Common::getInstance()->convertStringToInt(it->getID()));
            break;
        }
    }
}

void PhomScene::swapCard() {
    refreshCard();
    showInitCard();
}

vector<vector<int>> PhomScene::parseJSONToPair(string data) {
    vector<vector<int>> pairs;
    if (data != "") {
        vector<string> pairString = Common::getInstance()->split(data, ',');
        if (pairString.size() > 0) {
            for (vector<string>::iterator it = pairString.begin(); it != pairString.end(); it ++) {
                vector<string> pairData = Common::getInstance()->split(*it, '-');
                vector<int> pair = Common::getInstance()->convertStringsToInt(pairData);
                if (pair.size() > 0) {
                    pairs.push_back(pair);
                }
            }
        }
    }
    if (pairs.size() > 0) {
        std::sort(pairs.begin(), pairs.end(), [](vector<int> a, vector<int> b) {
            return a[0] < b[0];
        });
    }
    return pairs;
}

void PhomScene::initCardFromInts(vector<int> values) {
    for (vector<int>::iterator it = values.begin(); it != values.end(); it ++) {
        if (checkContainsCard(*it) == -1) {
            Card card;
            card.value = *it;
            _cards.push_back(card);
        }
    }
}

int PhomScene::checkContainsCard(int value){
    for (int i = 0; i < _cards.size(); i++) {
        if (_cards[i].value == value) {
            return i;
        }
    }
    return -1;
}

bool PhomScene::checkContainsCardTag(int value) {
    for (int i = 0; i < card_tag.size(); i++) {
        if (card_tag[i]->getNumberValue() == value) {
            return true;
        }
    }
    return false;
}

void PhomScene::turnTypeResponse(float duration,string data,bool canEat) {
    Avatar* curAvatar = findAvatarOfPlayer(getCurrentTurnUserId());
    
    if(curAvatar == 0) {
        return;
    }
    
    int posIndex = curAvatar->getPositionIndex();
    
    if (_turnType == DANHBAI) {
        refreshCard();
        int cardValue = Common::getInstance()->convertStringToInt(data);
        if (getCurrentTurnUserId() == Common::getInstance()->getUserId()) {
            for (int i = (int)card_tag.size() - 1; i >= 0; i --) {
                if (card_tag[i]->getNumberValue() == cardValue) {
                    auto throwCard = OtherCardSprite::createSelf(cardValue, cardWidth());
                    throwCard->setPosition(card_tag[i]->getPosition());
                    int indexCard = (int)groupThrowCards[posIndex].size();
                    throwCard->setMoveToCenterPhom(posIndex, indexCard, origin, visibleSize, cardWidth());
                    groupThrowCards[posIndex].push_back(throwCard);
                    if(groupThrowCards[posIndex][indexCard]->getParent() == nullptr)
                        this->addChild(groupThrowCards[posIndex][indexCard]);
                    break;
                }
            }
            this->removeCardAfterThrow(cardValue);
            this->sortCard();
        }else{
            auto throwCard = OtherCardSprite::createSelf(cardValue,cardWidth());
            throwCard->setPosition(getCardCoverPostion(curAvatar));
            int indexCard = (int)groupThrowCards[posIndex].size();
            throwCard->setMoveToCenterPhom(posIndex, indexCard, origin, visibleSize, cardWidth());
            groupThrowCards[posIndex].push_back(throwCard);
            if(groupThrowCards[posIndex][indexCard]->getParent() == nullptr)
                this->addChild(groupThrowCards[posIndex][indexCard]);
            
            if(getNextTurnUserId() == Common::getInstance()->getUserId() && canEat) { //highlight quan bai duoc an
                auto sprite = getSpriteEatAnimation();
                sprite->setTag(1001);
                Size cardSize = groupThrowCards[posIndex][groupThrowCards[posIndex].size() - 1]->getContentSize();
                groupThrowCards[posIndex][groupThrowCards[posIndex].size() - 1]->addChild(sprite);
                groupThrowCards[posIndex][groupThrowCards[posIndex].size() - 1]->setHighLight(true);
            }
        }
        for(int i = 0 ;i< groupThrowCards[posIndex].size();i++){
            if(i != groupThrowCards[posIndex].size()-1){
                groupThrowCards[posIndex][i]->showHidden(true);
            }
        }
    } else if (_turnType == BOCBAI) {
        refreshCard();
        remainCard->setString(StringUtils::format("%d",getMainCardCount()));
        remainCard->setPosition(MVec2(width/2-remainCard->getWidth()/2,height/2-remainCard->getHeight()/2));
        if (getNextTurnUserId() == Common::getInstance()->getUserId()) {
            auto previousAvatar = findAvatarOfPlayer(getPreviousTurnUserId());
            if(previousAvatar!=0){
                int _previousPosition = previousAvatar->getPositionIndex();
                if(groupThrowCards[_previousPosition].size()>0){
                    auto card = groupThrowCards[_previousPosition][groupThrowCards[_previousPosition].size() - 1];
                    if(card->getHighLight()){
                        if(card->getChildByTag(1001) != nullptr){
                            card->removeChildByTag(1001);
                        }
                    }
                }
            }
            
            int cardValue = Common::getInstance()->convertStringToInt(data);
            addNewCardIntoCardTag(MVec2(width/2, height/2),cardValue);
        } else {
            auto cardFromCenterToUser = OtherCardSprite::createCardCover(cardWidth());
            cardFromCenterToUser->setMoveFromToPhom(MVec2(width/2,height/2),getCardCoverPostion(curAvatar));
            this->addChild(cardFromCenterToUser);
        }
    } else if (_turnType == ANBAI) {
        refreshCard();
        auto an_animation = getFrameAnimation("an_%02d.png", 18);
        auto sprite = Sprite::createWithSpriteFrame(an_animation.front());
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(MVec2(width/2-sprite->getContentSize().width/2,
                                  height/2 - sprite->getContentSize().height/2));
        auto animation = Animation::createWithSpriteFrames(an_animation, 1.0f/10);
        auto repeat = Animate::create(animation);
        sprite->runAction(Sequence::create(repeat,RemoveSelf::create(),NULL));
        this->addChild(sprite,INDEX_ANIMATION);
        
        auto previousAvatar = findAvatarOfPlayer(getPreviousTurnUserId());
        if(previousAvatar!=0){
            int _previousPosition = previousAvatar->getPositionIndex();
            int pos = (int)groupThrowCards[_previousPosition].size() - 1;
            
            int cardValue = Common::getInstance()->convertStringToInt(data);
            _eatCard.push_back(cardValue);
            CCLOG("AN BAI : %d ",cardValue);
            if (getCurrentTurnUserId() == Common::getInstance()->getUserId()) {
                addNewCardIntoCardTag(groupThrowCards[_previousPosition][pos]->getPosition(),cardValue);
                auto sprite = getSpriteEatAnimation();
                sprite->setTag(1001);
                Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(card_tag[card_tag.size() -1]);
                card_tag[card_tag.size() -1]->addChild(sprite);
                groupThrowCards[_previousPosition][pos]->removeFromParentAndCleanup(true);
                groupThrowCards[_previousPosition].erase(groupThrowCards[_previousPosition].begin() + pos);
            } else {
                auto throwCard = OtherCardSprite::createSelf(cardValue,cardWidth()*0.8f);
                throwCard->setPosition(groupThrowCards[_previousPosition][pos]->getPosition());
                groupEatCards[posIndex].push_back(throwCard);
                int indexCard = (int)groupEatCards[posIndex].size() - 1;
                if(groupEatCards[posIndex][indexCard]->getParent() == nullptr)
                    this->addChild(groupEatCards[posIndex][indexCard],INDEX_AVATAR);
                
                for(int i=0;i<groupEatCards[posIndex].size();i++) {
                    auto postionEatCard = getCardCoverPostion(curAvatar)
                    + Vec2( (i - (float)(groupEatCards[posIndex].size()-1)/2)*throwCard->getWidth()*0.3f,
                           throwCard->getHeight()*0.5f);
                    groupEatCards[posIndex][i]->runAction(MoveTo::create(0.2f,postionEatCard));
                }
                groupThrowCards[_previousPosition][pos]->removeFromParentAndCleanup(true);
                groupThrowCards[_previousPosition].erase(groupThrowCards[_previousPosition].begin() + pos);
            }
        }else{
            setPreviousTurnUserId(getCurrentTurnUserId());
        }
        
    } else if (_turnType == HABAI || _turnType == TUDONGHA) {
        //TODO: xử lý phần hạ bài
        //các phỏm được hạ được show ra ở vị trí người hạ
        //nếu là người chơi thì xoá quân bài đã hạ
        log("ha bai %s", data.c_str());
        
        /*for(int i = 0; i < avatars.size();i++){
            avatars[i]->hideCardCover();
        }*/
        
        //curAvatar->hideCardCover(true);
        
        //hide throwcard
        for(std::vector<OtherCardSprite*> groupCards : groupThrowCards){
            for(OtherCardSprite* card : groupCards){
                card->showHidden(true);
            }
        }
        
        for(OtherCardSprite* card : groupEatCards[posIndex]){
            card->removeFromParentAndCleanup(true);
        }
        groupEatCards[posIndex].clear();
        
        vector<vector<int>> phoms = parseJSONToPair(data);  //số phỏm đã hạ tự động
        if (Common::getInstance()->getUserId() == getCurrentTurnUserId()) {
            vector<OtherCardSprite*> _haphom;
            for(int i =0;i<phoms.size();i++){
                _haphom.clear();
                for(int j =0;j<phoms[i].size();j++){
                    auto card = OtherCardSprite::createSelf(phoms[i][j], cardWidth()*0.8f);
                    card->setPosition(getCardCoverPostion(curAvatar));
                    
                    card->setMoveHaBaiPhom(curAvatar->getPosition()+Vec2(curAvatar->getContentSize().width/2,
                                                                         curAvatar->getContentSize().height*0.6f),
                                           posIndex,j, (int)phoms.size(),i, origin,visibleSize,cardWidth()*0.8f,false);
                    _haphom.push_back(card);
                    
                    //delete card on hand
                    for (int k = 0; k < card_tag.size(); k++) {
                        if (card_tag[k]->getNumberValue() == phoms[i][j]) {
                            this->removeChild(card_tag[k]);
                            card_tag.erase(card_tag.begin() + k);
                            break;
                        }
                    }
                    
                    for (int k = 0; k < _cards.size(); k++) {
                        if (_cards[k].getValue() == phoms[i][j]) {
                            _cards.erase(_cards.begin() + k);
                            break;
                        }
                    }
                    checkContaintCardInPair(_phoms, phoms[i][j]);
                    checkContaintCardInPair(_pairs, phoms[i][j]);
                    for (int k = 0; k < _singleCards.size(); k++) {
                        if (_singleCards[k] == phoms[i][j]) {
                            _singleCards.erase(_singleCards.begin()+ k);
                        }
                    }
                }
                if(_haphom.size()>0) {
                    groupHaBaiCards[posIndex].push_back(_haphom);
                }
            }
            
            for(int i=0;i<groupHaBaiCards[posIndex].size();i++){
                for(int j = 0;j < groupHaBaiCards[posIndex][i].size();j++) {
                    if(groupHaBaiCards[posIndex][i][j]->getParent() == nullptr) {
                        this->addChild(groupHaBaiCards[posIndex][i][j]);
                        
                        //highlight quan bai duoc an
                        for(int cardHighLight : _eatCard){
                            if(cardHighLight == groupHaBaiCards[posIndex][i][j]->getValue()){
                                auto sprite = getSpriteEatAnimation();
                                sprite->setLocalZOrder(j+i*4+2);
                                groupHaBaiCards[posIndex][i][j]->addChild(sprite);
                            }
                        }
                        groupHaBaiCards[posIndex][i][j]->setLocalZOrder(j+i*4+1);
                    }
                }
            }
            this->sortCardAfterMoveCardToCenter();
//            _phoms.clear();
//            for (int i = 0; i < _pairs.size(); i++) {
//                if (checkContaintCardInPair(phoms, _pairs[i][0])) {
//                    if (_pairs[i].size() > 1 && !checkContaintCardInPair(phoms, _pairs[i][1])) {
//                        int single = _pairs[i][1];
//                        _singleCards.push_back(single);
//                    }
//                    _pairs.erase(_pairs.begin() + i);
//                } else {
//                    if (_pairs[i].size() > 1 && checkContaintCardInPair(phoms, _pairs[i][1])) {
//                        int single = _pairs[i][0];
//                        _singleCards.push_back(single);
//                        _pairs.erase(_pairs.begin() + i);
//                    }
//                }
//            }
        } else {
            //các phỏm được hạ được show ra ở vị trí người hạ mỗi phỏm trên 1 hàng
            //...
            vector<OtherCardSprite*> _haphom;
            for(int i = 0;i < phoms.size();i++) {
                _haphom.clear();
                for(int j = 0;j<phoms[i].size();j++) {
                    auto card = OtherCardSprite::createSelf(phoms[i][j], cardWidth()*0.8f);
                    card->setPosition(getCardCoverPostion(curAvatar));
                    
                    Vec2 pos = Vec2(curAvatar->getPosition()+Vec2(curAvatar->getContentSize().width /2,
                                                                  curAvatar->getContentSize().height*0.6f));
                    if(posIndex == 2){
                        pos = curAvatar->getPosition() + Vec2(-2.5f*cardWidth()*0.8f + (i -1)*cardWidth()*0.5f,0);
                    }
                    card->setMoveHaBaiPhom(pos,posIndex,j, (int)phoms.size(),i,
                                           origin,visibleSize,cardWidth()*0.8f,true);
                    _haphom.push_back(card);
                }
                if(_haphom.size()>0){
                    groupHaBaiCards[posIndex].push_back(_haphom);
                }
            }
            
            for(int i=0;i<groupHaBaiCards[posIndex].size();i++){
                for(int j = 0;j < groupHaBaiCards[posIndex][i].size();j++){
                    if(groupHaBaiCards[posIndex][i][j]->getParent() == nullptr){
                        this->addChild(groupHaBaiCards[posIndex][i][j]);
                        
                        //highlight quan bai duoc an
                        for(int cardHighLight : _eatCard){
                            if(cardHighLight == groupHaBaiCards[posIndex][i][j]->getValue()){
                                auto sprite = getSpriteEatAnimation();
                                sprite->setLocalZOrder(j+i*4+2);
                                groupHaBaiCards[posIndex][i][j]->addChild(sprite);
                            }
                        }
                        groupHaBaiCards[posIndex][i][j]->setLocalZOrder(j+i*4+1);
                    }
                }
            }
        }
        
    } else if (_turnType == GUIBAI) {
        
        //TODO: xử lý phần gửi bài
        vector<string> guibaiData = Common::getInstance()->split(data, '-');
        int userID = Common::getInstance()->convertStringToInt(guibaiData[0]);
        int considerCard = Common::getInstance()->convertStringToInt(guibaiData[1]);
        vector<string> phomString = Common::getInstance()->split(guibaiData[2], ',');
        vector<int> phom = Common::getInstance()->convertStringsToInt(phomString);
        Avatar* userToiAvatar = findAvatarOfPlayer(userID);
        if(userToiAvatar==0){
            return;
        }
        int posIndex = userToiAvatar->getPositionIndex();
        
        vector<vector<int>> _phom;
        for(vector<OtherCardSprite*> groupCards : groupHaBaiCards[posIndex]) {
            vector<int> _phomx;
            for(OtherCardSprite* cardx : groupCards) {
                _phomx.push_back(cardx->getValue());
            }
            
            _phom.push_back(_phomx);
        }
        
        int indexPhom = 0;
        int cardGuiBaiIndex = 0;
        for(int j = 0;j< _phom.size();j++){
            std::sort(_phom[j].begin(),_phom[j].begin()+_phom[j].size());
            if(phom == _phom[j]){
                indexPhom = j;
                _phom[j].push_back(considerCard);
                if(considerCard < _phom[j][0]){
                    cardGuiBaiIndex = 0;
                }else {
                    cardGuiBaiIndex = (int)_phom[j].size();
                }
                std::sort(_phom[j].begin(),_phom[j].begin()+_phom[j].size());
                break;
            }
        }
        
        Vec2 pos = userToiAvatar->getPosition()+Vec2(userToiAvatar->getContentSize().width /2,
                                                     userToiAvatar->getContentSize().height*0.6f);
        if(posIndex == 2){
            pos = userToiAvatar->getPosition() + Vec2(-2.5f*cardWidth()*0.8f - 3*cardWidth()*0.5f , 0);
        }
        
        auto callBackFunc = CallFunc::create([=](){
            CCLOG("index phom : %d",indexPhom);
            auto cardx = OtherCardSprite::createSelf(considerCard, cardWidth()*0.8f);
            cardx->setPosition(Vec2(pos.x+(cardGuiBaiIndex - 2) *cardWidth()*0.8f*0.5f,
                                    groupHaBaiCards[posIndex][indexPhom][0]->getPosition().y));
            cardx->runAction(ScaleBy::create(0.1f, 0.8f));
            groupHaBaiCards[posIndex][indexPhom].push_back(cardx);
            int cardIndex = (int)groupHaBaiCards[posIndex][indexPhom].size() -1;
            this->addChild(groupHaBaiCards[posIndex][indexPhom][cardIndex]);
            groupHaBaiCards[posIndex][indexPhom][cardIndex]->setLocalZOrder(indexPhom*4+cardGuiBaiIndex+1);
            
            int sizePhom = (int)_phom[indexPhom].size();
            for(int t = 0;t<sizePhom ;t++) {
                for(int k = 0;k < groupHaBaiCards[posIndex][indexPhom].size();k++) {
                    if(groupHaBaiCards[posIndex][indexPhom][k]->getValue() == _phom[indexPhom][t]){
                        groupHaBaiCards[posIndex][indexPhom][k]->setLocalZOrder(indexPhom*4+t+1);
                        groupHaBaiCards[posIndex][indexPhom][k]
                        ->setPosition(Vec2(pos.x+(t - sizePhom/2.0f) *cardWidth()*0.8f*0.5f,
                                           groupHaBaiCards[posIndex][indexPhom][0]->getPosition().y));
                        break;
                    }
                }
            }
            for (int i = 0; i < _pairs.size(); i++) {
                if (_pairs[i][0] == considerCard) {
                    if (_pairs[i].size() > 1) {
                        int single = _pairs[i][1];
                        _singleCards.push_back(single);
                    }
                    _pairs.erase(_pairs.begin() + i);
                } else {
                    if (_pairs[i].size() > 1 && _pairs[i][1] == considerCard) {
                        int single = _pairs[1][0];
                        _singleCards.push_back(single);
                        _pairs.erase(_pairs.begin() + i);
                    }
                }
            }
            this->removeCardAfterThrow(considerCard);
            this->sortCard();
        });
        
        if (getCurrentTurnUserId() == Common::getInstance()->getUserId()) {
            //di chuyển quân bài từ bộ bài của mình về phía phỏm được gửi, xoá quân bài khỏi bộ bài
            //....
            
            for(int i =0; i < (int)card_tag.size(); i++) {
                if(card_tag[i]->getNumberValue() == considerCard) {
                    
                    auto card = OtherCardSprite::createSelf(considerCard, cardWidth());
                    card->setPosition(card_tag[i]->getPosition());
                    auto move = MoveTo::create(0.2f,pos);
                    card->runAction(Sequence::create(move,callBackFunc,RemoveSelf::create(),NULL));
                    this->addChild(card);
                    
                    break;
                }
            }
        }else {
            //di chuyển quân bài từ phía thằng gủi về phía phỏm được gửi
            auto cardFromTo = OtherCardSprite::createSelf(considerCard,cardWidth());
            cardFromTo->setPosition(getCardCoverPostion(curAvatar));
            cardFromTo->runAction(Sequence::create(MoveTo::create(0.2f,getCardCoverPostion(userToiAvatar)),
                                                   callBackFunc,RemoveSelf::create(),NULL));
            this->addChild(cardFromTo);
        }
        
    } else if (_turnType == U) {
        _phomsU = parseJSONToPair(data);
        this ->showToast("có thằng ù con mẹ nó rùi", 2);
    }
}

void PhomScene::addNewCardIntoCardTag(Vec2 postion,int value){
    Card cardx;
    cardx.setValue(value);
    PositionIndex positionIndex;
    positionIndex.x = 9;
    positionIndex.y = 0;
    auto cardSprite = CardSprite::create(cardx,positionIndex,this->cardWidth(),this);
    cardSprite->setPosition(postion);
    card_tag.push_back(cardSprite);
    int posIndex = (int)card_tag.size() -1;
    card_tag[posIndex]->runAction(MoveTo::create(0.2f,Vec2(originX + width/2+ (posIndex- 4)*cardWidth(),
                                                           card_tag[0]->posY)));
    card_tag[posIndex]->setPosY(card_tag[0]->posY);
    this->addChild(card_tag[posIndex],INDEX_CARD);
}

Sprite* PhomScene::getSpriteEatAnimation() {
    Vector<SpriteFrame*> frames = getFrameAnimation("eat_%d.png",6);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setAnchorPoint(Point::ZERO);
    auto animation = Animation::createWithSpriteFrames(frames,0.3f);
    auto repeat =  RepeatForever::create(Animate::create(animation));
    sprite->runAction(repeat);
    return sprite;
}

void PhomScene::setPreviousTurnUserId(int _previousTurnUserId){
    this->_previousTurnUserId = _previousTurnUserId;
}

int PhomScene::getPreviousTurnUserId() const {
    return _previousTurnUserId;
}

Player* PhomScene::findPlayer(long long player_id){
    char c_player_id[50];
    sprintf(c_player_id, "%lld", player_id);
    
    std::string s_player_id = std::string(c_player_id);
    
    for (int i = 0; i < _lstPlayer.size(); i++){
        if (_lstPlayer[i].getID() == s_player_id){
            return &_lstPlayer[i];
        }
    }
    
    return NULL;
}

//tim nguoi cho
Player* PhomScene::findWaiting(long long player_id){
    char c_player_id[50];
    sprintf(c_player_id, "%lld", player_id);
    std::string s_player_id = std::string(c_player_id);
    
    for (int i = 0; i < _lstWaiting.size(); i++){
        if (_lstWaiting[i].getID() == s_player_id){
            return &_lstWaiting[i];
        }
    }
    return NULL;
}

void PhomScene::deleteWaitingPlayer(string player_id){
    int k = -1;
    for (int i = 0; i < _lstWaiting.size(); i++){
        if (_lstWaiting[i].getID() == player_id){
            k = i;
        }
    }
    
    if (k != -1 && !_lstWaiting.empty())
        _lstWaiting.erase(_lstWaiting.begin() + k);
}

vector<JSONObject> PhomScene::parseJSONString(string json) {
    vector<JSONObject> result;
    Document document;
    document.Parse(json.c_str());
    for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
         itr != document.MemberEnd(); itr++) {
        string key = itr->name.GetString();
        string val = itr->value.GetString();
        result.push_back(JSONObject(key, val));
    }
    return result;
}

void PhomScene::refreshCard() {
    _cards.clear();
    if(_phoms.size() > 0) {
        for(vector<vector<int>>::iterator it = _phoms.begin(); it != _phoms.end(); it ++) {
            initCardFromInts(*it);
        }
    }
    if (_pairs.size() > 0) {
        for (vector<vector<int>>::iterator it = _pairs.begin(); it != _pairs.end(); it ++) {
            initCardFromInts(*it);
        }
    }
    if (_singleCards.size() > 0) {
        initCardFromInts(_singleCards);
    }
}

void PhomScene::resetDisplayAvatar(){
    if (!avatars.empty()){
        for (int i = 0; i < avatars.size(); i++){
            if (avatars[i]->getParent() != nullptr){
                this->removeChild(avatars[i]);
            }
        }
        avatars.clear();
    }
}

void PhomScene::displayInfoRemainCard(vector<PhomPlayer> &remain_card_infos) {
    currentIndex = -1;
    currentTableIndex = -1;
    
    for (int i = 0; i < remain_card_infos.size(); i++)  {
        int val;
        std::stringstream ss(remain_card_infos[i].getID());
        ss >> val;
        if (Common::getInstance()->getUserId() == val) {
            currentIndex = i;
            currentTableIndex = remain_card_infos[i].getTableIndex();
            break;
        }
    }
    //end find current index
    
    CCLOG("list player size: %lu", remain_card_infos.size());
    
    //int index = currentIndex;
    int len = (int) remain_card_infos.size();
    
    for (int i = 0; i < len; i++) {
        setPositionPlayer(remain_card_infos[i]);
    }
}

void PhomScene::setPositionPlayer(PhomPlayer& player){
    
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
    
    int _numberCard = player.getNumberCard();
    string user_name = player.getName();
    string user_id = player.getID();
    long long gold = player.getGold();
    long long cash = player.getCash();
    
    //char buffer[20];
    std::string buffer = StringUtils::format("%lld $", is_vip_room ? cash : gold);
    
    //sprintf(buffer, "%lld $", is_vip_room ? cash : gold);
    
    int image_index = player.getAvatarId();
    
    avatar->loadAvatar(image_index, user_id, user_name, buffer, roomIndex);
    auto pos = avatar->getAvatarPostion(position_index, origin, visibleSize, btn_message->getHeight());
    if(position_index == 0){
        pos = MVec2(width/2 - avatar->getContentSize().width/2,pos.y);
    }
    avatar->setPosition(pos);
    
    double cardCoverWidth = cardWidth() * 0.8f;
    
    avatar->loadCardCover(cardCoverWidth, position_index, _numberCard);
    if (position_index == 0) {
        avatar->hiddenNumberCardAndCover(true);
    }else{
        avatar->hideNumberCard(true);
    }
    
    avatars.push_back(avatar);
    
    if (avatar->getParent() == nullptr)
        this->addChild(avatar,1);
}

void PhomScene::checkContaintCardInPair(vector<vector<int>> &pair, int cardvalue) {
    for (int i = 0; i < pair.size(); i++) {
        for (int j = 0; j < pair[i].size(); j++) {
            if (pair[i][j] == cardvalue) {
                pair[i].erase(pair[i].begin() + j);
                if (pair[i].size() == 0) {
                    pair.erase(pair.begin() + i);
                }
                break;
            }
        }
    }
}

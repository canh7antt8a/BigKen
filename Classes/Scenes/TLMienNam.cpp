#include "TLMienNam.h"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Common.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "Handler/TLMNCardHandler.h"
#include <algorithm>
#include "Scenes/SceneTable.hpp"
#include "Utils/Utility.h"
#include "Objects/PositionPlayer.h"

#include "Utils/Utility.h"
#include "Utils/SoundManager.h"
#include "Utils/SoundConfig.h"
#include "Utils/AnimationManager.hpp"

#define DEBUG 1

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

#define padding 20

#define CARD_SHOWING_ZORDER 1

#define CARD_SUIT_TYPE_NUM 4 // Loại bài trong bộ
#define CARD_NUM_OF_SUIT 13 // Số quân bài trong 1 loại

#define CARD_X_NUM 13 // rows
#define CARD_MARGIN 10 // Khoảng cách giữa các thẻ

int enter_room_status = 0;

void TLMienNam::parseRemainCards(string json) {
    try {
        Document document;
        document.Parse(json.c_str());
        int index = 0;
        for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
            itr != document.MemberEnd(); ++itr) {

            string key = itr->name.GetString();
            int val = itr->value.GetInt();
            char buffer[20];
            sprintf(buffer, "%d", Common::getInstance()->getUserId());
            std::string str_buffer = std::string(buffer);
            int k = -1;
            for (int i = 0; i < lst_player.size(); i++) {
                if (lst_player[i].getID() == key) {
                    k = i;
                    break;
                }
            }
            if (k != -1) {
                //Player player("", key, val, 0, 0, index, 0);
                lst_player[k].setNumberCard(val);

                long long player_id;
                std::stringstream ss(lst_player[k].getID());
                ss >> player_id;
				Avatar* avatar = findAvatarOfPlayer(player_id);
				if (avatar != 0){
					avatar->setNumberCard(val);
				}
            }
            
           // result.push_back(player);
            // if (str_buffer == key) currentIndex = index;
            index++;
        }
    }
    catch (const std::exception &e) {
        CCLOG("error: %s", e.what());
    }
}

//int roomIndex;
int TLMNgameTag;
bool isDisplayRoomList;

Scene* TLMienNam::createScene(int _roomIndex, vector<BINPlayer> _playerList, vector<BINPlayer> _waitingPlayerList,
	bool _createRoom, int _gameTag, bool _isDisplayRoomList, bool passwordRequired, bool isVipRoom, int minBet,
	std::string cardRemainingCount, BINEnterRoomResponse* reEnterRoomResponse) {
    // 'scene' is an autorelease object
    //roomIndex = _roomIndex;
    TLMNgameTag = _gameTag;
    
    // 'layer' is an autorelease object
    auto scene = Scene::create();
    auto layer = TLMienNam::create();
    layer->setCreateRoom(_createRoom);
	layer->setVipRoom(isVipRoom);
    layer->setRoomIndex(_roomIndex);
    layer->setPassWordRequired(passwordRequired);
    layer->setDisplayRoomList(_isDisplayRoomList);
    layer->setPlayerList(_playerList);
    layer->setWaitingPlayerList(_waitingPlayerList);
    layer->setEnterRoomResponse(reEnterRoomResponse);
	layer->setMinBet(minBet);
    layer->initMenu();
	layer->initGame(cardRemainingCount);
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TLMienNam::init() {
    if (!PlayScene::init() ) {
        return false;
    }

    capacity_size = 4;

    /*this->initMenu();
    this->initGame();*/

    //Load audio
    this->scheduleUpdate();
    
    return true;
}

void TLMienNam::setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list,
	std::string cardRemainingCount) {

    if (lst_player.size() > 0) lst_player.clear();
    for (int i = 0; i < player_list.size(); i++) {
        TLMNPlayer player = convertFromBINPlayer(player_list[i]);
        lst_player.push_back(player);
    }

    for (int i = 0; i < waiting_player_list.size(); i++) {
        TLMNPlayer player = convertFromBINPlayer(waiting_player_list[i]);
        lst_waiting.push_back(player);
    }

    if (is_create_room){
        btn_san_sang->setVisible(false);
    }
    else {
        if (isUserPlaying()){
			showInvitePlayer(lst_player.size());
            btn_san_sang->setVisible(false);
		}
		else {
			showBtnWithWatingPlayer(false);
		}
    }

	if (!cardRemainingCount.empty()){
		parseRemainCards(cardRemainingCount);
	}

    showWaitingPlayerOnScene(lst_waiting);

    //sap xep lai lst_player theo table_index
    sortListPlayer();
    
    //hien thi avatar cua nhung nguoi join vao phong
    displayInfoRemainCard(lst_player);
}

void TLMienNam::initMenu(){
    PlayScene::initMenu();

    auto bkgTable = MSprite::create("sprite_table.png");
    bkgTable->setScale(width*0.8f/bkgTable->getWidth());
    bkgTable->setContentSize(Size(width*0.8f, bkgTable->getHeight()*bkgTable->getScale()));
    bkgTable->setPosition(Point(origin.x+visibleSize.width/2-bkgTable->getWidth()/2,
                                origin.y+visibleSize.height/2-bkgTable->getHeight()/2));
    
    //================ play game button
    
    menu_click = false;

    btn_danh_bai = MButton::create("btn_danhbai.png","Đánh bài",25,TAG_TLMN_BTN_DANHBAI);
    btn_danh_bai->setPosition(Vec2(origin.x+width*0.75f-btn_danh_bai->getWidth()/2,origin.y+padding/2));
    btn_danh_bai->addTouchEventListener(CC_CALLBACK_2(TLMienNam::cardCallBack,this));
    btn_danh_bai->setVisible(false);

    btn_start_match = MButton::create(BTN_START_MATCH, "Bắt đầu", 25, TAG_TLMN_START_MATCH);
    //btn_start_match->setAnchorPoint(Vec2(0.5f, 0.5f));
    btn_start_match->setPosition(Vec2(origin.x + visibleSize.width*0.4f - btn_start_match->getWidth() / 2,
        btn_danh_bai->getPosition().y));
    btn_start_match->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack, this));
    btn_start_match->setVisible(is_create_room && player_list.size() >= 2);

    btn_bo_luot = MButton::create("btn_boluot.png", "Bỏ lượt", 25, TAG_TLMN_BTN_BOLUOT);
    btn_bo_luot->setPosition(Vec2(origin.x+visibleSize.width*0.4f-btn_bo_luot->getWidth()/2,
                                  btn_danh_bai->getPosition().y));
    btn_bo_luot->addTouchEventListener(CC_CALLBACK_2(TLMienNam::cardCallBack, this));
    btn_bo_luot->setVisible(false);
    
    btn_san_sang = MButton::create(BTN_BUTTON, "Sẵn sàng", 25, TAG_TLMN_BTN_SANSANG);
    btn_san_sang->setPosition(Vec2(btn_message->getPosition().x - btn_san_sang->getWidth() - padding,
                                   btn_message->getPosition().y));
    btn_san_sang->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack, this));

    this->addChild(bkgTable);
    
    this->addChild(btn_danh_bai);
    this->addChild(btn_bo_luot);
    this->addChild(btn_start_match);
    this->addChild(btn_san_sang);
}

void TLMienNam::onEvent(int value){
    if(!lastCards.empty()){
        vector<int> allSuggest = TLMNCardHandler::getInstance()->getAllSuggessCard(this->cardTagToInts(card_tag), lastCards);
        vector<int> suggest = TLMNCardHandler::getInstance()->findSuggessCardByTurn(allSuggest, lastCards, value);
        
        for(int index : suggest) {
            CCLOG("suggest : %d",index);
        }
        
        for(CardSprite* card : card_tag){
            if(card->getState() != OnTable) {
                for(int index : suggest) {
                    if(index != value && index == card->getNumberValue()) {
                        card->setSuggest(true);
                    }
                }
            }
        }
        
        int count =0;
        for(CardSprite* card : card_tag) {
            if(card->getState() != OnTable) {
                if(card->getNumberValue() != value) {
                    if(card->getSuggest() == true) {
                        count++;
                        CCLOG("ONHAND");
                        card->setMoveUp(count);
                    }else {
                        CCLOG("IDLE");
                        card->setMoveDown();
                    }
                    card->setSuggest(false);
                }
            }
        }
    }
}

void TLMienNam::initGame(std::string cardRemainingCount){
    if (is_create_room){
        int current_user_id = Common::getInstance()->getUserId();
        setOwnerUserId(current_user_id);
    }

	setListPlayerFromParams(TLMienNam::player_list, TLMienNam::waiting_player_list, cardRemainingCount);
    if (enter_room_response != 0) {
        handleReEnterRoom(enter_room_response);
    }
}

void TLMienNam::createCards(PositionIndex positionIndex, int tag){
    auto cardx = cards[positionIndex.x];
    auto cardSprite = CardSprite::create(cardx,positionIndex,this->cardWidth(),this);
    cardSprite->addHidden();

    cardSprite->setPosition(MVec2(visibleSize.width/2,
                                 visibleSize.height/2));
    cardSprite->setTag(cardx.value);

    this->card_tag.push_back(cardSprite);
}

void TLMienNam::showInitCard() {
    for (int i = 0; i < cards.size(); i++){
        PositionIndex positionIndex;
        positionIndex.x = i;
        positionIndex.y = 0;
        this->createCards(positionIndex, i);
        if (card_tag[i]->getParent() == nullptr)
            this->addChild(card_tag[i]);
    }
    // play sound chiabai
    SoundManager::getInstance()->playSound(soundTLMN[37]);
    CCLOG("card tag size: %lu", card_tag.size());
    for(int i = 0; i < card_tag.size();i++){
        //auto delay = DelayTime::create(1.0f);

        auto moveTo = MoveTo::create(0.2f+0.06f*i,MVec2(visibleSize.width/2 + (i-(float)(card_tag.size()-1)/2) * cardWidth(),
                                                 5+btn_message->getHeight()*1.5f + cardWidth() *71/106));
        
        //auto sequence = Sequence::create(delay,moveTo, NULL);
        card_tag[i]->runAction(moveTo);
        card_tag[i]->setPosY(originY + 5 + btn_message->getHeight()*1.5f + cardWidth() *71/106);
    }
}

bool TLMienNam::isMatchEnd() const {
    return _matchEnd;
}

void TLMienNam::setMatchEnd(bool _matchEnd) {
    this->_matchEnd = _matchEnd;
}

void TLMienNam::setTurnCountDownTime(int _countDownTime) {
    this->_turnCountDownTime = _countDownTime;
}

int TLMienNam::getTurnCountDownTime() const {
    return _turnCountDownTime;
}

void TLMienNam::setMatchCountDownTime(int _countDownTime) {
    this->_matchCountDownTime = _countDownTime;
}

int TLMienNam::getMatchCountDownTime() const {
    return _matchCountDownTime;
}

void TLMienNam::setCurrentTurnUserId(int _currentTurnUserId) {
    this->_currentTurnUserId = _currentTurnUserId;
}

int TLMienNam::getCurrentTurnUserId() const {
    return _currentTurnUserId;
}

void TLMienNam::setNextTurnUserId(int _nextTurnUserId) {
    this->_nextTurnUserId = _nextTurnUserId;
}

int TLMienNam::getNextTurnUserId() const {
    return _nextTurnUserId;
}

void TLMienNam::setFirstTurnUserId(int _firstTurnUserId) {
    this->_firstTurnUserId = _firstTurnUserId;
}

int TLMienNam::getFirstTurnUserId() const {
    return _firstTurnUserId;
}

void TLMienNam::handleReEnterRoom(BINEnterRoomResponse* response) {
    try  {
        if (response != 0) {
            CCLOG("enter room response: %s", response->DebugString().c_str());
            if(response->has_currentturnuserid()) {
                setCurrentTurnUserId((int)response->currentturnuserid());
                btn_start_match->setVisible(false);
            }
            setOwnerUserId((int)response->owneruserid());
            int sizeCard = 0;
            //an nut start match di
            btn_start_match->setVisible(false);
            Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
			if (avatar != 0){
				avatar->runAction(MoveTo::create(0.5f, avatar->getAvatarPostion(0, origin, visibleSize, btn_start_match->getHeight())));
			}

            for (int i = 0; i < response->args_size(); i++) {
                if (response->args(i).key() == "currentCards") {
                    vector<int> current_card_values = Common::getInstance()
                        ->convertStringsToInt(Common::getInstance()->split(response->args(i).value(), ','));
                    sizeCard = (int)current_card_values.size();
                    sortCard(current_card_values);
                } else if (response->args(i).key() == "lastTurnCards") {
                    vector<int> listTurnCardValues = Common::getInstance()
                        ->convertStringsToInt(Common::getInstance()->split(response->args(i).value(), ','));

                    int currentTurnUserId = getCurrentTurnUserId();
                    char buffer[20];
                    sprintf(buffer, "%d", currentTurnUserId);
                    std::string current_user_id = std::string(buffer);
                    int numbercard = 0;
                    Avatar* avatar = findAvatarOfPlayer(currentTurnUserId);
                    if (avatar != 0) {
                        numbercard = avatar->getNumberCard();
                        numbercard -= listTurnCardValues.size();
                        avatar->setNumberCard(numbercard);
                    }

					CCLOG("number card reenter: %d", numbercard);

                    if (currentTurnUserId == Common::getInstance()->getUserId()) {
                        this->moveCardToCenter(listTurnCardValues, false, avatar);

                        // disable suggest
                        /*for(CardSprite* card : card_tag) {
                            if (card->getState() != OnTable) {
                                card->showHidden(false);
                            }
                        }*/
						//suggess bai
						if (!listTurnCardValues.empty()){
							vector<int> cardReady =
								TLMNCardHandler::getInstance()->getAllSuggessCard(this->cardTagToInts(card_tag), listTurnCardValues);
							if (!cardReady.empty()){
								for (CardSprite* card : card_tag){
									if (card->getState() != OnTable){
										for (int value : cardReady) {
											if (card->getNumberValue() == value) {
												card->setReady(true);
											}
										}
										card->showHidden(!card->getReady());
										card->setReady(false);
									}
								}
							}
							else {
								for (CardSprite* card : card_tag){
									if (card->getState() != OnTable){
										card->showHidden(true);
									}
								}
							}
						}
                    } else {
                        this->moveCardToCenter(listTurnCardValues, false, avatar);
                    }

                    if (getCurrentTurnUserId() == Common::getInstance()->getUserId()){
                        btn_danh_bai->setVisible(true);
						btn_bo_luot->setVisible(true);
					}
					
                    /*handler last turn cards*/

                }
                else if (response->args(i).key() == "turnCdRemaining") {
                    float time_count_down = Common::getInstance()->convertStringToInt(response->args(i).value()) * 1.0;
                    findAvatarOfPlayer(getCurrentTurnUserId())->updateProgressCircleBar(100, time_count_down);
                }
                else if (response->args(i).key() == "cardRemainingCount") {
                    std::string json = response->args(i).value();
                    parseRemainCards(json);
                }
                else {
                    if (response->args(i).key() == "hiddenCardRemainingCount") {
                        if (response->args(i).value() == "true"){
                            hiddenCardRemainingCount(avatars);
                        }
                    }
                }
            }
        }
    }
    catch (std::exception &e) {
        CCLOG("error message: %s", e.what());
    }
}

vector<pair<int, vector<int>>> TLMienNam::parseCardValue(std::string
    json_value) {
    vector<pair<int, vector<int>>> result; 
    try {
        Document document;
        document.Parse(json_value.c_str());
        int index = 0;
        for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
            itr != document.MemberEnd(); ++itr) {
            
            string val = itr->value.GetString();
            vector<int> card_values = Common::getInstance()->convertStringsToInt(Common::getInstance()
                ->split(val, ','));
            int user_id = Common::getInstance()->convertStringToInt(itr->name.GetString());
            result.push_back(make_pair(user_id, card_values));
        }
    }
    catch (...) {
        CCLOG("exception");
        result.clear();
    }

    return result; 
}

vector<pair<string, vector<int>>> TLMienNam::parseTurnResponse(BINMapFieldEntry entries) {
    vector<pair<string, vector<int>>> result;
    if (entries.has_key()) {
        if (entries.key() == TurnResponseKey[0]) {
            vector<int> listTurnCardValues = Common::getInstance()
                ->convertStringsToInt(Common::getInstance()->split(
                entries.value(), ','));
            result.push_back(std::make_pair(entries.key(),
                listTurnCardValues));
        }
        else {
            bool val = Common::getInstance()->to_bool(entries.value());
            vector<int> entries_val;
            entries_val.push_back(val ? 1 : 0);
            result.push_back(std::make_pair(entries.key(), entries_val));
        }
        
        if(entries.key() == TurnResponseKey[2])
            setPassUp(false);
    }
    return result;
}

int TLMienNam::getChangeOwnerRoomCd() const {
    return this->changeOwnerRoomCd;
}

void TLMienNam::setChangeOwnerRoomCd(int _change_owner_room_cd) {
    this->changeOwnerRoomCd = _change_owner_room_cd;
}

void TLMienNam::handleTurnResponseValues(vector<pair<string, vector<int>>> turn_response) {
    //TODO: Handle response
    int currentTurnUserId = getCurrentTurnUserId();
    char buffer[20];
    sprintf(buffer, "%d", currentTurnUserId);
    std::string current_user_id = std::string(buffer);

    Avatar* avatar = findAvatarOfPlayer(currentTurnUserId);
    //if turn_response[0].first == "turnCards" //Cac quan bai no dang danh,lam hieu ung quan bai dang danh
    //if turn_reeponse[0].first == "passUp", hien thi message la bo luot
    //if turn_response[0].first == "newTurn", clear cac quan bai da danh
    
    if(turn_response[0].first == "turnCards") {
        vector<int> values = turn_response[0].second;
        //lastCards = values;
        int numbercard = avatar->getNumberCard();
        numbercard -= values.size();
        avatar->setNumberCard(numbercard);

        if (currentTurnUserId == Common::getInstance()->getUserId()) {
            //handler quan bai cua chinh minh
            
            this->moveCardToCenter(values, true, avatar);
            
            //here here
            this->sortCardAfterMoveCardToCenter(numbercard);
            
            // disable suggest
            for(CardSprite* card : card_tag){
                if (card->getState() != OnTable) {
                    card->showHidden(false);
                }
            }

            lastCards.clear();
        }else {
            lastCards = values;
            this->moveCardToCenter(values, false, avatar);
        }

        /*
            Xử lý phần hiển thị quân bài suggest
         */
        if (getNextTurnUserId() == Common::getInstance()->getUserId()) {
            btn_danh_bai->setVisible(true);
            btn_bo_luot->setVisible(true);
            
            if (!isMatchEnd()){
                vector<int> cardReady =
                    TLMNCardHandler::getInstance()->getAllSuggessCard(this->cardTagToInts(card_tag), values);

                CCLOG("card suggess: ");
                for (int i = 0; i < cardReady.size(); i++){
                    CCLOG("%d", cardReady[i]);
                }
                CCLOG("end card suggess");

                if (!cardReady.empty()){
                    for (CardSprite* card : card_tag){
                        if (card->getState() != OnTable){
                            for (int value : cardReady) {
                                if (card->getNumberValue() == value) {
                                    card->setReady(true);
                                }
                            }
                            card->showHidden(!card->getReady());
                            card->setReady(false);
                        }
                    }
                }
                else {
                    for (CardSprite* card : card_tag){
                        if (card->getState() != OnTable){
                            card->showHidden(true);
                        }
                    }
                }
            }
            
        } else if (getCurrentTurnUserId() == Common::getInstance()->getUserId()){
            btn_danh_bai->setVisible(false);
            btn_bo_luot->setVisible(false);
        }
        
    } else if(turn_response[0].first == "passUp"){

        avatar->showPassUp(true);
        //play sound passup
        SoundManager::getInstance()->playSound(soundTLMN[cocos2d::RandomHelper::random_int(0,5)]);

        //Show animation bo luot
        if (getCurrentTurnUserId() == Common::getInstance()->getUserId()){
            btn_danh_bai->setVisible(false);
            btn_bo_luot->setVisible(false);
            // disable suggest
            for(CardSprite* card : card_tag){
                if (card->getState() != OnTable) {
                    card->showHidden(false);
                }
            }
        } else if (getNextTurnUserId() == Common::getInstance()->getUserId()) {
            btn_danh_bai->setVisible(true);
            btn_bo_luot->setVisible(true);

            if (!lastCards.empty() && !isMatchEnd()){ //show suggess card
                vector<int> cardReady =
                    TLMNCardHandler::getInstance()->getAllSuggessCard(this->cardTagToInts(card_tag), lastCards);
             /*   CCLOG("card suggess: ");
                for (int i = 0; i < cardReady.size(); i++){
                    CCLOG("%d", cardReady[i]);
                } 
                CCLOG("end card suggess");*/

                if (!cardReady.empty()){
                    for (CardSprite* card : card_tag){
                        if (card->getState() != OnTable){
                            for (int value : cardReady) {
                                if (card->getNumberValue() == value) {
                                    card->setReady(true);
                                }
                            }
                            card->showHidden(!card->getReady());
                            card->setReady(false);
                        }
                    }
                }
                else {
                    for (CardSprite* card : card_tag){
                        if (card->getState() != OnTable){
                            card->showHidden(true);
                        }
                    }
                }
            }
        }
    } else if(turn_response[0].first == "newTurn"){
        
        lastCards.clear();

        // disable suggest
        for (CardSprite* card : card_tag){
            if (card->getState() != OnTable) {
                card->showHidden(false);
            }
        }
        
        for(vector<OtherCardSprite*> vectorCard : groupOtherCards){
            for (OtherCardSprite* card : vectorCard){
                    auto rotate = RotateTo::create(0.3f,270);
                    auto scale = ScaleTo::create(0.3f, 0.1f);
                    auto spawn = Spawn::createWithTwoActions(rotate,scale);
                    auto callbackJump = CallFunc::create([=](){
                        this->removeChild(card);
                    });
                    card->runAction(Sequence::create(spawn,callbackJump,NULL));
            }
        }
        groupOtherCards.clear();
        
        if (getNextTurnUserId() == Common::getInstance()->getUserId()) {
            btn_danh_bai->setVisible(true);
            btn_bo_luot->setVisible(false);
        }

        auto passUpCall = CallFunc::create([=](){
            if (!avatar->getPassUp()){
                avatar->showPassUp(true);
            }
        });

        auto erasePassUpCall = CallFunc::create([=](){
            //bo hien thi bo luot khi turn moi
            for (int i = 0; i < avatars.size(); i++){
                if (avatars[i]->getPassUp()){
                    avatars[i]->showPassUp(false);
                }
            }
        });

        avatar->runAction(Sequence::create(passUpCall, DelayTime::create(0.8f), erasePassUpCall, NULL));
    }
}

void TLMienNam::moveCardToCenter(std::vector<int> values,bool self,Avatar* avatar){
    int cardType = TLMNCardHandler::getInstance()->checkCardType(values);
    if(getSound(cardType,values)!=-1 && avatar->getNumberCard()){
        SoundManager::getInstance()->playSound(soundTLMN[getSound(cardType,values)]);
    }
    
    // blur card ontable con lai
    for(vector<OtherCardSprite*> vectorCard : groupOtherCards){
        for (OtherCardSprite* card : vectorCard){
            card->showHidden(true);
            //move up card second
            card->runAction(MoveBy::create(0.1f, Vec2(0,30)));
        }
    }
    
    int randomX = RandomHelper::random_int(-30, 30);
    std::vector<OtherCardSprite*> otherCards;
    
    if(self){ // quân bài của chính mình đánh ra
        int sizeCard = (int)values.size();
        int cardTag = -1;

        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < card_tag.size(); j++) {
                if (card_tag[j]->getNumberValue() == values[i] &&
                    card_tag[j]->getState() != OnTable) {
                    card_tag[j]->setState(OnTable);
                    
                    cardTag++;
                    auto card = OtherCardSprite::createSelf(card_tag[j]->getNumberValue(),
                                                            cardWidth());
                    card->setAnchorPoint(Point::ANCHOR_MIDDLE);
                    card->setPosition(card_tag[j]->getPosition());
                    
                    card->setMoveToCenterSelf(sizeCard, cardTag, origin, visibleSize,
                                              cardWidth(), randomX);
                    otherCards.push_back(card);
                    
                    card_tag[j]->setVisible(false);
                    card_tag[j]->setPosition(MVec2(-width / 2, -height / 2));
                }
            }
        }
    }else { // quân bài của thằng khác đánh ra
		//if (getCurrentTurnUserId() != Common::getInstance()->getUserId()) {
			for (int i = 0; i<values.size(); i++) {
                auto card = OtherCardSprite::create(values[i], cardWidth());
                card->setPosition(getCardCoverPostion(avatar));
                
                card->setMoveToCenter((int)values.size(), i, origin, visibleSize,
                                      cardWidth(), randomX);
                CCLOG("Value: %d", card->getValue());
                otherCards.push_back(card);
            }
        //}
    }
    groupOtherCards.push_back(otherCards);
    
    for(vector<OtherCardSprite*> vectorCard : groupOtherCards){
        for (OtherCardSprite* card : vectorCard){
            if (card->getParent() == nullptr) {
                this->addChild(card);
            }
        }
    }
    // Remove card ontable đầu tiên.
    if(groupOtherCards.size() > 2){
        for(OtherCardSprite* card : groupOtherCards[0]){
            auto moveUp = MoveBy::create(0.5f,Vec2(0,50));
            auto fade = FadeOut::create(0.5f);
            auto spawn = Spawn::createWithTwoActions(moveUp,fade);
            auto callbackJump = CallFunc::create([=](){
                this->removeChild(card);
            });
            card->runAction(Sequence::create(spawn,callbackJump,NULL));
        }
        groupOtherCards.erase(groupOtherCards.begin()+ 0);
    }
}

void TLMienNam::sortCardAfterMoveCardToCenter(int numberCard){
    int countCardTag = -1;
    for (int i = 0; i < card_tag.size(); i++) {
        if (card_tag[i]->getState() != OnTable) {
            card_tag[i]->setState(Idle);
            
            countCardTag++;
            auto moveTo = MoveTo::create(0.2f, MVec2(visibleSize.width / 2 +
                                                     (countCardTag - (float)(numberCard - 1) / 2) * cardWidth(),
                                                     5+btn_message->getHeight()*1.5f + cardWidth() *71/106));
            card_tag[i]->runAction(moveTo);
        }
    }
    Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
	if (avatar != 0){
		auto pos = Vec2(originX + width / 2 - cardWidth()* (0.5f + numberCard / 2.0f) - avatar->getContentSize().width,
			avatar->getPosition().y);
		if (numberCard == 0){
			pos = Vec2(originX + width / 2 - avatar->getContentSize().width / 2, avatar->getPosition().y);
		}
		avatar->runAction(MoveTo::create(0.2f, pos));
	}
}

Vec2 TLMienNam::getCardCoverPostion(Avatar* avatar){
    return Vec2(avatar->getPosition().x + avatar->spriteCard->getPosition().x,
        avatar->getPosition().y + avatar->spriteCard->getPosition().y);
}

TLMNPlayer TLMienNam::convertFromBINPlayer(BINPlayer binplayer) {
    char buffer[20];
    sprintf(buffer, "%lld", binplayer.userid());
    std::string uid = std::string(buffer);

    int numberCard = 0;

    /*BINMapFieldEntry fieldEntry;
    for (int i = 0; i < binplayer.args_size(); i++){
        fieldEntry = binplayer.args(i);
        if (fieldEntry.key() == "currentCards"){
            std::string jsonFieldEntry = fieldEntry.value();
            vector<std::string> lstEntry = Common::getInstance()->split(jsonFieldEntry, ',');
            numberCard = (int)lstEntry.size();
            break;
        }
    }*/

    TLMNPlayer player = TLMNPlayer(binplayer.username(), uid, numberCard, binplayer.cash(),
        binplayer.gold(), 0, binplayer.tableindex(), binplayer.avatarid());
    return player;
}

void TLMienNam::handleWinLose(BINMatchEndResponse *response) {
    //handle win
    for (int i = 0; i < response->winninguserids_size(); i++) {
        int val = (int)response->winninguserids(i);
        for (int j = 0; j < lst_player.size(); j++) {
            std::stringstream ss(lst_player[j].getID());
            int player_uid;
            ss >> player_uid;
            if (val == player_uid) {
                lst_player[j].setWin(true);
                break;
            }
        }
    }
    //handle lose
    for (int i = 0; i < response->losinguserids_size(); i++) {
        int val = (int)response->losinguserids(i);
        for (int j = 0; j < lst_player.size(); j++) {
            std::stringstream ss(lst_player[j].getID());
            int player_uid;
            ss >> player_uid;
            if (val == player_uid) {
                lst_player[j].setWin(false);
                break;
            }
        }
    }
    // hung xu li cho nay,
    // Dua vao listplayer -> hien thi thang/thua tren avatar! sau do set lai
    // toan bo thanh = false cho win
    for(TLMNPlayer player : lst_player){
        if(player.isWin()){
            findAvatarOfPlayer(Common::getInstance()->convertStringToInt(player.getID()))->setWin(4.0f);
        }else{
            findAvatarOfPlayer(Common::getInstance()->convertStringToInt(player.getID()))->setLose(4.0f);
        }
    }
}

void TLMienNam::resetMatch() {
    CCLOG("card tag size: %lu", card_tag.size());
    
    lastCards.clear();
    
    enter_room_response = 0; //xoa bien luu trang thai dang choi cua nguoi choi khi join lai ban choi

    for (int i = 0; i < lst_player.size(); i++){
        lst_player[i].setNumberCard(0);
    }

    for (int i = 0; i < avatars.size(); i++){
        avatars[i]->setNumberCard(0);
    }

    if (!isUserPlaying() && lst_player.size() < capacity_size){
        btn_san_sang->setVisible(true);
    }
    
    for (CardSprite* card : card_tag) {
        this->removeChild(card);
    }
    card_tag.clear();
    //xoa quan bai con lai tren ban

    for(vector<OtherCardSprite*> vectorCard : groupOtherCards){
        for (OtherCardSprite* card : vectorCard){
            this->removeChild(card);
        }
    }
    groupOtherCards.clear();

    CCLOG("reset match-> change owner room: %d, current_user: %d", getOwnerUserId(), Common::getInstance()->getUserId());
    if (Common::getInstance()->getUserId() == getOwnerUserId() && lst_player.size() >= 2) {
        btn_start_match->setVisible(true);
    }
    
    TLMienNam::enter_room_response = 0;
}

void TLMienNam::update(float delta) {
    PlayScene::update(delta);
    /*
        nguoi choi huy dang ky roi ban
     */
    TLMienNam::cancelExitAfterMatchEndResponseHandler();
    
    /* 
     nguoi choi khac nhan duoc thong bao khi co nguoi dang ky roi ban
     */
    TLMienNam::playerExitAfterMatchEndResponse();
    
    /*
     update thong tin ban choi khi co nguoi roi ban
     */
    TLMienNam::playerExitRoomResponse();
    
    /* 
     Thay đổi chủ bàn
     */
    TLMienNam::roomOwnerChangedResponseHandler();
    
    /*
     TURN response
     */
    TLMienNam::turnResponse();

    /*
     begin UPDATE_MONEY
     */
    TLMienNam::updateMoneyResponseHandler();


    TLMienNam::prepareNewMatchResponseHandler();
    
    /*
     Match End
     */
    TLMienNam::matchEndResponseHandler();
    
    /*
     match begin
     */
    TLMienNam::matchBeginResponseHandler();
    
    /*
     player enter room
     */
    TLMienNam::playerEnterRoomResponseHandler();
    
    /*
     startMatch
     */
    TLMienNam::startMatchResponseHandler();
    
    /*
     kick user
     */
    TLMienNam::kickUserResponseHandler();

    /*
    readyToPlay
    */
    TLMienNam::readyToPlayResponseHandler();
    
    /*
     change_rule
     */
    TLMienNam::changeRuleResponseHandler();
}

//reset countdown cua tat ca nguoi choi
void TLMienNam::resetCountDownAll(){
    CCLOG("resetCountDownAll");
    for (size_t i = 0; i < avatars.size(); i++){
        avatars[i]->resetProcessCircleBar();
    }
}

int TLMienNam::findIndexPlayer(vector<TLMNPlayer> lstPlayer, Player& player){

    for (int i = 0; i < lstPlayer.size();i++){
        if (lstPlayer[i].getID() == player.getID()){
            return i;
        }
    }

    return -1;
}

//set vi tri nguoi choi: indexPos -> vi tri cua nguoi choi trong lst_player 
//capacity_size -> so nguoi choi toi da trong room
void TLMienNam::setPositionPlayer(TLMNPlayer& player, int indexPos){
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
        avatar->hideCardCover();
    }

    avatar->setNumberCard(_numberCard);

    avatars.push_back(avatar);

    if (avatar->getParent() == nullptr)
        this->addChild(avatar);
}

/*get player information from list_player*/
void TLMienNam::sortListPlayer() {
    sort(lst_player.begin(), lst_player.end());
}

//lay ra avatar cua nguoi choi
//Avatar* TLMienNam::findAvatarOfPlayer(long long player_id) {
//    for (int i = 0; i < avatars.size(); i++){
//        if (avatars[i]->getPlayerId() == player_id){
//            return avatars[i];
//        }
//    }
//    return NULL;
//}

//tim nguoi choi
Player* TLMienNam::findPlayer(long long player_id){
    char c_player_id[50];
    sprintf(c_player_id, "%lld", player_id);

    std::string s_player_id = std::string(c_player_id);

    for (int i = 0; i < lst_player.size(); i++){
        if (lst_player[i].getID() == s_player_id){
            return &lst_player[i];
        }
    }

    return NULL;
}

//tim nguoi cho
Player* TLMienNam::findWaiting(long long player_id){
    char c_player_id[50];
    sprintf(c_player_id, "%lld", player_id);
    std::string s_player_id = std::string(c_player_id);

    for (int i = 0; i < lst_waiting.size(); i++){
        if (lst_waiting[i].getID() == s_player_id){
            return &lst_waiting[i];
        }
    }
    return NULL;
}

void TLMienNam::deleteWaitingPlayer(string player_id){
    int k = -1;
    for (int i = 0; i < lst_waiting.size(); i++){
        if (lst_waiting[i].getID() == player_id){
            k = i;
        }
    }

    if (k != -1 && !lst_waiting.empty())
        lst_waiting.erase(lst_waiting.begin() + k);
}

int TLMienNam::getPositionOfUserId(string uid) {
    for (int i = 0; i < lst_player.size(); i++)
        if (lst_player[i].getID() == uid) return i;
    return -1;
}


void TLMienNam::displayInfoRemainCard(std::vector<TLMNPlayer>& remain_card_infos) {
    //find current index
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
        setPositionPlayer(remain_card_infos[i], i);
    }
}

void TLMienNam::sortCard(vector<int> card_values) {
    std::sort(card_values.begin(), card_values.end());
    if (!cards.empty()) cards.clear();
    for(int i=0;i<card_values.size();i++){
        Card card;
        card.value = card_values[i]; // Số thẻ là 1-52
        cards.push_back(card);

    }
    this->showInitCard();
}

void TLMienNam::resetDisplayAvatar(){
    if (!avatars.empty()){
        for (int i = 0; i < avatars.size(); i++){
            if (avatars[i]->getParent() != nullptr){
                this->removeChild(avatars[i]);
            }
        }
        avatars.clear();
    }
}

void TLMienNam::playCallBack(Ref *pSender, ui::Widget::TouchEventType eventType){
    MButton *btn = (MButton*) pSender;
     if(eventType == ui::Widget::TouchEventType::ENDED){
         int tag = btn->getTag();
         switch (tag) {
             case TAG_TLMN_BTN_XEPBAI:
                 CCLOG("%s","xep bai");
                 break;
             case TAG_TLMN_BTN_CHONLAI:
                 CCLOG("%s","chon lai");
                 break;
             default:
                 break;
         }
     }
}

void TLMienNam::menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType) {
    //PlayScene::menuCallBack(pSender, eventType);
    if(eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*) pSender)->getTag();
        switch (tag) {
                break;
            case TAG_TLMN_START_MATCH:
               CCLOG("%s", "start match");
               if (lst_player.size() >= 2) {
                    NetworkManager::getInstance()->getStartMatchMessageFromServer(roomIndex);
                    btn_start_match->setVisible(false);
                } else {
                    CCLOG("Khong du nguoi choi");
                }
               break;
            case TAG_TLMN_BTN_SANSANG:
                NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, -1);
                break;
            default:
                break;
        }
    }
}

void TLMienNam::cardCallBack(cocos2d::Ref *pSender, ui::Widget::TouchEventType eventType){

    MButton *btn = (MButton*)pSender;

    if (eventType == ui::Widget::TouchEventType::ENDED){
        int tag = btn->getTag();
        switch (tag) {
        case TAG_TLMN_BTN_BOLUOT: {
            
            // CCLOG("bo luot");
            vector<BINMapFieldEntry> entries;
            BINMapFieldEntry *entry = new BINMapFieldEntry();
            entry->set_key("passUp");
            entry->set_value("true");
            entries.push_back(*entry);
            setPassUp(true);
            NetworkManager::getInstance()->getTurnMessageFromServer(roomIndex, entries);
            break;
        }
        case TAG_TLMN_BTN_DANHBAI:
        {
            setPassUp(false);
            vector<int> card_values;
            for (int i = 0; i<card_tag.size(); i++) {
                if (card_tag[i]->getState() == OnHand) {
                    card_values.push_back(card_tag[i]->getCard().value);
                }
            }
            cardTag = (int)card_values.size();
            
            if (cardTag > 0) {
                vector<BINMapFieldEntry> entries;
                BINMapFieldEntry *entry = new BINMapFieldEntry();
                entry->set_key("turnCards");
                std::string cards_value = Common::getInstance()->convertListCardToString(card_values);
                entry->set_value(cards_value);
                entries.push_back(*entry);
                NetworkManager::getInstance()->getTurnMessageFromServer(roomIndex, entries);
                
            } else {
                /*
                    Chon quan bai khong hop le
                 */
            }
            break;
        }
        default:
            break;
        }
    }
}

//show danh sach nguoi cho
void TLMienNam::showWaitingPlayerOnScene(vector<TLMNPlayer> lstWaiting){
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
			waitingPlayer->setAvatar(lstWaiting[i].getName(), lstWaiting[i].getAvatarId());
            waitingPlayer->setPositionAvatar(origin, distance);
            distance += waitingPlayer->getAvatar()->getWidth()*0.5 + init_distance;
            lstDisplayWaitingPlayer.push_back(waitingPlayer);
            this->addChild(waitingPlayer);
        }
    }
}

void TLMienNam::onExit() {
    PlayScene::onExit();
    is_create_room = false;
    player_list.clear();
}

bool TLMienNam::isUserPlaying(){
    int user_id = Common::getInstance()->getUserId();
    Player* player = findPlayer(user_id);
    if (player != 0){
        return true;
    } 
    return false;
}

vector<int> TLMienNam::cardTagToInts(vector<CardSprite *> cards) {
    vector<int> result;
    for (CardSprite* card : cards) {
        if (card->getState() !=OnTable) {
            result.push_back(card->getNumberValue());
        }
    }
    return result;
}

TLMNPlayer* TLMienNam::currentUser() {
    for(int i = 0; i < lst_player.size(); i++) {
        char n_str[50];
        sprintf(n_str, "%d", Common::getInstance()->getUserId());
        if(lst_player[i].getID() == n_str) {
            return &lst_player[i];
        }
    }
    return nullptr;
}

//void TLMienNam::exitRoomResponseHandler() {
//    BINExitRoomResponse* exit_room_response =
//    (BINExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::EXIT_ROOM);
//    if (exit_room_response != 0) {
//        CCLOG("exit room response: %s", exit_room_response->DebugString().c_str());
//        if (exit_room_response->responsecode() && exit_room_response->has_exitaftermatchend()) {
//            if (!exit_room_response->exitaftermatchend()) {
//                enter_room_response = 0; //xoa bien luu trang thai dang choi khi nguoi choi join lai ban choi
//                auto showtable = SceneTable::createScene(isDisplayRoomList);
//                REPLACESCENE(0.1f, showtable);
//            }
//        } else {
//            this->showToast(exit_room_response->message().c_str(), 2);
//        }
//    }
//}

void TLMienNam::handleEmotion(long long user_id, int emotion_id, string message) {
    /*TODO: HungLe
    // emoticonId = 

	//1-Tới trắng 5 đôi thông
	//2-Tới trắng 6 đôi bất kỳ
	//3-Tới trắng sảnh rồng
	//4-Tới trắng tứ 2
	//5-Tới trắng tứ 3
	//6-Tới trắng 3 đôi thông có 3 bích
	//7-12 cây đồng màu
    */
    auto anim = AnimationManager::getInstance();
    if(anim->getParent() == NULL){
        this->addChild(anim);
        anim->show(0, visibleSize);
    }
    
}

void TLMienNam::handleCardValue(std::vector<std::pair<int, std::vector<int>>> card_values)  {
    int k = -1;
    for (int i = 0; i < card_values.size(); i++) {
        int user_id = card_values[0].first; 
        for (int j = 0; j < lst_player.size(); j++) {
            if (user_id == Common::getInstance()->convertStringToInt(
                lst_player[i].getID()) && lst_player[i].isWin()) {
                k = j; 
                break;
            }
        }
        if (k != -1) break;
    }

    if (k != -1) {
        vector<int> win_card_values = card_values[k].second; 
        //handle win card value - HungLe
        for(int i = 0;i < win_card_values.size(); i++) {
            auto card = OtherCardSprite::createSelf(win_card_values[i], cardWidth());
            card->setAnchorPoint(Point::ANCHOR_MIDDLE);
            card->setPosition(MVec2(visibleSize.width / 2 +
                                    (i - (float)(win_card_values.size() - 1) / 2) * cardWidth(),
                                    height*.75f - 0.5f*cardWidth()*71/106));
            card->runAction(Sequence::create(DelayTime::create(2),FadeOut::create(0.5f),RemoveSelf::create(),NULL));
            this->addChild(card);
        }
    }
}

void TLMienNam::matchEndResponseHandler() {
    BINMatchEndResponse *endmatchresponse = (BINMatchEndResponse*)
    Common::getInstance()->checkEvent(NetworkManager::MATCH_END);
    
    if (endmatchresponse != 0) {
        CCLOG("end match response: %s", endmatchresponse->DebugString().c_str());
        setMatchEnd(endmatchresponse->responsecode());
        if (endmatchresponse->responsecode()) {

            matchRunning = false;
            
            //neu ket thuc game
            handleWinLose(endmatchresponse);
            for (int i = 0; i < lst_player.size(); i++) {
                CCLOG("player uid: %s, play win: %s", lst_player[i].getID()
                      .c_str(), lst_player[i].isWin() ? "true" : "false");
            }
            
            //
            if(endmatchresponse->textemoticons_size() > 0){
                this->showToast(endmatchresponse->textemoticons(0).message().c_str(), 2);
            }
            //neu ket thuc game
            if (isMatchEnd()){
                
                for (int i = 0; i < endmatchresponse->textemoticons_size(); i++) {
                    BINTextEmoticon text_emoticon = endmatchresponse->textemoticons(i);
                    //get user id
                    long long user_id = text_emoticon.userid();
                    //get text_emotion_id 
                    int emotion_id = text_emoticon.emoticonid(); 
                    //get message attach emotion
                    string message = text_emoticon.message();
                    handleEmotion(user_id, emotion_id, message);
                }

                if (endmatchresponse->args_size() > 0) {
                    CCLOG("card remaining count: %s", endmatchresponse->args(0).key().c_str());
                    BINMapFieldEntry entries = endmatchresponse->args(0);
                    if (entries.has_key() && entries.key() == "cardRemaining") {
                        vector <pair<int, vector<int>>> match_end_card_values 
                            = parseCardValue(entries.value());
                        handleCardValue(match_end_card_values);
                        
                    }
                }
                
            }
        } else {
            this->showToast(endmatchresponse->message().c_str(), 2);
            
        }
    }
}

void TLMienNam::playerExitAfterMatchEndResponse() {
    BINPlayerExitAfterMatchEndResponse* exit_room_player_response =
    (BINPlayerExitAfterMatchEndResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_AFTER_MATCH_END);
    if (exit_room_player_response != 0) {
        CCLOG("exit room player response: %s", exit_room_player_response->DebugString().c_str());
        if (exit_room_player_response->responsecode()) {
            int leng = (int)lst_player.size();
            for (int i = 0; i < leng; i++) {
                //reset position
                string user_id = lst_player[i].getID();
                if (user_id == Common::getInstance()->convertIntToString((int)exit_room_player_response->exituserid())){
     //               char message[60];
     //               // Hung code them phan hien thi hieu ung nguoi choi dang ky roi ban
     //               sprintf(message, "Người chơi %s đăng ký rời bàn chơi", lst_player[i].getName().c_str());
					//this->showToast(message, 2);

					Avatar* avatar = findAvatarOfPlayer(exit_room_player_response->exituserid());
					if (avatar != 0){
						avatar->showRegisterExitRoom(true);
					}
                    
                    break;
                }
            }
        }
    }
}

void TLMienNam::playerExitRoomResponse() {
    BINPlayerExitRoomResponse* _player_exit_room_response =
    (BINPlayerExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_ROOM);
    if (_player_exit_room_response != 0) {
        CCLOG("exit room player response: %s", _player_exit_room_response->DebugString().c_str());
        if (_player_exit_room_response->responsecode()) {
            int leng = (int) lst_player.size();

            Avatar* avatar;
            for (int i = 0; i < leng; i++) {
                //xoa nguoi choi khoi ban choi
                string user_id = lst_player[i].getID();
                if (user_id == Common::getInstance()->convertIntToString((int)_player_exit_room_response->exituserid())){
                    lst_player.erase(lst_player.begin() + i);

					showInvitePlayer(lst_player.size());  //show moi choi

                    avatar = findAvatarOfPlayer(_player_exit_room_response->exituserid());
                    //xoa avatar khoi ban choi (khong hien thi nua)
                    removeOutTablePlay(avatar);
                    //xoa khoi danh sach luu avatars
                    avatars.erase(std::remove(avatars.begin(), avatars.end(), avatar), avatars.end());
                    
                    if (lst_player.size() < 2){ //neu so luong nguoi choi nho hon 2 thi an btn startmatch
                        btn_start_match->setVisible(false);
                    }

					if (_player_exit_room_response->changeownerroomcd() > 0){
						this->removeChildByTag(TAG_TIME_COUNTDOWN);

                        CCLOG("player exit room time countdown %d", _player_exit_room_response->changeownerroomcd());
                        int time_wait = _player_exit_room_response->changeownerroomcd()/1000;
                        addCountDown(time_wait);
                    } 
					//neu chi con 1 nguoi choi thi an countdown dem nguoc chu phong
					else if (lst_player.size() == 1 && this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){ 
						this->removeChildByTag(TAG_TIME_COUNTDOWN);
					}
                    break;
                }
            }

            //xoa nguoi cho di
            Player* playerWaiting = findWaiting(_player_exit_room_response->exituserid());
            if (playerWaiting != 0){
                deleteWaitingPlayer(playerWaiting->getID());

                //hien thi lai danh sach cho len giao dien
                resetListWaiting();
                showWaitingPlayerOnScene(lst_waiting);
            }
        }
    }
}

void TLMienNam::turnResponse() {
    BINTurnResponse *turnresponse =
    (BINTurnResponse*)Common::getInstance()->checkEvent(NetworkManager::TURN);
    if (turnresponse != 0) {
        
        CCLOG("turn response: %s", turnresponse->DebugString().c_str());
        if (turnresponse->responsecode()) {
            
            setTurnCountDownTime((int)turnresponse->countdowntimer());
            setMatchEnd(turnresponse->matchend());
            
            setCurrentTurnUserId((int)turnresponse->currentturnuserid());
            setNextTurnUserId((int)turnresponse->nextturnuserid());
            
            long long player_id = turnresponse->currentturnuserid();
            long long next_player_id = turnresponse->nextturnuserid();
            
            //neu la nguoi choi hien tai thi reset countdown
            auto avatar = findAvatarOfPlayer(player_id);
            if (avatar != 0){
                avatar->resetProcessCircleBar();
            }
            
            //neu chua ket thuc van choi
            if (!turnresponse->matchend()){
                //neu khong phai current player thi set countdown cho nguoi tiep theo
                avatar = findAvatarOfPlayer(next_player_id);
                if (avatar != 0){
                    avatar->updateProgressCircleBar(100, getTurnCountDownTime());
                }
            }
            
            if (turnresponse->args_size() > 0) {
                for (int i = 0; i < turnresponse->args_size(); i++) {
                    vector<pair<string, vector<int>>> turn_response_val
                    = parseTurnResponse(turnresponse->args(i));
                    handleTurnResponseValues(turn_response_val);
                    /*if (turnresponse->args(i).key() == TurnResponseKey[0])
                        break;
                    if (turnresponse->args(i).key() == TurnResponseKey[2]) {
                        break;
                    }*/
                }
            }

            if (turnresponse->matchend()){
                //ket thuc van bai + hieu ung thang thua
                btn_bo_luot->setVisible(false);
                btn_danh_bai->setVisible(false);
                
                SoundManager::getInstance()->playSound(soundTLMN[RandomHelper::random_int(34, 35)]);
            }
        } else {
            this->showToast(turnresponse->message().c_str(),2);
        }
    }
}

void TLMienNam::roomOwnerChangedResponseHandler() {
    BINRoomOwnerChangedResponse* _room_owner_change_response =
    (BINRoomOwnerChangedResponse *)Common::getInstance()->checkEvent(NetworkManager::ROOM_OWNER_CHANGED);
    if (_room_owner_change_response != 0) {
        CCLOG("room owber change response: %s", _room_owner_change_response->DebugString().c_str());
        if (_room_owner_change_response->responsecode()) {
			
            int newOwnerUserId = (int)_room_owner_change_response->newowneruserid();
            auto common = Common::getInstance();
            common->setOwnerUserId(newOwnerUserId);
            setOwnerUserId(newOwnerUserId);
            is_create_room = common->getUserId() == newOwnerUserId;

			displayLockRoomForOwner(newOwnerUserId);

            btn_start_match->setVisible(is_create_room && lst_player.size() >= 2);
            
            // thoi gian doi khi thay doi chu phong
            if (_room_owner_change_response->changeownerroomcd() > 0) {
                CCLOG("room owner change time countdown %d", _room_owner_change_response->changeownerroomcd());
                int time_wait = _room_owner_change_response->changeownerroomcd() / 1000;
                addCountDown(time_wait);
            }
        }
    }
}

void TLMienNam::updateMoneyResponseHandler() {
    BINUpdateMoneyResponse *updatemoneyresponse =
    (BINUpdateMoneyResponse*)Common::getInstance()->checkEvent(NetworkManager::UPDATE_MONEY);
    
    if (updatemoneyresponse != 0) {
        CCLOG("update money response: %s", updatemoneyresponse->DebugString().c_str());
        if (updatemoneyresponse->responsecode()) {
            if (updatemoneyresponse->moneyboxes_size() > 0) {
                
				BINMoneyBox moneyBox;
                long long origin_money; //so tien ma nguoi choi dang co
                Player* player;
                
                Avatar* avatar;
                for (int i = 0; i < updatemoneyresponse->moneyboxes_size(); i++) {
                    moneyBox = updatemoneyresponse->moneyboxes(i); //money_boxe : userId , money, reason
                    bool isCash = moneyBox.iscash();
                    player = findPlayer(moneyBox.userid());
                    
                    if (player != 0){
                        //lay ra tien cua nguoi choi dua vao cash hay gold
                        origin_money = moneyBox.currentmoney();

                        //set lai tien cho nguoi choi
                        player->setMoney(isCash, origin_money);

						//neu la nguoi dang nhap thi cap nhat lai tien vao common
						if (moneyBox.userid() == Common::getInstance()->getUserId()){
							if (isCash){
								Common::getInstance()->setCash(origin_money);
							}
							else {
								Common::getInstance()->setGold(origin_money);
							}
						}

                        avatar = findAvatarOfPlayer(moneyBox.userid());
                        if (avatar != 0){
                            avatar->setMoney(origin_money);
							
							if (moneyBox.displaychangemoney() != 0){
								auto moneyText = MLabel::createUpdateMoney(moneyBox.displaychangemoney());
								moneyText->setPosition(Vec2(avatar->getPosition().x + avatar->avatar->getWidth() / 2,
									avatar->getPosition().y + avatar->avatar->getHeight()));
								this->addChild(moneyText);
							}
                        }
                    }
                }
            }
        }
        else {
            this->showToast(updatemoneyresponse->message().c_str(), 2);
        }
    }
}

void TLMienNam::startMatchResponseHandler() {
    BINStartMatchResponse *rs =
    (BINStartMatchResponse*)Common::getInstance()->checkEvent(NetworkManager::START_MATCH);
    if (rs != 0) {
        CCLOG("start match response: %s", rs->DebugString().c_str());
        matchRunning = rs->responsecode();
        if (rs->responsecode()) {

            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
                this->removeChildByTag(TAG_TIME_COUNTDOWN);
            }

            if (rs->has_countdowntimer() && rs->countdowntimer() >= 0) {
                setMatchCountDownTime(rs->countdowntimer());
            }
            
            if (rs->has_firstturnuserid()) {
                setFirstTurnUserId((int)rs->firstturnuserid());
            }
            
            if (!isUserPlaying()){ //neu la nguoi cho khi bat dau game thi khong hien thi nut san sang
                btn_san_sang->setVisible(false);
            }

            for (int i = 0; i < rs->args_size(); i++) {
                if (rs->args(i).key() == "currentCards") {
                    vector<int> current_card_values =
                    Common::getInstance()->convertStringsToInt(Common::getInstance()->split(rs->args(i).value(), ','));
                    sortCard(current_card_values);
                    
                    Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
					if (avatar != 0){
						avatar->runAction(MoveTo::create(0.2f, avatar->getAvatarPostion(0, origin, visibleSize, btn_start_match->getHeight())));
					}
                    
                } else {
                    //handle card remain count
                    std::string json = rs->args(i).value();
                    parseRemainCards(json);
                }
            }
            
        } else {
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void TLMienNam::playerEnterRoomResponseHandler() {
    BINPlayerEnterRoomResponse *newplayerresponse = (BINPlayerEnterRoomResponse*)
    Common::getInstance()->checkEvent(NetworkManager::PLAYER_ENTER_ROOM);
    if (newplayerresponse != 0) {
        CCLOG("player enter room response: %s", newplayerresponse->DebugString().c_str());
        if (newplayerresponse->responsecode()) {
            TLMNPlayer player = convertFromBINPlayer(newplayerresponse->player());

            //neu la nguoi choi
            if (newplayerresponse->enterroomstatus() == PlayerState::PLAYING){
                TLMienNam::player_list.push_back(newplayerresponse->player());
                lst_player.push_back(player);

				showInvitePlayer(lst_player.size());  //show moi choi

                sortListPlayer();
                int index_pos_newplayer = findIndexPlayer(lst_player, player);
                if (index_pos_newplayer != -1){
                    setPositionPlayer(lst_player[index_pos_newplayer], index_pos_newplayer);
                }

                //neu so luong nguoi choi lon hon 2 thi hien thi btn startmatch
                if (Common::getInstance()->getUserId() == getOwnerUserId() && lst_player.size() >= 2){
                    btn_start_match->setVisible(true);
                }

				// thoi gian doi khi thay doi chu phong
				if (newplayerresponse->changeownerroomcd() > 0 && this->getChildByTag(TAG_TIME_COUNTDOWN) == nullptr) {
					int time_wait = newplayerresponse->changeownerroomcd() / 1000;
					addCountDown(time_wait);
				}
            } else {
                // xu ly voi nguoi cho
                if (newplayerresponse->enterroomstatus() == PlayerState::WAITING){
                    lst_waiting.push_back(player);
                    //hien thi danh sach nguoi cho len man hinh
                    resetListWaiting();
                    showWaitingPlayerOnScene(lst_waiting);
                }
            }
        } else {
            this->showToast(newplayerresponse->message().c_str(), 2);
            if (Common::getInstance()->getUserId() == this->_ownerUserId) {
                this->is_create_room = true;
                btn_start_match->setVisible(this->is_create_room);
            }
        }
    }
}

void TLMienNam::matchBeginResponseHandler() {
    BINMatchBeginResponse *matchbeginresponse = (BINMatchBeginResponse*)
    Common::getInstance()->checkEvent(NetworkManager::MATCH_BEGIN);
    if (matchbeginresponse != 0) {
        if (matchbeginresponse->responsecode()) {
            /*set match count down time*/
            setMatchCountDownTime(matchbeginresponse->countdowntimer());
            
            //nguoi choi dau tien bat dau tinh count down
            long long first_turn_user_id = getFirstTurnUserId();

            btn_danh_bai->setVisible((first_turn_user_id) == Common::getInstance()->getUserId());
            btn_bo_luot->setVisible(false);

            Avatar* avatar = findAvatarOfPlayer(first_turn_user_id);
            if (avatar != 0){
                avatar->updateProgressCircleBar(100, getMatchCountDownTime());
            }
        } else {
            this->showToast(matchbeginresponse->message().c_str(), 2);
        }
    }
}

void TLMienNam::prepareNewMatchResponseHandler() {
    BINPrepareNewMatchResponse* prepare_new_match_response =
    (BINPrepareNewMatchResponse*)Common::getInstance()->checkEvent(NetworkManager::PREPARE_NEW_MATCH);
    if (prepare_new_match_response != 0) {
        CCLOG("prepare new match response: %s", prepare_new_match_response->DebugString().c_str());
        if (prepare_new_match_response->responsecode()) {
            setChangeOwnerRoomCd(prepare_new_match_response->countdowntimer());
            if (getChangeOwnerRoomCd() > 0) {
                CCLOG("prepare newmatch time countdown %d", getChangeOwnerRoomCd());
                int time_wait = getChangeOwnerRoomCd() / 1000;
                addCountDown(time_wait);
            }
            //hung
            resetMatch();
        }
    }
}

void TLMienNam::cancelExitAfterMatchEndResponseHandler() {
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


void TLMienNam::kickUserResponseHandler() {
    BINKickPlayerOutResponse* kick_user_response =
        (BINKickPlayerOutResponse *) Common::getInstance()->checkEvent(NetworkManager::KICK_USER);
    if (kick_user_response != 0 && kick_user_response->kickeduserid()) {
        CCLOG("kick user response: %s", kick_user_response->DebugString().c_str());
    }
}

void TLMienNam::readyToPlayResponseHandler(){
    BINReadyToPlayResponse* ready_to_play_response =
        (BINReadyToPlayResponse *)Common::getInstance()->checkEvent(NetworkManager::READY_TO_PLAY);

    if (ready_to_play_response != 0){
        CCLOG("ready to play response: %s", ready_to_play_response->DebugString().c_str());
        if (ready_to_play_response->responsecode()){
            //if (btn_san_sang->isVisible()){
			if (Common::getInstance()->getUserId() == ready_to_play_response->readyuserid()){
                btn_san_sang->setVisible(false);
				showBtnWithWatingPlayer(true);
            }

            long long ready_player_id = ready_to_play_response->readyuserid();
            int table_index = ready_to_play_response->tableindex();
            TLMNPlayer* player = (TLMNPlayer*) findWaiting(ready_player_id);

            if (player != 0){
                //day vao lst playing
                TLMNPlayer waiting_player = *player;
                waiting_player.setTableIndex(table_index);
                lst_player.push_back(waiting_player);

				showInvitePlayer(lst_player.size());  //show moi choi

                //remove avatar tren ban choi
                resetDisplayAvatar();
                //dat waiting player len ban choi
                sortListPlayer();
                displayInfoRemainCard(lst_player);

				//neu so luong nguoi choi lon hon 2 thi hien thi btn startmatch
				if (Common::getInstance()->getUserId() == getOwnerUserId() && lst_player.size() >= 2){
					btn_start_match->setVisible(true);
				}

                //xoa khoi lst_waiting
                deleteWaitingPlayer(waiting_player.getID());

                //hien thi lai danh sach cho len giao dien
                resetListWaiting();
                showWaitingPlayerOnScene(lst_waiting);
            }
        }
        else {
            this->showToast(ready_to_play_response->message().c_str(), 2);
        }
    }
}

void TLMienNam::changeRuleResponseHandler() {
    BINChangeRuleResponse* change_rule_response =
    (BINChangeRuleResponse *)Common::getInstance()->checkEvent(NetworkManager::CHANGE_RULE);
    if (change_rule_response != 0) {
        CCLOG("change rule response: %s", change_rule_response->DebugString().c_str());
        if(change_rule_response->responsecode()) {
            hiddenCardRemaingCount = !hiddenCardRemaingCount;
        }
    }
}


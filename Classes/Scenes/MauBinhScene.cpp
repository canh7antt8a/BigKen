//
//  MauBinhScene.cpp
//  MyCards
//
//  Created by hungle on 8/1/16.
//
//

#include "MauBinhScene.hpp"
#include "Handler/MauBinhCardHandler.h"
#include "Utils/Common.h"

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

Scene* MauBinhScene::createScene(int _roomIndex, vector<BINPlayer> _playerList, vector<BINPlayer> _waitingPlayerList,
                                    bool _createRoom, int _gameTag, bool _isDisplayRoomList, bool passwordRequired,
                                    bool isVipRoom, int minBet, BINEnterRoomResponse* reEnterRoomResponse) {
    
    auto scene = Scene::create();
    auto layer = MauBinhScene::create();
    layer->setRoomIndex(_roomIndex);
    layer->setVipRoom(isVipRoom);
    Common::getInstance()->setGameTag(_gameTag);
    layer->setCreateRoom(_createRoom);
    layer->setPassWordRequired(passwordRequired);
    layer->setPlayerList(_playerList);
    
    layer->setWaitingPlayerList(_waitingPlayerList);
    layer->setEnterRoomResponse(reEnterRoomResponse);
    layer->setMinBet(minBet);
    layer->initMenu();
    layer->initGame();
    
    scene->addChild(layer);
    
    return scene;
}

float MauBinhScene::getTurnRequestTime() const {
    return turnRequestTime; 
}

bool MauBinhScene::isStartMatch() const {
    return start_match;
}

void MauBinhScene::setTurnRequestTime(float _turnRequestTime) {
    this->turnRequestTime = _turnRequestTime; 
}

void MauBinhScene::setStartMatch(bool _startMatch) {
    this->start_match = _startMatch; 
}

void MauBinhScene::initMenu() {
    PlayScene::initMenu(); 

    auto bkgTable = MSprite::create("sprite_table.png");
    bkgTable->setScale(width*0.8f / bkgTable->getWidth());
    bkgTable->setContentSize(Size(width*0.8f, bkgTable->getHeight()*bkgTable->getScale()));
    bkgTable->setPosition(Point(origin.x + visibleSize.width / 2 - bkgTable->getWidth() / 2,
        origin.y + visibleSize.height / 2 - bkgTable->getHeight() / 2));
    this->addChild(bkgTable);


    spr_compare_turn = MSprite::create("mau_binh/bg_compare_turn.png");
    spr_compare_turn->setPosition(Vec2(btn_message->getPosition().x - 
        spr_compare_turn->getWidth(), btn_message->getPosition().y + 
        btn_message->getHeight() * 1.2f));

    spr_compare_turn->setVisible(false);
    this->addChild(spr_compare_turn); 

    btn_san_sang = MButton::create(BTN_BUTTON, "Sẵn sàng", 25, TAG_MAUBINH_BTN_SANSANG);
    btn_san_sang->setScale(0.8f);
    btn_san_sang->setPosition(Vec2(btn_message->getPosition().x - btn_san_sang->getWidth() - 15,
        btn_message->getPosition().y));

    btn_san_sang->addTouchEventListener(CC_CALLBACK_2(MauBinhScene::cardCallBack, this));
    btn_san_sang->setVisible(true);
    this->addChild(btn_san_sang);

    btn_start_match = MButton::create(BTN_START_MATCH, TXT_BTN_START_MATCH, 25, TAG_MAUBINH_BTN_START_MATCH);
    // btn_start_match->setScale(0.8f);
    btn_start_match->setPosition(Vec2(btn_message->getPosition().x - btn_start_match->getWidth() - BUTTON_PADDING,
                                      btn_message->getPosition().y));
    btn_start_match->setVisible(false);
    btn_start_match->addTouchEventListener(CC_CALLBACK_2(MauBinhScene::cardCallBack, this));

    //nut xep bai
    btn_finish = MButton::create(BTN_BUTTON, TXT_BTN_FINISH, 25, TAG_MAUBINH_BTN_XONG);
    btn_finish->setPosition(Vec2(btn_message->getPosition().x - btn_finish->getWidth() - BUTTON_PADDING,
                                 btn_message->getPosition().y));
    btn_finish->setVisible(false);
    btn_finish->addTouchEventListener(CC_CALLBACK_2(MauBinhScene::cardCallBack, this));
    this->addChild(btn_start_match);
    this->addChild(btn_finish);
    
    sprite_lung = MSprite::create("mau_binh/sprite_lung_maubinh.png");
    sprite_lung->setPosition(Vec2(originX + width/2 - sprite_lung->getWidth()/2,
                                  btn_message->getPosition().y + (width/12.5f)*CARD_RATIO*(1*1.3f+0.75f)
                                  -sprite_lung->getHeight()/2));
    sprite_lung->setVisible(false);
    this->addChild(sprite_lung,CARD_UP+2);

    label_lung = MLabel::create("LỦNG", btn_message->getHeight(), Color3B(255, 0, 0));
    label_lung->enableOutline(Color4B(0,0,0,200),4);
    label_lung->setOpacity(200);
    label_lung->setPosition(Vec2(originX + width/2 - label_lung->getWidth() / 2,
                            btn_message->getPosition().y + (width/12.5f)*CARD_RATIO*(1*1.3f+0.75f)
                            -label_lung->getHeight()/2));
    label_lung->setVisible(false);
    this->addChild(label_lung,CARD_UP+2);

    label_turn[0] = MLabel::create("Mậu thầu", btn_message->getHeight() / 2.2f,Color3B::YELLOW);
    label_turn[0]->enableOutline(Color4B(0,0,0,200),2);

    label_turn[1] = MLabel::create("Đôi", btn_message->getHeight() / 2.2f, Color3B::YELLOW);
    label_turn[1]->enableOutline(Color4B(0,0,0,200),2);

    label_turn[2] = MLabel::create("Thung phá sảnh", btn_message->getHeight() / 2.2f, Color3B::YELLOW);
    label_turn[2]->enableOutline(Color4B(0,0,0,200),2);

    this->addChild(label_turn[0]);
    this->addChild(label_turn[1]);
    this->addChild(label_turn[2]);
    label_turn[0]->setVisible(false);
    label_turn[1]->setVisible(false);
    label_turn[2]->setVisible(false);
}

bool MauBinhScene::init() {
    if (!PlayScene::init()) {
        return false;
    }
    
    this->scheduleUpdate();
    
    return true;
}

Vec2 MauBinhScene::getCardPostion(int i, int j) {
    return MVec2(width/2 + cardWidth()*(j - (cardSprites[i].size() -1)*0.5f),
                 height/2 + cardWidth()*CARD_RATIO*(i - 1));
}

bool containPointCard(Vec2 location,Vec2 pos,Size size){
    return (location.x >= pos.x && location.x <= pos.x + size.width
            && location.y >= pos.y && location.y <= pos.y + size.height);
}

void MauBinhScene::addTurnCardSuggest(int index) {
    int ranking = rank[index];
    
    for (int j = 0; j < cardSprites[index].size(); j++)
        cardSprites[index][j]->showHidden(true);
    switch (ranking)
    {
    case MauBinhCardHandler::THUNG_PHA_SANH:
    case MauBinhCardHandler::THUNG:
    case MauBinhCardHandler::SANH:
    case MauBinhCardHandler::CU_LU:
    case MauBinhCardHandler::MAU_THAU: 
    {
        for (int j = 0; j < cardSprites[index].size(); j++) {
            cardSprites[index][j]->showHidden(false);
        }
    }
        break;
    case MauBinhCardHandler::TU_QUY:
    {
        vector<int> four_card = turn_cards_values[index].second[0];

        vector<int> single_card = turn_cards_values[index].second[1];
        for (int j = 0; j < cardSprites[index].size(); j++) {
            if (cardSprites[index][j]->getNumberValue() == single_card[0]) {
                cardSprites[index][j]->showHidden(true);
            } else {
                cardSprites[index][j]->showHidden(false);
            }
        }
    }
        break;
    case MauBinhCardHandler::SAM_CO:
    {
        vector<int> three_card = turn_cards_values[index].second[0];
        for (int j = 0; j < cardSprites[index].size(); j++) {
            bool isHidden = true;
            for (int card : three_card) {
                if (cardSprites[index][j]->getNumberValue() == card) {
                    isHidden = false;
                    break;
                }
            }
            cardSprites[index][j]->showHidden(isHidden);
        }
    }
        break;
    case MauBinhCardHandler::THU:
    case MauBinhCardHandler::DOI:
    {
        int numberPair = (ranking == MauBinhCardHandler::THU ? 2 : 1);
        if (numberPair == 2) {
            CCLOG("Thu");
        }
        vector<int> pair_card;
        for (int i = 0; i < numberPair; i++) {
            for (int card : turn_cards_values[index].second[i]) {
                pair_card.push_back(card);
            }
        }

        for (int j = 0; j < cardSprites[index].size(); j++) {
            bool isHidden = true;
            for (int card : pair_card) {
                if (cardSprites[index][j]->getNumberValue() == card) {
                    isHidden = false;
                    break;
                }
            }
            cardSprites[index][j]->showHidden(isHidden);
        }
    }
        break;
    default:
        break;
    }   
}


void MauBinhScene::getAllRankCardValue() {
    //xet rank
    for (int i = 0; i < 3; i++) {
        vector<int> turn_cards;
        for (int j = 0; j < cardSprites[i].size(); j++) {
            turn_cards.push_back(cardSprites[i][j]->getNumberValue());
            CCLOG("Card value: %d", turn_cards.back());
        }
        sort(turn_cards.begin(), turn_cards.end());
        if (i == 2) {
            CCLOG("index: %d", i);
        }
        turn_cards_values[i] = MauBinhCardHandler::getInstance()->getValue(turn_cards);
        rank[i] = turn_cards_values[i].first;
        CCLOG("rank %d: %d", i + 1, rank[i]);
        label_turn[i]->setString(StringUtils::format("%s",
            MauBinhCardHandler::getInstance()->getTurnValue(rank[i]).c_str()));
        label_turn[i]->setVisible(true);
        //xet suggest
        addTurnCardSuggest(i);
    }



    bool isBlack = false;
    for (int i = 1; i < 3; i++) {
        int prevRank = rank[i - 1];
        int currentRank = rank[i];
        if (prevRank < currentRank) {
            isBlack = true;
            break;
        }

        if (prevRank == currentRank) {
            switch (currentRank) {
            case MauBinhCardHandler::THUNG_PHA_SANH:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];

                if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[1]) <
                    MauBinhCardHandler::getInstance()->getCardValue(current_cards[1])) {
                    isBlack = true;
                }
            }
                break;
            case MauBinhCardHandler::TU_QUY:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];

                if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
                    MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
                    isBlack = true;
                }
            }
                break;
            case MauBinhCardHandler::CU_LU:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];

                if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
                    MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
                    isBlack = true;
                }
            }
                break;
            case MauBinhCardHandler::THUNG:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];
                for (int i = 0; i < prev_cards.size(); i++) {
                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[i])
                        < MauBinhCardHandler::getInstance()->getCardValue(current_cards[i])) {
                        isBlack = true;
                        break;
                    }

                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[i])
                        > MauBinhCardHandler::getInstance()->getCardValue(current_cards[i])) {
                        break;
                    }
                }
            }
                break;
            case MauBinhCardHandler::SANH:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];

                if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[1]) <
                    MauBinhCardHandler::getInstance()->getCardValue(current_cards[1])) {
                    isBlack = true;
                }
            }
                break;
            case MauBinhCardHandler::SAM_CO:
            {
                vector<int> prev_cards = turn_cards_values[i - 1].second[0];
                vector<int> current_cards = turn_cards_values[i].second[0];

                if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
                    MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
                    isBlack = true;
                }
            }
                break;
            case MauBinhCardHandler::THU:
            {
                for (int j = 0; j < turn_cards_values[i].second.size(); j++) {
                    vector<int> prev_card = turn_cards_values[i - 1].second[j];
                    vector<int> current_card = turn_cards_values[i].second[j];
                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        isBlack = true;
                        break;
                    }

                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        break;
                    }
                }
            }
                break;
            case MauBinhCardHandler::DOI:
            {
                for (int j = 0; j < turn_cards_values[i].second.size(); j++) {
                    vector<int> prev_card = turn_cards_values[i - 1].second[j];
                    vector<int> current_card = turn_cards_values[i].second[j];
                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        isBlack = true;
                        break;
                    }

                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        break;
                    }
                }
            }
                break;
            case MauBinhCardHandler::MAU_THAU:
            {
                for (int j = 0; j < turn_cards_values[i].second.size(); j++) {
                    vector<int> prev_card = turn_cards_values[i - 1].second[j];
                    vector<int> current_card = turn_cards_values[i].second[j];
                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        isBlack = true;
                        break;
                    }

                    if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                        > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                        break;
                    }
                }
            }
                break;
            default:
                break;
            }
        }
    }


    //xét mậu binh
    if (MauBinhCardHandler::getInstance()->isWildCards(current_card_values)) {
        sprite_lung->setVisible(true);
        label_lung->setVisible(true);
        label_lung->setColor(Color3B::YELLOW);
        label_lung->setString("Mậu binh");
        label_lung->setPosition(Vec2(originX + width / 2 - label_lung->getWidth() / 2,
                                label_lung->getPosition().y));
    }
    else if (isBlack) {
        label_lung->setString("Lủng");
        label_lung->setPosition(Vec2(originX +width / 2 - label_lung->getWidth() / 2,
                                label_lung->getPosition().y));
        label_lung->setColor(Color3B::WHITE);
        label_lung->setVisible(true);
        sprite_lung->setVisible(true);
    } else {
        label_lung->setVisible(false);
        sprite_lung->setVisible(false);
    }
}

void MauBinhScene::onEventCardSpriteMove(int value, float x, float y) {

    PosIndex posCurrent;
    PosIndex posNext;
    Vec2 pt = Vec2(x,y);
    bool currentCheck = false;
    for(int i=0;i<3;i++) {
        for(int j = 0; j< cardSprites[i].size();j++) {
            if(cardSprites[i][j]->getNumberValue() == value) {
                posCurrent.x = i;
                posCurrent.y = j;
                currentCheck = true;
                break;
            }
        }
    }
    
    bool move = false;
    for(int i=0;i<3;i++) {
        for(int j = 0; j< cardSprites[i].size();j++) {
            if (cardSprites[i][j]->getNumberValue() != value && !move
                && cardSprites[i][j]->getBoundingBox().containsPoint(pt)) {
                posNext.x = i;
                posNext.y = j;
                move = true;
                break;
            }
        }
    }
    if(move && currentCheck){
        cardSprites[posCurrent.x][posCurrent.y]->runAction(MoveTo::create(0.1f,cardSprites[posNext.x][posNext.y]->getCurrentPos()));
        cardSprites[posNext.x][posNext.y]->runAction(MoveTo::create(0.1f,cardSprites[posCurrent.x][posCurrent.y]->getCurrentPos()));
        Vec2 posCurrentCard = cardSprites[posCurrent.x][posCurrent.y]->getCurrentPos();
        cardSprites[posCurrent.x][posCurrent.y]->setCurrentPos(cardSprites[posNext.x][posNext.y]->getCurrentPos());
        cardSprites[posNext.x][posNext.y]->setCurrentPos(posCurrentCard);
        
        this->swapCardSprite(cardSprites[posCurrent.x][posCurrent.y],cardSprites[posNext.x][posNext.y]);
        Common::getInstance()->swap(current_card_values[5*posCurrent.x + posCurrent.y],current_card_values[5*posNext.x + posNext.y]);
        
        for(int i=0;i<3;i++) {
            for(int j = 0; j< cardSprites[i].size();j++) {
                CCLOG("CARDSPRITE : %d",cardSprites[i][j]->getNumberValue());
            }
        }
        getAllRankCardValue();
        cancelFinishSortCard();
        // check tai day
    }else{
        cardSprites[posCurrent.x][posCurrent.y]->runAction(MoveTo::create(0.1f,cardSprites[posCurrent.x][posCurrent.y]->getCurrentPos()));
    }
}

void MauBinhScene::swapCardSprite(MauBinhCardSprite* &currentCard,MauBinhCardSprite* &nextCard){
    auto temp = currentCard;
    currentCard = nextCard;
    nextCard = temp;
}

void MauBinhScene::initGame() {
    // TO DO
    capacity_size = 4;
    
    //text emotion
    for(int i = 11 ;i< 35;i++){
        emotion_id.push_back(i);
    }
    emotion_text = {"Rồng cuốn","Sảnh rồng","13 lá đồng màu","12 lá đồng màu","5 đôi 1 xám","Lục phế bôn","3 thùng","3 sảnh","Thùng"
                    ,"Thùng chi giữa","Tứ quý chi đầu","Tứ quý chi giữa","Cù lũ","Cù lũ chi giữa","Cù lũ chi giữa","Thùng","Sảnh"
                    ,"Xám","Xám chi cuối","Thú","Đôi","Mậu thầu","Binh lủng","Thắng sập hầm","Thua sập hầm"};
    emotion_bkg = {"mau_binh/effect_doi.png"};

    countSendTurn = 0;
    countNumberOfTime = 0;
    setStartMatch(false);
    setTurnRequestTime(0);

    if (is_create_room){
        int current_user_id = Common::getInstance()->getUserId();
        setOwnerUserId(current_user_id);
	}

    setListPlayerFromParams(MauBinhScene::player_list, MauBinhScene::waiting_player_list);

    if (enter_room_response != 0) {
        handleReEnterRoom(enter_room_response);
    }
}

void MauBinhScene::handleReEnterRoom(BINEnterRoomResponse *response) {
    
    if (response->has_message()){
        showToast(response->message().c_str(), 2);
    }
    
    if (response->responsecode()) {
        bool isArrange = false;
        for (int i = 0; i < response->args_size(); i++) {
            BINMapFieldEntry entry = response->args(i);
            if ((entry.key() == "firstBranch") || (entry.key() == "centerBranch") || (entry.key() == "lastBranch")) {
                vector<int> card_values = Common::getInstance()->convertStringsToInt(
                    Common::getInstance()->split(entry.value(), ','));
                current_card_values.insert(current_card_values.end(), card_values.begin(), card_values.end());
            }else if(entry.key() == "tableStatus") {
                isArrange = (entry.value() == "isArrange");
            }
        }
        
        if(!isArrange) {
            label_lung->setVisible(false);
            sprite_lung->setVisible(false);
            label_turn[0]->setVisible(false);
            label_turn[1]->setVisible(false);
            label_turn[2]->setVisible(false);
        }else{
            MauBinhCardHandler::getInstance()->sortCard(current_card_values);
            if (!cards.empty()) cards.clear();
            for (int i = 0; i < 13; i++) {
                Card card;
                card.value = current_card_values[i];
                cards.push_back(card);
            }
            addSpriteCards(0);
        }
        CCLOG("IS : %s",isArrange ? "isArrange : TRUE" : "isArrange : FALSE");
    }
}

void MauBinhScene::addSpriteCards(float dt){
    // add spriteCards
    float spriteCardWidth = width/12.5f;
    for(int i = 0;i < 13;i ++){
        PosIndex pos;
        pos.x = i%5;
        pos.y = i/5;
        auto cardSprite = MauBinhCardSprite::createCard(cards[i], pos, spriteCardWidth,this);
        cardSprites[i/5].push_back(cardSprite);
    }
    
    for(int i =0; i< 3; i ++) {
        for(int j = 0; j< cardSprites[i].size() ; j++) {
            cardSprites[i][j]->setPosition(Vec2(originX + width/2 + spriteCardWidth*(cardSprites[i][j]->getPosIndex().x
                                                                                     - (cardSprites[i].size() -1)*0.5f),
                                          btn_message->getPosition().y + spriteCardWidth*CARD_RATIO*(i*1.3f+0.75f)));
            cardSprites[i][j]->setCurrentPos(cardSprites[i][j]->getPosition());
            this->addChild(cardSprites[i][j]);
            cardSprites[i][j]->setLocalZOrder(CARD_DOWN);
        }
        label_turn[i]->setPosition(Vec2(originX + width/2 - spriteCardWidth*cardSprites[i].size()/2,
                                         btn_message->getPosition().y + spriteCardWidth*CARD_RATIO*(i*1.3f+1.25f)));
    }
    
    for(int i = (int)cardViews[0].size() - 1;i >=0 ;i--){
        for(int j = (int)cardViews[0][i].size() - 1;j >= 0 ;j--){
            cardViews[0][i][j]->removeFromParentAndCleanup(true);
        }
    }
    
    Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
    if(avatar!=0){
        avatar->runAction(EaseBackOut::create(MoveTo::create(0.5f,Vec2(originX+ width/2 - spriteCardWidth*2.8f
                                                                       - avatar->getContentSize().width,
                                                                       avatar->getAvatarPostion(0, origin, visibleSize,
                                                                                                btn_start_match->getHeight()).y))));
    }
    btn_finish->setVisible(true);
    getAllRankCardValue();

}

void MauBinhScene::distributeCardEffect(){
    if (!cards.empty()) cards.clear();
    for (int i = 0; i < 13; i++) {
        Card card; 
        card.value = current_card_values[i];
        cards.push_back(card);
    }
    for (int i = 0; i < 13; i++){
        cardsx[i / 5].push_back(cards[i].getValue());
    }
    float timeMove = 0;
    for (int i = 0; i < 3; i++){
        vector<OtherCardSprite*> cardSprites;
        for (int j = 0; j < cardsx[i].size(); j++){
            timeMove += 0.1f;
            auto card = OtherCardSprite::createSelf(cardsx[i][j],cardWidth());
            card->setPosition(MVec2(width / 2 - cardWidth() / 2, height / 2));
            auto pos = MVec2(width / 2 + cardWidth()*(j - 0.5f*(cardsx[i].size() - 1) - 0.5f),
                btn_message->getPosition().y + cardWidth()*CARD_RATIO*(i + 0.5f));
            card->runAction(Sequence::create(DelayTime::create(2.0f + timeMove), MoveTo::create(0.2f, pos), NULL));
            cardSprites.push_back(card);
        }
        cardViews[0].push_back(cardSprites);
    }

    for (int i = (int)cardViews[0].size() - 1; i >= 0; i--) {
        for (int j = (int)cardViews[0][i].size() - 1; j >= 0; j--) {
            this->addChild(cardViews[0][i][j]);
        }
    }
    
    auto card = OtherCardSprite::create(1, cardWidth());
    card->setAnchorPoint(Point::ZERO);
    card->setPosition(MVec2(width / 2 - cardWidth()*0.5f, height / 2));
    card->runAction(Sequence::create(DelayTime::create(2.0f + 0.1f * 13), RemoveSelf::create(), NULL));
    this->addChild(card);

    this->scheduleOnce(schedule_selector(MauBinhScene::addSpriteCards), 5.0f);
    
    auto avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
    if(avatar==0){
        return;
    }
    avatar->runAction(EaseBackOut::create(MoveTo::create(0.5f,Vec2(originX+ width/2 - (width/12.5f)*2.8f - avatar->getContentSize().width,
                                               avatar->getAvatarPostion(0, origin, visibleSize, btn_start_match->getHeight()).y))));
}

void MauBinhScene::prepareNewMatchResponseHandler() {
    BINPrepareNewMatchResponse *response = (BINPrepareNewMatchResponse *)
        Common::getInstance()->checkEvent(NetworkManager::PREPARE_NEW_MATCH);
    if (response != 0) {
        CCLOG("prepare new match response: %s", response->DebugString().c_str());
        
        /*Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
        avatar->runAction(EaseBackOut::create(MoveTo::create(0.5f,Vec2(originX+ width/2 - avatar->getContentSize().width/2,
                                                   avatar->getAvatarPostion(0, origin, visibleSize, btn_start_match->getHeight()).y))));*/
        for(Avatar* avatar : avatars){
            auto pos = avatar->getAvatarPostion(avatar->getPositionIndex(),origin,visibleSize,btn_message->getHeight());
            if(avatar->getPositionIndex() == 0 ){
                pos = Vec2(originX+width/2 - avatar->getContentSize().width/2,pos.y);
            }
            avatar->runAction(EaseBackOut::create(MoveTo::create(0.25f,pos)));
        }
        
        for(int i = 0;i < effect_Text.size(); i++){
            effect_Text[i]->removeFromParentAndCleanup(true);
        }
        effect_Text.clear();
        
        cards.clear();
        current_card_values.clear();
        
        Vector<Node*> children = this->getChildren();
        for(int i = 0; i < children.size(); i ++) {
            MauBinhCardSprite* card = dynamic_cast<MauBinhCardSprite*>(children.at(i));
            if (card != nullptr) {
                card->removeFromParentAndCleanup(true);
            }
        }
        
        Vector<Node*> childrenCard = this->getChildren();
        for(int i = 0; i < childrenCard.size(); i ++) {
            OtherCardSprite* card = dynamic_cast<OtherCardSprite*>(childrenCard.at(i));
            if (card != nullptr) {
                card->removeFromParentAndCleanup(true);
            }
        }
        
        for(int i = 0;i < 3 ;i++){
            cardSprites[i].clear();
            cardsx[i].clear();
        }
        
        for(int i = 0 ;i < 4;i++){
            cardViews[i].clear();
            //card_matchends[i].clear();
        }

        setStartMatch(false);
        setTurnRequestTime(0);

        for (int i = 0; i < lst_player.size(); i++) 
            lst_player[i].setStatus(MauBinhPlayer::NO_STATUS);
           
        if (response->has_countdowntimer()) {
            _timeCountDown = response->countdowntimer();
            for (int i = 0; i < avatars.size(); i++) {
                if (avatars[i]->getPositionIndex() != 0) {
                    avatars[i]->hiddenNumberCardAndCover(false);
                    avatars[i]->hideNumberCard(true);
                    avatars[i]->showXong(false);
                    avatars[i]->setWin(false);
                }
            }

            auto avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
            if (avatar != 0) {
                avatar->updateProgressCircleBar(100, _timeCountDown);
            }
            btn_start_match->setVisible(is_create_room && lst_player.size() >= 2);
        }
    }
}

void MauBinhScene::playerExitAfterMatchEndResponseHandler() {
    BINPlayerExitAfterMatchEndResponse *response = (BINPlayerExitAfterMatchEndResponse *)
        Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_AFTER_MATCH_END);
    if (response != 0) {
        CCLOG("player exit after match end: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            int leng = (int)lst_player.size();
            for (int i = 0; i < leng; i++) {
                //reset position
                string user_id = lst_player[i].getID();
                if (user_id == Common::getInstance()->convertIntToString((int)response->exituserid())){
                    /*char message[60];
                    sprintf(message, "Người chơi %s đăng ký rời bàn chơi", lst_player[i].getName().c_str());
					this->showToast(message, 2);*/

					auto avatar = findAvatarOfPlayer(response->exituserid());
					if (avatar != 0){
						avatar->showRegisterExitRoom(true);
					}
                    break;
                }
            }
        } else {
            this->showToast(response->message().c_str(), 2);
        }
    }
}

void MauBinhScene::cancelExitAfterMatchEndResponseHandler() {
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

//tim nguoi cho
Player* MauBinhScene::findWaiting(long long player_id){
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

void MauBinhScene::deleteWaitingPlayer(string player_id){
    int k = -1;
    for (int i = 0; i < lst_waiting.size(); i++){
        if (lst_waiting[i].getID() == player_id){
            k = i;
        }
    }

    if (k != -1 && !lst_waiting.empty())
        lst_waiting.erase(lst_waiting.begin() + k);
}

void MauBinhScene::playerExitRoomResponseHandler() {
    BINPlayerExitRoomResponse* _player_exit_room_response =
        (BINPlayerExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_ROOM);
    if (_player_exit_room_response != 0) {
        CCLOG("exit room player response: %s", _player_exit_room_response->DebugString().c_str());
        if (_player_exit_room_response->responsecode()) {
            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
                this->removeChildByTag(TAG_TIME_COUNTDOWN);
            }

            Player* playerWaiting = findWaiting(_player_exit_room_response->exituserid());
            //xoa nguoi cho di
            if (playerWaiting != 0){
                deleteWaitingPlayer(playerWaiting->getID());

                //hien thi lai danh sach cho len giao dien
                resetListWaiting();
                showWaitingPlayerOnScene(lst_waiting);
            }
            else {
                int leng = (int)lst_player.size();

                int ownerUserId = (int)_player_exit_room_response->owneruserid();
                auto common = Common::getInstance();
                common->setOwnerUserId(ownerUserId);
                setOwnerUserId(ownerUserId);
                is_create_room = common->getUserId() == ownerUserId;
                
                for (int i = 0; i < leng; i++) {
                    //xoa nguoi choi khoi ban choi
                    int user_id = Common::getInstance()
                        ->convertStringToInt(lst_player[i].getID());
                    if (user_id == _player_exit_room_response->exituserid()){
                        lst_player.erase(lst_player.begin() + i);

						showInvitePlayer((int)lst_player.size());

                        auto avatar = findAvatarOfPlayer(_player_exit_room_response->exituserid());
                        if(avatar!=0){
                            //xoa avatar khoi ban choi (khong hien thi nua)
                            removeOutTablePlay(avatar);
                            //xoa khoi danh sach luu avatars
                            avatars.erase(std::remove(avatars.begin(), avatars.end(), avatar), avatars.end());
                        }

                        if (_player_exit_room_response->changeownerroomcd() > 0){
                            CCLOG("player exit room time countdown %d", _player_exit_room_response->changeownerroomcd());
                            int time_wait = _player_exit_room_response->changeownerroomcd() / 1000;
                            addCountDown(time_wait);
                        }
                        break;
                    }
                }
            }
        }

        if (_player_exit_room_response->has_message()){
            //showToast(_player_exit_room_response->message().c_str(), 2);
        }
    }
}

void MauBinhScene::handleFinishSortCard(int user_id, bool isFinish) {
    //TODO: HungLe
    /*
    isFinish = true, đã xếp xong bài
    isFinish = false, bỏ xếp bài
    */
    auto avatar = findAvatarOfPlayer(user_id);
    if(avatar == 0){
        return;
    }
    avatar->showXong(isFinish);
}

void MauBinhScene::turnResponsehandler() {
    BINTurnResponse *response = (BINTurnResponse *)
        Common::getInstance()->checkEvent(NetworkManager::TURN);
    if (response != 0) {
        CCLOG("turn response: %s", response->DebugString().c_str());

        if (response->responsecode()) {
            if (response->args_size() > 0) {
                for (int i = 0; i < response->args_size(); i++) {
                    BINMapFieldEntry entry = response->args(0);
                    int user_id = Common::getInstance()->convertStringToInt(entry.key());
                    string status = entry.value(); 
                    if (status == "isFinishArrange"){
                        if (user_id == Common::getInstance()->getUserId()) {
                            setFinishTurn(MauBinhScene::IN_PROGRESS);
                            btn_finish->setVisible(false);
                        }
                        else {
                            //
                            handleFinishSortCard(user_id, true);
                        }
                    }
                    else {
                        if (user_id == Common::getInstance()->getUserId()) {
                            setFinishTurn(MauBinhScene::NOT_READY);
                            btn_finish->setVisible(true);
                        }
                        else {
                            //
                            handleFinishSortCard(user_id, false);
                        }
                    }
                }
            }
        }
        else if (response->has_message()) {
            this->showToast(response->message().c_str(), 2);
        }

        
    }
}

Player* MauBinhScene::findPlayer(long long player_id){
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


void MauBinhScene::updateMoneyResponseHandler() {
    BINUpdateMoneyResponse *response = (BINUpdateMoneyResponse *)
        Common::getInstance()->checkEvent(NetworkManager::UPDATE_MONEY);
    if (response != 0) {
        CCLOG("update money response: %s", response->DebugString().c_str());
        if (response->has_message()) {
            this->showToast(response->message().c_str(), 2);
        }

        if (response->responsecode()) {
            if (response->moneyboxes_size() > 0) {

                BINMoneyBox moneyBox;
                long long origin_money; //so tien ma nguoi choi dang co
                Player* player;

                Avatar* avatar;
                for (int i = 0; i < response->moneyboxes_size(); i++) {
                    moneyBox = response->moneyboxes(i); //money_boxe : userId , money, reason
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
                            }else {
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
								this->addChild(moneyText,INDEX_UPDATE_MONEY);
							}
                        }
                    }
                }
            }
        }
    }
}

void MauBinhScene::setMatchCountDownTime(int timeCountDown) {
    this->_timeCountDown = timeCountDown;
}

int MauBinhScene::getMatchCountDownTime() const {
    return this->_timeCountDown;
}

void MauBinhScene::resetDisplayAvatar(){
    if (!avatars.empty()){
        for (int i = 0; i < avatars.size(); i++){
            if (avatars[i]->getParent() != nullptr){
                this->removeChild(avatars[i]);
            }
        }
        avatars.clear();
    }
}

void MauBinhScene::readyToPlayResponseHandler() {
    BINReadyToPlayResponse* ready_to_play_response =
        (BINReadyToPlayResponse *)Common::getInstance()->checkEvent(NetworkManager::READY_TO_PLAY);

    if (ready_to_play_response != 0){
        CCLOG("ready to play response: %s", ready_to_play_response->DebugString().c_str());
        if (ready_to_play_response->responsecode()){
            if (Common::getInstance()->getUserId() == ready_to_play_response->readyuserid()){
                btn_san_sang->setVisible(false);
				showBtnWithWatingPlayer(true);
            }

            long long ready_player_id = ready_to_play_response->readyuserid();
            int table_index = ready_to_play_response->tableindex();
            MauBinhPlayer* player = (MauBinhPlayer*)findWaiting(ready_player_id);

            if (player != 0){
                //day vao lst playing
                MauBinhPlayer waiting_player = *player;
                waiting_player.setTableIndex(table_index);
                lst_player.push_back(waiting_player);

				showInvitePlayer(lst_player.size());  //show moi choi

                //remove avatar tren ban choi
                resetDisplayAvatar();
                //dat waiting player len ban choi
                sortListPlayer();
                displayInfoRemainCard(lst_player);

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

void MauBinhScene::startMatchResponseHandler() {
    BINStartMatchResponse *response = (BINStartMatchResponse *)
        Common::getInstance()->checkEvent(NetworkManager::START_MATCH);
    if (response != 0) {
        CCLOG("start match response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
                this->removeChildByTag(TAG_TIME_COUNTDOWN);
            }
            setStartMatch(true);
            setTurnRequestTime(0.0);
            btn_start_match->setVisible(false);
            

            if (response->has_countdowntimer() && response->countdowntimer() >= 0) {
                setMatchCountDownTime(response->countdowntimer());
            }

            countSendTurn = 0;
            countNumberOfTime = 0;

            Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->getUserId());
            if (avatar != 0) {
                avatar->updateProgressCircleBar(100, _timeCountDown);
            }

            if (response->args_size() > 0) {
                for (int i = 0; i < response->args_size(); i++) {
                    if (response->args(i).key() == "currentCards") {
                        current_card_values = Common::getInstance()->convertStringsToInt(
                            Common::getInstance()->split(response->args(0).value(), ','));
                        MauBinhCardHandler::getInstance()->sortCard(current_card_values);
                        distributeCardEffect();
                    }
                }
            }
        }
        if (response->has_message()) {
            //this->showToast(response->message().c_str(), 2);
        }
    }
}

vector<int> MauBinhScene::getCardValuesBranch(int index) {
    vector<int> card_values; 
    for (int i = 5 * index; i < 5 * index + 5 && i < current_card_values.size(); i++) {
        card_values.push_back(current_card_values[i]);
    }
    return card_values; 
}

void MauBinhScene::getCardValues() {

}

void MauBinhScene::setFinishTurn(int _finishTurn) {
    this->_finishTurn = _finishTurn; 
}
int MauBinhScene::getFinishTurn() const {
    return this->_finishTurn; 
}

void MauBinhScene::cancelFinishSortCard() {
    if (getFinishTurn() == MauBinhScene::IN_PROGRESS) {
        setFinishTurn(NOT_READY);
        vector<BINMapFieldEntry> entries;
        BINMapFieldEntry entry;
        entry.set_key("arrangeStatus");
        entry.set_value("isNotFinishArrange");
        entries.push_back(entry);
        NetworkManager::getInstance()->getTurnMessageFromServer(getRoomIndex(), entries);
    }
}

void MauBinhScene::sendSortedCard() {
    if (turnRequestTime >= countNumberOfTime + COUNT_TIME && turnRequestTime * 1000 < getMatchCountDownTime()) {
        CCLOG("turn request time: %lf", turnRequestTime);
        finishSortCard(true);
        countNumberOfTime += COUNT_TIME; 
    }
}

void MauBinhScene::finishSortCard(bool isPing) {
    CCLOG("turn request");
    for (int index : current_card_values){
        CCLOG("value : %d", index);
    }

    vector<BINMapFieldEntry> entries;
    BINMapFieldEntry entry;

    if (isPing) {
        entry.set_key("pingArrange"); 
        entry.set_value("pingArrange");
    }
    else {
        entry.set_key("arrangeStatus");
        entry.set_value("isFinishArrange");
    }
    
    entries.push_back(entry);
    //first branch
    entry.set_key(MauBinhCardHandler::FIRST_BRANCH);
    entry.set_value(Common::getInstance()->convertListCardToString(getCardValuesBranch(0)));
    entries.push_back(entry);

    //center branch
    entry.set_key(MauBinhCardHandler::CENTER_BRANCH);
    entry.set_value(Common::getInstance()->convertListCardToString(getCardValuesBranch(1)));
    entries.push_back(entry);

    //last branch
    entry.set_key(MauBinhCardHandler::LAST_BRANCH);
    entry.set_value(Common::getInstance()->convertListCardToString(getCardValuesBranch(2)));
    entries.push_back(entry);

    NetworkManager::getInstance()->getTurnMessageFromServer(getRoomIndex(), entries);
}

void MauBinhScene::sendTurnRequest(float dt) {
    //TODO: SangLX - send turn resquest
    
    finishSortCard(false);
    setFinishTurn(MauBinhScene::DONE_TURN);
    
    for(int i =0; i< 3; i ++) {
        for(int j = 0 ; j< cardSprites[i].size() ; j++) {
            cardSprites[i][j]->showHidden(true);
            cardSprites[i][j]->setPosition(cardSprites[i][j]->getCurrentPos());
            Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(cardSprites[i][j]);
        }
    }
    
    label_lung->setVisible(false);
    sprite_lung->setVisible(false);
    label_turn[0]->setVisible(false);
    label_turn[1]->setVisible(false);
    label_turn[2]->setVisible(false);
}

void MauBinhScene::roomOwnerChangedResponseHandler() {
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

void MauBinhScene::handleWinLose(BINMatchEndResponse *response) {
    //handle win
    for (int i = 0; i < response->winninguserids_size(); i++) {
        int val = (int)response->winninguserids(i);
        for (int j = 0; j < lst_player.size(); j++) {
            std::stringstream ss(lst_player[j].getID());
            int player_uid;
            ss >> player_uid;
            if (val == player_uid) {
                lst_player[j].setStatus(MauBinhPlayer::WIN_STATUS);
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
                lst_player[j].setStatus(MauBinhPlayer::LOSE_STATUS);
                break;
            }
        }
    }
    //handle draw
    for (int i = 0; i < response->drawuserids_size(); i++) {
        int val = (int) response->drawuserids(i);
        for (int j = 0; j < lst_player.size(); j++) {
            std::stringstream ss(lst_player[j].getID());
            int player_uid;
            ss >> player_uid; 
            if (val == player_uid) {
                lst_player[j].setStatus(MauBinhPlayer::DRAW_STATUS);
                break;
            }
        }
    }

    int current_user_id = Common::getInstance()->getUserId(); 

    for (MauBinhPlayer player : lst_player){
        Avatar* avatar = findAvatarOfPlayer(Common::getInstance()->convertStringToInt(player.getID()));
        if (avatar != 0) {
            switch (player.getStatus())
            {
            case MauBinhPlayer::DRAW_STATUS:
                avatar->setDraw(response->countdowntimer() / 1000.0f);
                break;
            case MauBinhPlayer::WIN_STATUS:
                avatar->setWin(response->countdowntimer() / 1000.0f);
                break;
            case MauBinhPlayer::LOSE_STATUS:
                avatar->setLose(response->countdowntimer() / 1000.0f);
                break;
            default:
                break;
            }
        }
    }
}

vector<pair<int, vector<int>>> MauBinhScene::parseCardValue(std::string
    json_value) {
    vector<pair<int, vector<int>>> result;
    try {
        Document document;
        document.Parse(json_value.c_str());
        for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
            itr != document.MemberEnd(); ++itr) {
            string val = itr->value.GetString();
            vector<int> card_values = Common::getInstance()->convertStringsToInt(Common::getInstance()
                ->split(val, ','));
            if (card_values.size() != 5 && card_values.size() != 3 && card_values.size() != 13) {
                CCLOG("convert sai");
            }
            int user_id = Common::getInstance()->convertStringToInt(itr->name.GetString());
            if (!card_values.empty())
                result.push_back(make_pair(user_id, card_values));
        }
    }
    catch (...) {
        CCLOG("exception");
        result.clear();
    }

    return result;
}

Vec2 MauBinhScene::getCardCoverPostion(Avatar* avatar) {
    return Vec2(avatar->getPosition().x + avatar->spriteCard->getPosition().x,
                avatar->getPosition().y + avatar->spriteCard->getPosition().y);
}

void MauBinhScene::addEmotion(int emotion,string message,Vec2 pos,int duration,bool maubinh) {
    string background_effect = "mau_binh/effect_doi.png" ;//: "mau_binh/effect_lung.png";
    auto effect_bkg = MSprite::create(background_effect);
    effect_bkg->setScale(cardWidth()*CARD_RATIO*2/(3*effect_bkg->getHeight()));
    effect_bkg->setContentSize(effect_bkg->getSize()*effect_bkg->getScale());
    effect_bkg->setPosition(Vec2(pos.x + cardWidth()*0.5f - effect_bkg->getWidth()*effect_bkg->getScale()*0.5f,pos.y));
    
    auto text = MLabel::create(message,effect_bkg->getHeight()*0.75f);
    if(maubinh){
        text->setColor(Color3B::YELLOW);
        text->enableOutline(Color4B::BLACK,2);
    }else{
        text->setColor(Color3B(127,206,239));
        text->enableOutline(Color4B::BLACK,2);
    }
    text->setPosition(Vec2(effect_bkg->getWidth()/2 - text->getWidth()/2,
                      effect_bkg->getHeight()/2 - text->getHeight()*0.45f));
    effect_bkg->addChild(text);
    if((emotion >=11 && emotion <=18) || emotion == 32){
        effect_Text.push_back(effect_bkg);
        this->addChild(effect_Text[effect_Text.size()-1]);
    }else{
        effect_bkg->runAction(Sequence::create(DelayTime::create(duration-0.2f),FadeOut::create(0.2f),RemoveSelf::create(),NULL));
        this->addChild(effect_bkg);
    }
}

void MauBinhScene::handleCompareTurn(int user_id, int emoticon_id,string message, vector<int> card_values, int duration) {
    //TODO: HungLe
    /*
    user_id : id của người chơi
    emoticon_id: id hiệu ứng
    card_values: giá trị quân bài của người chơi
    */
    
    auto currentAvatar = findAvatarOfPlayer(user_id);
    if (currentAvatar == 0) {
        return;
    }
    currentAvatar->hiddenNumberCardAndCover(true);
    int posIndex = currentAvatar->getPositionIndex();
    
    CCLOG("card values size: %d", (int) card_values.size());
    vector<int> valuess;
    for(int i = 0 ;i < card_values.size();i++){
        int index = card_values[i];
        index = card_values[i] - 4;
        if(index < 1) {
            index = index + 52;
        }
        valuess.push_back(index);
    }
    string text = Common::getInstance()->convertListCardToString(valuess);
    
    string s = StringUtils::format("%s : >>>  %s",findPlayer(user_id)->getName().c_str(),text.c_str());
    CCLOG("%s",s.c_str());
    
    if (card_values.size() != 0){
        
//        for (Sprite* card : card_matchends[posIndex]){
//            this->removeChild(card);
//        }
        //card_matchends[posIndex].clear();
    }
    
    Vec2 posX = currentAvatar->getPosition();
    if(posIndex == 2){
        posX = Vec2(originX + width/2 - 2.7f*cardWidth() - currentAvatar->getContentSize().width,
                    posX.y);
    }else if(posIndex == 1 ){
        posX = Vec2(originX + width - 2.7f*cardWidth() - currentAvatar->getContentSize().width/2,
                    height/2 - 2.5f*cardWidth()*CARD_RATIO);
    }else if(posIndex == 3){
        posX = Vec2(originX + 2.7f*cardWidth() - currentAvatar->getContentSize().width/2,
                    height/2 - 2.5f*cardWidth()*CARD_RATIO);
    }else{
        posX = Vec2(originX + width/2 - 2.7f*cardWidth() - currentAvatar->getContentSize().width,
                    posX.y);
    }
    
    auto pos = posX + currentAvatar->getContentSize()/2;
    if(posIndex == 0) {
        if(card_values.size() == 13) {
            pos = Vec2(width/2,pos.y - 1.5f*cardWidth()*CARD_RATIO);
        }else{
            pos = Vec2(width/2,pos.y - 0.5f*cardWidth()*CARD_RATIO);
        }
    }else if(posIndex == 3){
        pos = Vec2(originX+2.2f*cardWidth(),pos.y+currentAvatar->getContentSize().height);
    }else if(posIndex == 1){
        pos = Vec2(originX+width - 3.2f*cardWidth(),pos.y+currentAvatar->getContentSize().height);
    }else{
        if(card_values.size() == 13){
            pos = Vec2(width/2,originY + height - cardWidth()*CARD_RATIO*3.2f);
        }else{
            pos = Vec2(width/2,pos.y - 0.5f*cardWidth()*CARD_RATIO);
        }
    }
    
    for(int i = 0; i < card_values.size(); i++) {
        auto card = OtherCardSprite::createSelf(card_values[i],cardWidth());
        card->setPosition(pos);
        Vec2 posCard;
        if(card_values.size() != 13) {
            posCard = pos + Vec2((i- (card_values.size()-1)*0.5f)*cardWidth(),0.0f);
        }else{
            int x = i/5 < 2 ? 5 : 3;
            posCard = pos + Vec2((i%5 - (x - 1)*0.5f)*cardWidth(),(i/5)*cardWidth()*CARD_RATIO);
        }
        CCLOG("POS : >>>>> %f-%f",posCard.x,posCard.y);
        if((emoticon_id >=11 && emoticon_id <=18) || emoticon_id == 32){
            card->runAction(Sequence::create(DelayTime::create(0.02f*i),MoveTo::create(0.2f,posCard), NULL));
        }else{
            card->runAction(Sequence::create(DelayTime::create(0.02f*i),MoveTo::create(0.2f,posCard),
                                             DelayTime::create(duration - 0.2f - 0.02f*i),
                                             FadeOut::create(0.25f),RemoveSelf::create(), NULL));
        }
        //card_matchends[posIndex].push_back(card);
        this->addChild(card);
    }
    
    currentAvatar->runAction(MoveTo::create(0.15f,posX));
    
    if (card_values.size() != 0){
        if (!message.empty()){
            if(emoticon_id == 32 || emoticon_id == 31){
                addEmotion(emoticon_id, message, pos, duration,false);
            }else{
                addEmotion(emoticon_id, message, pos, duration,true);
            }
        }
    }
}

Sprite* MauBinhScene::createMauBinhSprite(int value){
    int cardValue = value;
    cardValue = value - 4;
    if(cardValue < 1){
        cardValue = cardValue + 52;
    }
    Sprite* cardSprite = Sprite::createWithSpriteFrameName(StringUtils::format("%02dx.png", cardValue));
    cardSprite->setAnchorPoint(Vec2(0,0));
    cardSprite->setScale(cardWidth()/cardSprite->getContentSize().width);
    cardSprite->setContentSize(Size(cardWidth(),cardWidth()*CARD_RATIO));
    return cardSprite;
}

void MauBinhScene::addDisplayTurnName(string branch,int duration) {
    //TODO: HungLe
    if (branch == "firstBranch") {
        CCLOG("firstBranch");
        //Chi dau: Xử lý avatar và hiển thị turn chi
        for(Avatar* avatar : avatars){
            avatar->showXong(false);
        }
        
        Vector<Node*> children = this->getChildren();
        for(int i = 0; i < children.size(); i ++) {
            MauBinhCardSprite* card = dynamic_cast<MauBinhCardSprite*>(children.at(i));
            if (card != nullptr) {
                card->removeFromParentAndCleanup(true);
            }
        }
        
        label_lung->setVisible(false);
        sprite_lung->setVisible(false);
        label_turn[0]->setVisible(false);
        label_turn[1]->setVisible(false);
        label_turn[2]->setVisible(false);
        
        CCLOG("DURATION1 : %d",duration);
        
        auto sprite_chi = MSprite::create("mau_binh/chi_1.png");
        sprite_chi->setScale(cardWidth()*CARD_RATIO/(sprite_chi->getHeight()));
        sprite_chi->setContentSize(sprite_chi->getSize()*sprite_chi->getScale());
        sprite_chi->setPosition(MVec2(width/2-sprite_chi->getWidth()*sprite_chi->getScale()/2,
                                      height/2-sprite_chi->getHeight()*sprite_chi->getScale()/2));
        sprite_chi->runAction(Sequence::create(DelayTime::create(duration),
                                               RemoveSelf::create(), NULL));
        this->addChild(sprite_chi);
        
    } else if (branch == "centerBranch") {
        CCLOG("centerBranch");
        CCLOG("DURATION2 : %d",duration);
        //chi giua: Chỉ hiển thị tên chi
        auto sprite_chi = MSprite::create("mau_binh/chi_2.png");
        sprite_chi->setScale(cardWidth()*CARD_RATIO/(sprite_chi->getHeight()));
        sprite_chi->setContentSize(sprite_chi->getSize()*sprite_chi->getScale());
        sprite_chi->setPosition(MVec2(width/2-sprite_chi->getWidth()*sprite_chi->getScale()/2,
                                      height/2-sprite_chi->getHeight()*sprite_chi->getScale()/2));
        sprite_chi->runAction(Sequence::create(DelayTime::create(duration),
                                               RemoveSelf::create(), NULL));
        this->addChild(sprite_chi);
        
    } else if (branch == "lastBranch") {
        CCLOG("lastBranch");
        CCLOG("DURATION3 : %d",duration);
        //Chi cuoi: Hiển thị tên chi
        auto sprite_chi = MSprite::create("mau_binh/chi_3.png");
        sprite_chi->setScale(cardWidth()*CARD_RATIO/(sprite_chi->getHeight()));
        sprite_chi->setContentSize(sprite_chi->getSize()*sprite_chi->getScale());
        sprite_chi->setPosition(MVec2(width/2-sprite_chi->getWidth()*sprite_chi->getScale()/2,
                                      height/2-sprite_chi->getHeight()*sprite_chi->getScale()/2));
        sprite_chi->runAction(Sequence::create(DelayTime::create(duration),
                                               RemoveSelf::create(), NULL));
        this->addChild(sprite_chi);
        
    } else {
        //3 chi
        CCLOG("DURATION4 : %d",duration);
        Vector<Node*> children = this->getChildren();
        for(int i = 0; i < children.size(); i ++) {
            MauBinhCardSprite* card = dynamic_cast<MauBinhCardSprite*>(children.at(i));
            if (card != nullptr) {
                card->removeFromParentAndCleanup(true);
            }
        }
    }
}


void MauBinhScene::matchEndResponseHandler() {
    BINMatchEndResponse *response = (BINMatchEndResponse *)
        Common::getInstance()->checkEvent(NetworkManager::MATCH_END);
    if (response != 0) {
        CCLOG("match end response: %s", response->DebugString().c_str());
        btn_finish->setVisible(false);
        vector<pair<int, vector<int>>> all_card_values;
        
        string levelBranch = ""; 
        if (response->responsecode()) {
            int duration = 2000;
            if (response->has_countdowntimer()) {
                duration = response->countdowntimer();
            };
            //handle current cards player
            if (response->args_size() > 0) {
                for (int i = 0; i < response->args_size(); i++) {
                    BINMapFieldEntry entry = response->args(i);
                    if (entry.key() == "currentCards") {
                        string json_value = entry.value();
                        all_card_values = parseCardValue(json_value);
                    } else if(entry.key() == "levelBranch") {
                        levelBranch = entry.value();
                    }
                }
            }

            //handle branch
            addDisplayTurnName(levelBranch,duration/1000.0f);
            CCLOG("XXX : %s",levelBranch.c_str());
            //handle find text emoticon
            if (response->textemoticons_size() > 0) {
                
                for (int i = 0; i < response->textemoticons_size(); i++) {
                    int user_id = (int)response->textemoticons(i).userid();
                    int emoticon_id = response->textemoticons(i).emoticonid();
                    //find current cards of user
                    pair<int, vector<int>> current_info_cards; 
                    for (pair<int, vector<int>> info_card : all_card_values) {
                        if (info_card.first == user_id) {
                            current_info_cards = info_card;
                            break; 
                        }
                    }
                    if (current_info_cards.second.size() != 0)
                        handleCompareTurn(user_id, emoticon_id,response->textemoticons(i).message(), current_info_cards.second, duration/1000);
                }
            }
            //handle win, lose, draw
            handleWinLose(response);
        }
       
        if (response->has_message()) {
            this->showToast(response->message().c_str(), 2);
        }
    }
}

void MauBinhScene::update(float dt) {
    PlayScene::update(dt);

    if (isStartMatch()) {
        turnRequestTime += dt;

        if ((countSendTurn < 1) && (1000 * turnRequestTime + 10000 >= getMatchCountDownTime())) {
            finishSortCard(true);
            CCLOG("turn request time: %lf", turnRequestTime);
            countSendTurn++;
        }

        if ((countSendTurn < 2) && (1000 * turnRequestTime + 5000 >= getMatchCountDownTime())) {
            finishSortCard(true);
            CCLOG("turn request time: %lf", turnRequestTime);
            countSendTurn++;
        }

        if (1000 * turnRequestTime >= getMatchCountDownTime()) {
            //====            
            sendTurnRequest(dt);
            turnRequestTime = 0;
            countSendTurn = 0;
            countNumberOfTime = 0;
            setStartMatch(false);
        }
    }

    readyToPlayResponseHandler();
    playerExitRoomResponseHandler();
    playerExitAfterMatchEndResponseHandler();
	cancelExitAfterMatchEndResponseHandler();
    roomOwnerChangedResponseHandler();
    playerEnterRoomResponseHandler();
    prepareNewMatchResponseHandler();
    startMatchResponseHandler();
    turnResponsehandler();
    matchEndResponseHandler();
    updateMoneyResponseHandler();
}

bool MauBinhScene::isUserPlaying() {
    int user_id = Common::getInstance()->getUserId();
    Player* player = findPlayer(user_id);
    if (player != 0){
        return true;
    }
    return false;
}

void MauBinhScene::setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list){
    if (lst_player.size() > 0) lst_player.clear();
    for (int i = 0; i < player_list.size(); i++) {
        MauBinhPlayer player = convertFromBINPlayer(player_list[i]);
        lst_player.push_back(player);
    }
    
    for (int i = 0; i < waiting_player_list.size(); i++) {
        MauBinhPlayer player = convertFromBINPlayer(waiting_player_list[i]);
        lst_waiting.push_back(player);
    }

    if (is_create_room){
        btn_san_sang->setVisible(false);
    }
    else {
        if (isUserPlaying()){
			showInvitePlayer(player_list.size());
			btn_san_sang->setVisible(false);
		} 
		else {
			showBtnWithWatingPlayer(false);
		}
    }
    
    showWaitingPlayerOnScene(lst_waiting);
    
    //sap xep lai lst_player theo table_index
    sortListPlayer();
    
    //hien thi avatar cua nhung nguoi join vao phong
    displayInfoRemainCard(lst_player);
}


void MauBinhScene::displayInfoRemainCard(std::vector<MauBinhPlayer>& remain_card_infos){
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

void MauBinhScene::sortListPlayer() {
    sort(lst_player.begin(), lst_player.end());
}

MauBinhPlayer MauBinhScene::convertFromBINPlayer(BINPlayer binplayer) {
    char buffer[20];
    sprintf(buffer, "%lld", binplayer.userid());
    std::string uid = std::string(buffer);
    
    int numberCard = 0;
    
    MauBinhPlayer player = MauBinhPlayer(binplayer.username(), uid, numberCard, binplayer.cash(),
                                   binplayer.gold(), 0, binplayer.tableindex(), binplayer.avatarid());
    return player;
}

int MauBinhScene::findIndexPlayer(vector<MauBinhPlayer> lstPlayer, Player& player){
    
    for (int i = 0; i < lstPlayer.size();i++){
        if (lstPlayer[i].getID() == player.getID()){
            return i;
        }
    }
    return -1;
}

//show danh sach nguoi cho
void MauBinhScene::showWaitingPlayerOnScene(vector<MauBinhPlayer> lstWaiting){
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

void MauBinhScene::playerEnterRoomResponseHandler() {
    BINPlayerEnterRoomResponse *newplayerresponse = (BINPlayerEnterRoomResponse*)
    Common::getInstance()->checkEvent(NetworkManager::PLAYER_ENTER_ROOM);
    if (newplayerresponse != 0) {
        CCLOG("player enter room response: %s", newplayerresponse->DebugString().c_str());
        if (newplayerresponse->responsecode()) {
            MauBinhPlayer player = convertFromBINPlayer(newplayerresponse->player());
            
            //neu la nguoi choi
            if (newplayerresponse->enterroomstatus() == PlayerState::PLAYING){
                MauBinhScene::player_list.push_back(newplayerresponse->player());
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

                    if (newplayerresponse->has_changeownerroomcd() > 0) {
                        CCLOG("time start match countdown %d", newplayerresponse->changeownerroomcd());
                        Avatar* avatar = findAvatarOfPlayer(getOwnerUserId());
                        if (avatar != 0){
                            avatar->updateProgressCircleBar(100, newplayerresponse->changeownerroomcd());
                        }
                    }
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

//set vi tri nguoi choi: indexPos -> vi tri cua nguoi choi trong lst_player
//capacity_size -> so nguoi choi toi da trong room
void MauBinhScene::setPositionPlayer(MauBinhPlayer& player, int indexPos){
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
    if(position_index == 0) {
        pos = MVec2(width/2 - avatar->getContentSize().width/2,pos.y);
    }
    avatar->setPosition(pos);
    
    double cardCoverWidth = cardWidth();
    
    avatar->loadCardCover(cardCoverWidth, position_index, _numberCard);
    if (position_index == 0) {
        avatar->hideCardCover();
    }else{
        avatar->hideNumberCard(true);
    }
    
    avatars.push_back(avatar);
    
    if (avatar->getParent() == nullptr)
        this->addChild(avatar,2);
}

void MauBinhScene::menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType){
}

float MauBinhScene::cardWidth() {
    return width*0.9f/18;
}

void MauBinhScene::onExit() {
    PlayScene::onExit();
}

void MauBinhScene::cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType) {
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*)pSender)->getTag();
        switch (tag)
        {
        case TAG_MAUBINH_BTN_SANSANG: 
            CCLOG("san sang");
            NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, -1);
            break;
        case TAG_MAUBINH_BTN_XONG:
            CCLOG("sap xep bai");
            finishSortCard(false);
            break;
        case TAG_MAUBINH_BTN_START_MATCH:
        {
            CCLOG("start match");
            if (lst_player.size() > 1) {
                NetworkManager::getInstance()->getStartMatchMessageFromServer(this->getRoomIndex());
            }
            else this->showToast(TXT_ENOUGH_PLAYER, 2);
        }
            break;
        default:
            break;
        }
    }
}

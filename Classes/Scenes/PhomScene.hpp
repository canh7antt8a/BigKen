//
//  PhomScene.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/17/16.
//
//

#ifndef PhomScene_hpp
#define PhomScene_hpp

#include <stdio.h>
#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Objects/CardSprite.hpp"
#include "Objects/Player.hpp"
#include "Objects/Avatar.hpp"
#include "Objects/OtherCardSprite.hpp"
#include "Objects/PhomPlayer.hpp"
#include "Objects/CardSpriteEventDelegate.hpp"
#include "Objects/JSONObject.hpp"

#include "protobufObject/player.pb.h"
#include "protobufObject/match_end.pb.h"
#include "protobufObject/enter_room.pb.h"

#include "PlayScene.h"

#include "Popups/PopupTLMN.hpp"

#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"

enum PhomTurnType {
    DANHBAI = 1,
    BOCBAI = 2,
    ANBAI = 3,
    GUIBAI = 4,
    HABAI = 5,
    TUDONGHA = 6,
    U = 7,
    OTHER_CARD = 8
};

struct OrderEnding {
    int id;
    int rank;
};

class SettingDialog;

using namespace cocos2d;
using namespace std;

class PhomScene : public PlayScene, public CardSpriteEventDelegate {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int roomIndex, std::vector<BINPlayer> playerList,
                                       vector<BINPlayer> _waitingPlayerList, bool createRoom,
                                       int gameTag, bool isDisplayRoomList, bool passwordRequired,
									   bool isVipRoom, int minBet, BINEnterRoomResponse* reEnterRoomResponse);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    
    virtual void onEvent(int value) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(PhomScene);
    
    void update(float) override;
    
    /*
     Response Handler
     */
    void matchEndResponseHandler();
    void playerExitAfterMatchEndResponse();
    void playerExitRoomResponse();
    void turnResponse();
    void roomOwnerChangedResponseHandler();
    void updateMoneyResponseHandler();
    void startMatchResponseHandler();
    void playerEnterRoomResponseHandler();
    void matchBeginResponseHandler();
    void prepareNewMatchResponseHandler();
    void cancelExitAfterMatchEndResponseHandler();
    void kickUserResponseHandler();
    void readyToPlayResponseHandler();
    void changeRuleResponseHandler();

    void enterRoomResponseHandler(BINEnterRoomResponse* response);
    
    //
    PhomPlayer convertFromBINPlayer(BINPlayer binplayer);
    
    void setMatchCountDownTime(int _countDownTime);
    int getMatchCountDownTime() const;
    
    int getFirstTurnUserId() const;
    void setFirstTurnUserId(int firstTurnUserId);
    void changeFirstTurnUserIdAfterEatCard();
    
    int getNextTurnUserId() const;
    void setNextTurnUserId(int id);
    
    int getCurrentTurnUserId() const;
    void setCurrentTurnUserId(int id);
    
    int getOwnerUserId() const;
    void setOwnerUserId(int id);
    
    int getFirstReleaseUserId() const;
    void setFirstReleaseUserId(int id);  
    // số quân bài ở giữa bàn
    int getMainCardCount() const;
    void setMainCardCount(int count);
    
    void sortCard(vector<int> cardValue);
    void sortCard();
    void layoutInit();
    void initGame();
    void refreshCard();
    
    static bool sortByValue(const Card &a, const Card &b);
    
    //turn card
    void u();
    void throwCard();
    void pickCard();
    void eatCard(std::string cardValue);
    void releaseCard(std::string cardsValue);
    void autoReleaseCard();
    void consignedCards();
    void turnRequest(PhomTurnType type);
    void turnRequest(PhomTurnType type, string data);
    
    //turn response
    void turnTypeResponse(float duration,string data,bool canEat);

    void sortListPlayer();
    //tim index cua nguoi choi so voi currentIndex
    int findIndexPlayer(vector<PhomPlayer> lstPlayer, Player& player);
    
    int getTableIndexByUserId(int userId);

	bool isUserPlaying();

    void setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list);
    void displayInfoPlayer(vector<PhomPlayer>& lst_info_players);
    Player* findPlayer(long long player_id);
    Player* findWaiting(long long player_id);
    void deleteWaitingPlayer(string player_id);

    //show list nguoi cho len game
    void showWaitingPlayerOnScene(vector<PhomPlayer> lstWaiting);

    void disableAllCardButton();
    
    void initListThrowAndEatenCard();
    void removeCardAfterThrow(int cardValue);
    void swapCard();
    void initCardFromInts(vector<int> values);
    tuple<vector<vector<int>>, vector<int>> timPhomNgang(vector<int> cards);
    tuple<vector<vector<int>>, vector<int>> timPhomDoc(vector<int> cards);
    vector<vector<int>> parseJSONToPair(string data);
    int checkContainsCard(int value);
    bool checkContainsCardTag(int value);
    int getPreviousTurnUserId() const;
    void setPreviousTurnUserId(int _previousTurnUserId);
    vector<JSONObject> parseJSONString(string json);
    void resetDisplayAvatar();
    void displayInfoRemainCard(vector<PhomPlayer>& remain_card_infos);
    void setPositionPlayer(PhomPlayer& player);
    
protected:

    void menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void playCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void cardCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    
    void sortCardAfterMoveCardToCenter();
    Vec2 getCardCoverPostion(Avatar* avatar);
    void createCard(PositionIndex positionIndex, int tag);
    void showInitCard();
    void addNewCardIntoCardTag(Vec2 postion,int value);
    Sprite* getSpriteEatAnimation();
    void checkContaintCardInPair(vector<vector<int>> &pair, int cardvalue);
    
private:
    MButton* btnStartMatch;
    MButton* btnDanhBai;
    MButton* btnBocBai;
    MButton* btnAnBai;
    MButton* btnHaPhom;
    MButton* btnGuiBai;
    MButton* btnU;
    MButton* btnXepBai;
	MButton* btn_san_sang;
    
    PopupTLMN *m_popupTLMN;
    
    MLabel *remainCard;
    MSprite *centerCard;
    MSprite *spriteFirstTurn;
    
    std::vector<PhomPlayer> _lstPlayer;  //danh sach nguoi choi
    std::vector<PhomPlayer> _lstWaiting; //danh sach nguoi cho
    std::vector<Card> _cards;
    
    vector<vector<int>> _pairs;
    vector<vector<int>> _phoms;
    vector<vector<int>> _phomsU;
    vector<vector<int>> _kitSameKind;
    vector<vector<int>> _kitStraight;
    vector<int> _singleCards;
    vector<int> _eatCard;

    std::vector<int> lastCards;
    std::vector<CardSprite*> card_tag;
    std::vector<OtherCardSprite*> groupThrowCards[4];
    std::vector<OtherCardSprite*> groupEatCards[4];
    std::vector<vector<OtherCardSprite*>> groupHaBaiCards[4];
    
    PhomTurnType _turnType;
    
    int _matchCountDownTime;
    int _firstTurnUserId;
    int _mainCardCount; //so quan bai o mo giua
    int _currentTurnUserId;
    int _previousTurnUserId;
    int _ownerUserId;
    int _nextTurnUserId;
    int _lastThrowCard;
    int _firstReleaseUserId;
    bool _isDisplayRoomList;
    
};

#endif /* PhomScene_hpp */

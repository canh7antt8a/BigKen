#ifndef __TLMIENNAM_SCENE_H__
#define __TLMIENNAM_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Objects/CardSprite.hpp"
#include "BaseScene.hpp"
#include "Objects/Player.hpp"
#include "protobufObject/player.pb.h"
#include "protobufObject/match_end.pb.h"
#include "Objects/Avatar.hpp"
#include "Objects/OtherCardSprite.hpp"
#include "Objects/TLMNPlayer.hpp"
#include "protobufObject/enter_room.pb.h"
#include <iostream>
#include "external/json/document.h"

#include "Scenes/PlayScene.h"
#include "Objects/CardSpriteEventDelegate.hpp"

class SettingDialog;

using namespace cocos2d;
using namespace std;

class TLMienNam : public PlayScene,public CardSpriteEventDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int roomIndex, std::vector<BINPlayer> playerList,
                                       vector<BINPlayer> _waitingPlayerList, bool createRoom,
                                       int gameTag, bool isDisplayRoomList, bool passwordRequired,
									   bool isVipRoom, int minBet, std::string cardRemainingCount,
									   BINEnterRoomResponse* reEnterRoomResponse);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    virtual void onEvent(int value) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TLMienNam);

    std::vector<std::pair<int, std::vector<int>>> parseCardValue(
        std::string json_value);
    void handleCardValue(std::vector<std::pair<int, std::vector<int>>>);
    bool isMatchEnd() const;

    void setMatchEnd(bool _matchEnd);

    void setTurnCountDownTime(int _countDownTime);
    
    int getTurnCountDownTime() const; 

    void setMatchCountDownTime(int _countDownTime);

    int getMatchCountDownTime() const;

    void setCurrentTurnUserId(int _currentTurnUserId);

    int getCurrentTurnUserId() const;

    void setNextTurnUserId(int _nextTurnUserId);

    int getNextTurnUserId() const;

    int getFirstTurnUserId() const; 

    void setFirstTurnUserId(int _firstTurnUserId); 
 
    void update(float) override;

    void handleEmotion(long long user_id, int emotion_id, string message);

    void sortListPlayer();

    int getPositionOfUserId(string uid);
    
    bool isPassUp() const {return _passUp; }
    
    void setPassUp(bool _pass_up) {_passUp = _pass_up; }

	void setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list, string cardRemainingCount);

    TLMNPlayer convertFromBINPlayer(BINPlayer binplayer);

    void handleReEnterRoom(BINEnterRoomResponse*);

    void handleWinLose(BINMatchEndResponse *response);

    int getChangeOwnerRoomCd() const; 

    void setChangeOwnerRoomCd(int _change_owner_room_cd);

    void resetMatch();

    //show list nguoi cho len game
    void showWaitingPlayerOnScene(vector<TLMNPlayer> lstWaiting);

    //static int enter_room_status;
protected:
    std::vector<Card> cards;
    std::vector<int> lastCards;
    std::vector<CardSprite*> card_tag;
    //std::vector<Player> AllPlayers;
    
    void initMenu();
    void initCards();
    void createCards(PositionIndex index,int tag);
    void showInitCard();
	void initGame(string cardRemainingCount);
    void sortCard(vector<int> card_values);
    void displayInfoRemainCard(vector<TLMNPlayer>& remain_card_infos);
    vector<pair<string, vector<int>>> parseTurnResponse(BINMapFieldEntry entries);

    void parseRemainCards(string json);
    void handleTurnResponseValues(vector<pair<string, vector<int>>> turn_response_val);
    
    vector<int> cardTagToInts(vector<CardSprite*> cards);
    
    Vec2 getCardCoverPostion(Avatar* avatar);
    
    void menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void playCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void cardCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);

    //lay ra avatar cua nguoi choi
    //input: id nguoi choi
    //return avatar
    //Avatar* findAvatarOfPlayer(long long player_id);

    TLMNPlayer* currentUser();
    //tim nguoi choi
    Player* findPlayer(long long player_id);
    //tim nguoi cho
    Player* findWaiting(long long player_id);
    //xem nguoi hien tai la nguoi choi hay nguoi cho
    bool isUserPlaying();

    //reset countdown cua tat ca nguoi choi
    void resetCountDownAll();

    //set vi tri nguoi choi: indexPos -> vi tri cua nguoi choi trong lst_player 
    //capacity_size -> so nguoi choi toi da trong room
    void setPositionPlayer(TLMNPlayer& player, int indexPos);
    
    /*
        Response Handler
     */
    void exitRoomResponseHandler();
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
    
    //move card to center
    void moveCardToCenter(std::vector<int> values,bool self,Avatar* avatar);
    void sortCardAfterMoveCardToCenter(int numberCard);

    //tim index cua nguoi choi so voi currentIndex
    int findIndexPlayer(vector<TLMNPlayer> lstPlayer, Player& player);
    //xoa nguoi cho
    void deleteWaitingPlayer(string player_id);
    //reset avatar
    void resetDisplayAvatar();
private:
    bool check_exit_room;
    int cardTag;
    std::vector<Sprite*> playerSprite;
    std::vector<std::vector<OtherCardSprite*>> groupOtherCards;
    std::vector<Sprite*> othercardss;

    MButton *btn_start_match;
    MButton *btn_danh_bai;
    MButton *btn_bo_luot;
    MButton *btn_san_sang;
    
    bool menu_click;
    bool _matchEnd;
    int _currentTurnUserId; 
    int _nextTurnUserId; 
    int _firstTurnUserId;
    bool _passUp;
    //turn count down
    int _turnCountDownTime;
    //match count down
    int _matchCountDownTime;
    
    std::vector<TLMNPlayer> lst_player;  //danh sach nguoi choi
    std::vector<TLMNPlayer> lst_waiting; //danh sach nguoi cho
    int changeOwnerRoomCd;
    int test_countdown_time = 15 * 1000;
    bool willExitRoomAfterMatchEnd = false;
    bool matchRunning = false;
    bool hiddenCardRemaingCount = false;
};


#endif // __TLMIENNAM_SCENE_H__

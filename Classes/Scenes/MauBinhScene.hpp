//
//  MauBinhScene.hpp
//  MyCards
//
//  Created by hungle on 8/1/16.
//
//

#ifndef MauBinhScene_hpp
#define MauBinhScene_hpp

#include "Objects/CardSpriteMoveDelegate.h"
#include "PlayScene.h"
#include "Objects/ThreeCardAvatar.hpp"
#include "Objects/MauBinhCardSprite.hpp"
#include "Objects/Player.hpp"
#include "Objects/MauBinhPlayer.hpp"
#include "Objects/Avatar.hpp"
#include "Objects/OtherCardSprite.hpp"
#include <vector>
#include <algorithm>

using namespace cocos2d;
using namespace std;

class MauBinhScene : public PlayScene,CardSpriteMoveDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int roomIndex, std::vector<BINPlayer> playerList,
                                       vector<BINPlayer> _waitingPlayerList, bool createRoom,
                                       int gameTag, bool isDisplayRoomList, bool passwordRequired,
                                       bool isVipRoom, int minBet, BINEnterRoomResponse* reEnterRoomResponse);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onExit();
    virtual void onEventCardSpriteMove(int value,float x,float y);
    void update(float);
    
    void setPositionPlayer(Player& player);
    Vec2 getCardCoverPostion(Avatar* avatar);
    Vec2 getCardPostion(int x,int y);
    void initGame();
    void menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void setMatchCountDownTime(int _timeCountDown);
    int getMatchCountDownTime() const;
    void getCardValues();
    void sendTurnRequest(float dt);
    void addDisplayTurnName(string branch,int duration);
    
    CREATE_FUNC(MauBinhScene);
    
    void addSpriteCards(float dt);
    void distributeCardEffect();
    void addEmotion(int emotion,string message,Vec2 pos,int duration,bool maubinh);
    void sendSortedCard();

    Point touchToPoint(Touch* touch);
    void playerEnterRoomResponseHandler();
    void prepareNewMatchResponseHandler();
    void playerExitRoomResponseHandler();
    void turnResponsehandler();
    void updateMoneyResponseHandler();
    void startMatchResponseHandler();
    void matchEndResponseHandler();
    void playerExitAfterMatchEndResponseHandler();
    void roomOwnerChangedResponseHandler();
    void readyToPlayResponseHandler();
    void resetDisplayAvatar();
	void cancelExitAfterMatchEndResponseHandler();
    void setPositionPlayer(MauBinhPlayer& player, int indexPos);
    MauBinhPlayer convertFromBINPlayer(BINPlayer binplayer);
    void handleWinLose(BINMatchEndResponse *response);
    void handleCompareTurn(int user_id, int emoticon_id,string mesage, vector<int> card_values, int duration);
    vector<pair<int, vector<int>>> parseCardValue(std::string
        json_value);
    void sortListPlayer();
    int findIndexPlayer(vector<MauBinhPlayer> lstPlayer, Player& player);
    void showWaitingPlayerOnScene(vector<MauBinhPlayer> lstWaiting);
    void setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list);
    void displayInfoRemainCard(std::vector<MauBinhPlayer>& remain_card_infos);
    void initMenu();
    void cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    std::vector<int> getCardValuesBranch(int index);
    void swapCardSprite(MauBinhCardSprite* &currentCard,MauBinhCardSprite* &nextCard);
    Player* findPlayer(long long player_id); 
    float getTurnRequestTime() const; 
    bool isStartMatch() const; 
    void setTurnRequestTime(float _turnRequestTime);
    void setStartMatch(bool _startMatch);
    void getAllRankCardValue();
    void addTurnCardSuggest(int i);
    float cardWidth();
    void setFinishTurn(int _finishTurn);
    int getFinishTurn() const;
    void cancelFinishSortCard();
    void finishSortCard(bool isPing);
    void handleFinishSortCard(int user_id, bool isFinish);
    Player* findWaiting(long long player_id);
    void deleteWaitingPlayer(string player_id);
    void handleReEnterRoom(BINEnterRoomResponse *response);
    bool isUserPlaying();
    
    const static int DONE_TURN = 2;
    const static int IN_PROGRESS = 1;
    const static int NOT_READY = 0;
    const static int DELAY_TIME = 2;
    const static int COUNT_TIME = 3; //3s

private:
    Sprite* createMauBinhSprite(int value);
    vector<int> emotion_id;
    vector<const char*> emotion_text;
    vector<const char*> emotion_bkg;
    vector<MauBinhCardSprite*> cardSprites[3];
    vector<Sprite*> card_matchends[4];
    vector<MLabel*> lbl_ends[4];
    pair<int, vector<vector<int>>> turn_cards_values[3];
    vector<Card> cards;
    vector<int> cardsx[3];
    MButton *btn_start_match;
    MButton *btn_san_sang;
    int countSendTurn; 
    
    MLabel* label_turn[3];
    MLabel *label_lung;
    vector<MSprite*> effect_Text;
    MSprite * sprite_lung;
    int rank[3];
    int countNumberOfTime; 
    MSprite *spr_compare_turn;
    MButton *btn_finish; 
    int _timeCountDown;
    float turnRequestTime; 
    bool start_match; 
    int _finishTurn; 
    vector<int> current_card_values;
    
    vector<vector<OtherCardSprite*>> cardViews[4];
    vector<pair<int, vector<int>>> all_card_values;
    
    std::vector<MauBinhPlayer> lst_player;  //danh sach nguoi choi
    std::vector<MauBinhPlayer> lst_waiting; //danh sach nguoi cho
};

#endif /* MauBinhScene_hpp */

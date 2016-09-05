//
//  ThreeCardsScene.hpp
//  MyCards
//
//  Created by hungle on 7/7/16.
//
//

#ifndef ThreeCardsScene_hpp
#define ThreeCardsScene_hpp

#include "Objects/CardSpriteMoveDelegate.h"
#include "Objects/Card.hpp"
#include "Objects/BaCayCardSprite.hpp"
#include "PlayScene.h"
#include "Objects/ThreeCardAvatar.hpp"
#include "protobufObject/enter_room.pb.h"
#include "Objects/ThreeCardPlayer.hpp"
#include "UI/MButton.hpp"
#include "UI/MLabel.hpp"
#include <vector>

#include "Popups/NodeConfirm.hpp"
#include "Objects/OnEvenListener.hpp"

using namespace cocos2d;
using namespace std;

class ThreeCardsScene : public PlayScene, OnEvenListener<BINBetResponse*>
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    /*static cocos2d::Scene* createScene(int roomIndex, std::vector<BINPlayer> playerList,
                                       vector<BINPlayer> _waitingPlayerList, bool createRoom,
                                       int gameTag, bool isDisplayRoomList, bool passwordRequired,
                                       bool isVipRoom, int minBet, BINEnterRoomResponse* reEnterRoomResponse);*/

	static cocos2d::Scene* createScene(BINRoomPlay roomPlay, std::vector<BINPlayer> playerList,
		vector<BINPlayer> waitingPlayerList, bool createRoom, bool isDisplayRoomList, BINEnterRoomResponse* reEnterRoomResponse);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    void update(float) override;
	void onEvent(int enventType, BINBetResponse* sender) override;

    void setPositionPlayer(ThreeCardPlayer& player, int position);
    void initMenu();
    void initGame();
    void setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list);
    void handleReEnterRoom(BINEnterRoomResponse* enter_room_response);
    ThreeCardPlayer convertFromBINPlayer(BINPlayer player);
    bool isUserPlaying();
    void displayInfoRemainCard(vector<ThreeCardPlayer>& remain_card_infos);
    Player* findPlayer(long long player_id);
	//tim nguoi cho
	Player* findWaiting(long long player_id);
    void showWaitingPlayerOnScene(vector<ThreeCardPlayer> lstWaiting);
    void menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    void cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
	void sliderEvent(Ref *pSender, Slider::EventType eventType);
    void handleBetMoneyType(int sourceuserid, vector<pair<int, int>> bet_money_response);
    void addCoin(int numberCard, int cardType, Vec2 point1, Vec2 point2);
    void sortListPlayer();
    void receiveMoneyFromBetChicken(int user_id);
	//reset avatar
	void resetDisplayAvatar();
	//xoa nguoi cho
	void deleteWaitingPlayer(string player_id);

	//an popup xac nhan
	void dissmissPopupConfirm();

	//show cuoc ban
	void showBetTable();

	//an cuoc ban
	void hiddenBetTable();

	void setTextBetTable(int moneyBetTable);

	//show cuoc bien
	void showBetBarier();
	//hidden cuoc bien
	void hiddenBetBarier();
	//hidden ga
	void hiddenBetUnion();

	//lat bat
	void latBai();

	Avatar* findAvatarOfPlayer(long long player_id) override;
	void handleWinLose(BINMatchEndResponse *response);

    CREATE_FUNC(ThreeCardsScene);
    
	//response message
	void startMatchHandler();
	void updateMoneyHandler();
	void betHandler();
	void preparenewMatchHandler();
	void turnHandler();
    void sortCard(vector<int> current_card_values);
    void showInitCard();

	void playerExitRoomResponse();
	void playerExitAfterMatchEndResponse();
	void playerEnterRoomResponseHandler();
	void readyToPlayResponseHandler();
    void matchEndResponseHandler(); 
	void roomOwnerChangedResponseHandler();
	void cancelExitAfterMatchEndResponseHandler();

	void showChuong(int userId);

    vector<pair<int, vector<int>>> parseCardValue(std::string
        json_value);

	vector<pair<int, bool>> parseKeyBoolValue(std::string json_value);
	vector<pair<int, int>> parseKeyIntValue(std::string json_value);

    static const int AVATARPOS[];
	//end

private:
    void setMatchCountDownTime(int _countDownTime);
    int getMatchCountDownTime();
    void createCards(int index);
    vector<pair<int, vector<int>>> card_values;
	//end
    std::vector<Card> cards;
    std::vector<BaCayCardSprite*> card_tag;
    vector<ThreeCardPlayer> lst_player; 
    vector<ThreeCardPlayer> lst_waiting; 
    MButton *btn_san_sang;
    MButton *btn_lat_bai; 
    MButton* btn_so_bai;
	MSprite *sprite_muccuoc;
	int betMoneyTable; //muc tien cuoc ban
	float posXcuoc; //vi tri toa do x hien thi so muc cuoc
    int _matchCountDownTime;
	vector<ThreeCardAvatar*> avatars;
    int totalUnionMoney; //tong so tien gop ga
	MButton* btn_gopga;
    MLabel* txt_tien_ga;
    MSprite* money_sprite; 
    vector<vector<MSprite*>> sprites;
};

#endif /* ThreeCardsScene_hpp */

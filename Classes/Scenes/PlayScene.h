#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.hpp"
#include "Objects/Player.hpp"
#include "UI/MButton.hpp"
#include "Popups/PopupTLMN.hpp"
#include "Popups/PopupChat.hpp"
#include "Popups/PopupLockTable.hpp"
#include "protobufObject/player.pb.h"
#include "protobufObject/enter_room.pb.h"
#include "Popups/NodeContactUser.hpp"
#include "Popups/PopupInviteToPlay.hpp"

USING_NS_CC;

 class PlayScene : public BaseScene {
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    void onExit();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
    void update(float);

    //reset danh sach nguoi cho
    void resetListWaiting();
    //hidden card remaining count
    void hiddenCardRemainingCount(vector<Avatar*> &avatars);

    void chatResponseHandler();
	void textEmoticonResponseHandler();
	void replyToInviteResponse();
	void getCapchaMessageResponse();

    //set vi tri nguoi choi: indexPos -> vi tri cua nguoi choi trong lst_player 
    //capacity_size -> so nguoi choi toi da trong room
    void setPositionPlayer(Player& player);

    void menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void levelResponseHandler(); 
    void medalResonseHandler();
    void lockRoomResponseHandler();
    void exitRoomResponseHandler();
    bool isDisplayRoomList() const; 
    void setDisplayRoomList(bool _isDisplayRoomList);

	void viewUserInfo(BINViewUserInfoResponse *viewUserInfo);

protected:
	//hien thi nut moi choi (neu so luong nguoi choi numPlaying >= capacity_size thi an nut moi choi di)
	void showInvitePlayer(int numPlaying);

    void initMenu();
    //lay ra avatar cua nguoi choi
    //input: id nguoi choi
    //return avatar
    virtual Avatar* findAvatarOfPlayer(long long player_id);

    void setRoomIndex(int roomIndex);
    int getRoomIndex() const;

    void setPassWordRequired(bool passwordRequired);
    bool getPassWordRequired() const;

    void setPlayerList(vector<BINPlayer> player_list);
    vector<BINPlayer> getPlayerList();

    void setWaitingPlayerList(vector<BINPlayer> waiting_player_list);
    vector<BINPlayer> getWaitingPlayerList();

    void setCreateRoom(bool is_create_room);
    bool isCreateRoom();

	void setVipRoom(bool is_vip_room);
	bool isVipRoom();

	void setMinBet(int minBet);
	int getMinBet();

    void setEnterRoomResponse(BINEnterRoomResponse* reEnterRoomResponse);
    BINEnterRoomResponse* getEnterRoomResponse();
     
     float posYCard();
     
     void runAnimation(const char *format, int count,Vec2 posTarget,int times);
     void addNemAnimation(Avatar * avatar1, Avatar* avatar2, int textEmoticonId);
     float cardWidth();
     
     Vector<SpriteFrame*> getFrameAnimation(const char *format, int count);

	 void displayLockRoomForOwner(int ownerUserId);
     void addCountDown(int countDown);

    //std::vector<Player> lst_player;
    //std::vector<Player&> lst_waiting;

    std::vector<BINPlayer> player_list;
    std::vector<BINPlayer> waiting_player_list;
    std::vector<Avatar*> avatars;
    vector<WaitingPlayer*> lstDisplayWaitingPlayer;
    //so nguoi choi toi da
    int capacity_size = 0;
    int roomIndex;
    int currentTableIndex;
    int currentIndex;
    bool passwordRequired = false;
    bool is_create_room = false;
	bool is_vip_room = false;
    bool _displayRoomList; 
    int _ownerUserId;
	bool check_exit_room = false;
	int minBet;

    int getOwnerUserId() const { return _ownerUserId; }

    void setOwnerUserId(int _ownerUserId) { this->_ownerUserId = _ownerUserId; }

	//an cac nut moi choi va chat doi voi nguoi cho
	void showBtnWithWatingPlayer(bool isShow);

	//int text_emoticon[] = { TAG_CLICK_PHAO, TAG_CLICK_DEP };

    //bien set cac trang thai khi re enterooom
    BINEnterRoomResponse* enter_room_response;

	MLabel* lb_title_game;
	MLabel* lb_title_minbet;
	MLabel* lb_value_minbet;
    //cac nut chung cho cac man hinh game
    MButton* btn_message; //nut message chat
    MButton* btnKhoa;
	MButton* btn_caidat;
	MButton* btnInvitePlay;
};

#endif // __PLAY_SCENE_H__

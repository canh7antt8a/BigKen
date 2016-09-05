//
//  SocdiaScene.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 8/1/16.
//
//

#ifndef SocdiaScene_hpp
#define SocdiaScene_hpp

#include <stdio.h>
#include <vector>
#include "Objects/XocDiaPlayer.hpp"
#include "PlayScene.h"
#include "Objects/XocDiaAvatar.hpp"
#include "Objects/JSONObject.hpp"
#include "Popups/PopupViewPlayerOutsite.hpp"

using namespace cocos2d;
using namespace std;

class SocdiaScene : public PlayScene {
public:
    static Scene* createScene(int roomIndex, vector<BINPlayer> playerList, vector<BINPlayer> waitingPlayerList,
                              bool isCreateRoom, int gameTag, bool isDisplayRoomList, bool passwordRequired,
                              bool isVipRoom, int minbet, BINEnterRoomResponse* reEnterRoomRS, string roomConfig);
    virtual bool init() override;
    virtual void onExit() override;
    
    CREATE_FUNC(SocdiaScene);
    
    void clockCountDown();
	void setPositionPlayer(XocDiaPlayer& player, int position);
    void layoutInit();
    void initGame();
    void update(float dt) override;
    Player* findPlayer(long long playerID);
    void updateListMatchResult(int result);
    
    int getBetRatio();
    void setBetRatio(int ratio);
	void updateMoneyLabel(long long userID, long long displayChangeMoney, long long currentMoney);
    void updateBetLabel(MLabel* totalBet, MLabel* playerBet, string total, string player);
    void enableBetButton(long long totalMoney);
    void setBetsRatio(string JSONString);
    void setVisibleBetButton(bool visible);
    
	void setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list);
	XocDiaPlayer convertFromBINPlayer(BINPlayer binplayer);
	void displayInfoPlayer(std::vector<XocDiaPlayer>& lst_player);
	void sortListPlayer();
	Avatar* findAvatarOfPlayer(long long player_id);

	bool isUserPlaying();

    int getTypeBetRatio(int type);
    void loadNormaTexture();
    void displayResult();

	Player* findWaiting(long long player_id);
	void showChipClicked(int tagChip);
	void showNumberPlayerOutsite();
	void resetDisplayAvatar();
	void deleteWaitingPlayer(string player_id);
    void addChipWhenBet(int typeID, string typeChip, long long userId);
    void removeChip(vector<MSprite*> lst);
    void addChipWin(vector<MSprite*> lst);
    void invisibleBetLable();
    vector<vector<int>> parseJSONtoVector(string JSONString);
    /* Response Handler*/
    void betHandler();
    void updateMoneyResponseHandler();
    void turnResponse();
    void startMatchResponse();
    void matchBeginResponse();
    void prepareNewMatchResponse();
    void playerExitRoomResponse();
    void playerExitRoomAfterMatchResponse();
    void playerEnterRoomResponse();
    void matchEndResponseHandler();
    void hostRegistration();
    void extraBetHandler();
	/*End Response Handler*/
    
protected:
    void menuCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
	void chipCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    
private:
	vector<int> avatar_position;
	vector<int> tag_chip;
    vector<int> _lstMatch;

	vector<XocDiaAvatar*> avatars;
	vector<XocDiaPlayer> lst_player;
	vector<XocDiaPlayer> lst_waiting;
    
    vector<MSprite*> _lstResult;
    vector<MSprite*> _lstChipCuaChan;
    vector<MSprite*> _lstChipCuaLe;
    vector<MSprite*> _lstChipCua4trang;
    vector<MSprite*> _lstChipCua3trang;
    vector<MSprite*> _lstChipCua1trang;
    vector<MSprite*> _lstChipCua0trang;
    vector<MSprite*> _lstChipWin;
    
    vector<vector<int>> _betsRatio;
    
	MButton* btn_san_sang;
    MButton* _btnX1;
    MButton* _btnX5;
    MButton* _btnX25;
    MButton* _btnX50;

    MButton* _btnDatlai;
    MButton* _btnHuyCuoc;
    MButton* _btnGapDoi;
    MButton* _btnCuaChan;
    MButton* _btnCuaLe;
    MButton* _btnCua4Trang;
    MButton* _btnCua3Trang;
    MButton* _btnCua1Trang;
    MButton* _btnCua0Trang;
    MButton* _btnXinlamcai;
    MButton* _btnHuylamcai;
    
    MLabel* _labelCuaChan;
    MLabel* _labelCuaLe;
    MLabel* _labelCua4Trang;
    MLabel* _labelCua3Trang;
    MLabel* _labelCua1Trang;
    MLabel* _labelCua0Trang;
    MLabel* numberPlayerOutsite;
    MLabel* lb_value_chan;
    MLabel* lb_value_le;
    MLabel* _cuaChantotalBet;
    MLabel* _cuaChanPlayBet;
    MLabel* _cuaLeTotalBet;
    MLabel* _cuaLePlayBet;
    MLabel* _cua0TrangTotalBet;
    MLabel* _cua0TrangPlayBet;
    MLabel* _cua1TrangTotalBet;
    MLabel* _cua1TrangPlayBet;
    MLabel* _cua3TrangTotalBet;
    MLabel* _cua3TrangPlayBet;
    MLabel* _cua4TrangTotalBet;
    MLabel* _cua4TrangPlayBet;

    MSprite* girl;
	MSprite* bg_chip;
	MSprite* ic_songuoixem;
	MSprite* bg_thongke_chanle;
    MSprite* dia;
    MSprite* bat;
    
    MSprite* sprite_clock;
    MLabel* timerCountDown;
    
    int _betRatio;
    int _totalBet;
    int _result;
    int _batZorder;
    
    long long _totalMoney;
    
    bool _canBet;
	const int NUMBER_PLAYER_ON_TABLE = 10;  //so nguoi choi hien thi tren ban choi
    
    Vec2 batPos;
};

#endif /* SocdiaScene_hpp */

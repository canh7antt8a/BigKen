
#ifndef __SHOWGAME_SCENE_H__
#define __SHOWGAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseScene.hpp"
#include "Popups/PopupSetting.hpp"
#include "UI/CircleBar.hpp"
#include "protobufObject/enter_zone.pb.h"
#include "Popups/PopupUserInfo.hpp"
#include "Popups/PopupDoiThe.hpp"
#include "Popups/PopupDoiThuong.hpp"
#include "Popups/PopupFriend.h"
#include "Popups/PopupTopUser.hpp"
#include "Popups/PopupGiftCode.hpp"
#include "Popups/PopupHotLine.hpp"
#include "Objects/CardSpriteEventDelegate.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

class PopupGiftCode;

class ShowGame : public BaseScene{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    
    //void addPopups();

    //virtual bool onTouchBegan(Touch touch, Event event);
    void gotoMenuDialog();
    
    void menuCallBack(Ref *sender,Widget::TouchEventType type);
    
    void gameItemCallBack(Ref *sender,Widget::TouchEventType type);

    void update(float) override;
    
	void loadEmail(vector<Mail> lstEmail) override;
	void readMail(Mail mail) override;
	void deleteMail(vector<long> lstMailId) override;

	void viewUserInfo(BINViewUserInfoResponse *viewUserInfo) override;

	void loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs) override;

	void updateMoneyResponseHandler();
    void turnOnPopupFriendResponseHandler();

	void showNumberNewMail();

    // implement the "static create()" method manually
    CREATE_FUNC(ShowGame);
private:
    int gameTag;
    int scrollPage;

    vector<BINUserInfo> listFriends;
    ui::ScrollView* scrollView;
	MLabel* label_xu;
	MLabel* label_ken;
	MLabel* label_hello;
	MSprite* sprite_thongtin;
    bool enableTouch;
    vector<BINRoomConfig> cashRoomList;
    vector<BINRoomConfig> goldRoomList;
	int totalNewMail = 0;
	MSprite* sprite_new_mail;
	MLabel* label_number_new_mail;
};

#endif // __SHOWGAME_SCENE_H__

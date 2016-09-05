//
//  Avatar.hpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#ifndef Avatar_hpp
#define Avatar_hpp

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "UI/MCircleBar.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "Utils/TLMNConfig.hpp"

using namespace cocos2d;

class Avatar : public Node {
public:
    
    virtual bool init(); //chung
    virtual void onExit(); //chung
    
    CREATE_FUNC(Avatar);
    
    void loadAvatar(int index,std::string id,std::string name,std::string money, int roomIndex = 0); //chung
    //void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
    
    Vec2 getCardCoverPostion(int index,Size avatarSize,Size cardSize);
    Vec2 getAvatarPostion(int index,Vec2 origin,Size visiableSize,float buttonHeight);
    
    void loadCardCover(float scale,int index,int numberCard);
    void loadExitRoom(float scale, int index, int numberCard); 
    void hideCardCover();
    void hideExitRoom();
    void addParticle();
    void showXong(bool finished);
    void showPassUp(bool isPassUp);
    void setStatus(string status, int duration);
    
    //event
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
    
    void setWin(int duration); //chung
    void setLose(int duration); //chung
    void setDraw(int duration); //chung
    void setU(int index,int duration);
    
    void hideCardCover(bool ishide);
    void hideNumberCard(bool ishide);
    void hiddenNumberCardAndCover(bool ishide);

    //cap nhat percent xung quanh avatar
    void updateProgressCircleBar(float percent, float time_countdown); //chung

    //reset percent xung quanh avatar
    void resetProcessCircleBar(); //chung

	//show dang ki thoat
	void showRegisterExitRoom(bool isShow);

    long long getPlayerId(){
        return player_id;
    } //chung

	//void menuCallBack(Ref *pSender, Widget::TouchEventType eventType);

public:
    MSprite* background;
    MSprite* avatar;
    MLabel* name;
    MLabel* number;
    MSprite* under_money;
    MLabel* money;
    MSprite* spriteCard;
    MSprite* exit_room;
    MCircleBar* circleBar;
    MSprite* spritePassUp;
	MSprite* ic_register_exit_room;
public:
    void setCurrentAvatar(bool isCurrentAvatar); //chung
    bool getPassUp();
	int getPositionIndex(); //chung
    void setNumberCard(int numberCard);
    //cap nhat tien hien thi cho avatar, money: so tien hien thi
    void setMoney(long long money); //chung
    int getNumberCard();
    int numberCard;

	//hien thi gach da de nem
	void showObjectThrow(); //chung

	void hiddenInfoExtend();  //an het cac thong tin show ra khi click avatar, chung
    
	void menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType); //chung
	void btnCallBack(Ref *pSender, ui::Widget::TouchEventType eventType); //chung

protected:
	int posIndex; //vi tri that cua nguoi choi
	int roomIndex;
	long long player_id;
private:
    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    bool is_current_avatar;
    bool isPassUp = false; //trang thai bo luot
};
#endif /* Avatar_hpp */

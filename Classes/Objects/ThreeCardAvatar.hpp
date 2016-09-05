//
//  Avatar.hpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#ifndef ThreeCardAvatar_hpp
#define ThreeCardAvatar_hpp

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "UI/MCircleBar.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "Utils/TLMNConfig.hpp"
#include "Avatar.hpp"
#include "Card.hpp"
#include <vector>

using namespace std;
using namespace cocos2d;


class ThreeCardAvatar : public Avatar {
public:
    
    virtual bool init();
    virtual void onExit();
    
    CREATE_FUNC(ThreeCardAvatar);
    ~ThreeCardAvatar();
    
    void loadAvatar(int index,std::string id,std::string name,std::string money, int roomIndex, int minBet = 0); //chung 
    Vec2 getCardCoverPostion(int index,Size avatarSize,Size cardSize);
    void setAvatarPostion(int index,Vec2 origin,Size visiableSize,float buttonHeight);
    //event

    void hideCard();
	void showCardCover();
    void addCardCover(float cardWidth);
    void flipCards();
    void setCards(vector<int> cards);
    void clear();


	void showBetBarier();
    void showBetMoney(bool showBetMoney);
    void setBetMoney(int betMoney);
	void hiddenBetBarier();

	void showChuong(bool isChuong);
	void showGa(bool isGa);

	void setConfirm(bool isConfirm);
	bool getConfirm();

	void showBetBarier(long long value, bool isConfirm);

	void menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
public:
    MSprite* cardCover[3];
    Card card[3];

private:
    //cap nhat tien hien thi cho avatar, money: so tien hien thi
	int minBet;  //so tien cuoc de hien thi danh bien
	MButton* betBarier1;
	MButton* betBarier2;
	MSprite* chuong;
	MSprite* ga;
    MSprite* bg_bet_money;
    MLabel *bet_money;
	bool isConfirm = false;
};
#endif /* ThreeCardAvatar_hpp */

//
//  NodeContactUser.hpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#ifndef NodeContactUser_hpp
#define NodeContactUser_hpp
#include "cocos2d.h"
#include <vector>
#include <protobufObject/friend.pb.h>
#include <UI/MSprite.hpp>
#include <UI/MLabel.hpp>
#include <UI/MButton.hpp>
#include <Utils/Common.h>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace std;

class NodeContactUser : public Node {
public:
	CREATE_FUNC(NodeContactUser);
    virtual bool init();
    virtual void onExit();
    
	void update(float);
    void changeText(int tag, string);
	void viewUserInfo(BINViewUserInfoResponse *viewUserInfo);

	void addFriendResponse();
	void removeFriendResponse();
	void approveFriendResponse();
	void viewUserInfoFromServer();

	void showFriendStatus(int friendStatus);

	void clickCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    
private:
    float getWidth();
    float getHeight();
	MSprite* avatar;
	MLabel* userID_text;
	MLabel* userLevel_text;
	MLabel* userName_text;
	MLabel* userVip_text;
	MLabel* userSdt;
	MLabel* userSdt_text;
	MLabel* chisotinnhiem_text;
	MLabel* sovanchoi_text;
	MLabel* sovanthang_text;
	MLabel* sovanthua_text;
	MLabel* xu_text;
	MLabel* ken_text;
	MButton* btnAddFriend;
	MButton* btnRemoveFriend;
	MButton* btnAccpeptFriend;
	MButton* btnDenyFriend;
	MLabel* lbStatusFriend;
	MSprite* backgroundPopup;
	long targetUserId = 0;
};

#endif /* NodeContactUser_hpp */

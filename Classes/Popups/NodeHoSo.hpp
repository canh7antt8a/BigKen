//
//  NodeHoSo.hpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#ifndef NodeHoSo_hpp
#define NodeHoSo_hpp
#include "cocos2d.h"
#include <vector>
#include <protobufObject/user_info.pb.h>
#include <UI/MSprite.hpp>
#include <UI/MLabel.hpp>
#include "ui/CocosGUI.h"
#include <Utils/Common.h>
#include "PopupChangePhone.h"
#include "PopupChangePass.h"
using namespace cocos2d;
using namespace std;

class NodeHoSo : public Node {
public:

	CREATE_FUNC(NodeHoSo);
    virtual bool init();
    virtual void onExit();
    void menuPopupCallBack1(Ref *sender, ui::Widget::TouchEventType type);
    void changeText(int tag, string);
	void viewUserInfo(BINUserInfo userInfo);
    void update(float) override;
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
    

    /*PopupChangePhone *m_popupEditPhone; 
    PopupChangePass *m_popupChangePass;*/
};

#endif /* NodeHoSo_hpp */

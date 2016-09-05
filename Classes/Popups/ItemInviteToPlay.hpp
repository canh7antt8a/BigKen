#ifndef ItemInviteToPlay_hpp
#define ItemInviteToPlay_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI/MSprite.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MLabel.hpp"
#include <protobufObject/user_info.pb.h>
#include "Popups/PopupInviteToPlay.hpp"

class PopupInviteToPlay;

using namespace std;
using namespace cocos2d;
USING_NS_CC;

class ItemInviteToPlay : public Node {
public:
	virtual bool init() override;
	virtual void onExit() override;
    
	ItemInviteToPlay();
	virtual ~ItemInviteToPlay();

	static ItemInviteToPlay* create(Size contentSize, BINUserInfo userInfo, bool isVipRoom, bool checkAll, PopupInviteToPlay* context);
    
    float getWidth();
    float getHeight();
    
	void setUserInviteId(long userInviteId);
	void setContext(PopupInviteToPlay* context);
	void setRadioChecked();

	void menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type);

private:
	long userInviteId;
	PopupInviteToPlay* context;
};
#endif /* ItemCell_hpp */

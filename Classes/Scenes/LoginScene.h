#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "zlib.h"
#include "ui/CocosGUI.h"
#include "BaseScene.hpp"
#include "UI/MEditBox.hpp"
#include "protobufObject/user_info.pb.h"

USING_NS_CC;

class LoginScene : public BaseScene, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    virtual void onExit() override;

    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    
    void menuCallBack(Ref *pSender, Widget::TouchEventType eventType);
    
    static void readFrom(std::vector<char> read_str, int len);
    static std::vector<char> decompress_gzip2(const char* byte_arr, uLong length);
    void handler(std::vector<std::pair<google::protobuf::Message*, int>> listMessages);
    bool isHasPlayingMatch() const; 
    void setHasPlayingMatch(bool _hasPlayingMatch); 
    
	// implement the "static create()" method manually
	CREATE_FUNC(LoginScene);
    
    void update(float) override;
    void enterRoomResponseHandler();
    
    void saveUserInfo(BINUserInfo userInfo);
    void saveUserSetting(BINUserSetting userSetting);
    
    //response handler
    

private:
    ui::EditBox* edit_user;
    ui::EditBox* edit_matkhau;
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox)  override;
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox)  override;
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text)  override;
    virtual void editBoxReturn(ui::EditBox *editBox)  override;
    bool hasPlayingMatch;
};

#endif // __LOGIN_SCENE_H__

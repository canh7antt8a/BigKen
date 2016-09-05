
#ifndef __REGISTER_SCENE_H__
#define __REGISTER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseScene.hpp"

USING_NS_CC;
using namespace cocos2d::ui;

class RegisterScene : public BaseScene,public ui::EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    
    virtual void editBoxEditingDidBegin(ui::EditBox* editBox) override;
    virtual void editBoxEditingDidEnd(ui::EditBox* editBox) override;
    virtual void editBoxTextChanged(ui::EditBox* editBox, std::string &text);
    virtual void editBoxReturn(ui::EditBox * editBox) override;
	
	// implement the "static create()" method manually
	CREATE_FUNC(RegisterScene);
    
    void update(float) override;

	void saveUserInfo(BINUserInfo userInfo);
	void saveUserSetting(BINUserSetting userSetting);
    
public:
    void initMenu();
    
public:
    
    std::string nhap_matkhau_str;
    std::string nhap_sdt_str;
    std::string nhaplai_matkhau_str;

private:
    void menuCallBack(Ref *sende,Widget::TouchEventType type);
};

#endif // __REGISTER_SCENE_H__

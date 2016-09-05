//
//  PopupDoiThe.hpp
//  MyCards
//
//  Created by hungle on 6/21/16.
//
//

#ifndef PopupDoiThe_hpp
#define PopupDoiThe_hpp

#include "UI/Popup.hpp"
#include "UI/MSprite.hpp"
#include "UI/MEditBox.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
class PopupDoiThe : public Popup,public ui::EditBoxDelegate {
    
public:
    
    CREATE_FUNC(PopupDoiThe);
    
    bool init();
    virtual void onExit();
    void addMenu();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);
    static PopupDoiThe* createPopup(string captcha_text, string security_key);
    void update(float) override;
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox) ;
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox) ;
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text) ;
    virtual void editBoxReturn(ui::EditBox *editBox) ;
    void setCaptchaText(string captcha_text);
    string getCaptchaText();
    void setSecurityKey(string captcha_text);
    string getSecurityKey();
private:
    MSprite* tab;
    MLabel* captcha;
    string captcha_text;
    string security_key;
    ui::EditBox* input_seria;
    ui::EditBox* input_mathe;
    ui::EditBox* input_captcha;
	MSprite* contentPopupLeft;
	MSprite* contentPopupRight;
	float padding_left;
	float heightTab;
protected:
    MButton * btnVinaphone;
    MButton * btnMobiphone;
    MButton * btnViettel;
    string type_selected;
};

#endif /* PopupDoiThe_hpp */

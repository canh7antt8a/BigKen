//
//  PopupMuaThe.hpp
//  MyCards
//
//  Created by hungle on 6/21/16.
//
//

#ifndef PopupMuaThe_hpp
#define PopupMuaThe_hpp

#include "UI/Popup.hpp"
#include "UI/MSprite.hpp"
#include "UI/MEditBox.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
class PopupMuaThe : public Popup,public ui::EditBoxDelegate {
    
public:
    
    CREATE_FUNC(PopupMuaThe);
    
    bool init();
    virtual void onExit();
    void addMenu();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);
    static PopupMuaThe* createPopup(string captcha_text, string security_key);
    void update(float) override;
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox) ;
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox) ;
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text) ;
    virtual void editBoxReturn(ui::EditBox *editBox) ;
private:
    MSprite* tab;
protected:
    MButton * btnVinaphone;
    MButton * btnMobiphone;
    MButton * btnViettel;
    string type_selected;
};

#endif /* PopupMuaThe_hpp */

#ifndef __POPUP_CHAT_H__
#define __POPUP_CHAT_H__

#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "UI/MEditBox.hpp"
#include "Utils/Image.h"

USING_NS_CC;

class PopupChat : public Popup,public ui::EditBoxDelegate{
    
public:

    void createPopUp(int scope);
    
    CREATE_FUNC(PopupChat);

    bool init();
    virtual void onExit();
    //virtual void editBoxEditingDidEnd(ui::EditBox *editBox)  override;

    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void buttonTextCallBack(Ref *sender, ui::Widget::TouchEventType type);
    static PopupChat* createPopup(int roomIndex);
    void setScope(int scope);
    void setMessage(std::string message);
    int getScope();
    std::string imageMessageTemp(std::string text);
    
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox);
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox);
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text);
    virtual void editBoxReturn(ui::EditBox *editBox);
    void disappear();
    void appear();
    
private:
    int scope;
    ui::EditBox* edit_message;
    MButton* btn_send_message;
    MButton* btn_txt_temp1;
    MButton* btn_txt_temp2;
    MButton* btn_txt_temp3;
    MButton* btn_txt_temp4;
    MButton* btn_txt_temp5;
    MButton* btn_txt_temp6;
};

#endif /* defined (__POPUP_CHAT_H__) */

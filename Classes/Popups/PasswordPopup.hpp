#ifndef PasswordPopup_hpp
#define PasswordPopup_hpp

#include <stdio.h>
#include "UI/Popup.hpp"
#include "UI/MEditbox.hpp"
class PasswordPopup : public Popup, public ui::EditBoxDelegate {
public:
    CREATE_FUNC(PasswordPopup);
    static PasswordPopup *create(int roomIndex);
    bool init();
    virtual void onExit();
    void setRoomIndex(int roomIndex);
    int getRoomIndex();
private:
    
    int roomIndex;
    std::string password;
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);

    virtual void editBoxEditingDidBegin(ui::EditBox *editBox);
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox);
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text);
    virtual void editBoxReturn(ui::EditBox *editBox);
};

#endif /* PasswordPopup_hpp */

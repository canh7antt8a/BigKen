//
//  PopupLockTable.hpp
//  MyCards
//
//  Created by hungle on 6/23/16.
//
//

#ifndef PopupLockTable_hpp
#define PopupLockTable_hpp

#include "UI/Popup.hpp"
#include "UI/MEditbox.hpp"

class PopupLockTable : public Popup,public ui::EditBoxDelegate {
    
public:
    CREATE_FUNC(PopupLockTable);
    static PopupLockTable *create(int roomIndex);
    bool init();
    virtual void onExit();
    
    void setLock(bool look);
    bool isLocked();

private:
    int roomIndex;
    std::string password;
    bool lock = false;
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox);
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox);
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text);
    virtual void editBoxReturn(ui::EditBox *editBox);
};

#endif /* PopupLockTable_hpp */

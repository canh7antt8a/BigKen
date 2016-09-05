
#ifndef PopupUserInfo_hpp
#define PopupUserInfo_hpp

#include "UI/Popup.hpp"
#include "UI/MSprite.hpp"
#include "UI/MEditBox.hpp"
#include "UI/MLabel.hpp"

#include "NodeHoSo.hpp"
#include "NodeHopThu.hpp"
#include "NodeLichSuDoiThuong.hpp"

class PopupUserInfo : public Popup, public ui::EditBoxDelegate {
    
public:
    
    CREATE_FUNC(PopupUserInfo);
    
    bool init();
    virtual void onExit();
    void addMenu();
    void addMenuHomThu();
    void addMenuDoiThuong();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);
    
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox) ;
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox) ;
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text) ;
    virtual void editBoxReturn(ui::EditBox *editBox) ;
	
	void setPositionTab(int positionTab);
	int getPositionTab();

	void setTargetUserId(int targetUserId);

	NodeHoSo* getNodeHoSo();
	NodeHopThu* getNodeHopThu();
	NodeLichSuDoiThuong* getNodeLsDoiThuong();

	void showPositionTab(int positionTab);
	
private:
    MSprite* tab;
    NodeHoSo* tab_user;
	NodeHopThu* tab_email;
	NodeLichSuDoiThuong* tab_ls_doithuong;
	int positionTab;  //1: userInfo, 2: email, 3: ls doi thuong
	int targetUserId = 0;
	MSprite* contentPopupLeft;
	float padding_left;
	float heightTab;
};

#endif /* PopupDoiThe_hpp */

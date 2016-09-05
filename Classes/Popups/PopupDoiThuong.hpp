#ifndef PopupDoiThuong_hpp
#define PopupDoiThuong_hpp

#include "UI/Popup.hpp"
#include "cocos2d.h"
#include <vector>
#include "UI/MEditBox.hpp"
#include "Scenes/ShowGame.h"
#include "NodeDoiTheCao.hpp"

using namespace std;
using namespace cocos2d;

class ShowGame;

class PopupDoiThuong : public Popup {
public:
	CREATE_FUNC(PopupDoiThuong);

    bool init();
    virtual void onExit();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);

	void update(float);

	void test();

	void setContext(ShowGame* showGame);

	void handlerAssetConfigResponse();
	void handlerExchangeAssetResponse();
private:
	ShowGame* showGame;
    MSprite* tab;
	float heightTab;
	MSprite* contentPopupLeft;
	NodeDoiTheCao* nodeDoiTheCao;
	float padding_left;
};

#endif

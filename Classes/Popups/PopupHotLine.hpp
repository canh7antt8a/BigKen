#ifndef PopupHotLine_hpp
#define PopupHotLine_hpp

#include "UI/Popup.hpp"
#include "cocos2d.h"
#include <vector>
#include "UI/MToast.hpp"

using namespace std;
using namespace cocos2d;

class PopupHotLine : public Popup {
public:
	CREATE_FUNC(PopupHotLine);
    
    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
	
	void update(float);
};

#endif

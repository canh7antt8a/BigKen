#ifndef NodeReadMail_hpp
#define NodeReadMail_hpp

#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <vector>
#include "Objects/Mail.h"
#include "ItemMail.hpp"
#include "Utils/TLMNConfig.hpp"
#include "NodeHopThu.hpp"
#include "Utils/NetworkManager.h"
#include "Objects/OnEvenListener.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
USING_NS_CC;

class NodeReadMail : public Node, OnEvenListener<Mail> {
public:
    CREATE_FUNC(NodeReadMail);
	static NodeReadMail* createReadMail(Mail mail, NodeHopThu* node);
    virtual bool init() override;
    virtual void onExit() override;
	void addEvents(MButton* btnDel, MButton* btnRead, MButton* btnRecv, Mail item, NodeHopThu* node);

	void menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type, Mail item, NodeHopThu* node);

	void onEvent(int enventType, Mail sender) override;
private:
    
    float getWidth();
    float getHeight();
	NodeHopThu* nodeHopThu;
};

#endif /* NodeReadMail_hpp */

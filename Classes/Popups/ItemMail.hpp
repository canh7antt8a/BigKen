#ifndef ItemMail_hpp
#define ItemMail_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI/MSprite.hpp"
#include "UI/MButton.hpp"
#include "Popups/NodeHopThu.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Objects/Mail.h"
#include "UI/MLabel.hpp"
#include "Objects/OnEvenListener.hpp"

using namespace std;
using namespace cocos2d;
USING_NS_CC;

class NodeHopThu;

class ItemMail : public Node, OnEvenListener<Mail> {
public:
    
	virtual bool init() override;
	virtual void onExit() override;
    
	ItemMail();
	virtual ~ItemMail();

	static ItemMail* create(Mail mail, int idx, NodeHopThu* nodeMail);
    
	void onEvent(int enventType, Mail sender) override;

    void addEvents(MButton* btnDel, MButton* btnRead, MButton* btnRecv, Mail item);
    
    float getWidth();
    float getHeight();
    
	void menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type, Mail item);
	void setNodeMail(NodeHopThu *nodeMail);

private:
	NodeHopThu* nodeMail;
};
#endif /* ItemCell_hpp */

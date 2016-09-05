#ifndef ItemDoiThe_hpp
#define ItemDoiThe_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "protobufObject/exchange.pb.h"
#include "Objects/OnEvenListener.hpp"

using namespace cocos2d;

class ItemDoiThe : public Node, OnEvenListener<BINAsset> {
    
public:
    
    ItemDoiThe();
    virtual ~ItemDoiThe();
    
    bool init();
    
	static ItemDoiThe* create(BINAsset asset, float width, float height);
    
	void onEvent(int enventType, BINAsset sender) override;

	void addEvents(BINAsset asset);

    virtual void onExit();
    
    float getWidth();
    float getHeight();
    
private:
    cocos2d::Vec2 getPostion();
};



#endif /* ItemDoiThe_hpp */

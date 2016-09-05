//
//  MCheckbox.hpp
//  MyCards
//
//  Created by hungle on 4/25/16.
//
//

#ifndef MCheckbox_hpp
#define MCheckbox_hpp

#include "cocos2d.h"
#include "UI/MSprite.hpp"

using namespace cocos2d;

class MCheckbox : public Node {
    
public:
    CREATE_FUNC(MCheckbox);
    
    virtual bool init();
    virtual void onExit();
    
    virtual void on(std::string textureName);
    virtual void off(std::string textureName);

protected:
    MSprite *checkbox;
};

#endif /* MCheckbox_hpp */

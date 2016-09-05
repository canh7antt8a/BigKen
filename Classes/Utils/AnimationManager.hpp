//
//  AnimationManager.hpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#ifndef AnimationManager_hpp
#define AnimationManager_hpp

#include "cocos2d.h"
using namespace cocos2d;

class AnimationManager : public Node {
    
public:
    AnimationManager();
    ~AnimationManager();
    void show(int index,Size _visibleSize);
    static AnimationManager* getInstance();
    bool init();
    void update(float);
    
private:
    float deltaTime;
    float _deltaTime;
    int count;
    bool isRunning;
    std::vector<Sprite*> anims;
    std::vector<Sprite*> _anims;
    Vector<SpriteFrame*> frames;
    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    static AnimationManager* _instance;
};

#endif /* AnimationManager_hpp */

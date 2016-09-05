#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.hpp"

USING_NS_CC;

class IntroScene : public BaseScene {
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onExit();
	CREATE_FUNC(IntroScene);
	void update(float);
    
public:
    std::string getId();
    
private:
	float percent = 0.0f;
	Slider* loadingBar;
	void gotoStartScene(float dt);
    float deltaTime = 0;
    bool nextScene = false;
};

#endif // __INTRO_SCENE_H__

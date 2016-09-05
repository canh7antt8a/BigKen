//
//  Popup.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

//
//  Popup.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ Popup.h
#ifndef ___POPUP_HPP__
#define ___POPUP_HPP__

#include "string"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "UI/MSprite.hpp"

using namespace cocos2d::ui;

USING_NS_CC;

class Popup : public Node {
public:
    CREATE_FUNC(Popup);
    
    virtual bool init();
    virtual void onExit();
    
    virtual void disappear();
    virtual void appear();
    
	bool checkLocation(float x, float y);
	bool onTouchBegan(Touch* touch, Event* event);
protected:
    Layer                       *m_popupLayer;
    LayerColor                     *background;
    MSprite                     *backgroundPopup;
    
    Size                        backgroundContentSize;
    Size                        visibleSize;
    Point                       origin;

public:
  //static Popup* createPopup(int roomIndex);
  void setRoomIndex(int roomIndex);
  int getRoomIndex();
  bool disablePopup;
};

#endif /* defined (___POPUP_HPP__) */

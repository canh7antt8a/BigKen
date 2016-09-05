//
//  MButton.hpp
//  GameVina
//
//  Created by Black3rry on 3/22/16.
//
//

#ifndef MButton_hpp
#define MButton_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

class MButton : public cocos2d::ui::Button {
    
public:
    
    static MButton* create(std::string textureNormal);
    static MButton* create(std::string textureNormal,int tag);
    static MButton* create(std::string textureNormal,std::string textureDisable,int tag);
    static MButton* create(std::string textureNormal,std::string text,
                           float textSize,int tag);
    static MButton* createWithIcon(std::string bgrName, std::string Iconname, std::string text, float size,
      int tag);
    static MButton* create(std::string textureNormal,std::string texturePressed,
                           std::string text,float textSize,int tag);
    static MButton* create(std::string textureNormal,std::string text,
                           float textSize,cocos2d::Color3B textColor,int tag);
    static MButton* create(std::string text,float size,int tag);
    
    static MButton* createExtends(std::string textureNormal,std::string text,
                                  float size,int tag);
	static MButton* createExtendsBottom(std::string textureName, std::string text,
		float size, int tag);
    static MButton* createExtendsIcon(std::string textureNormal, std::string text,
      float size, int tag, float width);
    static MButton* createItem(std::string textureNormal,int tag);
    
    
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize,
                                    std::string text,int tag);
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize);
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize,
                                    int tag);
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize,
                                    std::string text,float textSize,int tag);
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize,
                                    std::string texturePressed,std::string text,float textSize,int tag);
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size buttonSize,
                                    std::string text,float textSize,cocos2d::Color3B textColor,int tag);
    static MButton* createWidthSize(std::string text,float size,int tag);
    
    static MButton* createExtendsWithSize(std::string textureNormal,cocos2d::Size buttonSize,
                                          std::string text,float size,int tag);
    static MButton* createItemwithSize(std::string textureNormal,cocos2d::Size buttonSize,
                                       int tag);
   
    static MButton* createExtendsWithSizeTextLeft(std::string textureNormal, cocos2d::Size buttonSize,
      std::string text, float size, int tag);

    float getWidth();
    float getHeight();
    float getRightPosition();
    
    
    //===== init
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MButton);
    
};

#endif /* MButton_hpp */

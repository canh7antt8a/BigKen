//
//  MButton.cpp
//  GameVina
//
//  Created by Black3rry on 3/22/16.
//
//

#include "MButton.hpp"
#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"

USING_NS_CC;

MButton* MButton::create(std::string textureName){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    
    return btn;
}

MButton* MButton::create(std::string textureName,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    return btn;
}

MButton* MButton::create(std::string textureName,std::string text,float size,
                         int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}
MButton* MButton::createWithIcon(std::string bgrName, std::string iconName, std::string text, float size,
  int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(bgrName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0, 0));
    btn->setTag(tag);
    auto icon = MSprite::create(iconName);
    icon->setPosition(Vec2(btn->getWidth()/6,btn->getHeight()/2 - icon->getHeight()/2));
    btn->addChild(icon);
    auto label = MLabel::create(text, 28);
    label->setAnchorPoint(cocos2d::Vec2(0, 0));
    label->setPosition(icon->getPosition().x + icon->getWidth() + 5, btn->getHeight() / 2 - label->getHeight()/2);
    btn->addChild(label);
    return btn;

}

MButton* MButton::create(std::string textureNormal,std::string texturePressed,
                         std::string text,float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureNormal);
    btn->loadTexturePressed(texturePressed);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);

    
    return btn;
    
}

// icon + text
MButton* MButton::createExtends(std::string textureName,std::string text,
                                float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    if (text != ""){
      auto label = Label::createWithTTF(text, "fonts/gamevina.otf", btn->getHeight() / 1.5f);
      label->setAnchorPoint(cocos2d::Vec2(0, 0));
      label->setPosition(btn->getWidth() + 5, 0);
      btn->addChild(label);
    }
    return btn;
}

// icon + text bottom
MButton* MButton::createExtendsBottom(std::string textureName, std::string text,
	float size, int tag){
	MButton *btn = MButton::create();
	btn->loadTextureNormal(textureName);
	btn->setZoomScale(0.2f);
	btn->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	btn->setTag(tag);
	if (text != ""){
		auto label = Label::createWithTTF(text, "fonts/gamevina.otf", btn->getHeight() / 2.0f);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
		label->setPosition(btn->getWidth() / 2, -5);
		btn->addChild(label);
	}
	return btn;
}

//text + icon
 MButton* MButton::createExtendsIcon(std::string textureName, std::string text,
 float size, int tag, float width){

  MButton *btn = MButton::create();
  btn->loadTextureNormal(textureName);
  btn->setZoomScale(0.02f);
  btn->setAnchorPoint(cocos2d::Vec2(0, 0));
  btn->setTag(tag);

  auto label = Label::createWithTTF(text, "fonts/gamevina.otf", btn->getHeight() / 1.5f);
  label->setAnchorPoint(cocos2d::Vec2(0, 0));
  label->setPosition(btn->getWidth() - width, 0);
  btn->addChild(label);

  return btn;

 }

MButton* MButton::create(std::string textureName,std::string text,float size,
                         cocos2d::Color3B color,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleColor(color);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::create(std::string text,float size,int tag) {
    MButton *btn = MButton::create();
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::createItem(std::string textureName,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setTag(tag);
    
    return btn;
}

//========================== create button with Size

MButton* MButton::createWidthSize(std::string textureNormal,cocos2d::Size textureSize,
                                  std::string text,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureNormal);
    btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setTitleText(text);
	btn->setTitleFontSize(btn->getHeight() / 3);
    btn->setTag(tag);
    
    return btn;
}

MButton* MButton::createWidthSize(std::string textureName,cocos2d::Size textureSize){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    
    return btn;
}

MButton* MButton::createWidthSize(std::string textureName,cocos2d::Size textureSize,
                                  int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->ignoreContentAdaptWithSize(false);
    //btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setZoomScale(0.02f);
    //btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    
    return btn;
}

MButton* MButton::createWidthSize(std::string textureName,cocos2d::Size textureSize,
                                  std::string text,float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::createWidthSize(std::string textureNormal,cocos2d::Size textureSize,
                                  std::string texturePressed,std::string text,float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureNormal);
    btn->loadTexturePressed(texturePressed);
    btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}
// tao button text ben trai
MButton* MButton::createExtendsWithSizeTextLeft(std::string textureName, cocos2d::Size textureSize,
  std::string text, float size, int tag) { 
  MButton *btn = MButton::create();
  btn->loadTextureNormal(textureName);
  btn->setScale9Enabled(true);
  btn->setContentSize(textureSize);
  btn->setZoomScale(0.02f);
  btn->setAnchorPoint(cocos2d::Vec2(0, 0));
  btn->setTag(tag);
  
  auto label = Label::createWithTTF(text, "fonts/gamevina.otf", btn->getHeight() / 2);
  label->setAnchorPoint(cocos2d::Vec2(0, 0));
  label->setPosition(15, btn->getHeight() / 3);
  btn->addChild(label, 102);
  
  return btn;
}


MButton* MButton::createExtendsWithSize(std::string textureName,cocos2d::Size textureSize,
                                        std::string text,float size,int tag){
    
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setScale9Enabled(true);
    btn->setContentSize(textureSize);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    
    /*btn->setTitleText(text);
    btn->setTitleFontSize(btn->getHeight()/3);
    btn->setTitleFontName("fonts/gamevina.otf");*/
    
    auto label = Label::createWithTTF(text, "fonts/gamevina.otf", btn->getHeight()/2);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    label->setPosition(btn->getContentSize().width+5,0);
    btn->addChild(label);
    
    //btn->getTitleRenderer()->setAnchorPoint(Vec2(0,0));
    //btn->getTitleRenderer()->setPosition(btn->getContentSize().width+5,0);
    
    return btn;
    
}

float MButton::getWidth(){
    return this->getContentSize().width;
}

float MButton::getHeight(){
    return this->getContentSize().height;
}
float MButton::getRightPosition(){
  return this->getPosition().x + this->getWidth();
}
bool MButton::init()
{
    if (!Button::init()) {
        return false;
    }
    return true;
}



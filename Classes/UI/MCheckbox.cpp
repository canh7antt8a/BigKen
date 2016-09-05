//
//  MCheckbox.cpp
//  MyCards
//
//  Created by hungle on 4/25/16.
//
//

#include "MCheckbox.hpp"
#include "UI/MLabel.hpp"

bool MCheckbox::init() {
    if (!Node::init())
        return false;
    
    checkbox = MSprite::create("toogle_off.png");
    checkbox->setPosition(Vec2(0,0));
    this->addChild(checkbox);
    
    auto label = MLabel::create("sound", 30,Color3B(0,0,0));
    label->setPosition(Vec2(checkbox->getWidth()+5,
                            checkbox->getHeight()/2-label->getWidth()/2));
    this->addChild(label);
    
    return true;
}

void MCheckbox::on(std::string textureName){
    checkbox->setTexture(textureName);
}

void MCheckbox::off(std::string textureName){
    checkbox->setTexture(textureName);
}

void MCheckbox::onExit() {
    Node::onExit();
}



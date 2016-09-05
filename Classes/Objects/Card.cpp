//
//  Card.cpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//
#include "Card.hpp"
#include "cocos2d.h"
#include "Utils/Common.h"
USING_NS_CC;


Card::Card(const int value){
    this->value = value; 
}

Card::~Card()
{
    this->value = 0; 
}

string Card::name() const {
    return StringUtils::format("%02dx.png", value);
}

string Card::getPhomName() const {
    int nameValue = value - 8;
    if (nameValue < 1) nameValue = nameValue + 52;
    return StringUtils::format("%02dx.png", nameValue);
}

string Card::getMauBinhName() const {
    //1-4 ==> 49-52, 5-8 ==> 1-4, ..., 49-52 ==> 45-48
    int nameValue = value - 4; 
    if (nameValue < 1) nameValue = nameValue + 52; 
    return StringUtils::format("%02dx.png", nameValue);
}

string Card::getThreeCardName() const {
    int nameValue = value - 8;
    if (nameValue < 1) nameValue = nameValue + 52;
    if (nameValue % 4 == 0) {
        nameValue--;
    }
    else if (nameValue % 4 == 3) {
        nameValue++;
    }
    return StringUtils::format("%02dx.png", nameValue);
}

string Card::getActualName() {
    std::string val; 
    switch (Common::getInstance()->getZoneId())
    {
    case 4:
        val = this->getPhomName();
        break;
    case 5:
        val = this->name();
        break;
    case 1:
        val = this->getThreeCardName();
        break;
    case 12: 
        val = this->getMauBinhName();
        break;
    default:
        val = this->name();
        break;
    }
    return val; 
}

int Card::getValue() const {
    return this->value; 
}

void Card::setValue(int val) {
    this->value = val;
}
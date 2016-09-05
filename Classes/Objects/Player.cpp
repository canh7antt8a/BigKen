//
//  Player.cpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//
#include "Player.hpp"

Player::Player(){

}

Player::~Player()
{
}
Player::Player(std::string n, std::string i, long long c, long long g, int h)
{
    name = n; 
    id = i; 
    cash = c; 
    gold = g;
    avatar_id = h;
    this->_win = false;
    // Nothing Here
}

//===== get

std::string Player::getName() {
    return name;
}

std::string Player::getID() {
    return id;
}

long long int Player::getCash() {
    return cash;
}

long long int Player::getGold() {
    return gold;
}

int Player::getAvatarId(){
    if (this->avatar_id < 100000){
        return 0;
    }
    return this->avatar_id;
}

//=========== set

void Player::setName(std::string n) {
    name = n;
}

void Player::setID(std::string i) {
    id = i;
}

void Player::setCash(long long int c){
    cash = c;
}

void Player::setGold(long long int g){
    gold = g;
}

bool Player::isWin() const {
    return _win; 
}

void Player::setWin(bool _win) {
    this->_win = _win;
}

//set tien cho nguoi choi la cash hay gold
void Player::setMoney(bool isCash, long long money){
    if (isCash){
        cash = money;
    }
    else {
        gold = money;
    }
}

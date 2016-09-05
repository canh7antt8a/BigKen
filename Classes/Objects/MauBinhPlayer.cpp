//
//  MauBinhPlayer.cpp
//  MyCards
//
//  Created by hungle on 8/4/16.
//
//

#include "MauBinhPlayer.hpp"
#include <ostream>

MauBinhPlayer::MauBinhPlayer(std::string n, std::string i, int number, long long c, long long g, int pos, int tableIndex, int avatar_id) : Player(n, i, c, g, avatar_id) {
    numberCard = number;
    postion = pos;
    this->tableIndex = tableIndex;
    this->_draw = false; //set draw = false
    this->_status = NO_STATUS; 
}

int MauBinhPlayer::getNumberCard(){
    return numberCard;
}

int MauBinhPlayer::getPostion(){
    return postion;
}

void MauBinhPlayer::setDraw(bool _draw) {
    this->_draw = _draw; 
}
bool MauBinhPlayer::isDraw() const {
    return this->_draw;
}

void MauBinhPlayer::setNumberCard(int number){
    numberCard = number;
}

void MauBinhPlayer::setPostion(int pos){
    postion = pos;
}

PlayerState MauBinhPlayer::getState() {
    return this->state;
}

void MauBinhPlayer::setStatus(int _status) {
    this->_status = _status; 
}
int MauBinhPlayer::getStatus() const {
    return this->_status;
}

void MauBinhPlayer::setState(PlayerState state) {
    this->state = state;
}

void MauBinhPlayer::setTableIndex(int _tableIndex) {
    this->tableIndex = _tableIndex;
}

int MauBinhPlayer::getTableIndex() {
    return this->tableIndex;
}

bool MauBinhPlayer::operator<(const MauBinhPlayer &right) const {
    return (tableIndex < right.tableIndex);
}

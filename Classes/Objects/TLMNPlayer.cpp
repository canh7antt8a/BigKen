//
//  TLMNPlayer.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 5/17/16.
//
//

#include "TLMNPlayer.hpp"
#include <ostream>

TLMNPlayer::TLMNPlayer(std::string n, std::string i, int number, long long c, long long g, int pos, int tableIndex, int avatar_id) : Player(n, i, c, g, avatar_id) {
    numberCard = number;
    postion = pos;
    this->tableIndex = tableIndex; 
}

int TLMNPlayer::getNumberCard(){
    return numberCard;
}

int TLMNPlayer::getPostion(){
    return postion;
}

void TLMNPlayer::setNumberCard(int number){
    numberCard = number;
}

void TLMNPlayer::setPostion(int pos){
    postion = pos;
}

PlayerState TLMNPlayer::getState() {
    return this->state;
}

void TLMNPlayer::setState(PlayerState state) {
    this->state = state;
}

void TLMNPlayer::setTableIndex(int _tableIndex) {
    this->tableIndex = _tableIndex;
}

int TLMNPlayer::getTableIndex() {
    return this->tableIndex;
}

bool TLMNPlayer::operator<(const TLMNPlayer &right) const {
    return (tableIndex < right.tableIndex);
}

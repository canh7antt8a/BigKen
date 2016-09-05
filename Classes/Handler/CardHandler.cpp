#include "CardHandler.h"
#include "Utils/TLMNConfig.hpp"
#include "iostream"

using namespace std;

CardHandler::CardHandler()
{
    
}

CardHandler::~CardHandler()
{
}

/*lay ra gia tri goc cua quan bai*/
int CardHandler::getCardValue(int card){
    return (card - 1) / 4;
}

/*lay ra chat cua quan bai*/
int CardHandler::getCardType(int card) {
    return (card - 1) % 4;
}


bool CardHandler::isHavingTwoCard(vector<int> cards){
    for (int card : cards) {
        if (getCardValue(card) == CardValue::TWO){
            return true;
        }
    }
    return false;
}

/*kiem tra loai card la card don, bo doi, ba, bon hay la day lien tiep*/
int CardHandler::checkCardType(vector<int> cards){
    if (cards.size() == 0) {
        return CheckType::NO_CARD;
    }

    if (cards.size() == 1) {
        return CheckType::CARD_SINGLE;
    }

    if (cards.size() > 2) {
        if (isSerialCards(cards)) {
            return CheckType::CARD_SERIAL;
        }
        else if (isSerialCouple(cards)) {
            return CheckType::CARD_SERIAL_COUPLE;
        }
    }

    for (int i = 0; i < cards.size() - 1; i++) {
        if (getCardValue(cards.at(i)) != getCardValue(cards.at(i + 1))) {
            return CheckType::CARD_FAIL;
        }
    }

    if (cards.size() == 2 || cards.size() == 3 || cards.size() == 4) {
        return CheckType::CARD_COUPLE;
    }

    return CheckType::CARD_FAIL;
}

vector<int> CardHandler::findTuQuy(vector<int> cards){
    vector<int> tuquy;
    if (!cards.empty() && cards.size() >= 4){
        for (int i = 0; i < cards.size() - 3; i++){
            vector<int> temp;
            temp.push_back(cards[i]);
            for (int j = i + 1; j < cards.size(); j++){
                if (getCardValue(temp.back()) == getCardValue(cards[j])){
                    temp.push_back(cards[j]);
                }
            }
            if (temp.size() == 4){
                tuquy.insert(tuquy.end(), temp.begin(), temp.end());
            }
        }
    }
    return tuquy;
}

/*xem co gia tri value trong mang cards ko*/
bool CardHandler::contain(vector<int> cards, int value){
    if (find(cards.begin(), cards.end(), value) != cards.end()){
        return true;
    }

    return false;
}

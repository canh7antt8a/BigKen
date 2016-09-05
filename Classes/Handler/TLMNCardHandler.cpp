#include "TLMNCardHandler.h"
#include "Utils/TLMNConfig.hpp"
#include <algorithm>

TLMNCardHandler::TLMNCardHandler(){

}

TLMNCardHandler::~TLMNCardHandler(){

}

vector<int> TLMNCardHandler::find3DoiThong(vector<int> suggessCard, int cardValue){
    vector<int> lstResultSuggess;
    int start = 0;

    for (int i = 5; i < suggessCard.size(); i++){
        int valueTmp = -1;
        vector<int> tmp;

        for (int j = start; j < i; j++){
            for (int k = j + 1; k <= i; k++){
                if (getCardValue(suggessCard[j]) != CardValue::TWO
                    && getCardValue(suggessCard[j]) == getCardValue(suggessCard[k])
                    && (valueTmp < 0 || getCardValue(suggessCard[k]) == getCardValue(valueTmp) + 1)){
                    tmp.push_back(suggessCard[j]);
                    tmp.push_back(suggessCard[k]);
                    valueTmp = suggessCard[k];

                    if (tmp.size() == 6){

                        if (!contain(tmp, cardValue)){
                            for (int z = tmp.size() - 1; z >= 0; z--){
                                if (getCardValue(tmp[z]) == getCardValue(cardValue)){
                                    tmp[z] = cardValue;
                                    lstResultSuggess = tmp;
                                    return lstResultSuggess;
                                }
                            }

                            start++;
                        }
                        else {
                            lstResultSuggess = tmp;
                            return lstResultSuggess;
                        }
                    }
                }
            }
        }
    }

    return lstResultSuggess;
}

/*lay ra 1 card goi y*/
vector<int> TLMNCardHandler::getSuggessCardSingle(vector<int> cards, vector<int> lastCard, int cardValue){
    vector<int> suggessCard;
    
    if (cardValue > lastCard.back()){
        for (int card : cards)
        {
            if (card == cardValue){
                suggessCard.push_back(card);
                break;
            }
        }
    }
    else {
        //neu la quan 2 thi tim them tu quy va bo day thong vao suggess
        if (isHavingTwoCard(lastCard)){
            //tim tu quy
            for (int i = 0; i < cards.size(); i++){
                if (getCardValue(cards[i]) == getCardValue(cardValue)){
                    suggessCard.push_back(cards[i]);
                }
            }

            if (suggessCard.size() != 4){
                //neu khong co tu quy thi tim 3 doi thong
                suggessCard.clear();
                suggessCard = find4DoiThong(cards, cardValue);
                if (suggessCard.empty()){
                    suggessCard = find3DoiThong(cards, cardValue);
                }
            }
        }
    }

    return suggessCard;
}

/*kiem tra xem card co phai la day lien tiep khong*/
bool TLMNCardHandler::isSerialCards(vector<int> cards){
    /*check xem co 2 khong, neu co thi khong phai day serial*/
    if (isHavingTwoCard(cards)){
        return false;
    }
    /*check xem co phai day serial khong*/
    for (int i = 0; i < cards.size() - 1;i++)
    {
        if (getCardValue(cards[i]) + 1 != getCardValue(cards[i + 1])){
            return false;
        }
    }
    return true;
}

/*kiem tra xem card co phai la day serial couple khong*/
bool TLMNCardHandler::isSerialCouple(vector<int> cards){
    if (cards.size() < 6 || (cards.size() % 2) != 0) {
        return false;
    }
    
    /*check xem co 2 khong, neu co thi khong phai day serial*/
    if (isHavingTwoCard(cards)){
        return false;
    }

    /*check xem co phai day serial couple khong*/
    int value = 0;
    for (int i = 0; i < cards.size() - 3; i += 2) {
        value = getCardValue(cards[i+1]);
        if (!(getCardValue(cards[i]) == value
            && (value + 1 == getCardValue(cards[i + 2])))) {
            return false;
        }
    }
    if (getCardValue(cards.back()) == getCardValue(cards[cards.size() - 2])) {
        return true;
    }
    return false;
}

bool TLMNCardHandler::isCardCouple(vector<int> cards){
    int firtCard = cards.front();
    for (int card : cards)
    {
        if (card != firtCard){
            return false;
        }
    }
    return true;
}

/*lay ra day card serial goi y*/
//vector<int> TLMNCardHandler::findSuggessCardSerial(vector<int> cards, vector<int> lastCard){
//    vector<int> suggessCard;
//    int lengLastCard = lastCard.size();
//    int lastValueCard = lastCard.back();
//    if (cards.size() >= 3){
//        int sub = 0;
//        int card_size = cards.size();
//
//        for (int i = 1; i < card_size; i++){
//            if (getCardValue(cards[i]) != CardValue::TWO && cards[i] > lastValueCard){
//                vector<int> temp;
//                temp.push_back(cards[i]);
//                sub = lengLastCard - 1;
//
//                for (int k = 0; k < i; k++){
//                    if (getCardValue(cards[k]) == getCardValue(temp.front()) - sub){
//                        temp.push_back(cards[k]);
//                        sub -= 1;
//                        if (temp.size() == lengLastCard){
//                            suggessCard = temp;
//                            return suggessCard;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return suggessCard;
//}
//
///*lay ra day card serial couple goi y*/
//vector<int> TLMNCardHandler::findSuggessCardSerialCouple(vector<int> cards, vector<int> lastCard){
//    vector<int> suggessCard;
//    int lengLastCard = lastCard.size();
//    int lastValueCard = lastCard.back();
//    if (cards.size() >= 6){
//        int value;
//        for (int i = 1; i < cards.size(); i++){
//            if (getCardValue(cards[i]) != CardValue::TWO && cards[i] > lastValueCard){
//                vector<int> temp;
//                value = -1;
//                for (int j = i; j >= 1; j--){
//                    for (int k = j - 1; k >= 0; k--){
//                        if (getCardValue(cards[j]) == getCardValue(cards[k])
//                            && (value < 0 || getCardValue(cards[k]) == getCardValue(value) - 1)){
//                            temp.push_back(cards[j]);
//                            temp.push_back(cards[k]);
//                            value = cards[k];
//                        }
//                        if (temp.size() == lengLastCard){
//                            suggessCard = temp;
//                            return suggessCard;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    
//    return suggessCard;
//}
//
///*lay ra day card couple goi y*/
//vector<int> TLMNCardHandler::findSuggessCardCouple(vector<int> cards, vector<int> lastCard){
//    vector<int> suggessCard;
//    int lengLastCard = lastCard.size();
//    int lastValueCard = lastCard.back();
//    if (cards.size() >= 2){
//        for (int i = 0; i < cards.size(); i++)
//        {
//            if (cards[i] > lastValueCard && i != 0){
//                vector<int> temp;
//                temp.push_back(cards[i]);
//                for (int j = 0; j <= i - 1; j++)
//                {
//                    if (getCardValue(cards[j]) == getCardValue(cards[i])){
//                        temp.push_back(cards[j]);
//                    }
//                    if (temp.size() == lengLastCard){
//                        suggessCard = temp;
//                        return suggessCard;
//                    }
//                }
//
//            }
//        }
//    }
//    return suggessCard;
//}

/*lay ra quan bai goi y can danh*/
//vector<int> TLMNCardHandler::getSuggessCard(vector<int> cards, vector<int> lastCard){
//    vector<int> suggessCard;
//    //sap xep day bai truoc khi xu li
//    std::sort(cards.begin(), cards.end());
//    std::sort(lastCard.begin(), lastCard.end());
//
//    //xu li lay quan bai goi y danh
//    int typeLastCard = this->checkCardType(lastCard);
//    if (typeLastCard != CheckType::CARD_FAIL){
//        switch (typeLastCard)
//        {
//        case CheckType::CARD_SINGLE:
//            suggessCard = this->getSuggessCardSingle(cards, lastCard.back());
//            break;
//        case CheckType::CARD_SERIAL:
//            suggessCard = this->findSuggessCardSerial(cards, lastCard);
//            break;
//        case CheckType::CARD_SERIAL_COUPLE:
//            suggessCard = this->findSuggessCardSerialCouple(cards, lastCard);
//            break;
//        case CheckType::CARD_COUPLE:
//            suggessCard = this->findSuggessCardCouple(cards, lastCard);
//            break;
//        default:
//            break;
//        }
//    }
//    
//    return suggessCard;
//}

vector<int> TLMNCardHandler::findBoThong(vector<int> cards, int sizeRetunBoThong){
    vector<int> suggessCard;
    if (!cards.empty() && cards.size() >= 6){
        for (int i = cards.size() - 1; i >= 5; i--){
            int valueTmp = -1;
            vector<int> tmp;
            
            for (int j = i; j >= 1; j--){
                for (int k = j - 1; k >= 0; k--){
                    if (getCardValue(cards[j]) != CardValue::TWO
                        && getCardValue(cards[j]) == getCardValue(cards[k])
                        && (valueTmp < 0 || getCardValue(cards[k]) == getCardValue(valueTmp) - 1)){
                        tmp.push_back(cards[j]);
                        tmp.push_back(cards[k]);
                        valueTmp = cards[k];
                    }
                }
            }

            if (tmp.size() >= sizeRetunBoThong){
                for (int z = 0; z < tmp.size(); z++){
                    if (!contain(suggessCard, tmp[z])){
                        suggessCard.push_back(tmp[z]);
                    }
                }
            }
        }
    }

    return suggessCard;
}

vector<int> TLMNCardHandler::getAllSuggessCardSingle(vector<int> cards, int cardValue){
    vector<int> suggessCard;
    for (int card : cards)
    {
        if (card > cardValue){
            suggessCard.push_back(card);
        }
    }

    //neu la quan 2 thi tim them tu quy va bo doi thong vao suggess
    if (getCardValue(cardValue) == CardValue::TWO){
        vector<int> tuquy = findTuQuy(cards);

        if (tuquy.size() > 0){
            suggessCard.insert(suggessCard.end(), tuquy.begin(), tuquy.end());

            vector<int> bothong = findBoThong(cards, 6);
            if (bothong.size() > 0){
                int size_suggess = suggessCard.size();
                vector<int> tmpBoThong;
                for (int j = 0; j < bothong.size(); j++){
                    if (!contain(suggessCard, bothong[j])){
                        tmpBoThong.push_back(bothong[j]);
                    }
                }
                if (tmpBoThong.size() > 0){
                    suggessCard.insert(suggessCard.end(), tmpBoThong.begin(), tmpBoThong.end());
                }
            }
        }
        else {
            vector<int> bothong = findBoThong(cards, 6);
            if (bothong.size() > 0){
                suggessCard.insert(suggessCard.end(), bothong.begin(), bothong.end());
            }
        }
    }

    return suggessCard;
}

vector<int> TLMNCardHandler::findAllSuggessCardSerial(vector<int> cards, vector<int> lastCard){
    vector<int> suggessCard;
    int lengLastCard = lastCard.size();
    int lastValueCard = lastCard.back();
    if (cards.size() >= 3){
        int card_size = cards.size();

        for (int i = card_size - 1; i > 0; i--){
            if (getCardValue(cards[i]) != CardValue::TWO && cards[i] > lastValueCard){
                vector<int> temp;
                temp.push_back(cards[i]);

                for (int k = i - 1; k >= 0; k--){
                    if (getCardValue(cards[k]) == getCardValue(temp.back()) - 1){
                        temp.push_back(cards[k]);

                        if (temp.size() == lengLastCard){
                            for (int z = 0; z < temp.size(); z++){
                                if (!contain(suggessCard, temp[z])){
                                    suggessCard.push_back(temp[z]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        int suggessCardSize = suggessCard.size();
        for (int i = 0; i < suggessCardSize; i++){
            for (int j = 0; j < cards.size(); j++){
                if (suggessCard[i] != cards[j] && getCardValue(suggessCard[i]) == getCardValue(cards[j])
                    && !contain(suggessCard, cards[j])){
                    suggessCard.push_back(cards[j]);
                }
            }
        }
    }
    return suggessCard;
}

vector<int> TLMNCardHandler::findAllSuggessCardSerialCouple(vector<int> cards, vector<int> lastCard){
    vector<int> suggessCard;
    int lengLastCard = lastCard.size();
    int lastValueCard = lastCard.back();
    if (cards.size() >= 8 && lastCard.size() == 6){ //neu co 3 doi thong thi tim 4 doi thong de chat
        suggessCard = findBoThong(cards, 8);
    }
    if (suggessCard.empty()){ //neu khong tim thay 4 doi thong chat 3 doi thong thi tim cac kha nang khac
        int value;
        for (int i = cards.size() - 1; i >= 0; i--){
            if (getCardValue(cards[i]) != CardValue::TWO && cards[i] > lastValueCard){
                vector<int> temp;
                value = -1;
                for (int j = i; j >= 1; j--){
                    for (int k = j - 1; k >= 0; k--){
                        if (getCardValue(cards[j]) == getCardValue(cards[k])
                            && (value < 0 || getCardValue(cards[k]) == getCardValue(value) - 1)){
                            temp.push_back(cards[j]);
                            temp.push_back(cards[k]);
                            value = cards[k];

                            if (temp.size() == lengLastCard && temp.front() > lastValueCard){
                                for (int z = 0; z < temp.size(); z++){
                                    if (!contain(suggessCard, temp[z])){
                                        suggessCard.push_back(temp[z]);
                                    }
                                }
                                break;
                            }
                        }
                    }
                    if (temp.size() == lengLastCard){
                        break;
                    }
                }
            }
        }
    }
    
    int suggessCardSize = suggessCard.size();

    if (suggessCardSize > 0){
        //add them nhung quan bai cung do manh
        for (int i = 0; i < suggessCardSize; i++){
            for (int j = 0; j < cards.size(); j++){
                if (suggessCard[i] != cards[j] && getCardValue(suggessCard[i]) == getCardValue(cards[j])
                    && !contain(suggessCard, cards[j])){
                    suggessCard.push_back(cards[j]);
                }
            }
        }
    }
    else {
        if (lastCard.size() == 6){
            //neu khong tim duoc bo thong nao co kha nang danh dc thi tim tu quy chat 3 doi thong
            vector<int> tuquy = findTuQuy(cards);
            if (tuquy.size() > 0){
                suggessCard.insert(suggessCard.end(), tuquy.begin(), tuquy.end());
            }
        }
    }
    //}

    return suggessCard;
}

vector<int> TLMNCardHandler::findAllSuggessCardCouple(vector<int> cards, vector<int> lastCard){
    vector<int> suggessCard;
    if (cards.size() >= 2 && !lastCard.empty()){
        int lengLastCard = lastCard.size();
        int lastValueCard = lastCard.back();
        for (int i = cards.size() - 1; i >= 0; i--)
        {
            if (cards[i] > lastValueCard && i != 0){
                vector<int> temp;
                temp.push_back(cards[i]);
                for (int j = 0; j <= i - 1; j++)
                {
                    if (getCardValue(cards[j]) == getCardValue(cards[i])){
                        temp.push_back(cards[j]);

                        if (temp.size() == lengLastCard){
                            for (int z = 0; z < temp.size(); z++){
                                if (!contain(suggessCard, temp[z])){
                                    suggessCard.push_back(temp[z]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        //neu lastCard la doi 2 thi hien thi suggess them tu quy va 4 doi thong
        if (lastCard.size() == 2 && isHavingTwoCard(lastCard)){
            vector<int> tuquy = findTuQuy(cards);

            if (tuquy.size() > 0){
                suggessCard.insert(suggessCard.end(), tuquy.begin(), tuquy.end());

                vector<int> bothong = findBoThong(cards, 8);

                if (bothong.size() > 0){
                    int size_suggess = suggessCard.size();
                    vector<int> tmpBoThong;
                    for (int j = 0; j < bothong.size(); j++){
                        if (!contain(suggessCard, bothong[j])){
                            tmpBoThong.push_back(bothong[j]);
                        }
                    }
                    if (tmpBoThong.size() > 0){
                        suggessCard.insert(suggessCard.end(), tmpBoThong.begin(), tmpBoThong.end());
                    }
                }
            }
            else {
                vector<int> bothong = findBoThong(cards, 8);
                if (bothong.size() > 0){
                    suggessCard.insert(suggessCard.end(), bothong.begin(), bothong.end());
                }
            }
        }

        //truong hop chan tu quy => tim ra 4 doi thong chat tu
        if (lastCard.size() == 4){
            vector<int> bothong = findBoThong(cards, 8);
            if (bothong.size() > 0){
                suggessCard.insert(suggessCard.end(), bothong.begin(), bothong.end());
            }
        }

    }
    return suggessCard;
}

/*tim tat ca cac quan bai suggess*/
vector<int> TLMNCardHandler::getAllSuggessCard(vector<int> cards, vector<int> lastCard){
    vector<int> suggessCard;
    //sap xep day bai truoc khi xu li
    std::sort(cards.begin(), cards.end());
    std::sort(lastCard.begin(), lastCard.end());

    //xu li lay quan bai goi y danh
    int typeLastCard = this->checkCardType(lastCard);
    if (typeLastCard != CheckType::CARD_FAIL){
        switch (typeLastCard)
        {
        case CheckType::CARD_SINGLE:
            suggessCard = this->getAllSuggessCardSingle(cards, lastCard.back());
            break;
        case CheckType::CARD_SERIAL:
            suggessCard = this->findAllSuggessCardSerial(cards, lastCard);
            break;
        case CheckType::CARD_SERIAL_COUPLE:
            suggessCard = this->findAllSuggessCardSerialCouple(cards, lastCard);
            break;
        case CheckType::CARD_COUPLE:
            suggessCard = this->findAllSuggessCardCouple(cards, lastCard);
            break;
        default:
            break;
        }
    }

    return suggessCard;
}

vector<int> TLMNCardHandler::findSuggessCardSerialByTurn(vector<int> suggessCard, vector<int> lastCard, int value){
    vector<int> lstSuggessCard;
    int lengLastCard = lastCard.size();
    int lastValueCard = lastCard.back();
    if (suggessCard.size() >= 3){
        int sub = 0;
        int card_size = suggessCard.size();
        for (int i = 1; i < card_size; i++){
            if (getCardValue(suggessCard[i]) != CardValue::TWO && suggessCard[i] > lastValueCard){
                vector<int> temp;
                temp.push_back(suggessCard[i]);
                sub = lengLastCard - 1;
                for (int k = 0; k < i; k++){
                    if (getCardValue(suggessCard[k]) == getCardValue(temp.front()) - sub){
                        temp.push_back(suggessCard[k]);
                        sub -= 1;
                        if (temp.size() == lengLastCard){
                            for (int z = 0; z < temp.size(); z++){
                                if (getCardValue(temp[z]) == getCardValue(value)){
                                    temp[z] = value;
                                    lstSuggessCard = temp;
                                    return lstSuggessCard;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return lstSuggessCard;
}

vector<int> TLMNCardHandler::findSuggessCardSerialCoupleByTurn(vector<int> suggessCard, vector<int> lastCard, int valueTurn){
    vector<int> lstSuggessCard;
    int lengLastCard = lastCard.size();
    int lastValueCard = lastCard.back();
    if (suggessCard.size() >= 6){
        //tim xem cay turn co tu quy khong
        if (lastCard.size() == 6){
            //neu khong co doi thong de chan thi tim tu quy chan 3 doi thong
            for (int i = 0; i < suggessCard.size(); i++){
                if (getCardValue(suggessCard[i]) == getCardValue(valueTurn)){
                    lstSuggessCard.push_back(suggessCard[i]);
                }
            }
        }

        if (!lstSuggessCard.empty() && lstSuggessCard.size() == 4){
            return lstSuggessCard;
        }
        else {
            //tim 4 doi thong truoc
            lstSuggessCard = find4DoiThong(suggessCard, valueTurn);
        }
        
        if (!lstSuggessCard.empty()){
            return lstSuggessCard;
        }
        else {
            int value;
            int start = 0;

            for (int i = 1; i < suggessCard.size(); i++){
                if (getCardValue(suggessCard[i]) != CardValue::TWO && suggessCard[i] > lastValueCard){
                    vector<int> temp;
                    value = -1;
                    for (int j = start; j < i; j++){
                        for (int k = j + 1; k <= i; k++){
                            if (getCardValue(suggessCard[j]) == getCardValue(suggessCard[k])
                                && (value < 0 || getCardValue(suggessCard[k]) == getCardValue(value) + 1)){
                                temp.push_back(suggessCard[j]);
                                temp.push_back(suggessCard[k]);
                                value = suggessCard[k];

                                if (temp.size() == lengLastCard && temp.back() > lastValueCard){
                                    if (!contain(temp, valueTurn)){
                                        for (int z = temp.size() - 1; z >= 0; z--){
                                            if (getCardValue(temp[z]) == getCardValue(valueTurn)){
                                                temp[z] = valueTurn;
                                                lstSuggessCard = temp;
                                                return lstSuggessCard;
                                            }
                                        }

                                        start++;
                                    }
                                    else {
                                        lstSuggessCard = temp;
                                        return lstSuggessCard;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

  //  if (lastCard.size() == 6){
  //      //neu khong co doi thong de chan thi tim tu quy chan 3 doi thong
  //      for (int i = 0; i < suggessCard.size(); i++){
  //          if (getCardValue(suggessCard[i]) == getCardValue(valueTurn)){
  //              lstSuggessCard.push_back(suggessCard[i]);
  //          }
  //      }

        //if (lstSuggessCard.size() != 4){
        //  lstSuggessCard.clear();
        //}
  //  }

    return lstSuggessCard;
}

vector<int> TLMNCardHandler::findSuggessCardCoupleByTurn(vector<int> suggessCard, vector<int> lastCard, int value){
    vector<int> lstSuggessCard;
    if (!suggessCard.empty() && suggessCard.size() >= 2){
        if (lastCard.size() == 2 && isHavingTwoCard(lastCard) && getCardValue(suggessCard.back()) < CardValue::TWO){
            //neu co doi 2 thi tim tu quy va 4 doi thong
            for (int i = 0; i < suggessCard.size(); i++){
                if (getCardValue(suggessCard[i]) == getCardValue(value)){
                    lstSuggessCard.push_back(suggessCard[i]);
                }
            }

            if (lstSuggessCard.size() != 4){
                //neu khong co tu quy thi tim 4 doi thong
                lstSuggessCard = find4DoiThong(suggessCard, value);
            }
        }
        else {
            if (lastCard.size() == 4){ //neu co tu quy
                for (int i = 0; i < suggessCard.size(); i++){
                    if (getCardValue(suggessCard[i]) == getCardValue(value)){
                        lstSuggessCard.push_back(suggessCard[i]);
                    }
                }

                if (lstSuggessCard.size() != 4){  //neu khong co tu quy lon hon thi tim bon doi thong
                    lstSuggessCard = find4DoiThong(suggessCard, value);
                }
            }
            else {
                int lastCardSize = lastCard.size();
                vector<int> tmp;
                for (int i = 0; i < suggessCard.size(); i++){
                    if (getCardValue(suggessCard[i]) == getCardValue(value)){
                        tmp.push_back(suggessCard[i]);

                        if (tmp.size() == lastCardSize){
                            if (!contain(tmp, value)){
                                for (int z = tmp.size() - 1; z >= 0; z--){
                                    if (getCardValue(tmp[z]) == getCardValue(value)){
                                        tmp[z] = value;
                                        break;
                                    }
                                }
                            }
                            lstSuggessCard = tmp;
                            break;
                        }
                    }
                }
            }
        }
    }
    return lstSuggessCard;
}

/*ham tim 4 doi thong trong tat ca cac quan bai suggess : value(quan bai duoc click vao)*/
vector<int> TLMNCardHandler::find4DoiThong(vector<int> suggessCard, int value){
    vector<int> lstSuggessCard;
    int start = 0;

    for (int i = 7; i < suggessCard.size(); i++){
        int valueTmp = -1;
        vector<int> tmp;

        for (int j = start; j < i; j++){
            for (int k = j + 1; k <= i; k++){
                if (getCardValue(suggessCard[j]) != CardValue::TWO
                    && getCardValue(suggessCard[j]) == getCardValue(suggessCard[k])
                    && (valueTmp < 0 || getCardValue(suggessCard[k]) == getCardValue(valueTmp) + 1)){
                    tmp.push_back(suggessCard[j]);
                    tmp.push_back(suggessCard[k]);
                    valueTmp = suggessCard[k];

                    if (tmp.size() == 8){
                        if (!contain(tmp, value)){
                            for (int z = tmp.size() - 1; z >= 0; z--){
                                if (getCardValue(tmp[z]) == getCardValue(value)){
                                    tmp[z] = value;
                                    lstSuggessCard = tmp;
                                    return lstSuggessCard;
                                }
                            }

                            start++;
                        }
                        else {
                            lstSuggessCard = tmp;
                            return lstSuggessCard;
                        }
                    }
                }
            }
        }
    }

    return lstSuggessCard;
}

vector<int> TLMNCardHandler::findSuggessCardByTurn(vector<int> suggessCard, vector<int> lastCard, int value){
    vector<int> suggessCardByTurn;

    if (!suggessCard.empty()){
        std::sort(suggessCard.begin(), suggessCard.end());
        
        int typeLastCard = this->checkCardType(lastCard);
        if (typeLastCard != CheckType::CARD_FAIL){
            switch (typeLastCard){
            case CheckType::CARD_SINGLE:
                suggessCardByTurn = this->getSuggessCardSingle(suggessCard, lastCard, value);
                break;
            case CheckType::CARD_SERIAL:
                suggessCardByTurn = this->findSuggessCardSerialByTurn(suggessCard, lastCard, value);
                break;
            case CheckType::CARD_SERIAL_COUPLE:
                suggessCardByTurn = this->findSuggessCardSerialCoupleByTurn(suggessCard, lastCard, value);
                break;
            case CheckType::CARD_COUPLE:
                suggessCardByTurn = this->findSuggessCardCoupleByTurn(suggessCard, lastCard, value);
                break;
            default:
                break;
            }
        }
        
    }
    
    return suggessCardByTurn;
}

/* Singleton pattern */
TLMNCardHandler* TLMNCardHandler::instance = nullptr;
TLMNCardHandler* TLMNCardHandler::getInstance() {
    if (!instance) {
        instance = new TLMNCardHandler();
    }
    return instance;
}


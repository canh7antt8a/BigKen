#include "MauBinhCardHandler.h"
#include "Utils/TLMNConfig.hpp"
#include "cocos2d.h"
#include "Utils/Common.h"
#include <algorithm>

using namespace cocos2d;
using namespace std;

MauBinhCardHandler::MauBinhCardHandler(){
}

MauBinhCardHandler::~MauBinhCardHandler(){
}

const std::string MauBinhCardHandler::FIRST_BRANCH = "firstBranch";
const std::string MauBinhCardHandler::CENTER_BRANCH = "centerBranch";
const std::string MauBinhCardHandler::LAST_BRANCH = "lastBranch";
const std::string MauBinhCardHandler::THREE_BRANCH = "threeBranch";

/*lay gia tri goc cua quan bai*/
int MauBinhCardHandler::getCardValue(int card) {
    return (card - 1) / 4 + 2;  
}
/*lay chat cua quan bai*/
int MauBinhCardHandler::getCardType(int card) {
    return (card - 1) % 4; 
}

bool MauBinhCardHandler::isGreaterThan(vector<int> left_cards, vector<int> right_cards){
    pair<int, vector<vector<int>>> first_cards = getValue(left_cards);
    pair<int, vector<vector<int>>> second_cards = getValue(right_cards);
    if (first_cards.first > second_cards.first)
        return true;
    if (first_cards.first < second_cards.first)
        return false;

    bool isBlack = false;
    int rank = first_cards.first;
    switch (rank) {
    case MauBinhCardHandler::THUNG_PHA_SANH:
    {
        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[1]) <
            MauBinhCardHandler::getInstance()->getCardValue(current_cards[1])) {
            isBlack = true;
        }
    }
        break;
    case MauBinhCardHandler::TU_QUY:
    {
        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
            MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
            isBlack = true;
        }
    }
        break;
    case MauBinhCardHandler::CU_LU:
    {

        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
            MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
            isBlack = true;
        }
    }
        break;
    case MauBinhCardHandler::THUNG:
    {
        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        for (int i = 0; i < prev_cards.size(); i++) {
            if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[i])
                < MauBinhCardHandler::getInstance()->getCardValue(current_cards[i])) {
                isBlack = true;
                break;
            }

            if (MauBinhCardHandler::getInstance()->getCardValue(left_cards[i])
                > MauBinhCardHandler::getInstance()->getCardValue(right_cards[i])) {
                break;
            }
        }
    }
        break;
    case MauBinhCardHandler::SANH:
    {
        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[1]) <
            MauBinhCardHandler::getInstance()->getCardValue(current_cards[1])) {
            isBlack = true;
        }
    }
        break;
    case MauBinhCardHandler::SAM_CO:
    {
        vector<int> prev_cards = first_cards.second[0];
        vector<int> current_cards = second_cards.second[0];
        if (MauBinhCardHandler::getInstance()->getCardValue(prev_cards[0]) <
            MauBinhCardHandler::getInstance()->getCardValue(current_cards[0])) {
            isBlack = true;
        }
    }
        break;
    case MauBinhCardHandler::THU:
    {
        for (int j = 0; j < second_cards.second.size(); j++) {
            vector<int> prev_card = first_cards.second[j];
            vector<int> current_card = second_cards.second[j];
            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                isBlack = true;
                break;
            }

            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                break;
            }
        }
    }
        break;
    case MauBinhCardHandler::DOI:
    {
        for (int j = 0; j < second_cards.second.size(); j++) {
            vector<int> prev_card = first_cards.second[j];
            vector<int> current_card = second_cards.second[j];
            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                isBlack = true;
                break;
            }

            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                break;
            }
        }
    }
        break;
    case MauBinhCardHandler::MAU_THAU:
    {
        for (int j = 0; j < second_cards.second.size(); j++) {
            vector<int> prev_card = first_cards.second[j];
            vector<int> current_card = second_cards.second[j];
            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                < MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                isBlack = true;
                break;
            }

            if (MauBinhCardHandler::getInstance()->getCardValue(prev_card[0])
                > MauBinhCardHandler::getInstance()->getCardValue(current_card[0])) {
                break;
            }
        }
    }
        break;
    default:
        break;
    }    
    return !isBlack;
}

/*sap xep bo bai dau tien*/
void MauBinhCardHandler::sortCard(vector<int> &card_values) {
    if (card_values.size() != 13) return;
    int x[5];
    int k = 5;
    for (int i = 0; i < k; i++)
        x[i] = i;
    int count = 0;
    int n;
    int i;
    vector<int> best_cards(card_values.begin(), card_values.begin() + k);
    do {
        vector<int> tmp_cards;
        for (int i = 0; i < k; i++)
            tmp_cards.push_back(card_values[x[i]]);
        if (isGreaterThan(tmp_cards, best_cards)) {
            best_cards = tmp_cards; 
        }

        i = k - 1;
        while (i >= 0 && x[i] == card_values.size() - k + i) i--;
        if (i >= 0) {
            x[i]++;
            for (int j = i + 1; j < 5; j++) x[j] = x[j - 1] + 1;
        }

    } while (i >= 0);
    count = 0;
    for (int j = 0; j < best_cards.size(); j++) {
        int k = -1;
        for (int i = count; i < card_values.size(); i++) {
            if (best_cards[j] == card_values[i]) {
                k = i; 
                break;
            }
        }
        if (k != -1)
            Common::getInstance()->swap(card_values[count++], card_values[k]);
    }
}

/*check 5 con lien tiep*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isStraight(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result; 
    int last_tmp = card_values[4]; 
    int tmp = card_values[0];
    bool isValid = true; 
    if (getCardValue(last_tmp) == 14) {
        //la con at
        //truong hop con dau la con 2 
        isValid = false;
        if (getCardValue(tmp) == 2) {
            isValid = (getCardValue(card_values[1]) == 3
                && getCardValue(card_values[2]) == 4
                && getCardValue(card_values[3]) == 5); 
        } //truong hop con dau la con 10
        else if (getCardValue(tmp) == 10) {
            isValid = (getCardValue(card_values[1]) == 11
                && getCardValue(card_values[2]) == 12
                && getCardValue(card_values[3]) == 13);
        }
    }
    else {
        //truong hop ko phai co con at
        for (int i = 1; i < card_values.size(); i++) {
            if (getCardValue(card_values[i]) != getCardValue(card_values[i - 1])
                + 1) {
                isValid = false; 
                break;
            }
        }

        //
    }

    if (isValid) {
        result.first = MauBinhCardHandler::SANH;
        vector<int> cards;
        for (int i = card_values.size() - 1; i >= 0; i--)
            cards.push_back(card_values[i]);
        result.second.push_back(cards);
    }
    return result;
}

/*check 5 quan dong chat*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isFlush(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result;
    int card_type = getCardType(card_values[0]);
    for (int i = 1; i < card_values.size(); i++)
    if (getCardType(card_values[i]) != card_type)
        return result;

    //5 quan dong chat
    result.first = MauBinhCardHandler::THUNG; 
    vector<int> cards; 
    for (int i = card_values.size() - 1; i >= 0; i--) {
        cards.push_back(card_values[i]);
    }
    result.second.push_back(cards);
    return result;
}

/*tu quy*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isFourOfAKind(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result; 
    if (getCardValue(card_values[0]) == getCardValue(card_values[3])) {
        result.first = MauBinhCardHandler::TU_QUY; 
        vector<int> four_card(card_values.begin(), card_values.begin() + 4);
        vector<int> single_card(card_values.end() - 1, card_values.end());
        result.second.push_back(four_card);
        result.second.push_back(single_card);
    }
    if (getCardValue(card_values[1]) == getCardValue(card_values[4])) {
        result.first = MauBinhCardHandler::TU_QUY;
        vector<int> four_card(card_values.begin() + 1, card_values.end());
        vector<int> single_card(card_values.begin(), card_values.begin() + 1);
        result.second.push_back(four_card);
        result.second.push_back(single_card);
    }
    return result;
}

/*xet mau binh*/
bool MauBinhCardHandler::isWildCards(vector<int> card_values) {
    if (card_values.size() != 13) return false;
    int card_value[15];
    int card_type[4];
    memset(card_value, 0, sizeof(card_value));
    memset(card_type, 0, sizeof(card_type));

    for (int i = 0; i < card_values.size(); i++) {
        card_value[getCardValue(card_values[i])]++;
        card_type[getCardType(card_values[i])]++;
    }

    //xet sanh rong cuon

    for (int i = 0; i < 4; i++)  {
        if (card_type[i] == 13)
            return true;
    }

    //xet sanh rong
    bool is_straight = true;
    for (int i = 2; i < 15; i++) {
        if (card_value[i] != 1) {
            is_straight = false;
            break;
        }
    }

    if (is_straight) return true;

    int count_two = 0;
    int count_three = 0;
    for (int i = 2; i < 15; i++) {
        if (card_value[i] == 4) {
            count_two += 2;
        }
        else if (card_value[i] == 3){
            count_three++; 
        }
        else if (card_value[i] == 2) {
            count_two++;
        }
    }
   
    if (count_two == 6 || (count_three == 1 && count_two == 5)) return true; 
    //xet 3 thung
    sort(card_type, card_type + 4);
    if (card_type[2] == 3 && card_type[3] == 10) return true; 
    if (card_type[2] == 5 && card_type[3] == 8) return true; 
    if (card_type[3] == 5 && card_type[2] == 5 && card_type[1] == 3) return true;
    //xet 3 sanh
    return false;
}

/*cu lu*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isFullHouse(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result;
    sort(card_values.begin(), card_values.end());
    int cardValue1 = getCardValue(card_values[0]);
    int cardValue2 = getCardValue(card_values[1]);
    int cardValue3 = getCardValue(card_values[2]);
    int cardValue4 = getCardValue(card_values[3]);
    int cardValue5 = getCardValue(card_values[4]);
    if (cardValue1 == cardValue3 && cardValue4 == cardValue5) {
        result.first = MauBinhCardHandler::CU_LU; 
        vector<int> pair_card(card_values.begin() + 3, card_values.end());
        vector<int> three_card(card_values.begin(), card_values.begin() + 3);
        result.second.push_back(three_card);
        result.second.push_back(pair_card);
    }
        
    if (cardValue1 == cardValue2 && cardValue3 == cardValue5) {
        result.first = MauBinhCardHandler::CU_LU; 
        vector<int> pair_card(card_values.begin(), card_values.begin() + 2);
        vector<int> three_card(card_values.begin() + 2, card_values.end());

        result.second.push_back(three_card);
        result.second.push_back(pair_card);
    }
        
    return result;
}

/*check thung pha sanh*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isStraightFlush(vector<int> card_values) {
    pair<int, vector<vector<int>>> result = make_pair(0, * new vector<vector<int>>());
    if (card_values.size() != 5) return result;
    pair<int, vector<vector<int>>> straight_card = isStraight(card_values);
    pair<int, vector<vector<int>>> flush_card = isFlush(card_values);
    ; 
    if ((straight_card.first == MauBinhCardHandler::SANH) && (flush_card.first == MauBinhCardHandler::THUNG)) {

        result.first = MauBinhCardHandler::THUNG_PHA_SANH;
        vector<int> cards; 

        for (int i = card_values.size() - 1; i >= 0; i--)
            cards.push_back(card_values[i]); 

        result.second.push_back(cards);
    }
    return result;
    //return (isStraight(card_values) && isFlush(card_values));
}

/*sam co*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isThreeOfAKind(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result; 

    sort(card_values.begin(), card_values.end());
    if (getCardValue(card_values[0]) == getCardValue(card_values[2])) {
        result.first = MauBinhCardHandler::SAM_CO; 
        //add bo 3
        vector<int> three_card(card_values.begin(), card_values.begin() + 3); 
        result.second.push_back(three_card);

        //add bo 1
        for (int i = 4; i >= 3; i--) {
            vector<int> single_card;
            single_card.push_back(card_values[i]);
            result.second.push_back(single_card);
        }
    };

    if (getCardValue(card_values[1]) == getCardValue(card_values[3])) {

        result.first = MauBinhCardHandler::SAM_CO;
        //add bo 3
        vector<int> three_card(card_values.begin() + 1, card_values.begin() + 4);
        result.second.push_back(three_card);

        //add bo 1
        vector<int> single_card;
        single_card.push_back(card_values[4]);
        result.second.push_back(single_card);
        single_card[0] = card_values[0];
        result.second.push_back(single_card);
        
    }
    if (getCardValue(card_values[2]) == getCardValue(card_values[4]))  {
        //add bo 3
        result.first = MauBinhCardHandler::SAM_CO; 
        vector<int> three_card(card_values.begin() + 2, card_values.end());
        result.second.push_back(three_card);
        //add quan don
        for (int i = 1; i >= 0; i--) {
            vector<int> single_card; 
            single_card.push_back(card_values[i]);
            result.second.push_back(single_card);
        }
    }
    return result;
}

/*thu*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isTwoPair(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result;
    sort(card_values.begin(), card_values.end());
    int card[15];
    memset(card, 0, sizeof(card));
    for (int i = 0; i < card_values.size(); i++)
        card[getCardValue(card_values[i])]++;
    int count_two = 0; 
    vector<int> value;
    for (int i = 0; i < 15; i++) {
        if (card[i] == 2) value.push_back(i);
    }
    if (value.size() == 2) {
        //add doi
        result.first = MauBinhCardHandler::THU; 
        for (int j = value.size() - 1; j >= 0; j--)  {
            vector<int> val; 
            for (int i = 0; i < card_values.size(); i++) {
                if (value[j] == getCardValue(card_values[i]))
                    val.push_back(card_values[i]);
            }
            result.second.push_back(val);
        }
        
        //add don
        for (int i = card_values.size() - 1; i >= 0; i--) {
            bool is_single = true;
            for (int j = 0; j < value.size(); j++) {
                if (value[j] == getCardValue(card_values[i])) {
                    is_single = false;
                    break;
                }
            }
            if (is_single) {
                vector<int> single_card; 
                single_card.push_back(card_values[i]);
                result.second.push_back(single_card);
            }    
        }
    }

    return result;
}

/*doi*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isOnePair(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());
    if (card_values.size() != 5) return result;
    int card[15];
    memset(card, 0, sizeof(card));
    for (int i = 0; i < card_values.size(); i++)
        card[getCardValue(card_values[i])]++;
    int count_two = 0;
    int k = -1;
    for (int i = 0; i < 15; i++) {
        if (card[i] == 2) {
            count_two++;
            k = i;
        }
    }

    if (count_two == 1) {
        result.first = MauBinhCardHandler::DOI; 
        //add doi

        vector<int> pair_card; 
        for (int i = 0; i < card_values.size(); i++)
            if (getCardValue(card_values[i]) == k) {
                pair_card.push_back(card_values[i]);
            }

        result.second.push_back(pair_card);

        //add don
        for (int i = card_values.size() - 1; i >= 0; i--) {
            if (getCardValue(card_values[i]) != k) {
                vector<int> single_card;
                single_card.push_back(card_values[i]);
                result.second.push_back(single_card);
            }
        }
    }


    return result;
}

/*mau thau*/
pair<int, vector<vector<int>>> MauBinhCardHandler::isHighCard(vector<int> card_values) {
    pair<int, vector<vector<int>>> result;
    result = make_pair(0, *new vector<vector<int>>());

    if (card_values.size() != 5) return result;
    int card[15];
    memset(card, 0, sizeof(card));
    for (int i = 0; i < card_values.size(); i++)
        card[getCardValue(card_values[i])]++;
    
    for (int i = 0; i < 15; i++) {
        if (card[i] > 1) return result;
    }

    result.first = MauBinhCardHandler::MAU_THAU; 
    
    for (int i = card_values.size() - 1; i >= 0; i--) {
        vector<int> value;
        value.push_back(card_values[i]);
        result.second.push_back(value);
    }
        
    return result; 
}

std::string MauBinhCardHandler::getTurnValue(int rank) {
    std::string result = "";
    switch (rank)
    {
    case MauBinhCardHandler::THUNG_PHA_SANH:
        result = "Thùng phá sảnh";
        break;
    case MauBinhCardHandler::TU_QUY: 
        result = "Tứ quý";
        break;
    case MauBinhCardHandler::CU_LU:
        result = "Cù lũ";
        break;
    case MauBinhCardHandler::THUNG:
        result = "Thùng";
        break;
    case MauBinhCardHandler::SANH:
        result = "Sảnh";
        break;
    case MauBinhCardHandler::SAM_CO:
        result = "Sám cô";
        break;
    case MauBinhCardHandler::THU:
        result = "Thú";
        break;
    case MauBinhCardHandler::DOI:
        result = "Đôi";
        break;
    case MauBinhCardHandler::MAU_THAU:
        result = "Mậu thầu";
        break;
    default:
        break;
    }
    return result; 
}


pair<int, vector<vector<int>>> MauBinhCardHandler::getValue(vector<int> card_values) {
    int size = card_values.size();
    sort(card_values.begin(), card_values.end());
    pair<int, vector<vector<int>>> result = make_pair(0, * new vector<vector<int>>());

    if (size == 3) {
        if (getCardValue(card_values[0]) == getCardValue(card_values[1])
            && getCardValue(card_values[1]) == getCardValue(card_values[2])) {
            result.first = MauBinhCardHandler::SAM_CO; 
            vector<int> cards; 
            for (int i = card_values.size() - 1; i >= 0; i--)
                cards.push_back(card_values[i]);
            result.second.push_back(cards);
            return result;
        }
            
        if (getCardValue(card_values[0]) == getCardValue(card_values[1])) {
            vector<int> pair_card(card_values.begin(), card_values.begin() + 2);
            vector<int> single_card(card_values.end() -1, card_values.end());
            result.first = MauBinhCardHandler::DOI; 
            result.second.push_back(pair_card);
            result.second.push_back(single_card);
            return result;
        }
        if( getCardValue(card_values[1]) == getCardValue(card_values[2])) {
            vector<int> pair_card(card_values.begin() + 1, card_values.end());
            vector<int> single_card(card_values.begin(), card_values.begin() + 1);
            result.first = MauBinhCardHandler::DOI;
            result.second.push_back(pair_card);
            result.second.push_back(single_card);
            return result;
        }
        
        //mau thau
        result.first = MauBinhCardHandler::MAU_THAU; 
        for (int i = card_values.size() - 1; i >= 0; i--) {
            vector<int> cards; 
            cards.push_back(card_values[i]);
            result.second.push_back(cards);
        }
        return result;
            
    }
    else if (size == 5) {
        //find thung pha sanh
        pair<int, vector<vector<int>>> result;
        result = isStraightFlush(card_values);

        if (result.first == MauBinhCardHandler::THUNG_PHA_SANH)
            return result;
        //find tu quy
        result = isFourOfAKind(card_values);
        if (result.first == MauBinhCardHandler::TU_QUY)
            return result;

        //find cu lu
        result = isFullHouse(card_values);
        if (result.first == MauBinhCardHandler::CU_LU)
            return result;

        //find thung
        result = isFlush(card_values);
        if (result.first == MauBinhCardHandler::THUNG)
            return result;

        //find sanh
        result = isStraight(card_values);
        if (result.first == MauBinhCardHandler::SANH)
            return result;
        //find sam co
        result = isThreeOfAKind(card_values);
        if (result.first == MauBinhCardHandler::SAM_CO)
            return result;
        //find thu
        result = isTwoPair(card_values);
        if (result.first == MauBinhCardHandler::THU) 
            return result;
            
        //find doi
        result = isOnePair(card_values);
        if (result.first == MauBinhCardHandler::DOI)
            return result;

        //find mau. thau`
        result = isHighCard(card_values);
        if (result.first == MauBinhCardHandler::MAU_THAU)
            return result;
    }
    return result;
}


int MauBinhCardHandler::getRank(vector<int> card_values) {
    int size = card_values.size(); 
    sort(card_values.begin(), card_values.end());
    if (size == 3) {
        if (getCardValue(card_values[0]) == getCardValue(card_values[1]) 
            && getCardValue(card_values[1]) == getCardValue(card_values[2])) 
            return MauBinhCardHandler::SAM_CO; 
        if (getCardValue(card_values[0]) == getCardValue(card_values[1]) 
            || getCardValue(card_values[1]) == getCardValue(card_values[2]))
            return MauBinhCardHandler::DOI; 
        return MauBinhCardHandler::MAU_THAU;
    }
    else if(size == 5) {
        //find thung pha sanh
        pair<int, vector<vector<int>>> result; 
        result = isStraightFlush(card_values);
        
        if (result.first == MauBinhCardHandler::THUNG_PHA_SANH)
            return MauBinhCardHandler::THUNG_PHA_SANH; 
        //find tu quy
        result = isFourOfAKind(card_values);
        if (result.first == MauBinhCardHandler::TU_QUY)        
            return MauBinhCardHandler::TU_QUY;

        //find cu lu
        result = isFullHouse(card_values);
        if (result.first == MauBinhCardHandler::CU_LU)
            return MauBinhCardHandler::CU_LU;

        //find thung
        result = isFlush(card_values);
        if (result.first == MauBinhCardHandler::THUNG)
            return MauBinhCardHandler::THUNG;
       
        //find sanh
        result = isStraight(card_values);
        if (result.first == MauBinhCardHandler::SANH)
            return MauBinhCardHandler::SANH;
        //find sam co
        result = isThreeOfAKind(card_values);
        if (result.first == MauBinhCardHandler::SAM_CO)
            return MauBinhCardHandler::SAM_CO; 
        //find thu
        result = isTwoPair(card_values);
        if (result.first == MauBinhCardHandler::THU)
            return MauBinhCardHandler::THU; 
        //find doi
        result = isOnePair(card_values);
        if (result.first == MauBinhCardHandler::DOI)
            return MauBinhCardHandler::DOI; 
        //find mau. thau`
        return MauBinhCardHandler::MAU_THAU; 
    } 
    return 0; 
}

MauBinhCardHandler* MauBinhCardHandler::_instance = 0;
MauBinhCardHandler* MauBinhCardHandler::getInstance() {
    if (!_instance) {
        _instance = new MauBinhCardHandler();
    }
    return _instance;
}

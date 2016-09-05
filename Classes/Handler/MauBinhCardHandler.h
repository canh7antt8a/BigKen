#ifndef MauBinhCardHandler_h
#define MauBinhCardHandler_h

#include "CardHandler.h"
#include <vector>
using namespace std;

class MauBinhCardHandler {
public:
    MauBinhCardHandler();
    ~MauBinhCardHandler();
    int getRank(vector<int> card_values);
    pair<int, vector<vector<int>>> getValue(vector<int> card_values);
    pair<int, vector<vector<int>>> isStraight(vector<int> card_values);
    int getCardValue(int card);
    int getCardType(int card);
    pair<int, vector<vector<int>>> isFlush(vector<int> card_values);
    pair<int, vector<vector<int>>> isStraightFlush(vector<int> card_values);
    pair<int, vector<vector<int>>> isFourOfAKind(vector<int> card_values);
    pair<int, vector<vector<int>>> isFullHouse(vector<int> card_values);
    pair<int, vector<vector<int>>> isThreeOfAKind(vector<int> card_values);
    pair<int, vector<vector<int>>> isTwoPair(vector<int> card_values);
    pair<int, vector<vector<int>>> isOnePair(vector<int> card_values);
    pair<int, vector<vector<int>>> isHighCard(vector<int> card_values);
    bool isGreaterThan(vector<int> left_cards, vector<int> right_cards);
    void sortCard(vector<int> &card_values);
    /*xet mau binh*/
    bool isWildCards(vector<int> card_values);

    std::string getTurnValue(int val);

    static MauBinhCardHandler* getInstance();

    const static int THUNG_PHA_SANH = 9;
    const static int TU_QUY = 8;
    const static int CU_LU = 7;
    const static int THUNG = 6;
    const static int SANH = 5;
    const static int SAM_CO = 4;
    const static int THU = 3;
    const static int DOI = 2;
    const static int MAU_THAU = 1;
    const static std::string FIRST_BRANCH;
    const static std::string CENTER_BRANCH;
    const static std::string LAST_BRANCH;
    const static std::string THREE_BRANCH;
private:
    static MauBinhCardHandler* _instance; 
};

#endif
#ifndef CardHandler_h
#define CardHandler_h

#include <vector>
#include <algorithm>
using namespace std;

class CardHandler {
    
public:
    CardHandler();
    ~CardHandler();
public :
    /*lay ra quan bai goi y can danh*/
    virtual vector<int> getAllSuggessCard(vector<int> cards, vector<int> lastCard) = 0;
    /*kiem tra loai card la card don, bo doi, ba, bon hay la day lien tiep*/
    virtual int checkCardType(vector<int> cards);

    /*kiem tra xem card co phai la day lien tiep khong*/
    virtual bool isSerialCards(vector<int> cards) = 0;
    /*kiem tra xem card co phai la day serial couple khong*/
    virtual bool isSerialCouple(vector<int> cards) = 0;
    /*kiem tra xem co phai card couple ko*/
    virtual bool isCardCouple(vector<int> cards) = 0;
    /*lay ra gia tri goc cua quan bai*/
    static int getCardValue(int card);
    /*lay ra chat cua quan bai*/
    static int getCardType(int card);
    /*xem bai co quan hai khong*/
    bool isHavingTwoCard(vector<int> cards);
    /*tim tu quy trong 1 day bai*/
    virtual vector<int> findTuQuy(vector<int> cards);
    /*gia tri chua trong list ko*/
    bool contain(vector<int> cards, int value);
};

#endif
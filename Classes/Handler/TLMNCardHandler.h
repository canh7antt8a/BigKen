#ifndef TLMNCardHandler_h
#define TLMNCardHandler_h

#include "CardHandler.h"
#include <vector>
using namespace std;

class TLMNCardHandler : public CardHandler {
public:
    TLMNCardHandler();
    ~TLMNCardHandler();
public :
    /*lay ra quan bai goi y can danh*/
    //vector<int> getSuggessCard(vector<int> cards, vector<int> lastCard);
    /*lay ra 1 card goi y*/
    vector<int> getSuggessCardSingle(vector<int> cards, vector<int> lastCard, int cardValue);
    /*lay ra day serial goi y*/
    //vector<int> findSuggessCardSerial(vector<int> cards, vector<int> lastCard);
    /*lay ra day serial couple goi y*/
    //vector<int> findSuggessCardSerialCouple(vector<int> cards, vector<int> lastCard);
    /*lay ra day couple goi y*/
    //vector<int> findSuggessCardCouple(vector<int> cards, vector<int> lastCard);
    /*kiem tra xem 1 day co phai serial khong*/
    bool isSerialCards(vector<int> cards);
    /*kiem tra xem card co phai la day serial couple khong*/
    bool isSerialCouple(vector<int> cards);
    /*kiem tra xem co phai card couple ko*/
    bool isCardCouple(vector<int> cards);
    /*tim tat ca cac quan bai suggess*/
    vector<int> getAllSuggessCard(vector<int> cards, vector<int> lastCard);

    vector<int> getAllSuggessCardSingle(vector<int> cards, int cardValue);
    vector<int> findAllSuggessCardSerial(vector<int> cards, vector<int> lastCard);
    vector<int> findAllSuggessCardSerialCouple(vector<int> cards, vector<int> lastCard);
    vector<int> findAllSuggessCardCouple(vector<int> cards, vector<int> lastCard);
    
    /*tim suggesscard dua vao quan bai turn*/
    vector<int> findSuggessCardByTurn(vector<int> suggessCard, vector<int> lastCard, int value);
    vector<int> findSuggessCardSerialByTurn(vector<int> suggessCard, vector<int> lastCard, int value);
    vector<int> findSuggessCardSerialCoupleByTurn(vector<int> suggessCard, vector<int> lastCard, int value);
    vector<int> findSuggessCardCoupleByTurn(vector<int> suggessCard, vector<int> lastCard, int value);

    /*tim bo thong trong 1 day bai, sizeRetunBoThong(size bo thong tra ve = 6 la 3 doi thong, 8 la 4 doi thong)*/
    vector<int> findBoThong(vector<int> cards, int sizeRetunBoThong);

    /*ham tim 4 doi thong trong tat ca cac quan bai suggess : value(quan bai duoc click vao)*/
    vector<int> find4DoiThong(vector<int> suggessCard, int value);

    /*ham tim 3 doi thong trong tat ca cac quan bai suggess : value(quan bai duoc click vao)*/
    vector<int> find3DoiThong(vector<int> suggessCard, int cardValue);

    static TLMNCardHandler* getInstance();

private:
    static TLMNCardHandler* instance;
    
};

#endif
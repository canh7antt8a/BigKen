#ifndef PhomHandler_h
#define PhomHandler_h

#include "CardHandler.h"
#include <vector>
#include <tuple>

using namespace std;

class PhomHandler : public CardHandler {
public:
    PhomHandler();
    ~PhomHandler();
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

    int isNotSuggestOrValidCard(int cardValue, vector<int> cards, vector<int> eatenCards);

    int findCardIndex(int cardValue, vector<int> cards);

    vector<int> isHavingAKind(int cardValue, vector<int> cards);

    vector<int> isHavingStraightFlush(int cardValue, vector<int> cards);
    
    //Sắp xếp bài
    /*
        tìm tất cả các phỏm ngang trong vector cards
        phần tử thứ nhất của tuple: tất cả các phỏm
        phần tử thứ hai của tuple: các quân bài không thuộc phỏm nào
     */
    tuple<vector<vector<int>>, vector<int>> timPhomNgang(vector<int> cards);
    
    /*
        tìm tất cả các phỏm dọc trong vector cards
        phần tử thứ nhất của tuple: tất cả các phỏm
        phần tử thứ hai của tuple: các quân bài không thuộc phỏm nào
     */
    tuple<vector<vector<int>>, vector<int>> timPhomDoc(vector<int> cards);
    
    /*
        tìm tất cả các cặp trong vector cards
        phần tử thứ nhất của tuple: tất cả các cặp
        phần tử thứ 2: các quân bài không thuộc cặp nào
     */
    tuple<vector<vector<int>>, vector<int>> timCapNgang(vector<int> cards);
    
    /*
        tìm tất cả các cặp trong vector cards
        phần tử thứ nhất của tuple: tất cả các cặp
        phần tử thứ 2: các quân bài không thuộc cặp nào
     */
    tuple<vector<vector<int>>, vector<int>> timCapDoc(vector<int> cards);

    static PhomHandler* getInstance();

private:
    static PhomHandler* instance;
    const static int NOT_VALID = -1; 
    const static int NOT_SUGGEST = 0; 
    const static int CAN_BE_THROW = 1;
};

#endif
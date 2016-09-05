//
//  Card.hpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#ifndef Card_hpp
#define Card_hpp

#include <string>

using namespace std;

class Card
{
public:
    Card(const int = 0);
    ~Card();
    string name() const;
    string getPhomName() const;
    string getThreeCardName() const; 
    string getMauBinhName() const;
    string getActualName();
    int getValue() const; 
    void setValue(int value); 
    int value;

private: 
    
};

#endif /* Card_hpp */

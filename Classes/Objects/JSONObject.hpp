//
//  JSONObject.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 7/14/16.
//
//

#ifndef JSONObject_hpp
#define JSONObject_hpp

#include <string>
#include <stdio.h>

using namespace std;
class JSONObject {
public:
    JSONObject(string key, string value);
    
    string getKey() const;
    void setKey(string newKey);
    
    string getValue() const;
    void setValue(string newNalue);
private:
    string _key;
    string _value;
};

#endif /* JSONObject_hpp */

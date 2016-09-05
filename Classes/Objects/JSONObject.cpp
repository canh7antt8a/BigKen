//
//  JSONObject.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 7/14/16.
//
//

#include "JSONObject.hpp"

JSONObject::JSONObject(string key, string value) {
    _key = key;
    _value = value;
}

string JSONObject::getKey() const {
    return _key;
}

void JSONObject::setKey(string newKey) {
    _key = newKey;
}

string JSONObject::getValue() const {
    return _value;
}

void JSONObject::setValue(string newNalue) {
    _value = newNalue;
}

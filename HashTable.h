#pragma once

#include "DLList.h"
#include "String.h"

template<typename T_key, typename T_val>
struct Element {
    T_key key;
    T_val value;
};


template<typename T_key, typename T_val>
class HashTable {
public:
    HashTable();

    void insert(const T_key& key, const T_val& val);
    int hashFunction(const String &key);
private:
    static const int ARR_SIZE = 1000;
    DLList<Element<T_key, T_val>> arr[ARR_SIZE];
    int occupied_lists;

    int hashFunction(int key);
};

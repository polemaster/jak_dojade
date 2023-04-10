#pragma once

#include "DLList.h"
#include "String.h"


template<typename T_key, typename T_val>
class HashTable {
public:
    HashTable();

    void insert(T_key&& key, T_val&& val); // assumption: each key is different
    int hashFunction(const String &key);
    void print() const;
private:
    struct Element {
        T_key key;
        T_val value;

        bool operator==(const Element& other) const {
            return key == other.key;
        }
    };
    friend std::ostream& operator<<(std::ostream& os, const Element& el) {
        os << el.key << ": " << el.value;
        return os;
    }

    static const int ARR_SIZE = 1000;
    DLList<Element> arr[ARR_SIZE];
    int occupied_lists;

    int hashFunction(int key);
};


// bool operator==(const HashTable<T_key, T_val>::Element& left, const HashTable<T_key, T_val>::Element& right);

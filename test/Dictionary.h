#pragma once

// #include <random>
#include "Pair.h"
#include "DLList.h"
#include "String.h"

const int MAX_INT_KEY = 2147483647;

template<typename T_key, typename T_val>
class Dictionary {
public:
    Dictionary();

    void insert(T_key&& key, T_val&& val); // assumption: each key is different
    void insert(T_key&& key, const T_val& val);
    void insert(const T_key& key, T_val&& val);
    void insert(const T_key& key, const T_val& val);
    void insertKey(const T_key& key);
    // the same as insert but if the item already is in the list, then update it
    void update(const T_key& key, T_val&& val);
    void print() const;
    const T_val& at(const T_key& key) const; // change to const?
    int getNumOfOccupiedLists() const; // O(ARR_SIZE) complexity
    int count(const T_key& key) const;
    T_val& operator[](const T_key& key);
    // const T_val& operator[](const T_key& key) const;
    // DLList<Pair<T_key, T_val>>& operator[](const T_key& key);

    // struct Element {
    //     T_key key;
    //     T_val value;

    //     bool operator==(const Element& other) const {
    //         return key == other.key;
    //     }
    // };
    // friend std::ostream& operator<<(std::ostream& os, const Element& el) {
    //     os << el.key << ": " << el.value;
    //     return os;
    // }
private:

    static const int ARR_SIZE = 25000;
    DLList<Pair<T_key, T_val>> _arr[ARR_SIZE];
    int _a, _b;

    int _hashFunction(const int key) const;
    int _hashFunction(const String &key) const;
};

template<typename T_key, typename T_val>
Dictionary<T_key, T_val>::Dictionary() {
    // std::random_device rd;
    // std::mt19937 rng(rd());
    // std::uniform_int_distribution<std::mt19937::result_type> dis(1, MAX_INT_KEY - 1);
    // _a = dis(rng);
    // _b = dis(rng);
    _a = rand() % (MAX_INT_KEY - 2) + 1;
    _b = rand() % (MAX_INT_KEY - 2) + 1;


    // std::cout << "randomized: " << _a << " " << _b << std::endl;
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::insert(T_key&& key, T_val&& val) {
    int index = _hashFunction(key);
    Pair<T_key, T_val> tmp_pair(std::move(key), std::move(val));
    _arr[index].push_back(std::move(tmp_pair));
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::insert(T_key&& key, const T_val& val) {
    int index = _hashFunction(key);
    Pair<T_key, T_val> tmp_pair(std::move(key), val);
    _arr[index].push_back(std::move(tmp_pair));
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::insert(const T_key& key, T_val&& val) {
    int index = _hashFunction(key);
    Pair<T_key, T_val> tmp_pair(key, std::move(val));
    _arr[index].push_back(std::move(tmp_pair));
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::insert(const T_key& key, const T_val& val) {
    int index = _hashFunction(key);
    Pair<T_key, T_val> tmp_pair(key, val);
    _arr[index].push_back(std::move(tmp_pair));
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::insertKey(const T_key& key) {
    int index = _hashFunction(key);
}

template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::update(const T_key& key, T_val&& val) {
    int index = _hashFunction(key);
    for (auto it = _arr[index].begin(); it != _arr[index].end(); ++it) {
        if ((*it).first == key) {
            (*it).second = std::move(val);
            return;
        }
    }
    Pair<T_key, T_val> tmp_pair(key, val);
    _arr[index].push_back(std::move(tmp_pair));
}

// template<typename T_key, typename T_val>
// // maybe change Element to seperate class?
// DLList<Pair<T_key, T_val>& Dictionary<T_key, T_val>::operator[](const T_key& key) {
//     int index = _hashFunction(key);
//     return _arr[index];
// }


// template<typename T_key, typename T_val>
// DLList<Pair<T_key, T_val>>& Dictionary<T_key, T_val>::operator[](const T_key& key) {
//     int index = _hashFunction(key);
//     return _arr[index];
// }

template<typename T_key, typename T_val>
T_val& Dictionary<T_key, T_val>::operator[](const T_key& key) {
    int index = _hashFunction(key);
    // std::cout << "key: " << key << ", " << index << std::endl;
    DLList<Pair<T_key, T_val>>& tmp_list = _arr[index];
    // if (tmp_list.size() == 0) {
    //     insert(key, DLList<Pair<String,int>>());
    //     return tmp_list[0].second;
    // }
    // else {
    for (auto it = tmp_list.begin(); it != tmp_list.end(); ++it)
        if ((*it).first == key)
            return (*it).second;
    // }
    insert(key, DLList<Pair<String,int>>());
    // return tmp_list[0].second; // what if it is not 0???
    return tmp_list.top().second;
    // throw std::logic_error("key not found 2");
}



template<typename T_key, typename T_val>
int Dictionary<T_key, T_val>::_hashFunction(const String& key) const {
    unsigned long long hash_value = 0;
    for (std::size_t i = 0; i < key.size(); ++i) {
        hash_value = (hash_value * (unsigned long long)_a + key[i] * (unsigned long long)_b) % ARR_SIZE;
    }
    return hash_value;
}

template<typename T_key, typename T_val>
int Dictionary<T_key, T_val>::_hashFunction(const int key) const {

    unsigned long long result = ( ( (unsigned long long)_a * key + _b ) % MAX_INT_KEY ) % ARR_SIZE;
    return result;
}


template<typename T_key, typename T_val>
void Dictionary<T_key, T_val>::print() const {
    std::cout << "Printing Dictionary:" << std::endl;
    for (int i = 0; i < ARR_SIZE; ++i) {
        if (!_arr[i].empty()) {
            _arr[i].print();
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

template<typename T_key, typename T_val>
const T_val& Dictionary<T_key, T_val>::at(const T_key& key) const {
    int index = _hashFunction(key);
    const DLList<Pair<T_key, T_val>>& tmp_list = _arr[index];
    if (tmp_list.size() == 0)
        throw std::invalid_argument("this key doesn't exist");
    else {
        for (auto it = tmp_list.begin(); it != tmp_list.end(); ++it)
            if ((*it).first == key)
                return (*it).second;
    }
    throw std::logic_error("key not found");
}

template<typename T_key, typename T_val>
int Dictionary<T_key, T_val>::getNumOfOccupiedLists() const {
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        if (_arr[i].size())
            ++sum;
    }
    return sum;
}

template<typename T_key, typename T_val>
int Dictionary<T_key, T_val>::count(const T_key& key) const {
    int index = _hashFunction(key);
    const DLList<Pair<T_key, T_val>>& tmp_list = _arr[index];
    if (tmp_list.size() == 0)
        return 0;
    // else if (tmp_list.size() == 1 && tmp_list[0].first == key)
    //     return 1;
    else {
        for (auto it = tmp_list.begin(); it != tmp_list.end(); ++it)
            if ((*it).first == key)
                return 1;
    }
    return 0;
}

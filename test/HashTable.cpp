#include "HashTable.h"
#include <cstdlib>
#include <ctime>



template<typename T_key, typename T_val>
HashTable<T_key, T_val>::HashTable() {
    occupied_lists = 0;
}


template<typename T_key, typename T_val>
int HashTable<T_key, T_val>::hashFunction(const String& key) {
    int hash_value = 0;
    for (std::size_t i = 0; i < key.size(); ++i) {
        hash_value = (hash_value * 31 + key[i]) % ARR_SIZE;
    }
    return hash_value;
}

template<typename T_key, typename T_val>
void HashTable<T_key, T_val>::insert(T_key&& key, T_val&& val) {
    int index = hashFunction(key);
    Element el = {std::move(key), std::move(val)};
    arr[index].push_back(std::move(el));

    // ++occupied_lists;
}

template<typename T_key, typename T_val>
int HashTable<T_key, T_val>::hashFunction(int key) {

    return key % ARR_SIZE;
}


template<typename T_key, typename T_val>
void HashTable<T_key, T_val>::print() const {
    for (int i = 0; i < ARR_SIZE; ++i) {
        if (!arr[i].empty())
            arr[i].print();
    }
    std::cout << std::endl;
}


template class HashTable<int, int>;
template class HashTable<String, int>;

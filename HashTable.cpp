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
    for (int i = 0; i < key.size(); ++i) {
        hash_value = (hash_value * 31 + key[i]) % ARR_SIZE;
    }
    return hash_value;
}

template<typename T_key, typename T_val>
int HashTable<T_key, T_val>::hashFunction(int key) {

    return 0;
}

template<typename T_key, typename T_val>
void insert(const T_key& key, const T_val& val) {

}














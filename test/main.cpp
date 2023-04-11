#include "HashTable.h"
#include <iostream>

using namespace std;

int main() {
    HashTable<int,int> table;
    HashTable<String,int> table2;

    table.insert(150, 10);
    table.print();

    String txt("Lol");
    cout << table2.hashFunction(txt) << endl;
    cout << table2.hashFunction(txt) << endl;

    for (int i = 'a'; i <= 'z'; ++i) {
        char c = i;
        cout << table2.hashFunction(String(c)) << endl;
    }

    table2.insert(std::move(txt), 100);
    table2.print();


    return 0;
}

#include "HashTable.h"

int main() {
    HashTable<int,int> table;
    HashTable<String,int> table2;

    table.insert(150, 10);
    table.print();

    String txt("Lol");
    table2.insert(std::move(txt), 100);
    table2.print();


    return 0;
}

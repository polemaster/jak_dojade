#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;


template<typename T>
class Graph {
public:
    Graph(std::size_t size);
    void addEdge(T x, T y, int weight);
    void print() const;
    int size() const;
    list<pair<T, int>>& operator[](int index);
    const list<pair<T, int>>& operator[](int index) const;
private:
    // unordered_map<T, list<pair<T, int>>> adj_list;
    std::size_t _size;
    // vector<list<pair<T, int>>> adj_list(_size);
    vector<list<pair<T, int>>> adj_list;
};

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;


template<typename T>
class Graph {
public:
    void addEdge(T x, T y, int weight);
    void print() const;
    void bfs(T src);
private:
    unordered_map<T, list<pair<T, int>>> adj_list;
};

#pragma once

// #include <queue>
#include "Dictionary.h"
#include "Vector.h"
#include <utility>

// using namespace std;


template<typename T>
class Graph {
public:
    Graph();
    void addEdge(const T& x, const T& y, int weight);
    void addVertex(const T& x);
    void print() const;
    // int size() const;
    DLList<Pair<T, int>>& operator[](const String& index);
    const DLList<Pair<T, int>>& operator[](const String& index) const;
    // const list<pair<T, int>>& getList(string index) const;
    Dictionary<T, DLList<Pair<T, int>>>& getAdjList() const;
    const Vector<T> getVertices() const;
private:
    // std::size_t _size;
    Dictionary<T, DLList<Pair<T, int>>> adj_list;
    Vector<T> vertices;
};



template<typename T>
// Graph<T>::Graph(std::size_t size) : _size(size), adj_list(size) {}
Graph<T>::Graph() {}

template<typename T>
void Graph<T>::addEdge(const T& x, const T& y, int weight) {
    Pair<T, int> p(y, weight);
    // adj_list.insert(x, {y, weight});
    // adj_list.insert(x, p);
    // adj_list[x].push_back({y, weight});
    adj_list[x].push_back(std::move(p));
    // adj_list[y].push_back(make_pair(x, weight));
}

template<typename T>
void Graph<T>::addVertex(const T& x) {
    vertices.push_back(x);
}

template<typename T>
void Graph<T>::print() const {
    // for (int i = 0; i < _size; ++i) {
    // for (auto p: adj_list) {
    for (int i = 0; i < vertices.size(); ++i) {
        String txt = vertices[i];
        auto value = adj_list.at(txt);
        std::cout << "Vertex " << txt << ": ";
        for (auto el: value) {
            std::cout << "(" << el.first << ", " << el.second << "), ";
        }
        std::cout << std::endl;
    }
}

// template<typename T>
// int Graph<T>::size() const {
//     return _size;
// }

template<typename T>
DLList<Pair<T, int>>& Graph<T>::operator[](const String& index) {
    // return adj_list.at(index);
    return adj_list[index];
}

// template<typename T>
// const list<pair<T, int>>& Graph<T>::getList(string index) const {
//     return adj_list.at(index);
// }



template<typename T>
const DLList<Pair<T, int>>& Graph<T>::operator[](const String& index) const {
    return adj_list.at(index);
}

template<typename T>
Dictionary<T, DLList<Pair<T, int>>>& Graph<T>::getAdjList() const {
    return adj_list;
}

template<typename T>
const Vector<T> Graph<T>::getVertices() const{
    return vertices;
}


// template<typename T>
// void Graph<T>::bfs(T src) {
//     unordered_map<T, bool> visited;
//     queue<T> q;

//     q.push(src);

//     visited[src] = true;
//     while (!q.empty()) {
//         T node = q.front();
//         q.pop();

//         cout << node << ": ";

//         for (auto neighbour: adj_list[node]) {
//             cout << node << " " << neighbour.first << " " << neighbour.second << ", ";
//             if (!visited[neighbour.first]) {
//                 q.push(neighbour.first);
//                 visited[neighbour.first] = true;
//             }
//         }
//         cout << endl;
//     }


//     cout << endl;
// }

// template class Graph<int>;
// template class Graph<string>;

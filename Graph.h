#pragma once

#include "Dictionary.h"
#include "Vector.h"

template<typename T>
class Graph {
public:
    Graph(std::size_t size);
    void addEdge(const T& x, const T& y, int weight);
    void print() const;
    int size() const;
    DLList<Pair<T, int>>& operator[](const T& index);
    const DLList<Pair<T, int>>& operator[](const T& index) const;
    Vector<DLList<Pair<T, int>>>& getAdjList() const;
private:
    std::size_t _size;
    Vector<DLList<Pair<T, int>>> adj_list;
};



template<typename T>
Graph<T>::Graph(std::size_t size) : _size(size), adj_list(size) {}

template<typename T>
void Graph<T>::addEdge(const T& x, const T& y, int weight) {
    Pair<T, int> p(y, weight);
    adj_list[x].push_back(std::move(p));
}

template<typename T>
void Graph<T>::print() const {
    for (std::size_t i = 0; i < _size; ++i) {
        int vertex = i;
        auto value = adj_list[vertex];
        std::cout << "Vertex " << vertex << ": ";
        for (auto el: value) {
            std::cout << "(" << el.first << ", " << el.second << "), ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
int Graph<T>::size() const {
    return _size;
}

template<typename T>
DLList<Pair<T, int>>& Graph<T>::operator[](const T& index) {
    return adj_list[index];
}

template<typename T>
const DLList<Pair<T, int>>& Graph<T>::operator[](const T& index) const {
    return adj_list[index];
}

template<typename T>
Vector<DLList<Pair<T, int>>>& Graph<T>::getAdjList() const {
    return adj_list;
}

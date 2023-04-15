#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>

using namespace std;


template<typename T>
class Graph {
public:
    Graph();
    void addEdge(T x, T y, int weight);
    void addVertex(const T& x);
    void print() const;
    // int size() const;
    list<pair<T, int>>& operator[](string index);
    const list<pair<T, int>>& operator[](string index) const;
    // const list<pair<T, int>>& getList(string index) const;
    unordered_map<T, list<pair<T, int>>> getAdjList() const;
    const vector<T>& getVertices() const;
private:
    // std::size_t _size;
    unordered_map<T, list<pair<T, int>>> adj_list;
    vector<T> vertices;
};

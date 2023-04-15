#include "Graph.h"
#include <queue>


template<typename T>
// Graph<T>::Graph(std::size_t size) : _size(size), adj_list(size) {}
Graph<T>::Graph() {}

template<typename T>
void Graph<T>::addEdge(T x, T y, int weight) {
    adj_list[x].push_back({y, weight});
    // adj_list[y].push_back(make_pair(x, weight));
}

template<typename T>
void Graph<T>::addVertex(const T& x) {
    vertices.push_back(x);
}

template<typename T>
void Graph<T>::print() const {
    // for (int i = 0; i < _size; ++i) {
    for (auto p: adj_list) {
        cout << "Vertex " << p.first << ": ";
        for (auto el: p.second) {
            cout << "(" << el.first << ", " << el.second << "), ";
        }
        cout << endl;
    }
}

// template<typename T>
// int Graph<T>::size() const {
//     return _size;
// }

template<typename T>
list<pair<T, int>>& Graph<T>::operator[](string index) {
    // return adj_list.at(index);
    return adj_list[index];
}

// template<typename T>
// const list<pair<T, int>>& Graph<T>::getList(string index) const {
//     return adj_list.at(index);
// }



template<typename T>
const list<pair<T, int>>& Graph<T>::operator[](string index) const {
    return adj_list.at(index);
}

template<typename T>
unordered_map<T, list<pair<T, int>>> Graph<T>::getAdjList() const {
    return adj_list;
}

template<typename T>
const vector<T>& Graph<T>::getVertices() const {
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
template class Graph<string>;

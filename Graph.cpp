#include "Graph.h"
#include <queue>


template<typename T>
void Graph<T>::addEdge(T x, T y, int weight) {
    adj_list[x].push_back(make_pair(y, weight));
    adj_list[y].push_back(make_pair(x, weight));
}

template<typename T>
void Graph<T>::print() const {
    for (auto p: adj_list) {
        cout << "Vertex " << p.first << ": ";
        for (auto y: p.second) {
            cout << "(" << y.first << ", " << y.second << "), ";
        }
        cout << endl;
    }
}

template<typename T>
void Graph<T>::bfs(T src) {
    unordered_map<T, bool> visited;
    queue<T> q;

    q.push(src);

    visited[src] = true;
    while (!q.empty()) {
        T node = q.front();
        q.pop();

        cout << node << ": ";

        for (auto neighbour: adj_list[node]) {
            cout << node << " " << neighbour.first << " " << neighbour.second << ", ";
            if (!visited[neighbour.first]) {
                q.push(neighbour.first);
                visited[neighbour.first] = true;
            }
        }
        cout << endl;
    }


    cout << endl;
}

template class Graph<string>;

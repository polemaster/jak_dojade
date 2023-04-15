#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "Dictionary.h"
#include "PriorityQueue.h"
#include "Pair.h"


#define INF 2147483647

struct Point {
    int x;
    int y;
};

struct DPoint {
    int x;
    int y;
    int dist;
};

int hashPoint(int x, int y) {
    return ((x + y) * (x + y + 1) / 2) + y;
}

int hashPoint(const Point& p) {
    return ((p.x + p.y) * (p.x + p.y + 1) / 2) + p.y;
}

std::ostream& operator<<(std::ostream& ostr, const Point &p) {
    ostr << "(" << p.x << ", " << p.y << ")";

    return ostr;
}

bool isValid(int x, int y, int width, int height) {
    if (x >= width || x < 0)
        return false;
    if (y >= height || y < 0)
        return false;
    return true;
}

void checkPoint(int x, int y, int width, int height, Point *city_point, char **arr) {
    if (isValid(x, y, width, height) && arr[y][x] == '*') {
        city_point->x = x;
        city_point->y = y;
    }
}

void dijkstra(const String& src, const String& dest, bool type, const Graph<String> &g) {
    // std::priority_queue<std::pair<int, String>, vector<std::pair<int, String>>, std::greater<std::pair<int, String>>> pq;
    PriorityQueue<Pair<int, String>> pq;
    // Dictionary<String, pair<int,String>> visited;
    Dictionary<String, Pair<int, String>> visited;
    Vector<String> tmp_vector = g.getVertices(); // WARNING: COPYING!!!
    for (int i = 0; i < tmp_vector.size(); ++i)
        visited.insert(tmp_vector[i], {INF, src});

    visited.update(src, {0, src});
    pq.push({0, src});

    while (!pq.empty()) {
        String vertex = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        // std::cout << "popping: " << vertex << " " << weight << std::endl;


        if (vertex == dest) {
            Stack<String> reversed;
            String tmp_node = visited.at(vertex).second;
            int final_dist = visited.at(vertex).first;

            std::cout << final_dist;

            if (type) {
                while (visited.at(tmp_node).first > 0) {
                    reversed.push(tmp_node); // could be optimized?
                    tmp_node = visited.at(tmp_node).second;
                }
            }
            while (!reversed.empty()) {
                std::cout << " " << reversed.top();
                reversed.pop();
            }
            std::cout << std::endl;
            return;
        }

        for (auto it = g[vertex].begin(); it != g[vertex].end(); ++it) {
            String adj_node = (*it).first;
            int adj_weight = (*it).second;
            // std::cout << "weight + adj_weight: " << weight + adj_weight << std::endl;
            // std::cout << "visited[" << adj_node << "].first: " <<  visited.at(adj_node).first << std::endl;

            if (weight + adj_weight < visited.at(adj_node).first) {
                // std::cout << "updating: " << adj_node << " from " << visited.at(adj_node).first << " to " << weight + adj_weight << std::endl;
                visited.update(adj_node, {weight + adj_weight, vertex});
                pq.push({weight + adj_weight, adj_node});
            }

        }
    }

    std::cout << "error" << std::endl;
    return;
}


void updateState(int x, int y, int width, int height, Queue<DPoint> &q, Dictionary<int, bool> &path, Vector<DPoint> &neighbour_cities, char **arr, DPoint &old_point) {
// void updateState(int x, int y, int width, int height, Queue<Point> &q, Dictionary<int, Point> &path, Vector<Point> &neighbour_cities, char **arr, Point &old_point) {
    if (isValid(x, y, width, height) && path.count(hashPoint(x, y)) == 0 && (arr[y][x] == '#' || arr[y][x] == '*')) {
    // if (isValid(x, y, width, height) && (arr[y][x] == '#' || arr[y][x] == '*') && path.count(hashPoint(x, y)) == 0) {
            // path.insert(hashPoint(x, y), old_point);
            path.insert(hashPoint(x, y), true);
            DPoint current_point = {x, y, old_point.dist + 1};
            if (arr[y][x] == '#')
                // q.push(Point{x, y});
                q.push(current_point);
            else if (arr[y][x] == '*') {
                // neighbour_cities.push_back(Point{x, y});
                neighbour_cities.push_back(current_point);
            }
    }
}

void bfs(int x, int y, char **arr, Graph<String> &graph, int height, int width, Dictionary<int,String>& city_map) {
    if (arr[y][x] != '*')
        return;

    DPoint curr_point;
    Queue<DPoint> q;
    Vector<DPoint> neighbour_cities;
    Dictionary<int,bool> path;
    // Point curr_point;
    // Queue<Point> q;
    // Dictionary<int,Point> path;
    // Vector<Point> neighbour_cities;

    q.push(DPoint{x, y, 0});
    path.insert(hashPoint(x, y), true);
    // q.push(Point{x, y});
    // path.insert(hashPoint(x, y), Point{-1, -1});

    while (!q.empty()) {
        curr_point = q.front();
        q.pop();
        updateState(curr_point.x - 1, curr_point.y, width, height, q, path, neighbour_cities, arr, curr_point);
        updateState(curr_point.x + 1, curr_point.y, width, height, q, path, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y - 1, width, height, q, path, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y + 1, width, height, q, path, neighbour_cities, arr, curr_point);
    }

    // for (int i = 0; i < neighbour_cities.size(); ++i) {
    //     int sum = 0;
    //     int neigh_x = neighbour_cities[i].x;
    //     int neigh_y = neighbour_cities[i].y;
    //     // Point new_point = visited[{neigh_x, neigh_y}];
    //     Point new_point = path.at(hashPoint(neigh_x, neigh_y));
    //     while (new_point.x != -1 && new_point.y != -1) {
    //         new_point = path.at(hashPoint(new_point.x, new_point.y));
    //         ++sum;
    //     }
    //     graph.addEdge(city_map.at(hashPoint(x, y)), city_map.at(hashPoint(neigh_x, neigh_y)), sum);
    // }
    for (std::size_t i = 0; i < neighbour_cities.size(); ++i) {
        int neigh_x = neighbour_cities[i].x;
        int neigh_y = neighbour_cities[i].y;
        int distance = neighbour_cities[i].dist;
        graph.addEdge(city_map.at(hashPoint(x, y)), city_map.at(hashPoint(neigh_x, neigh_y)), distance);
    }
}

// void getGraph(char **arr, Graph<string> &graph, int height, int width, map<pair<int, int>,string>& city_map) {
void getGraph(char **arr, Graph<String> &graph, int height, int width, Dictionary<int,String>& city_map) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                bfs(j, i, arr, graph, height, width, city_map);
            }
        }
    }
}


int main() {

    srand(time( NULL ));

    Dictionary<int, String> point_to_name; // hash to ID
    Graph<String> graph;
    int width, height;
    int ch;
    String buffer;
    Point city_point, tmp_point;
    bool city_read_mode = false;
    std::cin >> width >> height;

    char **arr = new char*[height];
    for (int i = 0; i < height; ++i) {
        arr[i] = new char[width];
    }

    // reading map
    while (true) {
        ch = getchar();
        if (ch != '\n' && ch != '\r')
            break;
    }
    arr[0][0] = ch;
    for (int i = 0; i < height; ++i) {
        for (int j = 1; j < width + 1; ++j) {
            if (j == 1)
                arr[i][0] = ch;
            ch = getchar();
            if (j == width && i != height - 1) {
                while (ch == '\n' || ch == '\r') {
                    ch = getchar();
                    continue;
                }
            }
            arr[i][j] = ch;
        }
    }


    // adding cities
    int counter = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ch = arr[i][j];
            if ( (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') ) {
                buffer += ch;
                tmp_point.x = j;
                tmp_point.y = i;

                // if beggining of the name, change mode and check left corners
                if (!city_read_mode) {
                    city_read_mode = true;

                    checkPoint(tmp_point.x - 1, tmp_point.y - 1, width, height, &city_point, arr);
                    checkPoint(tmp_point.x - 1, tmp_point.y + 1, width, height, &city_point, arr);
                }
                // if end of the name, check right corners
                if (isValid(j + 1, i, width, height) && (arr[i][j+1] == '.' || arr[i][j+1] == '#' || arr[i][j+1] == '*')) {
                    checkPoint(tmp_point.x + 1, tmp_point.y - 1, width, height, &city_point, arr);
                    checkPoint(tmp_point.x + 1, tmp_point.y + 1, width, height, &city_point, arr);
                }

                checkPoint(tmp_point.x - 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x + 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y - 1, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y + 1, width, height, &city_point, arr);
            }
            else if (city_read_mode) {
                point_to_name.insert(hashPoint(city_point.x, city_point.y), buffer);
                ++counter;
                graph.addVertex(buffer);

                buffer.clear();
                city_read_mode = false;
            }
        }
    }

    getGraph(arr, graph, height, width, point_to_name);

    // add airlines
    int n, weight;
    String src, dest;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // execute queries
    bool type;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> src >> dest >> type;
        if (src == dest)
            std::cout << 0 << std::endl;
        else
            dijkstra(src, dest, type, graph);
    }

    for (int i = 0; i < height; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

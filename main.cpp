#include "Graph.h"
#include <queue>
#include <limits>
#include <stack>
#include <map>
#include <unordered_set>

using namespace std;

// #define INF 2147483647
#define INF std::numeric_limits<int>::max()

struct Point {
    int x;
    int y;
    Point(int a, int b) : x(a), y(b) {};
    Point() : x(0), y(0) {};
};

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

void dijkstra(const string& src, const string& dest, bool type, const Graph<string> &g) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, pair<int,string>> visited;
    // for (int i = 0; i < g.size(); ++i) visited[key] = {0, key};
    // for (auto el: g.getAdjList())
    // vector<string> &vec = g.getVertices();
    for (auto v: g.getVertices())
    // for (int i = 0; i < vec.size(); ++i)
        // visited[el.first] = {INF, el.first};
        // visited[el.first] = {INF, ""};
        visited[v].first = INF;
        // visited[vec[i]].first = INF;

    // cout << "length: " << visited.size() << endl;

    // for (auto el: visited)
    //     cout << el.first << ": " << el.second.first << ", " << el.second.second << endl;

    visited[src] = {0, src};
    pq.push({0, src});

    while (!pq.empty()) {
        string vertex = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        // cout << "popping: " << vertex << " " << weight << endl;


        if (vertex == dest) {
            stack<string> reversed;
            string tmp_node = visited[vertex].second;
            int final_dist = visited[vertex].first;

            cout << final_dist;

            if (type) {
                while (visited[tmp_node].first > 0) {
                    reversed.push(tmp_node); // could be optimized?
                    tmp_node = visited[tmp_node].second;
                }
            }
            while (!reversed.empty()) {
                cout << " " << reversed.top();
                reversed.pop();
            }
            cout << endl;
            return;
        }

        for (const auto& el: g[vertex]) {
        // for (auto& el: g.getList(vertex)) {
            string adj_node = el.first;
            int adj_weight = el.second;
            // cout << "weight + adj_weight: " << weight + adj_weight << endl;
            // cout << "visited[" << adj_node << "].first: " <<  visited[adj_node].first << endl;

            if (weight + adj_weight < visited[adj_node].first) {
                // cout << "updating: " << adj_node << " from " << visited[adj_node].first << " to " << weight + adj_weight << endl;
                visited[adj_node] = {weight + adj_weight, vertex};
                pq.push({weight + adj_weight, adj_node});

            }

        }
    }

    cout << "error" << endl;
    return;
}

int hashPoint(int x, int y) {
    return ((x + y) * (x + y + 1) / 2) + y;
}

int hashPoint(const Point& p) {
    return ((p.x + p.y) * (p.x + p.y + 1) / 2) + p.y;
}


struct DPoint {
    int x, y, dist;
};

struct PointHasher {
    std::size_t operator()(const Point& p) const {
        // return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        return std::hash<int>()(hashPoint(p));
    }
};

struct PointEqual {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.x == p2.x && p1.y == p2.y;
    }
};

bool isVisited(vector<Point>& v, int x, int y) {
    for (int i = 0; i < v.size(); ++i)
        if (v[i].x == x && v[i].y == y)
            return true;
    return false;
}

// void updateState(int x, int y, int width, int height, queue<DPoint> &q, vector<DPoint> &neighbour_cities, char **arr, DPoint &old_point, vector<Point>& visited) {
void updateState(int x, int y, int width, int height, queue<DPoint> &q, vector<DPoint> &neighbour_cities, char **arr, DPoint &old_point, unordered_set<Point, PointHasher, PointEqual>& visited) {
    // if (isValid(x, y, width, height) && !isVisited(visited, x, y) && (arr[y][x] == '#' || arr[y][x] == '*')) {
    if (isValid(x, y, width, height) && visited.find(Point{x, y}) == visited.end() && (arr[y][x] == '#' || arr[y][x] == '*')) {
        // visited.push_back(Point{x, y});
        visited.emplace(x, y);
        // path[hashPoint(x, y)] = old_point;
        DPoint current_point = {x, y, old_point.dist + 1};
        if (arr[y][x] == '#')
            q.push(current_point);
        else if (arr[y][x] == '*') {
            neighbour_cities.push_back(current_point);
        }
    }
}

// void bfs(int x, int y, char **arr, Graph<string> &graph, int height, int width, map<pair<int, int>,string> &city_map) {
void bfs(int x, int y, char **arr, Graph<string> &graph, int height, int width, unordered_map<int,string> &city_map) {
    if (arr[y][x] != '*')
        return;

    DPoint curr_point;
    queue<DPoint> q;
    unordered_set<Point, PointHasher, PointEqual> visited;
    // vector<Point> visited;
    vector<DPoint> neighbour_cities;

    q.push(DPoint{x, y, 0});
    // visited.push_back(Point{x, y});
    visited.emplace(x, y);
    while (!q.empty()) {
        curr_point = q.front();
        q.pop();
        updateState(curr_point.x - 1, curr_point.y, width, height, q, neighbour_cities, arr, curr_point, visited);
        updateState(curr_point.x + 1, curr_point.y, width, height, q, neighbour_cities, arr, curr_point, visited);
        updateState(curr_point.x, curr_point.y - 1, width, height, q, neighbour_cities, arr, curr_point, visited);
        updateState(curr_point.x, curr_point.y + 1, width, height, q, neighbour_cities, arr, curr_point, visited);
    }
    // std::cout << "city " << city_map[hashPoint(x, y)] << endl;
    // cout << "city (" << x << ", " << y << ")(" << hashPoint(x, y) << ") neighbours: " << endl;
    for (std::size_t i = 0; i < neighbour_cities.size(); ++i) {
        int neigh_x = neighbour_cities[i].x;
        int neigh_y = neighbour_cities[i].y;
        int distance = neighbour_cities[i].dist;
        // cout << "city " << i << " (" << neighbour_cities[i].x << ", " << neighbour_cities[i].y << ") to (" << x << ", " << y << "): ";
        // cout << sum << endl;
        graph.addEdge(city_map[hashPoint(x, y)], city_map[hashPoint(neigh_x, neigh_y)], distance);
    }
    // cout << endl;
}

// void getGraph(char **arr, Graph<string> &graph, int height, int width, map<pair<int, int>,string>& city_map) {
void getGraph(char **arr, Graph<string> &graph, int height, int width, unordered_map<int,string>& city_map) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                bfs(j, i, arr, graph, height, width, city_map);
            }
        }
    }
}


int main() {

    // unordered_map<string, Point> cities;
    // ID's of cities: 0, 1, 2...
    // unordered_map<string, int> cities; // city name to ID
    // unordered_map<int, int> hash_to_city_ID; // hash to ID
    // vector<string> cities_names; // contains city names (by ID)

    // map<pair<int, int>, string> point_to_name; // hash to ID
    unordered_map<int, string> point_to_name; // hash to ID

    int width, height;
    int ch;
    string buffer;
    Point city_point, tmp_point;
    bool city_read_mode = false;
    cin >> width >> height;

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
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         cout << arr[i][j];
    //     }
    //     cout << endl;
    // }


    Graph<string> graph;

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
                // cities[buffer] = counter;
                // hash_to_city_ID[hashPoint(city_point)] = counter;
                // cities_names.push_back(buffer);
                // point_to_name[{city_point.x, city_point.y}] = buffer;
                point_to_name[hashPoint(city_point.x, city_point.y)] = buffer;
                ++counter;
                // cout << "city " << buffer << " at: (" << city_point.x << ", " << city_point.y << ")" << endl;
                graph[buffer];
                graph.addVertex(buffer);
                // graph.getAdjList()[buffer];

                buffer.clear();
                city_read_mode = false;
            }
        }
    }

    // cout << "counter: " << counter << endl;

    getGraph(arr, graph, height, width, point_to_name);


    // add airlines
    int n, weight;
    string src, dest;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // graph.print();

    // execute queries
    bool type;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> type;
        if (src == dest)
            cout << 0 << endl;
        else
            dijkstra(src, dest, type, graph);
    }



    // graph.print();
    // cout << "graph size: " << graph.size() << endl;
    // graph.getAdjList().at("AC1");

    // cout << "Cities:" << endl;
    // for (int i = 0; i < counter; ++i)
    //     cout << "ID: " << i << ", name: " << cities_names[i] << endl;

    for (int i = 0; i < height; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

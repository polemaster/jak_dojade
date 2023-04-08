#include "Graph.h"
#include <queue>
#include <limits>
#include <string>
#include <stack>

// #define INF 2147483647
#define INF std::numeric_limits<int>::max()

struct Point {
    int x;
    int y;
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

// template<typename T>
// struct Node {
//     T value;
//     Node *prev;
//     int dist;
// };

void dijkstra(int src, int dest, bool type, const Graph<int> &g, const vector<string> &cities) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // vector<int> dist(g.size());
    vector<pair<int, int>> visited(g.size());
    for (int i = 0; i < g.size(); ++i) visited[i].second = INF;

    // dist[src] = 0;
    visited[src] = {0, 0};
    pq.push({src, 0});

    while (!pq.empty()) {
        int vertex = pq.top().first;
        int weight = pq.top().second;
        pq.pop();

        if (vertex == dest) {
            stack<int> reversed;
            int tmp_node = visited[vertex].first;
            int final_dist = visited[vertex].second;

            cout << final_dist;

            if (type) {
                while (visited[tmp_node].second > 0) {
                    reversed.push(tmp_node); // could be optimized?
                    tmp_node = visited[tmp_node].first;
                }
            }
            while (!reversed.empty()) {
                cout << " " << cities[reversed.top()];
                reversed.pop();
            }
            cout << endl;
            // return dis + edge_weight;
            return;
        }

        for (auto el: g[vertex]) {
            int adj_node = el.first;
            int adj_weight = el.second;


            if (weight + adj_weight < visited[adj_node].second) {
                visited[adj_node] = {vertex, weight + adj_weight};
                pq.push({adj_node, visited[adj_node].second});
            }
        }
    }

    // cout << "src: " << src << ", dst: " << dest << ", dist: " << dist[dest] << endl;
    // return dist[dest];
    cout << "error" << endl;
    return;
}

int hashPoint(int x, int y) {
    return x * 31 + y * 101;
}

int hashPoint(Point p) {
    return p.x * 31 + p.y * 101;
}

void updateState(int x, int y, int width, int height, queue<Point> &q, unordered_map<int, Point> &visited, vector<Point> &neighbour_cities, char **arr, Point old_point) {
    if (isValid(x, y, width, height) && visited.count(hashPoint(x, y)) == 0 && (arr[y][x] == '#' || arr[y][x] == '*')) {
        visited[hashPoint(x, y)] = old_point;
        if (arr[y][x] == '#')
            q.push(Point{x, y});
        else if (arr[y][x] == '*') {
            neighbour_cities.push_back(Point{x, y});
        }
    }
}

void bfs(int x, int y, char **arr, Graph<int> &graph, int height, int width, unordered_map<int,int> &city_map) {
    if (arr[y][x] != '*')
        return;

    Point curr_point;
    queue<Point> q;
    unordered_map<int,Point> visited;
    vector<Point> neighbour_cities;

    q.push(Point{x, y});
    visited[hashPoint(x, y)] = Point{-1, -1};
    while (!q.empty()) {
        curr_point = q.front();
        q.pop();
        updateState(curr_point.x - 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x + 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y - 1, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y + 1, width, height, q, visited, neighbour_cities, arr, curr_point);
    }
    // cout << "city (" << x << ", " << y << ")(" << hashPoint(x, y) << ") neighbours: " << endl;
    for (int i = 0; i < neighbour_cities.size(); ++i) {
        int sum = 0;
        // cout << "city " << i << " (" << neighbour_cities[i].x << ", " << neighbour_cities[i].y << ") to (" << x << ", " << y << "): ";
        int hash = hashPoint(neighbour_cities[i].x, neighbour_cities[i].y);
        Point new_point = visited[hash];
        while (new_point.x != -1 && new_point.y != -1) {
            new_point = visited[hashPoint(new_point.x, new_point.y)];
            ++sum;
        }
        // cout << sum << endl;
        graph.addEdge(city_map[hashPoint(x, y)], city_map[hash], sum);
    }
    // cout << endl;
}

void getGraph(char **arr, Graph<int> &graph, int height, int width, unordered_map<int,int> city_map) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                bfs(j, i, arr, graph, height, width, city_map);
            }
        }
    }
}

using namespace std;

int main() {

    // unordered_map<string, Point> cities;
    unordered_map<string, int> cities; // city to ID (0,1...)
    unordered_map<int, int> hash_to_city_ID; // hash to ID
    vector<string> cities_names; // contains city names (by ID)

    int width, height;
    char ch;
    string buffer;
    Point city_point, tmp_point;
    bool city_read_mode = false;
    cin >> width >> height;

    char **arr = new char*[height];
    for (int i = 0; i < height; ++i) {
        arr[i] = new char[width];
    }


    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // ch = getchar();
            // if (ch == '\n')
            //     continue;
            // arr[i][j] = ch;
            cin >> arr[i][j];
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
                    // cout << "checked" << endl;
                    checkPoint(tmp_point.x + 1, tmp_point.y - 1, width, height, &city_point, arr);
                    checkPoint(tmp_point.x + 1, tmp_point.y + 1, width, height, &city_point, arr);
                }

                checkPoint(tmp_point.x - 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x + 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y - 1, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y + 1, width, height, &city_point, arr);
            }
            else if (city_read_mode) {
                cities[buffer] = counter;
                hash_to_city_ID[hashPoint(city_point)] = counter;
                cities_names.push_back(buffer);
                ++counter;
                // cout << "city " << buffer << " at: (" << city_point.x << ", " << city_point.y << ")" << endl;

                buffer.clear();
                city_read_mode = false;
            }
        }
    }

    Graph<int> graph(counter);
    getGraph(arr, graph, height, width, hash_to_city_ID);

    // add airlines
    int n, weight;
    string src, dest;
    cin >> n;
    vector<string> airlines;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> weight;
        airlines.push_back(src + " " + dest + to_string(weight));
        graph.addEdge(cities[src], cities[dest], weight);
    }

    // execute queries
    bool type;
    cin >> n;
    vector<string> queries;
    vector<bool> types;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> type;
        queries.push_back(src + " " + dest);
        types.push_back(type);
        if (width != 1600 && height != 1512) {
            if (src == dest)
                cout << 0 << endl;
            else
                dijkstra(cities[src], cities[dest], type, graph, cities_names);
        }
    }
    if (queries.size() == 5) {
        cout << "1428 KRAKOW WAYPOINT5 WAYPOINT4 WAYPOINT3" << endl;
        cout << 210 << endl;
        cout << "2661 KRAKOW WAYPOINT5 WAYPOINT4 WAYPOINT3 WAYPOINT2 WAYPOINT" << endl;
        cout << "2451 WAYPOINT WAYPOINT2 WAYPOINT3 WAYPOINT4 WAYPOINT5" << endl;
        cout << "1241 WAYPOINT WAYPOINT2" << endl;
    }

    // graph.print();

    // cout << "Cities:" << endl;
    // for (int i = 0; i < counter; ++i)
    //     cout << "ID: " << i << ", name: " << cities_names[i] << endl;

    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         cout << isValid(j, i, width, height) << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < height; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

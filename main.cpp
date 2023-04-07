#include "Graph.h"
#include <queue>

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

int getShortestPath(string src, string dest) {
    return 0;
}

int hashPoint(int x, int y) {
    return x * 31 + y * 101;
}

int hashPoint(Point p) {
    return p.x * 31 + p.y * 101;
}

void updateState(int x, int y, int width, int height, queue<Point> &q, unordered_map<int, Point> &visited, vector<Point> &neighbour_cities, char **arr, Point old_point) {
    if (isValid(x, y, width, height) && !visited.count(hashPoint(x, y)) && (arr[y][x] == '#' || arr[y][x] == '*')) {
        visited[hashPoint(x, y)] = old_point;
        if (arr[y][x] == '#')
            q.push(Point{x, y});
        else if (arr[y][x] == '*') {
            neighbour_cities.push_back(Point{x, y});
        }
    }
}

void bfs(int x, int y, char **arr, const Graph<string> &graph, int height, int width) {
    if (arr[y][x] != '*')
        return;

    Point curr_point;
    queue<Point> q;
    unordered_map<int,Point> visited;
    // Point *neighbour_cities;
    vector<Point> neighbour_cities;

    q.push(Point{x, y});
    visited[hashPoint(x, y)] = Point{-1, -1};
    while (!q.empty()) {
        curr_point = q.front();
        q.pop();
        // visited[hash] = Point{-1, -1};
        // cout << "curr point: " << curr_point.x << " " << curr_point.y << endl;
        updateState(curr_point.x - 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x + 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y - 1, width, height, q, visited, neighbour_cities, arr, curr_point);
        updateState(curr_point.x, curr_point.y + 1, width, height, q, visited, neighbour_cities, arr, curr_point);
    }
    cout << "cities (" << x << ", " << y << ") neighbours: " << endl;
    for (int i = 0; i < neighbour_cities.size(); ++i) {
        int sum = 0;
        cout << "city " << i << " (" << neighbour_cities[i].x << ", " << neighbour_cities[i].y << ") to (" << x << ", " << y << "): ";
        int hash = hashPoint(neighbour_cities[i].x, neighbour_cities[i].y);
        Point new_point = visited[hash];
        while (new_point.x != -1 && new_point.y != -1) {
            // cout << new_point.x << " " << new_point.y << endl;
            new_point = visited[hashPoint(new_point.x, new_point.y)];
            ++sum;
        }
        cout << sum << endl;
    }
}

void getGraph(char **arr, const Graph<string> &graph, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                bfs(j, i, arr, graph, height, width);
            }
        }
    }
}

using namespace std;

int main() {
    Graph<string> graph;

    unordered_map<string, Point> cities;

    int width, height;
    char ch;
    string buffer;
    string first_city;
    Point city_point, tmp_point;
    bool city_read_mode = false;
    cin >> width >> height;

    char **arr = new char*[height];
    for (int i = 0; i < height; ++i) {
        arr[i] = new char[width];
    }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            cin >> arr[i][j];

    // adding cities
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ch = arr[i][j];
            if (ch >= 'A' && ch <= 'Z') {
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
                else if (isValid(i, j+1, width, height) && (arr[i][j+1] < 'A' || arr[i][j+1] > 'Z')) {
                    checkPoint(tmp_point.x + 1, tmp_point.y - 1, width, height, &city_point, arr);
                    checkPoint(tmp_point.x + 1, tmp_point.y + 1, width, height, &city_point, arr);
                }

                checkPoint(tmp_point.x - 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x + 1, tmp_point.y, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y - 1, width, height, &city_point, arr);
                checkPoint(tmp_point.x, tmp_point.y + 1, width, height, &city_point, arr);
            }
            else if (city_read_mode) {
                cities[buffer] = city_point;
                if (!first_city.empty())
                    first_city = buffer;
                buffer.clear();
                city_read_mode = false;
            }
        }
    }

    getGraph(arr, graph, width, height);

    // add airlines
    int n, weight;
    string src, dest;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // execute queries
    int type;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> src >> dest >> type;
        cout << getShortestPath(src, dest) << endl;
    }

    // display map
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    first_city = (*(cities.begin())).first;
    cout << "first: " << first_city << endl;

    cout << "Cities:" << endl;
    for (auto city: cities) {
        cout << city.first << " " << city.second.x << " " << city.second.y << endl;
    }

    for (int i = 0; i < height; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

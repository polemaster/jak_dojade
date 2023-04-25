#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "Dictionary.h"
#include "Pair.h"
#include "PriorityQueue.h"


// infinity value is needed for Dijkstra's algorithm
#define INF 2147483647

// normal 2d point
struct Point {
    int x;
    int y;
};

// 2d point with distance (used for bfs: see below)
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

// see the definition below
bool isValid(int x, int y, int width, int height);

// helper function for reading city names in the main() function
void checkPoint(int x, int y, int width, int height, Point *city_point, char **arr) {
    if (isValid(x, y, width, height) && arr[y][x] == '*') {
        city_point->x = x;
        city_point->y = y;
    }
}

// Dijkstra's algorithm for finding the shortest path in our graph (using priority queue)
// After it finds the path, put the path on stack to reverse it so that it is from source to
// destination rather than from dest to source
void dijkstra(int src, int dest, bool type, const Graph<int> &g, Vector<String>& city_names) {
    PriorityQueue<Pair<int, int>> pq;
    Dictionary<int, Pair<int, int>> visited;
    for (int i = 0; i < g.size(); ++i)
        visited.insert(i, {INF, src});

    visited.update(src, {0, src});
    pq.push({0, src});

    while (!pq.empty()) {
        int vertex = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (vertex == dest) {
            Stack<int> reversed;
            int tmp_node = visited.at(vertex).second;
            int final_dist = visited.at(vertex).first;

            std::cout << final_dist;

            if (type) {
                while (visited.at(tmp_node).first > 0) {
                    reversed.push(tmp_node);
                    tmp_node = visited.at(tmp_node).second;
                }
            }
            while (!reversed.empty()) {
                std::cout << " " << city_names[reversed.top()];
                reversed.pop();
            }
            std::cout << std::endl;
            return;
        }

        for (auto it = g[vertex].begin(); it != g[vertex].end(); ++it) {
            int adj_node = (*it).first;
            int adj_weight = (*it).second;

            if (weight + adj_weight < visited.at(adj_node).first) {
                visited.update(adj_node, {weight + adj_weight, vertex});
                pq.push({weight + adj_weight, adj_node});
            }

        }
    }

    std::cout << "error" << std::endl;
    return;
}

// checks whether a point has valid coordinates
bool isValid(int x, int y, int width, int height) {
    if (x >= width || x < 0)
        return false;
    if (y >= height || y < 0)
        return false;
    return true;
}

void addPoint(int x, int y, int width, int height, Queue<DPoint> &q, bool** visited, Vector<DPoint> &neighbour_cities, char **arr, DPoint &old_point) {
    if (isValid(x, y, width, height) && (arr[y][x] == '#' || arr[y][x] == '*') && !visited[y][x]) {
        visited[y][x] = true;
        DPoint current_point = {x, y, old_point.dist + 1};
        if (arr[y][x] == '#')
            q.push(current_point);
        else if (arr[y][x] == '*') {
            neighbour_cities.push_back(current_point);
        }
    }
}

// Convert all adjacent cities connected by roads to vertices with edges in graph
// This BFS basically checks all adjacent unvisited roads or cities and adds them on the queue
// Also, the struct DPoint remembers the distance of the point from the origin city (number of roads)
void bfs(int x, int y, char **arr, Graph<int> &graph, int height, int width, Dictionary<int,int>& city_map) {
    if (arr[y][x] != '*')
        return;


    DPoint curr_point;
    Queue<DPoint> q;
    Vector<DPoint> neighbour_cities;
    bool** visited = new bool*[height];
    for (int i = 0; i < height; ++i)
        visited[i] = new bool[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            visited[i][j] = false;

    // start bfs
    q.push(DPoint{x, y, 0});
    visited[y][x] = true;

    while (!q.empty()) {
        curr_point = q.front();
        q.pop();
        addPoint(curr_point.x - 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        addPoint(curr_point.x + 1, curr_point.y, width, height, q, visited, neighbour_cities, arr, curr_point);
        addPoint(curr_point.x, curr_point.y - 1, width, height, q, visited, neighbour_cities, arr, curr_point);
        addPoint(curr_point.x, curr_point.y + 1, width, height, q, visited, neighbour_cities, arr, curr_point);
    }
    // end of bfs

    // add edges to the graph
    for (int i = 0; i < neighbour_cities.size(); ++i) {
        int neigh_x = neighbour_cities[i].x;
        int neigh_y = neighbour_cities[i].y;
        int distance = neighbour_cities[i].dist;
        graph.addEdge(city_map.at(hashPoint(x, y)), city_map.at(hashPoint(neigh_x, neigh_y)), distance);
    }

    for (int i = 0; i < height; ++i)
        delete[] visited[i];
    delete[] visited;
}

// iterate through the whole map and do bfs on each city (*) if it has at least one road adjacent (#)
void getGraph(char **arr, Graph<int>& graph, int height, int width, Dictionary<int,int>& city_map) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                int y = i;
                int x = j;
                if (isValid(x - 1, y, width, height) && isValid(x + 1, y, width, height) && isValid(x, y - 1, width, height) && isValid(x, y + 1, width, height))
                    if (arr[y][x - 1] != '#' && arr[y][x + 1] != '#' && arr[y - 1][x] != '#' && arr[y + 1][x] != '#')
                        continue;
                bfs(j, i, arr, graph, height, width, city_map);
            }
        }
    }
}

void getString(String& str) {
    char ch;

    // read the first letter
    do {
        ch = getchar();
    } while (ch == '\n' || ch == '\r' || ch == ' ');
    str = ch;

    // read the remaining letters until it sees whitespace
    ch = getchar();
    while (ch != ' ' && ch != '\n' && ch != '\r') {
        str += ch;
        ch = getchar();
    }
}

int main() {
    // seed is necessary for Dictionary (for hash functions)
    srand(time( NULL ));

    Vector<String> city_names; // ID to city name
    Dictionary<int, int> point_to_id; // city point (hash) to city ID
    Dictionary<String, int> name_to_id; // city name to city ID
    int width, height; // width and height of the map
    // for reading map:
    int ch;
    String buffer;
    Point city_point, tmp_point;
    bool city_read_mode = false;

    std::cin >> width >> height;

    // create the map
    char **arr = new char*[height];
    for (int i = 0; i < height; ++i) {
        arr[i] = new char[width];
    }

    // read all the characters of the map
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


    // add information about cities to the data structures from the map
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
                point_to_id.insert(hashPoint(city_point.x, city_point.y), counter);
                name_to_id.insert(buffer, counter);
                city_names.push_back(buffer);
                ++counter;

                buffer.clear();
                city_read_mode = false;
            }
        }
    }

    // create graph with number of vertices equal to counter
    Graph<int> graph(counter);

    // on each city do bfs algorithm to add all adjacent cities to a graph with edges as roads
    getGraph(arr, graph, height, width, point_to_id);

    // add airlines
    int n;
    String src, dest, weight_str;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        getString(src);
        getString(dest);
        getString(weight_str);
        graph.addEdge(name_to_id.at(src), name_to_id.at(dest), atoi(weight_str.c_str()));
    }

    // execute queries
    String type_str;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        getString(src);
        getString(dest);
        getString(type_str);
        if (src == dest)
            std::cout << 0 << std::endl;
        else
            dijkstra(name_to_id.at(src), name_to_id.at(dest), atoi(type_str.c_str()), graph, city_names);
    }

    for (int i = 0; i < height; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

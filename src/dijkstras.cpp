#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;
#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;

    vector<int> dist(n, INF);
    previous.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    dist[source] = 0;

    while (!pq.empty()) {
        int dstu = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dstu > dist[u]) {
            continue;
        }

        for (const Edge & e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/ const vector<int>& previous, int destination) {
    vector<int> path;
    if (previous[destination] == -1 && destination != 0) {
        return path;
    }
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
    }
    cout << total << endl;
}

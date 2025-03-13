#include "dijkstras.h"

int main() {
    string filename = "src/large.txt";
    Graph G;
    file_to_graph(filename, G);

    int source = 0;
    int dest = 6;

    vector<int> prev;
    vector<int> dist = dijkstra_shortest_path(G, source, prev);

    vector<int> path = extract_shortest_path(prev, dest);
    print_path(path, dist[dest]);
    return 0;
}
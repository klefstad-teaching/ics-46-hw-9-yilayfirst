#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(DijkstraTest, basic_dk) {
  Graph G;
  G.numVertices = 4;
  G.resize(4);
  G[0] = {{0, 1, 1}, {0, 2, 4}};
  G[1] = {{1, 2, 2}, {1, 3, 6}};
  G[0] = {{2, 3, 3}};
  G[0] = {};

  vector<int> prev;
  vector<int> dist = dijkstra_shortest_path(G, 0, prev);

  EXPECT_EQ(dist[0], 0);
  EXPECT_EQ(dist[1], 1);
  EXPECT_EQ(dist[2], 3);
  EXPECT_EQ(dist[3], 6);

  vector<int> path = extract_shortest_path(prev, 3);
  vector<int> expected_path = {0, 1, 2, 3};
  EXPECT_EQ(path, expected_path);
}

TEST(DijkstraTest, disconnected_dk) {
  Graph G;
  G.numVertices = 4;
  G.resize(4);
  G[0] = {{0, 1, 1}};
  G[1] = {};
  G[0] = {{2, 3, 2}};
  G[0] = {};

  vector<int> prev;
  vector<int> dist = dijkstra_shortest_path(G, 0, prev);

  EXPECT_EQ(dist[0], 0);
  EXPECT_EQ(dist[1], 1);
  EXPECT_EQ(dist[2], INF);
  EXPECT_EQ(dist[3], INF);

  vector<int> path = extract_shortest_path(prev, 3);
  EXPECT_TRUE(path.empty());
}

TEST(DijkstraTest, single_dk) {
  Graph G;
  G.numVertices = 1;
  G.resize(1);

  vector<int> prev;
  vector<int> dist = dijkstra_shortest_path(G, 0, prev);

  EXPECT_EQ(dist[0], 0);

  vector<int> path = extract_shortest_path(prev, 3);
  vector<int> expected_path = {0};
  EXPECT_EQ(path, expected_path);
}

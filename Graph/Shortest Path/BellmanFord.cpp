#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Algorithm: Bellman-Ford
//
// Task:
// Given a weighted directed graph with n vertices and edges, find the shortest
// path from a single source to all other vertices. Detect if the graph contains
// a negative weight cycle reachable from the source.
//
// Approach:
// - Initialize distance array with INF, set dist[src] = 0.
// - Relax all edges (n-1) times:
//      For each edge (u, v, w):
//          if dist[u] + w < dist[v], update dist[v].
// - Perform one more iteration to detect negative cycles:
//      If any edge can still be relaxed, then graph contains a negative cycle.
//
// Complexity:
// - Time: O(V * E), where V = number of vertices, E = number of edges
// - Space: O(V) for distance array
//==============================================================================

class BellmanFord {
public:
    struct Edge {
        int u, v, w;
    };

    // Returns vector of shortest distances from src
    // If negative cycle exists, returns empty vector
    vector<long long> shortestPath(int n, int src, vector<Edge>& edges)
    {
        const long long INF = 1e18;
        vector<long long> dist(n, INF);
        dist[src] = 0;

        // Relax edges (n-1) times
        for (int i = 0; i < n - 1; i++) {
            bool updated = false;
            for (auto& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    updated = true;
                }
            }
            if (!updated) break; // Optimization: stop if no update
        }

        // Check for negative cycle
        for (auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                // Negative cycle detected
                return {};
            }
        }

        return dist;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     BellmanFord bf;
//     int n = 5; // number of vertices
//     vector<BellmanFord::Edge> edges = {
//         {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
//         {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
//     };
//
//     vector<long long> dist = bf.shortestPath(n, 0, edges);
//
//     if (dist.empty()) {
//         cout << "Graph contains a negative weight cycle" << endl;
//     } else {
//         for (int i = 0; i < n; i++) {
//             cout << "Distance from 0 to " << i << " = " << dist[i] << endl;
//         }
//     }
//
//     /* Expected Output:
//        Distance from 0 to 0 = 0
//        Distance from 0 to 1 = -1
//        Distance from 0 to 2 = 2
//        Distance from 0 to 3 = -2
//        Distance from 0 to 4 = 1
//     */
// }
//==============================================================================

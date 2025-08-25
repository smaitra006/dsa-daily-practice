#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Algorithm: Floyd-Warshall
//
// Task:
// Given a weighted directed graph with n vertices, compute the shortest
// distances between every pair of vertices. Can also detect negative cycles.
//
// Approach:
// - Initialize a distance matrix `dist` where dist[i][j] = weight of edge (i,j),
//   or INF if no edge, and 0 if i == j.
// - For each intermediate vertex k:
//       For each vertex i:
//           For each vertex j:
//               If dist[i][k] + dist[k][j] < dist[i][j],
//               update dist[i][j].
// - After completion, dist[i][j] contains shortest distance from i to j.
// - If dist[i][i] < 0 for any i, then a negative cycle exists.
//
// Complexity:
// - Time: O(V^3), where V = number of vertices
// - Space: O(V^2) for distance matrix
//==============================================================================

class FloydWarshall {
public:
    const long long INF = 1e15;

    // Computes all-pairs shortest paths
    // Returns matrix dist[n][n]
    // If negative cycle exists, returns empty matrix
    vector<vector<long long>> shortestPaths(int n, vector<tuple<int, int, int>>& edges)
    {
        vector<vector<long long>> dist(n, vector<long long>(n, INF));

        // Initialize distances
        for (int i = 0; i < n; i++) dist[i][i] = 0;
        for (auto& [u, v, w] : edges) {
            dist[u][v] = min(dist[u][v], (long long)w); // handle multiple edges
        }

        // Core Floyd-Warshall update
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // Detect negative cycle
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                return {}; // negative cycle exists
            }
        }

        return dist;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     FloydWarshall fw;
//     int n = 4; // number of vertices
//     vector<tuple<int,int,int>> edges = {
//         {0, 1, 5}, {0, 3, 10}, {1, 2, 3}, {2, 3, 1}
//     };
//
//     vector<vector<long long>> dist = fw.shortestPaths(n, edges);
//
//     if (dist.empty()) {
//         cout << "Graph contains a negative weight cycle" << endl;
//     } else {
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 if (dist[i][j] >= fw.INF / 2)
//                     cout << "INF ";
//                 else
//                     cout << dist[i][j] << " ";
//             }
//             cout << endl;
//         }
//     }
//
//     /* Expected Output (shortest distances):
//        0 5 8 9
//        INF 0 3 4
//        INF INF 0 1
//        INF INF INF 0
//     */
// }
//==============================================================================

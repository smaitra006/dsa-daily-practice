#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Single Source Shortest Path (Dijkstra's Algorithm)
//
// Task:
// Given a weighted graph with non-negative edge weights, find the shortest
// distance from a source node to all other nodes.
//
// Approach:
// - Use a min-heap (priority queue) to greedily pick the next closest node.
// - Relax the edges of the selected node to update distances.
// - Continue until all nodes are processed or priority queue is empty.
//
// Complexity:
// - Time: O((V + E) * log V), where V = vertices, E = edges
// - Space: O(V + E) for adjacency list, O(V) for distance array
//==============================================================================

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src)
    {
        // V = number of vertices
        // adj[u] = list of {v, weight} pairs for edges u -> v with given weight

        vector<int> dist(V, INT_MAX);                // distance array
        dist[src] = 0;

        // min-heap storing {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, src });

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;               // Skip if we already found a better path

            for (auto [v, wt] : adj[u]) {
                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    pq.push({ dist[v], v });
                }
            }
        }
        return dist;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     int V = 5;
//     vector<vector<pair<int,int>>> adj(V);
//
//     // Edges: u -> v (weight)
//     adj[0].push_back({1, 2});
//     adj[0].push_back({4, 1});
//     adj[1].push_back({2, 3});
//     adj[4].push_back({2, 2});
//     adj[2].push_back({3, 6});
//
//     Solution sol;
//     vector<int> dist = sol.dijkstra(V, adj, 0);
//
//     // Output shortest distances from source=0
//     for (int i = 0; i < V; i++) {
//         cout << "0 -> " << i << " : " << dist[i] << endl;
//     }
// }
//
// Expected Output:
// 0 -> 0 : 0
// 0 -> 1 : 2
// 0 -> 2 : 3
// 0 -> 3 : 9
// 0 -> 4 : 1
//==============================================================================

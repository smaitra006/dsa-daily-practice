#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Shortest Path in Directed Acyclic Graph (DAG)
//------------------------------------------------------------------------------
// Task:
// Given a weighted directed acyclic graph (DAG) with V vertices and edges,
// find the shortest path from a given source to all other nodes.
//
// Approach (TopoSort + Distance Vector):
// 1. Perform a Topological Sort of the graph.
// 2. Initialize distance[] with INF, set distance[source] = 0.
// 3. Process nodes in topological order:
//      - For each node u, relax all edges (u -> v) with weight w.
//      - If distance[u] + w < distance[v], update distance[v].
// 4. After processing, distance[] contains shortest paths from source.
//
// Complexity Analysis:
// - Time: O(V + E), since we do a topo sort (O(V+E)) and relax each edge once.
// - Space: O(V + E), for adjacency list and distance array.
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges, int src)
    {
        // Build adjacency list: adj[u] = {v, w}
        vector<vector<pair<int, int>>> adj(V);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w });
        }

        // Step 1: Topological Sort using DFS
        vector<bool> visited(V, false);
        stack<int> st;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topoDFS(i, visited, st, adj);
            }
        }

        // Step 2: Initialize distances
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Step 3: Process nodes in topological order
        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (dist[u] != INT_MAX) {
                for (auto& [v, w] : adj[u]) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        // Replace INF with -1 (unreachable)
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) dist[i] = -1;
        }

        return dist;
    }

private:
    void topoDFS(int node, vector<bool>& visited, stack<int>& st,
        vector<vector<pair<int, int>>>& adj)
    {
        visited[node] = true;
        for (auto& [v, w] : adj[node]) {
            if (!visited[v]) {
                topoDFS(v, visited, st, adj);
            }
        }
        st.push(node);
    }
};

//==============================================================================
// Example Usage:
// Input: V = 6, edges = {{0,1,2}, {0,4,1}, {4,5,4}, {4,2,2}, {1,2,3}, {2,3,6}},
//        src = 0
// Output: [0, 2, 3, 9, 1, 5]
// Explanation: Shortest distances from node 0 to all others.
//==============================================================================

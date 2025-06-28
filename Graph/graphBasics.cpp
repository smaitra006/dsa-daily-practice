#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================
 *                          GRAPH BASICS
 * ============================================================
 *
 * Graph: A collection of nodes (vertices) and edges.
 *
 * - Directed Graph: Edges have direction (A → B).
 * - Undirected Graph: Edges do not have direction (A — B).
 *
 * - Cycle: A path that starts and ends at the same vertex.
 * - Path: A sequence of adjacent vertices connected by edges.
 *         (In simple paths, nodes don’t repeat)
 *
 * - Degree:
 *     * Undirected: deg(v) = number of adjacent vertices.
 *     * Directed:
 *         - In-degree: Number of incoming edges.
 *         - Out-degree: Number of outgoing edges.
 *
 * - Weighted Graph: Edges have weights/costs. If not mentioned, assume weight = 1.
 *
 * - Representations:
 *     * Adjacency Matrix: 2D array (n x n), space O(n²)
 *     * Adjacency List: Array of lists/vectors, space O(n + m)
 *
 * - Connected Components:
 *     Use DFS/BFS from every unvisited node to count total components.
 *
 * - Traversal:
 *     * DFS: Depth First Search
 *     * BFS: Breadth First Search
 */

/* ============================================================
 *        ADJACENCY MATRIX REPRESENTATION (Undirected)
 * ============================================================ */
void createAdjMatrix(int n, int m, vector<vector<int>>& adj) {
    cout << "Enter " << m << " edges (u v):\n";
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}

 /* ============================================================
 *        ADJACENCY LIST REPRESENTATION (Undirected)
 * ============================================================ */
void createAdjList(int n, int m, vector<vector<int>>& adj) {
    cout << "Enter " << m << " edges (u v):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // omit for directed graph
    }
}

/* ============================================================
 *                   DFS TRAVERSAL
 * ============================================================ */
// Time: O(N + M), Space: O(N)
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    cout << node << " ";
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor])
            dfs(neighbor, adj, visited);
    }
}

/* ============================================================
 *                   BFS TRAVERSAL
 * ============================================================ */
// Time: O(N + M), Space: O(N)
void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

/* ============================================================
 *               CONNECTED COMPONENTS COUNT
 * ============================================================ */
int countConnectedComponents(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    int components = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            components++;
            dfs(i, adj, visited);  // can also use BFS
            cout << endl;
        }
    }

    return components;
}



int main() {

    return 0;
}

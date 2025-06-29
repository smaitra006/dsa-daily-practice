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
    visited[node] = true; // We got the node so mark it visited
    // Traverse all the neighbours of the node
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) // If this neighbour is not visited
            dfs(neighbor, adj, visited); // We go the depth of this neighbour
    }
}

/* ============================================================
 *                   BFS TRAVERSAL
 * ============================================================ */
// Time: O(N + M), Space: O(N)
void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start); // Push the first node
    visited[start] = true; // Mark first node as visited

    while (!q.empty()) {
        int node = q.front(); // Take out a node
        q.pop();
        cout << node << " "; // Print it
        // Traverse all neighbours of node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) { // If the neighbour is not visited
                visited[neighbor] = true; // Mark it as visited
                q.push(neighbor); // Push that into the queue to be popped later
            }
        }
    }
}

/* ============================================================
 *               CONNECTED COMPONENTS COUNT
 * ============================================================ */
// Time: O(N + (V + 2*E)) -> O(N), Space: O(N)
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

/* =====================================================================
 * PROBLEM XX: DETECT CYCLE IN AN UNDIRECTED GRAPH (DFS APPROACH)
 * ===================================================================== */

/**
 * @brief Check whether a given undirected graph contains a cycle
 *
 * PROBLEM STATEMENT:
 * Given an undirected graph represented using an adjacency list,
 * check if there is any cycle in the graph.
 *
 * The graph may be disconnected, so check all components.
 *
 * EXAMPLE:
 * Input:
 *   n = 5 (nodes are 0 to 4)
 *   edges = {{0,1}, {1,2}, {2,0}, {3,4}}
 * Output: true (cycle exists among 0-1-2)
 *
 * APPROACH:
 * - Use DFS to traverse the graph.
 * - Maintain a visited array.
 * - Pass the parent of the current node in the DFS.
 * - If a visited neighbor is found and it is not the parent → cycle exists.
 *
 * @param adj Adjacency list of the graph
 * @param n Number of nodes (0-based index)
 * @return true if cycle exists, false otherwise
 *
 * @complexity
 * Time: O(N + M) - N = number of nodes, M = number of edges
 * Space: O(N) - visited array + recursion stack
 */

 class Solution {
    public:
        // DFS helper function to detect cycle
        bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
            visited[node] = true;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    if (dfs(neighbor, node, adj, visited)) {
                        return true;
                    }
                } else if (neighbor != parent) {
                    // A visited neighbor not equal to parent means a cycle
                    return true;
                }
            }

            return false;
        }

        // Check all components for cycles
        bool hasCycle(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    if (dfs(node, -1, adj, visited)) {
                        return true;
                    }
                }
            }

            return false;
        }
    };

/* ============================================================================
 * PROBLEM XX: DETECT CYCLE IN AN UNDIRECTED GRAPH USING BFS
 * ============================================================================ */

/**
 * @brief Check whether an undirected graph contains a cycle using BFS
 *
 * PROBLEM STATEMENT:
 * Given an undirected graph represented as an adjacency list, check if
 * the graph contains any cycle.
 *
 * EXAMPLE:
 * Input:
 *   n = 4
 *   edges = {{0,1}, {1,2}, {2,0}, {2,3}}
 * Output: true
 *
 * APPROACH:
 * - Use BFS to traverse the graph.
 * - Track visited nodes and their parent nodes.
 * - If a visited neighbor is encountered that is not the parent, a cycle exists.
 *
 * @param adj Adjacency list of the graph
 * @param n Number of nodes (0-based index)
 * @return true if cycle exists, false otherwise
 *
 * @complexity
 * Time: O(N + M) - N = nodes, M = edges
 * Space: O(N) - visited array + queue
 */

 class Solution {
    public:
        // BFS helper to detect cycle from a starting node
        bool bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
            queue<pair<int, int>> q; // {node, parent}
            visited[start] = true;
            q.push({start, -1});

            while (!q.empty()) {
                auto [node, parent] = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, node});
                    } else if (neighbor != parent) {
                        // Already visited and not the parent ⇒ cycle
                        return true;
                    }
                }
            }

            return false;
        }

        // Check all components for cycles
        bool hasCycle(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    if (bfs(node, adj, visited)) {
                        return true;
                    }
                }
            }

            return false;
        }
    };



int main() {

    return 0;
}

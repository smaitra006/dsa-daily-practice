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
void dfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[start] = true;
    cout << start << " ";
    for(auto neighbour : adj[start]) {
        if(!visited[neighbour]) {
            dfs(neighbour, adj, visited);
        }
    }
}

// Callinf function for bfs -> We do it so that we handle the case of components
void callDFS(int start, vector<vector<int>>adj) {
    int n = adj.size();
    vector<bool> visited(n + 1, false); // Made (n + 1) so that 1-basec indexing is also supported
    for(int i = 1; i < n + 1; i++) { // This is for 1-based indexing case
        if(!visited[i]) {
            dfs(i, adj, visited);
        }
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

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for(auto neighbour : adj[node]) {
            if(!visited[neighbour]) {
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

// Callinf function for bfs -> We do it so that we handle the case of components
void callBFS(int start, vector<vector<int>>adj) {
    int n = adj.size();
    vector<bool> visited(n + 1, false); // Made (n + 1) so that 1-basec indexing is also supported
    for(int i = 0; i < n; i++) { // This is for 0-based indexing case
        if(!visited[i]) {
            bfs(i, adj, visited);
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
        // DFS helper function to detect cycle
        bool dfsHelper(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
            visited[node] = true;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    if (dfsHelper(neighbor, node, adj, visited)) {
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
        bool hasCycleDFS(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    if (dfsHelper(node, -1, adj, visited)) {
                        return true;
                    }
                }
            }

            return false;
        }

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
        // BFS helper to detect cycle from a starting node
        bool bfsHelper(int start, vector<vector<int>>& adj, vector<bool>& visited) {
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
        bool hasCycleBFS(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    if (bfsHelper(node, adj, visited)) {
                        return true;
                    }
                }
            }

            return false;
        }

/* ===================================================================
 * PROBLEM: NUMBER OF DISTINCT ISLANDS (Leetcode Premium)
 * =================================================================== */
/**
 * @brief Count number of distinct islands based on their shape
 *
 * APPROACH:
 * - Traverse the grid using DFS.
 * - For each island, record the relative path taken from the origin (e.g., "D", "U", "L", "R", "B").
 * - Store each unique path in a set to count distinct shapes.
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n) for visited + path recording
 */

 void numDistinctIslandsDFS(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited, string& path, char dir) {
    int m = grid.size();
    int n = grid[0].size();

    if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || grid[i][j] == 0)
        return;

    visited[i][j] = true;
    path += dir;  // record direction of movement

    // Explore in all 4 directions
    numDistinctIslandsDFS(i + 1, j, grid, visited, path, 'D');  // Down
    numDistinctIslandsDFS(i - 1, j, grid, visited, path, 'U');  // Up
    numDistinctIslandsDFS(i, j + 1, grid, visited, path, 'R');  // Right
    numDistinctIslandsDFS(i, j - 1, grid, visited, path, 'L');  // Left

    path += 'B';  // Backtrack marker (to differentiate shapes)
}

int numDistinctIslands(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    set<string> shapes;
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                string path = "";
                numDistinctIslandsDFS(i, j, grid, visited, path, 'S');  // 'S' = Start
                shapes.insert(path);
            }
        }
    }

    return shapes.size();
}

/* ===================================================================
 * PROBLEM: DETECT CYCLE IN DIRECTED GRAPH (DFS + PATH VISITED)
 * =================================================================== */

/**
 * @brief Detect whether there is a cycle in a directed graph using DFS
 *
 * PROBLEM STATEMENT:
 * Given a directed graph represented as an adjacency list, determine if the
 * graph contains any cycles.
 *
 * A cycle exists if during a DFS traversal, we visit a node that is already
 * in the current recursion path (i.e., visited but not yet fully processed).
 *
 * APPROACH:
 * - Use two vectors:
 *   → `visited` marks whether a node has ever been visited.
 *   → `pathVisited` marks whether the node is in the current recursion path.
 * - If during DFS, we encounter a neighbor that's visited **and** also in the
 *   current path (`pathVisited`), we found a cycle.
 *
 * @param graph Adjacency list representation of the graph
 * @return true if the graph has a cycle, false otherwise
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) - for visited and recursion stack
 */

bool hasCycleDFS(int node, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& pathVisited) {
    visited[node] = true;
    pathVisited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (hasCycleDFS(neighbor, graph, visited, pathVisited)) {
                return true;
            }
        } else if (pathVisited[neighbor]) {
            // Found a back edge → cycle exists
            return true;
        }
    }

    pathVisited[node] = false; // Backtrack
    return false;
}

bool hasCycle(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> pathVisited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycleDFS(i, graph, visited, pathVisited)) {
                return true;
            }
        }
    }

    return false;
}

/* ================================================================
 * GRAPH ALGORITHM: TOPOLOGICAL SORT USING DFS
 * ================================================================ */

/*
 * TOPOLOGICAL SORT:
 * - A linear ordering of vertices such that for every directed edge u → v,
 *   vertex `u` comes before `v` in the ordering.
 * - Only valid for **Directed Acyclic Graphs (DAGs)**.
 *
 * USE CASES:
 * - Course scheduling
 * - Build systems (compile order)
 * - Task dependency resolution
 *
 * KEY IDEA (DFS APPROACH):
 * - Run DFS on unvisited nodes
 * - After visiting all neighbors of a node, push the node onto a stack
 * - Finally, reverse the stack to get topological order
 *
 * TIME COMPLEXITY: O(V + E)
 * SPACE COMPLEXITY: O(V) for visited and recursion stack
 */

 // Topological Sort using DFS
 void topologicalSortDFS(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
     visited[node] = true;

     for (int neighbor : adj[node]) {
         if (!visited[neighbor]) {
            topologicalSortDFS(neighbor, adj, visited, st);
         }
     }

     st.push(node); // Push after exploring all neighbors. u -> v1 -> v2, here goes v2, v1, u. so that while popping from stack we get u, v1, v2.
 }

 vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
     vector<bool> visited(V, false);
     stack<int> st;

     // Call DFS for all unvisited nodes
     for (int i = 0; i < V; i++) {
         if (!visited[i]) {
            topologicalSortDFS(i, adj, visited, st);
         }
     }

     // Pop elements to get topological order
     vector<int> topo;
     while (!st.empty()) {
         topo.push_back(st.top());
         st.pop();
     }

     return topo;
 }

 /* ================================================================
 * GRAPH ALGORITHM: TOPOLOGICAL SORT USING KAHN'S ALGORITHM (BFS)
 * ================================================================ */

/*
 * TOPOLOGICAL SORT (BFS - KAHN'S ALGORITHM):
 * - A linear ordering of vertices such that for every directed edge u → v,
 *   vertex `u` comes before `v` in the ordering.
 * - Only valid for **Directed Acyclic Graphs (DAGs)**.
 *
 * APPROACH (KAHN’S ALGORITHM - BFS):
 * 1. Compute indegree (number of incoming edges) for each node.
 * 2. Add all nodes with indegree 0 to a queue.
 * 3. Pop from queue → add to result → reduce indegree of neighbors.
 * 4. If neighbor’s indegree becomes 0, add to queue.
 * 5. Repeat until queue is empty.
 *
 * If the final result size < V → graph has a cycle (not a DAG).
 *
 * TIME COMPLEXITY: O(V + E)
 * SPACE COMPLEXITY: O(V) for indegree, queue, and result
 */

// Topological Sort using Kahn's Algorithm (BFS)
vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    vector<int> topo;
    queue<int> q;

    // Step 1: Compute indegree of each node
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    // Step 2: Push nodes with 0 indegree to queue
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 3: BFS traversal
    while (!q.empty()) {
        int node = q.front(); q.pop();
        topo.push_back(node);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Step 4: If topo size != V, cycle exists
    if (topo.size() < V) {
        cout << "Graph has a cycle (not a DAG)\n";
        return {};
    }

    return topo;
}



int main() {

    return 0;
}

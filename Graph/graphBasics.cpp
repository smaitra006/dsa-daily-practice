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

/* ================================================================
 * DISJOINT SET UNION (DSU) - UNION BY RANK + PATH COMPRESSION
 * ================================================================ */

/*
 * CONCEPT:
 * - DSU (or Union-Find) is a data structure to efficiently manage
 *   disjoint sets and perform operations like:
 *     → Check if two elements are in the same set
 *     → Merge two sets
 *
 * OPTIMIZED WITH:
 * - Path Compression → Flattens the tree during `find`
 * - Union by Rank → Attach lower-rank tree under higher-rank one
 *
 * COMMON USES:
 * - Kruskal’s MST
 * - Cycle detection in undirected graphs
 * - Dynamic connectivity
 *
 * TIME COMPLEXITY: O(α(n)) per operation (inverse Ackermann function, almost constant)
 * SPACE COMPLEXITY: O(n)
 */

 class DSU {
 private:
     vector<int> parent;
     vector<int> rank;

 public:
     // Constructor to initialize DSU with n nodes (0 to n-1)
     DSU(int n) {
         parent.resize(n);
         rank.resize(n, 0); // Rank starts as 0
         for(int i = 0; i < n; i++) {
             parent[i] = i; // Initially, each node is its own parent
         }
     }

     // Find with Path Compression
     int findParent(int node) {
         if (parent[node] == node)
             return node;
         return parent[node] = findParent(parent[node]);
     }

     // Union by Rank
     bool unionByRank(int u, int v) {
         int pu = findParent(u);
         int pv = findParent(v);

         if (pu == pv) return false; // Same set, no need to union

         // Attach lower-rank tree under higher-rank tree
         if (rank[pu] < rank[pv]) {
             parent[pu] = pv;
         } else if (rank[pv] < rank[pu]) {
             parent[pv] = pu;
         } else {
             parent[pv] = pu;
             rank[pu]++; // Increase rank only if both are equal
         }
         return true; // sucessful union
     }

     // Optional: Check if two nodes are connected
     bool isConnected(int u, int v) {
         return findParent(u) == findParent(v);
     }

     /*
    * FUNCTION: detectCycle
    * ----------------------
    * @param n    → Number of vertices (0-indexed)
    * @param edges → Vector of edges (undirected)
    * @return true if a cycle exists, false otherwise
    */
   bool detectCycle(int n, vector<pair<int, int>>& edges) {
        DSU dsu(n);

        for(auto [u, v] : edges) {
            if(!unionByRank(u, v)) {
                return true; // Cycle detected
            }
        }

        return false; // No cycles found
    }
 };

/* =============================================================================
 * ALGORITHM: DIJKSTRA’S SHORTEST PATH ALGORITHM (Single Source)
 * ============================================================================= */

/**
 * @brief Find the shortest distance from the source node to all other nodes in a weighted graph.
 *
 * PROBLEM STATEMENT:
 * Given a weighted graph with `n` vertices and non-negative edge weights,
 * Dijkstra’s algorithm finds the shortest distance from a given source node
 * to all other nodes.
 *
 * APPLICABLE FOR:
 * - Graphs with non-negative weights
 * - Single source shortest path problem
 *
 * NOT FOR:
 * - Graphs with negative weight edges (Use Bellman-Ford instead)
 *
 * EXAMPLE:
 * Input:
 * n = 5, source = 0
 * adj = {
 *   { {1, 2}, {2, 4} },   // node 0 has edges to 1 (weight 2) and 2 (weight 4)
 *   { {2, 1}, {3, 7} },
 *   { {4, 3} },
 *   { {4, 1} },
 *   {}
 * }
 * Output: [0, 2, 3, 9, 6]
 *
 * APPROACH:
 * - Initialize all distances to INF except source node as 0.
 * - Use a min-heap (priority queue) to always expand the node with the smallest distance.
 * - For each neighbor of current node, update its distance if a shorter path is found.
 *
 * @complexity
 * Time: O((V + E) * log V) using min-heap
 * Space: O(V) for distance array + O(V) for priority queue
 */

 class Solution {
    public:
        vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int source) {
            // Step 1: Distance array initialized to infinity
            vector<int> dist(V, INT_MAX);
            dist[source] = 0;

            // Step 2: Min-heap to store {distance, node}
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            pq.push({0, source}); // {distance, node}

            // Step 3: BFS-like traversal using priority queue
            while (!pq.empty()) { // TC -> V
                int currDist = pq.top().first;
                int node = pq.top().second;
                pq.pop(); // TC -> log(V)

                for (auto neighbor : adj[node]) { // TC -> E
                    int adjNode = neighbor.first;
                    int weight = neighbor.second;

                    // Relaxation step
                    if (currDist + weight < dist[adjNode]) {
                        dist[adjNode] = currDist + weight;
                        pq.push({dist[adjNode], adjNode}); // TC -> log(V)
                    }
                }
            }

            return dist;
        }
    };

/* =============================================================================
 * ALGORITHM: DIJKSTRA’S SHORTEST PATH ALGORITHM using SET
 * ============================================================================= */

/**
 * @brief Find the shortest distance from the source node to all other nodes in a weighted graph.
 *
 * PROBLEM STATEMENT:
 * Given a weighted graph with `n` vertices and non-negative edge weights,
 * Dijkstra’s algorithm finds the shortest distance from a given source node
 * to all other nodes.
 *
 * This version uses a `set` to maintain a sorted order of {distance, node} pairs.
 * Unlike a priority_queue, a set allows easy updates (erase+insert) of distances.
 *
 * APPLICABLE FOR:
 * - Graphs with non-negative weights
 * - Single source shortest path problem
 *
 * NOT FOR:
 * - Graphs with negative weight edges (Use Bellman-Ford instead)
 *
 * EXAMPLE:
 * Input:
 * n = 5, source = 0
 * adj = {
 *   { {1, 2}, {2, 4} },
 *   { {2, 1}, {3, 7} },
 *   { {4, 3} },
 *   { {4, 1} },
 *   {}
 * }
 * Output: [0, 2, 3, 9, 6]
 *
 * APPROACH:
 * - Initialize all distances to INF except source node as 0.
 * - Use a `set` to always pick the node with the smallest distance.
 * - For each neighbor, if a better path is found, update distance and set.
 *
 * @complexity
 * Time: O(E * log V) using set
 * Space: O(V + E)
 */

 class Solution {
    public:
        vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int source) {
            // Step 1: Distance array initialized to infinity
            vector<int> dist(V, INT_MAX);
            dist[source] = 0;

            // Step 2: Set stores pairs of {distance, node}
            set<pair<int, int>> st;
            st.insert({0, source});

            // Step 3: Traverse
            while (!st.empty()) {
                auto top = *st.begin();
                st.erase(st.begin());

                int currDist = top.first;
                int node = top.second;

                for (auto neighbor : adj[node]) {
                    int adjNode = neighbor.first;
                    int weight = neighbor.second;

                    // Relaxation: If better distance is found
                    if (currDist + weight < dist[adjNode]) {
                        // If node already exists with older distance, erase it
                        if (dist[adjNode] != INT_MAX) {
                            st.erase({dist[adjNode], adjNode});
                        }

                        // Update new distance and insert
                        dist[adjNode] = currDist + weight;
                        st.insert({dist[adjNode], adjNode});
                    }
                }
            }

            return dist;
        }
    };

/* ===================================================================
 * PROBLEM: SHORTEST PATH IN WEIGHTED UNDIRECTED GRAPH
 * =================================================================== */

/**
 * @brief Find shortest distances and actual shortest paths from source
 *
 * PROBLEM STATEMENT:
 * Given an undirected, weighted graph with `n` nodes (0 to n-1) and edges,
 * find the shortest distance and actual path from source node `src` to every node.
 *
 * INPUT:
 * - `n`: number of nodes
 * - `adj`: adjacency list of pairs {neighbor, weight}
 * - `src`: source node
 *
 * OUTPUT:
 * - Pair of:
 *   → `dist`: vector<int> of shortest distances from src
 *   → `paths`: vector<vector<int>> of actual shortest paths from src
 *
 * APPROACH:
 * - Use Dijkstra's algorithm with a min-heap (priority queue).
 * - Track parent nodes to reconstruct paths.
 *
 * COMPLEXITY:
 * - Time: O((V + E) * log V)
 * - Space: O(V + E)
 */

 pair<vector<int>, vector<vector<int>>> dijkstraWithPaths(int n, vector<vector<pair<int, int>>>& adj, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n);  // To track shortest path
    vector<vector<int>> paths(n); // To store the actual paths

    // Initialization
    for (int i = 0; i < n; i++) parent[i] = i;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        for (auto [neighbor, wt] : adj[node]) {
            if (dist[neighbor] > d + wt) {
                dist[neighbor] = d + wt;
                pq.push({dist[neighbor], neighbor});
                parent[neighbor] = node;
            }
        }
    }

    // Path Reconstruction
    for (int i = 0; i < n; i++) {
        vector<int> path;
        int curr = i;
        while (parent[curr] != curr) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        paths[i] = path;
    }

    return {dist, paths};
}

/* ===================================================================
 * PROBLEM: SHORTEST PATH IN WEIGHTED DIRECTED GRAPH (WITH NEGATIVE WEIGHTS)
 * =================================================================== */

// BELLMAN FORD ALGORITHM

/**
 * @brief Find shortest distances from source node to all other nodes
 *
 * PROBLEM STATEMENT:
 * Given a directed graph with `n` nodes (0 to n-1) and `m` weighted edges,
 * some of which may have **negative weights**, compute the shortest path
 * from a source node `src` to all other nodes.
 *
 * Bellman-Ford can detect **negative weight cycles** as well.
 *
 * Input:
 * - Number of nodes `n`
 * - Edges represented as (u, v, wt)
 * - Source node `src`
 *
 * Output:
 * - Vector `dist[]` of size `n`, where dist[i] = shortest distance from `src` to node `i`
 *   If a negative weight cycle is detected, return {-1}
 *
 * ALGORITHM (Bellman-Ford):
 * - Initialize distances from `src` to all nodes as ∞, except dist[src] = 0
 * - Relax all edges (u, v, wt) for (n - 1) times
 * - Check for negative weight cycle in one extra iteration
 *
 * COMPLEXITY:
 * - Time: O(V * E)
 * - Space: O(V)
 */

 vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    // Relax all edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Check for negative weight cycle
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            return { -1 }; // Negative weight cycle detected
        }
    }

    return dist;
}

/* ===================================================================
 * PROBLEM: ALL PAIRS SHORTEST PATH IN WEIGHTED GRAPH
 * =================================================================== */

// FLOYD WARSHALL ALGORITHM

/**
 * @brief Compute shortest distances between all pairs of nodes
 *
 * PROBLEM STATEMENT:
 * Given a directed graph with `n` nodes (0 to n-1) and weighted edges,
 * compute the shortest distances between every pair of nodes.
 *
 * The graph may contain negative weight edges, but must **not** have any
 * negative weight cycles.
 *
 * Input:
 * - Number of nodes `n`
 * - Adjacency matrix `dist[n][n]` where:
 *   - dist[i][j] = weight of edge i → j
 *   - If no edge exists, use `1e9` (or any large constant representing ∞)
 *
 * Output:
 * - Updated matrix `dist[n][n]` where dist[i][j] = shortest distance from i to j
 *
 * ALGORITHM (Floyd-Warshall):
 * - Try every node `k` as an intermediate node
 * - For all pairs (i, j), update:
 *     dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *
 * DETECTING NEGATIVE WEIGHT CYCLE:
 * - After running the algorithm, if dist[i][i] < 0 for any `i`,
 *   a negative weight cycle exists.
 *
 * COMPLEXITY:
 * - Time: O(V^3)
 * - Space: O(V^2)
 */

 void floydWarshall(vector<vector<int>>& dist, int n) {
    const int INF = 1e9;

    // Main triple loop
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Optional: Detect negative weight cycles
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            // Negative weight cycle exists
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }
}

/* ===================================================================
 * PROBLEM: MINIMUM SPANNING TREE (MST) USING PRIM'S ALGORITHM
 * =================================================================== */

/**
 * @brief Find the minimum cost to connect all nodes in an undirected, weighted graph
 *
 * PROBLEM STATEMENT:
 * Given an undirected graph with `n` nodes (0 to n-1) and weighted edges,
 * find the weight of the **Minimum Spanning Tree (MST)**.
 *
 * Input:
 * - Number of nodes `n`
 * - Adjacency list `adj[]` where:
 *   adj[u] = vector of pairs {v, wt} representing an edge u — v with weight wt
 *
 * Output:
 * - Integer `minCost` representing the total weight of the MST
 *
 * ALGORITHM (Prim's using Min-Heap):
 * - Start from any node (usually node 0)
 * - Use a priority queue to always pick the minimum weight edge
 * - Maintain a visited array to avoid cycles
 * - Add the edge to MST if it connects a new node
 *
 * COMPLEXITY:
 * - Time: O(E * log V) using Min-Heap
 * - Space: O(V + E)
 */

 int primsMST(int n, vector<vector<pair<int, int>>>& adj) {
    // Min-heap: {weight, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<bool> inMST(n, false); // To mark included nodes
    int minCost = 0;

    // Start from node 0
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [wt, u] = pq.top();
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        minCost += wt;

        // Traverse neighbors
        for (auto [v, w] : adj[u]) {
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }

    return minCost;
}

/* ===================================================================
 * TOPIC: KRUSKAL'S ALGORITHM (Minimum Spanning Tree - MST)
 * =================================================================== */

/**
 * @brief Find the Minimum Spanning Tree (MST) of a connected, undirected,
 *        and weighted graph using Kruskal's algorithm.
 *
 * PROBLEM STATEMENT:
 * Given a graph with `V` nodes and `E` weighted edges,
 * find a subset of edges that connects all vertices (spanning tree),
 * and the sum of edge weights is minimized.
 *
 * Kruskal's algorithm is **greedy**, always picking the minimum weight edge
 * that does **not** form a cycle (using Union-Find to detect cycles).
 *
 * INPUT:
 * - Integer `n`: Number of nodes (0-indexed or 1-indexed)
 * - vector<vector<int>> edges: List of edges {u, v, weight}
 *
 * OUTPUT:
 * - Integer: Total weight of the Minimum Spanning Tree
 *
 * ALGORITHM:
 * 1. Sort all edges in ascending order of weights
 * 2. Initialize Disjoint Set Union (Union-Find) for cycle detection
 * 3. Traverse sorted edges:
 *    - If the edge connects two different components, add it to MST
 *    - Merge the two components using union operation
 * 4. Stop when MST contains (V - 1) edges
 *
 * COMPLEXITY:
 * - Time: O(E * log E) for sorting + union-find operations
 * - Space: O(V) for DSU data structures
 */

class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int node)
    {
        if (parent[node] != node)
        {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    // Union by rank
    bool unionSets(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return false;

        if (rank[pu] < rank[pv])
        {
            parent[pu] = pv;
        }
        else if (rank[pu] > rank[pv])
        {
            parent[pv] = pu;
        }
        else
        {
            parent[pu] = pv;
            rank[pv]++;
        }

        return true;
    }
};

class Solution
{
public:
    /**
     * @brief Kruskal's algorithm implementation
     * @param n: number of nodes
     * @param edges: list of {u, v, weight}
     * @return total weight of MST
     */
    int kruskalMST(int n, vector<vector<int>> &edges)
    {
        // Step 1: Sort edges by weight
        sort(edges.begin(), edges.end(), [](auto &a, auto &b)
             { return a[2] < b[2]; });

        DSU dsu(n);
        int mstWeight = 0;
        int edgesUsed = 0;

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            // If u and v are in different components
            if (dsu.unionSets(u, v))
            {
                mstWeight += wt;
                edgesUsed++;
                if (edgesUsed == n - 1)
                    break;
            }
        }

        return mstWeight;
    }
};

/* ===================================================================
 * TOPIC: STRONGLY CONNECTED COMPONENTS (Kosaraju's Algorithm)
 * =================================================================== */

/**
 * @brief Identify Strongly Connected Components (SCCs) in a directed graph
 *
 * DEFINITION:
 * A **Strongly Connected Component (SCC)** is a maximal subgraph of a directed graph
 * where every node is reachable from every other node in that subgraph.
 *
 * PROBLEM:
 * Given a directed graph with `V` vertices and `E` edges,
 * return the number of strongly connected components.
 *
 * APPLICATIONS:
 * - Optimizing compilers (function/module dependencies)
 * - Social networks (mutual follower clusters)
 * - Circuit analysis (feedback loops)
 * - Web page link analysis (PageRank)
 *
 * ALGORITHM: KOSARAJU'S ALGORITHM (3 steps)
 * 1. Do DFS and push nodes onto a stack (in postorder, i.e., finish time)
 * 2. Reverse the entire graph
 * 3. Pop nodes from the stack, and do DFS on reversed graph to find components
 *
 * COMPLEXITY:
 * - Time: O(V + E)
 * - Space: O(V + E)
 */

class Solution
{
public:
    /**
     * Step 1: DFS to fill stack in post-order
     */
    void dfs1(int node, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
    {
        visited[node] = true;

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                dfs1(neighbor, adj, visited, st);
            }
        }

        st.push(node); // Post-order push
    }

    /**
     * Step 2: DFS on the transposed graph
     */
    void dfs2(int node, vector<vector<int>> &revAdj, vector<bool> &visited)
    {
        visited[node] = true;

        for (int neighbor : revAdj[node])
        {
            if (!visited[neighbor])
            {
                dfs2(neighbor, revAdj, visited);
            }
        }
    }

    /**
     * @brief Main function to compute number of strongly connected components
     */
    int kosarajuSCC(int V, vector<vector<int>> &adj)
    {
        stack<int> st;
        vector<bool> visited(V, false);

        // Step 1: Do a DFS and fill stack with vertices by finish time
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs1(i, adj, visited, st);
            }
        }

        // Step 2: Reverse the graph
        vector<vector<int>> revAdj(V);
        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                revAdj[v].push_back(u); // Reverse the edge
            }
        }

        // Step 3: Process all nodes in reverse postorder (stack) and count SCCs
        fill(visited.begin(), visited.end(), false);
        int count = 0;

        while (!st.empty())
        {
            int node = st.top();
            st.pop();

            if (!visited[node])
            {
                dfs2(node, revAdj, visited);
                count++;
            }
        }

        return count; // Number of strongly connected components
    }
};

int main() {

    return 0;
}

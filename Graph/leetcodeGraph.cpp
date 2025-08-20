// LeetCode questions on Graph
#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 733: FLOOD FILL (LeetCode)
 * =================================================================== */

/**
 * @brief Perform flood fill on a 2D image starting from (sr, sc)
 *
 * PROBLEM STATEMENT:
 * You are given an image (2D grid) where each pixel has an integer value.
 * A pixel is connected 4-directionally to its adjacent pixels.
 * Starting from pixel (sr, sc), change its color and all connected pixels
 * of the same original color to a new color.
 *
 * EXAMPLE:
 * Input:
 *   image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
 * Output:
 *   [[2,2,2],[2,2,0],[2,0,1]]
 *
 * APPROACH:
 * - Use DFS to visit all pixels connected to the start pixel that have the same color.
 * - Mark visited to avoid reprocessing.
 * - Change color during the traversal.
 *
 * @param image 2D grid of pixel values
 * @param sr Start row index
 * @param sc Start column index
 * @param color Target color to apply
 * @return Modified image after flood fill
 *
 * @complexity
 * Time: O(m * n) - in worst case all pixels are visited
 * Space: O(m * n) - visited array + recursion stack
 */

class Solution
{
public:
    bool bfs(int start, vector<vector<int>> &adj, vector<bool> &visited)
    {
        queue<pair<int, int>> q; // {node, parent}
        visited[start] = true;
        q.push({start, -1});

        while (!q.empty())
        {
            pair<int, int> curr = q.front();
            q.pop();
            int node = curr.first;
            int parent = curr.second;

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push({neighbor, node});
                }
                else if (neighbor != parent)
                {
                    return true; // Cycle found
                }
            }
        }

        return false;
    }

    bool hasCycle(int n, vector<vector<int>> &adj)
    {
        vector<bool> visited(n, false);

        for (int node = 0; node < n; node++)
        {
            if (!visited[node])
            {
                if (bfs(node, adj, visited))
                    return true;
            }
        }

        return false;
    }
};


/* ========================================================================
 * PROBLEM 785: IS GRAPH BIPARTITE? (LeetCode)
 * ======================================================================== */

/**
 * @brief Check if the given graph is bipartite using DFS
 *
 * PROBLEM STATEMENT:
 * Given an undirected graph represented as an adjacency list,
 * determine whether it is bipartite. A graph is bipartite if the nodes
 * can be divided into two sets such that no two nodes within the same
 * set are adjacent.
 *
 * EXAMPLE:
 * Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
 * Output: false
 *
 * @param graph Adjacency list of the graph
 * @return true if the graph is bipartite, false otherwise
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) - for color/visited array and recursion stack
 */

// ====================== DFS APPROACH ======================

class Solution
{
public:
    bool dfs(vector<vector<int>> &graph, int node, vector<int> &color, int currColor)
    {
        color[node] = currColor;

        for (auto neighbour : graph[node])
        {
            if (color[node] == color[neighbour])
            {
                return false;
            }
            if (color[neighbour] == -1)
            {
                if (dfs(graph, neighbour, color, 1 - currColor) == false)
                { // If its 1 it becomes 0 and if its 0 then it becomes 1
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>> &graph)
    {
        // make the color
        int n = graph.size();
        vector<int> color(n, -1); // This will also work as visited array

        // color0 = 0, color1 = 1;

        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                if (dfs(graph, i, color, 0) == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

// ====================== BFS APPROACH ======================

/**
 * @brief Check if the given graph is bipartite using BFS
 *
 * @param graph Adjacency list of the graph
 * @return true if the graph is bipartite, false otherwise
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) - for color array and queue
 */

class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> color(n, -1); // -1 = unvisited

        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                queue<int> q;
                q.push(i);
                color[i] = 0;

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : graph[node])
                    {
                        if (color[neighbor] == -1)
                        {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        }
                        else if (color[neighbor] == color[node])
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

/* ===================================================================
 * PROBLEM 802: FIND EVENTUAL SAFE STATES (LeetCode)
 * =================================================================== */

/**
 * @brief Return all eventual safe nodes in a directed graph using DFS
 *
 * PROBLEM STATEMENT:
 * A node is called **eventually safe** if every possible path starting from
 * that node leads to a terminal node (i.e., a node with no outgoing edges).
 *
 * Given a directed graph represented as an adjacency list, return a sorted list
 * of all the **eventual safe nodes**.
 *
 * APPROACH:
 * - Use DFS to detect cycles using `visited` and `pathVisited`.
 * - Nodes involved in cycles or leading to cycles are not safe.
 * - A node is safe if it does not lie on any cycle path.
 *
 * STRATEGY:
 * - If a node is part of a cycle, or leads to one → mark unsafe.
 * - After all DFS calls, nodes not in the current recursion path (pathVisited)
 *   are safe nodes.
 *
 * @param graph Adjacency list of the directed graph
 * @return vector<int> of all safe node indices in sorted order
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) for visited, pathVisited arrays and recursion stack
 */

class Solution
{
public:
    // Helper DFS to detect cycles
    bool hasCycleDFS(vector<vector<int>> &graph, int node,
                     vector<bool> &visited, vector<bool> &pathVisited)
    {
        visited[node] = true;
        pathVisited[node] = true;

        for (int neighbour : graph[node])
        {
            if (!visited[neighbour])
            {
                if (hasCycleDFS(graph, neighbour, visited, pathVisited))
                {
                    return true;
                }
            }
            else if (pathVisited[neighbour])
            {
                // A back edge found → cycle
                return true;
            }
        }

        pathVisited[node] = false; // Backtrack
        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<bool> pathVisited(n, false);
        vector<int> safeNodes;

        // Step 1: DFS on all nodes to find unsafe/cyclic ones
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                hasCycleDFS(graph, i, visited, pathVisited);
            }
        }

        // Step 2: Nodes not part of any cycle are safe
        for (int i = 0; i < n; i++)
        {
            if (pathVisited[i] == false)
            {
                safeNodes.push_back(i);
            }
        }

        return safeNodes;
    }
};

/* ===================================================================
 * PROBLEM 207: COURSE SCHEDULE (LeetCode)
 * =================================================================== */

/**
 * @brief Determine if all courses can be finished (i.e., graph is a DAG)
 *
 * PROBLEM STATEMENT:
 * There are `numCourses` labeled from 0 to numCourses - 1. Some courses have
 * prerequisites in the form [a, b], meaning to take course a, you must first
 * take course b.
 *
 * Return true if it is possible to finish all courses. Otherwise, return false.
 *
 * In graph terms, check if the directed graph formed by prerequisites is a DAG.
 *
 * APPROACH:
 * - Use **Kahn's Algorithm** (Topological Sort using indegree).
 * - Count how many nodes can be processed with zero indegree.
 * - If all nodes are processed → valid DAG → all courses can be finished.
 *
 * STRATEGY:
 * - Build an adjacency list for the graph.
 * - Track indegree of each node.
 * - Use a queue to process nodes with indegree 0.
 * - If the count of processed nodes equals total nodes, return true.
 *
 * @param numCourses Total number of courses (nodes)
 * @param prerequisites List of [a, b] pairs meaning b → a
 * @return true if all courses can be finished, else false
 *
 * @complexity
 * Time: O(V + E) — where V = numCourses, E = prerequisites
 * Space: O(V + E) — for adjacency list and indegree array
 */

class Solution
{
public:
    // Helper function to check if graph is DAG using Kahn's Algorithm
    bool isDAG(vector<vector<int>> &adj, vector<int> &indegree)
    {
        int n = indegree.size();
        int count = 0;
        queue<int> q;

        // Add all nodes with 0 indegree
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // Kahn's Algorithm main loop
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            for (int neighbour : adj[node])
            {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0)
                {
                    q.push(neighbour);
                }
            }
        }

        // If all nodes are processed → graph is a DAG
        return count == n;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        // Build graph and indegree array
        for (const auto &pre : prerequisites)
        {
            int a = pre[0];
            int b = pre[1];
            // b → a (b must be done before a)
            adj[b].push_back(a);
            indegree[a]++;
        }

        return isDAG(adj, indegree);
    }
};

/* ===================================================================
 * PROBLEM 210: COURSE SCHEDULE II (LeetCode)
 * =================================================================== */

/**
 * @brief Return a valid order in which all courses can be completed
 *
 * PROBLEM STATEMENT:
 * You are given the total number of courses `numCourses` and a list of prerequisite pairs.
 * Each pair [a, b] indicates that to take course `a`, you must first take course `b`.
 *
 * Return a possible ordering of courses to finish all courses.
 * If it is not possible to complete all courses (i.e., there’s a cycle), return an empty list.
 *
 * APPROACH:
 * - Use **Kahn’s Algorithm** (Topological Sort using BFS and indegree tracking).
 * - If the topological ordering contains all nodes → return the result.
 * - If not → a cycle exists → return empty list.
 *
 * STRATEGY:
 * 1. Build the adjacency list for the directed graph.
 * 2. Track indegrees for each node.
 * 3. Start from nodes with zero indegree, and process using a queue.
 * 4. Append processed nodes to the topological ordering list.
 *
 * @param numCourses Total number of nodes (courses)
 * @param prerequisites Prerequisite edges [a, b] meaning b → a
 * @return vector<int> A valid ordering of courses or empty vector if cycle exists
 *
 * @complexity
 * Time: O(V + E), where V = numCourses and E = number of prerequisites
 * Space: O(V + E), for adjacency list, indegree array, and queue
 */

class Solution
{
public:
    // Helper function to perform Kahn's Topological Sort
    void topologicalSort(int numCourses, vector<vector<int>> &adj, vector<int> &indegree, vector<int> &topo)
    {
        queue<int> q;

        // Push all nodes with zero indegree into the queue
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // BFS traversal
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Decrease indegree of all adjacent nodes
            for (int neighbour : adj[node])
            {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0)
                {
                    q.push(neighbour);
                }
            }
        }
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adj(numCourses); // Adjacency list
        vector<int> indegree(numCourses, 0); // Indegree array

        // Step 1: Build the graph and populate indegree
        for (const auto &p : prerequisites)
        {
            int a = p[0];
            int b = p[1];
            // Edge: b → a (b must be completed before a)
            adj[b].push_back(a);
            indegree[a]++;
        }

        // Step 2: Perform topological sort
        vector<int> topo;
        topologicalSort(numCourses, adj, indegree, topo);

        // Step 3: If topological sort includes all nodes, return it
        if (topo.size() == numCourses)
        {
            return topo;
        }

        // Cycle detected: return empty vector
        return {};
    }
};

/* ===================================================================
 * PROBLEM 269: ALIEN DICTIONARY (LeetCode)
 * =================================================================== */

/**
 * @brief Determine the order of characters in an alien language
 *
 * PROBLEM STATEMENT:
 * You are given a list of words sorted lexicographically according to the rules
 * of an unknown alien language. You must derive the order of characters in the alien alphabet.
 *
 * If the ordering is invalid (e.g., a prefix appears after its full word), return "".
 * If multiple valid orderings exist, return any one of them.
 *
 * EXAMPLE:
 * Input:  words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * APPROACH:
 * - Build a graph of characters using pairwise comparisons of adjacent words.
 * - If char1 comes before char2 → add edge: char1 → char2.
 * - Use Kahn’s Algorithm (BFS Topological Sort) to determine character order.
 *
 * STRATEGY:
 * 1. Initialize graph (adjacency list) and indegree map.
 * 2. For each pair of adjacent words, compare characters and build edges.
 * 3. Apply topological sort using queue to find valid order.
 * 4. If result length != total unique characters → cycle exists → return "".
 *
 * @param words Vector of words sorted by alien dictionary
 * @return string A valid character order or "" if not possible
 *
 * @complexity
 * Time:  O(N * L), where N = number of words, L = average word length
 * Space: O(1), since alphabet is limited to 26 characters
 */

class Solution
{
public:
    string alienOrder(vector<string> &words)
    {
        unordered_map<char, unordered_set<char>> adj; // adjacency list
        unordered_map<char, int> indegree;            // indegree of each node

        // Step 1: Initialize graph nodes
        for (const string &word : words)
        {
            for (char c : word)
            {
                indegree[c] = 0; // Ensure every character is in the indegree map
            }
        }

        // Step 2: Build the graph from adjacent word pairs
        for (int i = 0; i < words.size() - 1; ++i)
        {
            string &w1 = words[i];
            string &w2 = words[i + 1];

            // Invalid case: longer word appears before its prefix
            if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2)
            {
                return "";
            }

            // Compare characters to find the first difference
            for (int j = 0; j < min(w1.size(), w2.size()); ++j)
            {
                char c1 = w1[j];
                char c2 = w2[j];

                if (c1 != c2)
                {
                    // Add edge only if not already present
                    if (!adj[c1].count(c2))
                    {
                        adj[c1].insert(c2);
                        indegree[c2]++;
                    }
                    break; // Only first differing character matters
                }
            }
        }

        // Step 3: Kahn’s Algorithm (Topological Sort using BFS)
        queue<char> q;
        for (auto &[c, deg] : indegree)
        {
            if (deg == 0)
            {
                q.push(c);
            }
        }

        string result;
        while (!q.empty())
        {
            char c = q.front();
            q.pop();
            result += c;

            for (char neighbor : adj[c])
            {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: Check if all characters are included in result
        return result.size() == indegree.size() ? result : "";
    }
};

/* =============================================================================
 * PROBLEM 990: SATISFIABILITY OF EQUALITY EQUATIONS (LeetCode)
 * ============================================================================= */

/**
 * @brief Determine if all given equality and inequality equations are satisfiable
 *
 * PROBLEM STATEMENT:
 * You are given an array of strings `equations` of length n representing relationships between variables.
 * Each equation is of the form "a==b" or "a!=b", where a and b are lowercase English letters.
 * Return true if it is possible to assign integers to variable names such that all equations are satisfied.
 *
 * EXAMPLE:
 * Input: ["a==b","b!=a"]
 * Output: false
 *
 * APPROACH:
 * - Use Disjoint Set Union (DSU) to group variables connected by equality (==).
 * - Then, for every inequality (!=), check if both variables belong to the same group.
 * - If they do, it's a contradiction → return false.
 *
 * ALGORITHM:
 * 1. Initialize DSU for 26 lowercase letters.
 * 2. Process all equations with `==` and perform union.
 * 3. Process all equations with `!=` and check for contradiction.
 *
 * COMPLEXITY:
 * Time: O(N * α(26)) ≈ O(N), where N = number of equations
 * Space: O(26)
 */

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    // FIND operation with path compression
    int findParent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent[x]);
    }

    // UNION operation by rank
    void Union(int x, int y)
    {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py)
            return;

        if (rank[px] < rank[py])
        {
            parent[px] = py;
        }
        else if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    bool equationsPossible(vector<string> &equations)
    {
        parent.resize(26);
        rank.resize(26, 0);

        // Step 1: Initialize parent of each variable to itself
        for (int i = 0; i < 26; i++)
        {
            parent[i] = i;
        }

        // Step 2: Union all equal variables
        for (const string &eq : equations)
        {
            if (eq[1] == '=')
            {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                Union(u, v);
            }
        }

        // Step 3: Check all not-equal constraints
        for (const string &eq : equations)
        {
            if (eq[1] == '!')
            {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';

                if (findParent(u) == findParent(v))
                {
                    return false; // Contradiction found
                }
            }
        }

        return true; // No contradiction
    }
};

/* =============================================================================
 * PROBLEM 1319: NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED (LeetCode)
 * ============================================================================= */

/**
 * @brief Connect all computers in a network using the minimum number of operations
 *
 * PROBLEM STATEMENT:
 * - There are `n` computers labeled from `0` to `n - 1`.
 * - Given a list of connections where `connections[i] = [a, b]` represents a direct connection.
 * - You can remove and reconnect cables.
 * - Return the minimum number of operations needed to connect all computers.
 * - If it is not possible, return -1.
 *
 * EXAMPLE:
 * Input: n = 4, connections = [[0,1],[0,2],[1,2]]
 * Output: 1
 *
 * APPROACH:
 * - Use Disjoint Set Union (DSU) to find connected components.
 * - If total connections < n - 1 → impossible to connect → return -1.
 * - Otherwise, count how many components exist.
 * - To connect `k` components into one, you need `k - 1` cables.
 *
 * TIME COMPLEXITY: O(E * α(N)) where E = connections.size(), α = inverse Ackermann
 * SPACE COMPLEXITY: O(N)
 */

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    // FIND with path compression
    int findParent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent[x]);
    }

    // UNION by rank
    void Union(int x, int y)
    {
        int px = findParent(x);
        int py = findParent(y);

        if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else if (rank[py] > rank[px])
        {
            parent[px] = py;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    int makeConnected(int n, vector<vector<int>> &connections)
    {
        // Not enough cables to connect all computers
        if (connections.size() < n - 1)
            return -1;

        parent.resize(n);
        rank.resize(n, 0);

        // Step 1: Initialize each computer to be its own parent
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }

        int components = n;

        // Step 2: Union operation for each connection
        for (auto &edge : connections)
        {
            int u = edge[0];
            int v = edge[1];

            int pu = findParent(u);
            int pv = findParent(v);

            if (pu != pv)
            {
                Union(u, v);
                components--; // Successfully connected two components
            }
        }

        // Step 3: We need (components - 1) operations to connect them
        return components - 1;
    }
};

/* =============================================================================
 * PROBLEM 2316: COUNT UNREACHABLE PAIRS OF NODES IN AN UNDIRECTED GRAPH (LeetCode)
 * ============================================================================= */

/**
 * @brief Count the number of unordered pairs of nodes that are unreachable from each other.
 *
 * PROBLEM STATEMENT:
 * You are given an integer `n` (total number of nodes labeled 0 to n - 1) and
 * a 2D array `edges` where `edges[i] = [a, b]` represents an undirected edge.
 *
 * Return the number of **unreachable node pairs** in the graph.
 *
 * EXAMPLE:
 * Input: n = 5, edges = [[0,1],[2,3],[0,4]]
 * Output: 6
 *
 * EXPLANATION:
 * - Components: {0,1,4} and {2,3}
 * - Unreachable pairs = 3 * 2 = 6 (from each pair of distinct components)
 *
 * APPROACH:
 * - Use DSU to find connected components.
 * - Count the size of each component.
 * - For each component of size `s`, it contributes `s * (remaining - s)` unreachable pairs.
 *
 * @complexity
 * Time: O(n + e * α(n)) where e = edges.size(), α is inverse Ackermann
 * Space: O(n)
 */

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    // DSU: Find with path compression
    int findParent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent[x]);
    }

    // DSU: Union by rank
    void Union(int x, int y)
    {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py)
            return;

        if (rank[px] < rank[py])
        {
            parent[px] = py;
        }
        else if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    long long countPairs(int n, vector<vector<int>> &edges)
    {
        parent.resize(n);
        rank.resize(n, 0);

        // Step 1: Initialize each node as its own parent
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }

        // Step 2: Union all connected nodes
        for (auto &edge : edges)
        {
            Union(edge[0], edge[1]);
        }

        // Step 3: Count size of each component using parent map
        unordered_map<int, int> componentSize;
        for (int i = 0; i < n; i++)
        {
            int p = findParent(i);
            componentSize[p]++;
        }

        // Step 4: Count unreachable pairs
        long long totalPairs = 0;
        long long remaining = n;

        for (auto &[leader, size] : componentSize)
        {
            totalPairs += size * (remaining - size);
            remaining -= size;
        }

        return totalPairs;
    }
};

/* ===================================================================
 * PROBLEM 743: NETWORK DELAY TIME (LeetCode)
 * =================================================================== */

/**
 * @brief Find the time it takes for all nodes to receive a signal from a source node.
 *
 * PROBLEM STATEMENT:
 * You are given a directed weighted graph with `n` nodes labeled from 1 to `n`,
 * and a list of travel times as directed edges `times[i] = [u, v, w]`,
 * where `u` sends a signal to `v` with a time delay of `w`.
 *
 * Return the minimum time it takes for all the `n` nodes to receive the signal from the source `k`.
 * If it is impossible for all nodes to receive the signal, return `-1`.
 *
 * APPROACH:
 * - Build an adjacency list to represent the graph.
 * - Use Dijkstra's Algorithm (min-heap) to find the shortest time from node `k` to all others.
 * - Track the time to reach each node using a `time[]` array.
 * - The result is the maximum value in the `time[]` array (i.e., the longest minimum delay).
 *
 * @complexity
 * Time: O((V + E) * log V)
 * Space: O(V + E)
 */

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        // Step 1: Build the adjacency list
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto vec : times)
        {
            int u = vec[0];
            int v = vec[1];
            int w = vec[2];
            adj[u].push_back({v, w});
        }

        // Step 2: Initialize min-heap and distance array
        vector<int> time(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        time[k] = 0;
        pq.push({0, k}); // {delayTime, node}

        // Step 3: Dijkstra’s Algorithm
        while (!pq.empty())
        {
            auto [d, node] = pq.top();
            pq.pop();

            for (auto [neighbor, weight] : adj[node])
            {
                if (d + weight < time[neighbor])
                {
                    time[neighbor] = d + weight;
                    pq.push({time[neighbor], neighbor});
                }
            }
        }

        // Step 4: Compute max delay time among all nodes
        int maxTime = 0;
        for (int i = 1; i <= n; i++)
        {
            if (time[i] == INT_MAX)
                return -1; // unreachable node
            maxTime = max(maxTime, time[i]);
        }

        return maxTime;
    }
};



/* ===================================================================
 * PROBLEM 1631: PATH WITH MINIMUM EFFORT (LeetCode)
 * =================================================================== */

/**
 * @brief Find a path from (0, 0) to (m-1, n-1) minimizing the maximum height difference.
 *
 * PROBLEM:
 * - You are given an `m x n` grid of integers `heights`.
 * - A path is valid if at each step you move to an adjacent cell (up/down/left/right).
 * - The *effort* of a path is the **maximum absolute difference** in heights between adjacent cells.
 * - Return the minimum possible *effort* needed to reach the bottom-right from the top-left.
 *
 * APPROACH (Dijkstra’s Algorithm):
 * - Treat each cell as a node, and each move to a neighbor as an edge with a weight = abs(height difference).
 * - The goal is to minimize the **maximum edge weight** on the path from source to destination.
 * - Use a min-heap (priority queue) to always pick the path with the least *effort so far*.
 * - For each neighbor, compute the maximum effort along that path and update it if it's better.
 *
 * COMPLEXITY:
 * - Time: O(m * n * log(m * n)) because each cell is pushed to the heap at most once
 * - Space: O(m * n) for the result matrix and priority queue
 */

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int m = heights.size();
        int n = heights[0].size();

        // result[i][j] stores the minimum effort needed to reach cell (i, j)
        vector<vector<int>> result(m, vector<int>(n, INT_MAX));
        result[0][0] = 0;

        // Min-heap: stores {effort to reach, {x, y}}
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<>>
            pq;

        pq.push({0, {0, 0}}); // Start from the top-left cell

        // 4-directional movement (up, down, left, right)
        vector<pair<int, int>> directions = {
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (!pq.empty())
        {
            auto [currEffort, coords] = pq.top();
            pq.pop();
            auto [x, y] = coords;

            // If we've reached the destination cell, return the current effort
            if (x == m - 1 && y == n - 1)
                return currEffort;

            // Visit all 4 neighbors
            for (auto [dx, dy] : directions)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Make sure neighbor is within grid bounds
                if (nx >= 0 && ny >= 0 && nx < m && ny < n)
                {
                    // Calculate the effort to move to neighbor
                    int diff = abs(heights[nx][ny] - heights[x][y]);
                    int newEffort = max(currEffort, diff); // max of path so far and current edge

                    // If this path offers a smaller max effort to reach (nx, ny), update it
                    if (newEffort < result[nx][ny])
                    {
                        result[nx][ny] = newEffort;
                        pq.push({newEffort, {nx, ny}});
                    }
                }
            }
        }

        return 0; // Fallback, although the problem guarantees reachability
    }
};

/* ===================================================================
 * PROBLEM 1584: MINIMUM COST TO CONNECT ALL POINTS (USING PRIM'S MST)
 * =================================================================== */

/**
 * @brief Find the minimum cost to connect all points in 2D space
 *
 * PROBLEM STATEMENT:
 * Given `n` points in a 2D plane, you are to connect all points such that the total cost is minimized.
 * The cost to connect two points (x1, y1) and (x2, y2) is the **Manhattan Distance**:
 *   cost = |x1 - x2| + |y1 - y2|
 *
 * You can connect any two points directly; the goal is to **connect all points with minimum total cost**
 * such that all nodes are reachable (Minimum Spanning Tree).
 *
 * Input:
 * - vector<vector<int>> points: where points[i] = {xi, yi}
 *
 * Output:
 * - Integer value representing minimum total cost to connect all points
 *
 * APPROACH (Prim's Algorithm for MST):
 * - Construct a complete graph using Manhattan distances
 * - Apply Prim’s algorithm with Min-Heap to find MST cost
 *
 * COMPLEXITY:
 * - Time: O(N^2 * log N) due to dense graph and priority queue
 * - Space: O(N^2) for adjacency list
 */

class Solution
{
public:
    /**
     * @brief Prim's algorithm to compute MST cost from adjacency list
     * @param adj: Adjacency list of the graph {neighbour, cost}
     * @param n: Number of nodes
     * @return Total cost of the Minimum Spanning Tree
     */
    int primsAlgo(vector<vector<pair<int, int>>> &adj, int n)
    {
        // Min-heap: {cost, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<bool> inMST(n, false); // Mark nodes already included in MST
        int minCost = 0;

        pq.push({0, 0}); // Start from node 0 with 0 cost

        while (!pq.empty())
        {
            auto [cost, node] = pq.top();
            pq.pop();

            if (inMST[node])
                continue;

            inMST[node] = true;
            minCost += cost;

            // Add all neighbors of current node to the heap
            for (auto [neighbour, neighbourCost] : adj[node])
            {
                if (!inMST[neighbour])
                {
                    pq.push({neighbourCost, neighbour});
                }
            }
        }

        return minCost;
    }

    /**
     * @brief Main function to compute the minimum cost to connect all given points
     */
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();

        // Step 1: Build complete graph with Manhattan distances
        vector<vector<pair<int, int>>> adj(n); // adj[u] = {v, cost}
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                adj[i].push_back({j, cost});
                adj[j].push_back({i, cost});
            }
        }

        // Step 2: Apply Prim's algorithm to get MST cost
        return primsAlgo(adj, n);
    }
};


/* ===================================================================
 * LEETCODE 947: MOST STONES REMOVED WITH SAME ROW OR COLUMN
 * =================================================================== */

/**
 * @brief Remove the maximum number of stones from a 2D grid
 *
 * PROBLEM STATEMENT:
 * You are given a list of stones where each stone is at position (x, y) on a 2D grid.
 * A stone can be removed **if there is another stone in the same row or column**.
 *
 * Return the **maximum number of stones that can be removed**.
 *
 * Note: You can only remove a stone if it shares a row or column with at least one other remaining stone.
 *
 * Input:
 * - vector<vector<int>> stones: list of stone coordinates
 *
 * Output:
 * - Integer: Maximum number of stones that can be removed
 *
 * EXAMPLE:
 * Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
 * Output: 5
 * Explanation: We can remove 5 stones, one per move, leaving one isolated stone.
 *
 * ALGORITHM (DFS + Connected Components):
 * - Treat each stone as a node in a graph
 * - Connect two stones if they share a row or column
 * - Count number of connected components using DFS
 * - Answer = total stones - number of connected components
 *
 * COMPLEXITY:
 * - Time: O(N^2), where N is the number of stones (due to pairwise comparisons)
 * - Space: O(N) for visited array
 */

class Solution
{
public:
    /**
     * @brief DFS to mark all connected stones (same row or column)
     */
    void dfs(vector<vector<int>> &stones, int index, vector<bool> &visited)
    {
        int n = stones.size();
        visited[index] = true;

        int r = stones[index][0];
        int c = stones[index][1];

        // Traverse all other stones and visit connected ones
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && (stones[i][0] == r || stones[i][1] == c))
            {
                dfs(stones, i, visited);
            }
        }
    }

    /**
     * @brief Main function to compute max removable stones
     */
    int removeStones(vector<vector<int>> &stones)
    {
        int n = stones.size();
        vector<bool> visited(n, false);

        int group = 0; // Count connected components (islands)

        // Use DFS to find all connected components
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(stones, i, visited);
                group++;
            }
        }

        return n - group; // Max stones removed = total - groups
    }
};



/* ===================================================================
 * LEETCODE 1971: FIND IF PATH EXISTS IN GRAPH
 * =================================================================== */

/**
 * @brief Determine if there is a valid path between source and destination
 *
 * PROBLEM STATEMENT:
 * You are given an **undirected graph** with `n` nodes numbered from 0 to n - 1.
 * You are also given a list of `edges` where each edge connects two nodes.
 *
 * Given a `source` node and a `destination` node, return `true` if there is a valid path
 * between the two, or `false` otherwise.
 *
 * Input:
 * - Integer `n`: number of nodes
 * - vector<vector<int>> edges: list of undirected edges
 * - Integer `source`: start node
 * - Integer `destination`: target node
 *
 * Output:
 * - Boolean: true if path exists, false otherwise
 *
 * EXAMPLE:
 * Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
 * Output: false
 *
 * ALGORITHM (DFS Traversal):
 * - Build the adjacency list from edge list
 * - Perform DFS from the source
 * - If destination is found during DFS, return true
 *
 * COMPLEXITY:
 * - Time: O(V + E)
 * - Space: O(V + E) for adjacency list and visited array
 */

class Solution
{
public:
    /**
     * @brief DFS to find if destination is reachable from source
     */
    bool dfs(vector<vector<int>> &adj, int source, int destination, vector<bool> &visited)
    {
        if (source == destination)
            return true;

        visited[source] = true;

        for (auto neighbour : adj[source])
        {
            if (!visited[neighbour] && dfs(adj, neighbour, destination, visited))
            {
                return true;
            }
        }

        return false;
    }

    /**
     * @brief Main function to check if path exists between source and destination
     */
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);

        // Build adjacency list
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        return dfs(adj, source, destination, visited);
    }
};



/* ===================================================================
 * LEETCODE 886: POSSIBLE BIPARTITION
 * =================================================================== */

/**
 * @brief Check if it’s possible to partition people into two groups such that
 *        no pair of people who dislike each other are in the same group.
 *
 * PROBLEM STATEMENT:
 * Given `n` people labeled from 1 to n and a list of `dislikes` pairs,
 * determine if it is possible to split all people into two groups such that:
 * - No pair in the same group dislikes each other.
 *
 * This is equivalent to checking if the graph is **bipartite**.
 *
 * Input:
 * - Integer `n`: number of people
 * - vector<vector<int>> dislikes: list of mutual dislikes (edges)
 *
 * Output:
 * - Boolean: true if bipartition is possible, false otherwise
 *
 * EXAMPLE:
 * Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
 * Output: true
 * Explanation: Group 1 = {1, 4}, Group 2 = {2, 3}
 *
 * ALGORITHM (DFS for Bipartite Check):
 * - Build the graph using adjacency list
 * - Use DFS to color nodes in two groups (0 and 1)
 * - If a conflict is found (same color on both sides), return false
 *
 * COMPLEXITY:
 * - Time: O(V + E), where V = n, E = size of dislikes
 * - Space: O(V + E) for graph + O(V) for visited/group
 */

class Solution
{
public:
    /**
     * @brief Recursive DFS to check bipartiteness by coloring
     */
    bool checkBipart(vector<vector<int>> &adj, int curr, vector<int> &group, int currGroup)
    {
        group[curr] = currGroup;

        for (int neighbour : adj[curr])
        {
            if (group[neighbour] == group[curr])
                return false;

            if (group[neighbour] == -1)
            {
                if (!checkBipart(adj, neighbour, group, 1 - currGroup))
                {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * @brief Main function to check if possible to bipartition the graph
     */
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        vector<vector<int>> adj(n + 1);
        vector<int> group(n + 1, -1); // -1 = unvisited, 0 and 1 = two groups

        // Build adjacency list
        for (auto &edge : dislikes)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check for each connected component
        for (int i = 1; i <= n; i++)
        {
            if (group[i] == -1)
            {
                if (!checkBipart(adj, i, group, 0))
                {
                    return false;
                }
            }
        }

        return true;
    }
};


/* ===================================================================
 * LEETCODE 1443: MINIMUM TIME TO COLLECT ALL APPLES IN A TREE
 * =================================================================== */

/**
 * @brief Find the minimum time needed to collect all apples in the tree
 *
 * PROBLEM STATEMENT:
 * Given a tree with `n` nodes (0 to n - 1) and an array `hasApple` where
 * hasApple[i] = true means node i has an apple, find the **minimum time**
 * to collect all apples starting and ending at the root node (node 0).
 *
 * Each edge takes 1 second to go and 1 second to return (2 seconds total).
 *
 * INPUT:
 * - int n: number of nodes
 * - vector<vector<int>> edges: undirected edges of the tree
 * - vector<bool> hasApple: array indicating which nodes have apples
 *
 * OUTPUT:
 * - Integer: minimum time to collect all apples
 *
 * EXAMPLE:
 * Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
 * Output: 8
 *
 * ALGORITHM (DFS Tree Traversal):
 * - Build an adjacency list from the edge list
 * - Do DFS from the root (node 0)
 * - At each node, recursively calculate time for its children
 * - If a child subtree contains an apple, add 2 seconds (go + return)
 *
 * COMPLEXITY:
 * - Time: O(N)
 * - Space: O(N) for recursion and adjacency list
 */

class Solution
{
public:
    /**
     * @brief DFS function to calculate the total time for apple collection
     * @param adj: adjacency list of the tree
     * @param node: current node
     * @param parent: previous node to avoid revisiting
     * @param hasApple: apple presence array
     * @return time taken from this node's subtree
     */
    int dfs(vector<vector<int>> &adj, int node, int parent, vector<bool> &hasApple)
    {
        int time = 0;

        for (int child : adj[node])
        {
            if (child == parent)
                continue;

            int timeChild = dfs(adj, child, node, hasApple);

            // If child has apple or any of its descendants have one
            if (timeChild != 0 || hasApple[child])
            {
                time += timeChild + 2; // +2 for the round trip edge
            }
        }

        return time;
    }

    /**
     * @brief Main function to return minimum time
     */
    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Perform DFS from root (node 0)
        return dfs(adj, 0, -1, hasApple);
    }
};

/* ===================================================================
 * LEETCODE 1061: LEXICOGRAPHICALLY SMALLEST EQUIVALENT STRING
 * =================================================================== */

/**
 * @brief Return the lexicographically smallest equivalent string
 *
 * PROBLEM STATEMENT:
 * You are given two strings `s1` and `s2` of equal length, and a `baseStr`.
 * Characters from `s1[i]` and `s2[i]` are considered **equivalent**.
 *
 * You may replace a character in `baseStr` with any of its equivalents.
 * Return the **lexicographically smallest** string after replacements.
 *
 * INPUT:
 * - string s1, s2: mapping of equivalent characters (same length)
 * - string baseStr: base string to transform
 *
 * OUTPUT:
 * - Transformed string: lexicographically smallest equivalent version of baseStr
 *
 * EXAMPLE:
 * Input: s1 = "parker", s2 = "morris", baseStr = "parser"
 * Output: "makkek"
 *
 * ALGORITHM (DFS + Graph of Equivalents):
 * - Treat characters as nodes in a graph
 * - If s1[i] = u and s2[i] = v → add edges u ↔ v
 * - For each character in baseStr:
 *   - DFS to find the lexicographically smallest character in its component
 *
 * COMPLEXITY:
 * - Time: O(N + M * 26), where N = length of s1/s2, M = baseStr.length()
 * - Space: O(26) for visited array + adjacency list
 */

class Solution
{
public:
    /**
     * @brief DFS to find the lexicographically smallest character in the component
     */
    char dfsMinCh(unordered_map<char, vector<char>> &adj, char ch, vector<bool> &visited)
    {
        visited[ch - 'a'] = true;
        char minCh = ch;

        for (char neighbour : adj[ch])
        {
            if (!visited[neighbour - 'a'])
            {
                minCh = min(minCh, dfsMinCh(adj, neighbour, visited));
            }
        }

        return minCh;
    }

    /**
     * @brief Main function to return lexicographically smallest equivalent string
     */
    string smallestEquivalentString(string s1, string s2, string baseStr)
    {
        int n = s1.length();
        int m = baseStr.length();

        unordered_map<char, vector<char>> adj;

        // Step 1: Build equivalence graph
        for (int i = 0; i < n; i++)
        {
            char u = s1[i];
            char v = s2[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        string result;

        // Step 2: For each char in baseStr, find smallest equivalent
        for (int i = 0; i < m; i++)
        {
            char ch = baseStr[i];
            vector<bool> visited(26, false);
            char minCh = dfsMinCh(adj, ch, visited);
            result.push_back(minCh);
        }

        return result;
    }
};

/* ===================================================================
 * LEETCODE 2359: FIND CLOSEST NODE TO GIVEN TWO NODES
 * =================================================================== */

/**
 * @brief Find the node reachable from both start1 and start2 with minimal maximum distance
 *
 * PROBLEM STATEMENT:
 * Given a directed graph (each node has at most one outgoing edge),
 * and two starting nodes `start1` and `start2`,
 * return the node that is reachable from **both** and has the **minimum maximum distance**
 * from the two starting nodes.
 *
 * If multiple answers exist, return the one with the smallest index.
 * If no such node exists, return -1.
 *
 * INPUT:
 * - vector<int> edges: graph represented as edges[i] = node i points to
 * - int start1, start2: starting nodes
 *
 * OUTPUT:
 * - int: closest meeting node index
 *
 * EXAMPLE:
 * Input: edges = [2,2,3,-1], start1 = 0, start2 = 1
 * Output: 2
 *
 * ALGORITHM:
 * - Perform DFS from both start1 and start2 to compute distances to all reachable nodes
 * - For every node, if it’s reachable from both, track max(dist1, dist2)
 * - Return node with the smallest such max distance
 *
 * COMPLEXITY:
 * - Time: O(N) where N = number of nodes
 * - Space: O(N) for storing distances
 */

class Solution
{
public:
    /**
     * @brief DFS-like traversal to populate distance array from a starting node
     */
    void dfs(int current, int distance, const vector<int> &edges, vector<int> &distances)
    {
        while (current != -1 && distances[current] == -1)
        {
            distances[current] = distance++;
            current = edges[current]; // Follow the next edge
        }
    }

    /**
     * @brief Main function to return the closest meeting node
     */
    int closestMeetingNode(vector<int> &edges, int start1, int start2)
    {
        int n = edges.size();
        vector<int> dist1(n, -1), dist2(n, -1);

        // Compute distances from both starting nodes
        dfs(start1, 0, edges, dist1);
        dfs(start2, 0, edges, dist2);

        int res = -1;
        int minMaxDist = INT_MAX;

        // Compare distances at each node
        for (int i = 0; i < n; i++)
        {
            if (dist1[i] >= 0 && dist2[i] >= 0)
            {
                int maxDist = max(dist1[i], dist2[i]);
                if (maxDist < minMaxDist)
                {
                    minMaxDist = maxDist;
                    res = i; // Store index of closest meeting node
                }
            }
        }

        return res;
    }
};

/* ===================================================================
 * LEETCODE 2492: MINIMUM SCORE OF A PATH BETWEEN TWO CITIES
 * =================================================================== */

/**
 * @brief Find the minimum score of a path between city 1 and city n
 *
 * PROBLEM STATEMENT:
 * You are given a connected undirected graph with `n` cities (1 to n) and weighted roads.
 * Each road connects two cities and has a score (weight).
 * A path from city 1 to city n can pass through any number of cities.
 *
 * The **score of a path** is defined as the **minimum weight** of all the roads in the path.
 * Return the **minimum possible score** of a path between city 1 and city n.
 *
 * INPUT:
 * - int n: number of cities
 * - vector<vector<int>> roads: list of roads, each road = [u, v, weight]
 *
 * OUTPUT:
 * - int: the minimum score of any path from city 1 to city n
 *
 * EXAMPLE:
 * Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
 * Output: 5
 *
 * ALGORITHM (DFS + Min Tracking):
 * - Use DFS to visit all reachable nodes from city 1.
 * - Track the **minimum edge weight** encountered during traversal.
 * - Since the graph is connected, every node is eventually reachable.
 *
 * COMPLEXITY:
 * - Time: O(V + E)
 * - Space: O(V + E)
 */

class Solution
{
public:
    /**
     * @brief DFS traversal to explore graph and track minimum edge weight
     */
    void dfs(int node, vector<vector<pair<int, int>>> &adj,
             vector<bool> &visited, int &score)
    {

        visited[node] = true;

        for (auto &[neighbour, weight] : adj[node])
        {
            score = min(score, weight); // update minimum score
            if (!visited[neighbour])
            {
                dfs(neighbour, adj, visited, score);
            }
        }
    }

    /**
     * @brief Main function to return minimum score between city 1 and city n
     */
    int minScore(int n, vector<vector<int>> &roads)
    {
        vector<vector<pair<int, int>>> adj(n + 1); // 1-based indexing

        // Step 1: Build adjacency list
        for (auto &road : roads)
        {
            int u = road[0], v = road[1], w = road[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w); // undirected graph
        }

        vector<bool> visited(n + 1, false);
        int minScore = INT_MAX;

        // Step 2: DFS from node 1 to explore reachable area and track min edge
        dfs(1, adj, visited, minScore);

        return minScore;
    }
};

/* ===================================================================
 * LEETCODE 1466: REORDER ROUTES TO MAKE ALL PATHS LEAD TO CITY ZERO
 * =================================================================== */

/**
 * @brief Count the minimum number of edge reorientations required
 *        so that all paths lead to city 0.
 *
 * PROBLEM STATEMENT:
 * You are given a directed tree (graph with n nodes and n - 1 directed edges) where each edge
 * goes from city `u` to city `v`.
 *
 * Your goal is to **reorient the minimum number of edges** so that every node has a path
 * that leads to city 0.
 *
 * INPUT:
 * - int n: number of cities
 * - vector<vector<int>> connections: directed edges from u → v
 *
 * OUTPUT:
 * - int: minimum number of edges that need to be reversed
 *
 * EXAMPLE:
 * Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
 * Output: 3
 *
 * ALGORITHM (DFS with directed edge marking):
 * - For each directed edge u → v:
 *      - store (v, true) in adj[u]   → original direction
 *      - store (u, false) in adj[v] → reverse edge to allow bidirectional DFS
 * - Start DFS from node 0
 *      - If we traverse an edge in the original direction (i.e., away from 0), count it
 * - Return the total number of such edges that need to be reversed.
 *
 * COMPLEXITY:
 * - Time: O(N)
 * - Space: O(N)
 */

class Solution
{
public:
    /**
     * @brief DFS traversal that counts wrongly directed edges
     */
    void dfs(unordered_map<int, vector<pair<int, bool>>> &adj, int node,
             int parent, vector<bool> &visited, int &count)
    {
        visited[node] = true;

        for (auto [neighbour, isReal] : adj[node])
        {
            if (!visited[neighbour])
            {
                if (isReal)
                {
                    count++; // edge needs to be reversed
                }
                dfs(adj, neighbour, node, visited, count);
            }
        }
    }

    /**
     * @brief Main function to return the minimum number of edge reversals
     */
    int minReorder(int n, vector<vector<int>> &connections)
    {
        unordered_map<int, vector<pair<int, bool>>> adj;

        // Step 1: Build an adjacency list with direction info
        for (auto &edge : connections)
        {
            int u = edge[0];
            int v = edge[1];

            adj[u].emplace_back(v, true);  // original directed edge u → v
            adj[v].emplace_back(u, false); // reversed (virtual) edge v → u
        }

        vector<bool> visited(n, false);
        int count = 0;

        // Step 2: DFS from node 0
        dfs(adj, 0, -1, visited, count);

        return count;
    }
};

/* ===================================================================
 * LEETCODE 2360: LONGEST CYCLE IN A GRAPH
 * =================================================================== */

/**
 * @brief Find the length of the longest cycle in a directed graph
 *
 * PROBLEM STATEMENT:
 * Given a directed graph where each node has at most one outgoing edge,
 * find the length of the longest cycle in the graph. If no cycle exists, return -1.
 *
 * INPUT:
 * - vector<int>& edges: edges[i] = the node that node i points to (or -1 if none)
 *
 * OUTPUT:
 * - int: length of the longest cycle (or -1 if none exists)
 *
 * EXAMPLE:
 * Input: edges = [3,3,4,2,3]
 * Output: 3
 *
 * ALGORITHM (DFS + Recursion Tracking):
 * - Use DFS to explore paths and detect cycles
 * - Track recursion stack (`inRecursion[]`) to identify back-edges
 * - Maintain a `count[]` array to store distance (depth) from the start node
 * - If a cycle is found, calculate its length using count difference
 *
 * COMPLEXITY:
 * - Time: O(N), where N is number of nodes (since each node is visited once)
 * - Space: O(N) for visited, inRecursion, and count arrays
 */

class Solution
{
public:
    int result = -1;

    /**
     * @brief DFS traversal to detect and measure cycles
     */
    void dfs(int u, vector<int> &edges, vector<bool> &visited,
             vector<int> &count, vector<bool> &inRecursion)
    {

        if (u == -1)
            return;

        visited[u] = true;
        inRecursion[u] = true;

        int v = edges[u];

        if (v != -1 && !visited[v])
        {
            count[v] = count[u] + 1;
            dfs(v, edges, visited, count, inRecursion);
        }
        // Cycle detected: v is in current DFS path
        else if (v != -1 && inRecursion[v])
        {
            result = max(result, count[u] - count[v] + 1);
        }

        inRecursion[u] = false; // backtrack
    }

    /**
     * @brief Main function to compute longest cycle length
     */
    int longestCycle(vector<int> &edges)
    {
        int n = edges.size();
        vector<bool> visited(n, false);
        vector<bool> inRecursion(n, false);
        vector<int> count(n, 1); // initial depth is 1 for each start node

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(i, edges, visited, count, inRecursion);
            }
        }

        return result;
    }
};

/* ===================================================================
 * LEETCODE 1557: MINIMUM NUMBER OF VERTICES TO REACH ALL NODES
 * =================================================================== */

/**
 * @brief Find all nodes in a DAG that have no incoming edges.
 *
 * PROBLEM STATEMENT:
 * Given a directed acyclic graph (DAG) with `n` nodes labeled from 0 to n - 1,
 * and a list of directed edges, return a list of all vertices with **in-degree 0**.
 *
 * These are the **minimum number of vertices** needed to reach all nodes.
 *
 * ALGORITHM:
 * - Track in-degrees of each node.
 * - Nodes with no incoming edges (in-degree 0) must be part of the answer.
 *
 * TIME COMPLEXITY: O(E + N)
 * SPACE COMPLEXITY: O(N)
 */

class Solution
{
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges)
    {
        // Step 1: Track which nodes have incoming edges
        vector<bool> hasIncoming(n, false);

        for (auto &edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            hasIncoming[to] = true; // mark as having an incoming edge
        }

        // Step 2: Nodes with no incoming edges are our answer
        vector<int> result;
        for (int i = 0; i < n; ++i)
        {
            if (!hasIncoming[i])
            {
                result.push_back(i); // can't be reached by any other node
            }
        }

        return result;
    }
};

/* ===================================================================
 * LEETCODE 399: EVALUATE DIVISION
 * =================================================================== */

/**
 * @brief Given equations like a / b = 2.0 and queries like a / c,
 *        evaluate the result using a graph-based approach.
 *
 * ALGORITHM (DFS Traversal):
 * - Treat each variable as a node in a graph.
 * - Each equation (a / b = val) forms two edges: a → b with weight val and b → a with weight 1/val.
 * - For each query, run DFS to find a path from source to destination,
 *   multiplying edge weights along the way.
 *
 * TIME COMPLEXITY:
 * - Building graph: O(E), where E is number of equations
 * - Query DFS traversal: O(N + E) worst case per query
 */

class Solution
{
public:
    /**
     * @brief Helper DFS to evaluate the product path from src to dst
     *
     * @param adj      Adjacency list storing graph
     * @param src      Current node
     * @param dst      Target node
     * @param visited  Set to prevent revisiting nodes
     * @param product  Current accumulated product
     * @param ans      Reference to store final result if path is found
     */
    void dfs(unordered_map<string, vector<pair<string, double>>> &adj,
             const string &src, const string &dst,
             unordered_set<string> &visited,
             double product, double &ans)
    {

        // already visited → cycle
        if (visited.count(src))
            return;

        visited.insert(src);

        // base case: source and destination matched
        if (src == dst)
        {
            ans = product;
            return;
        }

        // explore neighbors
        for (auto &[neighbor, weight] : adj[src])
        {
            dfs(adj, neighbor, dst, visited, product * weight, ans);
        }
    }

    /**
     * @brief Solve all division queries based on given equations
     */
    vector<double> calcEquation(vector<vector<string>> &equations,
                                vector<double> &values,
                                vector<vector<string>> &queries)
    {
        int n = equations.size();
        unordered_map<string, vector<pair<string, double>>> adj;

        // Step 1: Build the graph
        for (int i = 0; i < n; i++)
        {
            string u = equations[i][0];
            string v = equations[i][1];
            double val = values[i];

            adj[u].emplace_back(v, val);       // u → v with weight val
            adj[v].emplace_back(u, 1.0 / val); // v → u with weight 1/val
        }

        // Step 2: Process each query using DFS
        vector<double> result;

        for (auto &query : queries)
        {
            string src = query[0];
            string dst = query[1];
            double ans = -1.0;

            if (adj.count(src) && adj.count(dst))
            {
                unordered_set<string> visited;
                dfs(adj, src, dst, visited, 1.0, ans);
            }

            result.push_back(ans);
        }

        return result;
    }
};

/* ===================================================================
 * LEETCODE 2097: VALID ARRANGEMENT OF PAIRS
 * =================================================================== */

/**
 * @brief Given a list of directed pairs [u, v], rearrange them so that:
 *        - For every adjacent pair (a, b) and (b, c), b matches.
 *        - In other words, form a valid Eulerian path from the pairs.
 *
 * ALGORITHM (Hierholzer's Algorithm for Directed Graph):
 * - Build adjacency list and track in-degree/out-degree for all nodes.
 * - Identify the starting node of the Eulerian path:
 *     → It should have out-degree = in-degree + 1
 *     → If none, start with any node
 * - Use a stack to simulate DFS and construct the path in reverse.
 * - Convert the node path into an edge list format.
 *
 * TIME COMPLEXITY: O(E), where E = number of pairs
 */

class Solution
{
public:
    /**
     * @brief Reconstruct a valid arrangement of pairs using Eulerian path
     *
     * @param pairs  List of directed edges [from, to]
     * @return       Sequence of pairs forming a valid path
     */
    vector<vector<int>> validArrangement(vector<vector<int>> &pairs)
    {
        // Step 1: Build adjacency list and degree counters
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> indegree, outdegree;

        for (auto &edge : pairs)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            outdegree[u]++;
            indegree[v]++;
        }

        // Step 2: Find start node for Eulerian path
        int start = pairs[0][0];
        for (auto &[node, _] : adj)
        {
            if (outdegree[node] - indegree[node] == 1)
            {
                start = node;
                break;
            }
        }

        // Step 3: Perform Hierholzer’s Algorithm (iterative DFS)
        vector<int> path;
        stack<int> st;
        st.push(start);

        while (!st.empty())
        {
            int curr = st.top();

            if (!adj[curr].empty())
            {
                int next = adj[curr].back();
                adj[curr].pop_back();
                st.push(next);
            }
            else
            {
                path.push_back(curr);
                st.pop();
            }
        }

        // Step 4: Build result as list of edges
        reverse(path.begin(), path.end());

        vector<vector<int>> result;
        for (int i = 0; i < path.size() - 1; i++)
        {
            result.push_back({path[i], path[i + 1]});
        }

        return result;
    }
};

/* ===================================================================
 * LEETCODE: MINIMUM DIAMETER AFTER MERGE OF TWO TREES
 * =================================================================== */

/**
 * @brief Given two trees (acyclic connected graphs), you are to merge them
 *        by connecting one node from each with a new edge.
 *        Return the minimum diameter of the resulting tree.
 *
 * KEY OBSERVATION:
 * - Connecting two trees of diameters `d1` and `d2` through a new edge increases
 *   the longest path possibly via midpoints of each tree → total = ⌊(d1+1)/2⌋ + ⌊(d2+1)/2⌋ + 1
 * - Final diameter = max(existing d1 or d2, or the new combined path)
 *
 * APPROACH:
 * - Use BFS twice to find the **diameter** of each tree:
 *     1. First BFS: from any node to find farthest node (one endpoint of diameter)
 *     2. Second BFS: from that endpoint to compute the actual diameter
 * - Merge logic = connect deepest midpoints of both trees to minimize overall diameter
 *
 * TIME COMPLEXITY: O(N1 + N2) where N1 and N2 are number of nodes in tree1 and tree2
 */

class Solution
{
public:
    /**
     * @brief Perform BFS to find the farthest node and its distance from source
     *
     * @param adj     Adjacency list of the tree
     * @param source  Starting node
     * @return        {farthestNode, distance}
     */
    pair<int, int> BFS(unordered_map<int, vector<int>> &adj, int source)
    {
        queue<int> q;
        unordered_map<int, bool> visited;

        q.push(source);
        visited[source] = true;

        int dist = 0;
        int node = source;

        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                int temp = q.front();
                q.pop();
                node = temp;

                for (int neighbor : adj[temp])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            dist++;
        }

        return {node, dist - 1}; // dist - 1 as we count levels
    }

    /**
     * @brief Finds the diameter of a tree using double BFS
     */
    int findDiameter(unordered_map<int, vector<int>> &adj)
    {
        // First BFS to find one end of the diameter
        auto [farthestNode, _] = BFS(adj, 0);

        // Second BFS from farthest node to get actual diameter
        auto [otherEnd, diameter] = BFS(adj, farthestNode);

        return diameter;
    }

    /**
     * @brief Builds adjacency list from edge list
     */
    unordered_map<int, vector<int>> buildGraph(const vector<vector<int>> &edges)
    {
        unordered_map<int, vector<int>> adj;
        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return adj;
    }

    /**
     * @brief Returns the minimum possible diameter after merging two trees
     *
     * @param edges1   Tree 1 edges
     * @param edges2   Tree 2 edges
     * @return         Diameter of merged tree
     */
    int minimumDiameterAfterMerge(vector<vector<int>> &edges1, vector<vector<int>> &edges2)
    {
        // Build adjacency lists for both trees
        unordered_map<int, vector<int>> adj1 = buildGraph(edges1);
        unordered_map<int, vector<int>> adj2 = buildGraph(edges2);

        // Compute diameters of each tree
        int d1 = findDiameter(adj1);
        int d2 = findDiameter(adj2);

        // Combined path through midpoints + 1 edge connecting them
        int combinedPath = ((d1 + 1) / 2) + ((d2 + 1) / 2) + 1;

        // Final diameter is the max of original diameters and the combined path
        return max({d1, d2, combinedPath});
    }
};

/* ===================================================================
 * LEETCODE 1765: MAP OF HIGHEST PEAK
 * =================================================================== */

/**
 * @brief Given a grid with water and land, assign height to each cell such that:
 *        - Water cells have height 0
 *        - Heights of adjacent cells differ by at most 1
 *        - The final result forms the "highest peak" from water sources
 *
 * STRATEGY:
 * - Use multi-source BFS starting from all water cells
 * - Assign increasing heights to adjacent unvisited land cells
 *
 * TIME COMPLEXITY: O(M * N)
 * SPACE COMPLEXITY: O(M * N)
 */

class Solution
{
public:
    /**
     * @brief Returns height map for the terrain where water cells are 0 and heights increase by 1 away from water.
     *
     * @param isWater  2D grid marking water (1) and land (0)
     * @return         2D height grid
     */
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        int m = isWater.size(), n = isWater[0].size();

        // Step 1: Initialize height matrix and BFS queue
        vector<vector<int>> height(m, vector<int>(n, -1)); // -1 = unvisited
        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isWater[i][j] == 1)
                {
                    height[i][j] = 0; // Water cell = height 0
                    q.push({i, j});   // Enqueue all water cells
                }
            }
        }

        // Step 2: Directions for up, down, left, right
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Step 3: BFS from all water cells
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto &dir : dirs)
            {
                int nx = x + dir[0], ny = y + dir[1];

                // Valid and unvisited neighbor
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && height[nx][ny] == -1)
                {
                    height[nx][ny] = height[x][y] + 1; // increase height
                    q.push({nx, ny});
                }
            }
        }

        return height;
    }
};

/* ===================================================================
 * LEETCODE 787: CHEAPEST FLIGHTS WITHIN K STOPS
 * =================================================================== */

/**
 * @brief Given a list of flights (u → v with cost), find the cheapest price
 *        from `src` to `dst` with at most `k` stops (i.e., k+1 flights).
 *
 * APPROACH (Dijkstra Variant with K-stops constraint):
 * - Use a min-heap (priority queue) where each entry stores:
 *       {total_cost, {current_node, stops_so_far}}
 * - Track the minimum number of stops used to reach a node to prune paths.
 * - Skip expanding nodes if current path exceeds allowed stops (k).
 *
 * TIME COMPLEXITY: O(E log V), but controlled by K (max depth)
 * SPACE COMPLEXITY: O(V + E)
 */

class Solution
{
public:
    /**
     * @brief Find cheapest price from src to dst within at most k stops
     *
     * @param n       Number of cities
     * @param flights Edge list [from, to, cost]
     * @param src     Source city
     * @param dst     Destination city
     * @param k       Max number of allowed stops
     * @return        Minimum cost or -1 if not possible
     */
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        // Step 1: Build adjacency list → u -> {v, price}
        unordered_map<int, vector<pair<int, int>>> adj;
        for (auto &flight : flights)
        {
            int u = flight[0], v = flight[1], price = flight[2];
            adj[u].emplace_back(v, price);
        }

        // Step 2: Min-heap → {totalCost, {currentNode, stopsSoFar}}
        using T = pair<int, pair<int, int>>;
        priority_queue<T, vector<T>, greater<>> pq;
        pq.push({0, {src, 0}}); // Initial state

        // Step 3: Track minimum stops to each node to avoid unnecessary revisits
        vector<int> minStops(n, INT_MAX);

        // Step 4: Explore graph with cost and stop tracking
        while (!pq.empty())
        {
            auto [cost, info] = pq.top();
            pq.pop();
            int node = info.first;
            int stops = info.second;

            // If destination is reached
            if (node == dst)
                return cost;

            // Prune if stops exceeded
            if (stops > k)
                continue;

            // Skip if we've already reached this node with fewer stops
            if (stops >= minStops[node])
                continue;
            minStops[node] = stops;

            // Explore all neighbors
            for (auto &[neighbor, weight] : adj[node])
            {
                pq.push({cost + weight, {neighbor, stops + 1}});
            }
        }

        // Destination not reachable within k stops
        return -1;
    }
};

/* ===================================================================
 * LEETCODE 721: ACCOUNTS MERGE
 * =================================================================== */

/**
 * @brief Given accounts with multiple emails, merge all accounts that share
 *        at least one common email. Output should be [name, sorted emails...].
 *
 * APPROACH (Disjoint Set Union - DSU):
 * - Treat each account as a node.
 * - If two accounts share an email, connect them (union operation).
 * - Finally, group emails by their parent node.
 *
 * TIME COMPLEXITY: O(N * α(N) + E log E), where N = accounts, E = emails
 * SPACE COMPLEXITY: O(N + E)
 */

class DisjointSet
{
    vector<int> parent, size;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // path compression
    }

    void unionBySize(int u, int v)
    {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv)
            return;

        if (size[pu] < size[pv])
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution
{
public:
    /**
     * @brief Merges accounts with common emails using DSU
     *
     * @param accounts  List of accounts: [name, email1, email2, ...]
     * @return          Merged account list
     */
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        int n = accounts.size();
        DisjointSet ds(n);

        unordered_map<string, int> emailToIndex; // email → account index

        // Step 1: Union accounts with shared emails
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < accounts[i].size(); ++j)
            {
                string email = accounts[i][j];
                if (emailToIndex.count(email))
                {
                    ds.unionBySize(i, emailToIndex[email]);
                }
                else
                {
                    emailToIndex[email] = i;
                }
            }
        }

        // Step 2: Group emails by parent index
        vector<string> mergedEmails[n];
        for (auto &[email, idx] : emailToIndex)
        {
            int parent = ds.findUPar(idx);
            mergedEmails[parent].push_back(email);
        }

        // Step 3: Build final result
        vector<vector<string>> result;
        for (int i = 0; i < n; ++i)
        {
            if (mergedEmails[i].empty())
                continue;

            sort(mergedEmails[i].begin(), mergedEmails[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]); // account name
            temp.insert(temp.end(), mergedEmails[i].begin(), mergedEmails[i].end());
            result.push_back(temp);
        }

        return result;
    }
};

/* ==============================================================================
 * LeetCode 2106: Maximum Fruits Harvested After at Most K Steps
 * ==============================================================================
 * Problem:
 * You are given a list of `fruits`, where `fruits[i] = [position, amount]`, a starting
 * position `startPos`, and an integer `k`. You can move at most `k` steps and pick all
 * fruits at each visited position. Return the **maximum total fruits** you can harvest.
 *
 * Approach: Sliding Window + Min Steps Calculation
 * - Use a sliding window [left, right] over sorted fruit positions.
 * - Expand the right boundary and accumulate fruits.
 * - Shrink from the left if the minimal steps needed to collect [left, right]
 *   from startPos exceeds `k`.
 * - `minSteps()` calculates the fewest moves to cover [left, right] range from startPos.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k)
    {
        int left = 0, sum = 0, maxFruits = 0;

        for (int right = 0; right < fruits.size(); ++right) {
            sum += fruits[right][1];  // Add current fruit amount

            // Shrink window if out of allowed step range
            while (left <= right && minSteps(fruits[left][0], fruits[right][0], startPos) > k) {
                sum -= fruits[left][1];
                left++;
            }

            maxFruits = max(maxFruits, sum);  // Update result
        }

        return maxFruits;
    }

private:
    // Compute minimal steps to collect fruits from [left, right] range starting at start
    int minSteps(int left, int right, int start)
    {
        return min(abs(start - left) + (right - left),
            abs(start - right) + (right - left));
    }
};

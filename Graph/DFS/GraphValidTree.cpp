#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Graph Valid Tree (LeetCode 261)
================================================================================
Task:
    You have a graph of n nodes labeled from 0 to n - 1 and a list of edges.
    Check if these edges form a valid tree.

    Conditions for a graph to be a valid tree:
      1. It must be connected (all nodes reachable).
      2. It must be acyclic (no cycles).

--------------------------------------------------------------------------------
Approach (DFS Traversal):
    1. A valid tree with n nodes must have exactly (n - 1) edges.
       If not, return false immediately.
    2. Build an adjacency list from the given edges.
    3. Run DFS from node 0 while checking:
        - If a visited node is encountered again (other than parent), a cycle exists.
        - Mark visited nodes to avoid revisiting.
    4. After DFS, ensure all nodes were visited → graph is connected.
    5. If both conditions (no cycles + connected) are satisfied → it's a valid tree.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(N + E)
        - N nodes and E edges are processed once.
    Space Complexity: O(N + E)
        - Adjacency list + visited array + recursion stack.
================================================================================
*/

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> visited;
    int n;

    bool dfs(int node, int parent)
    {
        visited[node] = 1;
        for (int nei : adj[node]) {
            if (nei == parent) continue;      // Ignore edge to parent
            if (visited[nei]) return false;   // Cycle detected
            if (!dfs(nei, node)) return false;
        }
        return true;
    }

    bool validTree(int n, vector<vector<int>>& edges)
    {
        if (edges.size() != n - 1) return false; // Must have n-1 edges

        this->n = n;
        adj.assign(n, {});
        visited.assign(n, 0);

        // Build adjacency list
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // DFS from node 0
        if (!dfs(0, -1)) return false;

        // Ensure all nodes are visited (graph is connected)
        for (int i = 0; i < n; i++) {
            if (!visited[i]) return false;
        }
        return true;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 5
    edges = [[0,1],[0,2],[0,3],[1,4]]
Output:
    true
Explanation:
    Graph has 5 nodes, 4 edges, no cycles, and is fully connected.

--------------------------------------------------------------------------------
Input:
    n = 5
    edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output:
    false
Explanation:
    Cycle exists (1-2-3-1), so it's not a valid tree.

--------------------------------------------------------------------------------
Input:
    n = 4
    edges = [[0,1],[2,3]]
Output:
    false
Explanation:
    Graph is disconnected, so not a tree.
================================================================================
*/


#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Course Schedule IV (LeetCode 1462)
================================================================================
Task:
    There are `numCourses` courses labeled from `0` to `numCourses - 1`.
    Given a list of prerequisite pairs and queries, return a boolean array
    `result` where `result[i]` is true if course `queries[i][0]`
    is a prerequisite of course `queries[i][1]`, otherwise false.

--------------------------------------------------------------------------------
Approach (DFS per query):
    1. Build an adjacency list from prerequisites (u → v).
    2. For each query (source, dest):
        - Run a DFS from `source` to see if we can reach `dest`.
        - Maintain a visited array to avoid cycles.
        - If path exists → mark `true`.
    3. Store results for all queries.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let V = numCourses, E = prerequisites.size(), Q = queries.size().

    Time Complexity:  O(Q * (V + E))
        - For each query, DFS may traverse entire graph in worst case.
    Space Complexity: O(V + E)
        - Adjacency list + visited array.
================================================================================
*/

class Solution {
public:
    // DFS helper: check if dest reachable from source
    bool dfs(vector<vector<int>>& adj, int source, int dest, vector<bool>& visited)
    {
        if (source == dest) return true;
        visited[source] = true;

        for (auto nxt : adj[source]) {
            if (!visited[nxt]) {
                if (dfs(adj, nxt, dest, visited))
                    return true;
            }
        }
        return false;
    }

    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(numCourses);
        for (auto& x : prerequisites) {
            int u = x[0], v = x[1];
            adj[u].push_back(v);
        }

        // Step 2: Process queries
        vector<bool> result(queries.size(), false);
        for (int i = 0; i < queries.size(); i++) {
            int source = queries[i][0], dest = queries[i][1];
            vector<bool> visited(numCourses, false);
            result[i] = dfs(adj, source, dest, visited);
        }

        return result;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    numCourses = 2
    prerequisites = [[0,1]]
    queries = [[0,1], [1,0]]

Output:
    [true, false]

Explanation:
    - 0 is prerequisite for 1 → true
    - 1 is not prerequisite for 0 → false
--------------------------------------------------------------------------------
Notes:
    - This DFS-per-query approach is simple but not optimal.
    - More efficient methods:
        * Floyd-Warshall for transitive closure (O(V^3))
        * BFS/DFS with memoization
        * Topological + DP propagation
================================================================================
*/


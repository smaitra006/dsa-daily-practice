#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Possible Bipartition (LeetCode 886)
================================================================================
Task:
    Given n people (labeled 1 to n) and a list of dislikes (pairs of people who
    dislike each other), determine if it is possible to split everyone into
    two groups such that no two people in the same group dislike each other.

--------------------------------------------------------------------------------
Key Insight:
    - This is equivalent to checking if the graph formed by dislikes is bipartite.
    - If the graph can be 2-colored without conflicts → possible bipartition.
    - DFS or BFS coloring works for this.

--------------------------------------------------------------------------------
Approach (DFS Coloring):
    1. Build adjacency list from the dislikes array.
    2. Initialize a color array with -1 (uncolored).
    3. For each uncolored person:
        - Run DFS to color the graph:
            - Assign current color.
            - If a neighbor has the same color → return false.
            - If uncolored, DFS with opposite color.
    4. If all nodes can be colored consistently → return true.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of people, e = number of dislikes (edges).
    - Time Complexity:  O(n + e)
        Each node and edge is visited once.
    - Space Complexity: O(n + e)
        For adjacency list + recursion stack + color array.
================================================================================
*/

class Solution {
public:
    // Helper: DFS to check bipartite coloring
    bool dfsBipartite(vector<vector<int>>& graph, vector<int>& color, int node, int curr_color)
    {
        color[node] = curr_color;

        for (auto neighbour : graph[node]) {
            // Conflict detected
            if (color[neighbour] == curr_color) {
                return false;
            }
            // Uncolored neighbor → DFS with opposite color
            if (color[neighbour] == -1) {
                if (!dfsBipartite(graph, color, neighbour, 1 - curr_color)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(n + 1);
        for (auto x : dislikes) {
            int u = x[0];
            int v = x[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Step 2: Initialize color array (-1 = uncolored)
        vector<int> color(n + 1, -1);

        // Step 3: Check all components
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) {
                if (!dfsBipartite(adj, color, i, 0)) {
                    return false;
                }
            }
        }

        return true;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 4
    dislikes = [[1,2],[1,3],[2,4]]

Output:
    true

Explanation:
    - Group 1: [1,4]
    - Group 2: [2,3]
    - No two people in the same group dislike each other.
================================================================================
*/


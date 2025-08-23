#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Maximum Detonation (LeetCode 2101)
================================================================================
Task:
    You are given a list of bombs. Each bomb is represented as [x, y, r],
    where (x, y) is the coordinate and r is the radius of the bomb.

    - A bomb can detonate another bomb if the other bomb is within its radius.
    - Chain reactions are allowed: detonated bombs can trigger others.

    Return the maximum number of bombs that can be detonated if you choose
    a single bomb to start the detonation.

--------------------------------------------------------------------------------
Key Insight:
    - Represent bombs as a **directed graph**:
        - Edge from bomb A → bomb B if B is within A's blast radius.
    - The problem reduces to **finding the largest reachable component** in the graph.
    - DFS can simulate chain reactions starting from each bomb.

--------------------------------------------------------------------------------
Approach (DFS + Graph):
    1. Build adjacency list:
        - For each bomb i, connect i → j if distance(i,j) <= radius_i^2.
    2. For each bomb i:
        - Run DFS to count how many bombs can be reached (detonated) starting from i.
        - Keep track of the maximum count.
    3. Return the maximum number of detonated bombs.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of bombs.
    - Time Complexity:  O(n^2)
        - Building adjacency: O(n^2)
        - DFS from each node: O(n^2) in worst case
    - Space Complexity: O(n^2)
        - Adjacency list + visited array
================================================================================
*/

class Solution {
public:
    // DFS to count reachable bombs
    int dfs(int node, vector<vector<int>>& adj, vector<bool>& visited)
    {
        visited[node] = true;
        int count = 1; // Count current bomb
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                count += dfs(neighbor, adj, visited);
            }
        }
        return count;
    }

    int maximumDetonation(vector<vector<int>>& bombs)
    {
        int n = bombs.size();
        vector<vector<int>> adj(n);

        // Step 1: Build adjacency list
        for (int i = 0; i < n; i++) {
            long long x1 = bombs[i][0], y1 = bombs[i][1], r = bombs[i][2];
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                long long x2 = bombs[j][0], y2 = bombs[j][1];
                long long dx = x1 - x2, dy = y1 - y2;
                long long distSq = dx * dx + dy * dy;
                if (distSq <= r * r) {
                    adj[i].push_back(j);
                }
            }
        }

        // Step 2: Try detonating each bomb
        int maxDetonated = 0;
        for (int i = 0; i < n; i++) {
            vector<bool> visited(n, false);
            maxDetonated = max(maxDetonated, dfs(i, adj, visited));
        }

        return maxDetonated;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    bombs = [[2,1,3],[6,1,4]]

Output:
    2

Explanation:
    - Detonating bomb 0 triggers bomb 0 itself.
    - Detonating bomb 1 triggers bomb 1 itself.
    - Max detonated bombs = 2 (if bomb 0 triggers bomb 1 via chain, depends on radius).
================================================================================
*/

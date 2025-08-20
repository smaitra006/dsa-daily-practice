#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Jump Game III (LeetCode 1306)
================================================================================
Task:
    Given an array of non-negative integers `arr` and an integer `start`
    representing the starting index, determine if you can reach any index with
    value 0.

    From index `i`, you can jump either to:
        - i + arr[i], or
        - i - arr[i],
    provided the destination index is within bounds.

--------------------------------------------------------------------------------
Approach (BFS Traversal):
    1. Model the array as a graph where each index has up to 2 neighbors
       (i + arr[i] and i - arr[i]).
    2. Use BFS starting from `start`:
        - If the value at the current index is 0 → return true.
        - Otherwise, enqueue all unvisited valid neighbors.
    3. If BFS finishes without finding a 0 → return false.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(N)
        - Each index is visited at most once.
    Space Complexity: O(N)
        - Visited array + BFS queue.
================================================================================
*/

class Solution {
public:
    bool canReach(vector<int>& arr, int start)
    {
        int n = arr.size();
        if (arr[start] == 0) return true;

        // Build adjacency list (optional, since we can compute neighbors directly)
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            if (i + arr[i] < n) adj[i].push_back(i + arr[i]);
            if (i - arr[i] >= 0) adj[i].push_back(i - arr[i]);
        }

        queue<int> q;
        vector<int> visited(n, 0);
        q.push(start);
        visited[start] = 1;

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                int node = q.front();
                q.pop();

                if (arr[node] == 0) return true; // Reached zero

                for (auto neighbour : adj[node]) {
                    if (!visited[neighbour]) {
                        q.push(neighbour);
                        visited[neighbour] = 1;
                    }
                }
            }
        }
        return false;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    arr = [4,2,3,0,3,1,2], start = 5
Output:
    true
Explanation:
    From index 5 → jump to 4 → jump to 1 → jump to 3 (arr[3] == 0).

--------------------------------------------------------------------------------
Input:
    arr = [4,2,3,0,3,1,2], start = 0
Output:
    true
Explanation:
    From index 0 → jump to 4 → jump to 1 → jump to 3 (arr[3] == 0).

--------------------------------------------------------------------------------
Input:
    arr = [3,0,2,1,2], start = 2
Output:
    false
Explanation:
    No sequence of jumps leads to a 0.
================================================================================
*/


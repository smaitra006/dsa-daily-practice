#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Sequence Reconstruction (LeetCode 444)
================================================================================
Task:
    Check whether the original sequence can be uniquely reconstructed from the
    given list of subsequences. The sequence is reconstructable if:
      1. The sequence can be reconstructed at all.
      2. The sequence is unique (only one possible order).

--------------------------------------------------------------------------------
Approach (Topological Sort - Kahn's Algorithm):
    1. Build a directed graph:
        - Each pair (u -> v) from subsequences defines ordering.
        - Track indegree of each node.
    2. Perform Topological Sort:
        - Use a queue for nodes with indegree 0.
        - At each step, check:
            - If more than one node has indegree 0 → multiple valid orders.
            - If the current popped node ≠ nums[index] → mismatch with original.
        - Continue until all nodes are processed.
    3. If the entire nums sequence matches the reconstructed order → return true.
       Otherwise → return false.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = length of nums, M = total length of subsequences.

    Time Complexity:  O(N + M)
        - Graph construction: O(M).
        - Topological sort: O(N + edges).

    Space Complexity: O(N + M)
        - For adjacency list, indegree map, and visited structures.
================================================================================
*/

class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences)
    {
        int n = nums.size();

        // Step 1: Build adjacency list & indegree map
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> indegree;
        for (int num : nums) indegree[num] = 0;

        for (auto& seq : sequences) {
            for (int i = 1; i < seq.size(); i++) {
                int u = seq[i - 1], v = seq[i];
                adj[u].push_back(v);
                indegree[v]++;
            }
        }

        // Step 2: Topological Sort (Kahn’s Algorithm)
        queue<int> q;
        for (auto& [node, deg] : indegree) {
            if (deg == 0) q.push(node);
        }

        int idx = 0;
        while (!q.empty()) {
            if (q.size() > 1) return false;   // Multiple possible orders → not unique
            int curr = q.front(); q.pop();

            if (nums[idx++] != curr) return false; // Order mismatch

            for (int nxt : adj[curr]) {
                indegree[nxt]--;
                if (indegree[nxt] == 0) q.push(nxt);
            }
        }

        return idx == n;  // Must reconstruct exactly nums
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    nums = [1,2,3]
    sequences = [[1,2],[1,3]]

Output:
    false

Explanation:
    Both [1,2,3] and [1,3,2] are valid reconstructions → not unique.
--------------------------------------------------------------------------------
Input:
    nums = [1,2,3]
    sequences = [[1,2],[2,3]]

Output:
    true

Explanation:
    Only one possible order exists → [1,2,3].
--------------------------------------------------------------------------------
Notes:
    - This is a **unique topological sort problem**.
    - Condition: At every step, exactly one valid node with indegree 0.
    - If mismatch or multiple options → return false.
================================================================================
*/

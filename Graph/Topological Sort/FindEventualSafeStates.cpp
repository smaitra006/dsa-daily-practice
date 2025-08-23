#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Find Eventual Safe States (LeetCode 802)
================================================================================
Task:
    Given a directed graph where graph[i] is a list of nodes that node i points to,
    return all the nodes that are **eventually safe**.

    - A node is eventually safe if every possible path starting from that node
      leads to a terminal node (no cycles).
    - Return the list of safe nodes in sorted order.

--------------------------------------------------------------------------------
Key Insight:
    - Nodes that are part of cycles or can reach cycles are unsafe.
    - Terminal nodes (outdegree 0) are safe.
    - This is equivalent to **finding nodes not part of any cycle**.
    - Reverse the graph and use **Kahn's algorithm (topological sort)**.

--------------------------------------------------------------------------------
Approach (BFS / Topological Sort):
    1. Build the **reverse graph**:
        - For each edge u → v, add v → u in the reversed adjacency.
        - Track indegree of original graph nodes.
    2. Initialize a queue with nodes having indegree 0 (terminal nodes in original graph).
    3. Process queue:
        - Pop node, mark as safe (add to result).
        - Reduce indegree of its neighbors in reversed graph.
        - If indegree becomes 0, push neighbor to queue.
    4. Sort result and return.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of nodes, e = number of edges.
    - Time Complexity:  O(n + e)
        - Building reverse graph: O(e)
        - BFS processing: O(n + e)
    - Space Complexity: O(n + e)
        - Reverse adjacency + indegree array + queue + result
================================================================================
*/

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        int n = graph.size();
        vector<vector<int>> adj(n); // Reverse graph
        vector<int> indegree(n, 0);
        vector<int> result;

        // Step 1: Build reverse graph and indegree array
        for (int i = 0; i < n; i++) {
            for (auto v : graph[i]) {
                adj[v].push_back(i);  // Reverse edge
                indegree[i]++;         // Original node indegree
            }
        }

        // Step 2: Initialize queue with terminal nodes
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: BFS topological sort to mark safe nodes
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            result.push_back(curr);

            for (auto neighbour : adj[curr]) {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0) {
                    q.push(neighbour);
                }
            }
        }

        // Step 4: Return sorted result
        sort(result.begin(), result.end());
        return result;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    graph = [[1,2],[2,3],[5],[0],[5],[],[]]

Output:
    [2,4,5,6]

Explanation:
    - Nodes 2,4,5,6 are safe; all paths from them eventually reach terminal nodes.
================================================================================
*/


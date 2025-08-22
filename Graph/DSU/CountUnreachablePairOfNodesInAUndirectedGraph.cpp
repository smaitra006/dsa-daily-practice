#include <bits/stdc++.h>
using namespace std;

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

        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }
    }

    long long countPairs(int n, vector<vector<int>>& edges)
    {
        parent.resize(n);
        rank.resize(n, 0);

        // Step 1: Initialize each node as its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        // Step 2: Union all connected nodes
        for (auto& edge : edges) {
            Union(edge[0], edge[1]);
        }

        // Step 3: Count size of each component using parent map
        unordered_map<int, int> componentSize;
        for (int i = 0; i < n; i++) {
            int p = findParent(i);
            componentSize[p]++;
        }

        // Step 4: Count unreachable pairs
        long long totalPairs = 0;
        long long remaining = n;

        for (auto& [leader, size] : componentSize) {
            totalPairs += size * (remaining - size);
            remaining -= size;
        }

        return totalPairs;
    }
};

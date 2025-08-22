#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Redundant Connection (LeetCode 684)
================================================================================
Task:
    In this problem, a tree is an undirected graph that is connected and has no cycles.
    You are given a graph that started as a tree with n nodes (labeled 1 to n),
    with one additional edge added. The added edge may cause a cycle.

    Return the edge that can be removed so that the graph is still a tree.
    If there are multiple answers, return the edge that occurs last in the input.

--------------------------------------------------------------------------------
Approach (Disjoint Set Union - Union by Rank + Path Compression):
    1. Use DSU to keep track of connected components.
    2. For each edge (u, v):
        - If u and v are already connected (same root), that edge is redundant.
        - Otherwise, union them.
    3. The first edge that fails union is the redundant one.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of nodes.

    Time Complexity:  O(N * α(N)) ≈ O(N)
        - Each union/find operation is nearly O(1).

    Space Complexity: O(N)
        - DSU parent and rank arrays.
================================================================================
*/

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
public:
    // Constructor
    DSU(int n)
    {
        parent.resize(n + 1);   // 1-indexed
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;  // Cycle detected

        if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        int n = edges.size();
        DSU dsu(n);

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (!dsu.unite(u, v)) {
                // This edge forms a cycle
                return edge;
            }
        }
        return {};
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    edges = [[1,2],[1,3],[2,3]]

Output:
    [2,3]

Explanation:
    - Edge [2,3] creates a cycle with edges [1,2] and [1,3].
    - Removing [2,3] restores a tree structure.
================================================================================
*/


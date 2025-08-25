#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Making A Large Island
// Link: https://leetcode.com/problems/making-a-large-island/
//
// Task:
// Given an n x n binary grid, you are allowed to change at most one 0 into 1.
// Return the size of the largest island possible after performing this operation.
// An island is a group of 1's connected 4-directionally.
//
// Approach:
// 1. Use DSU (Disjoint Set Union) to group connected land cells (1's).
// 2. Store sizes of each connected component in DSU.
// 3. For each 0 cell, try flipping it to 1 and compute the new island size
//    by merging unique adjacent island components.
// 4. Keep track of the maximum possible island size.
//
// DSU Features:
// - Path Compression (optimizes find())
// - Union by Rank
// - Component Size Tracking
//
// Complexity:
// - Time: O(N^2 * α(N^2)) ~ O(N^2), where α is Inverse Ackermann function.
// - Space: O(N^2) for DSU parent, rank, size arrays.
//
//==============================================================================
class DSU {
private:
    vector<int> parent, rank, size;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1); // Initially, each node size = 1
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path Compression
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; //  Already in the same set

        // Union by Rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
            size[rootX] += size[rootY];
        }
        return true;
    }

    int getSize(int x)
    {
        return size[find(x)];
    }
};

//==============================================================================
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        int total = m * n;
        DSU dsu(total);

        vector<pair<int, int>> dirs = { {1,0}, {-1,0}, {0,1}, {0,-1} };

        // Step 1: Union all adjacent land cells (1's)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int id = i * n + j;
                    for (auto [dx, dy] : dirs) {
                        int ni = i + dx, nj = j + dy;
                        if (ni >= 0 && nj >= 0 && ni < m && nj < n && grid[ni][nj] == 1) {
                            int nid = ni * n + nj;
                            dsu.unite(id, nid);
                        }
                    }
                }
            }
        }

        // Step 2: Compute max island size without flipping
        int maxIsland = 0;
        for (int i = 0; i < total; i++) {
            if (grid[i / n][i % n] == 1)
                maxIsland = max(maxIsland, dsu.getSize(i));
        }

        // Step 3: Try flipping each 0 -> 1 and calculate new island size
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> seen;
                    int newSize = 1; // Current flipped cell

                    for (auto [dx, dy] : dirs) {
                        int ni = i + dx, nj = j + dy;
                        if (ni >= 0 && nj >= 0 && ni < m && nj < n && grid[ni][nj] == 1) {
                            int root = dsu.find(ni * n + nj);
                            if (seen.insert(root).second) {
                                newSize += dsu.getSize(root);
                            }
                        }
                    }
                    maxIsland = max(maxIsland, newSize);
                }
            }
        }

        return maxIsland;
    }
};

//==============================================================================
// Example Usage:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 → one large island of size 3.
//
// Input: grid = [[1,1],[1,0]]
// Output: 4
//==============================================================================

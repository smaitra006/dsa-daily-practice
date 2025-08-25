#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Number of Islands II (Leetcode 305)
//
// Task:
// You are given an empty 2D grid of size m x n. Initially all cells are water.
// We sequentially add land at positions[i] = (row, col).
// After each addition, return the number of islands in the grid.
//
// Definition of Island:
// A group of 1's (land) connected horizontally or vertically (not diagonally).
//
// Approach (Disjoint Set Union - DSU):
// 1. Treat each cell as a node in DSU, indexed as row * n + col.
// 2. For each new land added:
//      - If it’s already land, skip.
//      - Mark it as land and increase island count.
//      - Union it with adjacent land cells. If union merges two sets, reduce count.
// 3. Record the count after each addition.
//
// Complexity:
// - Time: O(k * α(m*n)), where k = number of positions, α = Inverse Ackermann (≈ constant).
// - Space: O(m*n) for DSU parent and rank arrays.
//==============================================================================

class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; // Already in same set

        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions)
    {
        DSU dsu(m * n);
        vector<int> result;
        vector<vector<int>> grid(m, vector<int>(n, 0));

        int count = 0;
        vector<int> directions = { 0, 1, 0, -1, 0 }; // Right, Down, Left, Up

        for (auto& pos : positions) {
            int r = pos[0], c = pos[1];

            // Skip if already land
            if (grid[r][c] == 1) {
                result.push_back(count);
                continue;
            }

            grid[r][c] = 1;
            count++; // New island

            int node = r * n + c;

            // Check 4 neighbors
            for (int k = 0; k < 4; k++) {
                int nr = r + directions[k];
                int nc = c + directions[k + 1];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    int neighbor = nr * n + nc;

                    // If union merges two islands, reduce count
                    if (dsu.unite(node, neighbor)) {
                        count--;
                    }
                }
            }

            result.push_back(count);
        }

        return result;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     int m = 3, n = 3;
//     vector<vector<int>> positions = {{0,0}, {0,1}, {1,2}, {2,1}};
//
//     vector<int> ans = sol.numIslands2(m, n, positions);
//     // Expected Output: [1, 1, 2, 3]
//
//     for (int x : ans) cout << x << " ";
// }
//==============================================================================

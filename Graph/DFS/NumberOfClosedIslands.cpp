#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Number of Closed Islands (LeetCode 1254)
//
// Task:
// Given a 2D grid of 0s (land) and 1s (water), a "closed island" is a group
// of 0s completely surrounded by 1s (cannot touch the boundary of the grid).
// Return the number of closed islands.
//
// Approach:
// 1. Use DFS to "flood fill" from any land cell (0).
// 2. First, eliminate all land cells connected to the boundary (since they
//    can’t form closed islands).
// 3. Then, count and flood-fill remaining islands inside the grid.
//==============================================================================

class Solution {
public:
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {0,-1}, {-1,0} };
    int m, n;

    // DFS flood-fill to mark land as visited (convert to water 2)
    void dfs(vector<vector<int>>& grid, int r, int c)
    {
        grid[r][c] = 2; // mark visited
        for (auto dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                dfs(grid, nr, nc);
            }
        }
    }

    int closedIsland(vector<vector<int>>& grid)
    {
        m = grid.size();
        n = grid[0].size();

        // Step 1: Eliminate all boundary-connected islands
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 0) dfs(grid, i, 0);
            if (grid[i][n - 1] == 0) dfs(grid, i, n - 1);
        }
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 0) dfs(grid, 0, j);
            if (grid[m - 1][j] == 0) dfs(grid, m - 1, j);
        }

        // Step 2: Count closed islands
        int island_cnt = 0;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 0) {
                    island_cnt++;
                    dfs(grid, i, j);
                }
            }
        }
        return island_cnt;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(m * n)   (each cell visited at most once)
// - Space: O(m * n)  (DFS recursion stack in worst case)
//
// Example:
// Input:
// grid = [[1,1,1,1,1,1,1,0],
//         [1,0,0,0,0,1,1,0],
//         [1,0,1,0,1,1,1,0],
//         [1,0,0,0,0,1,0,1],
//         [1,1,1,1,1,1,1,0]]
//
// Output: 2
//==============================================================================

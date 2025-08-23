#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Number of Enclaves (LeetCode 1020)
================================================================================
Task:
    You are given an m x n binary matrix `grid` where:
      - 0 represents water
      - 1 represents land

    A land cell (1) can move in 4 directions (up, down, left, right).
    Return the number of land cells in `grid` that **cannot reach the boundary**.

--------------------------------------------------------------------------------
Key Insight:
    - Any land cell connected to the boundary is NOT an enclave.
    - Enclaves are land cells completely surrounded by water and not touching border.
    - Strategy:
        1. Traverse all border cells and run DFS/BFS to "flood out" boundary-connected land.
        2. After marking them (turning into water), the remaining land cells are enclaves.
        3. Count them.

--------------------------------------------------------------------------------
Approach (DFS):
    1. Traverse border cells:
        - If land (1), run DFS to mark it and all connected land as 0 (water).
    2. After DFS, traverse the grid and count remaining 1’s.
    3. Return count.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.
    - Time Complexity:  O(m * n)
        Each cell is visited at most once.
    - Space Complexity: O(m * n) in worst case (recursion stack).
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };

    // DFS to "flood" boundary-connected land into water
    void dfs(vector<vector<int>>& grid, int sr, int sc)
    {
        grid[sr][sc] = 0;

        for (auto dir : directions) {
            int nr = sr + dir.first;
            int nc = sc + dir.second;

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                dfs(grid, nr, nc);
            }
        }
    }

    int numEnclaves(vector<vector<int>>& grid)
    {
        m = grid.size();
        n = grid[0].size();

        // Step 1: Flood out boundary-connected land
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1) dfs(grid, i, 0);
            if (grid[i][n - 1] == 1) dfs(grid, i, n - 1);
        }
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) dfs(grid, 0, j);
            if (grid[m - 1][j] == 1) dfs(grid, m - 1, j);
        }

        // Step 2: Count remaining land (enclaves)
        int enclaves = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) enclaves++;
            }
        }

        return enclaves;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [[0,0,0,0],
            [1,0,1,0],
            [0,1,1,0],
            [0,0,0,0]]

Output:
    3

Explanation:
    - Land cells connected to border are removed.
    - Remaining land cells = 3 enclaves.
================================================================================
*/


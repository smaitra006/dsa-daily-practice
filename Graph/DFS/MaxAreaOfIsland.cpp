#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Max Area of Island (LeetCode 695)
================================================================================
Task:
    You are given an m x n binary matrix grid. An island is a group of 1's
    (representing land) connected 4-directionally (horizontal or vertical).
    You may assume all four edges of the grid are surrounded by water.

    The area of an island is the number of cells with a value 1 in the island.

    Return the maximum area of an island in grid. If there is no island, return 0.

--------------------------------------------------------------------------------
Approach (DFS Traversal + Counting Area):
    1. Traverse every cell in the grid.
    2. When an unvisited land cell (1) is found:
        - Initialize a counter `cnt` for the current island.
        - Run DFS to explore all connected land cells and count their total area.
    3. Keep track of the maximum area encountered among all islands.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(M * N)
        - Each cell is visited at most once.
    Space Complexity: O(M * N)
        - Visited matrix + recursive DFS stack space.
================================================================================
*/

class Solution {
public:
    int m, n;
    int cnt = 0;  // Current island area counter
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // 4 directions

    // Depth First Search to explore an island and count its area
    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& visited)
    {
        visited[r][c] = 1;
        cnt++; // Count this land cell

        for (auto dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;

            if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                grid[nr][nc] == 1 && !visited[nr][nc]) {
                dfs(grid, nr, nc, visited);
            }
        }
    }

    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        m = grid.size();
        n = grid[0].size();
        int maxCnt = 0;

        vector<vector<int>> visited(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    cnt = 0;                       // Reset counter for new island
                    dfs(grid, i, j, visited);      // Explore and count area
                    maxCnt = max(maxCnt, cnt);     // Update max area
                }
            }
        }
        return maxCnt;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [
      [0,0,1,0,0,0,0,1,0,0,0,0,0],
      [0,0,0,0,0,0,0,1,1,1,0,0,0],
      [0,1,1,0,1,0,0,0,0,0,0,0,0],
      [0,1,0,0,1,1,0,0,1,0,1,0,0],
      [0,1,0,0,1,1,0,0,1,1,1,0,0],
      [0,0,0,0,0,0,0,0,0,0,1,0,0],
      [0,0,0,0,0,0,0,1,1,1,0,0,0],
      [0,0,0,0,0,0,0,1,1,0,0,0,0]
    ]
Output:
    6

--------------------------------------------------------------------------------
Input:
    grid = [
      [0,0,0,0,0,0,0,0]
    ]
Output:
    0
================================================================================
*/


#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Number of Islands (LeetCode 200)
================================================================================
Task:
    Given an m x n 2D binary grid grid which represents a map of '1's (land)
    and '0's (water), return the number of islands.

    An island is surrounded by water and is formed by connecting adjacent lands
    horizontally or vertically. You may assume all four edges of the grid are
    surrounded by water.

--------------------------------------------------------------------------------
Approach (DFS Traversal):
    1. Traverse every cell in the grid.
    2. When an unvisited land cell ('1') is found:
        - Increment the island count.
        - Run DFS from this cell to mark all connected land cells as visited.
    3. DFS explores in 4 directions (up, down, left, right) and ensures that
       connected land cells are grouped as part of the same island.

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
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // 4 directions

    // Depth First Search to explore the island
    void dfs(vector<vector<char>>& grid, int r, int c, vector<vector<int>>& visited)
    {
        visited[r][c] = 1;
        for (auto dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                grid[nr][nc] == '1' && !visited[nr][nc]) {
                dfs(grid, nr, nc, visited);
            }
        }
    }

    int numIslands(vector<vector<char>>& grid)
    {
        m = grid.size();
        n = grid[0].size();
        int cnt = 0;

        vector<vector<int>> visited(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    cnt++;                 // Found a new island
                    dfs(grid, i, j, visited);
                }
            }
        }
        return cnt;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [
      ['1','1','1','1','0'],
      ['1','1','0','1','0'],
      ['1','1','0','0','0'],
      ['0','0','0','0','0']
    ]
Output:
    1

--------------------------------------------------------------------------------
Input:
    grid = [
      ['1','1','0','0','0'],
      ['1','1','0','0','0'],
      ['0','0','1','0','0'],
      ['0','0','0','1','1']
    ]
Output:
    3
================================================================================
*/

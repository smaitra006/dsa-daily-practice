#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Detect Cycles in 2D Grid (LeetCode 1559)
================================================================================
Task:
    Given a 2D grid of characters, determine if there exists a cycle of the same
    character. A cycle is formed if:
      - Starting from a cell, you can move to adjacent cells (up, down, left, right),
      - All cells in the path have the same character,
      - You can return to the starting cell,
      - The cycle length is >= 4.

    Return true if such a cycle exists, otherwise false.

--------------------------------------------------------------------------------
Key Insight:
    - This is a **graph cycle detection problem** in a grid.
    - Each cell is a node, connected to its neighbors if they have the same char.
    - Perform DFS while tracking the parent cell.
    - If a visited neighbor is not the parent, a cycle is found.

--------------------------------------------------------------------------------
Approach (DFS with Parent Tracking):
    1. Iterate over all cells.
    2. If a cell is unvisited, run DFS from it:
        - Mark cell visited.
        - Explore neighbors with the same character.
        - Skip if out of bounds or different character.
        - If neighbor not visited, recurse with current as parent.
        - If neighbor visited and not the parent → cycle detected.
    3. If any DFS detects a cycle, return true.
    4. Otherwise, return false.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.
    - Time Complexity:  O(m * n)
        Each cell is visited once during DFS.
    - Space Complexity: O(m * n)
        Visited matrix + recursion stack.
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };

    // DFS to detect cycle in grid
    bool dfs(vector<vector<char>>& grid, int x, int y, int px, int py, char ch, vector<vector<bool>>& visited)
    {
        visited[x][y] = true;

        for (auto dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;

            // Boundary check
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

            // Must be the same character to continue
            if (grid[nx][ny] != ch) continue;

            if (!visited[nx][ny]) {
                if (dfs(grid, nx, ny, x, y, ch, visited)) {
                    return true; // Cycle detected in recursion
                }
            }
            else if (nx != px || ny != py) {
                // Already visited and not the parent → cycle found
                return true;
            }
        }
        return false;
    }

    bool containsCycle(vector<vector<char>>& grid)
    {
        m = grid.size();
        n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Check all cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) {
                    if (dfs(grid, i, j, -1, -1, grid[i][j], visited)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [["a","a","a","a"],
            ["a","b","b","a"],
            ["a","b","b","a"],
            ["a","a","a","a"]]

Output:
    true

Explanation:
    The border 'a' cells form a cycle.
================================================================================
*/


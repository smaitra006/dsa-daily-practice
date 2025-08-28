#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Shortest Bridge (LeetCode 934)
//
// You are given a binary grid where 0 represents water and 1 represents land.
// There are exactly two islands in the grid. An island is formed by connecting
// adjacent lands horizontally or vertically. You may change 0's into 1's to
// connect the two islands.
//
// Task: Return the smallest number of 0's that must be flipped to connect
// the two islands.
//
// Approach:
// 1. Find the first island using DFS and mark all its cells.
// 2. Use BFS starting from all cells of the first island to expand outward
//    level by level until reaching the second island.
// 3. The BFS level count gives the minimum number of flips needed.
//
// Complexity:
// - DFS for marking first island: O(m * n)
// - BFS expansion: O(m * n)
// - Overall: O(m * n), where m, n = grid dimensions.
//==============================================================================

class Solution {
public:
    vector<pair<int, int>> first_island;   // Stores coordinates of first island
    vector<pair<int, int>> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int m, n;

    //------------------------------------------------------------------------------
    // Depth First Search: Marks the first island and collects its coordinates
    //------------------------------------------------------------------------------
    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited)
    {
        visited[r][c] = true;
        grid[r][c] = 2;  // Mark as part of first island
        first_island.push_back({ r, c });

        for (auto dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n
                && grid[nr][nc] == 1 && !visited[nr][nc]) {
                dfs(grid, nr, nc, visited);
            }
        }
    }

    //------------------------------------------------------------------------------
    // Main Function: Shortest Bridge
    //------------------------------------------------------------------------------
    int shortestBridge(vector<vector<int>>& grid)
    {
        m = grid.size();
        n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Step 1: Locate and mark the first island
        bool found = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, visited);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        // Step 2: BFS from all cells of first island to reach second island
        queue<pair<int, int>> q;
        for (auto& cord : first_island) {
            q.push(cord);
        }

        int steps = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c] = q.front();
                q.pop();

                // If we reach the second island
                if (grid[r][c] == 1) {
                    return steps - 1;
                }

                // Explore neighbors
                for (auto dir : directions) {
                    int nr = r + dir.first;
                    int nc = c + dir.second;
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({ nr, nc });
                    }
                }
            }
            steps++;
        }

        return -1; // Should not happen (problem guarantees two islands exist)
    }
};

//==============================================================================
// Example Usage:
// Input: grid = [[0,1],[1,0]]
// Output: 1
//
// Explanation: Flip one 0 → [[1,1],[1,0]] connects the islands.
//==============================================================================

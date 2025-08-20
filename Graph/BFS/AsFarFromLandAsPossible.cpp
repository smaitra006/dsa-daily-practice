#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: As Far from Land as Possible (LeetCode 1162)
================================================================================
Task:
    Given an n x n grid containing only 0s (water) and 1s (land), return the
    maximum distance of a water cell from the nearest land cell.

    If the grid contains only land or only water, return -1.

--------------------------------------------------------------------------------
Approach (Multi-Source BFS):
    1. Push all land cells into a queue as starting points (multi-source BFS).
    2. Perform BFS level by level:
        - Each step expands outward from all land cells simultaneously.
        - Water cells (0) are converted into land (1) when reached.
    3. The last BFS level processed gives the maximum distance from land.
    4. Edge Cases:
        - If no land cells exist → return -1.
        - If the grid is full of land → return -1.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(N^2)
        - Each cell is pushed/popped at most once.
    Space Complexity: O(N^2)
        - Queue + grid storage.
================================================================================
*/

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid)
    {
        int n = grid.size();
        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };

        // Push all land cells into the queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({ i, j });
                }
            }
        }

        // Edge cases: no land or all land
        if (q.empty() || q.size() == n * n) return -1;

        int dist = -1;

        // BFS Expansion
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c] = q.front();
                q.pop();

                for (auto [dr, dc] : directions) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        grid[nr][nc] = 1;       // Mark as visited (converted to land)
                        q.push({ nr, nc });
                    }
                }
            }
            dist++;  // Increment after finishing a level
        }

        return dist;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [
      [1,0,1],
      [0,0,0],
      [1,0,1]
    ]
Output:
    2
Explanation:
    The water cell at (1,1) is at distance 2 from the nearest land.

--------------------------------------------------------------------------------
Input:
    grid = [
      [1,0,0],
      [0,0,0],
      [0,0,0]
    ]
Output:
    4
Explanation:
    The farthest water cell (2,2) is 4 steps away from the nearest land (0,0).

--------------------------------------------------------------------------------
Input:
    grid = [
      [1,1],
      [1,1]
    ]
Output:
    -1
Explanation:
    Grid has only land → return -1.
================================================================================
*/


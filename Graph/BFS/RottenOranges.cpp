#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 994: ROTTING ORANGES (LeetCode)
 * =================================================================== */

 /**
  * @brief Find the minimum number of minutes to rot all oranges
  *
  * PROBLEM STATEMENT:
  * Given a 2D grid:
  * - 0 = empty cell
  * - 1 = fresh orange
  * - 2 = rotten orange
  * Each minute, any fresh orange adjacent (4-directionally) to a rotten orange
  * becomes rotten. Return the minimum number of minutes that must elapse until
  * no cell has a fresh orange. If impossible, return -1.
  *
  * EXAMPLE:
  * Input:
  *   grid = [[2,1,1],[1,1,0],[0,1,1]]
  * Output: 4
  *
  * APPROACH:
  * - BFS traversal from all initially rotten oranges
  * - Each level of BFS represents a minute passed
  * - Count remaining fresh oranges; if any left at the end → return -1
  *
  * @param grid 2D grid of integers
  * @return int Minimum minutes to rot all oranges, or -1 if impossible
  *
  * @complexity
  * Time: O(m * n)
  * Space: O(m * n)
  */

class Solution
{
public:
    int orangesRotting(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;

        // Step 1: Count fresh oranges and enqueue all rotten ones
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({ i, j });
                }
                else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0)
            return 0;

        int minutes = -1;
        vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

        // Step 2: BFS traversal
        while (!q.empty()) {
            int sz = q.size();
            minutes++;

            while (sz--) {
                pair<int, int> curr = q.front();
                q.pop();
                int r = curr.first;
                int c = curr.second;

                for (int d = 0; d < 4; d++) {
                    int nr = r + directions[d].first;
                    int nc = c + directions[d].second;

                    if (nr >= 0 && nc >= 0 && nr < m && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        fresh--;
                        q.push({ nr, nc });
                    }
                }
            }
        }

        return (fresh == 0) ? minutes : -1;
    }
};


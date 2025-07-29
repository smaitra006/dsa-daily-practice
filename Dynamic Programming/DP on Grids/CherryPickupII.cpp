#include <bits/stdc++.h>
using namespace std;

/* =============================================================
 *  Leetcode 1463 – Cherry Pickup II
 * ============================================================= */

class Solution
{
public:
    // directions for the 3 possible moves
    vector<int> directions = { -1, 0, 1 };

    /* =========================================================================
     * METHOD 1: PURE RECURSION (TLE)
     * TIME: O(3^m * 3^m) | SPACE: O(m)
     * ========================================================================= */
    int recur(int i, int j1, int j2, vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();

        // going outside the bounds base case
        if (j1 < 0 || j1 >= n || j2 < 0 || j2 >= n)
            return -1e8;

        // reached the bottom row
        if (i == m - 1) {
            // if reached same position then send it only once, otherwise send the sum of both
            return (j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        }

        int maxCherries = INT_MIN;
        // for each dir taken by first robot the other robot has 3 more choices of dir to go (9 choices)
        for (int dj1 : directions) {
            for (int dj2 : directions) {
                // if same place then taken only once
                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                value += recur(i + 1, j1 + dj1, j2 + dj2, grid);
                maxCherries = max(maxCherries, value);
            }
        }

        return maxCherries;
    }

    /* =========================================================================
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n * n * 9) = O(m * n²)
     * SPACE: O(m * n²) + O(m) recursion stack
     * ========================================================================= */
    int memo(int i, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp)
    {
        int m = grid.size(), n = grid[0].size();

        if (j1 < 0 || j1 >= n || j2 < 0 || j2 >= n)
            return -1e8;

        if (i == m - 1) {
            return (j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        }

        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];

        int maxCherries = INT_MIN;

        for (int dj1 : directions) {
            for (int dj2 : directions) {
                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                value += memo(i + 1, j1 + dj1, j2 + dj2, grid, dp);
                maxCherries = max(maxCherries, value);
            }
        }

        return dp[i][j1][j2] = maxCherries;
    }

    /* =========================================================================
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n² * 9) = O(m * n²)
     * SPACE: O(m * n²)
     * ========================================================================= */
    int tabulation(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, 0)));

        // Base case: last row is completely taken as we may reach anywhere
        for (int j1 = 0; j1 < n; j1++) {
            for (int j2 = 0; j2 < n; j2++) {
                // if reached same place then send only once or else sum of both
                dp[m - 1][j1][j2] = (j1 == j2) ? grid[m - 1][j1] : grid[m - 1][j1] + grid[m - 1][j2];
            }
        }

        // start filling up from the second last row
        for (int i = m - 2; i >= 0; i--) {
            // all combinations of j1 and j2
            for (int j1 = 0; j1 < n; j1++) {
                for (int j2 = 0; j2 < n; j2++) {
                    int maxCherries = INT_MIN;

                    // going to all directions from all those positions
                    for (int dj1 : directions) {
                        for (int dj2 : directions) {
                            int nj1 = j1 + dj1;
                            int nj2 = j2 + dj2;
                            // if inside the bounds
                            if (nj1 >= 0 && nj1 < n && nj2 >= 0 && nj2 < n) {
                                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                                value += dp[i + 1][nj1][nj2];
                                maxCherries = max(maxCherries, value);
                            }
                        }
                    }

                    dp[i][j1][j2] = maxCherries;
                }
            }
        }

        return dp[0][0][n - 1];
    }

    /* =========================================================================
     * METHOD 4: SPACE OPTIMIZATION (3D → 2D)
     * TIME: O(m * n² * 9)
     * SPACE: O(n²)
     * ========================================================================= */
    int cherryPickup(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> front(n, vector<int>(n, 0)), curr(n, vector<int>(n, 0));

        // Base case
        for (int j1 = 0; j1 < n; j1++) {
            for (int j2 = 0; j2 < n; j2++) {
                front[j1][j2] = (j1 == j2) ? grid[m - 1][j1] : grid[m - 1][j1] + grid[m - 1][j2];
            }
        }

        for (int i = m - 2; i >= 0; i--) {
            for (int j1 = 0; j1 < n; j1++) {
                for (int j2 = 0; j2 < n; j2++) {
                    int maxCherries = INT_MIN;

                    for (int dj1 : directions) {
                        for (int dj2 : directions) {
                            int nj1 = j1 + dj1;
                            int nj2 = j2 + dj2;

                            if (nj1 >= 0 && nj1 < n && nj2 >= 0 && nj2 < n) {
                                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                                value += front[nj1][nj2];
                                maxCherries = max(maxCherries, value);
                            }
                        }
                    }

                    curr[j1][j2] = maxCherries;
                }
            }
            front = curr;
        }

        return front[0][n - 1];
    }
};

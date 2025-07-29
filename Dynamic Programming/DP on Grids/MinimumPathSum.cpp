#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LEETCODE 62 : MINIMUM PATH SUM (Only Right and Down)
 * ================================================================ */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: PURE RECURSION (TLE for large inputs)
     * TIME: O(2^(m * n)) | SPACE: O(m + n) stack
     * ------------------------------------------------------------ */
    int recur(int i, int j, vector<vector<int>>& grid)
    {
        if (i < 0 || j < 0)
            return 1e9; // invalid path
        if (i == 0 && j == 0)
            return grid[0][0];

        int up = recur(i - 1, j, grid);
        int left = recur(i, j - 1, grid);

        return grid[i][j] + min(up, left);
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n) | SPACE: O(m * n) + Recursion stack
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp)
    {
        if (i < 0 || j < 0)
            return 1e9;
        if (i == 0 && j == 0)
            return grid[0][0];

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int left = memo(i, j - 1, grid, dp);

        return dp[i][j] = grid[i][j] + min(up, left);
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                }
                else {
                    int up = (i > 0) ? dp[i - 1][j] : 1e9;
                    int left = (j > 0) ? dp[i][j - 1] : 1e9;
                    dp[i][j] = grid[i][j] + min(up, left);
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZED (1D DP)
     * TIME: O(m * n) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int minPathSum(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> prev(n, 0);

        for (int i = 0; i < m; ++i) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) {
                    curr[j] = grid[i][j];
                }
                else {
                    int up = (i > 0) ? prev[j] : 1e9;
                    int left = (j > 0) ? curr[j - 1] : 1e9;
                    curr[j] = grid[i][j] + min(up, left);
                }
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

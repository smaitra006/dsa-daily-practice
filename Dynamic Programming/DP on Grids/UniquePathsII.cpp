#include <bits/stdc++.h>
using namespace std;

/* ====================================================================
 * Leetcode 63: Unique Paths II (DP with obstacles, can move Right or Down)
 * ==================================================================== */

class Solution
{
public:
    /* ----------------------------------------------------------------
     * METHOD 1: RECURSION (TLE for large inputs)
     * TIME: Exponential | SPACE: O(m + n) stack space
     * ---------------------------------------------------------------- */
    int recur(int i, int j, vector<vector<int>>& grid)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == 1)
            return 0;
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        int up = recur(i - 1, j, grid);
        int left = recur(i, j - 1, grid);

        return up + left;
    }

    /* ----------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ---------------------------------------------------------------- */
    int memo(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == 1)
            return 0;
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int left = memo(i, j - 1, grid, dp);

        return dp[i][j] = up + left;
    }

    /* ----------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ---------------------------------------------------------------- */
    int tabulation(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                }
                else if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ----------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZED DP (1D array)
     * TIME: O(m * n) | SPACE: O(n)
     * ---------------------------------------------------------------- */
    int uniquePathsWithObstacles(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (grid[0][0] == 1)
            return 0;

        vector<int> prev(n, 0);
        prev[0] = 1;

        for (int i = 0; i < m; i++) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    curr[j] = 0;
                }
                else {
                    int left = (j > 0) ? curr[j - 1] : 0;
                    curr[j] = prev[j] + left;
                }
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

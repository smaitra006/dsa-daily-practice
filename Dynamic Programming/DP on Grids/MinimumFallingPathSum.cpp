#include <bits/stdc++.h>
using namespace std;

/* =============================================================
 * LEETCODE 931: MINIMUM FALLING PATH SUM
 * ============================================================= */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: RECURSION (TLE)
     * TIME: O(3^N) | SPACE: O(N) stack space
     * ------------------------------------------------------------ */
    int recur(int i, int j, vector<vector<int>>& grid)
    {
        int n = grid.size();
        if (j < 0 || j >= n)
            return 1e9;
        if (i == 0)
            return grid[0][j];

        int up = recur(i - 1, j, grid);
        int leftDiag = recur(i - 1, j - 1, grid);
        int rightDiag = recur(i - 1, j + 1, grid);

        return grid[i][j] + min({ up, leftDiag, rightDiag });
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-down DP)
     * TIME: O(N^2) | SPACE: O(N^2) + Recursion Stack
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp)
    {
        int n = grid.size();
        if (j < 0 || j >= n)
            return 1e9;
        if (i == 0)
            return grid[0][j];

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int leftDiag = memo(i - 1, j - 1, grid, dp);
        int rightDiag = memo(i - 1, j + 1, grid, dp);

        return dp[i][j] = grid[i][j] + min({ up, leftDiag, rightDiag });
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-up DP)
     * TIME: O(N^2) | SPACE: O(N^2)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>>& grid)
    {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 0; j < n; j++) {
            dp[0][j] = grid[0][j];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int up = dp[i - 1][j];
                int leftDiag = (j > 0) ? dp[i - 1][j - 1] : 1e9;
                int rightDiag = (j < n - 1) ? dp[i - 1][j + 1] : 1e9;

                dp[i][j] = grid[i][j] + min({ up, leftDiag, rightDiag });
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZATION (1D DP)
     * TIME: O(N^2) | SPACE: O(N)
     * ------------------------------------------------------------ */
    int minFallingPathSum(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        vector<int> prev(matrix[0].begin(), matrix[0].end());

        for (int i = 1; i < n; i++) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++) {
                int up = prev[j];
                int leftDiag = (j > 0) ? prev[j - 1] : 1e9;
                int rightDiag = (j < n - 1) ? prev[j + 1] : 1e9;

                curr[j] = matrix[i][j] + min({ up, leftDiag, rightDiag });
            }
            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }
};

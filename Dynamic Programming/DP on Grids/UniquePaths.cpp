#include <bits/stdc++.h>
using namespace std;

/* =============================================================
 * LEETCODE 62 :UNIQUE PATHS (DP – Move Right or Down from top-left to bottom-right)
 * ============================================================= */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: Recursion (Brute Force)
     * TIME: Exponential, SPACE: O(m + n) stack
     * ------------------------------------------------------------ */
    int recur(int i, int j)
    {
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        int up = recur(i - 1, j);
        int left = recur(i, j - 1);

        return up + left;
    }

    /* ------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n), SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>>& dp)
    {
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, dp);
        int left = memo(i, j - 1, dp);

        return dp[i][j] = up + left;
    }

    /* ------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n), SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int tabulation(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0)
                    dp[i][j] = 1;
                else {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ------------------------------------------------------------
     * METHOD 4: Space Optimized DP
     * TIME: O(m * n), SPACE: O(n)
     * ------------------------------------------------------------ */
    int uniquePaths(int m, int n)
    {
        vector<int> prev(n, 1); // First row is all 1s

        for (int i = 1; i < m; i++) {
            vector<int> curr(n, 1);
            for (int j = 1; j < n; j++) {
                curr[j] = curr[j - 1] + prev[j];
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

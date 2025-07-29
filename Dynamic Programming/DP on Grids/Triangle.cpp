#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * TRIANGLE - MINIMUM PATH SUM (Top to Bottom)
 * ================================================================ */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: RECURSION
     * TIME: O(2^n) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int recur(int r, int c, vector<vector<int>>& triangle)
    {
        int n = triangle.size();
        if (r == n - 1)
            return triangle[r][c];

        int down = recur(r + 1, c, triangle);
        int diag = recur(r + 1, c + 1, triangle);

        return triangle[r][c] + min(down, diag);
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(n^2) | SPACE: O(n^2) + Recursion Stack
     * ------------------------------------------------------------ */
    int memo(int r, int c, vector<vector<int>>& triangle, vector<vector<int>>& dp)
    {
        int n = triangle.size();
        if (r == n - 1)
            return triangle[r][c];

        if (dp[r][c] != -1)
            return dp[r][c];

        int down = memo(r + 1, c, triangle, dp);
        int diag = memo(r + 1, c + 1, triangle, dp);

        return dp[r][c] = triangle[r][c] + min(down, diag);
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(n^2) | SPACE: O(n^2)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>>& triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: bottom row
        for (int j = 0; j < triangle[n - 1].size(); ++j) {
            dp[n - 1][j] = triangle[n - 1][j];
        }

        // Bottom-up filling
        for (int r = n - 2; r >= 0; --r) {
            for (int c = 0; c < triangle[r].size(); ++c) {
                int down = dp[r + 1][c];
                int diag = dp[r + 1][c + 1];
                dp[r][c] = triangle[r][c] + min(down, diag);
            }
        }

        return dp[0][0];
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZATION (1D DP)
     * TIME: O(n^2) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int minimumTotal(vector<vector<int>>& triangle)
    {
        int n = triangle.size();
        vector<int> front(n, 0);

        // Base case: bottom row
        for (int j = 0; j < triangle[n - 1].size(); ++j) {
            front[j] = triangle[n - 1][j];
        }

        // Bottom-up filling
        for (int r = n - 2; r >= 0; --r) {
            vector<int> curr(n, 0);
            for (int c = 0; c < triangle[r].size(); ++c) {
                int down = front[c];
                int diag = front[c + 1];
                curr[c] = triangle[r][c] + min(down, diag);
            }
            front = curr;
        }

        return front[0];
    }
};

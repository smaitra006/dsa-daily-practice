#include <bits/stdc++.h>
using namespace std;
/* ================================================================
 * LONGEST COMMON SUBSEQUENCE (Leetcode 1143)
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings `text1` and `text2`, return the length of their longest common subsequence.
 *
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative order
 * of the remaining characters.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY:
 *     - Recursion: O(m + n)
 *     - Memoization: O(m * n)
 *     - Tabulation: O(m * n)
 *     - Space Optimized: O(2n)
 */

class Solution {
public:

    /* ----------------------------------------------------------------
     * METHOD 1: Recursion (TLE on large inputs)
     * TIME: O(2^(m+n))
     * SPACE: O(m + n) recursion stack
     * ---------------------------------------------------------------- */
    int lcsRec(string& text1, string& text2, int i, int j)
    {
        if (i == text1.length() || j == text2.length()) return 0;

        if (text1[i] == text2[j])
            return 1 + lcsRec(text1, text2, i + 1, j + 1);
        else
            return max(lcsRec(text1, text2, i + 1, j), lcsRec(text1, text2, i, j + 1));
    }

    /* ----------------------------------------------------------------
     * METHOD 2: Memoization (Top-down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + recursion stack
     * ---------------------------------------------------------------- */
    int lcsMemo(string& text1, string& text2, int i, int j, vector<vector<int>>& dp)
    {
        if (i == text1.length() || j == text2.length()) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (text1[i] == text2[j])
            return dp[i][j] = 1 + lcsMemo(text1, text2, i + 1, j + 1, dp);
        else
            return dp[i][j] = max(lcsMemo(text1, text2, i + 1, j, dp),
                lcsMemo(text1, text2, i, j + 1, dp));
    }

    /* ----------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * ---------------------------------------------------------------- */
    int lcsTab(string& text1, string& text2)
    {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[m][n];
    }

    /* ----------------------------------------------------------------
     * METHOD 4: Space Optimized (Rolling 2 rows)
     * TIME: O(m * n)
     * SPACE: O(2 * n)
     * ---------------------------------------------------------------- */
    int lcsSpaceOptimized(string& text1, string& text2)
    {
        int m = text1.size();
        int n = text2.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }

        return prev[n];
    }

    /* ----------------------------------------------------------------
     * FINAL FUNCTION (uses Tabulation as standard)
     * ---------------------------------------------------------------- */
    int longestCommonSubsequence(string text1, string text2)
    {
        return lcsTab(text1, text2);

        // For other methods:
        // vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), -1));
        // return lcsMemo(text1, text2, 0, 0, dp);
        // return lcsRec(text1, text2, 0, 0);
        // return lcsSpaceOptimized(text1, text2);
    }
};

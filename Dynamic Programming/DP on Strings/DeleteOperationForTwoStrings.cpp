#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * DELETE OPERATION FOR TWO STRINGS (Leetcode 583)
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings word1 and word2, return the minimum number of steps required to make them equal.
 * In each step you can delete exactly one character in either string.
 *
 * Key Insight:
 * ------------
 * Minimum deletions = (len(word1) - LCS) + (len(word2) - LCS)
 *
 * Approach:
 * ---------
 * 1. Compute the length of the Longest Common Subsequence (LCS).
 * 2. Subtract it from both strings' lengths to find the minimum deletions.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: O(m * n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^(m + n))
     * SPACE: O(m + n)
     * --------------------------------------------------------------- */
    int recur(string& w1, string& w2, int i, int j)
    {
        if (i == 0 || j == 0) return 0;
        if (w1[i - 1] == w2[j - 1])
            return 1 + recur(w1, w2, i - 1, j - 1);
        else
            return max(recur(w1, w2, i - 1, j), recur(w1, w2, i, j - 1));
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n)
     * --------------------------------------------------------------- */
    int memo(string& w1, string& w2, int i, int j, vector<vector<int>>& dp)
    {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (w1[i - 1] == w2[j - 1])
            return dp[i][j] = 1 + memo(w1, w2, i - 1, j - 1, dp);
        else
            return dp[i][j] = max(memo(w1, w2, i - 1, j, dp), memo(w1, w2, i, j - 1, dp));
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int tabulation(string& word1, string& word2)
    {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lcs = dp[m][n];
        return (m - lcs) + (n - lcs);
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (Final Submission)
     * TIME: O(m * n)
     * SPACE: O(2 * n)
     * --------------------------------------------------------------- */
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }

        int lcs = prev[n];
        return (m - lcs) + (n - lcs);
    }
};


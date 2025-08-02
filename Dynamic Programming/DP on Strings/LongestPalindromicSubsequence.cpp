#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LONGEST PALINDROMIC SUBSEQUENCE (Leetcode 516)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a string `s`, return the length of the longest palindromic subsequence in `s`.
 *
 * Key Insight:
 * ------------
 * Longest Palindromic Subsequence (LPS) = LCS(s, reverse(s))
 *
 * Approach:
 * ---------
 * 1. Reverse the string.
 * 2. Compute the Longest Common Subsequence between `s` and `reversed(s)`.
 *
 * TIME COMPLEXITY: O(n * n)
 * SPACE COMPLEXITY: varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int recur(string& s1, string& s2, int i, int j)
    {
        if (i == 0 || j == 0) return 0;
        if (s1[i - 1] == s2[j - 1])
            return 1 + recur(s1, s2, i - 1, j - 1);
        else
            return max(recur(s1, s2, i - 1, j), recur(s1, s2, i, j - 1));
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * n)
     * SPACE: O(n * n) + O(n)
     * --------------------------------------------------------------- */
    int memo(string& s1, string& s2, int i, int j, vector<vector<int>>& dp)
    {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i - 1] == s2[j - 1])
            return dp[i][j] = 1 + memo(s1, s2, i - 1, j - 1, dp);
        else
            return dp[i][j] = max(memo(s1, s2, i - 1, j, dp), memo(s1, s2, i, j - 1, dp));
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * n)
     * SPACE: O(n * n)
     * --------------------------------------------------------------- */
    int tabulation(string& s)
    {
        string s1 = s;
        reverse(s.begin(), s.end());
        string s2 = s;

        int n = s1.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[n][n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (Final Submission)
     * TIME: O(n * n)
     * SPACE: O(2 * n)
     * --------------------------------------------------------------- */
    int longestPalindromeSubseq(string s)
    {
        string s1 = s;
        reverse(s.begin(), s.end());
        string s2 = s;

        int n = s1.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }

        return prev[n];
    }
};


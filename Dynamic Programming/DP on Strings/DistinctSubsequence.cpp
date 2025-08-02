#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * DISTINCT SUBSEQUENCES (Leetcode 115)
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings `s` and `t`, return the number of distinct subsequences of `s` which equals `t`.
 *
 * A subsequence of a string is a new string formed from the original string by deleting some (can be none) characters
 * without disturbing the relative positions of the remaining characters.
 *
 * Key Insight:
 * ------------
 * For each character in `s`, we either:
 *   1. Match it with a character in `t` and move both pointers.
 *   2. Skip it and only move the `s` pointer.
 *
 * Approach:
 * ---------
 * Use dynamic programming to count subsequence matches from `s[i:]` and `t[j:]`.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^m)
     * SPACE: O(m + n)
     * --------------------------------------------------------------- */
    int recur(string& s, string& t, int i, int j)
    {
        if (j == 0) return 1;                // matched full t
        if (i == 0) return 0;                // exhausted s

        if (s[i - 1] == t[j - 1])
            return recur(s, t, i - 1, j - 1) + recur(s, t, i - 1, j);  // take + skip
        else
            return recur(s, t, i - 1, j);     // only skip
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n)
     * --------------------------------------------------------------- */
    int memo(string& s, string& t, int i, int j, vector<vector<int>>& dp)
    {
        if (j == 0) return 1;
        if (i == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == t[j - 1])
            return dp[i][j] = memo(s, t, i - 1, j - 1, dp) + memo(s, t, i - 1, j, dp);
        else
            return dp[i][j] = memo(s, t, i - 1, j, dp);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int tabulation(string& s, string& t)
    {
        int m = s.size(), n = t.size();
        vector<vector<unsigned long long>> dp(m + 1, vector<unsigned long long>(n + 1, 0));

        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;  // Empty t can always be matched
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return (int)dp[m][n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (Final Submission)
     * TIME: O(m * n)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int numDistinct(string s, string t)
    {
        int m = s.length(), n = t.length();
        vector<unsigned long long> prev(n + 1, 0), curr(n + 1, 0);
        prev[0] = 1;

        for (int i = 1; i <= m; i++) {
            curr[0] = 1;
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    curr[j] = prev[j - 1] + prev[j];
                else
                    curr[j] = prev[j];
            }
            prev = curr;
        }

        return (int)prev[n];
    }
};


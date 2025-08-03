#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * WILDCARD MATCHING (Leetcode 44)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an input string `s` and a pattern `p`, implement wildcard pattern matching with support for `'?'` and `'*'`:
 *   - `'?'` Matches any single character.
 *   - `'*'` Matches any sequence of characters (including the empty sequence).
 *
 * Return true if the entire string `s` matches the pattern `p`.
 *
 * Key Insight:
 * ------------
 * Use dynamic programming to check if the characters match, and how `'*'` can be used flexibly:
 *   - If characters match or `p[j-1] == '?'`, reduce both indices.
 *   - If `p[j-1] == '*'`, try matching with or without the current character:
 *     - `solve(i-1, j)` -> use `'*'` for matching current character.
 *     - `solve(i, j-1)` -> skip `'*'`.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^(m + n))
     * SPACE: O(m + n)
     * --------------------------------------------------------------- */
    bool recur(int i, int j, string& s, string& p)
    {
        if (i == 0 && j == 0) return true;
        if (j == 0) return false;
        if (i == 0) {
            for (int k = 0; k < j; k++) {
                if (p[k] != '*') return false;
            }
            return true;
        }

        if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
            return recur(i - 1, j - 1, s, p);
        }
        else if (p[j - 1] == '*') {
            return recur(i - 1, j, s, p) || recur(i, j - 1, s, p);
        }
        else {
            return false;
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n)
     * --------------------------------------------------------------- */
    bool memo(int i, int j, string& s, string& p, vector<vector<int>>& dp)
    {
        if (i == 0 && j == 0) return true;
        if (j == 0) return false;
        if (i == 0) {
            for (int k = 0; k < j; k++) {
                if (p[k] != '*') return false;
            }
            return true;
        }

        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
            return dp[i][j] = memo(i - 1, j - 1, s, p, dp);
        }
        else if (p[j - 1] == '*') {
            return dp[i][j] = memo(i - 1, j, s, p, dp) || memo(i, j - 1, s, p, dp);
        }
        else {
            return dp[i][j] = false;
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    bool tabulation(string& s, string& p)
    {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        dp[0][0] = true;

        for (int j = 1; j <= n; j++) {
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }

        return dp[m][n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (Final Submission)
     * TIME: O(m * n)
     * SPACE: O(2 * n)
     * --------------------------------------------------------------- */
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        vector<bool> prev(n + 1, false), curr(n + 1, false);

        prev[0] = true;
        for (int j = 1; j <= n; j++) {
            prev[j] = prev[j - 1] && p[j - 1] == '*';
        }

        for (int i = 1; i <= m; i++) {
            curr[0] = false;
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                }
                else if (p[j - 1] == '*') {
                    curr[j] = prev[j] || curr[j - 1];
                }
                else {
                    curr[j] = false;
                }
            }
            prev = curr;
        }

        return prev[n];
    }
};


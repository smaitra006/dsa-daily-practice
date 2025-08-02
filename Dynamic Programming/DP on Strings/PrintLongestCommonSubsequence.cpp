#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * PRINT LONGEST COMMON SUBSEQUENCE
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings s1 and s2, return any one Longest Common Subsequence (LCS) between them.
 *
 * A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.
 *
 * Approach:
 * ---------
 * 1. Compute LCS using DP.
 * 2. Trace back from dp[m][n] to recover one valid LCS.
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
    string recur(string& s1, string& s2, int i, int j)
    {
        if (i == 0 || j == 0) return "";

        if (s1[i - 1] == s2[j - 1])
            return recur(s1, s2, i - 1, j - 1) + s1[i - 1];
        else {
            string a = recur(s1, s2, i - 1, j);
            string b = recur(s1, s2, i, j - 1);
            return a.size() > b.size() ? a : b;
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n)
     * --------------------------------------------------------------- */
    string memo(string& s1, string& s2, int i, int j, vector<vector<string>>& dp)
    {
        if (i == 0 || j == 0) return "";

        if (!dp[i][j].empty()) return dp[i][j];

        if (s1[i - 1] == s2[j - 1])
            return dp[i][j] = memo(s1, s2, i - 1, j - 1, dp) + s1[i - 1];
        else {
            string a = memo(s1, s2, i - 1, j, dp);
            string b = memo(s1, s2, i, j - 1, dp);
            return dp[i][j] = (a.size() > b.size() ? a : b);
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation with Path Recovery
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    string tabulation(string& s1, string& s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Reconstruct LCS
        int i = m, j = n;
        string lcs = "";

        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs.push_back(s1[i - 1]);
                i--; j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) i--;
            else j--;
        }

        reverse(lcs.begin(), lcs.end());
        return lcs;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (2 Rows)
     * TIME: O(m * n)
     * SPACE: O(2 * n)
     * --------------------------------------------------------------- */
    string spaceOptimized(string& s1, string& s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(2, vector<int>(n + 1, 0));
        vector<vector<char>> path(m + 1, vector<char>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            int curr = i % 2, prev = (i - 1) % 2;
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[curr][j] = 1 + dp[prev][j - 1];
                    path[i][j] = 'D';  // Diagonal
                }
                else if (dp[prev][j] > dp[curr][j - 1]) {
                    dp[curr][j] = dp[prev][j];
                    path[i][j] = 'U';  // Up
                }
                else {
                    dp[curr][j] = dp[curr][j - 1];
                    path[i][j] = 'L';  // Left
                }
            }
        }

        // Reconstruct LCS using path table
        string lcs = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (path[i][j] == 'D') {
                lcs.push_back(s1[i - 1]);
                i--; j--;
            }
            else if (path[i][j] == 'U') {
                i--;
            }
            else {
                j--;
            }
        }

        reverse(lcs.begin(), lcs.end());
        return lcs;
    }
};

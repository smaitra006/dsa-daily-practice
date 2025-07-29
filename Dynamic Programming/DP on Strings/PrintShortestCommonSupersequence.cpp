#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * SHORTEST COMMON SUPERSEQUENCE (Leetcode 1092)
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.
 * If there are multiple valid answers, return any of them.
 *
 * Approach:
 * ---------
 * 1. Use Longest Common Subsequence (LCS) to identify common parts.
 * 2. Build shortest supersequence by merging str1 and str2 around the LCS.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: O(m * n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^(m + n))
     * SPACE: O(m + n) recursion stack
     * --------------------------------------------------------------- */
    string recur(int i, int j, string& str1, string& str2)
    {
        if (i == str1.size()) return str2.substr(j);
        if (j == str2.size()) return str1.substr(i);

        if (str1[i] == str2[j])
            return str1[i] + recur(i + 1, j + 1, str1, str2);
        else {
            string res1 = str1[i] + recur(i + 1, j, str1, str2);
            string res2 = str2[j] + recur(i, j + 1, str1, str2);
            return res1.size() < res2.size() ? res1 : res2;
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n) recursion
     * --------------------------------------------------------------- */
    string memo(int i, int j, string& str1, string& str2, vector<vector<string>>& dp)
    {
        if (i == str1.size()) return str2.substr(j);
        if (j == str2.size()) return str1.substr(i);
        if (!dp[i][j].empty()) return dp[i][j];

        if (str1[i] == str2[j])
            return dp[i][j] = str1[i] + memo(i + 1, j + 1, str1, str2, dp);
        else {
            string res1 = str1[i] + memo(i + 1, j, str1, str2, dp);
            string res2 = str2[j] + memo(i, j + 1, str1, str2, dp);
            return dp[i][j] = (res1.size() < res2.size() ? res1 : res2);
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP for LCS length only)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int lcsLength(string& str1, string& str2)
    {
        int m = str1.size(), n = str2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

        return dp[m][n];  // Only returns length of LCS
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Tabulation with Path Recovery (Final Submission)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    string shortestCommonSupersequence(string str1, string str2)
    {
        int m = str1.length();
        int n = str2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Fill LCS dp table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Reconstruct the supersequence from the LCS table
        int i = m, j = n;
        string result = "";

        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                result.push_back(str1[i - 1]);
                i--; j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                result.push_back(str1[i - 1]);
                i--;
            }
            else {
                result.push_back(str2[j - 1]);
                j--;
            }
        }

        // Add remaining characters from str1 and str2
        while (i > 0) result.push_back(str1[i-- - 1]);
        while (j > 0) result.push_back(str2[j-- - 1]);

        reverse(result.begin(), result.end());
        return result;
    }
};

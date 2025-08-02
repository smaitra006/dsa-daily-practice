#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LONGEST COMMON SUBSTRING
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings s1 and s2, return the length of the longest substring that appears in both.
 * A substring is a contiguous sequence of characters.
 *
 * Approach:
 * ---------
 * Use Dynamic Programming:
 * - If characters match, extend the current substring.
 * - If not, reset the streak to 0.
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: O(m * n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^(m + n))
     * SPACE: O(m + n) recursion depth
     * --------------------------------------------------------------- */
    int recur(string& s1, string& s2, int i, int j, int count)
    {
        if (i == 0 || j == 0) return count;

        int curr = count;
        if (s1[i - 1] == s2[j - 1])
            curr = recur(s1, s2, i - 1, j - 1, count + 1);

        int left = recur(s1, s2, i - 1, j, 0);
        int right = recur(s1, s2, i, j - 1, 0);

        return max({ curr, left, right });
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n) recursion
     * --------------------------------------------------------------- */
    int memo(string& s1, string& s2, int i, int j, vector<vector<int>>& dp, int& maxLen)
    {
        if (i == 0 || j == 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i - 1] == s2[j - 1]) {
            dp[i][j] = 1 + memo(s1, s2, i - 1, j - 1, dp, maxLen);
            maxLen = max(maxLen, dp[i][j]);
            return dp[i][j];
        }

        dp[i][j] = 0;
        memo(s1, s2, i - 1, j, dp, maxLen);
        memo(s1, s2, i, j - 1, dp, maxLen);
        return 0;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int tabulation(string& s1, string& s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLen = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }

        return maxLen;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Optimized Tabulation (Final Submission)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int longestCommonSubstr(string& s1, string& s2)
    {
        int m = s1.size();
        int n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLen = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxLen = max(maxLen, dp[i][j]);
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }

        return maxLen;
    }
};

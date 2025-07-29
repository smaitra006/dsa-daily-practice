#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * INTERLEAVING STRING (Leetcode 97)
 * ================================================================
 *
 * Problem:
 * --------
 * Given strings s1, s2, and s3, return true if s3 is formed by an interleaving of s1 and s2.
 * Interleaving means s3 contains all the characters of s1 and s2,
 * and the order of characters in s1 and s2 is preserved.
 *
 * Constraints:
 * ------------
 * - s1.length + s2.length == s3.length
 *
 * Approach:
 * ---------
 * Use 3 pointers (i, j, k) for s1, s2, s3 respectively.
 * At each step, try matching s1[i] or s2[j] with s3[k].
 *
 * TIME COMPLEXITY: O(n * m)
 * SPACE COMPLEXITY: O(n * m)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^(n + m))
     * SPACE: O(n + m) recursion depth
     * --------------------------------------------------------------- */
    bool recur(string& s1, string& s2, string& s3, int i, int j, int k)
    {
        if (i == s1.size() && j == s2.size() && k == s3.size())
            return true;
        if (k >= s3.size()) return false;

        bool take_i = false, take_j = false;
        if (i < s1.size() && s1[i] == s3[k])
            take_i = recur(s1, s2, s3, i + 1, j, k + 1);
        if (j < s2.size() && s2[j] == s3[k])
            take_j = recur(s1, s2, s3, i, j + 1, k + 1);

        return take_i || take_j;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * m)
     * SPACE: O(n * m) + O(n + m) recursion
     * --------------------------------------------------------------- */
    bool memo(string& s1, string& s2, string& s3, int i, int j, int k, vector<vector<int>>& dp)
    {
        if (i == s1.size() && j == s2.size() && k == s3.size())
            return true;
        if (k >= s3.size()) return false;

        if (dp[i][j] != -1) return dp[i][j];

        bool take_i = false, take_j = false;
        if (i < s1.size() && s1[i] == s3[k])
            take_i = memo(s1, s2, s3, i + 1, j, k + 1, dp);
        if (j < s2.size() && s2[j] == s3[k])
            take_j = memo(s1, s2, s3, i, j + 1, k + 1, dp);

        return dp[i][j] = take_i || take_j;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * m)
     * SPACE: O(n * m)
     * --------------------------------------------------------------- */
    bool tabulation(string& s1, string& s2, string& s3)
    {
        int n = s1.size(), m = s2.size(), p = s3.size();
        if (n + m != p) return false;

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i > 0 && s1[i - 1] == s3[i + j - 1])
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                if (j > 0 && s2[j - 1] == s3[i + j - 1])
                    dp[i][j] = dp[i][j] || dp[i][j - 1];
            }
        }

        return dp[n][m];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Memoized DFS (Final Submission)
     * TIME: O(n * m)
     * SPACE: O(n * m)
     * --------------------------------------------------------------- */
    int n, m, p;

    bool solve(string s1, string s2, string s3, int i, int j, int k, vector<vector<int>>& dp)
    {
        if (i == n && j == m && k == p)
            return true;
        if (k >= p)
            return false;

        if (dp[i][j] != -1)
            return dp[i][j];

        bool take_i = false, take_j = false;
        if (i < n && s1[i] == s3[k])
            take_i = solve(s1, s2, s3, i + 1, j, k + 1, dp);
        if (j < m && s2[j] == s3[k])
            take_j = solve(s1, s2, s3, i, j + 1, k + 1, dp);

        return dp[i][j] = take_i || take_j;
    }

    bool isInterleave(string s1, string s2, string s3)
    {
        n = s1.size();
        m = s2.size();
        p = s3.size();
        if (n + m != p) return false;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(s1, s2, s3, 0, 0, 0, dp);
    }
};

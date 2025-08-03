#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * EDIT DISTANCE (Leetcode 72)
 * ================================================================
 *
 * Problem:
 * --------
 * Given two strings `word1` and `word2`, return the minimum number of operations required to convert `word1` to `word2`.
 * You are allowed to perform the following operations:
 *   1. Insert a character
 *   2. Delete a character
 *   3. Replace a character
 *
 * Key Insight:
 * ------------
 * Use DP to explore all three operations at each step:
 *   - Insert: dp[i][j-1] + 1
 *   - Delete: dp[i-1][j] + 1
 *   - Replace: dp[i-1][j-1] + 1
 *
 * TIME COMPLEXITY: O(m * n)
 * SPACE COMPLEXITY: varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(3^max(m, n))
     * SPACE: O(m + n)
     * --------------------------------------------------------------- */
    int recur(string& w1, string& w2, int i, int j) {
        if (i == 0) return j;
        if (j == 0) return i;

        if (w1[i - 1] == w2[j - 1])
            return recur(w1, w2, i - 1, j - 1);
        else {
            int insert_char = 1 + recur(w1, w2, i, j - 1);
            int delete_char = 1 + recur(w1, w2, i - 1, j);
            int replace_char = 1 + recur(w1, w2, i - 1, j - 1);
            return min({insert_char, delete_char, replace_char});
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n)
     * SPACE: O(m * n) + O(m + n)
     * --------------------------------------------------------------- */
    int memo(string& w1, string& w2, int i, int j, vector<vector<int>>& dp) {
        if (i == 0) return j;
        if (j == 0) return i;
        if (dp[i][j] != -1) return dp[i][j];

        if (w1[i - 1] == w2[j - 1])
            return dp[i][j] = memo(w1, w2, i - 1, j - 1, dp);
        else {
            int insert_char = 1 + memo(w1, w2, i, j - 1, dp);
            int delete_char = 1 + memo(w1, w2, i - 1, j, dp);
            int replace_char = 1 + memo(w1, w2, i - 1, j - 1, dp);
            return dp[i][j] = min({insert_char, delete_char, replace_char});
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n)
     * SPACE: O(m * n)
     * --------------------------------------------------------------- */
    int tabulation(string& word1, string& word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else {
                    int insert_char = 1 + dp[i][j - 1];
                    int delete_char = 1 + dp[i - 1][j];
                    int replace_char = 1 + dp[i - 1][j - 1];
                    dp[i][j] = min({insert_char, delete_char, replace_char});
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
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int j = 0; j <= n; j++) prev[j] = j;

        for (int i = 1; i <= m; i++) {
            curr[0] = i;
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    curr[j] = prev[j - 1];
                else {
                    int insert_char = 1 + curr[j - 1];
                    int delete_char = 1 + prev[j];
                    int replace_char = 1 + prev[j - 1];
                    curr[j] = min({insert_char, delete_char, replace_char});
                }
            }
            prev = curr;
        }

        return prev[n];
    }
};

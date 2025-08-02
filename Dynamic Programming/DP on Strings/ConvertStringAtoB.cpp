#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
 * CONVERT STRING a TO b: MINIMUM INSERTIONS & DELETIONS
 * ============================================================================
 * Given strings a and b, find the minimum number of insertions and deletions
 * required to transform string a into b using only insertions and deletions.
 */

class Solution {
public:
    /* ------------------------------------------------------------------------
     * METHOD 1: RECURSION (TLE for large inputs)
     * TIME: O(2^(m+n)), SPACE: O(m + n)
     * ------------------------------------------------------------------------ */
    int recur(string& a, string& b, int i, int j)
    {
        if (i == 0 || j == 0) return 0;

        if (a[i - 1] == b[j - 1])
            return 1 + recur(a, b, i - 1, j - 1);
        else
            return max(recur(a, b, i - 1, j), recur(a, b, i, j - 1));
    }

    /* ------------------------------------------------------------------------
     * METHOD 2: MEMOIZATION (TOP-DOWN DP)
     * TIME: O(m * n), SPACE: O(m * n) + O(m + n)
     * ------------------------------------------------------------------------ */
    int memo(string& a, string& b, int i, int j, vector<vector<int>>& dp)
    {
        if (i == 0 || j == 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (a[i - 1] == b[j - 1])
            return dp[i][j] = 1 + memo(a, b, i - 1, j - 1, dp);
        else
            return dp[i][j] = max(memo(a, b, i - 1, j, dp), memo(a, b, i, j - 1, dp));
    }

    /* ------------------------------------------------------------------------
     * METHOD 3: TABULATION (BOTTOM-UP DP)
     * TIME: O(m * n), SPACE: O(m * n)
     * ------------------------------------------------------------------------ */
    int minOperations_tab(string a, string b)
    {
        int m = a.size(), n = b.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lcs = dp[m][n];
        int deletions = m - lcs;
        int insertions = n - lcs;
        return deletions + insertions;
    }

    /* ------------------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZED DP (FINAL METHOD)
     * TIME: O(m * n), SPACE: O(n)
     * ------------------------------------------------------------------------ */
    int minOperations(string a, string b)
    {
        int m = a.size(), n = b.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }

        int lcs = prev[n];
        int deletions = m - lcs;
        int insertions = n - lcs;
        return deletions + insertions;
    }
};


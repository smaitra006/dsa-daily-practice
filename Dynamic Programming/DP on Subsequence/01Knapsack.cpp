#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * 0/1 KNAPSACK
 * ================================================================
 *
 * Problem:
 * --------
 * Given weights[] and values[] of N items, and a capacity W,
 * determine the maximum total value that can be obtained by
 * selecting items such that their total weight does not exceed W.
 *
 * Each item can be picked at most once (0/1 constraint).
 *
 * Recurrence:
 * -----------
 * dp[i][w] = max(dp[i-1][w], val[i] + dp[i-1][w - wt[i]])
 *
 * TIME COMPLEXITY: O(n * W)
 * SPACE COMPLEXITY: O(n * W) → O(W) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int W, vector<int>& wt, vector<int>& val)
    {
        if (i == 0) {
            return (wt[0] <= W) ? val[0] : 0; // If we can fit the item then we take its val otherwise 0
        }

        int notTake = recur(i - 1, W, wt, val);
        int take = 0;
        if (wt[i] <= W)
            take = val[i] + recur(i - 1, W - wt[i], wt, val);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * W)
     * SPACE: O(n * W) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp)
    {
        if (i == 0) {
            return (wt[0] <= W) ? val[0] : 0;
        }

        if (dp[i][W] != -1)
            return dp[i][W];

        int notTake = memo(i - 1, W, wt, val, dp);
        int take = 0;
        if (wt[i] <= W)
            take = val[i] + memo(i - 1, W - wt[i], wt, val, dp);

        return dp[i][W] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * W)
     * SPACE: O(n * W)
     * --------------------------------------------------------------- */
    int tabulation(int W, vector<int>& wt, vector<int>& val)
    {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        // Base case already initialized to 0 (dp[0][*] = 0 and dp[*][0] = 0)

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= W; j++) {

                int not_take = dp[i - 1][j]; // Not take case. If we can't take it then at its place we store the value we had while using (i-1)th element and same j capacity

                int take = 0;
                if (wt[i - 1] <= j) {
                    take = val[i - 1] + dp[i - 1][j - wt[i - 1]]; // Take case. We take the current one, so capacity reduces to j - wt[i - 1]
                }

                dp[i][j] = max(take, not_take);
            }
        }

        return dp[n][W];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * W)
     * SPACE: O(W)
     * --------------------------------------------------------------- */
    int knapsack(int W, vector<int>& wt, vector<int>& val)
    {
        int n = wt.size();
        vector<int> prev(W + 1, 0); // We only need the previous row

        for (int i = 1; i <= n; i++) {
            vector<int> curr(W + 1, 0);
            for (int j = 1; j <= W; j++) {
                int not_take = prev[j];
                int take = 0;
                if (wt[i - 1] <= j) {
                    take = val[i - 1] + prev[j - wt[i - 1]];
                }
                curr[j] = max(take, not_take);
            }
            prev = curr;
        }

        return prev[W];
    }
};

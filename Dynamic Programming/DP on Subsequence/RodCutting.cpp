#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * ROD CUTTING PROBLEM (Unbounded Knapsack Variant)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a rod of length `n` and an array `prices` where prices[i]
 * denotes the price of a rod of length `i+1`, find the maximum total
 * value you can obtain by cutting the rod into pieces.
 *
 * You can make multiple cuts and reuse the same length multiple times.
 *
 * Observation:
 * ------------
 * This is a classic Unbounded Knapsack problem where:
 * - 'n' is the total capacity (rod length)
 * - You can pick the same piece (length) multiple times
 *
 * Recurrence:
 * -----------
 * dp[i][len] = max(dp[i-1][len], price[i] + dp[i][len - length[i]])
 *
 * TIME COMPLEXITY: O(n * n)
 * SPACE COMPLEXITY: O(n * n) → O(n) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int len, vector<int>& prices)
    {
        if (i == 0)
            return len * prices[0]; // only length 1 rod available

        int notCut = recur(i - 1, len, prices);
        int cut = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= len)
            cut = prices[i] + recur(i, len - rodLength, prices);

        return max(cut, notCut);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * n)
     * SPACE: O(n * n) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int len, vector<int>& prices, vector<vector<int>>& dp)
    {
        if (i == 0)
            return len * prices[0];

        if (dp[i][len] != -1)
            return dp[i][len];

        int notCut = memo(i - 1, len, prices, dp);
        int cut = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= len)
            cut = prices[i] + memo(i, len - rodLength, prices, dp);

        return dp[i][len] = max(cut, notCut);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * n)
     * SPACE: O(n * n)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& prices, int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int len = 0; len <= n; len++) // We can make anything with rod length 1
            dp[0][len] = len * prices[0];

        for (int i = 1; i < n; i++) {
            for (int len = 0; len <= n; len++) {
                int notCut = dp[i - 1][len];
                int cut = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= len)
                    cut = prices[i] + dp[i][len - rodLength];
                dp[i][len] = max(cut, notCut);
            }
        }

        return dp[n][n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * n)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int cutRod(vector<int>& prices, int n)
    {
        vector<int> dp(n + 1, 0);

        for (int len = 0; len <= n; len++)
            dp[len] = len * prices[0];

        for (int i = 1; i < n; i++) {
            for (int len = 0; len <= n; len++) {
                int notCut = dp[len];
                int cut = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= len)
                    cut = prices[i] + dp[len - rodLength];
                dp[len] = max(cut, notCut);
            }
        }

        return dp[n];
    }
};

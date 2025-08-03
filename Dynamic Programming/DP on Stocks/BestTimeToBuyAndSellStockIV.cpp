#include <bits/stdc++.h>
using namespace std;

/* =========================================================================
 * BEST TIME TO BUY AND SELL STOCK IV (Leetcode 188)
 * =========================================================================
 *
 * Problem:
 * --------
 * You are given an integer `k` and an array `prices` where prices[i] is the price of a stock on the i-th day.
 * Find the maximum profit you can achieve with at most `k` transactions.
 * You may not engage in multiple transactions simultaneously (must sell before buying again).
 *
 * Key Insight:
 * ------------
 * Use a 3D DP: (i, buy/sell state, remaining transactions).
 * Reduce `k` only after a **sell**.
 *
 * TIME COMPLEXITY: O(n * 2 * k)
 * SPACE COMPLEXITY: Depends on the method
 */

class Solution {
public:

    /* ---------------------------------------------------------------------
     * METHOD 1: Recursion
     * TIME: O(2^n)
     * SPACE: O(n)
     * --------------------------------------------------------------------- */
    int recur(int i, int buy, int k, vector<int>& prices)
    {
        if (i == prices.size() || k == 0) return 0;

        if (buy) {
            return max(
                -prices[i] + recur(i + 1, 0, k, prices), // Buy
                recur(i + 1, 1, k, prices)               // Skip
            );
        }
        else {
            return max(
                prices[i] + recur(i + 1, 1, k - 1, prices), // Sell
                recur(i + 1, 0, k, prices)                  // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2 * k)
     * SPACE: O(n * 2 * k) + O(n)
     * --------------------------------------------------------------------- */
    int f(int i, int buy, vector<int>& prices, int k, vector<vector<vector<int>>>& dp)
    {
        if (i == prices.size() || k == 0) return 0;

        if (dp[i][buy][k] != -1) return dp[i][buy][k];

        if (buy) {
            return dp[i][buy][k] = max(
                -prices[i] + f(i + 1, 0, prices, k, dp),  // Buy
                f(i + 1, 1, prices, k, dp)                // Skip
            );
        }
        else {
            return dp[i][buy][k] = max(
                prices[i] + f(i + 1, 1, prices, k - 1, dp), // Sell
                f(i + 1, 0, prices, k, dp)                  // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 2 * k)
     * SPACE: O(n * 2 * k)
     * --------------------------------------------------------------------- */
    int tabulation(int k, vector<int>& prices)
    {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy) {
                        dp[i][buy][cap] = max(
                            -prices[i] + dp[i + 1][0][cap],   // Buy
                            0 + dp[i + 1][1][cap]             // Skip
                        );
                    }
                    else {
                        dp[i][buy][cap] = max(
                            prices[i] + dp[i + 1][1][cap - 1], // Sell
                            0 + dp[i + 1][0][cap]              // Skip
                        );
                    }
                }
            }
        }

        return dp[0][1][k];
    }

    /* ---------------------------------------------------------------------
     * METHOD 4: Space Optimized (2D DP)
     * TIME: O(n * 2 * k)
     * SPACE: O(2 * k) = O(k)
     * --------------------------------------------------------------------- */
    int maxProfit(int k, vector<int>& prices)
    {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        vector<vector<int>> next(2, vector<int>(k + 1, 0)), curr(2, vector<int>(k + 1, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy) {
                        curr[buy][cap] = max(
                            -prices[i] + next[0][cap],   // Buy
                            0 + next[1][cap]             // Skip
                        );
                    }
                    else {
                        curr[buy][cap] = max(
                            prices[i] + next[1][cap - 1], // Sell
                            0 + next[0][cap]              // Skip
                        );
                    }
                }
            }
            next = curr;
        }

        return next[1][k];
    }
};

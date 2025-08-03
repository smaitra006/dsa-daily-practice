#include <bits/stdc++.h>
using namespace std;

/* =========================================================================
 * BEST TIME TO BUY AND SELL STOCK III (Leetcode 123)
 * =========================================================================
 *
 * Problem:
 * --------
 * You are given an array prices where prices[i] is the price of a stock on the i-th day.
 * Find the maximum profit you can achieve. You may complete at most **two transactions**.
 * Note: You may not engage in multiple transactions simultaneously
 * (i.e., you must sell the stock before you buy again).
 *
 * Key Insight:
 * ------------
 * Track (index, buy/sell, remaining transactions).
 * For each day, you can either buy, sell, or skip. Reduce `cap` only after a sell.
 *
 * TIME COMPLEXITY: O(n * 2 * k) = O(n) for k=2
 * SPACE COMPLEXITY: Varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------------
     * METHOD 1: Recursion
     * TIME: O(2^n)
     * SPACE: O(n) // recursion stack
     * --------------------------------------------------------------------- */
    int recur(vector<int>& prices, int i, bool canBuy, int cap)
    {
        if (i == prices.size() || cap == 0) return 0;

        if (canBuy) {
            return max(
                -prices[i] + recur(prices, i + 1, false, cap),  // buy
                0 + recur(prices, i + 1, true, cap)             // skip
            );
        }
        else {
            return max(
                prices[i] + recur(prices, i + 1, true, cap - 1), // sell
                0 + recur(prices, i + 1, false, cap)             // skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2 * 3)
     * SPACE: O(n * 2 * 3) + O(n) // dp + recursion stack
     * --------------------------------------------------------------------- */
    int solve(vector<int>& prices, int i, bool canBuy, int cap, vector<vector<vector<int>>>& dp)
    {
        if (cap == 0 || i == prices.size()) return 0;

        if (dp[i][canBuy][cap] != -1) return dp[i][canBuy][cap];

        if (canBuy) {
            return dp[i][canBuy][cap] = max(
                -prices[i] + solve(prices, i + 1, 0, cap, dp),  // buy
                0 + solve(prices, i + 1, 1, cap, dp)            // skip
            );
        }
        else {
            return dp[i][canBuy][cap] = max(
                prices[i] + solve(prices, i + 1, 1, cap - 1, dp), // sell
                0 + solve(prices, i + 1, 0, cap, dp)              // skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 2 * 3)
     * SPACE: O(n * 2 * 3)
     * --------------------------------------------------------------------- */
    int tabulation(vector<int>& prices)
    {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        for (int i = n - 1; i >= 0; i--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (canBuy) {
                        dp[i][canBuy][cap] = max(
                            -prices[i] + dp[i + 1][0][cap],   // buy
                            0 + dp[i + 1][1][cap]             // skip
                        );
                    }
                    else {
                        dp[i][canBuy][cap] = max(
                            prices[i] + dp[i + 1][1][cap - 1], // sell
                            0 + dp[i + 1][0][cap]              // skip
                        );
                    }
                }
            }
        }

        return dp[0][1][2]; // start from day 0, canBuy=1, cap=2
    }

    /* ---------------------------------------------------------------------
     * METHOD 4: Space Optimized (2D DP)
     * TIME: O(n * 2 * 3)
     * SPACE: O(2 * 3) = O(1)
     * --------------------------------------------------------------------- */
    int maxProfit(vector<int>& prices)
    {
        int n = prices.size();
        vector<vector<int>> next(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (canBuy) {
                        curr[canBuy][cap] = max(
                            -prices[i] + next[0][cap],   // buy
                            0 + next[1][cap]             // skip
                        );
                    }
                    else {
                        curr[canBuy][cap] = max(
                            prices[i] + next[1][cap - 1], // sell
                            0 + next[0][cap]              // skip
                        );
                    }
                }
            }
            next = curr;
        }

        return next[1][2];
    }
};

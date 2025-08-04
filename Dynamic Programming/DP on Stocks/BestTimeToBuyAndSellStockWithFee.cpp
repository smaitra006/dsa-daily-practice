#include <bits/stdc++.h>
using namespace std;

/* =========================================================================
 * BEST TIME TO BUY AND SELL STOCK WITH TRANSACTION FEE (Leetcode 714)
 * =========================================================================
 *
 * Problem:
 * --------
 * You are given an array `prices` where `prices[i]` is the price of a stock on day i,
 * and an integer `fee` representing a transaction fee.
 * You may buy and sell the stock multiple times, but must pay the fee each time you sell.
 *
 * Return the maximum profit you can achieve.
 *
 * Key Insight:
 * ------------
 * After selling, deduct the fee from the profit.
 * Buy → -prices[i] + dp[i+1][0]
 * Sell → prices[i] - fee + dp[i+1][1]
 *
 * TIME COMPLEXITY: O(n)
 * SPACE COMPLEXITY: Depends on method
 */

class Solution {
public:

    /* ---------------------------------------------------------------------
     * METHOD 1: Recursion
     * TIME: Exponential
     * SPACE: O(n)
     * --------------------------------------------------------------------- */
    int recur(int i, bool canBuy, vector<int>& prices, int fee)
    {
        if (i >= prices.size()) return 0;

        if (canBuy) {
            return max(
                -prices[i] + recur(i + 1, 0, prices, fee),  // Buy
                recur(i + 1, 1, prices, fee)                // Skip
            );
        }
        else {
            return max(
                prices[i] - fee + recur(i + 1, 1, prices, fee),  // Sell with fee
                recur(i + 1, 0, prices, fee)                     // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2) + O(n) recursion stack
     * --------------------------------------------------------------------- */
    int solve(vector<int>& prices, int i, bool canBuy, vector<vector<int>>& dp, int fee)
    {
        if (i >= prices.size()) return 0;

        if (dp[i][canBuy] != -1) return dp[i][canBuy];

        if (canBuy) {
            return dp[i][canBuy] = max(
                -prices[i] + solve(prices, i + 1, 0, dp, fee),   // Buy
                solve(prices, i + 1, 1, dp, fee)                 // Skip
            );
        }
        else {
            return dp[i][canBuy] = max(
                prices[i] - fee + solve(prices, i + 1, 1, dp, fee), // Sell with fee
                solve(prices, i + 1, 0, dp, fee)                   // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2)
     * --------------------------------------------------------------------- */
    int tabulation(vector<int>& prices, int fee)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                if (canBuy) {
                    dp[i][canBuy] = max(
                        -prices[i] + dp[i + 1][0],   // Buy
                        dp[i + 1][1]                 // Skip
                    );
                }
                else {
                    dp[i][canBuy] = max(
                        prices[i] - fee + dp[i + 1][1], // Sell with fee
                        dp[i + 1][0]                   // Skip
                    );
                }
            }
        }

        return dp[0][1];
    }

    /* ---------------------------------------------------------------------
     * METHOD 4: Space Optimized (Bottom-Up)
     * TIME: O(n)
     * SPACE: O(1)
     * --------------------------------------------------------------------- */
    int maxProfit(vector<int>& prices, int fee)
    {
        int n = prices.size();
        int aheadBuy = 0, aheadNotBuy = 0;

        for (int i = n - 1; i >= 0; i--) {
            int currBuy = max(-prices[i] + aheadNotBuy, aheadBuy);           // Buy
            int currNotBuy = max(prices[i] - fee + aheadBuy, aheadNotBuy);   // Sell with fee

            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }

        return aheadBuy;
    }
};


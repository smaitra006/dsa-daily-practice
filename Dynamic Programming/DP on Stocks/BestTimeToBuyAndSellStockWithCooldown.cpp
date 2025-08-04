#include <bits/stdc++.h>
using namespace std;

/* =========================================================================
 * BEST TIME TO BUY AND SELL STOCK WITH COOLDOWN (Leetcode 309)
 * =========================================================================
 *
 * Problem:
 * --------
 * You are given an array prices where prices[i] is the price of a given stock on the i-th day.
 * After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
 * Return the maximum profit you can achieve.
 *
 * Key Insight:
 * ------------
 * After a SELL operation, next buy must wait for i+2 (i.e., cooldown of 1 day).
 * Track `canBuy` state (1 or 0), and on sell, move to index `i+2`.
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
    int recur(int i, bool canBuy, vector<int>& prices)
    {
        if (i >= prices.size()) return 0;

        if (canBuy) {
            return max(
                -prices[i] + recur(i + 1, false, prices),  // Buy
                recur(i + 1, true, prices)                 // Skip
            );
        }
        else {
            return max(
                prices[i] + recur(i + 2, true, prices),    // Sell (with cooldown)
                recur(i + 1, false, prices)                // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2) + O(n) recursion stack
     * --------------------------------------------------------------------- */
    int solve(vector<int>& prices, int i, bool canBuy, vector<vector<int>>& dp)
    {
        if (i >= prices.size()) return 0;

        if (dp[i][canBuy] != -1) return dp[i][canBuy];

        if (canBuy) {
            return dp[i][canBuy] = max(
                -prices[i] + solve(prices, i + 1, 0, dp),   // Buy
                solve(prices, i + 1, 1, dp)                 // Skip
            );
        }
        else {
            return dp[i][canBuy] = max(
                prices[i] + solve(prices, i + 2, 1, dp),    // Sell (cooldown)
                solve(prices, i + 1, 0, dp)                 // Skip
            );
        }
    }

    /* ---------------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2)
     * --------------------------------------------------------------------- */
    int tabulation(vector<int>& prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

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
                        prices[i] + dp[i + 2][1],    // Sell (cooldown)
                        dp[i + 1][0]                 // Skip
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
    int maxProfit(vector<int>& prices)
    {
        int n = prices.size();
        int aheadBuy = 0, aheadNotBuy = 0;
        int ahead2Buy = 0, ahead2NotBuy = 0;

        for (int i = n - 1; i >= 0; i--) {
            int currBuy = max(-prices[i] + aheadNotBuy, aheadBuy); // Buy
            int currNotBuy = max(prices[i] + ahead2Buy, aheadNotBuy); // Sell

            ahead2Buy = aheadBuy;
            ahead2NotBuy = aheadNotBuy;
            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }

        return aheadBuy;
    }
};


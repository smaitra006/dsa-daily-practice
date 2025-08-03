#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * BEST TIME TO BUY AND SELL STOCK (Leetcode 121)
 * ================================================================
 *
 * Problem:
 * --------
 * You are given an array `prices` where prices[i] is the price of a stock on day `i`.
 * You want to maximize your profit by choosing a single day to buy one stock
 * and choosing a different day in the future to sell that stock.
 *
 * Return the maximum profit you can achieve. If you cannot achieve any profit, return 0.
 *
 * Key Insight:
 * ------------
 * Track the minimum price seen so far and at each step compute the potential profit
 * if you were to sell on that day. Keep track of the maximum profit encountered.
 *
 * TIME COMPLEXITY: O(n)
 * SPACE COMPLEXITY: varies by method
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion
     * TIME: O(2^n)
     * SPACE: O(n)  // recursion stack
     * --------------------------------------------------------------- */
    int recur(int i, bool canBuy, vector<int>& prices)
    {
        if (i == prices.size()) return 0;

        if (canBuy) {
            return max(-prices[i] + recur(i + 1, false, prices),
                0 + recur(i + 1, true, prices));
        }
        else {
            return max(prices[i] + recur(i + 1, true, prices),
                0 + recur(i + 1, false, prices));
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2) + O(n) // dp + recursion stack
     * --------------------------------------------------------------- */
    int solve(vector<int>& prices, int i, bool canBuy, vector<vector<int>>& dp)
    {
        if (i == prices.size()) return 0;

        if (dp[i][canBuy] != -1) return dp[i][canBuy];

        if (canBuy) {
            return dp[i][canBuy] = max(-prices[i] + solve(prices, i + 1, 0, dp),
                0 + solve(prices, i + 1, 1, dp));
        }
        else {
            return dp[i][canBuy] = max(prices[i] + solve(prices, i + 1, 1, dp),
                0 + solve(prices, i + 1, 0, dp));
        }
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 2)
     * SPACE: O(n * 2)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                if (canBuy) {
                    dp[i][canBuy] = max(-prices[i] + dp[i + 1][0],
                        0 + dp[i + 1][1]);
                }
                else {
                    dp[i][canBuy] = max(prices[i] + dp[i + 1][1],
                        0 + dp[i + 1][0]);
                }
            }
        }

        return dp[0][1];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (Greedy — Final Submission)
     * TIME: O(n)
     * SPACE: O(1)
     * --------------------------------------------------------------- */
    int maxProfit(vector<int>& prices)
    {
        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < prices.size(); i++) {
            int profit = prices[i] - minPrice;
            maxProfit = max(maxProfit, profit);
            minPrice = min(minPrice, prices[i]);
        }

        return maxProfit;
    }
};

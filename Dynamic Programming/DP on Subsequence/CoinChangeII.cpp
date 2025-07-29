#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * COIN CHANGE II (Leetcode 518)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a list of coins `coins[]` and an integer `amount`, return
 * the total number of combinations that make up that amount.
 *
 * Each coin can be used unlimited times.
 *
 * Order of coins in combinations doesn’t matter (i.e., combinations,
 * not permutations).
 *
 * Recurrence:
 * -----------
 * dp[i][amt] = dp[i-1][amt] + dp[i][amt - coins[i]]
 *
 * TIME COMPLEXITY: O(n * amount)
 * SPACE COMPLEXITY: O(n * amount) → O(amount) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: Exponential
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int amount, vector<int>& coins)
    {
        if (i == 0) {
            return (amount % coins[0] == 0) ? 1 : 0;
        }

        int notTake = recur(i - 1, amount, coins);
        int take = 0;
        if (coins[i] <= amount)
            take = recur(i, amount - coins[i], coins);

        return take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * amount)
     * SPACE: O(n * amount) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int amount, vector<int>& coins, vector<vector<int>>& dp)
    {
        if (i == 0) {
            return (amount % coins[0] == 0) ? 1 : 0;
        }

        if (dp[i][amount] != -1)
            return dp[i][amount];

        int notTake = memo(i - 1, amount, coins, dp);
        int take = 0;
        if (coins[i] <= amount)
            take = memo(i, amount - coins[i], coins, dp);

        return dp[i][amount] = take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * amount)
     * SPACE: O(n * amount)
     * --------------------------------------------------------------- */
    int tabulation(int amount, vector<int>& coins)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        // Base case: ways to make 0 amount is 1 (choose nothing)
        for (int i = 0; i < n; i++)
            dp[i][0] = 1;

        // Fill first row: only using coins[0]
        for (int amt = 0; amt <= amount; amt++) {
            if (amt % coins[0] == 0)
                dp[0][amt] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int amt = 0; amt <= amount; amt++) {
                int notTake = dp[i - 1][amt];
                int take = (coins[i] <= amt) ? dp[i][amt - coins[i]] : 0;
                dp[i][amt] = take + notTake;
            }
        }

        return dp[n - 1][amount];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * amount)
     * SPACE: O(amount)
     * --------------------------------------------------------------- */
    int change(int amount, vector<int>& coins)
    {
        int n = coins.size();
        vector<int> dp(amount + 1, 0);

        dp[0] = 1; // 1 way to make amount 0

        for (int i = 0; i < n; i++) {
            for (int amt = coins[i]; amt <= amount; amt++) {
                dp[amt] += dp[amt - coins[i]];
            }
        }

        return dp[amount];
    }
};

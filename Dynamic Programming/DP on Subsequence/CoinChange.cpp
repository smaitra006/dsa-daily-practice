#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * COIN CHANGE (Leetcode 322)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a list of coins `coins[]` and an integer `amount`,
 * return the fewest number of coins needed to make up that amount.
 * If that amount cannot be made up by any combination of coins,
 * return -1.
 *
 * Unlimited supply of each coin.
 *
 * Recurrence:
 * -----------
 * dp[i][amt] = min(1 + dp[i][amt - coins[i]], dp[i+1][amt])
 *
 * TIME COMPLEXITY: O(n * amount)
 * SPACE COMPLEXITY: O(n * amount) → O(amount) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n * amount)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int amount, vector<int>& coins)
    {
        if (amount == 0)
            return 0;
        if (i >= coins.size())
            return INT_MAX;

        // Skip current coin
        int notTake = recur(i + 1, amount, coins);

        // Take current coin (unlimited)
        int take = INT_MAX;
        if (coins[i] <= amount) {
            int res = recur(i, amount - coins[i], coins);
            if (res != INT_MAX)
                take = 1 + res;
        }

        return min(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * amount)
     * SPACE: O(n * amount) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int amount, vector<int>& coins, vector<vector<int>>& dp)
    {
        if (amount == 0)
            return 0;
        if (i >= coins.size())
            return INT_MAX;

        if (dp[i][amount] != -1)
            return dp[i][amount];

        int notTake = memo(i + 1, amount, coins, dp);

        int take = INT_MAX;
        if (coins[i] <= amount) {
            take = memo(i, amount - coins[i], coins, dp);
        }
        if (take != INT_MAX) {
            take += 1;
        }

        return dp[i][amount] = min(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * amount)
     * SPACE: O(n * amount)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1)); // Use amount+1 as "infinity"

        // Base Case: 0 amount can be formed using 0 coins
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int amt = 1; amt <= amount; ++amt) {
                int notTake = dp[i - 1][amt];
                int take = amount + 1;
                if (coins[i - 1] <= amt)
                    take = 1 + dp[i][amt - coins[i - 1]]; // Use same row for unbounded pick
                dp[i][amt] = min(take, notTake);
            }
        }

        return (dp[n][amount] == amount + 1) ? -1 : dp[n][amount];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * amount)
     * SPACE: O(amount)
     * --------------------------------------------------------------- */
    int coinChange(vector<int>& coins, int amount)
    {
        int n = coins.size();
        vector<int> prev(amount + 1, amount + 1);

        prev[0] = 0; // base case: 0 amount needs 0 coins

        for (int i = 1; i <= n; i++) {
            vector<int> curr(amount + 1, amount + 1);
            curr[0] = 0;
            for (int amt = 1; amt <= amount; amt++) {
                int not_take = prev[amt];
                int take = amount + 1;
                if (coins[i - 1] <= amt) {
                    take = 1 + curr[amt - coins[i - 1]];
                }
                curr[amt] = min(take, not_take);
            }
            prev = curr;
        }

        return (prev[amount] == amount + 1) ? -1 : prev[amount];
    }
};

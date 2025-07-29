#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 70: CLIMBING STAIRS
 * =================================================================== */

 /**
  * @brief You are climbing a staircase. It takes `n` steps to reach the top.
  *        Each time you can either climb 1 or 2 steps.
  *        In how many distinct ways can you climb to the top?
  *
  * This is a classic Fibonacci-style Dynamic Programming problem.
  *
  * Recurrence Relation:
  * --------------------
  * ways(n) = ways(n - 1) + ways(n - 2)
  *
  * WHY?
  * - To reach step `n`, you must come from step `n-1` (1 step jump) OR
  *   from `n-2` (2 step jump).
  *
  * TIME COMPLEXITY:
  * - Recursion: O(2^n)
  * - Memoization: O(n)
  * - Tabulation: O(n)
  * - Space-Optimized: O(n) time, O(1) space
  *
  * SPACE COMPLEXITY:
  * - O(n) for memo/tabulation, O(1) for optimized
  */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int climbRec(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        return climbRec(n - 1) + climbRec(n - 2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int climbMemo(int n, vector<int>& memo)
    {
        if (n == 0 || n == 1)
            return 1;
        if (memo[n] != -1)
            return memo[n];
        return memo[n] = climbMemo(n - 1, memo) + climbMemo(n - 2, memo);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int climbTab(int n)
    {
        if (n == 0 || n == 1)
            return 1;

        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int climbStairs(int n)
    {
        if (n == 0 || n == 1)
            return 1;

        int prev1 = 1, prev2 = 1, curr = 0;

        for (int i = 2; i <= n; ++i) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return curr;
    }
};

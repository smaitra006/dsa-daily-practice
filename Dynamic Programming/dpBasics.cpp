#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * DYNAMIC PROGRAMMING: CORE TEMPLATE + NOTES
 * =================================================================== */

/**
 * @brief Dynamic Programming (DP) is an optimization technique
 *        used to solve problems with overlapping subproblems
 *        and optimal substructure.
 *
 * TYPES:
 * -------
 * 1. Memoization (Top-Down): Use recursion + cache results.
 * 2. Tabulation (Bottom-Up): Solve smaller problems first, build up.
 *
 * IDENTIFYING DP:
 * ---------------
 *  Overlapping Subproblems
 *  Optimal Substructure
 *  Reuse of results = avoid recomputation
 *
 * TIME COMPLEXITY: Depends on number of states × time per state
 * SPACE COMPLEXITY: Depends on cache/DP array size
 *
 * Common DP Dimensions:
 * ---------------------
 * - 1D DP → dp[i]
 * - 2D DP → dp[i][j]
 * - 3D DP → dp[i][j][k] (used in intervals, substrings, games)
 */

class Solution
{
public:
    // Example Problem: Fibonacci Number using all 3 approaches

    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time, for explanation only)
     * --------------------------------------------------------------- */
    int fibRec(int n)
    {
        if (n <= 1)
            return n;
        return fibRec(n - 1) + fibRec(n - 2); // Overlapping subproblems!
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(N), SPACE: O(N) for memo
     * --------------------------------------------------------------- */
    int fibMemo(int n, vector<int> &memo)
    {
        if (n <= 1)
            return n;
        if (memo[n] != -1)
            return memo[n]; // Use stored result
        return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(N), SPACE: O(N)
     * --------------------------------------------------------------- */
    int fibTab(int n)
    {
        if (n <= 1)
            return n;

        vector<int> dp(n + 1, 0); // dp[i] stores fib(i)
        dp[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2]; // Build from bottom
        }

        return dp[n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (Bottom-Up with O(1) space)
     * --------------------------------------------------------------- */
    int fibOpt(int n)
    {
        if (n <= 1)
            return n;

        int prev2 = 0, prev1 = 1;

        for (int i = 2; i <= n; ++i)
        {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

/* ===================================================================
 * FROG JUMP - MINIMUM COST TO REACH THE LAST STAIR
 * =================================================================== */

/**
 * @brief You are given an integer array `height[]` of size `n`,
 *        where height[i] represents the height of the i-th stair.
 *
 * A frog starts from stair 0 and wants to reach stair `n - 1`.
 * From stair i, it can jump to:
 *     - i + 1 (1-step)
 *     - i + 2 (2-step)
 *
 * The cost of a jump is:
 *     cost = abs(height[i] - height[j])
 *
 * GOAL: Reach stair `n-1` with minimum total cost.
 *
 * Recurrence Relation:
 * ---------------------
 * dp[i] = min(
 *      dp[i - 1] + abs(height[i] - height[i - 1]),
 *      dp[i - 2] + abs(height[i] - height[i - 2])
 * )
 *
 * TIME COMPLEXITY:
 * - Recursion: O(2^n)
 * - Memoization / Tabulation: O(n)
 *
 * SPACE COMPLEXITY:
 * - Memo/Tabulation: O(n), Space-Optimized: O(1)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int frogRec(int i, vector<int> &height)
    {
        if (i == 0)
            return 0;

        int cost1 = frogRec(i - 1, height) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1)
        {
            cost2 = frogRec(i - 2, height) + abs(height[i] - height[i - 2]);
        }

        return min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogMemo(int i, vector<int> &height, vector<int> &dp)
    {
        if (i == 0)
            return 0;
        if (dp[i] != -1)
            return dp[i];

        int cost1 = frogMemo(i - 1, height, dp) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1)
        {
            cost2 = frogMemo(i - 2, height, dp) + abs(height[i] - height[i - 2]);
        }

        return dp[i] = min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogTab(vector<int> &height)
    {
        int n = height.size();
        vector<int> dp(n, 0);
        dp[0] = 0;

        for (int i = 1; i < n; ++i)
        {
            int cost1 = dp[i - 1] + abs(height[i] - height[i - 1]);
            int cost2 = (i > 1) ? dp[i - 2] + abs(height[i] - height[i - 2]) : INT_MAX;

            dp[i] = min(cost1, cost2);
        }

        return dp[n - 1];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int frogJump(vector<int> &height)
    {
        int n = height.size();
        int prev1 = 0; // dp[i - 1]
        int prev2 = 0; // dp[i - 2]

        for (int i = 1; i < n; ++i)
        {
            int cost1 = prev1 + abs(height[i] - height[i - 1]);
            int cost2 = (i > 1) ? prev2 + abs(height[i] - height[i - 2]) : INT_MAX;

            int curr = min(cost1, cost2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

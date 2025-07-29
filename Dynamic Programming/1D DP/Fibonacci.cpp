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
    int fibMemo(int n, vector<int>& memo)
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

        for (int i = 2; i <= n; ++i) {
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

        for (int i = 2; i <= n; ++i) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

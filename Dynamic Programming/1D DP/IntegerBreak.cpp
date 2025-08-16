#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem: Integer Break (Leetcode 343)
-------------------------------------------------------------------------------
Given an integer n, break it into the sum of k positive integers, where k >= 2,
and maximize the product of those integers. Return the maximum product.

-------------------------------------------------------------------------------
Approach:
1. Recursion (Try all partitions)
2. Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimized (Reduced space usage for 1D DP)

-------------------------------------------------------------------------------
Time Complexity:
- Recursion:   Exponential (O(2^n))
- Memoization: O(n^2)
- Tabulation:  O(n^2)
- Space Opt:   O(n^2) → optimized in dp array usage

Space Complexity:
- Recursion:   O(n) (stack)
- Memoization: O(n) (dp array + stack)
- Tabulation:  O(n) (dp array)
- Space Opt:   O(n)

===============================================================================
*/

class Solution {
public:

    //============================================================================
    // Method 1: Recursion
    //============================================================================
    int solveRec(int n)
    {
        if (n == 1) return 1;

        int ans = 0;
        for (int i = 1; i < n; i++) {
            // Either take i * (n - i) directly OR break (n - i) further
            ans = max(ans, max(i * (n - i), i * solveRec(n - i)));
        }
        return ans;
    }

    //============================================================================
    // Method 2: Memoization (Top-Down DP)
    //============================================================================
    vector<int> dp;
    int solveMemo(int n)
    {
        if (n == 1) return 1;
        if (dp[n] != -1) return dp[n];

        int ans = 0;
        for (int i = 1; i < n; i++) {
            ans = max(ans, max(i * (n - i), i * solveMemo(n - i)));
        }
        return dp[n] = ans;
    }

    //============================================================================
    // Method 3: Tabulation (Bottom-Up DP)
    //============================================================================
    int solveTab(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;

        for (int num = 2; num <= n; num++) {
            for (int i = 1; i < num; i++) {
                dp[num] = max(dp[num], max(i * (num - i), i * dp[num - i]));
            }
        }
        return dp[n];
    }

    //============================================================================
    // Method 4: Space Optimized
    // (1D dp is already optimal here, no further big reduction possible)
    //============================================================================
    int solveSpaceOpt(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;

        for (int num = 2; num <= n; num++) {
            int best = 0;
            for (int i = 1; i < num; i++) {
                best = max(best, max(i * (num - i), i * dp[num - i]));
            }
            dp[num] = best;
        }
        return dp[n];
    }

    //============================================================================
    // Main Function
    //============================================================================
    int integerBreak(int n)
    {
        // --- Uncomment one approach to use ---

        // return solveRec(n);                // Recursion
        // dp.assign(n + 1, -1); return solveMemo(n); // Memoization
        // return solveTab(n);                // Tabulation
        return solveSpaceOpt(n);              // Space Optimized
    }
};

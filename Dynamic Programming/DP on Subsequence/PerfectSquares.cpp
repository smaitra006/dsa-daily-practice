#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem: Perfect Squares (Leetcode 279)
===============================================================================
Task:
------
Given an integer `n`, return the least number of perfect square numbers
(e.g., 1, 4, 9, 16, ...) which sum to `n`.

Example:
---------
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Constraints:
------------
1 <= n <= 10^4

===============================================================================
Approach:
===============================================================================
We try to break `n` into smaller parts by subtracting perfect squares
and recursively finding the minimum count needed.

We will implement:
1. Recursion (Brute Force)
2. Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimization (Possible as 1D DP)

===============================================================================
Complexity Analysis:
===============================================================================
Let m = sqrt(n) (number of perfect squares ≤ n)
- Recursion:  O(m^n) → exponential
- Memoization: O(n * m)
- Tabulation:  O(n * m)
- Space Optimized: O(n)

===============================================================================
*/

class Solution {
public:

    //============================================================================
    // 1. Recursion
    //============================================================================
    int solveRec(int n, int i)
    {
        if (n == 0) return 0;          // Found exact sum
        if (i * i > n) return INT_MAX; // No perfect square fits

        // Choice 1: Skip this square
        int not_take = solveRec(n, i + 1);

        // Choice 2: Take this square (can reuse)
        int take = INT_MAX;
        if (n - (i * i) >= 0) {
            int res = solveRec(n - (i * i), i);
            if (res != INT_MAX) take = 1 + res;
        }

        return min(take, not_take);
    }

    //============================================================================
    // 2. Memoization
    //============================================================================
    int solveMemo(int n, int i, vector<vector<int>>& dp)
    {
        if (n == 0) return 0;
        if (i * i > n) return INT_MAX;

        if (dp[n][i] != -1) return dp[n][i];

        int not_take = solveMemo(n, i + 1, dp);
        int take = INT_MAX;
        if (n - (i * i) >= 0) {
            int res = solveMemo(n - (i * i), i, dp);
            if (res != INT_MAX) take = 1 + res;
        }

        return dp[n][i] = min(take, not_take);
    }

    //============================================================================
    // 3. Tabulation
    //============================================================================
    int solveTab(int n)
    {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0; // Base case

        for (int num = 1; num <= n; num++) {
            for (int sq = 1; sq * sq <= num; sq++) {
                dp[num] = min(dp[num], 1 + dp[num - sq * sq]);
            }
        }
        return dp[n];
    }

    //============================================================================
    // 4. Space Optimization
    //============================================================================
    // Already optimized to 1D DP in Tabulation — can't reduce further
    // because each state depends on smaller states of the same dp array.

    //============================================================================
    // Main Function
    //============================================================================
    int numSquares(int n)
    {
        // --- Method 1: Recursion ---
        // return solveRec(n, 1);

        // --- Method 2: Memoization ---
        // int maxI = sqrt(n);
        // vector<vector<int>> dp(n + 1, vector<int>(maxI + 2, -1));
        // return solveMemo(n, 1, dp);

        // --- Method 3: Tabulation ---
        return solveTab(n);

        // --- Method 4: Space Optimization ---
        // Same as Tabulation
    }
};

/*
===============================================================================
Example Usage:
===============================================================================
Solution sol;
cout << sol.numSquares(12); // Output: 3
cout << sol.numSquares(13); // Output: 2
===============================================================================
*/


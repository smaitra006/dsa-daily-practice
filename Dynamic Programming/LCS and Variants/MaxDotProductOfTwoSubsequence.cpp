#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Maximum Dot Product of Two Subsequences (LeetCode 1458)
// Task: Given two integer arrays nums1 and nums2, return the maximum dot
//       product between non-empty subsequences of the two arrays.
//
// Key Observations:
//   - Must pick at least one element from both arrays.
//   - Choices: Take nums1[i] * nums2[j], extend with previous subsequence,
//              or skip from either array.
//   - Very similar to LCS-like DP, but with product instead of equality check.
//
// Approaches:
//   1. Recursion (Exponential, TLE)
//   2. Memoization (Top-Down DP, O(m * n))
//   3. Tabulation (Bottom-Up DP, O(m * n))
//   4. Space Optimization (2-row DP, O(n))
//
// Complexity:
//   - Time: O(m * n) for DP
//   - Space: O(m * n) → O(n) after optimization
//==============================================================================

class Solution {
public:

    //==========================================================================
    // Method 1: Recursion (Exponential)
    //==========================================================================
    int solveRec(vector<int>& A, vector<int>& B, int i, int j)
    {
        if (i == A.size() || j == B.size()) return INT_MIN; // must pick at least one

        int prod = A[i] * B[j];

        // Choices: take current pair, extend with next, skip one from either array
        int takeBoth = prod + max(0, solveRec(A, B, i + 1, j + 1));
        int skipA = solveRec(A, B, i + 1, j);
        int skipB = solveRec(A, B, i, j + 1);

        return max({ prod, takeBoth, skipA, skipB });
    }


    //==========================================================================
    // Method 2: Memoization (Top-Down DP)
    //==========================================================================
    int solveMemo(vector<int>& A, vector<int>& B, int i, int j, vector<vector<int>>& dp)
    {
        if (i == A.size() || j == B.size()) return INT_MIN;

        if (dp[i][j] != INT_MIN) return dp[i][j];

        int prod = A[i] * B[j];
        int takeBoth = prod + max(0, solveMemo(A, B, i + 1, j + 1, dp));
        int skipA = solveMemo(A, B, i + 1, j, dp);
        int skipB = solveMemo(A, B, i, j + 1, dp);

        return dp[i][j] = max({ prod, takeBoth, skipA, skipB });
    }


    //==========================================================================
    // Method 3: Tabulation (Bottom-Up DP)
    //==========================================================================
    int solveTab(vector<int>& A, vector<int>& B)
    {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MIN));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int prod = A[i - 1] * B[j - 1];
                dp[i][j] = max({
                    prod,
                    prod + max(0, dp[i - 1][j - 1]),
                    dp[i - 1][j],
                    dp[i][j - 1]
                    });
            }
        }
        return dp[m][n];
    }


    //==========================================================================
    // Method 4: Space Optimization (2-row DP)
    //==========================================================================
    int solveSO(vector<int>& A, vector<int>& B)
    {
        int m = A.size(), n = B.size();
        vector<int> prev(n + 1, INT_MIN), curr(n + 1, INT_MIN);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int prod = A[i - 1] * B[j - 1];
                curr[j] = max({
                    prod,
                    prod + max(0, prev[j - 1]),
                    prev[j],
                    curr[j - 1]
                    });
            }
            prev = curr;
        }
        return prev[n];
    }


    //==========================================================================
    // Main Function
    //==========================================================================
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2)
    {
        // Method 1 (Recursion) → TLE for large inputs
        // return solveRec(nums1, nums2, 0, 0);

        // Method 2 (Memoization)
        // vector<vector<int>> dp(nums1.size(), vector<int>(nums2.size(), INT_MIN));
        // return solveMemo(nums1, nums2, 0, 0, dp);

        // Method 3 (Tabulation)
        // return solveTab(nums1, nums2);

        // Method 4 (Space Optimized)
        return solveSO(nums1, nums2);
    }
};

#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem: Maximum Length of Repeated Subarray (Leetcode 718)
-------------------------------------------------------------------------------
Given two integer arrays nums1 and nums2, return the maximum length of a
subarray that appears in both arrays.

-------------------------------------------------------------------------------
Key Idea:
- Similar to "Longest Common Substring" (not subsequence).
- If nums1[i] == nums2[j], then we extend the length from dp[i-1][j-1].
- Otherwise, reset to 0 since substring must be contiguous.

-------------------------------------------------------------------------------
Approach:
1. Recursion (Check matching suffixes)
2. Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimized (1D Rolling Arrays)

-------------------------------------------------------------------------------
Time Complexity:
- Recursion:   Exponential
- Memoization: O(m * n)
- Tabulation:  O(m * n)
- Space Opt:   O(n)

Space Complexity:
- Recursion:   O(m * n) (stack)
- Memoization: O(m * n) (dp + stack)
- Tabulation:  O(m * n)
- Space Opt:   O(n)

===============================================================================
*/

class Solution {
public:

    //============================================================================
    // Method 1: Recursion
    //============================================================================
    int solveRec(vector<int>& nums1, vector<int>& nums2, int i, int j, int count)
    {
        if (i == 0 || j == 0) return count;

        int ans = count;
        if (nums1[i - 1] == nums2[j - 1]) {
            ans = max(ans, solveRec(nums1, nums2, i - 1, j - 1, count + 1));
        }

        // Reset count when mismatch, try other options
        ans = max(ans, max(solveRec(nums1, nums2, i - 1, j, 0),
            solveRec(nums1, nums2, i, j - 1, 0)));
        return ans;
    }

    //============================================================================
    // Method 2: Memoization (Top-Down DP)
    //============================================================================
    int dpMemo[1001][1001];
    int solveMemo(vector<int>& nums1, vector<int>& nums2, int i, int j, int& ans)
    {
        if (i == 0 || j == 0) return 0;

        if (dpMemo[i][j] != -1) return dpMemo[i][j];

        if (nums1[i - 1] == nums2[j - 1]) {
            dpMemo[i][j] = 1 + solveMemo(nums1, nums2, i - 1, j - 1, ans);
            ans = max(ans, dpMemo[i][j]);
        }
        else {
            dpMemo[i][j] = 0;
        }

        // explore other choices
        solveMemo(nums1, nums2, i - 1, j, ans);
        solveMemo(nums1, nums2, i, j - 1, ans);

        return dpMemo[i][j];
    }

    //============================================================================
    // Method 3: Tabulation (Bottom-Up DP)
    //============================================================================
    int solveTab(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int ans = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    ans = max(ans, dp[i][j]);
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }
        return ans;
    }

    //============================================================================
    // Method 4: Space Optimized (Rolling Arrays)
    //============================================================================
    int solveSpaceOpt(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        int ans = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    ans = max(ans, curr[j]);
                }
                else {
                    curr[j] = 0;
                }
            }
            prev = curr;
        }
        return ans;
    }

    //============================================================================
    // Main Function
    //============================================================================
    int findLength(vector<int>& nums1, vector<int>& nums2)
    {
        // --- Uncomment one approach to use ---

        // return solveRec(nums1, nums2, nums1.size(), nums2.size(), 0); // Recursion

        // memset(dpMemo, -1, sizeof(dpMemo));
        // int ans = 0;
        // solveMemo(nums1, nums2, nums1.size(), nums2.size(), ans);
        // return ans;                                                     // Memoization

        // return solveTab(nums1, nums2);                                   // Tabulation
        return solveSpaceOpt(nums1, nums2);                                // Space Optimized
    }
};

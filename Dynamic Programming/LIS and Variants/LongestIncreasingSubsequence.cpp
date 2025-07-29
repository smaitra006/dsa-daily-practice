#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LONGEST INCREASING SUBSEQUENCE (Leetcode 300)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an integer array `nums`, return the length of the longest
 * strictly increasing subsequence (not necessarily contiguous).
 *
 * Recurrence:
 * -----------
 * For index `i` and previous index `prev`, we try:
 *  - Take nums[i] if nums[i] > nums[prev]
 *  - Don't take nums[i]
 *
 * TIME COMPLEXITY:
 * - Recursion: O(2^n)
 * - Memoization: O(n^2)
 * - Tabulation: O(n^2)
 * - Binary Search Optimization: O(n log n)
 *
 * SPACE COMPLEXITY:
 * - O(n^2) for DP table or O(n) with optimization
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int prev, vector<int>& nums)
    {
        if (i == nums.size())
            return 0;

        int notTake = recur(i + 1, prev, nums);
        int take = 0;
        if (prev == -1 || nums[i] > nums[prev])
            take = 1 + recur(i + 1, i, nums);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n^2)
     * SPACE: O(n^2) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int prev, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (i == nums.size())
            return 0;
        if (dp[i][prev + 1] != -1)
            return dp[i][prev + 1];

        int notTake = memo(i + 1, prev, nums, dp);
        int take = 0;
        if (prev == -1 || nums[i] > nums[prev])
            take = 1 + memo(i + 1, i, nums, dp);

        return dp[i][prev + 1] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> dp(n, 1); // dp[i] = LIS ending at index i
        int maxLIS = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLIS = max(maxLIS, dp[i]);
        }

        return maxLIS;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized using Binary Search (Patience Sort)
     * TIME: O(n log n)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int lengthOfLIS(vector<int>& nums)
    {
        vector<int> lis;

        for (int num : nums) {
            auto it = lower_bound(lis.begin(), lis.end(), num); // gives me just >= num
            if (it == lis.end()) {
                // not found any such item, so insert it
                lis.push_back(num); // extends LIS
            }
            else {
                *it = num; // replace to maintain smaller values
            }
        }

        return lis.size();
    }
};

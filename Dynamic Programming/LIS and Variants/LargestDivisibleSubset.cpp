#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LARGEST DIVISIBLE SUBSET (Leetcode 368)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a set of distinct positive integers, find the largest subset such that:
 *     For every pair (Si, Sj) in subset:
 *         Si % Sj == 0 or Sj % Si == 0
 *
 * Return the subset in any order.
 *
 * Approach:
 * ---------
 * 1. Sort the array.
 * 2. Use a variation of Longest Increasing Subsequence.
 * 3. Track maximum length and predecessors to reconstruct the subset.
 *
 * TIME COMPLEXITY: O(n^2)
 * SPACE COMPLEXITY: O(n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursion stack
     * --------------------------------------------------------------- */
    int recur(int i, int prevIdx, vector<int>& nums)
    {
        if (i == nums.size()) return 0;

        int notTake = recur(i + 1, prevIdx, nums);
        int take = 0;
        if (prevIdx == -1 || nums[i] % nums[prevIdx] == 0)
            take = 1 + recur(i + 1, i, nums);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n^2)
     * SPACE: O(n^2)
     * --------------------------------------------------------------- */
    int memo(int i, int prevIdx, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (i == nums.size()) return 0;
        if (dp[i][prevIdx + 1] != -1) return dp[i][prevIdx + 1];

        int notTake = memo(i + 1, prevIdx, nums, dp);
        int take = 0;
        if (prevIdx == -1 || nums[i] % nums[prevIdx] == 0)
            take = 1 + memo(i + 1, i, nums, dp);

        return dp[i][prevIdx + 1] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP without subset recovery)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1);
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                    maxLen = max(maxLen, dp[i]);
                }
            }
        }
        return maxLen;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Tabulation with Path Recovery (Final Submission)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1);      // Length of largest subset ending at i
        vector<int> prev(n, -1);   // To trace back the path
        int maxLIS = 1;
        int maxIdx = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }
            if (dp[i] > maxLIS) {
                maxLIS = dp[i];
                maxIdx = i;
            }
        }

        // Reconstruct the subset
        vector<int> ans;
        int i = maxIdx;
        while (i != -1) {
            ans.push_back(nums[i]);
            i = prev[i];
        }

        return ans;  // Can reverse(ans.begin(), ans.end()) if needed
    }
};

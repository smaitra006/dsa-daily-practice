#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * MAX BALANCED SUBSEQUENCE SUM (Leetcode 2866)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums`, find the maximum sum of a **subsequence**
 * such that for each selected index `i`, the condition:
 *     nums[i] - i >= nums[j] - j (for all previous selected j)
 * holds true.
 *
 * This is similar to Longest Increasing Subsequence but with a
 * custom comparator: nums[i] - i ≥ nums[j] - j.
 *
 * Observation:
 * ------------
 * Let val[i] = nums[i] - i
 * We need to find the max sum subsequence where val[i] ≥ val[j]
 *
 * Recurrence:
 * -----------
 * dp[i] = max over all j < i where val[i] ≥ val[j]:
 *         dp[i] = max(dp[i], dp[j] + nums[i])
 *
 * TIME COMPLEXITY: O(n^2)
 * SPACE COMPLEXITY: O(n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    long long recur(int i, int prev, vector<int>& nums, vector<long long>& val)
    {
        if (i == nums.size()) return 0;

        long long notTake = recur(i + 1, prev, nums, val);
        long long take = LLONG_MIN;

        if (prev == -1 || val[i] >= val[prev])
            take = nums[i] + recur(i + 1, i, nums, val);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n^2)
     * SPACE: O(n^2) + O(n) stack
     * --------------------------------------------------------------- */
    long long memo(int i, int prev, vector<int>& nums, vector<long long>& val, vector<vector<long long>>& dp)
    {
        if (i == nums.size()) return 0;
        if (dp[i][prev + 1] != -1) return dp[i][prev + 1];

        long long notTake = memo(i + 1, prev, nums, val, dp);
        long long take = LLONG_MIN;

        if (prev == -1 || val[i] >= val[prev])
            take = nums[i] + memo(i + 1, i, nums, val, dp);

        return dp[i][prev + 1] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    long long tabulation(vector<int>& nums)
    {
        int n = nums.size();
        vector<long long> val(n), dp(n);
        for (int i = 0; i < n; i++) val[i] = (long long)nums[i] - i;

        long long maxSum = nums[0];
        for (int i = 0; i < n; i++) {
            dp[i] = nums[i];
            for (int j = 0; j < i; j++) {
                if (val[i] >= val[j]) {
                    dp[i] = max(dp[i], dp[j] + (long long)nums[i]);
                }
            }
            maxSum = max(maxSum, dp[i]);
        }

        return maxSum;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Optimized DP (Final Submission)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    long long maxBalancedSubsequenceSum(vector<int>& nums)
    {
        int n = nums.size();
        vector<long long> val(n), dp(n, LLONG_MIN);
        for (int i = 0; i < n; i++) val[i] = (long long)nums[i] - i;

        long long maxSum = LLONG_MIN;

        for (int i = 0; i < n; i++) {
            dp[i] = nums[i];
            for (int j = 0; j < i; j++) {
                if (val[i] >= val[j]) {
                    dp[i] = max(dp[i], dp[j] + nums[i]);
                }
            }
            maxSum = max(maxSum, dp[i]);
        }

        return maxSum;
    }
};

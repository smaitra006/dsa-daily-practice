#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * PARTITION EQUAL SUBSET SUM (Leetcode 416)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a non-empty array `nums` of positive integers, determine
 * if the array can be partitioned into two subsets such that the
 * sum of elements in both subsets is equal.
 *
 * Recurrence:
 * -----------
 * dp[i][k] = dp[i+1][k] || dp[i+1][k - nums[i]] if k >= nums[i]
 *
 * TIME COMPLEXITY: O(n * k)
 * SPACE COMPLEXITY: O(n * k) → O(k) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    bool recur(int i, int k, vector<int>& nums)
    {
        if (k == 0)
            return true;
        if (i >= nums.size())
            return false;

        bool take = false;
        if (k >= nums[i])
            take = recur(i + 1, k - nums[i], nums);

        bool notTake = recur(i + 1, k, nums);

        return take || notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k)
     * SPACE: O(n * k) + O(n) stack
     * --------------------------------------------------------------- */
    bool memo(int i, int k, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (k == 0)
            return true;
        if (i >= nums.size())
            return false;
        if (dp[i][k] != -1)
            return dp[i][k];

        bool take = false;
        if (k >= nums[i])
            take = memo(i + 1, k - nums[i], nums, dp);

        bool notTake = memo(i + 1, k, nums, dp);

        return dp[i][k] = take || notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k)
     * SPACE: O(n * k)
     * --------------------------------------------------------------- */
    bool tabulation(vector<int>& nums, int target)
    {
        int n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // base case: sum = 0 is always possible
        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= target; k++) {
                bool notTake = dp[i - 1][k];
                bool take = false;
                if (k >= nums[i - 1])
                    take = dp[i - 1][k - nums[i - 1]];
                dp[i][k] = take || notTake;
            }
        }

        return dp[n][target];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * k)
     * SPACE: O(k)
     * --------------------------------------------------------------- */
    bool canPartition(vector<int>& nums)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if (total_sum % 2 != 0)
            return false;

        int target = total_sum / 2;
        int n = nums.size();

        vector<bool> prev(target + 1, false), curr(target + 1, false);
        prev[0] = true, curr[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= target; k++) {
                bool notTake = prev[k];
                bool take = (k >= nums[i - 1]) ? prev[k - nums[i - 1]] : false;
                curr[k] = take || notTake;
            }
            prev = curr;
        }

        return prev[target];
    }
};

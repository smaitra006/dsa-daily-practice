#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * PARTITIONS WITH GIVEN DIFFERENCE
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums` and a difference `d`, count the number
 * of ways to partition the array into two subsets such that
 * the absolute difference of their sums is exactly `d`.
 *
 * Observation:
 * ------------
 * Let total_sum = sum(nums)
 * Let the two subset sums be s1 and s2 such that:
 *   s1 - s2 = d  and  s1 + s2 = total_sum
 *
 * Solving:
 * --------
 *   s1 = (total_sum + d) / 2
 *
 * So, reduce to: Count number of subsets with sum = s1
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
    int recur(int i, int target, vector<int>& nums)
    {
        if (i == 0) {
            if (target == 0 && nums[0] == 0)
                return 2; // pick or not pick 0
            if (target == 0 || target == nums[0])
                return 1;
            return 0;
        }

        int notTake = recur(i - 1, target, nums);
        int take = 0;
        if (target >= nums[i])
            take = recur(i - 1, target - nums[i], nums);

        return take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k)
     * SPACE: O(n * k) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int target, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (i == 0) {
            if (target == 0 && nums[0] == 0)
                return 2;
            if (target == 0 || target == nums[0])
                return 1;
            return 0;
        }

        if (dp[i][target] != -1)
            return dp[i][target];

        int notTake = memo(i - 1, target, nums, dp);
        int take = 0;
        if (target >= nums[i])
            take = memo(i - 1, target - nums[i], nums, dp);

        return dp[i][target] = take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k)
     * SPACE: O(n * k)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums, int target)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        // base case
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int t = 0; t <= target; t++) {
                int notTake = dp[i - 1][t];
                int take = 0;
                if (t >= nums[i - 1])
                    take = dp[i - 1][t - nums[i - 1]];
                dp[i][t] = take + notTake;
            }
        }

        return dp[n][target];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * k)
     * SPACE: O(k)
     * --------------------------------------------------------------- */
    int countPartitions(int n, int d, vector<int>& nums)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if ((total_sum + d) % 2 != 0 || total_sum < d)
            return 0;

        int target = (total_sum + d) / 2;

        vector<int> prev(target + 1, 0);

        // base case
        prev[0] = 1;

        for (int i = 1; i <= n; i++) {
            vector<int> curr(target + 1, 0);
            for (int t = 0; t <= target; t++) {
                int notTake = prev[t];
                int take = 0;
                if (t >= nums[i - 1])
                    take = prev[t - nums[i - 1]];
                curr[t] = take + notTake;
            }
            prev = curr;
        }

        return prev[target];
    }
};

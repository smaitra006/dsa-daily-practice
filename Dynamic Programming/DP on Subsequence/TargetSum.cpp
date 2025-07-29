#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * TARGET SUM (Leetcode 494)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an integer array `nums` and an integer `target`, return the
 * number of ways to assign '+' or '-' signs to each element so that
 * the resulting expression evaluates to `target`.
 *
 * Observation:
 * ------------
 * Let sum(P) = subset with '+' signs
 * Let sum(N) = subset with '-' signs
 * Then:
 *   sum(P) - sum(N) = target
 *   sum(P) + sum(N) = total sum = S
 *
 * → 2 * sum(P) = S + target
 * → sum(P) = (S + target) / 2 = k
 *
 * This reduces to: Count the number of subsets with sum = k
 *
 * Recurrence:
 * -----------
 * dp[i][k] = dp[i-1][k] + dp[i-1][k - nums[i]]
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
    int recur(int i, int k, vector<int>& nums)
    {
        if (k < 0)
            return 0;

        if (i == 0) {
            if (k == 0 && nums[0] == 0)
                return 2; // +0, -0
            if (k == 0)
                return 1;                  // no element picked
            return (nums[0] == k) ? 1 : 0; // pick or not
        }

        int notTake = recur(i - 1, k, nums);
        int take = 0;
        if (nums[i] <= k)
            take = recur(i - 1, k - nums[i], nums);

        return take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k)
     * SPACE: O(n * k) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int k, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (k < 0)
            return 0;

        if (i == 0) {
            if (k == 0 && nums[0] == 0)
                return 2;
            if (k == 0)
                return 1;
            return (nums[0] == k) ? 1 : 0;
        }

        if (dp[i][k] != -1)
            return dp[i][k];

        int notTake = memo(i - 1, k, nums, dp);
        int take = 0;
        if (nums[i] <= k)
            take = memo(i - 1, k - nums[i], nums, dp);

        return dp[i][k] = take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k)
     * SPACE: O(n * k)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums, int target)
    {
        int n = nums.size();
        int S = accumulate(nums.begin(), nums.end(), 0);
        if ((S + target) % 2 != 0 || S < abs(target))
            return 0;
        int k = (S + target) / 2;

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // Base case: i == 0
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int t = 0; t <= k; t++) {
                int notTake = dp[i - 1][t];
                int take = (nums[i - 1] <= t) ? dp[i - 1][t - nums[i - 1]] : 0;
                dp[i][t] = take + notTake;
            }
        }

        return dp[n][k];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * k)
     * SPACE: O(k)
     * --------------------------------------------------------------- */
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int n = nums.size();
        int S = accumulate(nums.begin(), nums.end(), 0);
        if ((S + target) % 2 != 0 || S < abs(target))
            return 0;

        int k = (S + target) / 2;

        vector<int> prev(k + 1, 0);

        // Base case
        prev[0] = 1;

        for (int i = 1; i <= n; i++) {
            vector<int> curr(k + 1, 0);
            for (int t = 0; t <= k; t++) {
                int notTake = prev[t];
                int take = (nums[i - 1] <= t) ? prev[t - nums[i - 1]] : 0;
                curr[t] = take + notTake;
            }
            prev = curr;
        }

        return prev[k];
    }
};

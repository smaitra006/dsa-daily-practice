#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * COUNT SUBSETS WITH SUM K (DP – 0/1 Knapsack Variant)
 * =================================================================== */

 /**
  * @brief Given an array of integers and a target sum `k`,
  *        return the number of subsets whose elements sum to exactly `k`.
  *
  * Recurrence:
  * -----------
  * dp[i][target] = dp[i+1][target] + dp[i+1][target - arr[i]] (if arr[i] <= target)
  *
  * TIME COMPLEXITY:
  * - Recursion:      O(2^n)
  * - Memoization:    O(n * k)
  * - Tabulation:     O(n * k)
  * - Space Optimized: O(k)
  *
  * SPACE COMPLEXITY:
  * - Memoization:    O(n * k)
  * - Tabulation:     O(n * k)
  * - Space Optimized: O(k)
  */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int recur(int i, int target, vector<int>& nums)
    {
        if (i == 0) {
            if (target == 0 && nums[0] == 0)
                return 2; // {} and {0}
            if (target == 0 || target == nums[0])
                return 1;
            return 0;
        }

        int notPick = recur(i - 1, target, nums);
        int pick = 0;
        if (nums[i] <= target)
            pick = recur(i - 1, target - nums[i], nums);

        return pick + notPick;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k), SPACE: O(n * k)
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

        int notPick = memo(i - 1, target, nums, dp);
        int pick = 0;
        if (nums[i] <= target)
            pick = memo(i - 1, target - nums[i], nums, dp);

        return dp[i][target] = pick + notPick;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k), SPACE: O(n * k)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // Base Case: 1 way to form sum 0 with 0 elements(empty subset)
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int target = 0; target <= k; target++) {
                int notPick = dp[i - 1][target];
                int pick = 0;
                if (nums[i - 1] <= target)
                    pick = dp[i - 1][target - nums[i - 1]];
                dp[i][target] = notPick + pick;
            }
        }

        // Special fix: if nums[0] == 0, there are 2 subsets that make sum 0: {} and {0}
        if (nums[0] == 0)
            dp[1][0] = 2;

        return dp[n][k];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (O(k) Space)
     * TIME: O(n * k), SPACE: O(k)
     * --------------------------------------------------------------- */
    int countSubsets(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<int> prev(k + 1, 0), curr(k + 1, 0);

        prev[0] = (nums[0] == 0) ? 2 : 1;

        for (int i = 1; i <= n; ++i) {
            curr[0] = (nums[i - 1] == 0) ? 2 * prev[0] : prev[0]; // careful for zeros -> 2 * prev[0] because if nums[i] == 0 , then we can have all subsets of prev[0] and also all those with a zero in it
            for (int target = 1; target <= k; ++target) {
                int notPick = prev[target];
                int pick = 0;
                if (nums[i - 1] <= target)
                    pick = prev[target - nums[i - 1]];
                curr[target] = pick + notPick;
            }
            prev = curr;
        }

        return prev[k];
    }
};

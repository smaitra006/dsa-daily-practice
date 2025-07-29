#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 198: HOUSE ROBBER
 * =================================================================== */

 /**
  * @brief You are a professional robber planning to rob houses along a street.
  *        Each house has a certain amount of money. Adjacent houses have alarms,
  *        so you can't rob two directly connected houses.
  *
  * GOAL: Return the maximum amount of money you can rob without alerting the police.
  *
  * Recurrence Relation:
  * --------------------
  * dp[i] = max(
  *      nums[i] + dp[i - 2],   // Pick current house and skip previous
  *      dp[i - 1]              // Skip current house
  * )
  *
  * TIME COMPLEXITY:
  * - Recursion: O(2^n)
  * - Memoization / Tabulation: O(n)
  *
  * SPACE COMPLEXITY:
  * - Memo/Tabulation: O(n), Optimized: O(1)
  */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int robRec(vector<int>& nums, int idx)
    {
        if (idx == 0)
            return nums[0];
        if (idx < 0)
            return 0;

        int pick = nums[idx] + robRec(nums, idx - 2);
        int notPick = robRec(nums, idx - 1);

        return max(pick, notPick);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int solveMemo(vector<int>& nums, int idx, vector<int>& memo)
    {
        if (idx == 0)
            return nums[0];
        if (idx < 0)
            return 0;

        if (memo[idx] != -1)
            return memo[idx];

        int pick = nums[idx] + solveMemo(nums, idx - 2, memo);
        int notPick = solveMemo(nums, idx - 1, memo);

        return memo[idx] = max(pick, notPick);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int robTab(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];

        for (int i = 1; i < n; ++i) {
            int pick = nums[i] + (i >= 2 ? dp[i - 2] : 0);
            int notPick = dp[i - 1];
            dp[i] = max(pick, notPick);
        }

        return dp[n - 1];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int rob(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        int prev1 = nums[0]; // dp[i - 1]
        int prev2 = 0;       // dp[i - 2]

        for (int i = 1; i < n; ++i) {
            int pick = nums[i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 213: HOUSE ROBBER II
 * =================================================================== */

 /**
  * @brief You are a professional robber planning to rob houses arranged in a circle.
  *        Each house has some money, but adjacent houses cannot be robbed.
  *
  * KEY DIFFERENCE from House Robber I:
  * - First and last house are also adjacent!
  * - So, we cannot rob both the first and last house together.
  *
  * STRATEGY:
  * - Case 1: Rob from house 0 to n-2 (exclude last)
  * - Case 2: Rob from house 1 to n-1 (exclude first)
  * - Take max of both cases
  *
  * TIME COMPLEXITY: O(n)
  * SPACE COMPLEXITY: O(n) for memo/tabulation, O(1) for optimized
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

    int robCircleRec(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        vector<int> case1(nums.begin(), nums.end() - 1);
        vector<int> case2(nums.begin() + 1, nums.end());

        int a1 = robRec(case1, case1.size() - 1);
        int a2 = robRec(case2, case2.size() - 1);

        return max(a1, a2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int robMemo(vector<int>& nums, int idx, vector<int>& memo)
    {
        if (idx == 0)
            return nums[0];
        if (idx < 0)
            return 0;

        if (memo[idx] != -1)
            return memo[idx];

        int pick = nums[idx] + robMemo(nums, idx - 2, memo);
        int notPick = robMemo(nums, idx - 1, memo);

        return memo[idx] = max(pick, notPick);
    }

    int robCircleMemo(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        vector<int> case1(nums.begin(), nums.end() - 1);
        vector<int> case2(nums.begin() + 1, nums.end());

        vector<int> memo1(n, -1);
        vector<int> memo2(n, -1);

        int a1 = robMemo(case1, case1.size() - 1, memo1);
        int a2 = robMemo(case2, case2.size() - 1, memo2);

        return max(a1, a2);
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

    int robCircleTab(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        vector<int> case1(nums.begin(), nums.end() - 1);
        vector<int> case2(nums.begin() + 1, nums.end());

        int a1 = robTab(case1);
        int a2 = robTab(case2);

        return max(a1, a2);
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int robLinear(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        int prev1 = nums[0];
        int prev2 = 0;

        for (int i = 1; i < n; ++i) {
            int pick = nums[i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int rob(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        vector<int> case1(nums.begin(), nums.end() - 1); // exclude last
        vector<int> case2(nums.begin() + 1, nums.end()); // exclude first

        int a1 = robLinear(case1);
        int a2 = robLinear(case2);

        return max(a1, a2);
    }
};

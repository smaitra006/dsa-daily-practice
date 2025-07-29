#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * FROG JUMP - MINIMUM COST TO REACH THE LAST STAIR
 * =================================================================== */

 /**
  * @brief You are given an integer array `height[]` of size `n`,
  *        where height[i] represents the height of the i-th stair.
  *
  * A frog starts from stair 0 and wants to reach stair `n - 1`.
  * From stair i, it can jump to:
  *     - i + 1 (1-step)
  *     - i + 2 (2-step)
  *
  * The cost of a jump is:
  *     cost = abs(height[i] - height[j])
  *
  * GOAL: Reach stair `n-1` with minimum total cost.
  *
  * Recurrence Relation:
  * ---------------------
  * dp[i] = min(
  *      dp[i - 1] + abs(height[i] - height[i - 1]),
  *      dp[i - 2] + abs(height[i] - height[i - 2])
  * )
  *
  * TIME COMPLEXITY:
  * - Recursion: O(2^n)
  * - Memoization / Tabulation: O(n)
  *
  * SPACE COMPLEXITY:
  * - Memo/Tabulation: O(n), Space-Optimized: O(1)
  */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int frogRec(int i, vector<int>& height)
    {
        if (i == 0)
            return 0;

        int cost1 = frogRec(i - 1, height) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1) {
            cost2 = frogRec(i - 2, height) + abs(height[i] - height[i - 2]);
        }

        return min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogMemo(int i, vector<int>& height, vector<int>& dp)
    {
        if (i == 0)
            return 0;
        if (dp[i] != -1)
            return dp[i];

        int cost1 = frogMemo(i - 1, height, dp) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1) {
            cost2 = frogMemo(i - 2, height, dp) + abs(height[i] - height[i - 2]);
        }

        return dp[i] = min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogTab(vector<int>& height)
    {
        int n = height.size();
        vector<int> dp(n, 0);
        dp[0] = 0;

        for (int i = 1; i < n; ++i) {
            int cost1 = dp[i - 1] + abs(height[i] - height[i - 1]);
            int cost2 = (i > 1) ? dp[i - 2] + abs(height[i] - height[i - 2]) : INT_MAX;

            dp[i] = min(cost1, cost2);
        }

        return dp[n - 1];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int frogJump(vector<int>& height)
    {
        int n = height.size();
        int prev1 = 0; // dp[i - 1]
        int prev2 = 0; // dp[i - 2]

        for (int i = 1; i < n; ++i) {
            int cost1 = prev1 + abs(height[i] - height[i - 1]);
            int cost2 = (i > 1) ? prev2 + abs(height[i] - height[i - 2]) : INT_MAX;

            int curr = min(cost1, cost2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

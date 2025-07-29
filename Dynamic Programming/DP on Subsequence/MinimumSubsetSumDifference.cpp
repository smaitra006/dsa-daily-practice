#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * MINIMUM SUBSET SUM DIFFERENCE
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums` of positive integers, partition it into
 * two subsets such that the absolute difference between their sums
 * is minimized.
 *
 * Return the minimum possible difference.
 *
 * Key Observation:
 * ----------------
 * Total sum = S
 * Goal: Find subset with sum `s1` such that |S - 2*s1| is minimized.
 * That is, find the largest `s1 ≤ S/2` such that a subset with sum s1 exists.
 *
 * TIME COMPLEXITY: O(n * sum)
 * SPACE COMPLEXITY: O(n * sum) → O(sum) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int currSum, int total, vector<int>& nums)
    {
        if (i == nums.size()) {
            int sum2 = total - currSum;
            return abs(currSum - sum2);
        }

        int take = recur(i + 1, currSum + nums[i], total, nums);
        int notTake = recur(i + 1, currSum, total, nums);

        return min(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * total)
     * SPACE: O(n * total) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int currSum, int total, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (i == nums.size()) {
            int sum2 = total - currSum;
            return abs(currSum - sum2);
        }

        if (dp[i][currSum] != -1)
            return dp[i][currSum];

        int take = memo(i + 1, currSum + nums[i], total, nums, dp);
        int notTake = memo(i + 1, currSum, total, nums, dp);

        return dp[i][currSum] = min(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Subset Sum Table)
     * TIME: O(n * total)
     * SPACE: O(n * total)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums)
    {
        int n = nums.size();
        int total = accumulate(nums.begin(), nums.end(), 0);
        vector<vector<bool>> dp(n + 1, vector<bool>(total + 1, false));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= total; j++) {
                bool notTake = dp[i - 1][j];
                bool take = false;
                if (nums[i - 1] <= j)
                    take = dp[i - 1][j - nums[i - 1]];
                dp[i][j] = take || notTake;
            }
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (dp[n][s1]) {
                int s2 = total - s1; // as s1 + s2 = total
                minDiff = min(minDiff, abs(s2 - s1));
            }
        }

        return minDiff;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * total)
     * SPACE: O(total)
     * --------------------------------------------------------------- */
    int minimumDifference(vector<int>& nums)
    {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();

        vector<bool> prev(total + 1, false);
        prev[0] = true;

        for (int i = 1; i <= n; i++) {
            vector<bool> curr(total + 1, false);
            curr[0] = true;
            for (int j = 1; j <= total; j++) {
                bool notTake = prev[j];
                bool take = (j >= nums[i - 1]) ? prev[j - nums[i - 1]] : false;
                curr[j] = take || notTake;
            }
            prev = curr;
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (prev[s1]) {
                int s2 = total - s1;
                minDiff = min(minDiff, abs(s2 - s1));
            }
        }

        return minDiff;
    }
};

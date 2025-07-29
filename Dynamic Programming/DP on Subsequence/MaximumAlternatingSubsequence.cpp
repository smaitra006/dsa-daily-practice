#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * MAXIMUM ALTERNATING SUBSEQUENCE SUM (Leetcode 1911)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums`, find the maximum alternating sum of any
 * subsequence. Alternating sum is defined as:
 *   sum = a1 - a2 + a3 - a4 + ...
 *
 * We must choose a subsequence and apply alternating signs starting
 * with a '+'. Return the maximum possible value.
 *
 * State:
 * ------
 * dp[i][j] = max alternating sum starting from index i,
 * where:
 *    j = 1 → we expect a '+' at index i
 *    j = 0 → we expect a '-' at index i
 *
 * Recurrence:
 * -----------
 * dp[i][j] = max(
 *     +nums[i] (or -nums[i]) + dp[i+1][!j],   // take
 *     dp[i+1][j]                              // skip
 * )
 *
 * TIME COMPLEXITY: O(n)
 * SPACE COMPLEXITY: O(n) → O(1) if optimized
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    long long recur(int i, int sign, vector<int>& nums)
    {
        if (i == nums.size()) return 0;

        long long notTake = recur(i + 1, sign, nums);
        long long take = (sign ? nums[i] : -nums[i]) + recur(i + 1, !sign, nums);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 2) = O(n)
     * SPACE: O(n * 2) + O(n) stack
     * --------------------------------------------------------------- */
    long long memo(int i, int sign, vector<int>& nums, vector<vector<long long>>& dp)
    {
        if (i == nums.size()) return 0;
        if (dp[i][sign] != -1) return dp[i][sign];

        long long notTake = memo(i + 1, sign, nums, dp);
        long long take = (sign ? nums[i] : -nums[i]) + memo(i + 1, !sign, nums, dp);

        return dp[i][sign] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n)
     * SPACE: O(n * 2)
     * --------------------------------------------------------------- */
    long long tabulation(vector<int>& nums)
    {
        int n = nums.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int sign = 0; sign <= 1; sign++) {
                long long notTake = dp[i + 1][sign];
                long long take = (sign ? nums[i] : -nums[i]) + dp[i + 1][!sign];
                dp[i][sign] = max(take, notTake);
            }
        }

        return dp[0][1]; // start with '+'
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n)
     * SPACE: O(1)
     * --------------------------------------------------------------- */
    long long maxAlternatingSum(vector<int>& nums)
    {
        long long even = 0, odd = 0; // even → '+' turn, odd → '-' turn

        for (int i = nums.size() - 1; i >= 0; i--) {
            long long takeEven = nums[i] + odd;
            long long takeOdd = -nums[i] + even;

            even = max(takeEven, even);
            odd = max(takeOdd, odd);
        }

        return even; // final answer must start with '+'
    }
};

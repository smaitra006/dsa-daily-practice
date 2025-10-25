#include <bits/stdc++.h>
using namespace std;

/* =============================================================================
 *  MAX ALTERNATING SUBSEQUENCE SUM (Leetcode 1911)
 * =============================================================================
 *
 *  PROBLEM STATEMENT:
 *  -------------------
 *  You are given an integer array `nums`.
 *  You must choose a subsequence (not necessarily contiguous) such that
 *  its **alternating sum** is maximized.
 *
 *  The alternating sum of a subsequence is defined as:
 *      sum = a1 - a2 + a3 - a4 + a5 - ... (alternating signs)
 *
 *  FORMALLY:
 *      Given `nums = [x1, x2, x3, ...]`,
 *      we need to select elements such that we maximize:
 *          x[i1] - x[i2] + x[i3] - x[i4] + ...
 *      where i1 < i2 < i3 < i4 < ...
 *
 *  GOAL:
 *      Return the maximum alternating sum achievable.
 *
 *  RECURSION IDEA:
 *  ----------------
 *      At index `i`, we have two choices:
 *         1️  NOT TAKE → move to next index with same parity (even/odd position)
 *         2️  TAKE     → add/subtract current element and flip parity
 *
 *      If we consider:
 *          is_even = true  → next value adds (+nums[i])
 *          is_even = false → next value subtracts (-nums[i])
 *
 *      Recurrence:
 *          dp[i][is_even] = max(
 *               solve(i+1, is_even),                         // not take
 *               solve(i+1, !is_even) + (is_even ? +nums[i] : -nums[i])  // take
 *          )
 *
 *  TIME COMPLEXITY:
 *      - Recursion:   O(2^n)
 *      - Memoization: O(n * 2)
 *      - Tabulation:  O(n * 2)
 *      - Space-Optimized: O(1)
 *
 *  SPACE COMPLEXITY:
 *      - Recursion:   O(n)
 *      - Memoization: O(n * 2)
 *      - Tabulation:  O(n * 2)
 *      - Space-Optimized: O(1)
 * =============================================================================
 */

class Solution
{
public:
  /* ---------------------------------------------------------------
   * METHOD 1: Plain Recursion (Exponential)
   * --------------------------------------------------------------- */
  long long solveRec(vector<int> &nums, int i, bool is_even)
  {
    if (i >= nums.size())
      return 0;

    long long not_take = solveRec(nums, i + 1, is_even);

    long long val = (is_even ? nums[i] : -nums[i]);
    long long take = solveRec(nums, i + 1, !is_even) + val;

    return max(take, not_take);
  }

  /* ---------------------------------------------------------------
   * METHOD 2: Top-Down DP (Memoization)
   * TIME: O(n * 2), SPACE: O(n * 2)
   * --------------------------------------------------------------- */
  long long solveMemo(vector<int> &nums, int i, bool is_even, vector<vector<long long>> &dp)
  {
    if (i >= nums.size())
      return 0;

    if (dp[i][(int)is_even] != -1)
      return dp[i][(int)is_even];

    long long not_take = solveMemo(nums, i + 1, is_even, dp);

    long long val = (is_even ? nums[i] : -nums[i]);
    long long take = solveMemo(nums, i + 1, !is_even, dp) + val;

    return dp[i][(int)is_even] = max(take, not_take);
  }

  /* ---------------------------------------------------------------
   * METHOD 3: Bottom-Up DP (Tabulation)
   * TIME: O(n * 2), SPACE: O(n * 2)
   * --------------------------------------------------------------- */
  long long solveTab(vector<int> &nums)
  {
    int n = nums.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

    // Base case: dp[n][0] = dp[n][1] = 0 (beyond last index)
    for (int i = n - 1; i >= 0; --i)
    {
      for (int is_even = 0; is_even <= 1; ++is_even)
      {
        long long not_take = dp[i + 1][is_even];
        long long val = (is_even ? nums[i] : -nums[i]);
        long long take = dp[i + 1][!is_even] + val;

        dp[i][is_even] = max(take, not_take);
      }
    }

    return dp[0][1]; // start with even position (addition)
  }

  /* ---------------------------------------------------------------
   * METHOD 4: Space-Optimized DP (O(1) space)
   * TIME: O(n * 2), SPACE: O(1)
   * --------------------------------------------------------------- */
  long long maxAlternatingSum(vector<int> &nums)
  {
    int n = nums.size();
    long long next_even = 0, next_odd = 0;

    // Reverse iteration
    for (int i = n - 1; i >= 0; --i)
    {
      long long curr_even = max(next_even, next_odd + nums[i]); // take or skip
      long long curr_odd = max(next_odd, next_even - nums[i]);  // take or skip

      next_even = curr_even;
      next_odd = curr_odd;
    }

    return next_even; // even position first (add)
  }
};

/* =============================================================================
 * Example Usage:
 * =============================================================================
 *
 * int main() {
 *     Solution sol;
 *     vector<int> nums = {4, 2, 5, 3};
 *
 *     // METHOD 1: Recursion
 *     cout << sol.solveRec(nums, 0, true) << endl;
 *
 *     // METHOD 2: Memoization
 *     vector<vector<long long>> dp(nums.size(), vector<long long>(2, -1));
 *     cout << sol.solveMemo(nums, 0, true, dp) << endl;
 *
 *     // METHOD 3: Tabulation
 *     cout << sol.solveTab(nums) << endl;
 *
 *     // METHOD 4: Space Optimized
 *     cout << sol.maxAlternatingSum(nums) << endl;
 * }
 *
 * Output:
 *     7
 * =============================================================================
 */

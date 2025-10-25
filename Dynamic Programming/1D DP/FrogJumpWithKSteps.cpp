#include <bits/stdc++.h>
using namespace std;

/* =============================================================================
 *  FROG JUMP WITH K DISTANCE - MINIMUM ENERGY TO REACH LAST STAIR
 * =============================================================================
 *
 *  PROBLEM STATEMENT:
 *  -------------------
 *  Given an integer array `height[]` of size `n`, where height[i] denotes
 *  the height of the i-th stair, and an integer `k` representing the maximum
 *  number of stairs the frog can jump at once.
 *
 *  The frog starts at stair 0 and wants to reach stair (n - 1).
 *  From stair i, it can jump to any stair j such that:
 *        i < j ≤ i + k
 *
 *  The cost of jumping from i → j is:
 *        cost = abs(height[i] - height[j])
 *
 *  GOAL: Reach stair (n - 1) with the **minimum total energy cost**.
 *
 *  Recurrence Relation:
 *  ---------------------
 *      dp[i] = min( dp[i - j] + abs(height[i] - height[i - j]) )
 *               for all j ∈ [1, k] and i - j ≥ 0
 *
 *  TIME COMPLEXITY:
 *      Recursion:     O(k^n)      (exponential)
 *      Memoization:   O(n * k)
 *      Tabulation:    O(n * k)
 *      Space-Opt:     O(k) or O(1) depending on implementation
 *
 *  SPACE COMPLEXITY:
 *      Recursion:     O(n) stack
 *      Memoization:   O(n)
 *      Tabulation:    O(n)
 *      Space-Opt:     O(1)
 * =============================================================================
 */

class Solution
{
public:
  /* ---------------------------------------------------------------
   * METHOD 1: Plain Recursion (Exponential Time)
   * --------------------------------------------------------------- */
  int frogRec(int i, vector<int> &height, int k)
  {
    if (i == 0)
      return 0;

    int minCost = INT_MAX;

    // Try all possible jumps from i-k to i-1
    for (int j = 1; j <= k; ++j)
    {
      if (i - j >= 0)
      {
        int cost = frogRec(i - j, height, k) + abs(height[i] - height[i - j]);
        minCost = min(minCost, cost);
      }
    }

    return minCost;
  }

  /* ---------------------------------------------------------------
   * METHOD 2: Top-Down DP (Memoization)
   * TIME: O(n * k), SPACE: O(n)
   * --------------------------------------------------------------- */
  int frogMemo(int i, vector<int> &height, int k, vector<int> &dp)
  {
    if (i == 0)
      return 0;
    if (dp[i] != -1)
      return dp[i];

    int minCost = INT_MAX;

    for (int j = 1; j <= k; ++j)
    {
      if (i - j >= 0)
      {
        int cost = frogMemo(i - j, height, k, dp) + abs(height[i] - height[i - j]);
        minCost = min(minCost, cost);
      }
    }

    return dp[i] = minCost;
  }

  /* ---------------------------------------------------------------
   * METHOD 3: Bottom-Up DP (Tabulation)
   * TIME: O(n * k), SPACE: O(n)
   * --------------------------------------------------------------- */
  int frogTab(vector<int> &height, int k)
  {
    int n = height.size();
    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; ++i)
    {
      int minCost = INT_MAX;

      for (int j = 1; j <= k; ++j)
      {
        if (i - j >= 0)
        {
          int cost = dp[i - j] + abs(height[i] - height[i - j]);
          minCost = min(minCost, cost);
        }
      }

      dp[i] = minCost;
    }

    return dp[n - 1];
  }

  /* ---------------------------------------------------------------
   * METHOD 4: Space-Optimized DP (O(k) Space)
   * TIME: O(n * k), SPACE: O(k)
   * --------------------------------------------------------------- */
  int frogJump(vector<int> &height, int k)
  {
    int n = height.size();
    deque<int> dp(k + 1, 0); // Sliding window for last k computations
    dp[0] = 0;

    vector<int> minCost(n, 0);
    minCost[0] = 0;

    for (int i = 1; i < n; ++i)
    {
      int currMin = INT_MAX;

      for (int j = 1; j <= k && i - j >= 0; ++j)
      {
        currMin = min(currMin, minCost[i - j] + abs(height[i] - height[i - j]));
      }

      minCost[i] = currMin;
    }

    return minCost[n - 1];
  }
};

/* =============================================================================
 * Example Usage:
 * =============================================================================
 *
 * int main() {
 *     Solution sol;
 *     vector<int> height = {30, 10, 60, 10, 60, 50};
 *     int k = 2;
 *
 *     // METHOD 1 (Recursion)
 *     cout << sol.frogRec(height.size() - 1, height, k) << endl;
 *
 *     // METHOD 2 (Memoization)
 *     vector<int> dp(height.size(), -1);
 *     cout << sol.frogMemo(height.size() - 1, height, k, dp) << endl;
 *
 *     // METHOD 3 (Tabulation)
 *     cout << sol.frogTab(height, k) << endl;
 *
 *     // METHOD 4 (Space Optimized)
 *     cout << sol.frogJump(height, k) << endl;
 * }
 *
 * Output:
 *     40
 * =============================================================================
 */

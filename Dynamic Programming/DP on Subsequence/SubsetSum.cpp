#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * SUBSET SUM PROBLEM (DP - PICK / NOT PICK PATTERN)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `arr[]` of `n` positive integers and a value `sum`,
 * determine if there is a subset of the given set with a sum equal to `sum`.
 *
 * Recurrence:
 * -----------
 * dp[i][target] = dp[i-1][target] || dp[i-1][target - arr[i]]
 *
 * TIME COMPLEXITY: O(n * sum)
 * SPACE COMPLEXITY: O(n * sum) or O(sum) if space-optimized
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * TIME: O(2^n)
     * SPACE: O(n) stack space
     * --------------------------------------------------------------- */
    bool recur(int i, int target, vector<int>& arr)
    {
        if (target == 0) {
            return true; // We got the sum
        }
        if (i == 0) {
            return (arr[0] == target); // return if the last element is equal to the current required target
        }

        bool not_take = recur(i - 1, target, arr); // Not take case
        bool take = false;
        if (arr[i] <= target) {                                              // we will take only if its smaller than the current required target
            take = recur(i - 1, target - arr[i], arr); // taking reduces the target
        }

        return take || not_take;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * sum)
     * SPACE: O(n * sum) + O(n) stack space
     * --------------------------------------------------------------- */
    bool memo(int i, int target, vector<int>& arr, vector<vector<int>>& dp)
    {
        if (target == 0)
            return true;
        if (i == 0)
            return (arr[0] == target);

        if (dp[i][target] != -1)
            return dp[i][target];

        bool notPick = memo(i - 1, target, arr, dp);
        bool pick = false;
        if (target >= arr[i])
            pick = memo(i - 1, target - arr[i], arr, dp);

        return dp[i][target] = pick || notPick;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * sum)
     * SPACE: O(n * sum)
     * --------------------------------------------------------------- */
    bool tabulation(vector<int>& arr, int sum)
    {
        int n = arr.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

        // Already initialised all dp[0][*] false ,without any element any sum is not possible(expect dp[0][0])

        // dp[*][0] is always true. Its always possible to form target 0
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; ++i) {
            for (int target = 1; target <= sum; ++target) {
                bool notPick = dp[i - 1][target];
                bool pick = false;
                if (target >= arr[i - 1])
                    pick = dp[i - 1][target - arr[i - 1]];
                dp[i][target] = pick || notPick;
            }
        }

        return dp[n][sum];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (1D DP)
     * TIME: O(n * sum)
     * SPACE: O(sum)
     * --------------------------------------------------------------- */
    bool isSubsetSum(vector<int>& arr, int sum)
    {
        int n = arr.size();
        vector<bool> prev(sum + 1, false), curr(sum + 1, false);

        prev[0] = curr[0] = true; // target 0 is always possible

        for (int i = 1; i <= n; ++i) {
            for (int target = 1; target <= sum; ++target) {
                bool notPick = prev[target];
                bool pick = false;
                if (target >= arr[i - 1])
                    pick = prev[target - arr[i - 1]];
                curr[target] = pick || notPick;
            }
            prev = curr;
        }

        return prev[sum];
    }
};

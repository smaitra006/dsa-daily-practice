#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * DYNAMIC PROGRAMMING: CORE TEMPLATE + NOTES
 * =================================================================== */

/**
 * @brief Dynamic Programming (DP) is an optimization technique
 *        used to solve problems with overlapping subproblems
 *        and optimal substructure.
 *
 * TYPES:
 * -------
 * 1. Memoization (Top-Down): Use recursion + cache results.
 * 2. Tabulation (Bottom-Up): Solve smaller problems first, build up.
 *
 * IDENTIFYING DP:
 * ---------------
 *  Overlapping Subproblems
 *  Optimal Substructure
 *  Reuse of results = avoid recomputation
 *
 * TIME COMPLEXITY: Depends on number of states × time per state
 * SPACE COMPLEXITY: Depends on cache/DP array size
 *
 * Common DP Dimensions:
 * ---------------------
 * - 1D DP → dp[i]
 * - 2D DP → dp[i][j]
 * - 3D DP → dp[i][j][k] (used in intervals, substrings, games)
 */

class Solution
{
public:
    // Example Problem: Fibonacci Number using all 3 approaches

    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time, for explanation only)
     * --------------------------------------------------------------- */
    int fibRec(int n)
    {
        if (n <= 1)
            return n;
        return fibRec(n - 1) + fibRec(n - 2); // Overlapping subproblems!
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(N), SPACE: O(N) for memo
     * --------------------------------------------------------------- */
    int fibMemo(int n, vector<int> &memo)
    {
        if (n <= 1)
            return n;
        if (memo[n] != -1)
            return memo[n]; // Use stored result
        return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(N), SPACE: O(N)
     * --------------------------------------------------------------- */
    int fibTab(int n)
    {
        if (n <= 1)
            return n;

        vector<int> dp(n + 1, 0); // dp[i] stores fib(i)
        dp[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2]; // Build from bottom
        }

        return dp[n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (Bottom-Up with O(1) space)
     * --------------------------------------------------------------- */
    int fibOpt(int n)
    {
        if (n <= 1)
            return n;

        int prev2 = 0, prev1 = 1;

        for (int i = 2; i <= n; ++i)
        {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

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
    int frogRec(int i, vector<int> &height)
    {
        if (i == 0)
            return 0;

        int cost1 = frogRec(i - 1, height) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1)
        {
            cost2 = frogRec(i - 2, height) + abs(height[i] - height[i - 2]);
        }

        return min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogMemo(int i, vector<int> &height, vector<int> &dp)
    {
        if (i == 0)
            return 0;
        if (dp[i] != -1)
            return dp[i];

        int cost1 = frogMemo(i - 1, height, dp) + abs(height[i] - height[i - 1]);

        int cost2 = INT_MAX;
        if (i > 1)
        {
            cost2 = frogMemo(i - 2, height, dp) + abs(height[i] - height[i - 2]);
        }

        return dp[i] = min(cost1, cost2);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int frogTab(vector<int> &height)
    {
        int n = height.size();
        vector<int> dp(n, 0);
        dp[0] = 0;

        for (int i = 1; i < n; ++i)
        {
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
    int frogJump(vector<int> &height)
    {
        int n = height.size();
        int prev1 = 0; // dp[i - 1]
        int prev2 = 0; // dp[i - 2]

        for (int i = 1; i < n; ++i)
        {
            int cost1 = prev1 + abs(height[i] - height[i - 1]);
            int cost2 = (i > 1) ? prev2 + abs(height[i] - height[i - 2]) : INT_MAX;

            int curr = min(cost1, cost2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

// 2D DP
/* ===================================================================
 * NINJA'S TRAINING (DP - NOT DOING SAME ACTIVITY ON TWO CONSECUTIVE DAYS)
 * =================================================================== */

/**
 * @brief Given a points matrix of size n x 3 (n days, 3 activities),
 *        return the maximum points the ninja can accumulate over n days
 *        such that he does NOT repeat the same activity on consecutive days.
 *
 * Recurrence:
 * -----------
 * dp[day][last] = max(
 *     points[day][i] + dp[day-1][i] for all i != last
 * )
 *
 * TIME COMPLEXITY: O(n * 4 * 3) = O(n)
 * SPACE COMPLEXITY: O(n * 4) or O(1) if optimized
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int recur(int day, int last, vector<vector<int>> &points)
    {
        if (day == 0)
        {
            int maxPoint = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (i != last)
                    maxPoint = max(maxPoint, points[0][i]);
            }
            return maxPoint;
        }

        int maxPoint = 0;
        for (int i = 0; i < 3; ++i)
        {
            if (i != last)
            {
                int point = points[day][i] + recur(day - 1, i, points);
                maxPoint = max(maxPoint, point);
            }
        }
        return maxPoint;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 4), SPACE: O(n * 4)
     * --------------------------------------------------------------- */
    int memo(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
    {
        if (day == 0)
        {
            int maxPoint = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (i != last)
                    maxPoint = max(maxPoint, points[0][i]);
            }
            return dp[0][last] = maxPoint;
        }

        if (dp[day][last] != -1)
            return dp[day][last];

        int maxPoint = 0;
        for (int i = 0; i < 3; ++i)
        {
            if (i != last)
            {
                int point = points[day][i] + memo(day - 1, i, points, dp);
                maxPoint = max(maxPoint, point);
            }
        }

        return dp[day][last] = maxPoint;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 4), SPACE: O(n * 4)
     * --------------------------------------------------------------- */
    int tabulation(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base case for day 0
        dp[0][0] = max(points[0][1], points[0][2]);                 // last = 0
        dp[0][1] = max(points[0][0], points[0][2]);                 // last = 1
        dp[0][2] = max(points[0][0], points[0][1]);                 // last = 2
        dp[0][3] = max({points[0][0], points[0][1], points[0][2]}); // last = 3 (no restriction)

        for (int day = 1; day < n; ++day)
        {
            for (int last = 0; last < 4; ++last)
            {
                dp[day][last] = 0;
                for (int i = 0; i < 3; ++i)
                {
                    if (i != last)
                    {
                        int point = points[day][i] + dp[day - 1][i];
                        dp[day][last] = max(dp[day][last], point);
                    }
                }
            }
        }

        return dp[n - 1][3];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (O(1) space)
     * TIME: O(n * 4), SPACE: O(4)
     * --------------------------------------------------------------- */
    int ninjaTraining(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<int> prev(4, 0);

        // Base case
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max({points[0][0], points[0][1], points[0][2]});

        for (int day = 1; day < n; ++day)
        {
            vector<int> temp(4, 0);

            for (int last = 0; last < 4; ++last)
            {
                temp[last] = 0;
                for (int i = 0; i < 3; ++i)
                {
                    if (i != last)
                    {
                        int point = points[day][i] + prev[i];
                        temp[last] = max(temp[last], point);
                    }
                }
            }

            prev = temp;
        }

        return prev[3];
    }
};

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
    bool recur(int i, int target, vector<int> &arr)
    {
        if (target == 0)
            return true;
        if (i == 0)
            return (arr[0] == target);

        bool notPick = recur(i - 1, target, arr);
        bool pick = false;
        if (target >= arr[i])
            pick = recur(i - 1, target - arr[i], arr);

        return pick || notPick;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * sum)
     * SPACE: O(n * sum) + O(n) stack space
     * --------------------------------------------------------------- */
    bool memo(int i, int target, vector<int> &arr, vector<vector<int>> &dp)
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
    bool tabulation(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));

        // Base Case: sum == 0 is always possible
        for (int i = 0; i < n; ++i)
            dp[i][0] = true;

        // Base Case: only arr[0] can be picked
        if (arr[0] <= sum)
            dp[0][arr[0]] = true;

        for (int i = 1; i < n; ++i)
        {
            for (int target = 1; target <= sum; ++target)
            {
                bool notPick = dp[i - 1][target];
                bool pick = false;
                if (target >= arr[i])
                    pick = dp[i - 1][target - arr[i]];
                dp[i][target] = pick || notPick;
            }
        }

        return dp[n - 1][sum];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (1D DP)
     * TIME: O(n * sum)
     * SPACE: O(sum)
     * --------------------------------------------------------------- */
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<bool> prev(sum + 1, false), curr(sum + 1, false);

        prev[0] = curr[0] = true;
        if (arr[0] <= sum)
            prev[arr[0]] = true;

        for (int i = 1; i < n; ++i)
        {
            for (int target = 1; target <= sum; ++target)
            {
                bool notPick = prev[target];
                bool pick = false;
                if (target >= arr[i])
                    pick = prev[target - arr[i]];
                curr[target] = pick || notPick;
            }
            prev = curr;
        }

        return prev[sum];
    }
};

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
    int recur(int i, int target, vector<int> &nums)
    {
        if (i == 0)
        {
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
    int memo(int i, int target, vector<int> &nums, vector<vector<int>> &dp)
    {
        if (i == 0)
        {
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
    int tabulation(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));

        // base cases
        dp[0][0] = (nums[0] == 0) ? 2 : 1; // if nums[0] == 0: {} and {0}, else only {}
        if (nums[0] != 0 && nums[0] <= k)
            dp[0][nums[0]] = 1;

        for (int i = 1; i < n; ++i)
        {
            for (int target = 0; target <= k; ++target)
            {
                int notPick = dp[i - 1][target];
                int pick = 0;
                if (nums[i] <= target)
                    pick = dp[i - 1][target - nums[i]];

                dp[i][target] = pick + notPick;
            }
        }

        return dp[n - 1][k];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (O(k) Space)
     * TIME: O(n * k), SPACE: O(k)
     * --------------------------------------------------------------- */
    int countSubsets(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prev(k + 1, 0), curr(k + 1, 0);

        prev[0] = (nums[0] == 0) ? 2 : 1;
        if (nums[0] != 0 && nums[0] <= k)
            prev[nums[0]] = 1;

        for (int i = 1; i < n; ++i)
        {
            curr[0] = (nums[i] == 0) ? 2 * prev[0] : prev[0]; // careful for zeros
            for (int target = 1; target <= k; ++target)
            {
                int notPick = prev[target];
                int pick = 0;
                if (nums[i] <= target)
                    pick = prev[target - nums[i]];
                curr[target] = pick + notPick;
            }
            prev = curr;
        }

        return prev[k];
    }
};

/* ================================================================
 * PARTITIONS WITH GIVEN DIFFERENCE
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums` and a difference `d`, count the number
 * of ways to partition the array into two subsets such that
 * the absolute difference of their sums is exactly `d`.
 *
 * Observation:
 * ------------
 * Let total_sum = sum(nums)
 * Let the two subset sums be s1 and s2 such that:
 *   s1 - s2 = d  and  s1 + s2 = total_sum
 *
 * Solving:
 * --------
 *   s1 = (total_sum + d) / 2
 *
 * So, reduce to: Count number of subsets with sum = s1
 *
 * TIME COMPLEXITY: O(n * k)
 * SPACE COMPLEXITY: O(n * k) → O(k) (if space optimized)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int target, vector<int>& nums) {
        if (i == 0) {
            if (target == 0 && nums[0] == 0) return 2; // pick or not pick 0
            if (target == 0 || target == nums[0]) return 1;
            return 0;
        }

        int notTake = recur(i - 1, target, nums);
        int take = 0;
        if (target >= nums[i]) take = recur(i - 1, target - nums[i], nums);

        return take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k)
     * SPACE: O(n * k) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int target, vector<int>& nums, vector<vector<int>>& dp) {
        if (i == 0) {
            if (target == 0 && nums[0] == 0) return 2;
            if (target == 0 || target == nums[0]) return 1;
            return 0;
        }

        if (dp[i][target] != -1) return dp[i][target];

        int notTake = memo(i - 1, target, nums, dp);
        int take = 0;
        if (target >= nums[i]) take = memo(i - 1, target - nums[i], nums, dp);

        return dp[i][target] = take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k)
     * SPACE: O(n * k)
     * --------------------------------------------------------------- */
    int tabulation(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        // base case
        if (nums[0] == 0) dp[0][0] = 2; // pick or not pick
        else dp[0][0] = 1;

        if (nums[0] != 0 && nums[0] <= target) dp[0][nums[0]] = 1;

        for (int i = 1; i < n; i++) {
            for (int t = 0; t <= target; t++) {
                int notTake = dp[i - 1][t];
                int take = 0;
                if (t >= nums[i]) take = dp[i - 1][t - nums[i]];
                dp[i][t] = take + notTake;
            }
        }

        return dp[n - 1][target];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * k)
     * SPACE: O(k)
     * --------------------------------------------------------------- */
    int countPartitions(int n, int d, vector<int>& nums) {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if ((total_sum + d) % 2 != 0 || total_sum < d) return 0;

        int target = (total_sum + d) / 2;

        vector<int> prev(target + 1, 0);

        // base case
        if (nums[0] == 0) prev[0] = 2;
        else prev[0] = 1;

        if (nums[0] != 0 && nums[0] <= target) prev[nums[0]] = 1;

        for (int i = 1; i < n; i++) {
            vector<int> curr(target + 1, 0);
            for (int t = 0; t <= target; t++) {
                int notTake = prev[t];
                int take = 0;
                if (t >= nums[i]) take = prev[t - nums[i]];
                curr[t] = take + notTake;
            }
            prev = curr;
        }

        return prev[target];
    }
};

/* ================================================================
 * PARTITIONS WITH GIVEN DIFFERENCE
 * ================================================================
 *
 * Problem:
 * --------
 * Given an array `nums` and a difference `d`, count the number
 * of ways to partition the array into two subsets such that
 * the absolute difference of their sums is exactly `d`.
 *
 * Observation:
 * ------------
 * Let total_sum = sum(nums)
 * Let the two subset sums be s1 and s2 such that:
 *   s1 - s2 = d  and  s1 + s2 = total_sum
 *
 * Solving:
 * --------
 *   s1 = (total_sum + d) / 2
 *
 * So, reduce to: Count number of subsets with sum = s1
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
    int recur(int i, int target, vector<int> &nums)
    {
        if (i == 0)
        {
            if (target == 0 && nums[0] == 0)
                return 2; // pick or not pick 0
            if (target == 0 || target == nums[0])
                return 1;
            return 0;
        }

        int notTake = recur(i - 1, target, nums);
        int take = 0;
        if (target >= nums[i])
            take = recur(i - 1, target - nums[i], nums);

        return take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * k)
     * SPACE: O(n * k) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int target, vector<int> &nums, vector<vector<int>> &dp)
    {
        if (i == 0)
        {
            if (target == 0 && nums[0] == 0)
                return 2;
            if (target == 0 || target == nums[0])
                return 1;
            return 0;
        }

        if (dp[i][target] != -1)
            return dp[i][target];

        int notTake = memo(i - 1, target, nums, dp);
        int take = 0;
        if (target >= nums[i])
            take = memo(i - 1, target - nums[i], nums, dp);

        return dp[i][target] = take + notTake;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * k)
     * SPACE: O(n * k)
     * --------------------------------------------------------------- */
    int tabulation(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        // base case
        if (nums[0] == 0)
            dp[0][0] = 2; // pick or not pick
        else
            dp[0][0] = 1;

        if (nums[0] != 0 && nums[0] <= target)
            dp[0][nums[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int t = 0; t <= target; t++)
            {
                int notTake = dp[i - 1][t];
                int take = 0;
                if (t >= nums[i])
                    take = dp[i - 1][t - nums[i]];
                dp[i][t] = take + notTake;
            }
        }

        return dp[n - 1][target];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * k)
     * SPACE: O(k)
     * --------------------------------------------------------------- */
    int countPartitions(int n, int d, vector<int> &nums)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if ((total_sum + d) % 2 != 0 || total_sum < d)
            return 0;

        int target = (total_sum + d) / 2;

        vector<int> prev(target + 1, 0);

        // base case
        if (nums[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        if (nums[0] != 0 && nums[0] <= target)
            prev[nums[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(target + 1, 0);
            for (int t = 0; t <= target; t++)
            {
                int notTake = prev[t];
                int take = 0;
                if (t >= nums[i])
                    take = prev[t - nums[i]];
                curr[t] = take + notTake;
            }
            prev = curr;
        }

        return prev[target];
    }
};

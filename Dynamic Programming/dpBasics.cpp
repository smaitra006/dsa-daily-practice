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
        {
            return true; // We got the sum
        }
        if (i == 0)
        {
            return (arr[0] == target); // return if the last element is equal to the current required target
        }

        bool not_take = recur(i - 1, target, arr); // Not take case
        bool take = false;
        if (arr[i] <= target)
        {                                              // we will take only if its smaller than the current required target
            take = recur(i - 1, target - arr[i], arr); // taking reduces the target
        }

        return take || not_take;
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
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

        // Already initialised all dp[0][*] false ,without any element any sum is not possible(expect dp[0][0])

        // dp[*][0] is always true. Its always possible to form target 0
        for(int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int target = 1; target <= sum; ++target)
            {
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
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<bool> prev(sum + 1, false), curr(sum + 1, false);

        prev[0] = curr[0] = true; // target 0 is always possible

        for (int i = 1; i <= n; ++i)
        {
            for (int target = 1; target <= sum; ++target)
            {
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
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // Base Case: 1 way to form sum 0 with 0 elements(empty subset)
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int target = 0; target <= k; target++)
            {
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
    int countSubsets(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prev(k + 1, 0), curr(k + 1, 0);

        prev[0] = (nums[0] == 0) ? 2 : 1;

        for (int i = 1; i <= n; ++i)
        {
            curr[0] = (nums[i - 1] == 0) ? 2 * prev[0] : prev[0]; // careful for zeros -> 2 * prev[0] because if nums[i] == 0 , then we can have all subsets of prev[0] and also all those with a zero in it
            for (int target = 1; target <= k; ++target)
            {
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
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        // base case
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int t = 0; t <= target; t++)
            {
                int notTake = dp[i - 1][t];
                int take = 0;
                if (t >= nums[i - 1])
                    take = dp[i - 1][t - nums[i - 1]];
                dp[i][t] = take + notTake;
            }
        }

        return dp[n][target];
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
        prev[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            vector<int> curr(target + 1, 0);
            for (int t = 0; t <= target; t++)
            {
                int notTake = prev[t];
                int take = 0;
                if (t >= nums[i - 1])
                    take = prev[t - nums[i - 1]];
                curr[t] = take + notTake;
            }
            prev = curr;
        }

        return prev[target];
    }
};

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
    int recur(int i, int currSum, int total, vector<int> &nums)
    {
        if (i == nums.size())
        {
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
    int memo(int i, int currSum, int total, vector<int> &nums, vector<vector<int>> &dp)
    {
        if (i == nums.size())
        {
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
    int tabulation(vector<int> &nums)
    {
        int n = nums.size();
        int total = accumulate(nums.begin(), nums.end(), 0);
        vector<vector<bool>> dp(n + 1, vector<bool>(total + 1, false));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= total; j++)
            {
                bool notTake = dp[i - 1][j];
                bool take = false;
                if (nums[i - 1] <= j)
                    take = dp[i - 1][j - nums[i - 1]];
                dp[i][j] = take || notTake;
            }
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++)
        {
            if (dp[n][s1])
            {
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
    int minimumDifference(vector<int> &nums)
    {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();

        vector<bool> prev(total + 1, false);
        prev[0] = true;

        for (int i = 1; i <= n; i++)
        {
            vector<bool> curr(total + 1, false);
            curr[0] = true;
            for (int j = 1; j <= total; j++)
            {
                bool notTake = prev[j];
                bool take = (j >= nums[i - 1]) ? prev[j - nums[i - 1]] : false;
                curr[j] = take || notTake;
            }
            prev = curr;
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++)
        {
            if (prev[s1])
            {
                int s2 = total - s1;
                minDiff = min(minDiff, abs(s2 - s1));
            }
        }

        return minDiff;
    }
};

/* ================================================================
 * 0/1 KNAPSACK
 * ================================================================
 *
 * Problem:
 * --------
 * Given weights[] and values[] of N items, and a capacity W,
 * determine the maximum total value that can be obtained by
 * selecting items such that their total weight does not exceed W.
 *
 * Each item can be picked at most once (0/1 constraint).
 *
 * Recurrence:
 * -----------
 * dp[i][w] = max(dp[i-1][w], val[i] + dp[i-1][w - wt[i]])
 *
 * TIME COMPLEXITY: O(n * W)
 * SPACE COMPLEXITY: O(n * W) → O(W) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int W, vector<int> &wt, vector<int> &val)
    {
        if (i == 0)
        {
            return (wt[0] <= W) ? val[0] : 0; // If we can fit the item then we take its val otherwise 0
        }

        int notTake = recur(i - 1, W, wt, val);
        int take = 0;
        if (wt[i] <= W)
            take = val[i] + recur(i - 1, W - wt[i], wt, val);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * W)
     * SPACE: O(n * W) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp)
    {
        if (i == 0)
        {
            return (wt[0] <= W) ? val[0] : 0;
        }

        if (dp[i][W] != -1)
            return dp[i][W];

        int notTake = memo(i - 1, W, wt, val, dp);
        int take = 0;
        if (wt[i] <= W)
            take = val[i] + memo(i - 1, W - wt[i], wt, val, dp);

        return dp[i][W] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * W)
     * SPACE: O(n * W)
     * --------------------------------------------------------------- */
    int tabulation(int W, vector<int> &wt, vector<int> &val)
    {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        // Base case already initialized to 0 (dp[0][*] = 0 and dp[*][0] = 0)

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= W; j++)
            {

                int not_take = dp[i - 1][j]; // Not take case. If we can't take it then at its place we store the value we had while using (i-1)th element and same j capacity

                int take = 0;
                if (wt[i - 1] <= j)
                {
                    take = val[i - 1] + dp[i - 1][j - wt[i - 1]]; // Take case. We take the current one, so capacity reduces to j - wt[i - 1]
                }

                dp[i][j] = max(take, not_take);
            }
        }

        return dp[n][W];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * W)
     * SPACE: O(W)
     * --------------------------------------------------------------- */
    int knapsack(int W, vector<int> &wt, vector<int> &val)
    {
        int n = wt.size();
        vector<int> prev(W + 1, 0); // We only need the previous row

        for (int i = 1; i <= n; i++)
        {
            vector<int> curr(W + 1, 0);
            for (int j = 1; j <= W; j++)
            {
                int not_take = prev[j];
                int take = 0;
                if (wt[i - 1] <= j)
                {
                    take = val[i - 1] + prev[j - wt[i - 1]];
                }
                curr[j] = max(take, not_take);
            }
            prev = curr;
        }

        return prev[W];
    }
};

/* ================================================================
 * ROD CUTTING PROBLEM (Unbounded Knapsack Variant)
 * ================================================================
 *
 * Problem:
 * --------
 * Given a rod of length `n` and an array `prices` where prices[i]
 * denotes the price of a rod of length `i+1`, find the maximum total
 * value you can obtain by cutting the rod into pieces.
 *
 * You can make multiple cuts and reuse the same length multiple times.
 *
 * Observation:
 * ------------
 * This is a classic Unbounded Knapsack problem where:
 * - 'n' is the total capacity (rod length)
 * - You can pick the same piece (length) multiple times
 *
 * Recurrence:
 * -----------
 * dp[i][len] = max(dp[i-1][len], price[i] + dp[i][len - length[i]])
 *
 * TIME COMPLEXITY: O(n * n)
 * SPACE COMPLEXITY: O(n * n) → O(n) (if space optimized)
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int len, vector<int> &prices)
    {
        if (i == 0)
            return len * prices[0]; // only length 1 rod available

        int notCut = recur(i - 1, len, prices);
        int cut = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= len)
            cut = prices[i] + recur(i, len - rodLength, prices);

        return max(cut, notCut);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * n)
     * SPACE: O(n * n) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int len, vector<int> &prices, vector<vector<int>> &dp)
    {
        if (i == 0)
            return len * prices[0];

        if (dp[i][len] != -1)
            return dp[i][len];

        int notCut = memo(i - 1, len, prices, dp);
        int cut = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= len)
            cut = prices[i] + memo(i, len - rodLength, prices, dp);

        return dp[i][len] = max(cut, notCut);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * n)
     * SPACE: O(n * n)
     * --------------------------------------------------------------- */
    int tabulation(vector<int> &prices, int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int len = 0; len <= n; len++) // We can make anything with rod length 1
            dp[0][len] = len * prices[0];

        for (int i = 1; i < n; i++)
        {
            for (int len = 0; len <= n; len++)
            {
                int notCut = dp[i - 1][len];
                int cut = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= len)
                    cut = prices[i] + dp[i][len - rodLength];
                dp[i][len] = max(cut, notCut);
            }
        }

        return dp[n][n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized (1D DP)
     * TIME: O(n * n)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int cutRod(vector<int> &prices, int n)
    {
        vector<int> dp(n + 1, 0);

        for (int len = 0; len <= n; len++)
            dp[len] = len * prices[0];

        for (int i = 1; i < n; i++)
        {
            for (int len = 0; len <= n; len++)
            {
                int notCut = dp[len];
                int cut = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= len)
                    cut = prices[i] + dp[len - rodLength];
                dp[len] = max(cut, notCut);
            }
        }

        return dp[n];
    }
};

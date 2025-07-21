#include<bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 70: CLIMBING STAIRS
 * =================================================================== */

/**
 * @brief You are climbing a staircase. It takes `n` steps to reach the top.
 *        Each time you can either climb 1 or 2 steps.
 *        In how many distinct ways can you climb to the top?
 *
 * This is a classic Fibonacci-style Dynamic Programming problem.
 *
 * Recurrence Relation:
 * --------------------
 * ways(n) = ways(n - 1) + ways(n - 2)
 *
 * WHY?
 * - To reach step `n`, you must come from step `n-1` (1 step jump) OR
 *   from `n-2` (2 step jump).
 *
 * TIME COMPLEXITY:
 * - Recursion: O(2^n)
 * - Memoization: O(n)
 * - Tabulation: O(n)
 * - Space-Optimized: O(n) time, O(1) space
 *
 * SPACE COMPLEXITY:
 * - O(n) for memo/tabulation, O(1) for optimized
 */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int climbRec(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        return climbRec(n - 1) + climbRec(n - 2);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Top-Down DP (Memoization)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int climbMemo(int n, vector<int> &memo)
    {
        if (n == 0 || n == 1)
            return 1;
        if (memo[n] != -1)
            return memo[n];
        return memo[n] = climbMemo(n - 1, memo) + climbMemo(n - 2, memo);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Bottom-Up DP (Tabulation)
     * TIME: O(n), SPACE: O(n)
     * --------------------------------------------------------------- */
    int climbTab(int n)
    {
        if (n == 0 || n == 1)
            return 1;

        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space-Optimized DP (O(1) space)
     * TIME: O(n), SPACE: O(1)
     * --------------------------------------------------------------- */
    int climbStairs(int n)
    {
        if (n == 0 || n == 1)
            return 1;

        int prev1 = 1, prev2 = 1, curr = 0;

        for (int i = 2; i <= n; ++i)
        {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return curr;
    }
};

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
    int robRec(vector<int> &nums, int idx)
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
    int solveMemo(vector<int> &nums, int idx, vector<int> &memo)
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
    int robTab(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];

        for (int i = 1; i < n; ++i)
        {
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
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        int prev1 = nums[0]; // dp[i - 1]
        int prev2 = 0;       // dp[i - 2]

        for (int i = 1; i < n; ++i)
        {
            int pick = nums[i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

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
    int robRec(vector<int> &nums, int idx)
    {
        if (idx == 0)
            return nums[0];
        if (idx < 0)
            return 0;

        int pick = nums[idx] + robRec(nums, idx - 2);
        int notPick = robRec(nums, idx - 1);

        return max(pick, notPick);
    }

    int robCircleRec(vector<int> &nums)
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
    int robMemo(vector<int> &nums, int idx, vector<int> &memo)
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

    int robCircleMemo(vector<int> &nums)
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
    int robTab(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];

        for (int i = 1; i < n; ++i)
        {
            int pick = nums[i] + (i >= 2 ? dp[i - 2] : 0);
            int notPick = dp[i - 1];
            dp[i] = max(pick, notPick);
        }

        return dp[n - 1];
    }

    int robCircleTab(vector<int> &nums)
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
    int robLinear(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        int prev1 = nums[0];
        int prev2 = 0;

        for (int i = 1; i < n; ++i)
        {
            int pick = nums[i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int rob(vector<int> &nums)
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

/* =============================================================
 * LEETCODE 62 :UNIQUE PATHS (DP – Move Right or Down from top-left to bottom-right)
 * ============================================================= */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: Recursion (Brute Force)
     * TIME: Exponential, SPACE: O(m + n) stack
     * ------------------------------------------------------------ */
    int recur(int i, int j)
    {
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        int up = recur(i - 1, j);
        int left = recur(i, j - 1);

        return up + left;
    }

    /* ------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(m * n), SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>> &dp)
    {
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, dp);
        int left = memo(i, j - 1, dp);

        return dp[i][j] = up + left;
    }

    /* ------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(m * n), SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int tabulation(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                    dp[i][j] = 1;
                else
                {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ------------------------------------------------------------
     * METHOD 4: Space Optimized DP
     * TIME: O(m * n), SPACE: O(n)
     * ------------------------------------------------------------ */
    int uniquePaths(int m, int n)
    {
        vector<int> prev(n, 1); // First row is all 1s

        for (int i = 1; i < m; i++)
        {
            vector<int> curr(n, 1);
            for (int j = 1; j < n; j++)
            {
                curr[j] = curr[j - 1] + prev[j];
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

/* ====================================================================
 * Leetcode 63: Unique Paths II (DP with obstacles, can move Right or Down)
 * ==================================================================== */

class Solution
{
public:
    /* ----------------------------------------------------------------
     * METHOD 1: RECURSION (TLE for large inputs)
     * TIME: Exponential | SPACE: O(m + n) stack space
     * ---------------------------------------------------------------- */
    int recur(int i, int j, vector<vector<int>> &grid)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == 1)
            return 0;
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        int up = recur(i - 1, j, grid);
        int left = recur(i, j - 1, grid);

        return up + left;
    }

    /* ----------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ---------------------------------------------------------------- */
    int memo(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == 1)
            return 0;
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int left = memo(i, j - 1, grid, dp);

        return dp[i][j] = up + left;
    }

    /* ----------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ---------------------------------------------------------------- */
    int tabulation(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (grid[i][j] == 1)
                {
                    dp[i][j] = 0;
                }
                else if (i == 0 && j == 0)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ----------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZED DP (1D array)
     * TIME: O(m * n) | SPACE: O(n)
     * ---------------------------------------------------------------- */
    int uniquePathsWithObstacles(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (grid[0][0] == 1)
            return 0;

        vector<int> prev(n, 0);
        prev[0] = 1;

        for (int i = 0; i < m; i++)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++)
            {

                if (grid[i][j] == 1)
                {
                    curr[j] = 0;
                }
                else
                {
                    int left = (j > 0) ? curr[j - 1] : 0;
                    curr[j] = prev[j] + left;
                }
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

/* ================================================================
 * LEETCODE 62 : MINIMUM PATH SUM (Only Right and Down)
 * ================================================================ */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: PURE RECURSION (TLE for large inputs)
     * TIME: O(2^(m * n)) | SPACE: O(m + n) stack
     * ------------------------------------------------------------ */
    int recur(int i, int j, vector<vector<int>> &grid)
    {
        if (i < 0 || j < 0)
            return 1e9; // invalid path
        if (i == 0 && j == 0)
            return grid[0][0];

        int up = recur(i - 1, j, grid);
        int left = recur(i, j - 1, grid);

        return grid[i][j] + min(up, left);
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n) | SPACE: O(m * n) + Recursion stack
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (i < 0 || j < 0)
            return 1e9;
        if (i == 0 && j == 0)
            return grid[0][0];

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int left = memo(i, j - 1, grid, dp);

        return dp[i][j] = grid[i][j] + min(up, left);
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n) | SPACE: O(m * n)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                {
                    dp[i][j] = grid[i][j];
                }
                else
                {
                    int up = (i > 0) ? dp[i - 1][j] : 1e9;
                    int left = (j > 0) ? dp[i][j - 1] : 1e9;
                    dp[i][j] = grid[i][j] + min(up, left);
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZED (1D DP)
     * TIME: O(m * n) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> prev(n, 0);

        for (int i = 0; i < m; ++i)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                {
                    curr[j] = grid[i][j];
                }
                else
                {
                    int up = (i > 0) ? prev[j] : 1e9;
                    int left = (j > 0) ? curr[j - 1] : 1e9;
                    curr[j] = grid[i][j] + min(up, left);
                }
            }
            prev = curr;
        }

        return prev[n - 1];
    }
};

/* ================================================================
 * TRIANGLE - MINIMUM PATH SUM (Top to Bottom)
 * ================================================================ */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: RECURSION
     * TIME: O(2^n) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int recur(int r, int c, vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        if (r == n - 1)
            return triangle[r][c];

        int down = recur(r + 1, c, triangle);
        int diag = recur(r + 1, c + 1, triangle);

        return triangle[r][c] + min(down, diag);
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(n^2) | SPACE: O(n^2) + Recursion Stack
     * ------------------------------------------------------------ */
    int memo(int r, int c, vector<vector<int>> &triangle, vector<vector<int>> &dp)
    {
        int n = triangle.size();
        if (r == n - 1)
            return triangle[r][c];

        if (dp[r][c] != -1)
            return dp[r][c];

        int down = memo(r + 1, c, triangle, dp);
        int diag = memo(r + 1, c + 1, triangle, dp);

        return dp[r][c] = triangle[r][c] + min(down, diag);
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(n^2) | SPACE: O(n^2)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: bottom row
        for (int j = 0; j < triangle[n - 1].size(); ++j)
        {
            dp[n - 1][j] = triangle[n - 1][j];
        }

        // Bottom-up filling
        for (int r = n - 2; r >= 0; --r)
        {
            for (int c = 0; c < triangle[r].size(); ++c)
            {
                int down = dp[r + 1][c];
                int diag = dp[r + 1][c + 1];
                dp[r][c] = triangle[r][c] + min(down, diag);
            }
        }

        return dp[0][0];
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZATION (1D DP)
     * TIME: O(n^2) | SPACE: O(n)
     * ------------------------------------------------------------ */
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<int> front(n, 0);

        // Base case: bottom row
        for (int j = 0; j < triangle[n - 1].size(); ++j)
        {
            front[j] = triangle[n - 1][j];
        }

        // Bottom-up filling
        for (int r = n - 2; r >= 0; --r)
        {
            vector<int> curr(n, 0);
            for (int c = 0; c < triangle[r].size(); ++c)
            {
                int down = front[c];
                int diag = front[c + 1];
                curr[c] = triangle[r][c] + min(down, diag);
            }
            front = curr;
        }

        return front[0];
    }
};

/* =============================================================
 * LEETCODE 931: MINIMUM FALLING PATH SUM
 * ============================================================= */

class Solution
{
public:
    /* ------------------------------------------------------------
     * METHOD 1: RECURSION (TLE)
     * TIME: O(3^N) | SPACE: O(N) stack space
     * ------------------------------------------------------------ */
    int recur(int i, int j, vector<vector<int>> &grid)
    {
        int n = grid.size();
        if (j < 0 || j >= n)
            return 1e9;
        if (i == 0)
            return grid[0][j];

        int up = recur(i - 1, j, grid);
        int leftDiag = recur(i - 1, j - 1, grid);
        int rightDiag = recur(i - 1, j + 1, grid);

        return grid[i][j] + min({up, leftDiag, rightDiag});
    }

    /* ------------------------------------------------------------
     * METHOD 2: MEMOIZATION (Top-down DP)
     * TIME: O(N^2) | SPACE: O(N^2) + Recursion Stack
     * ------------------------------------------------------------ */
    int memo(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        int n = grid.size();
        if (j < 0 || j >= n)
            return 1e9;
        if (i == 0)
            return grid[0][j];

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = memo(i - 1, j, grid, dp);
        int leftDiag = memo(i - 1, j - 1, grid, dp);
        int rightDiag = memo(i - 1, j + 1, grid, dp);

        return dp[i][j] = grid[i][j] + min({up, leftDiag, rightDiag});
    }

    /* ------------------------------------------------------------
     * METHOD 3: TABULATION (Bottom-up DP)
     * TIME: O(N^2) | SPACE: O(N^2)
     * ------------------------------------------------------------ */
    int tabulation(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 0; j < n; j++)
        {
            dp[0][j] = grid[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int up = dp[i - 1][j];
                int leftDiag = (j > 0) ? dp[i - 1][j - 1] : 1e9;
                int rightDiag = (j < n - 1) ? dp[i - 1][j + 1] : 1e9;

                dp[i][j] = grid[i][j] + min({up, leftDiag, rightDiag});
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    /* ------------------------------------------------------------
     * METHOD 4: SPACE OPTIMIZATION (1D DP)
     * TIME: O(N^2) | SPACE: O(N)
     * ------------------------------------------------------------ */
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        vector<int> prev(matrix[0].begin(), matrix[0].end());

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++)
            {
                int up = prev[j];
                int leftDiag = (j > 0) ? prev[j - 1] : 1e9;
                int rightDiag = (j < n - 1) ? prev[j + 1] : 1e9;

                curr[j] = matrix[i][j] + min({up, leftDiag, rightDiag});
            }
            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }
};

class Solution
{
public:
    // directions for the 3 possible moves
    vector<int> directions = {-1, 0, 1};

    /* =========================================================================
     * METHOD 1: PURE RECURSION (TLE)
     * TIME: O(3^m * 3^m) | SPACE: O(m)
     * ========================================================================= */
    int recur(int i, int j1, int j2, vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        if (j1 < 0 || j1 >= n || j2 < 0 || j2 >= n)
            return -1e8;

        if (i == m - 1)
        {
            return (j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        }

        int maxCherries = INT_MIN;

        for (int dj1 : directions)
        {
            for (int dj2 : directions)
            {
                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                value += recur(i + 1, j1 + dj1, j2 + dj2, grid);
                maxCherries = max(maxCherries, value);
            }
        }

        return maxCherries;
    }

    /* =========================================================================
     * METHOD 2: MEMOIZATION (Top-Down DP)
     * TIME: O(m * n * n * 9) = O(m * n²)
     * SPACE: O(m * n²) + O(m) recursion stack
     * ========================================================================= */
    int memo(int i, int j1, int j2, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
    {
        int m = grid.size(), n = grid[0].size();

        if (j1 < 0 || j1 >= n || j2 < 0 || j2 >= n)
            return -1e8;

        if (i == m - 1)
        {
            return (j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        }

        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];

        int maxCherries = INT_MIN;

        for (int dj1 : directions)
        {
            for (int dj2 : directions)
            {
                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                value += memo(i + 1, j1 + dj1, j2 + dj2, grid, dp);
                maxCherries = max(maxCherries, value);
            }
        }

        return dp[i][j1][j2] = maxCherries;
    }

    /* =========================================================================
     * METHOD 3: TABULATION (Bottom-Up DP)
     * TIME: O(m * n² * 9) = O(m * n²)
     * SPACE: O(m * n²)
     * ========================================================================= */
    int tabulation(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, 0)));

        // Base case: last row
        for (int j1 = 0; j1 < n; j1++)
        {
            for (int j2 = 0; j2 < n; j2++)
            {
                dp[m - 1][j1][j2] = (j1 == j2) ? grid[m - 1][j1] : grid[m - 1][j1] + grid[m - 1][j2];
            }
        }

        for (int i = m - 2; i >= 0; i--)
        {
            for (int j1 = 0; j1 < n; j1++)
            {
                for (int j2 = 0; j2 < n; j2++)
                {
                    int maxCherries = INT_MIN;

                    for (int dj1 : directions)
                    {
                        for (int dj2 : directions)
                        {
                            int nj1 = j1 + dj1;
                            int nj2 = j2 + dj2;

                            if (nj1 >= 0 && nj1 < n && nj2 >= 0 && nj2 < n)
                            {
                                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                                value += dp[i + 1][nj1][nj2];
                                maxCherries = max(maxCherries, value);
                            }
                        }
                    }

                    dp[i][j1][j2] = maxCherries;
                }
            }
        }

        return dp[0][0][n - 1];
    }

    /* =========================================================================
     * METHOD 4: SPACE OPTIMIZATION (3D → 2D)
     * TIME: O(m * n² * 9)
     * SPACE: O(n²)
     * ========================================================================= */
    int cherryPickup(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> front(n, vector<int>(n, 0)), curr(n, vector<int>(n, 0));

        // Base case
        for (int j1 = 0; j1 < n; j1++)
        {
            for (int j2 = 0; j2 < n; j2++)
            {
                front[j1][j2] = (j1 == j2) ? grid[m - 1][j1] : grid[m - 1][j1] + grid[m - 1][j2];
            }
        }

        for (int i = m - 2; i >= 0; i--)
        {
            for (int j1 = 0; j1 < n; j1++)
            {
                for (int j2 = 0; j2 < n; j2++)
                {
                    int maxCherries = INT_MIN;

                    for (int dj1 : directions)
                    {
                        for (int dj2 : directions)
                        {
                            int nj1 = j1 + dj1;
                            int nj2 = j2 + dj2;

                            if (nj1 >= 0 && nj1 < n && nj2 >= 0 && nj2 < n)
                            {
                                int value = (j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                                value += front[nj1][nj2];
                                maxCherries = max(maxCherries, value);
                            }
                        }
                    }

                    curr[j1][j2] = maxCherries;
                }
            }
            front = curr;
        }

        return front[0][n - 1];
    }
};

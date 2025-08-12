#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Problem: Min Cost Climbing Stairs (LeetCode 746)
==============================================================================

Task:
-----
You are given an integer array 'cost' where cost[i] is the cost of the i-th step
on a staircase. Once you pay the cost, you can climb either one or two steps.
You can either start from step 0 or step 1.
Return the minimum cost to reach the top of the staircase.

-------------------------------------------------------------------------------
Key Observations:
-----------------
1. From any step `i`, you can move to either:
     - i + 1
     - i + 2
2. The "top" is considered beyond the last step (index n).
3. The choice at each step is:
     cost[i] + minCost(from next step)
4. Overlapping subproblems → perfect for DP.

-------------------------------------------------------------------------------
Approaches:
-----------
1. Recursion (Brute Force)
2. Recursion + Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimization (Bottom-Up with O(1) space)

==============================================================================
Method 1: Recursion (Brute Force)
==============================================================================
Time Complexity: O(2^n) - exponential due to repeated subproblems
Space Complexity: O(n) - recursion stack
==============================================================================
*/

class Solution {
public:
    int recur(vector<int>& cost, int n, int i)
    {
        // Base case: reached the top
        if (i == n) return 0;

        // Cost of taking 1 step
        int step1 = INT_MAX;
        if (i + 1 <= n) {
            step1 = cost[i] + recur(cost, n, i + 1);
        }

        // Cost of taking 2 steps
        int step2 = INT_MAX;
        if (i + 2 <= n) {
            step2 = cost[i] + recur(cost, n, i + 2);
        }

        return min(step1, step2);
    }

    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
        int start0 = recur(cost, n, 0);
        int start1 = recur(cost, n, 1);
        return min(start0, start1);
    }
};

/*
==============================================================================
Method 2: Memoization (Top-Down DP)
==============================================================================
Time Complexity: O(n) - each state computed once
Space Complexity: O(n) - dp array + recursion stack
==============================================================================
*/

class Solution {
public:
    int recur(vector<int>& cost, int n, int i, vector<int>& memo)
    {
        if (i == n) return 0;
        if (memo[i] != -1) return memo[i];

        int step1 = INT_MAX, step2 = INT_MAX;
        if (i + 1 <= n) {
            step1 = cost[i] + recur(cost, n, i + 1, memo);
        }
        if (i + 2 <= n) {
            step2 = cost[i] + recur(cost, n, i + 2, memo);
        }

        return memo[i] = min(step1, step2);
    }

    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
        vector<int> memo(n + 1, -1);
        int start0 = recur(cost, n, 0, memo);
        int start1 = recur(cost, n, 1, memo);
        return min(start0, start1);
    }
};

/*
==============================================================================
Method 3: Tabulation (Bottom-Up DP)
==============================================================================
Time Complexity: O(n)
Space Complexity: O(n)
==============================================================================
*/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1, 0); // dp[i] = min cost to reach step i

        for (int i = 2; i <= n; i++) {
            int oneStep = dp[i - 1] + cost[i - 1];
            int twoStep = dp[i - 2] + cost[i - 2];
            dp[i] = min(oneStep, twoStep);
        }

        return dp[n];
    }
};

/*
==============================================================================
Method 4: Space Optimization
==============================================================================
Time Complexity: O(n)
Space Complexity: O(1)
==============================================================================
*/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
        int prev2 = 0; // dp[i-2]
        int prev1 = 0; // dp[i-1]

        for (int i = 2; i <= n; i++) {
            int curr = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

/*
==============================================================================
Example Usage:
==============================================================================
Input:
    cost = [10, 15, 20]
Output:
    15
Explanation:
    Start at index 1 (cost = 15), jump to the top.

Input:
    cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output:
    6
==============================================================================
*/

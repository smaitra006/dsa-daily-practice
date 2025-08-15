#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// Problem: Last Stone Weight II (LeetCode 1049)
// Task:
//     You are given an array `stones` where each element represents the weight
//     of a stone. In each turn, you can smash two stones together:
//       - If they are of equal weight, both are destroyed.
//       - If they have different weights, the smaller one is destroyed and the
//         larger one is reduced by the weight of the smaller one.
//     The goal is to minimize the weight of the last remaining stone (or 0 if none remain).
//
// Key Observation:
//     This is equivalent to splitting stones into two subsets whose sums are as
//     close as possible. The answer will be the absolute difference of the two sums.
//
// Approach:
//     - Let total = sum of all stones.
//     - We try to choose a subset with sum close to total/2 to minimize the difference.
//     - This becomes a variation of the Subset Sum / Partition problem.
//
// ============================================================================
//
// Method 1: Recursion
// Time Complexity: O(2^n)
// Space Complexity: O(n) recursion stack
// ============================================================================
class Solution {
public:
    int solveRec(vector<int>& stones, int i, int sum1, int total)
    {
        if (i == stones.size()) {
            return abs((total - sum1) - sum1);
        }

        // Option 1: Include current stone in subset1
        int include = solveRec(stones, i + 1, sum1 + stones[i], total);

        // Option 2: Exclude current stone from subset1
        int exclude = solveRec(stones, i + 1, sum1, total);

        return min(include, exclude);
    }

    int lastStoneWeightII(vector<int>& stones)
    {
        int total = accumulate(stones.begin(), stones.end(), 0);
        return solveRec(stones, 0, 0, total);
    }
};

// ============================================================================
//
// Method 2: Memoization (Top-Down DP)
// Time Complexity: O(n * totalSum)
// Space Complexity: O(n * totalSum) + O(n) recursion stack
// ============================================================================
class Solution {
public:
    int solveMemo(vector<int>& stones, int i, int sum1, int total, vector<vector<int>>& dp)
    {
        if (i == stones.size()) {
            return abs((total - sum1) - sum1);
        }

        if (dp[i][sum1] != -1) return dp[i][sum1];

        int include = solveMemo(stones, i + 1, sum1 + stones[i], total, dp);
        int exclude = solveMemo(stones, i + 1, sum1, total, dp);

        return dp[i][sum1] = min(include, exclude);
    }

    int lastStoneWeightII(vector<int>& stones)
    {
        int total = accumulate(stones.begin(), stones.end(), 0);
        vector<vector<int>> dp(stones.size(), vector<int>(total + 1, -1));
        return solveMemo(stones, 0, 0, total, dp);
    }
};

// ============================================================================
//
// Method 3: Tabulation (Bottom-Up DP)
// Time Complexity: O(n * totalSum)
// Space Complexity: O(n * totalSum)
// ============================================================================
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        int total = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size();

        // dp[i][j] = true if we can form sum j using first i stones
        vector<vector<bool>> dp(n + 1, vector<bool>(total / 2 + 1, false));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= total / 2; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - stones[i - 1]];
                }
            }
        }

        // Find the closest sum to total/2
        for (int j = total / 2; j >= 0; j--) {
            if (dp[n][j]) {
                return total - 2 * j;
            }
        }

        return 0; // Should never reach here
    }
};

// ============================================================================
//
// Method 4: Space Optimized DP
// Time Complexity: O(n * totalSum)
// Space Complexity: O(totalSum)
// ============================================================================
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        int total = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size();

        vector<bool> dp(total / 2 + 1, false);
        dp[0] = true;

        for (int stone : stones) {
            for (int j = total / 2; j >= stone; j--) {
                dp[j] = dp[j] || dp[j - stone];
            }
        }

        for (int j = total / 2; j >= 0; j--) {
            if (dp[j]) {
                return total - 2 * j;
            }
        }

        return 0;
    }
};


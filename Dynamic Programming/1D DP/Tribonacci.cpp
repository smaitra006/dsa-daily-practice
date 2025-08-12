#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: N-th Tribonacci Number
--------------------------------------------------------------------------------
The Tribonacci sequence Tn is defined as:
T0 = 0, T1 = 1, T2 = 1
Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0

Task:
Given n, return the value of Tn.

Approach:
We will implement this in 4 ways:
1. Recursion (Brute Force)
2. Recursion + Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimization

Complexity Analysis:
1. Recursion: O(3^n) time, O(n) space (stack)
2. Memoization: O(n) time, O(n) space
3. Tabulation: O(n) time, O(n) space
4. Space Optimization: O(n) time, O(1) space
================================================================================
*/

class Solution {
public:

    //============================================================================
    // 1. Recursion
    //============================================================================
    int tribonacciRec(int n)
    {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;
        return tribonacciRec(n - 1) + tribonacciRec(n - 2) + tribonacciRec(n - 3);
    }

    //============================================================================
    // 2. Memoization
    //============================================================================
    int tribonacciMemoHelper(int n, vector<int>& dp)
    {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;
        if (dp[n] != -1) return dp[n];
        return dp[n] = tribonacciMemoHelper(n - 1, dp) +
            tribonacciMemoHelper(n - 2, dp) +
            tribonacciMemoHelper(n - 3, dp);
    }

    int tribonacciMemo(int n)
    {
        vector<int> dp(n + 1, -1);
        return tribonacciMemoHelper(n, dp);
    }

    //============================================================================
    // 3. Tabulation
    //============================================================================
    int tribonacciTab(int n)
    {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        vector<int> dp(n + 1, 0);
        dp[0] = 0, dp[1] = 1, dp[2] = 1;

        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }

        return dp[n];
    }

    //============================================================================
    // 4. Space Optimization
    //============================================================================
    int tribonacciSpaceOpt(int n)
    {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        int first = 0, second = 1, third = 1, cur;
        for (int i = 3; i <= n; i++) {
            cur = first + second + third;
            first = second;
            second = third;
            third = cur;
        }
        return third;
    }
};


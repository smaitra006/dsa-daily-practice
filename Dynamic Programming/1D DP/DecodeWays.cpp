#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem: Decode Ways (Leetcode 91)
===============================================================================
Task:
------
A message containing letters from A-Z is encoded using the following mapping:
'A' -> "1", 'B' -> "2", ..., 'Z' -> "26".

Given a string s containing only digits, return the number of ways to decode it.

Example:
---------
Input: s = "226"
Output: 3
Explanation: "226" can be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Constraints:
------------
1 <= s.length <= 100
s[i] is a digit and may contain leading zeros.

===============================================================================
Approach:
===============================================================================
We consider two decoding choices at each step:
1. Take 1 digit (must be non-zero).
2. Take 2 digits (must be between 10 and 26 inclusive).

We use:
1. Recursion
2. Memoization (Top-down DP)
3. Tabulation (Bottom-up DP)
4. Space Optimization

===============================================================================
Complexity Analysis:
===============================================================================
Let n = length of string
- Recursion:  O(2^n) exponential
- Memoization: O(n)
- Tabulation:  O(n)
- Space Optimized: O(1)

===============================================================================
*/

class Solution {
public:
    //============================================================================
    // 1. Recursion
    //============================================================================
    int solveRec(string& s, int i, int n)
    {
        if (i == n) return 1;       // Reached end successfully
        if (s[i] == '0') return 0;  // Invalid starting digit

        // Take 1 digit
        int only1 = solveRec(s, i + 1, n);

        // Take 2 digits (if valid)
        int only2 = 0;
        if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
            only2 = solveRec(s, i + 2, n);
        }

        return only1 + only2;
    }

    //============================================================================
    // 2. Memoization
    //============================================================================
    int solveMemo(string& s, int i, int n, vector<int>& dp)
    {
        if (i == n) return 1;
        if (s[i] == '0') return 0;

        if (dp[i] != -1) return dp[i];

        int only1 = solveMemo(s, i + 1, n, dp);
        int only2 = 0;
        if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
            only2 = solveMemo(s, i + 2, n, dp);
        }

        return dp[i] = only1 + only2;
    }

    //============================================================================
    // 3. Tabulation
    //============================================================================
    int solveTab(string& s)
    {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1; // Base case: empty string = 1 way

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            // Single digit
            dp[i] = dp[i + 1];
            // Double digit
            if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                dp[i] += dp[i + 2];
            }
        }
        return dp[0];
    }

    //============================================================================
    // 4. Space Optimization
    //============================================================================
    int solveSpaceOpt(string& s)
    {
        int n = s.size();
        int next = 1;      // dp[n]
        int nextNext = 0;  // dp[n+1] (dummy)

        for (int i = n - 1; i >= 0; i--) {
            int curr = 0;
            if (s[i] != '0') {
                curr = next; // Take 1 digit
                if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    curr += (i + 2 <= n ? (i + 2 == n ? 1 : (i + 2 <= n ? nextNext : 0)) : 0);
                    curr += (i + 2 <= n ? (i + 2 == n ? 1 : (i + 2 <= n ? nextNext : 0)) : 0);
                }
            }
            // Shift variables
            nextNext = next;
            next = curr;
        }
        return next;
    }

    //============================================================================
    // Main Function
    //============================================================================
    int numDecodings(string s)
    {
        int n = s.length();

        // --- Method 1: Recursion ---
        // return solveRec(s, 0, n);

        // --- Method 2: Memoization ---
        // vector<int> dp(n, -1);
        // return solveMemo(s, 0, n, dp);

        // --- Method 3: Tabulation ---
        return solveTab(s);

        // --- Method 4: Space Optimization ---
        // return solveSpaceOpt(s);
    }
};

/*
===============================================================================
Example Usage:
===============================================================================
Solution sol;
cout << sol.numDecodings("12");   // Output: 2  ("AB", "L")
cout << sol.numDecodings("226");  // Output: 3  ("BZ", "VF", "BBF")
cout << sol.numDecodings("06");   // Output: 0  (invalid)
===============================================================================
*/

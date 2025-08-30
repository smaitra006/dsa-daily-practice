#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Reverse Integer (LeetCode 7)
//
// Task:
// Given a signed 32-bit integer `x`, return `x` with its digits reversed.
// If reversing `x` causes the value to go outside the signed 32-bit integer
// range [-2^31, 2^31 - 1], return 0.
//
// Example:
//   Input:  x = 123
//   Output: 321
//
//   Input:  x = -123
//   Output: -321
//
//   Input:  x = 1534236469
//   Output: 0   (overflow case)
//
// Approach:
// 1. Use a `long long` to safely handle intermediate reversed value.
// 2. Extract digits using modulo and build reversed number by multiplying ans by 10.
// 3. Divide x by 10 in each step to reduce it.
// 4. Check for overflow after reversal is complete.
// 5. If out of 32-bit signed integer range, return 0, else return result.
//==============================================================================

class Solution {
public:
    int reverse(int x)
    {
        long long ans = 0;

        // Extract digits and build reversed number
        while (x != 0) {
            ans = (ans * 10) + (x % 10);
            x /= 10;
        }

        // Check for 32-bit signed integer overflow
        if (ans < INT_MIN || ans > INT_MAX)
            return 0;

        return static_cast<int>(ans);
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(log₁₀N), where N is the absolute value of x
//          (since we process each digit once).
// - Space: O(1), only a few variables used.
//
// Example Walkthrough:
// Input:  x = -123
// Steps:  ans = -3 → -32 → -321
// Output: -321
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Armstrong Number (LeetCode 1134)
//
// Task:
// Given an integer `n`, return true if and only if it is an *Armstrong number*.
//
// An n-digit number is an Armstrong number if it is equal to the sum of its
// digits raised to the n-th power.
//
// Example:
//   Input:  n = 153
//   Output: true
//   Explanation: 1³ + 5³ + 3³ = 153
//
//   Input:  n = 123
//   Output: false
//   Explanation: 1³ + 2³ + 3³ = 36 ≠ 123
//
// Approach:
// 1. Convert the number to string to easily count the digits (d).
// 2. Iterate over each digit, compute digit^d, and add to sum.
// 3. If the sum equals the original number, return true; else false.
//==============================================================================

class Solution {
public:
    bool isArmstrong(int n)
    {
        string num = to_string(n);
        int d = num.length();   // Number of digits
        long long sum = 0;

        // Compute sum of digits^d
        for (char c : num) {
            int digit = c - '0';
            sum += pow(digit, d);
        }

        return sum == n;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(d), where d = number of digits in n.
// - Space: O(1), only a few variables used.
//
// Example Walkthrough:
// Input:  n = 9474
// Digits: 9, 4, 7, 4  → 9⁴ + 4⁴ + 7⁴ + 4⁴ = 9474
// Output: true
//==============================================================================

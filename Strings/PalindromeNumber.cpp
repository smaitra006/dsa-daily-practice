#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Palindrome Number (LeetCode 9)
//
// Task:
// Given an integer `x`, return true if `x` is a palindrome, and false otherwise.
//
// A palindrome is a number that reads the same backward as forward.
//
// Example:
//   Input:  x = 121
//   Output: true
//
//   Input:  x = -121
//   Output: false   (negative sign not symmetric)
//
//   Input:  x = 10
//   Output: false
//
// Approach:
// 1. If x is negative, return false (negative numbers can't be palindromes).
// 2. Convert x to string form.
// 3. Use two pointers (i, j) from both ends of the string.
// 4. Compare characters at i and j until they meet.
// 5. If all match, return true; otherwise return false.
//==============================================================================

class Solution {
public:
    bool isPalindrome(int x)
    {
        if (x < 0) return false;   // Negative numbers can't be palindromes

        string num = to_string(x);
        int i = 0, j = num.length() - 1;

        // Two-pointer check
        while (i <= j) {
            if (num[i] != num[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = number of digits in x (string length).
// - Space: O(N), for storing string representation of x.
//
// Example Walkthrough:
// Input:  x = 1221
// String: "1221"
// Compare: '1' == '1', '2' == '2' → Palindrome → return true
//==============================================================================

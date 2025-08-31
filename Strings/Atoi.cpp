#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: String to Integer (atoi) (LeetCode 8)
//
// Task:
// Implement the `atoi` function, which converts a string to a 32-bit signed
// integer. The function should handle leading whitespaces, optional signs,
// digits, and overflow cases.
//
// Rules:
// 1. Ignore leading whitespaces.
// 2. An optional '+' or '-' sign may appear before digits.
// 3. Convert continuous digits until a non-digit is encountered.
// 4. If no valid digits exist → return 0.
// 5. Clamp result to [-2^31, 2^31 - 1] = [-2147483648, 2147483647] on overflow.
//
// Example:
//   Input:  s = "   -42"
//   Output: -42
//
//   Input:  s = "4193 with words"
//   Output: 4193
//
//   Input:  s = "words and 987"
//   Output: 0
//
// Approach:
// 1. Skip leading whitespaces.
// 2. Detect sign (`+` or `-`).
// 3. Skip leading zeros (optional optimization).
// 4. Parse digits and build number using long long to detect overflow.
// 5. Clamp to INT_MIN or INT_MAX if overflow occurs.
// 6. Return final result with sign.
//==============================================================================

class Solution {
public:
    int myAtoi(string s)
    {
        int ind = 0;

        // Step 1: Skip leading spaces
        while (ind < s.size() && s[ind] == ' ')
            ind++;

        // Step 2: Handle sign
        bool positive = true;
        if (ind < s.size() && s[ind] == '-') {
            positive = false;
            ind++;
        }
        else if (ind < s.size() && s[ind] == '+') {
            ind++;
        }

        // Step 3: Skip leading zeros
        while (ind < s.size() && s[ind] == '0')
            ind++;

        // Step 4: Extract continuous digits
        int start = ind;
        while (ind < s.size() && isdigit(s[ind]))
            ind++;

        if (start == ind) return 0; // no valid digits

        // Step 5: Convert digits to number
        long long ans = 0;
        for (int i = start; i < ind; i++) {
            int digit = s[i] - '0';
            ans = ans * 10 + digit;

            // Step 6: Clamp on overflow
            if (positive && ans > INT_MAX) return INT_MAX;
            if (!positive && -ans < INT_MIN) return INT_MIN;
        }

        // Step 7: Apply sign
        if (!positive) ans = -ans;

        return static_cast<int>(ans);
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of input string (single scan).
// - Space: O(1), constant extra space.
//
// Example Walkthrough:
// Input: "   -42"
//   Skip spaces → index at '-'
//   Sign → negative
//   Parse "42" → ans = 42
//   Apply sign → -42
// Output = -42
//==============================================================================

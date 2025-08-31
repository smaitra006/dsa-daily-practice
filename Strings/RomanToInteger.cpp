#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Roman to Integer (LeetCode 13)
//
// Task:
// Given a Roman numeral string `s`, convert it into an integer.
//
// Roman numeral rules:
//   - I (1), V (5), X (10), L (50), C (100), D (500), M (1000)
//   - Smaller numeral before a larger numeral → subtractive notation
//     e.g., IV = 4, IX = 9, XL = 40, XC = 90, CD = 400, CM = 900
//
// Example:
//   Input:  s = "MCMXCIV"
//   Output: 1994
//   Explanation: M (1000) + CM (900) + XC (90) + IV (4) = 1994
//
// Approach:
// 1. Map each Roman numeral character to its integer value.
// 2. Iterate through the string from left to right:
//    - If the current numeral is smaller than the next → subtract it.
//    - Otherwise, add it.
// 3. Finally, add the last numeral (since it is always added).
//
//==============================================================================

class Solution {
public:
    int romanToInt(string s)
    {
        int ans = 0;
        vector<int> roman(128); // ASCII-based mapping for O(1) lookup

        // Roman numeral mappings
        roman['I'] = 1;
        roman['V'] = 5;
        roman['X'] = 10;
        roman['L'] = 50;
        roman['C'] = 100;
        roman['D'] = 500;
        roman['M'] = 1000;

        // Process string except last character
        for (int i = 0; i + 1 < s.length(); ++i) {
            if (roman[s[i]] < roman[s[i + 1]])
                ans -= roman[s[i]]; // subtractive case
            else
                ans += roman[s[i]]; // normal case
        }

        // Add the last character
        return ans + roman[s.back()];
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of string `s` (single scan).
// - Space: O(1), since Roman numeral mapping is fixed size.
//
// Example Walkthrough:
// Input: "MCMXCIV"
//   M(1000) < C? No → ans = 1000
//   C(100) < M(1000)? Yes → ans = 1000 - 100 = 900
//   M(1000) < X? No → ans = 1900
//   X(10) < C(100)? Yes → ans = 1900 - 10 = 1890
//   C(100) < I? No → ans = 1990
//   I(1) < V(5)? Yes → ans = 1990 - 1 = 1989
//   Add last V(5) → 1989 + 5 = 1994
// Final Answer = 1994
//==============================================================================

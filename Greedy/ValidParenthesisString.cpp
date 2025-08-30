#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Valid Parenthesis String (LeetCode 678)
//
// Task:
// Given a string `s` containing only '(', ')', and '*', return true if `s` is
// valid. A string is valid if:
// 1. Any '(' must have a corresponding ')'
// 2. Any ')' must have a corresponding '('
// 3. '*' can be treated as '(', ')', or an empty string
//
// Example:
//   Input:  s = "(*))"
//   Output: true
//
//   Input:  s = "(*()"
//   Output: true
//
// Approach (Greedy with Range Tracking):
// 1. Use two counters: `low` and `high`.
//    - `low` = minimum number of open parentheses possible
//    - `high` = maximum number of open parentheses possible
// 2. Iterate through string:
//    - '(' → increase both low and high
//    - ')' → decrease both; ensure low >= 0
//    - '*' → could be '(', ')' or empty → low--, high++
// 3. If at any point high < 0 → too many ')' → invalid
// 4. At the end, if low == 0 → valid
//==============================================================================

class Solution {
public:
    bool checkValidString(string s)
    {
        int low = 0, high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low = max(0, low - 1);
                high--;
            }
            else { // c == '*'
                low = max(0, low - 1); // treat as ')'
                high++;                // treat as '('
            }

            if (high < 0) return false; // too many ')'
        }

        return low == 0;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of string s (single pass).
// - Space: O(1), only two counters used.
//
// Example Walkthrough:
// Input: s = "(*))"
// Step1: '(' → low=1, high=1
// Step2: '*' → low=0, high=2
// Step3: ')' → low=0, high=1
// Step4: ')' → low=0, high=0
// Output: true
//==============================================================================

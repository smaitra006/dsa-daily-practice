#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Maximum Nesting Depth of the Parentheses (LeetCode 1614)
//
// Task:
// Given a valid parentheses string `s`, return the maximum nesting depth
// of the parentheses.
//
// Example:
//   Input:  s = "(1+(2*3)+((8)/4))+1"
//   Output: 3
//
//   Input:  s = "(1)+((2))+(((3)))"
//   Output: 3
//
// Approach:
// 1. Use a stack to simulate the parentheses nesting.
// 2. Push '(' onto the stack, pop when encountering ')', and track max depth.
// 3. The maximum stack size during the process = max nesting depth.
//
// Optimization:
// Instead of stack, we can directly use a counter (since we only care about
// the count of open parentheses).
//==============================================================================

class Solution {
public:
    int maxDepth(string s)
    {
        stack<char> st;
        int maxD = 0;

        for (auto ch : s) {
            if (ch == '(') {
                st.push(ch);
                int sz = st.size();
                maxD = max(maxD, sz);
            }
            else if (ch == ')') {
                st.pop();
            }
        }

        return maxD;
    }
};

//==============================================================================
// Optimized Approach (without stack):
//
// class Solution {
// public:
//     int maxDepth(string s) {
//         int depth = 0, maxD = 0;
//         for (char ch : s) {
//             if (ch == '(') {
//                 depth++;
//                 maxD = max(maxD, depth);
//             } else if (ch == ')') {
//                 depth--;
//             }
//         }
//         return maxD;
//     }
// };
//
//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of the string.
// - Space: O(N) with stack, O(1) with counter (optimized).
//
// Example Walkthrough:
// Input: "(1+(2*3)+((8)/4))+1"
// - '(' -> depth=1, maxD=1
// - '(' -> depth=2, maxD=2
// - '(' -> depth=3, maxD=3
// Final Answer = 3
//==============================================================================

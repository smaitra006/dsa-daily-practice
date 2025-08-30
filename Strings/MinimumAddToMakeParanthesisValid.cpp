#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Minimum Add to Make Parentheses Valid (LeetCode 921)
//
// Task:
// Given a string s consisting only of characters '(' and ')',
// return the minimum number of parentheses we must add to make the string valid.
//
// A string is valid if:
// - Every opening '(' has a corresponding closing ')'
// - Parentheses are properly nested
//
// Approach:
// 1. Use a stack to keep track of unmatched '(' characters.
// 2. Traverse the string:
//    - If '(' → push into stack.
//    - If ')' →
//         * If stack is not empty → pop (one '(' matched).
//         * Else → increment counter (extra ')' needs a matching '(').
// 3. At the end, the stack size represents unmatched '(' that need closing ')'
// 4. Answer = cnt (extra ')') + stack.size() (extra '(').
//==============================================================================

class Solution {
public:
    int minAddToMakeValid(string s)
    {
        int cnt = 0;               // count of unmatched ')'
        stack<char> st;            // stack to store unmatched '('

        for (auto ch : s) {
            if (ch == '(') {
                st.push(ch);
            }
            else if (ch == ')') {
                if (st.empty()) {
                    cnt++;         // extra ')' needs an opening
                }
                else {
                    st.pop();      // match found for one '('
                }
            }
        }

        // Add remaining unmatched '('
        cnt += st.size();
        return cnt;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of s (single traversal).
// - Space: O(N) in worst case (all '(' stored in stack).
//
// Example:
// Input:  "()))(("
// Output: 4
// Explanation: Need two '(' at beginning and two ')' at the end.
//==============================================================================

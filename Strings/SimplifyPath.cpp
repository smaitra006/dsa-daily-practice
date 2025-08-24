#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Simplify Path (LeetCode 71)
// Task: Given an absolute path for a Unix-style file system, simplify it.
//==============================================================================
//
// Approach:
// - Use a stack to process directory tokens separated by '/'.
// - Ignore empty tokens and "." (current directory).
// - For "..", pop from the stack if not empty (go up one directory).
// - Otherwise, push valid directory names.
// - Finally, rebuild the canonical path from the stack contents.
//
// Complexity Analysis:
// - Time: O(n), where n = length of the path (we scan once and process each token).
// - Space: O(n), for storing tokens in the stack.
//
//==============================================================================

class Solution {
public:
    string simplifyPath(string path)
    {
        stack<string> tokens;
        stringstream ss(path);
        string token;

        // Split the path by '/'
        while (getline(ss, token, '/')) {
            if (token.empty() || token == ".") {
                continue;  // skip empty parts and current directory
            }
            if (token == "..") {
                if (!tokens.empty()) {
                    tokens.pop();  // move one directory up
                }
            }
            else {
                tokens.push(token);  // valid directory
            }
        }

        // If stack is empty, return root
        if (tokens.empty()) {
            return "/";
        }

        // Rebuild the path from the stack
        string result;
        while (!tokens.empty()) {
            result = '/' + tokens.top() + result;
            tokens.pop();
        }

        return result;
    }
};

//==============================================================================
// Example Usage:
// Input: path = "/home//foo/../bar/"
// Output: "/home/bar"
//==============================================================================

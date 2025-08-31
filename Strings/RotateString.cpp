#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Rotate String (LeetCode 796)
//
// Task:
// Given two strings `s` and `goal`, return true if and only if `s` can become
// `goal` after some number of shifts (rotations). A rotation shifts the first
// character of `s` to the end of the string.
//
// Example:
//   Input:  s = "abcde", goal = "cdeab"
//   Output: true
//
//   Input:  s = "abcde", goal = "abced"
//   Output: false
//
// Approach (Rotation Check):
// 1. If `s` and `goal` have different lengths → not possible.
// 2. Try aligning `s` with each position in `goal` where the first character matches.
// 3. Check if the remainder of `s` matches `goal` in a cyclic manner.
//==============================================================================

class Solution {
public:
    int m, n;

    // Helper function: checks if rotating s starting from index `j` in goal matches.
    bool check(string s, string goal, int i, int j)
    {
        while (i < n) {
            if (s[i] != goal[j % m]) return false;  // mismatch
            i++;
            j++;
        }
        return true;
    }

    bool rotateString(string s, string goal)
    {
        if (s.length() != goal.length()) return false;

        m = goal.size();
        n = s.size();

        // Try all possible alignments in goal where s[0] matches goal[k]
        for (int k = 0; k < goal.size(); k++) {
            if (goal[k] == s[0]) {
                if (check(s, goal, 1, k + 1)) return true;
            }
        }
        return false;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N^2) in the worst case (for each matching start, check full string).
//   (Can be optimized to O(N) using `goal+goal` trick.)
// - Space: O(1), constant extra memory.
//
// Example Walkthrough:
// Input:  s="abcde", goal="cdeab"
// - Try starting match at 'c' in goal → works → return true.
//
// Input:  s="abcde", goal="abced"
// - No rotation matches → return false.
//==============================================================================

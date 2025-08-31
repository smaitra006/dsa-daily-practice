#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Palindrome Partitioning (LeetCode 131)
//
// Task:
// Given a string `s`, partition `s` such that every substring of the partition
// is a palindrome. Return all possible palindrome partitioning of `s`.
//
// Example:
//   Input:  s = "aab"
//   Output: [["a","a","b"],["aa","b"]]
//
//   Input:  s = "a"
//   Output: [["a"]]
//
// Approach (Backtracking):
// 1. Use backtracking to explore all possible partitions of the string.
// 2. At each step, consider every substring starting at current index.
// 3. If the substring is a palindrome, include it in current path and recurse for the remaining string.
// 4. After recursion, remove the substring from path (backtrack).
// 5. When the start index reaches the end of the string, add the path to result.
//==============================================================================

class Solution {
public:
    void backtrack(const string& s, int start, vector<string>& path, vector<vector<string>>& result)
    {
        if (start == s.length()) {
            result.push_back(path);
            return;
        }
        for (int end = start + 1; end <= s.length(); ++end) {
            if (isPalindrome(s, start, end - 1)) {
                path.push_back(s.substr(start, end - start));
                backtrack(s, end, path, result);
                path.pop_back(); // backtrack
            }
        }
    }

    bool isPalindrome(const string& s, int left, int right)
    {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }

    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> result;
        vector<string> path;
        backtrack(s, 0, path, result);
        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N * 2^N), N = length of s. Each substring partition is explored, and palindrome check costs O(N).
// - Space: O(N), for recursion stack and path storage.
//
// Example Walkthrough:
// Input: s = "aab"
// Step1: "a" → "a" → "b" → path=["a","a","b"] → add to result
// Step2: "aa" → "b" → path=["aa","b"] → add to result
// Output: [["a","a","b"],["aa","b"]]
//==============================================================================

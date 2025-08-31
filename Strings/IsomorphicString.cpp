#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Isomorphic Strings (LeetCode 205)
//
// Task:
// Given two strings `s` and `t`, determine if they are isomorphic. Two strings
// are isomorphic if the characters in `s` can be replaced to get `t`, with a
// one-to-one mapping between characters.
//
// Example:
//   Input:  s = "egg", t = "add"
//   Output: true
//
//   Input:  s = "foo", t = "bar"
//   Output: false
//
// Approach (Pattern Mapping):
// 1. Map each unique character in a string to a unique index representing its first occurrence.
// 2. Convert both strings to their corresponding pattern of indices.
// 3. Compare the patterns. If they match → strings are isomorphic.
//==============================================================================

class Solution {
public:
    vector<int> getPattern(const string& s)
    {
        unordered_map<char, int> mp;
        vector<int> pattern;
        int idx = 0;

        for (char c : s) {
            if (mp.find(c) == mp.end()) mp[c] = idx++;
            pattern.push_back(mp[c]);
        }

        return pattern;
    }

    bool isIsomorphic(string s, string t)
    {
        return getPattern(s) == getPattern(t);
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), N = length of strings s and t.
// - Space: O(N), for storing patterns and mapping.
//
// Example Walkthrough:
// Input: s="egg", t="add"
// Pattern(s)="0,1,1", Pattern(t)="0,1,1" → match → Output: true
//
// Input: s="foo", t="bar"
// Pattern(s)="0,1,1", Pattern(t)="0,1,2" → mismatch → Output: false
//==============================================================================

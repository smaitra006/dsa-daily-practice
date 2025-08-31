#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Valid Anagram (LeetCode 242)
//
// Task:
// Given two strings `s` and `t`, return true if `t` is an anagram of `s`,
// and false otherwise.
// An Anagram is formed by rearranging the letters of a word.
//
// Example:
//   Input:  s = "anagram", t = "nagaram"
//   Output: true
//
//   Input:  s = "rat", t = "car"
//   Output: false
//
// Approach (Sorting):
// 1. Sort both strings.
// 2. If sorted versions are equal → they are anagrams.
//==============================================================================

class Solution {
public:
    bool isAnagram(string s, string t)
    {
        sort(begin(s), end(s));   // sort string s
        sort(begin(t), end(t));   // sort string t
        return s == t;            // compare sorted strings
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N log N), where N = max(|s|, |t|), due to sorting.
// - Space: O(1) (ignoring sort stack space).
//
// Example Walkthrough:
// Input:  s="anagram", t="nagaram"
// - Sorted s = "aaagmnr"
// - Sorted t = "aaagmnr"
// - Equal → return true
//
// Input:  s="rat", t="car"
// - Sorted s = "art"
// - Sorted t = "acr"
// - Not equal → return false
//==============================================================================

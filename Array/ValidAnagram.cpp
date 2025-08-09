/* ==============================================================================
 * Problem: Valid Anagram
 *
 * Task:
 * - Given two strings `s` and `t`, determine if `t` is an anagram of `s`.
 * - An anagram is formed by rearranging all the letters of another string exactly once.
 *
 * Approach:
 * 1. Sort both strings.
 * 2. If they become identical after sorting → they are anagrams.
 *
 * Time Complexity  : O(n log n) — Sorting both strings.
 * Space Complexity : O(1)       — Sorting done in-place.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t)
    {
        sort(begin(s), end(s));  // Sort first string
        sort(begin(t), end(t));  // Sort second string

        return s == t;  // Compare sorted strings
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     Solution sol;
 *     cout << boolalpha << sol.isAnagram("anagram", "nagaram") << endl; // Output: true
 *     cout << boolalpha << sol.isAnagram("rat", "car") << endl;         // Output: false
 *
 *     return 0;
 * }
 * ============================================================================== */

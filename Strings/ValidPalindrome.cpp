#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Valid Palindrome (LeetCode 125)
//
// Task:
// A phrase is a palindrome if, after converting all uppercase letters into
// lowercase and removing all non-alphanumeric characters, it reads the same
// forward and backward.
//
// Given a string `s`, return true if it is a palindrome, or false otherwise.
//
// Example:
//   Input:  s = "A man, a plan, a canal: Panama"
//   Output: true
//   Explanation: "amanaplanacanalpanama" is a palindrome.
//
//   Input:  s = "race a car"
//   Output: false
//
// Approach:
// 1. Build a filtered string by keeping only alphanumeric characters
//    and converting them to lowercase.
// 2. Use two pointers (`left`, `right`) to compare characters from both ends.
// 3. If all characters match, return true; else false.
//==============================================================================

class Solution {
public:
    bool isPalindrome(string s)
    {
        string filtered;

        // Keep only alphanumeric characters in lowercase
        for (char c : s) {
            if (isalnum(c)) {
                filtered += tolower(c);
            }
        }

        int left = 0;
        int right = filtered.size() - 1;

        // Two-pointer comparison
        while (left < right) {
            if (filtered[left] != filtered[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of string `s` (each character processed once).
// - Space: O(N), for storing the filtered string.
//
// Example Walkthrough:
// Input:  s = "A man, a plan, a canal: Panama"
// Filter: "amanaplanacanalpanama"
// Compare: matches from both ends → return true
//==============================================================================

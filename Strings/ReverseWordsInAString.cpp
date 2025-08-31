#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Reverse Words in a String (LeetCode 151)
//
// Task:
// Given an input string `s`, reverse the order of the words.
// A word is defined as a sequence of non-space characters. The words are
// separated by spaces. Return the string with words in reverse order,
// separated by a single space, and no leading/trailing spaces.
//
// Example 1:
//   Input:  s = "the sky is blue"
//   Output: "blue is sky the"
//
// Example 2:
//   Input:  s = "  hello world  "
//   Output: "world hello"
//
// Example 3:
//   Input:  s = "a good   example"
//   Output: "example good a"
//
// Approach:
// 1. Use `stringstream` to split the input string into words,
//    automatically handling multiple spaces.
// 2. Store words in a vector.
// 3. Rebuild the string by iterating the vector in reverse order.
//==============================================================================

class Solution {
public:
    string reverseWords(string s)
    {
        stringstream ss(s);
        string word;
        vector<string> words;

        // Step 1: Extract words using stringstream
        while (ss >> word) {
            words.push_back(word);
        }

        // Step 2: Rebuild in reverse order
        string result;
        for (int i = words.size() - 1; i >= 0; i--) {
            result += words[i];
            if (i > 0) result += " "; // add space between words
        }

        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of input string (scan + rebuild).
// - Space: O(N), to store extracted words.
//
// Example Walkthrough:
// Input: "  hello world  "
//   Extracted words = ["hello", "world"]
//   Reverse join    = "world hello"
// Output: "world hello"
//==============================================================================

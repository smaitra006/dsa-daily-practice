#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 49. Group Anagrams (Leetcode)
 *
 * Task:
 * - Given an array of strings, group the anagrams together.
 * - You can return the answer in any order.
 *
 * Key Idea:
 * - Anagrams have the same characters in a different order.
 * - If we sort the characters in each word, all anagrams share the same sorted key.
 *
 * Approach:
 * 1. Create an unordered_map<string, vector<string>> where:
 *      - key   = sorted version of the string
 *      - value = list of words having the same sorted characters
 * 2. Iterate through each string:
 *      - Sort the string to get the key.
 *      - Append the original string to the map entry for that key.
 * 3. Collect all values from the map into a result vector.
 *
 * Time Complexity  : O(N * K log K)
 *      - N = number of strings
 *      - K = max length of a string
 *      - Sorting each string costs O(K log K).
 * Space Complexity : O(N * K) for storing grouped anagrams.
 * ============================================================================== */

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        unordered_map<string, vector<string>> groups;

        // Step 1: Group by sorted string key
        for (string& s : strs) {
            string key = s;
            sort(key.begin(), key.end()); // Same for all anagrams
            groups[key].push_back(s);
        }

        // Step 2: Move grouped values into result
        vector<vector<string>> result;
        for (auto& entry : groups) {
            result.push_back(entry.second);
        }

        return result;
    }
};


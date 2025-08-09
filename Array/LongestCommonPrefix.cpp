/* ==============================================================================
 * Problem: Longest Common Prefix
 *
 * Task:
 * - Given an array of strings `strs`, find the longest common prefix string
 *   shared among all the strings.
 * - If there is no common prefix, return an empty string "".
 *
 * Approach:
 * 1. Start with the first string as the initial prefix.
 * 2. Compare it with each subsequent string, character by character.
 * 3. Truncate the prefix to the matching part.
 * 4. Stop early if the prefix becomes empty.
 *
 * Time Complexity  : O(n * m) — n = number of strings, m = length of shortest string.
 * Space Complexity : O(1)     — Only uses variables for comparison.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        string prefix = strs[0];  // Assume first string is the prefix

        // Compare prefix with each string in the array
        for (int i = 1; i < strs.size(); i++) {
            int j = 0;
            // Match characters until a mismatch or end of either string
            while (j < min(prefix.length(), strs[i].length())) {
                if (prefix[j] != strs[i][j]) {
                    break;
                }
                j++;
            }
            // Shorten prefix to the matched length
            prefix = prefix.substr(0, j);

            if (prefix.empty()) break; // No common prefix
        }
        return prefix;
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<string> strs1 = {"flower", "flow", "flight"};
 *     vector<string> strs2 = {"dog", "racecar", "car"};
 *
 *     Solution sol;
 *     cout << sol.longestCommonPrefix(strs1) << endl; // Output: "fl"
 *     cout << sol.longestCommonPrefix(strs2) << endl; // Output: ""
 *
 *     return 0;
 * }
 * ============================================================================== */

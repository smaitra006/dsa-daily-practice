#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Minimum Insertions to Make a String Palindrome
// Task: Find the minimum number of insertions needed to make a given string a palindrome.
// Approach:
//   - The minimum insertions = length of string - LCS(s, reverse(s)).
//   - Compute Longest Common Subsequence (LCS) between original string and its reverse.
//   - Answer = n - LCS.
// Complexity:
//   - Time: O(n^2)
//   - Space: O(n^2)
//==============================================================================

class Solution {
public:
    int minInsertions(string s)
    {
        string s1 = s;                  // Original string
        string s2 = s;
        reverse(s2.begin(), s2.end());  // Reverse of string

        int n = s1.length();

        // DP table for LCS computation
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];  // Characters match
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);  // Skip one char
                }
            }
        }

        // Minimum insertions = n - LCS(s, reverse(s))
        return n - dp[n][n];
    }
};

#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LONGEST STRING CHAIN (Leetcode 1048)
 * ================================================================
 *
 * Problem:
 * --------
 * You are given a list of words. A word A is a predecessor of word B
 * if you can add **exactly one character** anywhere in A to make B.
 * Find the length of the longest possible chain.
 *
 * Observation:
 * ------------
 * This is a variation of Longest Increasing Subsequence, where
 * instead of numeric comparisons, we check if word1 is a valid
 * predecessor of word2.
 *
 * Recurrence:
 * -----------
 * If word[j] is a predecessor of word[i], then:
 *   dp[i] = max(dp[i], 1 + dp[j])
 *
 * TIME COMPLEXITY: O(n^2 * k) where k is avg word length
 * SPACE COMPLEXITY: O(n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * isPred(): Check if word1 is a valid predecessor of word2
     * --------------------------------------------------------------- */
    bool isPred(const string& word1, const string& word2)
    {
        int m = word1.length(), n = word2.length();
        if (n - m != 1) return false;

        int i = 0, j = 0;
        while (i < m && j < n) {
            if (word1[i] == word2[j]) i++;
            j++;
        }

        return i == m;
    }

    static bool lambda(const string& a, const string& b)
    {
        return a.length() < b.length();
    }

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n * k)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int prev, vector<string>& words)
    {
        if (i == words.size()) return 0;

        int notTake = recur(i + 1, prev, words);
        int take = 0;
        if (prev == -1 || isPred(words[prev], words[i]))
            take = 1 + recur(i + 1, i, words);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n^2 * k)
     * SPACE: O(n^2) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int prev, vector<string>& words, vector<vector<int>>& dp)
    {
        if (i == words.size()) return 0;
        if (dp[i][prev + 1] != -1) return dp[i][prev + 1];

        int notTake = memo(i + 1, prev, words, dp);
        int take = 0;
        if (prev == -1 || isPred(words[prev], words[i]))
            take = 1 + memo(i + 1, i, words, dp);

        return dp[i][prev + 1] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n^2 * k)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int tabulation(vector<string>& words)
    {
        int n = words.size();
        sort(words.begin(), words.end(), lambda);
        vector<int> dp(n, 1);
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (isPred(words[j], words[i])) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Optimized Tabulation (Final version)
     * TIME: O(n^2 * k)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int longestStrChain(vector<string>& words)
    {
        int n = words.size();
        sort(words.begin(), words.end(), lambda);

        vector<int> dp(n, 1);
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (isPred(words[j], words[i])) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }
};

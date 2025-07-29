#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * LONGEST CHAIN OF PAIRS (Leetcode 646)
 * ================================================================
 *
 * Problem:
 * --------
 * You are given `n` pairs where each pair[i] = [a, b].
 * A pair [c, d] can follow [a, b] if b < c.
 * Return the length of the longest chain you can form.
 *
 * Observation:
 * ------------
 * This is similar to Longest Increasing Subsequence.
 * Sort the pairs by first element, and use DP or Greedy to find
 * the maximum chain length where each next pair starts after the
 * current pair ends.
 *
 * Recurrence:
 * -----------
 * dp[i] = max over all j < i such that pairs[j][1] < pairs[i][0]
 *
 * TIME COMPLEXITY:
 * - Recursion/Memoization: O(n^2)
 * - Tabulation: O(n^2)
 * - Greedy: O(n log n)
 *
 * SPACE COMPLEXITY:
 * - O(n^2) or O(n)
 */

class Solution {
public:

    /* ---------------------------------------------------------------
     * METHOD 1: Recursion (TLE)
     * TIME: O(2^n)
     * SPACE: O(n) recursive stack
     * --------------------------------------------------------------- */
    int recur(int i, int prev, vector<vector<int>>& pairs)
    {
        if (i == pairs.size()) return 0;

        int notTake = recur(i + 1, prev, pairs);
        int take = 0;
        if (prev == -1 || pairs[i][0] > pairs[prev][1])
            take = 1 + recur(i + 1, i, pairs);

        return max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n^2)
     * SPACE: O(n^2) + O(n) stack
     * --------------------------------------------------------------- */
    int memo(int i, int prev, vector<vector<int>>& pairs, vector<vector<int>>& dp)
    {
        if (i == pairs.size()) return 0;
        if (dp[i][prev + 1] != -1) return dp[i][prev + 1];

        int notTake = memo(i + 1, prev, pairs, dp);
        int take = 0;
        if (prev == -1 || pairs[i][0] > pairs[prev][1])
            take = 1 + memo(i + 1, i, pairs, dp);

        return dp[i][prev + 1] = max(take, notTake);
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n^2)
     * SPACE: O(n)
     * --------------------------------------------------------------- */
    int tabulation(vector<vector<int>>& pairs)
    {
        int n = pairs.size();
        sort(pairs.begin(), pairs.end());
        vector<int> dp(n, 1);
        int maxChain = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxChain = max(maxChain, dp[i]);
        }

        return maxChain;
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Greedy (Optimized)
     * TIME: O(n log n)
     * SPACE: O(1)
     * --------------------------------------------------------------- */
    int findLongestChain(vector<vector<int>>& pairs)
    {
        sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
            return a[1] < b[1];  // sort by ending time (greedy)
            });

        int chainLength = 0;
        int currEnd = INT_MIN;

        for (auto& p : pairs) {
            if (p[0] > currEnd) {
                chainLength++;
                currEnd = p[1];
            }
        }

        return chainLength;
    }
};

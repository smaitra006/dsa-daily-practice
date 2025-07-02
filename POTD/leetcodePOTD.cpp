// LeetCode POTD Questions

#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 3330: FIND THE ORIGINAL TYPED STRING I (LeetCode)
 * =================================================================== */

/**
 * @brief Return the total number of possible original strings
 *
 * PROBLEM STATEMENT:
 * Alice typed a string `word` on her keyboard. She may have pressed at most
 * one key for **too long**, causing a character to repeat one or more times.
 *
 * You are given the final string `word`. Determine how many **possible original
 * strings** Alice could have intended to type.
 *
 * A character group of repeated characters could be reduced to just one character
 * (only one group can be reduced in total).
 *
 * EXAMPLE:
 * Input:  word = "aaab"
 * Output: 3
 * Explanation: Alice may have intended to type "aab", "ab", or "aaab".
 *
 * APPROACH:
 * - Traverse the string and identify groups of consecutive identical characters.
 * - Each such group (of length > 1) is a candidate for being the *long press* group.
 * - Only one group can be reduced — total possible original strings = number of such groups + 1
 *   (1 for the case where Alice didn't long press at all).
 *
 * STRATEGY:
 * - Initialize `possible = 1` for the no-long-press case.
 * - For each index `i`, if word[i] == word[i-1], it is part of a long-press group.
 *   Increment `possible` for each group (counted only once per group).
 *
 * @param word The final typed string shown on screen
 * @return int Total number of possible original strings
 *
 * @complexity
 * Time: O(N) — single traversal of the string
 * Space: O(1) — constant extra space
 */

 class Solution {
    public:
        int numberOfPossibleOriginalStrings(string word) {
            int possible = 1;  // No long-press case is always valid

            for (int i = 1; i < word.size(); i++) {
                // If a new long-press group starts
                if (word[i] == word[i - 1]) {
                    possible++;
                }
            }

            return possible;
        }
    };

/* ===================================================================
 * PROBLEM 3333: FIND THE ORIGINAL TYPED STRING II (LeetCode)
 * =================================================================== */

/**
 * @brief Count total possible original strings given final string and length constraint
 *
 * PROBLEM STATEMENT:
 * Alice was trying to type a string, but she may have pressed a key for too long,
 * causing some characters to repeat. She did this clumsily at most once per character group.
 *
 * You're given:
 * - `word`: the final typed string (may contain long presses)
 * - `k`: the minimum length of the original string
 *
 * Return the number of possible original strings Alice could have intended to type
 * that are of length at least `k`. Since the result may be large, return it modulo 1e9+7.
 *
 * EXAMPLE:
 * Input:  word = "aaabb", k = 2
 * Output: 5
 * Explanation: All possible compressed combinations of length ≥ 2 are counted.
 *
 * APPROACH:
 * - First, break `word` into consecutive character groups (e.g., "aaabb" → [3,2]).
 * - For each group of length `g`, we can choose to reduce it to size `1` through `g`.
 * - So, total possible combinations = product of sizes of all groups.
 *
 * - However, we must subtract those combinations where the final compressed string
 *   has length less than `k`.
 *
 * STRATEGY:
 * - Use DP to count the number of ways to compress groups such that resulting length < k.
 * - Use prefix sum technique within DP for efficiency.
 * - Subtract invalid counts from total.
 *
 * @param word The final typed string (after clumsy typing)
 * @param k Minimum required length of original string
 * @return int Total number of valid original strings modulo 1e9+7
 *
 * @complexity
 * Time:  O(N * k) — where N = number of character groups in `word`
 * Space: O(k) — dynamic programming with space optimization
 */

 class Solution {
    public:
        const int MOD = 1e9 + 7;

        int possibleStringCount(string word, int k) {
            if (word.empty()) return 0;

            // Step 1: Break the string into consecutive character groups
            vector<int> groups;
            int count = 1;

            for (int i = 1; i < word.size(); i++) {
                if (word[i] == word[i - 1])
                    count++;
                else {
                    groups.push_back(count);
                    count = 1;
                }
            }
            groups.push_back(count);  // Add last group

            // Step 2: Calculate total possible combinations
            long total = 1;
            for (int g : groups) {
                total = (total * g) % MOD;
            }

            // Step 3: If k is more than max possible original string length, it's invalid
            if (k > groups.size()) {
                // DP[s]: Number of ways to get a compressed string of length s
                vector<int> dp(k, 0);
                dp[0] = 1;

                for (int g : groups) {
                    vector<int> new_dp(k, 0);
                    long sum = 0;

                    for (int s = 0; s < k; s++) {
                        if (s > 0)
                            sum = (sum + dp[s - 1]) % MOD;
                        if (s > g)
                            sum = (sum - dp[s - g - 1] + MOD) % MOD;

                        new_dp[s] = sum;
                    }

                    dp = new_dp;
                }

                // Step 4: Sum all invalid cases with length < k
                long invalid = 0;
                for (int s = groups.size(); s < k; s++) {
                    invalid = (invalid + dp[s]) % MOD;
                }

                // Final result = total - invalid
                return (total - invalid + MOD) % MOD;
            }

            return total;
        }
    };


#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Decode Ways II (Leetcode 639)
// Task: Given a string s containing digits and '*' characters, return the
//       number of ways to decode it modulo 1e9+7.
//
// Key Points:
// - '*' can represent digits '1' to '9'.
// - Must handle both single-digit and two-digit decoding cases.
// - Requires modular arithmetic due to large numbers.
//
// Approaches Covered:
// 1. Recursion (Exponential, TLE for large inputs)
// 2. Memoization (Top-Down DP)
// 3. Tabulation (Bottom-Up DP)
// 4. Space Optimization (O(1) Space)
//
// Time Complexity:
// - Recursion: O(2^n) (exponential, not feasible)
// - Memoization: O(n)
// - Tabulation: O(n)
// - Space Optimized: O(n) time, O(1) space
//==============================================================================

class Solution {
    using ll = long long;
    const int MOD = 1e9 + 7;

    //==============================================================================
    // 1. Recursion (Brute Force) - Exponential
    //==============================================================================
    ll recur(string& s, int pos)
    {
        if (pos < 0) return 1;

        ll ans = 0;
        if (s[pos] == '*') {
            ans = (ans + 9 * recur(s, pos - 1)) % MOD;
            if (pos > 0 && s[pos - 1] == '1') ans = (ans + 9 * recur(s, pos - 2)) % MOD;
            else if (pos > 0 && s[pos - 1] == '2') ans = (ans + 6 * recur(s, pos - 2)) % MOD;
            else if (pos > 0 && s[pos - 1] == '*') ans = (ans + 15 * recur(s, pos - 2)) % MOD;
        }
        else {
            ans = (s[pos] == '0' ? 0 : recur(s, pos - 1)) % MOD;
            if (pos > 0) {
                if (s[pos - 1] == '1') ans = (ans + recur(s, pos - 2)) % MOD;
                else if (s[pos - 1] == '2' && s[pos] <= '6') ans = (ans + recur(s, pos - 2)) % MOD;
                else if (s[pos - 1] == '*') {
                    ans = (ans + ((s[pos] <= '6' ? 2 : 1) * recur(s, pos - 2)) % MOD) % MOD;
                }
            }
        }
        return ans;
    }

    //==============================================================================
    // 2. Memoization (Top-Down DP)
    //==============================================================================
    ll memo(string& s, int pos, vector<int>& dp)
    {
        if (pos < 0) return 1;
        if (dp[pos] != -1) return dp[pos];

        ll ans = 0;
        if (s[pos] == '*') {
            ans = (ans + 9 * memo(s, pos - 1, dp)) % MOD;
            if (pos > 0 && s[pos - 1] == '1') ans = (ans + 9 * memo(s, pos - 2, dp)) % MOD;
            else if (pos > 0 && s[pos - 1] == '2') ans = (ans + 6 * memo(s, pos - 2, dp)) % MOD;
            else if (pos > 0 && s[pos - 1] == '*') ans = (ans + 15 * memo(s, pos - 2, dp)) % MOD;
        }
        else {
            ans = (s[pos] == '0' ? 0 : memo(s, pos - 1, dp)) % MOD;
            if (pos > 0) {
                if (s[pos - 1] == '1') ans = (ans + memo(s, pos - 2, dp)) % MOD;
                else if (s[pos - 1] == '2' && s[pos] <= '6') ans = (ans + memo(s, pos - 2, dp)) % MOD;
                else if (s[pos - 1] == '*') {
                    ans = (ans + ((s[pos] <= '6' ? 2 : 1) * memo(s, pos - 2, dp)) % MOD) % MOD;
                }
            }
        }
        return dp[pos] = ans;
    }

    //==============================================================================
    // 3. Tabulation (Bottom-Up DP)
    //==============================================================================
    ll tabulation(string& s)
    {
        int n = s.size();
        vector<ll> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = (s[0] == '*') ? 9 : (s[0] == '0' ? 0 : 1);

        for (int i = 2; i <= n; i++) {
            char curr = s[i - 1];
            char prev = s[i - 2];

            // Single digit
            if (curr == '*') dp[i] = (dp[i] + 9 * dp[i - 1]) % MOD;
            else if (curr != '0') dp[i] = (dp[i] + dp[i - 1]) % MOD;

            // Two digits
            if (prev == '1') {
                if (curr == '*') dp[i] = (dp[i] + 9 * dp[i - 2]) % MOD;
                else dp[i] = (dp[i] + dp[i - 2]) % MOD;
            }
            else if (prev == '2') {
                if (curr == '*') dp[i] = (dp[i] + 6 * dp[i - 2]) % MOD;
                else if (curr <= '6') dp[i] = (dp[i] + dp[i - 2]) % MOD;
            }
            else if (prev == '*') {
                if (curr == '*') dp[i] = (dp[i] + 15 * dp[i - 2]) % MOD;
                else dp[i] = (dp[i] + ((curr <= '6' ? 2 : 1) * dp[i - 2]) % MOD) % MOD;
            }
        }
        return dp[n];
    }

    //==============================================================================
    // 4. Space Optimized (Only keep last two states)
    //==============================================================================
    ll spaceOptimized(string& s)
    {
        int n = s.size();
        ll prev2 = 1;
        ll prev1 = (s[0] == '*') ? 9 : (s[0] == '0' ? 0 : 1);

        for (int i = 2; i <= n; i++) {
            char curr = s[i - 1];
            char prev = s[i - 2];
            ll currVal = 0;

            // Single digit
            if (curr == '*') currVal = (currVal + 9 * prev1) % MOD;
            else if (curr != '0') currVal = (currVal + prev1) % MOD;

            // Two digits
            if (prev == '1') {
                if (curr == '*') currVal = (currVal + 9 * prev2) % MOD;
                else currVal = (currVal + prev2) % MOD;
            }
            else if (prev == '2') {
                if (curr == '*') currVal = (currVal + 6 * prev2) % MOD;
                else if (curr <= '6') currVal = (currVal + prev2) % MOD;
            }
            else if (prev == '*') {
                if (curr == '*') currVal = (currVal + 15 * prev2) % MOD;
                else currVal = (currVal + ((curr <= '6' ? 2 : 1) * prev2) % MOD) % MOD;
            }

            prev2 = prev1;
            prev1 = currVal;
        }
        return prev1;
    }

public:
    int numDecodings(string s)
    {
        int n = s.size();
        if (s[0] == '0') return 0;

        // ======= Choose one method =======
        // return recur(s, n - 1);                  // Method 1: Recursion (TLE)
        vector<int> dp(n, -1);
        // return memo(s, n - 1, dp);              // Method 2: Memoization
        // return tabulation(s);                   // Method 3: Tabulation
        return spaceOptimized(s);                  // Method 4: Space Optimization
    }
};


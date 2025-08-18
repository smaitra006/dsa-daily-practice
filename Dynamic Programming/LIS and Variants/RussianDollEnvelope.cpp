#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Russian Doll Envelopes (LeetCode 354)
// Task: You are given envelopes represented by (width, height).
//       One envelope can fit into another if both width and height are strictly larger.
//       Return the maximum number of envelopes you can Russian doll (nest).
//
// Key Observations:
//   - Classic "Longest Increasing Subsequence (LIS)" problem in 2D.
//   - Sorting strategy:
//       • Sort by width ascending
//       • If widths are equal, sort by height descending (to avoid false nesting)
//   - After sorting, problem reduces to finding LIS on heights.
//
// Approach:
//   1. Sort envelopes as above
//   2. Apply LIS on heights using patience sorting + binary search
//      (lower_bound ensures O(N log N))
//
// Complexity:
//   - Time: O(N log N) [sorting + LIS with binary search]
//   - Space: O(N)
//==============================================================================

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes)
    {
        // Step 1: Sort by width ascending, height descending for ties
        sort(envelopes.begin(), envelopes.end(),
            [&](const vector<int>& a, const vector<int>& b) {
                if (a[0] == b[0]) return a[1] > b[1];
                return a[0] < b[0];
            });

        // Step 2: Find LIS on heights
        vector<int> lis;  // stores increasing sequence of heights
        for (auto& env : envelopes) {
            int h = env[1];
            auto it = lower_bound(lis.begin(), lis.end(), h);
            if (it == lis.end()) {
                lis.push_back(h);  // extend LIS
            }
            else {
                *it = h;           // replace to maintain smallest possible values
            }
        }
        return lis.size();
    }
};

//==============================================================================
// Example Usage:
//
// Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
// Sorted: [[2,3],[5,4],[6,7],[6,4]]
// LIS on heights = [3,4,7]
// Output: 3
//==============================================================================


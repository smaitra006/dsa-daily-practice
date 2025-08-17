#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Number of Longest Increasing Subsequence (LeetCode 673)
// Task: Given an integer array nums, return the number of longest increasing
//       subsequences (LIS).
//
// Key Observations:
//   - Each element contributes to LIS in two ways:
//       (1) It extends a smaller LIS ending before it
//       (2) It starts a new LIS of length 1
//   - Maintain two arrays:
//       lis[i]   → length of LIS ending at i
//       count[i] → number of LIS of that length ending at i
//   - Final answer = sum of counts of all subsequences that reach max LIS length
//
// Approach:
//   - O(N^2) DP: For each i, check all j < i
//   - If nums[i] > nums[j]:
//         • If lis[j] + 1 > lis[i], update lis[i] and reset count[i]
//         • If lis[j] + 1 == lis[i], increment count[i]
//   - Track max LIS length while building
//
// Complexity:
//   - Time: O(N^2)
//   - Space: O(N)
//==============================================================================

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0) return 0;

        vector<int> lis(n, 1);    // length of LIS ending at i
        vector<int> count(n, 1);  // number of LIS of length lis[i]
        int maxLen = 1;

        // Build LIS lengths and counts
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (lis[j] + 1 > lis[i]) {
                        lis[i] = lis[j] + 1;
                        count[i] = count[j];  // inherit count from j
                    }
                    else if (lis[j] + 1 == lis[i]) {
                        count[i] += count[j]; // accumulate ways
                    }
                }
            }
            maxLen = max(maxLen, lis[i]);
        }

        // Count number of subsequences with length = maxLen
        int numOfLIS = 0;
        for (int i = 0; i < n; i++) {
            if (lis[i] == maxLen) {
                numOfLIS += count[i];
            }
        }

        return numOfLIS;
    }
};

//==============================================================================
// Example Usage:
//
// Input: nums = [1,3,5,4,7]
// LIS = [1,3,4,7] and [1,3,5,7] → both length 4
// Output: 2
//==============================================================================

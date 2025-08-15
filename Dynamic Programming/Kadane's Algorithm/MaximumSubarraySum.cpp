#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  Problem: Maximum Subarray (Kadane's Algorithm)
//  Task: Find the contiguous subarray with the largest sum in an integer array.
//
//  Approach:
//  - Initialize sum = 0, maxSum = INT_MIN.
//  - Iterate through the array:
//      - If sum < 0, reset sum to 0 (start new subarray).
//      - Add current element to sum.
//      - Update maxSum with the maximum of itself and sum.
//  - Return maxSum as the answer.
//
//  Time Complexity: O(n)   -> Single pass through the array
//  Space Complexity: O(1)  -> Constant extra space
//  NOTE : Resetting sum = 0 should be done first to handle all negative numbers case
// ============================================================================

class Solution {
public:
    int maxSubArray(vector<int>& nums)
    {
        int sum = 0;               // Running sum of current subarray
        int maxSum = INT_MIN;      // Best sum found so far

        for (int i = 0; i < nums.size(); i++) {
            if (sum < 0) {
                sum = 0;           // Reset sum if it drops below zero
            }
            sum += nums[i];        // Extend the current subarray
            maxSum = max(maxSum, sum); // Update maximum sum found
        }

        return maxSum;
    }
};

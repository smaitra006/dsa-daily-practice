#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  Problem: Maximum Sum Circular Subarray
//  Task: Find the maximum subarray sum in a circular integer array.
//
//  Approach:
//  1. Normal Maximum Subarray (Kadane's Algorithm):
//     - Finds the max sum in a standard non-circular array.
//
//  2. Circular Case:
//     - The maximum sum for a circular array can be thought of as:
//       totalSum - (minimum subarray sum in non-circular form)
//     - This effectively chooses the "wrap-around" elements.
//
//  3. Edge Case:
//     - If all elements are negative, the normal max sum is the answer.
//
//  Time Complexity: O(n)   -> Two Kadane passes (max and min sum) + sum
//  Space Complexity: O(1)  -> Constant extra space
// ============================================================================

class Solution {
public:
    // ------------------------------------------------------------------------
    // Helper: Maximum subarray sum (Kadane's Algorithm)
    // ------------------------------------------------------------------------
    int maxSum(vector<int>& nums)
    {
        int sum = 0;
        int maxSum = INT_MIN;

        for (int num : nums) {
            sum = max(sum + num, num);   // Extend or restart subarray
            maxSum = max(sum, maxSum);   // Update best sum
        }
        return maxSum;
    }

    // ------------------------------------------------------------------------
    // Helper: Minimum subarray sum (Modified Kadane's Algorithm)
    // ------------------------------------------------------------------------
    int minSum(vector<int>& nums)
    {
        int sum = 0;
        int minSum = INT_MAX;

        for (int num : nums) {
            sum = min(sum + num, num);   // Extend or restart subarray
            minSum = min(sum, minSum);   // Update best (minimum) sum
        }
        return minSum;
    }

    // ------------------------------------------------------------------------
    // Main Function: Maximum sum in circular array
    // ------------------------------------------------------------------------
    int maxSubarraySumCircular(vector<int>& nums)
    {
        int total = accumulate(nums.begin(), nums.end(), 0);

        int sumNormal = maxSum(nums);       // Non-circular case
        int sumCircular = total - minSum(nums); // Circular case

        // If all numbers are negative, circular case becomes invalid
        if (sumNormal < 0) return sumNormal;

        return max(sumNormal, sumCircular);
    }
};


#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Maximum Subarray (Leetcode 53)
 *
 * Given an integer array `nums`, find the contiguous subarray
 * (containing at least one number) which has the largest sum and return its sum.
 *
 * Approach: Kadane’s Algorithm
 * - Iterate through the array while maintaining:
 *   → curr_sum: maximum subarray sum ending at current index
 *   → max_sum: global maximum of all such curr_sum values
 * - If curr_sum drops below 0, reset it (no point carrying forward negative sum)
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(1)
 * ============================================================================== */

class Solution {
public:
    int maxSubArray(vector<int>& nums)
    {
        int curr_sum = 0;               // Current subarray sum
        int max_sum = INT_MIN;          // Global max subarray sum

        for (int i = 0; i < nums.size(); i++) {
            curr_sum += nums[i];                    // Add current element
            max_sum = max(max_sum, curr_sum);       // Update global max
            if (curr_sum <= 0) curr_sum = 0;        // Reset if sum becomes negative
        }

        return max_sum;
    }
};


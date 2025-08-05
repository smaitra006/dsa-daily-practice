#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Maximum Subarray with Printing Subarray (Leetcode 53 extended)
 *
 * Task:
 * - Return the contiguous subarray which has the largest sum.
 * - Also print the subarray that gives this maximum sum.
 *
 * Approach: Extended Kadane’s Algorithm
 * - Maintain variables to track:
 *   → curr_sum : Sum of current subarray
 *   → max_sum  : Maximum sum found so far
 *   → start    : Start index of current subarray
 *   → ans_start & ans_end : Final subarray range for max sum
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(1)
 * ============================================================================== */

class Solution {
public:
    int maxSubArray(vector<int>& nums)
    {
        int n = nums.size();
        int curr_sum = 0;
        int max_sum = INT_MIN;

        int start = 0;          // Start index for current subarray
        int ans_start = 0;      // Start index for result subarray
        int ans_end = 0;        // End index for result subarray

        for (int i = 0; i < n; i++) {
            curr_sum += nums[i];

            if (curr_sum > max_sum) {
                max_sum = curr_sum;
                ans_start = start;
                ans_end = i;
            }

            if (curr_sum < 0) {
                curr_sum = 0;
                start = i + 1;  // Start a new subarray from next index
            }
        }

        // Print the subarray with max sum
        cout << "Subarray with maximum sum: [ ";
        for (int i = ans_start; i <= ans_end; i++) {
            cout << nums[i] << " ";
        }
        cout << "]" << endl;

        return max_sum;
    }
};

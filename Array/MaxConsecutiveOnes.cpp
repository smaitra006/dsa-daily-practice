#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 485: Max Consecutive Ones
 * ==============================================================================
 * Problem:
 * Given a binary array `nums`, return the maximum number of consecutive 1s
 * in the array.
 *
 * Approach: Simple Linear Scan
 * - Traverse the array and count the current streak of 1s.
 * - Reset the counter whenever a 0 is encountered.
 * - Track the maximum streak length throughout.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums)
    {
        int count = 0;
        int maxCount = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                count++;
                maxCount = max(maxCount, count);
            }
            else {
                count = 0;
            }
        }

        return maxCount;
    }
};


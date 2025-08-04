#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 1752: Check if Array Is Sorted and Rotated
 * ==============================================================================
 * Problem:
 * Given a circular array `nums`, check if it can become non-decreasing by rotating
 * it some number of times (possibly zero). Return true if it satisfies the condition.
 *
 * Approach: Count Rotation Breaks
 * - Traverse the array and count how many times the current element is greater than the next.
 * - If this happens more than once, it cannot be a sorted rotated array.
 * - Use modulo to simulate the circular nature of the array.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    bool check(vector<int>& nums)
    {
        int n = nums.size();
        int count = 0;

        // Count number of "drops" in the circular array
        for (int i = 0; i < n; ++i) {
            if (nums[i] > nums[(i + 1) % n]) {
                count++;
            }
        }

        return count <= 1;
    }
};


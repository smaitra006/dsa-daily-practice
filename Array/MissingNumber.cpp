#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 268: Missing Number
 * ==============================================================================
 * Problem:
 * Given an array `nums` containing `n` distinct numbers in the range [0, n],
 * return the one number that is missing from the array.
 *
 * Approach: Sum Formula (Gauss' Formula)
 * - The sum of numbers from 0 to n is (n * (n + 1)) / 2.
 * - Subtract the actual sum of the array from this total.
 * - The difference is the missing number.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    int missingNumber(vector<int>& nums)
    {
        int n = nums.size();
        int total = (n * (n + 1)) / 2;

        int sum = accumulate(nums.begin(), nums.end(), 0);

        return total - sum;
    }
};

#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Two Sum II – Input Array Is Sorted
 *
 * Task:
 * - Given a 1-indexed array of integers `numbers` that is already sorted in
 *   non-decreasing order, find two numbers such that they add up to a specific
 *   target number.
 * - Return the indices of the two numbers (1-based).
 *
 * Approach: Two Pointers
 * - Start with two pointers: `i` at the beginning, `j` at the end.
 * - If sum < target → increment `i`
 * - If sum > target → decrement `j`
 * - Else, found the pair.
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(1)
 * ============================================================================== */

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int i = 0;
        int j = numbers.size() - 1;

        while (i < j) {
            int sum = numbers[i] + numbers[j];

            if (sum == target) {
                // Return 1-based indices
                return { i + 1, j + 1 };
            }
            else if (sum < target) {
                i++; // Need a bigger sum
            }
            else {
                j--; // Need a smaller sum
            }
        }

        // Should never reach here if a valid answer exists
        return { -1, -1 };
    }
};


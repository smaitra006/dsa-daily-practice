/* ==============================================================================
 * Problem: Contains Duplicate
 *
 * Task:
 * - Given an integer array `nums`, determine if any value appears at least twice.
 * - Return `true` if there are duplicates, otherwise return `false`.
 *
 * Approach:
 * 1. Sort the array.
 * 2. Scan through adjacent elements; if any two are equal → duplicate exists.
 *
 * Time Complexity  : O(n log n) — Sorting the array dominates.
 * Space Complexity : O(1)       — In-place sort, no extra significant space used.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums)
    {
        sort(begin(nums), end(nums));  // Sort array to bring duplicates together
        int n = nums.size();

        // Check adjacent elements for equality
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                return true;  // Found duplicate
            }
        }
        return false;  // No duplicates found
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> nums = {1, 2, 3, 1};
 *     Solution sol;
 *     cout << boolalpha << sol.containsDuplicate(nums) << endl; // Output: true
 *
 *     nums = {1, 2, 3, 4};
 *     cout << boolalpha << sol.containsDuplicate(nums) << endl; // Output: false
 *
 *     return 0;
 * }
 * ============================================================================== */

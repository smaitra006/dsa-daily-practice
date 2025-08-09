/* ==============================================================================
 * Problem: Concatenate Array
 *
 * Task:
 * - Given an integer array `nums` of length `n`,
 *   create a new array `ans` of length `2 * n` where:
 *       ans[i]     = nums[i]
 *       ans[i + n] = nums[i]
 * - Return the resulting array.
 *
 * Approach:
 * - Initialize a result array of size `2 * n`.
 * - Fill the first half with the original array elements.
 * - Fill the second half with the same elements again.
 *
 * Time Complexity  : O(n) — Single pass over the array.
 * Space Complexity : O(n) — Extra array of size `2 * n`.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> result(2 * n);  // Allocate space for 2 * n elements

        // Fill both halves
        for (int i = 0; i < n; i++) {
            result[i] = nums[i];      // First half
            result[i + n] = nums[i];  // Second half
        }
        return result;
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> nums = {1, 2, 1};
 *     Solution sol;
 *     vector<int> ans = sol.getConcatenation(nums);
 *
 *     // Output: 1 2 1 1 2 1
 *     for (int x : ans) cout << x << " ";
 *     cout << endl;
 *
 *     return 0;
 * }
 * ============================================================================== */

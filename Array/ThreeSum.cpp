#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 15. 3Sum (Leetcode)
 *
 * Task:
 * - Find all unique triplets in the array which gives the sum of zero.
 * - Triplets must be unique and in non-descending order.
 *
 * Approach: Two-pointer technique after fixing the first element
 * - Sort the array.
 * - Iterate through the array and fix one number.
 * - Use two pointers (`i`, `j`) to find pairs such that: nums[fixed] + nums[i] + nums[j] == 0
 * - Skip duplicates while fixing and while scanning with two pointers.
 *
 * Time Complexity  : O(n^2)
 * Space Complexity : O(1)  (excluding the output vector)
 * ============================================================================== */

class Solution {
public:

    // Helper function to find valid triplets for a fixed index
    void solve(vector<int>& nums, int fixedIndex, vector<vector<int>>& result)
    {
        int num1 = nums[fixedIndex];
        int i = fixedIndex + 1;
        int j = nums.size() - 1;

        while (i < j) {
            int sum = num1 + nums[i] + nums[j];

            if (sum == 0) {
                result.push_back({ num1, nums[i], nums[j] });
                i++;
                j--;

                // Skip duplicates
                while (i < j && nums[i] == nums[i - 1]) i++;
                while (i < j && nums[j] == nums[j + 1]) j--;
            }
            else if (sum < 0) {
                i++;  // Need a larger sum
            }
            else {
                j--;  // Need a smaller sum
            }
        }
    }

    // Main function to find all unique triplets
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());  // Sort to use two-pointer technique
        int n = nums.size();
        vector<vector<int>> result;

        for (int i = 0; i < n - 2; i++) {
            // Skip duplicate fixed elements
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            solve(nums, i, result);
        }

        return result;
    }
};

#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 16. 3Sum Closest (Leetcode)
 *
 * Task:
 * - Given an integer array nums and a target integer target,
 *   find three integers in nums such that the sum is closest to target.
 * - Return the sum of the three integers.
 *
 * Approach: Sorting + Two Pointers
 * - Sort the array to allow two-pointer traversal.
 * - Fix one number and use two pointers to find the closest sum.
 * - Update the result whenever a closer sum is found.
 *
 * Time Complexity  : O(n^2)  (n = size of nums)
 * Space Complexity : O(1)    (only variables used, no extra structures)
 * ============================================================================== */

class Solution
{
public:
  int threeSumClosest(vector<int> &nums, int target)
  {
    sort(nums.begin(), nums.end()); // Sort array for two-pointer logic

    // Initialize result with the sum of the first three elements
    int result = nums[0] + nums[1] + nums[2];

    // Iterate fixing one number at a time
    for (int i = 0; i < nums.size() - 2; i++)
    {
      int left = i + 1;
      int right = nums.size() - 1;

      while (left < right)
      {
        int sum = nums[i] + nums[left] + nums[right];

        // Update result if this sum is closer to target
        if (abs(target - sum) < abs(target - result))
        {
          result = sum;
        }

        // Move pointers based on comparison
        if (sum == target)
        {
          return target; // Perfect match found
        }
        else if (sum < target)
        {
          left++;
        }
        else
        {
          right--;
        }
      }
    }

    return result;
  }
};

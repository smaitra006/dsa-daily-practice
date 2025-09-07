#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Remove Duplicates from Sorted Array II (LeetCode 80)
//
// Task:
// Given a sorted array `nums`, remove duplicates in-place such that each unique
// element appears at most twice. The relative order of elements should remain
// the same. Return the new length `k` of the modified array.
//
// Key Observations:
// - The array is sorted, so duplicates are always consecutive.
// - We can allow at most 2 occurrences of each element.
// - If the current number is different from the element at index `k - 2`,
//   it means we can safely include it in the result.
//
// Approach:
// 1. If the size of nums ≤ 2, return its size (all elements allowed).
// 2. Use index `k` as the position to insert the next valid element.
// 3. Iterate from index 2 onward:
//    - If nums[i] != nums[k - 2], it means nums[i] can be placed at nums[k].
//    - Increment k accordingly.
// 4. Return k as the new length.
//
//==============================================================================

class Solution
{
public:
  int removeDuplicates(vector<int> &nums)
  {
    int k = 2; // Allow at most 2 occurrences

    if (nums.size() <= 2)
      return nums.size();

    for (int i = 2; i < nums.size(); i++)
    {
      // Only insert nums[i] if it's not equal to nums[k-2]
      if (nums[i] != nums[k - 2])
      {
        nums[k] = nums[i];
        k++;
      }
    }

    return k;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(n), single pass through nums.
// - Space: O(1), in-place modification with no extra memory.
//
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
vector<int> nums = {0,0,1,1,1,1,2,3,3};
int k = sol.removeDuplicates(nums);
// k = 7, nums = {0,0,1,1,2,3,3,...}
*/

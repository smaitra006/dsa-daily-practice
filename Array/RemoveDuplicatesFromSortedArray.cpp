#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 26: Remove Duplicates from Sorted Array
 * ==============================================================================
 * Problem:
 * Given a sorted array `nums`, remove the duplicates **in-place** such that each
 * element appears only once and return the new length. Do not use extra space.
 *
 * Approach: Two-Pointer Technique
 * - Use pointer `l` to mark the position of the next unique element.
 * - Use pointer `r` to traverse the array.
 * - When `nums[r]` is different from the last placed unique value (`nums[l - 1]`),
 *   place it at position `l` and move both pointers.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int n = nums.size();
        int l = 1, r = 1;

        while (r < n) {
            if (nums[r] != nums[l - 1]) {
                swap(nums[l], nums[r]);  // Place unique value at correct position
                l++;
            }
            r++;
        }

        return l;
    }
};


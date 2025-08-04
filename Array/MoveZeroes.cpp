#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 283: Move Zeroes (Skip + Swap Approach)
 * ==============================================================================
 * Problem:
 * Given an integer array `nums`, move all 0's to the end while maintaining the
 * relative order of non-zero elements. Do this in-place.
 *
 * Approach 1: First-Zero + Right Pointer Swap
 * - Step 1: Find the first zero's position (`l`).
 * - Step 2: Use a second pointer `r` to find the next non-zero.
 * - Swap elements at `l` and `r`, and increment both.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    void moveZeroes(vector<int>& nums)
    {
        int n = nums.size();
        int l = -1;

        // Step 1: Find the first zero
        for (int k = 0; k < n; ++k) {
            if (nums[k] == 0) {
                l = k;
                break;
            }
        }

        if (l == -1) return;  // No zero found

        int r = l + 1;

        while (r < n) {
            while (r < n && nums[r] == 0) {
                r++;  // Skip zeroes
            }

            if (r < n) {
                swap(nums[l], nums[r]);
                l++;
                r++;
            }
        }
    }
};


/* ==============================================================================
 * LeetCode 283: Move Zeroes (Compaction Approach)
 * ==============================================================================
 * Approach 2: Two-Pointer Write + Fill
 * - Use pointer `l` to write the next non-zero element.
 * - Traverse the array with pointer `r`:
 *     - If `nums[r]` is non-zero, write it to `nums[l++]`.
 * - After all non-zeros are placed at the front,
 *   fill the remaining positions with zeroes.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    void moveZeroes(vector<int>& nums)
    {
        int n = nums.size();
        int l = 0;  // Write index

        // Step 1: Move all non-zeroes to the front
        for (int r = 0; r < n; ++r) {
            if (nums[r] != 0) {
                nums[l++] = nums[r];
            }
        }

        // Step 2: Fill remaining positions with zeroes
        while (l < n) {
            nums[l++] = 0;
        }
    }
};


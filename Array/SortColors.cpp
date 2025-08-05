#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Sort Colors (Leetcode 75)
 *
 * Given an array `nums` with `n` objects colored red (0), white (1), or blue (2),
 * sort them in-place so that objects of the same color are adjacent and in the
 * order red → white → blue.
 *
 * Approach: Dutch National Flag Algorithm
 * - Use three pointers:
 *     i → for 0s (red)
 *     j → current index
 *     k → for 2s (blue)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================== */

class Solution {
public:
    void sortColors(vector<int>& nums)
    {
        int n = nums.size();
        int i = 0;        // Pointer for next position of 0
        int j = 0;        // Current index
        int k = n - 1;    // Pointer for next position of 2

        while (j <= k) {
            if (nums[j] == 0) {
                swap(nums[i], nums[j]);
                i++;
                j++;
            }
            else if (nums[j] == 2) {
                swap(nums[j], nums[k]);
                k--;
                // Do not increment j here, as the swapped value needs to be checked
            }
            else {
                j++;  // nums[j] == 1 → move forward
            }
        }
    }
};

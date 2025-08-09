/* ==============================================================================
 * Problem: Remove Element
 *
 * Task:
 * - Given an integer array `nums` and an integer `val`,
 *   remove all occurrences of `val` in-place.
 * - The order of the remaining elements can be changed.
 * - Return the number of elements `k` after removal.
 * - The first `k` elements of `nums` should contain the elements that are not equal to `val`.
 *
 * Approach:
 * 1. Use a pointer `k` to track the position for the next valid element.
 * 2. Traverse the array:
 *    - If the current element is not `val`, copy it to position `k` and increment `k`.
 * 3. Return `k` as the count of remaining elements.
 *
 * Time Complexity  : O(n) — Single pass over the array.
 * Space Complexity : O(1) — In-place operation.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val)
    {
        int k = 0;  // Position for placing the next valid element

        // Traverse the array
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {      // Found a valid element
                nums[k] = nums[i];     // Place it at the next valid position
                k++;
            }
        }
        return k;  // Number of valid elements
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> nums = {3, 2, 2, 3};
 *     int val = 3;
 *     Solution sol;
 *     int k = sol.removeElement(nums, val);
 *
 *     // Output: k = 2, nums = {2, 2, _, _}
 *     cout << "k = " << k << endl;
 *     for (int i = 0; i < k; i++) cout << nums[i] << " ";
 *     cout << endl;
 *
 *     return 0;
 * }
 * ============================================================================== */

/* ==============================================================================
 * Problem: Minimum Deletions to Remove Minimum and Maximum
 *
 * Task:
 * - Given an integer array `nums`, remove both the minimum and maximum elements
 *   from the array with the least number of deletions.
 * - A deletion means removing an element from either the **front** or the **back**.
 * - Return the minimum number of deletions required.
 *
 * Approach:
 * 1. Find the indices of the minimum and maximum elements.
 * 2. Consider all possible deletion strategies:
 *      a) Remove from the front only.
 *      b) Remove from the back only.
 *      c) Remove from front to min and from back to max.
 *      d) Remove from front to max and from back to min.
 * 3. Return the smallest number of deletions among these strategies.
 *
 * Time Complexity  : O(n) — One pass to find min and max indices, constant work after.
 * Space Complexity : O(1) — No extra space used apart from variables.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Find index of minimum element
    int find_min(vector<int>& nums)
    {
        int k = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[k]) k = i;
        }
        return k;
    }

    // Find index of maximum element
    int find_max(vector<int>& nums)
    {
        int k = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[k]) k = i;
        }
        return k;
    }

public:
    int minimumDeletions(vector<int>& nums)
    {
        int n = nums.size();
        int min_idx = find_min(nums);
        int max_idx = find_max(nums);

        // Calculate possible strategies
        int front_only = max(min_idx, max_idx) + 1;                  // Remove from front
        int back_only = max(n - min_idx, n - max_idx);               // Remove from back
        int front_min_back_max = min_idx + 1 + (n - max_idx);        // Remove min from front, max from back
        int front_max_back_min = max_idx + 1 + (n - min_idx);        // Remove max from front, min from back

        // Return the minimum deletions among all strategies
        return min({ front_only, back_only, front_min_back_max, front_max_back_min });
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> nums = {2, 10, 7, 5, 4, 1, 8, 6};
 *     Solution sol;
 *     cout << sol.minimumDeletions(nums) << endl; // Output: 5
 *
 *     return 0;
 * }
 * ============================================================================== */

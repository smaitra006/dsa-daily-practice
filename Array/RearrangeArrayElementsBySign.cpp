#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Rearrange Array Elements by Sign (Leetcode 2149)
 *
 * Task:
 * - Given an array `nums` of even length.
 * - Rearrange the elements so that:
 *     → Positive and negative integers appear alternately.
 *     → Positive numbers are placed at even indices (0, 2, 4, ...)
 *     → Negative numbers are placed at odd indices (1, 3, 5, ...)
 *
 * Approach:
 * - Use two pointers `i` and `j` for even and odd indices respectively.
 * - Traverse the input array once.
 * - Place positives at `i` and negatives at `j`, incrementing each by 2.
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(n)
 * ============================================================================== */

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> ans(n); // Result array with same size

        int i = 0; // Even index pointer for positives
        int j = 1; // Odd index pointer for negatives

        for (int k = 0; k < n; k++) {
            if (nums[k] > 0) {
                ans[i] = nums[k];
                i += 2;
            }
            else {
                ans[j] = nums[k];
                j += 2;
            }
        }

        return ans;
    }
};


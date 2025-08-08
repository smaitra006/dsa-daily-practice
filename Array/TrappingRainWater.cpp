#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 42. Trapping Rain Water (Leetcode)
 *
 * Task:
 * - Given n non-negative integers representing elevation map bars, compute how much
 *   water can be trapped after raining.
 *
 * Approach: Prefix & Suffix Maximums
 * - Precompute the maximum height to the left of each position.
 * - Precompute the maximum height to the right of each position.
 * - For each position, trapped water = min(maxLeft, maxRight) - height[i]
 * - Sum all trapped water.
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(n)  (can be optimized to O(1) using two pointers)
 * ============================================================================== */

class Solution {
public:
    int trap(vector<int>& height)
    {
        int n = height.size();
        if (n == 0) return 0;

        // Step 1: Compute left maximums
        vector<int> left_greatest(n);
        left_greatest[0] = height[0];
        for (int i = 1; i < n; i++) {
            left_greatest[i] = max(height[i], left_greatest[i - 1]);
        }

        // Step 2: Compute right maximums
        vector<int> right_greatest(n);
        right_greatest[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            right_greatest[i] = max(height[i], right_greatest[i + 1]);
        }

        // Step 3: Calculate trapped water
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(left_greatest[i], right_greatest[i]) - height[i];
        }

        return water;
    }
};


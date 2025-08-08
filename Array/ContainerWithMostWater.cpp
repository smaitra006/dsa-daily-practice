#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 11. Container With Most Water (Leetcode)
 *
 * Task:
 * - You are given an array `height` of length n.
 * - The i-th element represents the height of a vertical line on the x-axis.
 * - Find two lines that together with the x-axis form a container,
 *   such that the container holds the most water.
 *
 * Approach: Two Pointers
 * 1. Start with the widest container (left = 0, right = n-1).
 * 2. Calculate area = min(height[left], height[right]) * (right - left).
 * 3. Move the pointer with the smaller height inward (to try to find a taller line).
 * 4. Repeat until the pointers meet.
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(1)
 * ============================================================================== */

class Solution {
public:
    int maxArea(vector<int>& height)
    {
        int n = height.size();
        int l = 0, r = n - 1;
        int max_area = 0;

        while (l < r) {
            // Calculate current area
            int curr_area = (r - l) * min(height[l], height[r]);
            max_area = max(max_area, curr_area);

            // Move pointer with smaller height inward
            if (height[l] < height[r]) {
                l++;
            }
            else if (height[r] < height[l]) {
                r--;
            }
            else {
                // If equal, move both
                l++;
                r--;
            }
        }

        return max_area;
    }
};

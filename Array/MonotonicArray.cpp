#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// Problem: Check if Array is Monotonic
// Approach:
// - An array is monotonic if it is entirely non-increasing or non-decreasing.
// - We check if both conditions hold for all adjacent pairs.
// Complexity: O(n) time, O(1) space
// ============================================================================

class Solution {
public:
    bool isMonotonic(vector<int>& nums)
    {
        int n = nums.size();
        bool increasing = true, decreasing = true;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) decreasing = false;
            if (nums[i] < nums[i - 1]) increasing = false;
        }

        return increasing || decreasing;
    }
};

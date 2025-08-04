#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 189: Rotate Array
 * ==============================================================================
 * Problem:
 * Given an integer array `nums` and an integer `k`, rotate the array to the right
 * by `k` steps, where `k` is non-negative.
 *
 * Approach: Extra Space + Modulo Rotation
 * - Normalize `k` to `k % n` to avoid unnecessary full rotations.
 * - Store the last `k` elements followed by the first `n-k` elements into a new array.
 * - Assign the new array back to `nums`.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * ============================================================================= */

class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        int n = nums.size();
        k = k % n;  // Handle k > n

        vector<int> ans;

        // Append last k elements
        for (int i = n - k; i < n; ++i) {
            ans.push_back(nums[i]);
        }

        // Append first n - k elements
        for (int i = 0; i < n - k; ++i) {
            ans.push_back(nums[i]);
        }

        nums = ans;
    }
};

/* ==============================================================================
 * LeetCode 189: Rotate Array (In-Place Version)
 * ==============================================================================
 * Problem:
 * Given an integer array `nums` and an integer `k`, rotate the array to the right
 * by `k` steps, where `k` is non-negative.
 *
 * Approach: Reverse Three Segments (In-Place)
 * - Normalize `k` to `k % n`.
 * - Reverse the entire array.
 * - Reverse the first `k` elements.
 * - Reverse the remaining `n - k` elements.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        int n = nums.size();
        k = k % n;

        // Helper function to reverse subarray
        auto reverse = [&](int start, int end) {
            while (start < end) {
                std::swap(nums[start++], nums[end--]);
            }
            };

        // Reverse entire array
        reverse(0, n - 1);

        // Reverse first k elements
        reverse(0, k - 1);

        // Reverse remaining elements
        reverse(k, n - 1);
    }
};


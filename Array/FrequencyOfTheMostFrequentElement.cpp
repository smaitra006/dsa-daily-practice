#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Frequency of the Most Frequent Element (LeetCode 1838)
//
// Task:
// The frequency of an element is the number of times it appears in an array.
// You are allowed to perform at most `k` operations, where in one operation
// you increment any element by 1.
//
// Return the maximum possible frequency of the most frequent element after
// performing at most `k` operations.
//
// Example:
//   Input:  nums = [1,2,4], k = 5
//   Output: 3
//   Explanation: Increment 1 two times and 2 three times to make nums = [4,4,4].
//
//   Input:  nums = [1,4,8,13], k = 5
//   Output: 2
//
// Approach (Binary Search + Prefix Sum):
// 1. Sort the array to work with increasing order of numbers.
// 2. Maintain a prefix sum array for efficient subarray sum calculation.
// 3. For each index (target_idx), treat nums[target_idx] as the target value.
// 4. Use binary search to find the farthest left index that can be increased
//    to nums[target_idx] using at most k operations.
// 5. Calculate maximum frequency window length accordingly.
//==============================================================================

class Solution {
public:
    // Binary search to find max frequency window ending at target_idx
    int bSearch(int target_idx, int k, vector<long long>& prefixSum, vector<int>& nums)
    {
        int target = nums[target_idx];
        int best_idx = target_idx;
        int l = 0, r = target_idx;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            // Window [mid ... target_idx]
            int windowSize = target_idx - mid + 1;
            long long windowSum = (long long)windowSize * target;

            // Original sum of elements in window
            long long originalSum = prefixSum[target_idx] - prefixSum[mid] + nums[mid];

            // Operations needed to make all elements = target
            int ops = windowSum - originalSum;

            if (ops > k) {
                l = mid + 1;    // Need fewer elements → move right
            }
            else {
                best_idx = mid; // Feasible → try expanding left
                r = mid - 1;
            }
        }

        return target_idx - best_idx + 1;
    }

    int maxFrequency(vector<int>& nums, int k)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        // Build prefix sum array
        vector<long long> prefixSum(n);
        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        int result = 0;
        for (int target_idx = 0; target_idx < n; target_idx++) {
            result = max(result, bSearch(target_idx, k, prefixSum, nums));
        }

        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Sorting: O(N log N)
// - Prefix sum: O(N)
// - For each index (N), binary search takes O(log N).
// - Total: O(N log N)
//
// - Space: O(N) for prefix sum array.
//
// Example Walkthrough:
// Input: nums = [1,2,4], k = 5
// Sorted: [1,2,4]
// For target=4: window [0..2] → ops = 7 - 3 = 4 ≤ 5 → frequency = 3
// Output: 3
//==============================================================================

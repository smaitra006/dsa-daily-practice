#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Kth Largest Element in an Array (LeetCode 215)
//
// Task:
// Given an integer array `nums` and an integer `k`, return the `k`th largest
// element in the array.
//
// Example:
//   Input:  nums = [3,2,1,5,6,4], k = 2
//   Output: 5
//
//   Input:  nums = [3,2,3,1,2,4,5,5,6], k = 4
//   Output: 4
//
// Approach (Max Heap):
// 1. Push all elements into a max-heap (priority_queue).
// 2. Pop the top (largest) element k-1 times.
// 3. The top element now is the kth largest.
//==============================================================================

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        priority_queue<int> pq;

        // Build max-heap
        for (auto i : nums) {
            pq.push(i);
        }

        // Pop k-1 largest elements
        for (int i = 0; i < k - 1; i++) {
            pq.pop();
        }

        // kth largest element
        return pq.top();
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N log N), for pushing all N elements into the heap.
// - Space: O(N), for the heap.
// - Note: Can be optimized to O(N log k) using min-heap of size k.
//
// Example Walkthrough:
// Input: nums = [3,2,1,5,6,4], k=2
// Max-heap: [6,5,4,3,2,1]
// Pop 1 time → top=5
// Output: 5
//==============================================================================
